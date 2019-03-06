#include <Laplace/BinaryFile.h>
#include <Laplace/Filter.h>
#include <Laplace/Bitmap.h>



void displayHelpAndExit(void);
void loadBitmap(const char *path, Bitmap *bitmap);
void applyFilter(Bitmap *bitmap);
void saveBitmap(const char *path, Bitmap *bitmap);



/**
 * Main function.
 */
int main(int argc, const char *argv[]) {
    if(argc != 2) {
        displayHelpAndExit();
    }
    
    Bitmap bitmap;
    
    loadBitmap(argv[1], &bitmap);
    applyFilter(&bitmap);
    saveBitmap("out.bmp", &bitmap);
    
    bitmapDelete(&bitmap);
    return EXIT_SUCCESS;
}


/**
 * Displays proper usage of program and exits.
 */
void displayHelpAndExit(void) {
    puts("Usage: Laplace [path to BMP file]");
    exit(EXIT_FAILURE);
}


/**
 * Loads bitmap.
 */
void loadBitmap(const char *path, Bitmap *bitmap) {
    switch(bitmapLoadFromFile(path, bitmap)) {
        case BITMAP_FILE_ERROR:
            fputs("Error opening bitmap.\n", stderr);
            exit(EXIT_FAILURE);
            
        case BITMAP_UNSUPPORTED_TYPE:
            fputs("Unsupported bitmap.\n", stderr);
            exit(EXIT_FAILURE);
    }
}


/**
 * Apllies filter to bitmap.
 */
void applyFilter(Bitmap *bitmap) {
    if(filterApplyToBitmap(LaplaceFilter, bitmap) == FILTER_ERROR) {
        fputs("Error applying filter", stderr);
        bitmapDelete(bitmap);
        exit(EXIT_FAILURE);
    }
}


/**
 * Saves processed bitmap.
 */
void saveBitmap(const char *path, Bitmap *bitmap) {
    if(bitmapSaveToFile(bitmap, path) == BINFILE_ERROR_WRITING_FILE) {
        fputs("Error saving bitmap.\n", stderr);
        bitmapDelete(bitmap);
        exit(EXIT_FAILURE);
    }
}
