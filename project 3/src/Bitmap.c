#include <string.h>
#include <Laplace/Bitmap.h>
#include <Laplace/BinaryFile.h>


#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))



/**
 * Loads bitmap from file and checks if it is supported one.
 * @param path Path to file to load bitmap from.
 * @param bitmap Structure which will represent loaded bitmap.
 * @return 0 on success, BITMAP_FILE_ERROR or BITMAP_UNSUPPORTED_TYPE.
 */
int bitmapLoadFromFile(const char *path, Bitmap *bitmap) {
    size_t filesize;
    uint8_t *buffer = NULL;
    
    if((filesize = binfileLoad(path, (void**)&buffer)) == BINFILE_ERROR_OPENING_FILE) {
        return BITMAP_FILE_ERROR;
    }
    
       // Return if file is too small
    if(filesize <= sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) ||
       // Or if file doesn't start with BM
       (bitmap->fileHeader = (BitmapFileHeader*)buffer)->magic != BITMAP_MAGIC ||
       // Or if pixels data offset is too big
       (uint8_t*)(bitmap->pixels = (RGBTriple*)(buffer + bitmap->fileHeader->offset)) - buffer > (long)filesize ||
       // Or if picture is compressed
       (bitmap->infoHeader = (BitmapInfoHeader*)(buffer + sizeof(BitmapFileHeader)))->compression != 0) {
        free(buffer);
        return BITMAP_UNSUPPORTED_TYPE;
    }
    
    bitmap->fileHeader->filesize = (uint32_t)filesize;
    bitmap->padding = (4 - ((bitmap->infoHeader->width * 3) % 4)) % 4;
    return 0;
}



/**
 * Gets one pixel of picture from given bitmap.
 * @param bitmap Bitmap to get pixel from.
 * @param x X coordinate of pixel in bitmap.
 * @param y Y coordinate of pixel in bitmap.
 * @return Requesting pixel or white pixel if x or y exceeds picture bounds.
 */
RGBTriple bitmapGetPixel(Bitmap *bitmap, uint32_t x, uint32_t y) {
    if(x >= bitmap->infoHeader->width || y >= bitmap->infoHeader->height) {
        return (RGBTriple){ 255, 255, 255 };
    }
    
    uint32_t offset = y * (bitmap->infoHeader->width * sizeof(RGBTriple) + bitmap->padding);
    offset += x * sizeof(RGBTriple);
    return *(RGBTriple*)((uint8_t*)bitmap->pixels + offset);
}



/**
 * Changes pixel in given bitmap.
 * @param bitmap Bitmap to change pixel in.
 * @param x X coordinate of pixel to change.
 * @param y Y coordinate of pixel to change.
 */
void bitmapSetPixel(Bitmap *bitmap, uint32_t x, uint32_t y, RGBTriple pixel) {
    if(x >= bitmap->infoHeader->width || y >= bitmap->infoHeader->height) {
        return;
    }
    
    uint32_t offset = y * (bitmap->infoHeader->width * sizeof(RGBTriple) + bitmap->padding);
    offset += x * sizeof(RGBTriple);
    memcpy((uint8_t*)bitmap->pixels + offset, &pixel, sizeof(RGBTriple));
}



/**
 * Makes copy of given bitmap.
 * @param destination This structure will represent copied bitmap.
 * @param source Bitmap to copy.
 * @return Copied bitmap or NULL on error.
 */
Bitmap *bitmapMakeCopy(Bitmap *destination, Bitmap *source) {
    uint8_t *buffer;
    
    if(!(buffer = malloc(source->fileHeader->filesize))) {
        return NULL;
    }
    
    memcpy(buffer, source->fileHeader, source->fileHeader->filesize);
    
    destination->fileHeader = (BitmapFileHeader*)buffer;
    destination->infoHeader = (BitmapInfoHeader*)(buffer + sizeof(BitmapFileHeader));
    destination->padding = source->padding;
    destination->pixels = (RGBTriple*)(buffer + destination->fileHeader->offset);
    
    return destination;
}



/**
 * Saves bitmap to file.
 * @param bitmap Bitmap to sacve.
 * @param path Path to file to save bitmap to.
 * @return 0 on success or BINFILE_ERROR_WRITING_FILE.
 */
int bitmapSaveToFile(Bitmap *bitmap, const char *path) {
    return binfileSave(path, bitmap->fileHeader, bitmap->fileHeader->filesize);
}



/**
 * Deletes given bitmap from memory.
 * @param bitmap Bitmap to delete.
 */
void bitmapDelete(Bitmap *bitmap) {
    free((void*)bitmap->fileHeader);
}
