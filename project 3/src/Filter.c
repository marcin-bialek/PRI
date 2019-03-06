#include <stdarg.h>
#include <string.h>
#include <Laplace/Filter.h>


#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))



/**
 * Applies filter to given pixel in bitmap.
 * @param filter Filter to apply.
 * @param bitmap Bitmap to apply filter to.
 * @param x X coordinate of pixel to filter.
 * @param y Y coordinate of pixel to filter.
 * @return Pixel after applying filter. Oryginal pixel will not be changed.
 */
RGBTriple applyFilterToPixel(Filter filter, Bitmap *bitmap, uint32_t x, uint32_t y) {
    RGBTriple tmp;
    int red = 0, green = 0, blue = 0;
    
    for(int a = 0, b = -(FILTER_DIMMENSION / 2); a < FILTER_DIMMENSION; a++, b++) {
        for(int c = 0, d = -(FILTER_DIMMENSION / 2); c < FILTER_DIMMENSION; c++, d++) {
            tmp = bitmapGetPixel(bitmap, x + b, y + d);
            
            red += (int)tmp.red * filter.weights[a][c];
            green += (int)tmp.green * filter.weights[a][c];
            blue += (int)tmp.blue * filter.weights[a][c];
        }
    }
    
    return (RGBTriple){
        MAX(MIN(blue / filter.divisor + filter.offset, 255), 0),
        MAX(MIN(green / filter.divisor + filter.offset, 255), 0),
        MAX(MIN(red / filter.divisor + filter.offset, 255), 0)
    };
}



/**
 * Applies filter to whole bitmap.
 * @param filter Filter to apply.
 * @param bitmap Bitmap to apply filter to.
 * @return 0 on success or FILTER_ERROR.
 */
int filterApplyToBitmap(Filter filter, Bitmap *bitmap) {
    Bitmap tmp;
    RGBTriple pixel;
    
    if(!bitmapMakeCopy(&tmp, bitmap)) {
        return FILTER_ERROR;
    }
    
    for(uint32_t y = 0; y < bitmap->infoHeader->height; y++) {
        for(uint32_t x = 0; x < bitmap->infoHeader->width; x++) {
            pixel = applyFilterToPixel(filter, bitmap, x, y);
            bitmapSetPixel(&tmp, x, y, pixel);
        }
    }
    
    bitmapDelete(bitmap);
    bitmapMakeCopy(bitmap, &tmp);
    bitmapDelete(&tmp);
    return 0;
}



const Filter LaplaceFilter = {{
    { -1, -1, -1 },
    { -1,  8, -1 },
    { -1, -1, -1 }
}, 0.75, 0 };
