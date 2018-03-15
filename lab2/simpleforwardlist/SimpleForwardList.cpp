//
// Created by dell on 11.03.2018.
//

#include "SimpleForwardList.h"

ForwardList *CreateNode(int value) {
    ForwardList *head=new ForwardList;
    head->value=value;
    head->next= nullptr;
     return head;
}

void DestroyList(ForwardList *head) {
    //ForwardList new_head=head;
    while (head!= nullptr){
        ForwardList *tmp=head->next;
        delete head;
        head=tmp;
    }
}

ForwardList *PushFront(ForwardList *list, int value) {
    //ForwardList *old_head=list;
    if (list!= nullptr){
        ForwardList *new_head=new ForwardList;
        new_head->value=value;
        new_head->next=list;
        return new_head;
    }
    return nullptr;
}
