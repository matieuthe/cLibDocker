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

/*
 * Return an empty initialize container
 */
struct CONTAINER * init_container();

/*
 * result
 */
void get_Json(struct CONTAINER * container, char ** result);

/*
 *  Function to set automatically the parameter and realloc memory
 */
void set_Id(struct CONTAINER * container, char * Id);
void set_Image(struct CONTAINER * container, char * Image);
void set_Hostname(struct CONTAINER * container, char * Hostname);
void set_Domainname(struct CONTAINER * container, char * Domainname);
void set_User(struct CONTAINER * container, char * User);
void set_AttachStdin(struct CONTAINER * container, char * AttachStdin);
void set_AttachStdout(struct CONTAINER * container, char * AttachStdout);
void set_AttachStderr(struct CONTAINER * container, char * AttachStderr);
void set_Tty(struct CONTAINER * container, char * Tty);
void set_OpenStdin(struct CONTAINER * container, char * OpenStdin);
void set_StdinOnce(struct CONTAINER * container, char * StdinOnce);
void set_Entrypoint(struct CONTAINER * container, char * Entrypoint);
void set_WorkingDir(struct CONTAINER * container, char * WorkingDir);
void set_NetworkDisabled(struct CONTAINER * container, char * NetworkDisabled);
void set_MacAddress(struct CONTAINER * container, char * MacAddress);
void set_StopSignal(struct CONTAINER * container, char * StopSignal);
void set_StopTimeout(struct CONTAINER * container, char * StopTimeout);

/*
 * Free the memory used by the structure
 */
void free_container(struct CONTAINER * container);

#endif

