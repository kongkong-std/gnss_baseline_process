#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h>

// data structure
/*
 * linked list item, contains
 *     1. year(int)/month(int)/day(int)
 *     2. hour(int)/minute(int)/second(double)
 *     3. x(double)  y(double) z(double) ratio(double)
 */
typedef struct item_linked_list
{
    int year, month, day;
    int hour, minute;
    double second;
    double x, y, z;
    double ratio;
} Item_LinkedList;

/*
 * node of linked list
 *     1. linked list item
 *     2. pointer to next node
 */
typedef struct node_linked_list
{
    Item_LinkedList item;
    struct node_linked_list *next;
} Node_LinkedList;

/*
 * linked list
 *     1. head node of linked list
 *     2. size of linked list
 */
typedef struct list_linked_list
{
    Node_LinkedList *head;
    int size;
} List_LinkedList;

// function prototype
/*
 * initialize linked list
 *     null linked list
 *     size = 0
 */
void InitializeLinkedList(List_LinkedList *);

/*
 * determine whether linked list empty or not
 * if empty, return 1
 * if not empty, return 0
 */
int IsLinkedListEmpty(const List_LinkedList *);

/*
 * determine whether linked list full or not
 * if full, return 1
 * if not full, return 0
 */
int IsLinkedListFull(const List_LinkedList *);

/*
 * add item to linked list
 * if add successfully, return 1
 * if add unsuccessfully, return 0
 */
int AddItemToLinkedList(Item_LinkedList, List_LinkedList *);

/*
 * linked list traversal with function pointer
 */
void TraverseLinkedList(const List_LinkedList *, void (*pFun)(Item_LinkedList));

/*
 * destroy linked list
 */
void DestroyLinkedList(List_LinkedList *);

#endif