#include <Liga/DataFile.h>


/**
 * Reads clubs from file and adds them to given list.
 * @param list List to append clubs.
 * @param filename Path to file.
 */
int addClubsFromFile(List* list, char* filename) {
    FILE *file;
    
    if(!(file = fopen(filename, "r"))) {
        return 1;
    }
    
    Club club;
    while(!feof(file)) {
        fscanf(file, "%[^\n]%*c %[^\n]%*c %[^\n]%*c %[^\n]%*c %[^\n]%*[\n]", club.id, club.name, club.city, club.establishmentYear, club.stadiumCapacity);
        
        if(!clubAppend(list, club)) {
            return 1;
        }
    }
    
    fclose(file);
    return 0;
}



