#include "container.h"
#define NB_PARAM 20

//Private function
void catChaineJson(char * containerElmt, char * elmtName,char * result, int * precedent);
int set_param_Container(char ** param, char * value);

/**************************************************************************
 * Init function
 **************************************************************************/
void init_container(CONTAINER * container){
    container->Id = NULL;
    container->Hostname = NULL;
    container->Domainname = NULL;
    container->User = NULL;
    container->AttachStdin = NULL;
    container->AttachStdout = NULL;
    container->AttachStderr = NULL;
    container->Tty = NULL;
    container->OpenStdin = NULL;
    container->StdinOnce = NULL;
    container->Entrypoint = NULL;
    container->Image = NULL;
    container->WorkingDir = NULL;
    container->NetworkDisabled = NULL;
    container->MacAddress = NULL;
    container->StopSignal = NULL;
    container->StopTimeout = NULL;
    
    container->nbCmd = 0;
    container->nbEnv = 0;
    container->maxEnv = 10;
    container->maxCmd = 10;
    container->Cmd = (char **)malloc(10 * sizeof(char *));
    container->Env = (char **)malloc(10 * sizeof(char *));

    for(int i = 0; i < 10; i++){
        container->Cmd[i] = NULL;
        container->Env[i] = NULL;
    }
}

CONTAINER * new_container(){
    CONTAINER * container = (CONTAINER *)malloc(sizeof(CONTAINER));
    init_container(container);

    return container;
}

/**************************************************************************
 * Setter Function
 **************************************************************************/
int set_param_Container(char ** param, char * value){
    if(value != NULL){
        *param = (char *)realloc(*param, (strlen(value) + 1) * sizeof(char));
        
        if(param == NULL)
            printf("ERROR : realloc hasn't work\n");
        else
        {
            strcpy(*param, value);
            return 1;
        }
    }else{
        *param = NULL;
        return 1;
    }
    return 0;
}

int set_Id(CONTAINER * container, char * Id){
    return set_param_Container(&container->Id, Id);
}

int set_Image(CONTAINER * container, char * Image){
    return set_param_Container(&container->Image, Image);
}

int set_Hostname(CONTAINER * container, char * Hostname){
    return set_param_Container(&container->Hostname, Hostname);
}

int set_Domainname(CONTAINER * container, char * Domainname){
    return set_param_Container(&container->Domainname, Domainname);
}

int set_User(CONTAINER * container, char * User){
    return set_param_Container(&container->User, User);
}

int set_AttachStdin(CONTAINER * container, char * AttachStdin){
    return set_param_Container(&container->AttachStdin, AttachStdin);
}

int set_AttachStdout(CONTAINER * container, char * AttachStdout){
    return set_param_Container(&container->AttachStdout, AttachStdout);
}

int set_AttachStderr(CONTAINER * container, char * AttachStderr){
    return set_param_Container(&container->AttachStderr, AttachStderr);
}

int set_Tty(CONTAINER * container, char * Tty){
    return set_param_Container(&container->Tty, Tty);
}

int set_OpenStdin(CONTAINER * container, char * OpenStdin){
    return set_param_Container(&container->OpenStdin, OpenStdin);
}

int set_StdinOnce(CONTAINER * container, char * StdinOnce){
    return set_param_Container(&container->StdinOnce, StdinOnce);
}

int set_Entrypoint(CONTAINER * container, char * Entrypoint){
    return set_param_Container(&container->Entrypoint, Entrypoint);
}

int set_WorkingDir(CONTAINER * container, char * WorkingDir){
    return set_param_Container(&container->WorkingDir, WorkingDir);
}

int set_NetworkDisabled(CONTAINER * container, char * NetworkDisabled){
    return set_param_Container(&container->NetworkDisabled, NetworkDisabled);
}

int set_MacAddress(CONTAINER * container, char * MacAddress){
    return set_param_Container(&container->MacAddress, MacAddress);
}

int set_StopSignal(CONTAINER * container, char * StopSignal){
    return set_param_Container(&container->StopSignal, StopSignal);
}

int set_StopTimeout(CONTAINER * container, char * StopTimeout){
    return set_param_Container(&container->StopTimeout, StopTimeout);
}

/**************************************************************************
 * Complex parameters of the struct
 **************************************************************************/
int add_Command_Container(CONTAINER * container, char * command){
    if(container->nbCmd == container->maxCmd){
        //reallocation memoire
    }

    if(command != NULL){
        container->Cmd[container->nbCmd] = (char *)realloc(container->Cmd[container->nbCmd],(strlen(command) + 1) * sizeof(char));
        if(container->Cmd[container->nbCmd] != NULL){
            strcpy(container->Cmd[container->nbCmd++], command);
            return 1;
        }
    }
    else
        return 1;
    return 0;
}

/**************************************************************************
 * JSON maker function
 **************************************************************************/
void get_Json(CONTAINER * container, char ** res){
    char result[10000];
    result[0] = '{';
    result[1] = '\0';
    int precedent = 0;
    
    catChaineJson(container->Id, "Id", result, &precedent);
    catChaineJson(container->Image, "Image", result, &precedent);
    
    catChaineJson(container->Hostname, "Hostname", result, &precedent);
    catChaineJson(container->Domainname, "Domainname", result, &precedent);
    catChaineJson(container->User, "User", result, &precedent);
    catChaineJson(container->AttachStdin, "AttachStdin", result, &precedent);
    catChaineJson(container->AttachStdout, "AttachStdout", result, &precedent);
    catChaineJson(container->AttachStderr, "AttachStderr", result, &precedent);
    catChaineJson(container->Tty, "Tty", result, &precedent);
    catChaineJson(container->OpenStdin, "OpenStdin", result, &precedent);
    catChaineJson(container->StdinOnce, "StdinOnce", result, &precedent);
    catChaineJson(container->Entrypoint, "Entrypoint", result, &precedent);
    catChaineJson(container->WorkingDir, "WorkingDir", result, &precedent);
    catChaineJson(container->NetworkDisabled, "NetworkDisabled", result, &precedent);
    catChaineJson(container->MacAddress, "MacAddress", result, &precedent);
    catChaineJson(container->StopSignal, "StopSignal", result, &precedent);
    catChaineJson(container->StopTimeout, "StopTimeout", result, &precedent);
    strcat(result, "}");
    
    *res = NULL; //In case of a non init param
    *res = (char *)realloc(*res, (strlen(result) + 1) * sizeof(char));
    
    strcpy(*res, result);
}

void catChaineJson(char * containerElmt, char * elmtName,char * result, int * precedent){
    if(containerElmt != NULL){
        if(*precedent)
            strcat(result, ",");
        strcat(result, "\"");
        strcat(result, elmtName);
        strcat(result, "\":\"");
        strcat(result, containerElmt);
        strcat(result, "\"");
        *precedent = 1;
    }
}

/**************************************************************************
 * Free memory
 **************************************************************************/
void free_container(CONTAINER * container){
    //Free the char *
    free(container->Id);
    free(container->Hostname);
    free(container->Domainname);
    free(container->User);
    free(container->AttachStdin);
    free(container->AttachStdout);
    free(container->AttachStderr);
    free(container->Tty);
    free(container->OpenStdin);
    free(container->StdinOnce);
    free(container->Entrypoint);
    free(container->Image);
    free(container->WorkingDir);
    free(container->NetworkDisabled);
    free(container->MacAddress);
    free(container->StopSignal);
    free(container->StopTimeout);
    
    for(int i = 0; i < container->maxCmd; i++)
        free(container->Cmd[i]);
    for(int i = 0; i < container->maxEnv; i++)
        free(container->Env[i]);
    free(container->Cmd);
    free(container->Env);
    
    //Free the container itself
    free(container);
}

/**************************************************************************
 * Copy function
 **************************************************************************/
void copy_container(const CONTAINER * origin, CONTAINER * dst){
    set_Id(dst, origin->Id);
    set_Image(dst, origin->Image);
    set_Hostname(dst, origin->Hostname);
    set_Domainname(dst, origin->Domainname);
    set_User(dst, origin->User);
    set_AttachStdin(dst, origin->AttachStdin);
    set_AttachStdout(dst, origin->AttachStdout);
    set_AttachStderr(dst, origin->AttachStderr);
    set_Tty(dst, origin->Tty);
    set_OpenStdin(dst, origin->OpenStdin);
    set_StdinOnce(dst, origin->StdinOnce);
    set_Entrypoint(dst, origin->Entrypoint);
    set_WorkingDir(dst, origin->WorkingDir);
    set_NetworkDisabled(dst, origin->NetworkDisabled);
    set_MacAddress(dst, origin->MacAddress);
    set_StopSignal(dst, origin->StopSignal);
    set_StopTimeout(dst, origin->StopTimeout);
}
