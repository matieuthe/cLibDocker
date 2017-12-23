#ifndef container_h
#define container_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
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
} CONTAINER;

/*
 * Return an empty initialize container with memory allocated
 */
CONTAINER * new_container();

/*
 *  Reinit the container in parameters
 */
void init_container(CONTAINER * container);


/*
 * Return a Json representation of the container to use it with into docker
 * Result is automatically realloc
 */
void get_Json(CONTAINER * container, char ** result);

/*
 *  Function to set automatically the parameter and realloc memory
 *  Return 1 if the operation works and 0 if not
 */
int set_Id(CONTAINER * container, char * Id);
int set_Image(CONTAINER * container, char * Image);
int set_Hostname(CONTAINER * container, char * Hostname);
int set_Domainname(CONTAINER * container, char * Domainname);
int set_User(CONTAINER * container, char * User);
int set_AttachStdin(CONTAINER * container, char * AttachStdin);
int set_AttachStdout(CONTAINER * container, char * AttachStdout);
int set_AttachStderr(CONTAINER * container, char * AttachStderr);
int set_Tty(CONTAINER * container, char * Tty);
int set_OpenStdin(CONTAINER * container, char * OpenStdin);
int set_StdinOnce(CONTAINER * container, char * StdinOnce);
int set_Entrypoint(CONTAINER * container, char * Entrypoint);
int set_WorkingDir(CONTAINER * container, char * WorkingDir);
int set_NetworkDisabled(CONTAINER * container, char * NetworkDisabled);
int set_MacAddress(CONTAINER * container, char * MacAddress);
int set_StopSignal(CONTAINER * container, char * StopSignal);
int set_StopTimeout(CONTAINER * container, char * StopTimeout);

/*
 *  Copy the struct origin into dst
 */
void copy_container(const CONTAINER * origin, CONTAINER * dst);

/*
 * Free the memory used by the structure
 */
void free_container(CONTAINER * container);

#endif

