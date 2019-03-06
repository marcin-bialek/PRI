#include <Liga/List.h>
#include <Liga/Menu.h>
#include <Liga/DataFile.h>


void drawUserInterface(size_t);
void handleOption(uintmax_t, List*);


/**
 * Main function.
 */
int main(int argc, const char *argv[]) {
    setBanner(3, GREEN, (const char*[]) {
        "Katalog ligii piłkarskiej (by Marcin Białek)",
        "Nawigacja: ↑, ↓ i ENTER",
        ""
    });
    
    List *clubsList = listCreate();
    addClubsFromFile(clubsList, argc > 1 ? (char*)argv[1] : "data.txt");
    
    for(;;) {
        clearScreen();
        drawUserInterface(clubsList->size);
        handleOption(menuNavigate(), clubsList);
    }
    
    return 0;
}


/**
 * Displays main menu.
 * @param numberOfClubs Number of clubs to display.
 */
void drawUserInterface(size_t numberOfClubs) {
    printf("Liczba drużyn: %zu\r\n\n", numberOfClubs);
    
    drawMenu(4, (char*[]){
        "Dodaj drużynę",
        "Wyświetl/edytuj drużyny",
        "Generuj terminarz spotkań",
        "Wyjście"
    });
}


/**
 * Quits an app.
 * @param list List of clubs (needed to delete).
 */
void quit(List* list) {
    listDeleteWithValues(list);
    setBanner(0, WHITE, NULL);
    clearScreen();
    exit(0);
}


/**
 * Function to handle main menu options.
 * @param option Option to handle.
 * @param list List of clubs.
 */
void handleOption(uintmax_t option, List *list) {
    switch(option) {
        case 0: menuAddClub(list);
            break;
        case 1: menuShowClubs(list);
            break;
        case 2: menuGenerateSchedule(list);
            break;
        case 3: quit(list);
    }
}
