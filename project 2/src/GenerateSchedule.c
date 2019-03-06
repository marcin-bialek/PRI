#include <Liga/Menu.h>


void menuTooLessClubs(List*);
void displaySchedule(List*);


/**
 * Checks if number of clubs is even. If yes, displays schedule. If not, displays warning.
 * @param list List of clubs.
 */
void menuGenerateSchedule(List *list) {
    clearScreen();
    
    if(list->size == 0 || list->size % 2 == 1) {
        menuTooLessClubs(list);
        return;
    }
    
    displaySchedule(list);
    
    printf("\n");
    drawMenu(1, (char*[]) { "Wróć" });
    menuNavigate();
}


/**
 * Displays warning that number of clubs is not even.
 * @param list List of clubs.
 */
void menuTooLessClubs(List *list) {
    printf("Liczba drużyn musi być parzysta.\n\n");
    drawMenu(2, (char*[]) {
        "Dodaj drużynę",
        "Wróć"
    });
    
    if(menuNavigate() == 0) {
        menuAddClub(list);
    }
}


/**
 * Displays schedule.
 * @param list List of clubs.
 */
void displaySchedule(List *list) {
    List* pairsList = listCreate();
    listGeneratePairs(list, pairsList);
    Pair* pair;
    
    for(int p = 0; p < 2; p++) {
        listResetIterator(pairsList);
        
        for(uintmax_t i = 0; i < list->size - 1; i++) {
            boldOn();
            printf("\n%s połowa - Tydzień %ju\n\n", p ? "Druga" : "Pierwsza", i + 1);
            resetAttributes();
            
            for(uintmax_t j = 0; j < list->size / 2; j++) {
                pair = (Pair*)listNextNode(pairsList)->value;
                
                printfInTable(4, ((Club*)pair->first)->name);
                printf(" %s", ((Club*)pair->first)->city);
                
                printfInTable(4 + 2 * CLUB_MAX_STR_LEN, ((Club*)pair->second)->name);
                printf(" %s\n", ((Club*)pair->second)->city);
            }
        }
    }
    
    listDeleteWithValues(pairsList);
}













