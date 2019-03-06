#pragma once
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>


// Error codes
#define BITMAP_FILE_ERROR 1
#define BITMAP_UNSUPPORTED_TYPE 2

// BMP magic
#define BITMAP_MAGIC 0x4d42 /* BM */



// Header of BMP file (starting at offset 0)
typedef struct {
    uint16_t magic;         // First two bytes of BMP file (must be equal to BITMAP_MAGIC)
    uint32_t filesize;      // Size of BMP file in bytes
    uint32_t reserved;
    uint32_t offset;        // Offset where picture data starts
} __attribute__((packed)) BitmapFileHeader;



// Info header of BMP file (starting at offset 0x0E)
typedef struct {
    uint32_t size;          // Size of bitmap info header (version)
    uint32_t width;         // Width of bitmap in pixels
    uint32_t height;        // Height of bitmap in pixels
    uint16_t planes;
    uint16_t bitCount;      // Number of bits per pixel
    uint32_t compression;   // Type of compression (0 for none)
} __attribute__((packed)) BitmapInfoHeader;



// Structure of one pixel where each color occupies 1 byte (bitCount in BitmapInfoHeader = 24)
typedef struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} __attribute__((packed)) RGBTriple;



// Bitmap structure
typedef struct {
    BitmapFileHeader *fileHeader;   // Pointer to BitmapFileHeader (also beggining of BMP file in memory)
    BitmapInfoHeader *infoHeader;   // Pointer to BitmapInfoHeader
    RGBTriple *pixels;              // Pointer to first RGBTriple (beggining of picture data)
    uint8_t padding;                // Padding in picture data (0 - 3)
} Bitmap;



int bitmapLoadFromFile(const char *path, Bitmap *bitmap);
int bitmapSaveToFile(Bitmap *bitmap, const char *path);

Bitmap *bitmapMakeCopy(Bitmap *destination, Bitmap *source);
void bitmapDelete(Bitmap *bitmap);

RGBTriple bitmapGetPixel(Bitmap *bitmap, uint32_t x, uint32_t y);
void bitmapSetPixel(Bitmap *bitmap, uint32_t x, uint32_t y, RGBTriple pixel);

