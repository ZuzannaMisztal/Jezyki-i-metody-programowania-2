//
// Created by dell on 11.03.2018.
//

#include "SimpleForwardList.h"

struct Node{
    int value;
    Node *next;
};

struct ForwardList{
    //Node *Head;
    int value;
    Node *next;
    //Node *Tail;
};

ForwardList *CreateNode(int value) {
    /*Node new_node;
    Node *nodeptr= &new_node;
    nodeptr->value=value;
    nodeptr->next= nullptr;
    ForwardList *new_list;
    new_list->Head=nodeptr;
    //new_list->Tail= nullptr;
    */
    ForwardList *head;
    head->value=value;
    head->next= nullptr;
     return head;
}

void DestroyList(ForwardList head){
    delete &head;
}