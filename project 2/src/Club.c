#include <Liga/Club.h>
#include <Liga/List.h>


int clubCheckIfExists(List*, Club*);
ListNode* clubFindPlaceForClub(List*, Club*);


/**
 * Appends club to given list provided that same one doesn't already exist.
 * Clubs will be ordered alphabetically by name and city.
 * @param list List of clubs.
 * @param club Club to append.
 * @return List node with value of given club or NULL
 *         if club with same id or name and city already exist.
 */
ListNode* clubAppend(List *list, Club club) {
    Club *c = malloc(sizeof(Club));
    
    if(!c) {
        return NULL;
    }
    
    strcpy(c->id, club.id);
    strcpy(c->name, club.name);
    strcpy(c->city, club.city);
    strcpy(c->establishmentYear, club.establishmentYear);
    strcpy(c->stadiumCapacity, club.stadiumCapacity);
    
    if(clubCheckIfExists(list, c)) {
        free(c);
        return NULL;
    }
    
    return listInsert(list, c, clubFindPlaceForClub(list, c));
}


/**
 * Daletes club from list.
 * @param list List of clubs.
 * @param club List node with value of club to delete.
 */
void clubDelete(List *list, ListNode *club) {
    free(club->value);
    listRemoveNode(list, club);
}


/**
 * Returns pointer to club with id of 'id'.
 * @param list List of clubs.
 * @param id Id of club.
 * @return Pointer to club or NULL if club doesn't exist.
 */
Club* clubGetById(List *list, char *id) {
    listResetIterator(list);
    ListNode *node;
    
    while((node = listNextNode(list))) {
        if(!strcmp(((Club*)node->value)->id, id)) {
            return (Club*)node->value;
        }
    }
    
    return NULL;
}


/**
 * Returns pointer to club with name of 'name' and city of 'city'.
 * @param list List of clubs.
 * @param name Name of club.
 * @param city City of club.
 * @return Pointer to club or NULL if club doesn't exist.
 */
Club* clubGetByNameAndCity(List *list, char *name, char *city) {
    listResetIterator(list);
    ListNode *node;
    Club *club;
    
    while((node = listNextNode(list))) {
        club = (Club*)node->value;
        
        if(!strcmp(club->name, name) && !strcmp(club->city, city)) {
            return club;
        }
    }
    
    return NULL;
}


/**
 * Checks if club with same id or name and city exists.
 * @param list List of clubs.
 * @param club Club to check.
 * @return 1 if club exists or 0 if doesn't.
 */
int clubCheckIfExists(List *list, Club *club) {
    if(clubGetById(list, club->id) || clubGetByNameAndCity(list, club->name, club->city)) {
        return 1;
    }
    
    return 0;
}



ListNode* clubFindPlaceForClub(List *list, Club *club) {
    listResetIterator(list);
    
    ListNode *node = NULL;
    Club *c;
    for(uintmax_t i = 0; i < list->size; i++) {
        node = listNextNode(list);
        c = (Club*)node->value;
        
        if(strcmp(c->name, club->name) > 0) {
            return node->previous;
        }
        else if(strcmp(c->name, club->name) == 0 && strcmp(c->city, club->city) > 0) {
            return node->previous;
        }
    }
    
    return node;
}

