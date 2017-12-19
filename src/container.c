#include "container.h"
#define NB_PARAM 20

void catChaineJson(char * containerElmt, char * elmtName,char * result, int * precedent);

/**************************************************************************
 * Init function
 **************************************************************************/
struct CONTAINER * init_container(){
    struct CONTAINER * container = (struct CONTAINER *)malloc(sizeof(struct CONTAINER));
    //Id
    container->Id = (char *)malloc(sizeof(char));
    container->Id[0] = '\0';
    
    //Hostname
    container->Hostname = (char *)malloc(sizeof(char));
    container->Hostname[0] = '\0';
    
    //Domainname
    container->Domainname = (char *)malloc(sizeof(char));
    container->Domainname[0] = '\0';

    //User
    container->User = (char *)malloc(sizeof(char));
    container->User[0] = '\0';
    
    //AttachStdin
    container->AttachStdin = (char *)malloc(sizeof(char));
    container->AttachStdin[0] = '\0';
    
    //AttachStdout
    container->AttachStdout = (char *)malloc(sizeof(char));
    container->AttachStdout[0] = '\0';
    
    //AttachStderr
    container->AttachStderr = (char *)malloc(sizeof(char));
    container->AttachStderr[0] = '\0';
    
    //Tty
    container->Tty = (char *)malloc(sizeof(char));
    container->Tty[0] = '\0';
    
    //OpenStdin
    container->OpenStdin = (char *)malloc(sizeof(char));
    container->OpenStdin[0] = '\0';
    
    //StdinOnce
    container->StdinOnce = (char *)malloc(sizeof(char));
    container->StdinOnce[0] = '\0';

    //Entrypoint
    container->Entrypoint = (char *)malloc(sizeof(char));
    container->Entrypoint[0] = '\0';
    
    //Image
    container->Image = (char *)malloc(sizeof(char));
    container->Image[0] = '\0';
    
    //WorkingDir
    container->WorkingDir = (char *)malloc(sizeof(char));
    container->WorkingDir[0] = '\0';
    
    //NetworkDisabled
    container->NetworkDisabled = (char *)malloc(sizeof(char));
    container->NetworkDisabled[0] = '\0';
    
    //MacAddress
    container->MacAddress = (char *)malloc(sizeof(char));
    container->MacAddress[0] = '\0';
    
    //StopSignal
    container->StopSignal = (char *)malloc(sizeof(char));
    container->StopSignal[0] = '\0';
    
    //StopTimeout
    container->StopTimeout = (char *)malloc(sizeof(char));
    container->StopTimeout[0] = '\0';
    
    return container;
}

/**************************************************************************
 * Setter Function
 **************************************************************************/
void set_Id(struct CONTAINER * container, char * Id){
    container->Id = realloc(container->Id, (strlen(Id) + 1) * sizeof(char));
    strcpy(container->Id, Id);
}

void set_Image(struct CONTAINER * container, char * Image){
    container->Image = realloc(container->Image, (strlen(Image) + 1) * sizeof(char));
    strcpy(container->Image, Image);
}

void set_Hostname(struct CONTAINER * container, char * Hostname){
    container->Hostname = realloc(container->Hostname, (strlen(Hostname) + 1) * sizeof(char));
    strcpy(container->Hostname, Hostname);
}

void set_Domainname(struct CONTAINER * container, char * Domainname){
    container->Domainname = realloc(container->Domainname, (strlen(Domainname) + 1) * sizeof(char));
    strcpy(container->Domainname, Domainname);
}

void set_User(struct CONTAINER * container, char * User){
    container->User = realloc(container->User, (strlen(User) + 1) * sizeof(char));
    strcpy(container->User, User);
}

void set_AttachStdin(struct CONTAINER * container, char * AttachStdin){
    container->AttachStdin =  realloc(container->AttachStdin, (strlen(AttachStdin) + 1) * sizeof(char));
    strcpy(container->AttachStdin, AttachStdin);
}

void set_AttachStdout(struct CONTAINER * container, char * AttachStdout){
    container->AttachStdout = realloc(container->AttachStdout, (strlen(AttachStdout) + 1) * sizeof(char));
    strcpy(container->AttachStdout, AttachStdout);
}

void set_AttachStderr(struct CONTAINER * container, char * AttachStderr){
    container->AttachStderr = realloc(container->AttachStderr, (strlen(AttachStderr) + 1) * sizeof(char));
    strcpy(container->AttachStderr, AttachStderr);
}

void set_Tty(struct CONTAINER * container, char * Tty){
    container->Tty = realloc(container->Tty, (strlen(Tty) + 1) * sizeof(char));
    strcpy(container->Tty, Tty);
}

void set_OpenStdin(struct CONTAINER * container, char * OpenStdin){
    container->OpenStdin = realloc(container->OpenStdin, (strlen(OpenStdin) + 1) * sizeof(char));
    strcpy(container->OpenStdin, OpenStdin);
}

void set_StdinOnce(struct CONTAINER * container, char * StdinOnce){
    container->StdinOnce = realloc(container->StdinOnce, (strlen(StdinOnce) + 1) * sizeof(char));
    strcpy(container->StdinOnce, StdinOnce);
}

void set_Entrypoint(struct CONTAINER * container, char * Entrypoint){
    container->Entrypoint = realloc(container->Entrypoint, (strlen(Entrypoint) + 1) * sizeof(char));
    strcpy(container->Entrypoint, Entrypoint);
}

void set_WorkingDir(struct CONTAINER * container, char * WorkingDir){
    container->WorkingDir = realloc(container->WorkingDir, (strlen(WorkingDir) + 1) * sizeof(char));
    strcpy(container->WorkingDir, WorkingDir);
}

void set_NetworkDisabled(struct CONTAINER * container, char * NetworkDisabled){
    container->NetworkDisabled = realloc(container->NetworkDisabled, (strlen(NetworkDisabled) + 1) * sizeof(char));
    strcpy(container->NetworkDisabled, NetworkDisabled);
}

void set_MacAddress(struct CONTAINER * container, char * MacAddress){
    container->MacAddress = realloc(container->MacAddress, (strlen(MacAddress) + 1) * sizeof(char));
    strcpy(container->MacAddress, MacAddress);
}

void set_StopSignal(struct CONTAINER * container, char * StopSignal){
    container->StopSignal = realloc(container->StopSignal, (strlen(StopSignal) + 1) * sizeof(char));
    strcpy(container->StopSignal, StopSignal);
}

void set_StopTimeout(struct CONTAINER * container, char * StopTimeout){
    container->StopTimeout = realloc(container->StopTimeout, (strlen(StopTimeout) + 1) * sizeof(char));
    strcpy(container->StopTimeout, StopTimeout);
}

/**************************************************************************
 * JSON maker function
 **************************************************************************/
void get_Json(struct CONTAINER * container, char ** res){
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
    
    *res = (char *)realloc(*res, (strlen(result) + 1) * sizeof(char));
    
    strcpy(*res, result);
    //free(result);
}

void catChaineJson(char * containerElmt, char * elmtName,char * result, int * precedent){
    if(containerElmt[0] != '\0'){
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
void free_container(struct CONTAINER * container){
    //Free the char *
    //free(container->Id);
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
    
    //Free the struct itself
    free(container);
}

