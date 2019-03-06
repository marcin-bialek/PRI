#include <Liga/Terminal.h>


static struct Menu {
    size_t size;
    uintmax_t selectedOption;
} menu = { 0, 0 };


static struct Banner {
    size_t size;
    const char** lines;
    ForegroundColor color;
} banner = { 0, NULL, WHITE };


/**
 * Tells terminal not to buffer stdin.
 */
void getRawInputFromTerminal(void) {
    system("/bin/stty raw");
}


/**
 * Tells terminal to buffer stdin.
 */
void resetTerminal(void) {
    system("/bin/stty cooked");
}


/**
 * Moves cursor up in terminal by given number of lines.
 */
void moveCursorUp(uintmax_t numberOfLines) {
    printf("\x1b[%juA", numberOfLines);
}

/**
 * Moves cursor down in terminal by given number of lines.
 */
void moveCursorDown(uintmax_t numberOfLines) {
    printf("\x1b[%juB", numberOfLines);
}


/**
 * Moves cursor left in terminal by given number of columns.
 */
void moveCursorLeft(uintmax_t numberOfColumns) {
    printf("\x1b[%juD", numberOfColumns);
}


/**
 * Moves cursor right in terminal by given number of columns.
 */
void moveCursorRight(uintmax_t numberOfColumns) {
    printf("\x1b[%juC", numberOfColumns);
}


/**
 * Clears line where the cursor currently is.
 */
void clearLine(void) {
    printf("\r\x1b[K\r");
}


/**
 * Clears current line and 'numberOfLines' lines above it.
 */
void clearLinesUp(uintmax_t numberOfLines) {
    for(uintmax_t i = 0; i < numberOfLines; i++) {
        clearLine();
        moveCursorUp(1);
    }
    
    clearLine();
}


/**
 * Clears screen of terminal and writes text set by setBanner function.
 */
void clearScreen(void) {
    system("clear");
    
    for(size_t i = 0; i < banner.size; i++) {
        printfColor(banner.color, banner.lines[i]);
        printf("\r\n");
    }
}


/**
 * Sets text which will be shown on the top of terminal after calling clearScreen function.
 * @param size Number of lines of text.
 * @param color Color of text.
 * @param lines Array of strings.
 */
void setBanner(size_t size, ForegroundColor color, const char* lines[]) {
    banner.size = size;
    banner.lines = lines;
    banner.color = color;
}


/**
 * Sets color of text in terminal.
 */
void setForegroundColor(ForegroundColor color) {
    printf("\x1b[%dm", color);
}


/**
 * Writes text in given color.
 * @param color Color of text.
 * @param str Text to write.
 */
void printfColor(ForegroundColor color, const char* str) {
    setForegroundColor(color);
    printf("%s", str);
    setForegroundColor(WHITE);
}


/**
 * Gets text from stdin.
 * @param color Color of text in terminal.
 * @param str A pointer to buffer where text will be saved.
 * @param limit Max number of chars to read.
 */
void fgetsColor(ForegroundColor color, char *str, int limit) {
    setForegroundColor(color);
    
    int i = 0;
    for(int c; (c = fgetc(stdin)) != EOF; i++) {
        if (c == '\n') {
            break;
        }
        
        else if (i + 1 < limit) {
            str[i] = c;
        }
    }
    
    str[i] = '\0';
    
    setForegroundColor(WHITE);
}


/**
 * Draws menu like:
 *   [•]  Option 1
 *   [ ]  Option 2
 *   [ ]  Option 3
 *         ...
 * @param size Number of options in menu.
 * @param optionsName Names of option in menu.
 */
void drawMenu(size_t size, char** optionsName) {
    menu.size = size;
    menu.selectedOption = 0;
    
    clearLine();
    
    for(size_t i = 0; i < menu.size; i++) {
        printf("[ ]  %s\r\n", optionsName ? optionsName[i] : "");
    }
    
    moveCursorUp(menu.size);
    moveCursorRight(1);
    printfColor(MENU_ACCENT_COLOR, "•");
    moveCursorDown(menu.size);
    printf("\r");
}


/**
 * Select option in menu drawn by drawMenu function.
 * Cursor must be right below menu!
 * @param option Index of option to select (0 - first option).
 */
static void menuSelectOption(uintmax_t option) {
    menu.selectedOption = option % menu.size;
    
    moveCursorUp(menu.size);
    moveCursorRight(2);
    
    for(size_t i = 0; i < menu.size; i++) {
        moveCursorLeft(1);
        
        if(i == menu.selectedOption) {
            printfColor(MENU_ACCENT_COLOR, "•");
        }
        else {
            printf(" ");
        }
        
        moveCursorDown(1);
    }
    
    printf("\r");
}


/**
 * Allows user to select options by up and down arrow keys in menu drawn by drawMenu function.
 * Returns selected option if user press enter.
 * Cursor must be right below menu!
 * @return Index of selected option.
 */
uintmax_t menuNavigate(void) {
    getRawInputFromTerminal();
    
    while(1) {
        char key = getchar();
        clearLine();
        
        switch(key) {
            case 65: menuSelectOption(menu.selectedOption + menu.size - 1);
            break;
                
            case 66: menuSelectOption(menu.selectedOption + 1);
            break;
                
            case 13: resetTerminal();
            return menu.selectedOption;
        }
    }
}


/**
 * Writes text in console shifted to the right by given number of columns.
 * @param offset Number of columns to shift text to the right.
 * @param str Text to write.
 */
void printfInTable(uintmax_t offset, char *str) {
    printf("\r");
    moveCursorRight(offset);
    printf("%s", str);
}


/**
 * Text in terminal will be bolded.
 */
void boldOn(void) {
    printf("\x1b[1m");
}

/**
 * Disables all terminal attributes (like bolding text).
 */
void resetAttributes(void) {
    printf("\x1b[0m");
}

