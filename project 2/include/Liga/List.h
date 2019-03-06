//
//  List.h
//  Project 2
//
//  Created by Marcin Białek on 03/12/2018.
//  Copyright © 2018 Marcin Białek. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


typedef struct ListNode {
    void *value;
    struct ListNode *next;
    struct ListNode *previous;
} ListNode;


typedef struct {
    size_t size;
    ListNode *current;
    ListNode *head;
    ListNode *back;
} List;


typedef struct {
    void *first;
    void *second;
} Pair;


List* listCreate(void);
void listDelete(List*);
void listDeleteWithValues(List*);
void listResetIterator(List*);
void listSetIteratorToBack(List*);
ListNode* listAppend(List*, void*);
ListNode* listInsert(List*, void*, ListNode*);
ListNode* listRemoveNode(List*, ListNode*);
ListNode* listNextNode(List*);
ListNode* listPreviousNode(List*);
ListNode* listGetNodeByIndex(List*, uintmax_t);
void listGeneratePairs(List*, List*);

