#include <Liga/List.h>


/**
 * Creates new list.
 * @return A pointer to list.
 */
List* listCreate() {
    List *list = malloc(sizeof(List));
    list->head = list->back = list->current = NULL;
    list->size = 0;
    
    return list;
}


/**
 * Creates new list element.
 * @param any A pointer to value.
 * @return A pointer to list element.
 */
ListNode* listNewNode(void *any) {
    ListNode *node = malloc(sizeof(ListNode));
    
    if(node) {
        node->value = any;
    }
    
    return node;
}


/**
 * Appends node to the end of a list.
 * @param node Node to append.
 * @return A pointer to appended node.
 */
ListNode* listAppendNode(List *list, ListNode *node) {
    if(!list || !node) {
        return NULL;
    }
    
    if(list->back) {
        list->back->next = node;
    }
    
    node->next = NULL;
    node->previous = list->back;
    list->back = node;
    
    if(!list->head) {
        list->head = list->back;
    }
    
    listResetIterator(list);
    list->size++;
    return node;
}


/**
 * Creates new node with value of 'any' and appends it to the end of a list.
 * @param any Value to append.
 * @return A pointer to appended node.
 */
ListNode* listAppend(List *list, void *any) {
    return listAppendNode(list, listNewNode(any));
}


/**
 * Appends node to the begining of a list.
 * @param node Node to append.
 * @return A pointer to appended node.
 */
ListNode* listPushFront(List *list, ListNode *node) {
    if(!list->head) {
        return listAppendNode(list, node);
    }
    
    node->previous = NULL;
    node->next = list->head;
    list->head->previous = node;
    list->head = node;
    listResetIterator(list);
    
    return node;
}


/**
 * Inserts node after 'after' node.
 * @param node Node to insert.
 * @param after Node after which new node will be inserted.
 * @return A pointer to inserted node.
 */
ListNode* listInsertNode(List *list, ListNode *node, ListNode *after) {
    if(!list || !node) {
        return NULL;
    }
    
    if(!after) {
        return listPushFront(list, node);
    }
    
    node->next = after->next;
    node->previous = after;
    after->next = node;
    
    if(node->next) {
        node->next->previous = node;
    }
    else {
        list->back = node;
    }
    
    listResetIterator(list);
    list->size++;
    return node;
}


/**
 * Inserts node with value of 'any' after 'after' node.
 * @param any Value to insert.
 * @param after Node after which new node will be inserted.
 * @return A pointer to inserted node.
 */
ListNode* listInsert(List *list, void *any, ListNode *after) {
    return listInsertNode(list, listNewNode(any), after);
}


/**
 * Removes node from list but doesn't dealloc it from memory.
 * @param node Node to remove.
 * @return A pointer to removed node.
 */
ListNode* listRemoveNode(List *list, ListNode *node) {
    if(node->previous) {
        node->previous->next = node->next;
    }
    else {
        list->head = node->next;
    }
    
    if(node->next) {
        node->next->previous = node->previous;
    }
    else {
        list->back = node->previous;
    }
    
    listResetIterator(list);
    list->size--;
    return node;
}


/**
 * Sets 'current' pointer to the begging of a list.
 */
void listResetIterator(List *list) {
    list->current = list->head;
}


/**
 * Sets 'current' pointer to the end of a list.
 */
void listSetIteratorToBack(List *list) {
    list->current = list->back;
}


/**
 * Returns node pointed by 'current' and sets 'current' to the next node.
 * @return Node pointed by 'current' or NULL
 */
ListNode* listNextNode(List *list) {
    if(!list->current) {
        return NULL;
    }
    
    ListNode *node = list->current;
    list->current = list->current->next;
    return node;
}


/**
 * Sets 'current' to the previous node and returns node pointed by 'current'.
 * @return Previous node or NULL
 */
ListNode* listPreviousNode(List *list) {
    if(!list->current) {
        return NULL;
    }
    
    list->current = list->current->previous;
    return list->current;
}


/**
 * Dealloc list and its nodes from memory but keeps values pointed by nodes.
 */
void listDelete(List* list) {
    listResetIterator(list);
    
    for(uintmax_t i = 0; i < list->size; i++) {
        free(listNextNode(list));
    }
    
    free(list);
}


/**
 * Dealloc list, its nodes and values from memory.
 */
void listDeleteWithValues(List* list) {
    listResetIterator(list);
    ListNode *node;
    
    for(uintmax_t i = 0; i < list->size; i++) {
        node = listNextNode(list);
        free(node->value);
        free(node);
    }
    
    free(list);
}


/**
 * Gets node by its index where 0 is index of head of a list.
 * @param index Index of node.
 * @return Node with index of 'index'
 */
ListNode* listGetNodeByIndex(List *list, uintmax_t index) {
    if(index > list->size - 1) {
        return NULL;
    }
    
    listResetIterator(list);
    ListNode *node = listNextNode(list);
    
    for(uintmax_t i = 0; i < index; i++) {
        node = listNextNode(list);
    }
    
    return node;
}


/**
 * Generates all possible pairs of list nodes (list size must be even).
 * @param pairsList List where pairs will be appended.
 */
void listGeneratePairs(List *list, List *pairsList) {
    list->head->next->previous = list->back;
    list->head->previous = list->back;
    list->back->next = list->head->next;
    ListNode *last;
    
    for(uintmax_t i = 0; i < list->size - 1; i++) {
        list->current = list->head;
        last = list->head->previous;
        
        for(uintmax_t j = 0; j < list->size / 2; j++) {
            Pair *pair = malloc(sizeof(Pair));
            pair->first = list->current->value;
            pair->second = last->value;
            
            listAppend(pairsList, pair);
            
            list->current = list->current->next;
            last = last->previous;
        }
        
        list->head->previous = list->head->previous->previous;
        list->head->next = list->head->previous->next;
    }
    
    list->head->next->previous = list->head;
    list->head->previous = NULL;
    list->back->next = NULL;
}
