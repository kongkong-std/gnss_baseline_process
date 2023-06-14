#include "../include/linked_list.h"

void InitializeLinkedList(List_LinkedList *pList)
{
    pList->head = NULL;
    pList->size = 0;
}

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

    free( temp );

    return value;
}

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
