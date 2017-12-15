#include "container.h"
#define NB_PARAM 20

void init_container(struct CONTAINER * container){
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
}

void set_Id(struct CONTAINER * container, char * Id){
    realloc(container->Id, (strlen(Id) + 1) * sizeof(char));
    strcpy(container->Id, Id);
}

void set_Image(struct CONTAINER * container, char * Image){
    realloc(container->Image, (strlen(Image) + 1) * sizeof(char));
    strcpy(container->Image, Image);
}

void getJson(struct CONTAINER * container, char * result){
    result[0] = '{';
    result[1] = '\0';
    int precedent = 0;
    
    if(container->Id[0] != '\0'){
        strcat(result, "\"Id\":\"");
        strcat(result, container->Id);
        strcat(result, "\"");
        precedent = 1;
    }
    
    if(container->Image[0] != '\0'){
        if(precedent)
            strcat(result, ",");
        strcat(result, "\"Image\":\"");
        strcat(result, container->Image);
        strcat(result, "\"");
    }
    
    strcat(result, "}");
}




















