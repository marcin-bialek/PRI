#include <Liga/Menu.h>
#include <Liga/List.h>


void displayClubsInfoInTable(List*);
void menuClubDetails(List*, ListNode*);
void menuEditClub(List*, Club*);
void menuDeleteClub(List*, ListNode*);


/**
 * Displays list of clubs and menu to edit them.
 * @param list List of clubs.
 */
void menuShowClubs(List *list) {
    clearScreen();
    
    boldOn();
    printfInTable(5, "Nazwa");
    printfInTable(6 + CLUB_MAX_STR_LEN, "Miasto");
    printfInTable(7 + 2 * CLUB_MAX_STR_LEN, "Rok zał.");
    printfInTable(8 + 2 * CLUB_MAX_STR_LEN + CLUB_MAX_NUM_LEN, "Poj. stadionu\n\n");
    resetAttributes();
    
    drawMenu(list->size + 1, NULL);
    displayClubsInfoInTable(list);
    
    boldOn();
    setForegroundColor(GREEN);
    printfInTable(5, "Wróć\n");
    resetAttributes();
    
    uintmax_t option = menuNavigate();
    if(option < list->size) {
        menuClubDetails(list, listGetNodeByIndex(list, option));
    }
}


/**
 * Lists clubs in formated table.
 * @param list List of clubs.
 */
void displayClubsInfoInTable(List* list) {
    moveCursorUp(list->size + 1);
    Club *club;
    
    listResetIterator(list);
    for(uintmax_t i = 0; i < list->size; i++) {
        club = (Club*)listNextNode(list)->value;
        
        printfInTable(5, club->name);
        printfInTable(6 + CLUB_MAX_STR_LEN, club->city);
        printfInTable(7 + 2 * CLUB_MAX_STR_LEN, club->establishmentYear);
        printfInTable(8 + 2 * CLUB_MAX_STR_LEN + CLUB_MAX_NUM_LEN, club->stadiumCapacity);
        
        moveCursorDown(1);
    }
}


/**
 * Dislays club details and menu to edit them.
 * @param list List of clubs.
 * @param club Node of club list with value of club to display/edit.
 */
void menuClubDetails(List *list, ListNode* club) {
    clearScreen();
    
    printf("ID: %s\n", ((Club*)club->value)->id);
    printf("Nazwa: %s\n", ((Club*)club->value)->name);
    printf("Miasto: %s\n", ((Club*)club->value)->city);
    printf("Rok założenia: %s\n", ((Club*)club->value)->establishmentYear);
    printf("Pojemność stadionu: %s\n\n", ((Club*)club->value)->stadiumCapacity);
    
    drawMenu(3, (char*[]){
        "Edytuj",
        "Usuń",
        "Wróć"
    });
    
    switch(menuNavigate()) {
        case 0: menuEditClub(list, (Club*)club->value);
            break;
        case 1: menuDeleteClub(list, club);
            break;
    }
}


/**
 * Displays menu to delete club.
 * @param list List of clubs.
 * @param club Node of club list with value of club to delete.
 */
void menuDeleteClub(List *list, ListNode* club) {
    clearScreen();
    
    printf("Czy na pewno usunąć %s %s?\n\n", ((Club*)club->value)->name, ((Club*)club->value)->city);
    
    drawMenu(2, (char*[]){
        "Nie",
        "Tak"
    });
    
    if(menuNavigate() == 1) {
        clubDelete(list, club);
    }
}


/**
 * Displays menu to edit club name.
 * @param list List of clubs.
 * @param club Club to edit.
 */
void editClubName(List *list, Club *club) {
    char name[CLUB_MAX_STR_LEN];
    
    printf("Nowa nazwa: ");
    fgetsColor(CYAN, name, CLUB_MAX_STR_LEN);
    
    if(isEmpty(name)) {
        wrongDataMenu();
        return;
    }
    
    if(clubGetByNameAndCity(list, name, club->city)) {
        menuClubExistsError();
        return;
    }
    
    strcpy(club->name, name);
}


/**
 * Displays menu to edit club city.
 * @param list List of clubs.
 * @param club Club to edit.
 */
void editClubCity(List *list, Club *club) {
    char city[CLUB_MAX_STR_LEN];
    
    printf("Nowe miasto: ");
    fgetsColor(CYAN, city, CLUB_MAX_STR_LEN);
    
    if(isEmpty(city)) {
        wrongDataMenu();
        return;
    }
    
    if(clubGetByNameAndCity(list, club->name, city)) {
        menuClubExistsError();
        return;
    }
    
    strcpy(club->city, city);
}


/**
 * Displays menu to edit club establishment year.
 * @param club Club to edit.
 */
void editClubEstablishmentYear(Club *club) {
    char establishmentYear[CLUB_MAX_NUM_LEN];
    
    printf("Nowy rok założenia: ");
    fgetsColor(CYAN, establishmentYear, CLUB_MAX_NUM_LEN);
    
    if(!isNumber(establishmentYear)) {
        wrongDataMenu();
        return;
    }
    
    strcpy(club->establishmentYear, establishmentYear);
}


/**
 * Displays menu to edit club stadium capacity.
 * @param club Club to edit.
 */
void editClubStadiumCapacity(Club *club) {
    char stadiumCapacity[CLUB_MAX_NUM_LEN];
    
    printf("Nowa pojemność stadionu: ");
    fgetsColor(CYAN, stadiumCapacity, CLUB_MAX_NUM_LEN);
    
    if(!isNumber(stadiumCapacity)) {
        wrongDataMenu();
        return;
    }
    
    strcpy(club->stadiumCapacity, stadiumCapacity);
}


/**
 * Displays menu to choose which club value user want to edit.
 * @param list List of clubs.
 * @param club Club to edit.
 */
void menuEditClub(List *list, Club *club) {
    clearLinesUp(3);
    printf("Wybierz pole do edycji:\n");
    
    drawMenu(5, (char*[]) {
        "Nazwa",
        "Miasto",
        "Rok założenia",
        "Pojemność stadionu",
        "Anuluj"
    });
    
    uintmax_t option = menuNavigate();
    clearLinesUp(6);
    
    switch(option) {
        case 0: editClubName(list, club);
            break;
        case 1: editClubCity(list, club);
            break;
        case 2: editClubEstablishmentYear(club);
            break;
        case 3: editClubStadiumCapacity(club);
            break;
    }
}

