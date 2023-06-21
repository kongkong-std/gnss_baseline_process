/**
 * @file linked_list.c
 * @author Zikang Qin
 * @brief linked list implementation, contains linked list generation,
 * initialize linked list, add item to linked list, destroy linked list,
 * traversal of linked list
 *
 * @version 0.1
 * @date 2023-06-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../include/linked_list.h"

/**
 * @callgraph
 * @brief initialize linked list
 *
 * @param [in,out] pList linked list
 */
void InitializeLinkedList(List_LinkedList *pList)
{
    pList->head = NULL;
    pList->size = 0;
}

/**
 * @callgraph
 * @brief check if linked list is empty,
 * if empty, return 1; else, return 0
 *
 * @param [in] pList linked list
 * @return int(1) empty linked list, int(0) not empty linked list
 */
int IsLinkedListEmpty(const List_LinkedList *pList)
{
    int value = 0;

    if (pList->head == NULL)
    {
        value = 1;
    }
    else
    {
        value = 0;
    }

    return value;
}

/**
 * @callgraph
 * @brief check if linked list if full,
 * if full, return 1; else, return 0
 *
 * @param [in] pList linked list
 * @return int(1) full linked list, int(0) non full linked list
 */
int IsLinkedListFull(const List_LinkedList *pList)
{
    int value = 0;
    Node_LinkedList *temp = NULL;

    if ((temp = (Node_LinkedList *)malloc(sizeof(Node_LinkedList))) == NULL)
    {
        value = 1;
    }
    else
    {
        value = 0;
    }

    free(temp);

    return value;
}

/**
 * @callgraph
 * @brief add new item to linked list,
 * add to tail of current linked list,
 * if add successfully, return 1, else return 0
 * 
 * @param [in] item struct variant
 * @param [in,out] pList linked list
 * @return int(1) add successfully, int(0) add unsuccessfully
 */
int AddItemToLinkedList(Item_LinkedList item, List_LinkedList *pList)
{
    int value = 0;

    Node_LinkedList *pNewNode = NULL;
    Node_LinkedList *pTmpNode = pList->head;

    if ((pNewNode = (Node_LinkedList *)malloc(sizeof(Node_LinkedList))) == NULL)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        value = 0;
        return value;
    }

    pNewNode->item = item;
    pNewNode->next = NULL;

    if (pTmpNode == NULL)
    {
        // add to head of linked list
        pList->head = pNewNode;
        pList->size += 1;
        value = 1;
    }
    else
    {
        // add to tail of linked list
        while (pTmpNode->next != NULL)
        {
            pTmpNode = pTmpNode->next;
        }
        pTmpNode->next = pNewNode;
        pList->size += 1;
        value = 1;
    }

    return value;
}

/**
 * @callgraph
 * @brief traversal of linked list,
 * from head of linked list to tail
 * of linked list, with function pointer
 * 
 * @param [in] pList linked list
 * @param [in] pFun function pointer
 */
void TraverseLinkedList(const List_LinkedList *pList, void (*pFun)(Item_LinkedList item))
{
    Node_LinkedList *pTmpNode = pList->head;

    printf("total node is %d\n", pList->size);

    int index = 0;
    while (pTmpNode != NULL)
    {
        printf("\nnode %d:\n", ++index);
        (*pFun)(pTmpNode->item);
        pTmpNode = pTmpNode->next;
    }
}

/**
 * @callgraph
 * @brief free memory of linked list
 * 
 * @param [in,out] pList linked list 
 */
void DestroyLinkedList(List_LinkedList *pList)
{
    pList->size = 0;

    Node_LinkedList *pTmpNode = NULL;
    while (pList->head != NULL)
    {
        pTmpNode = pList->head->next;
        free(pList->head);
        pList->head = pTmpNode;
    }
}
