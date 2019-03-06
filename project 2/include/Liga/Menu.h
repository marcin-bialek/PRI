//
//  Menu.h
//  Project 2
//
//  Created by Marcin Białek on 01/12/2018.
//  Copyright © 2018 Marcin Białek. All rights reserved.
//

#pragma once

#include "Terminal.h"
#include "Club.h"
#include <inttypes.h>


void menuAddClub(List*);
void menuShowClubs(List*);
void menuGenerateSchedule(List*);

void menuClubExistsError(void);

