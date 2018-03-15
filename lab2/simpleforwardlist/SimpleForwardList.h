//
// Created by dell on 11.03.2018.
//

#ifndef JIMP_EXERCISES_SIMPLEFORWARDLIST_H
#define JIMP_EXERCISES_SIMPLEFORWARDLIST_H


typedef struct List{
    int value;
    struct List *next;
}ForwardList;

ForwardList *CreateNode(int value);
void DestroyList(ForwardList *head);
ForwardList *PushFront(ForwardList *list, int value);


#endif //JIMP_EXERCISES_SIMPLEFORWARDLIST_H
