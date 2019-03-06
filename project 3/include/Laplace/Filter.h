#pragma once
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <Laplace/Bitmap.h>


// Error codes
#define FILTER_ERROR 1

// Dimmension of filter matrix
#define FILTER_DIMMENSION 3


typedef struct {
    int weights[FILTER_DIMMENSION][FILTER_DIMMENSION];  // Matrix of weights
    float divisor;  // Each value will be divided by this variable after applying matrix
    int offset;     // This variable will be added to each value after applying matrix and division
} Filter;



int filterApplyToBitmap(Filter filter, Bitmap *bitmap);


// Predefined filters
extern const Filter LaplaceFilter;
