#ifndef cLibDocker_h
#define cLibDocker_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>

struct Docker {
    CURL * curl;
    char ** idContainers;
    int nbContainers;
    int sizeTab;
};

void init_docker(struct Docker * docker);

int start_container(struct Docker * docker, char * data);

int statut_containers(struct Docker * docker);

int rm_container(struct Docker * docker, int indice);
    
void close_docker(struct Docker * docker);

#endif
