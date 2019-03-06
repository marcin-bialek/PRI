#include <Liga/Menu.h>


int verifyData(Club club);
void menuClubExistsError(void);


/**
 * Displays menu to add new club.
 * @param list List of clubs.
 */
void menuAddClub(List *list) {
    clearScreen();
    Club club;
    
    printf("Dodaj drużynę:\n\n");
    
    printfColor(WHITE, "  ID: ");
    fgetsColor(CYAN, club.id, CLUB_MAX_ID_LEN);
    
    printfColor(WHITE, "  Nazwa: ");
    fgetsColor(CYAN, club.name, CLUB_MAX_STR_LEN);

    printfColor(WHITE, "  Miasto: ");
    fgetsColor(CYAN, club.city, CLUB_MAX_STR_LEN);
    
    printfColor(WHITE, "  Pojemność stadionu: ");
    fgetsColor(CYAN, club.stadiumCapacity, CLUB_MAX_NUM_LEN);
    
    printfColor(WHITE, "  Rok założenia: ");
    fgetsColor(CYAN, club.establishmentYear, CLUB_MAX_NUM_LEN);
    
    if(!verifyData(club)) {
        wrongDataMenu();
        return;
    }
    
    printfColor(WHITE, "\n");
    drawMenu(2, (char*[]){
        "Zapisz",
        "Anuluj"
    });
    
    if(menuNavigate() == 0) {
        if(!clubAppend(list, club)) {
            clearLinesUp(2);
            menuClubExistsError();
        }
    }
}


/**
 * Displays 'wrong data' error.
 */
void wrongDataMenu(void) {
    printfColor(RED, "Niepoprawne dane\n");
    drawMenu(1, (char*[]){
        "Wróć"
    });
    menuNavigate();
}


/**
 * Displays 'club exists' error.
 */
void menuClubExistsError(void) {
    printfColor(RED, "Klub o takim samym id lub nazwie i mieście już istnieje.\n");
    drawMenu(1, (char*[]){
        "Wróć"
    });
    menuNavigate();
}


/**
 * Chceks if string contains at least one alphanumeric character.
 * @param string String to check.
 * @return 0 if string contains at least one alphanumeric character, 1 if not.
 */
int isEmpty(char *string) {
    for(size_t i = 0; i < strlen(string); i++) {
        if(isalnum(string[i])) return 0;
    }
    
    return 1;
}


/**
 * Chceks if string contains only digits.
 * @param string String to check.
 * @return 1 if string contains only digits, 0 if not.
 */
int isNumber(char *string) {
    if(isEmpty(string)) {
        return 0;
    }
        
    for(size_t i = 0; i < strlen(string); i++) {
        if(!isdigit(string[i])) {
            return 0;
        }
    }
    
    return 1;
}


/**
 * Checks if club data are correct.
 * @param club Club to check.
 * @return 1 if data are correct, 0 if not.
 */
int verifyData(Club club) {
    int a = isNumber(club.id);
    int b = !isEmpty(club.name);
    int c = !isEmpty(club.city);
    int d = isNumber(club.establishmentYear);
    int e = isNumber(club.stadiumCapacity);
    return a && b && c && d && e;
}
