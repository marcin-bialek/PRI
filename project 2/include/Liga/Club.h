//
//  Club.h
//  Project 2
//
//  Created by Marcin Białek on 19/11/2018.
//  Copyright © 2018 Marcin Białek. All rights reserved.
//

#pragma once

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include "List.h"

#define CLUB_MAX_ID_LEN 6
#define CLUB_MAX_STR_LEN 20
#define CLUB_MAX_NUM_LEN 10

typedef struct {
    char id[CLUB_MAX_ID_LEN];
    char name[CLUB_MAX_STR_LEN];
    char city[CLUB_MAX_STR_LEN];
    char stadiumCapacity[CLUB_MAX_NUM_LEN];
    char establishmentYear[CLUB_MAX_NUM_LEN];
} Club;


ListNode* clubAppend(List*, Club);
void clubDelete(List*, ListNode*);
Club* clubGetByNameAndCity(List*, char*, char*);


int isEmpty(char*);
int isNumber(char*);
void wrongDataMenu(void);
