//
//  Terminal.h
//  Project 2
//
//  Created by Marcin Białek on 30/11/2018.
//  Copyright © 2018 Marcin Białek. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


typedef enum {
    RED = 31,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
} ForegroundColor;

#define  MENU_ACCENT_COLOR  GREEN

void moveCursorUp(uintmax_t);
void moveCursorDown(uintmax_t);

void boldOn(void);
void resetAttributes(void);
void setForegroundColor(ForegroundColor);
void printfColor(ForegroundColor, const char*);
void printfInTable(uintmax_t, char*);
void fgetsColor(ForegroundColor, char*, int);
void setBanner(size_t, ForegroundColor, const char*[]);
void clearLinesUp(uintmax_t);
void clearLine(void);
void clearScreen(void);
void clearStdin(void);

void drawMenu(size_t, char**);
uintmax_t menuNavigate(void);

