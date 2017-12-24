#ifndef cLibDocker_h
#define cLibDocker_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>
#include "container.h"

typedef struct{
    CURL * curl;
    CONTAINER ** containers;
    int nbContainers;
    int sizeTab;
} DOCKER;

DOCKER * init_docker();

int start_container(DOCKER * docker, CONTAINER * container);
int statut_containers(DOCKER * docker);

int rm_container(DOCKER * docker, int indice);
int rm_stopped_containers(DOCKER * docker);
void free_docker(DOCKER * docker);

#endif
