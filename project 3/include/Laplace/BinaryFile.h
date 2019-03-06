#pragma once
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>


// Error codes
#define BINFILE_ERROR_OPENING_FILE 0
#define BINFILE_ERROR_WRITING_FILE 1


size_t binfileLoad(const char *path, void **buffer);
int binfileSave(const char *path, void *source, size_t size);
