#ifndef listContainer_h
#define listContainer_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <container.h>

struct nodeContainer{
    struct CONTAINER container;
    int key;
    struct nodeContainer *next;
}

struct containerList{
    struct nodeContainer *head = NULL;
    struct nodeContainer *current = NULL;
    int nbElmt = 0;
}

void addContainerToList();

#endif
