#include <Laplace/BinaryFile.h>


/**
 * Gets size of given file.
 */
size_t getFilesize(FILE *file) {
    fseek(file, 0, 2);
    size_t filesize = ftell(file) + 1;
    rewind(file);
    return filesize;
}



/**
 * Loads binary file into memory.
 * @param path Path to file.
 * @param buffer This pointer will point at the address of loaded file in memory.
 * @return Size of loaded file in bytes or BINFILE_ERROR_OPENING_FILE.
 */
size_t binfileLoad(const char *path, void **buffer) {
    FILE *file;
    
    // Opening file
    if(!(file = fopen(path, "rb"))) {
        fclose(file);
        return BINFILE_ERROR_OPENING_FILE;
    };
    
    size_t filesize = getFilesize(file);
    
    // Loading whole file into memory
    if(!(*buffer = malloc(filesize)) || !fread(*buffer, 1, filesize, file)) {
        free(*buffer);
        fclose(file);
        return BINFILE_ERROR_OPENING_FILE;
    }
    
    fclose(file);
    return filesize;
}



/**
 * Saves memory into file.
 * @param path Path to file where memory will be saved.
 * @param source Address where data to save starts at.
 * @param size Number of bytes to save.
 * @return 0 on success or BINFILE_ERROR_WRITING_FILE.
 */
int binfileSave(const char *path, void *source, size_t size) {
    FILE *file;
    
    if(!(file = fopen(path, "wb")) || !fwrite(source, 1, size, file)) {
        return BINFILE_ERROR_WRITING_FILE;
    };
    
    fclose(file);
    return 0;
}
