#ifndef container_h
#define container_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>

struct CONTAINER {
    char * Id;
    char * Hostname;
    char * Domainname;
    char * User;
    char * AttachStdin;
    char * AttachStdout;
    char * AttachStderr;
    char * Tty;
    char * OpenStdin;
    char * StdinOnce;
    //Env;
    //Cmd;
    char * Entrypoint;
    char * Image;
    //Labels
    //Volumes
    char * WorkingDir;
    char * NetworkDisabled;
    char * MacAddress;
    //ExposedPorts
    char * StopSignal;
    char * StopTimeout;
    //HostConfig
    //NetworkingConfig
};

void init_container(struct CONTAINER * container);

void set_Id(struct CONTAINER * container, char * Id);

void set_Image(struct CONTAINER * container, char * Image);

#endif

