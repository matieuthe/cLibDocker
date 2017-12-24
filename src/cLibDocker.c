#include "cLibDocker.h"
#define ID_SIZE 64

int init_curl(DOCKER * docker, char * url_request);
size_t default_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
size_t rm_All_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
int get_indice_container(const DOCKER * docker, const char * id);
int delete_container_indice(DOCKER * docker, const indice);

/************************************************************
 * Curl Function
*************************************************************/

int init_curl(DOCKER * docker, char * url_request){
    docker->curl = curl_easy_init();

    if(docker->curl){
        curl_easy_setopt(docker->curl, CURLOPT_UNIX_SOCKET_PATH, "/var/run/docker.sock");
        curl_easy_setopt(docker->curl, CURLOPT_URL, url_request);
        curl_easy_setopt(docker->curl, CURLOPT_HTTPGET, 1L);
    }else{
        fprintf( stderr, "Error init curl\n");
        return 0;
    }
    return 1;
}

/*
 *  CallBack function starting container
 */
size_t start_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
    DOCKER * docker = (DOCKER *)userdata;

    if(ptr[2] == 'I' && ptr[3] == 'd'){
        char res[ID_SIZE + 1];
        for(int i = 0; i < ID_SIZE; i++){
            res[i] = ptr[i+7];
        }
        res[ID_SIZE] = '\0';
        printf("CREATE : \"%s\" with id : %s \n", docker->containers[docker->nbContainers]->Image, res);
        set_Id(docker->containers[docker->nbContainers], res);
        docker->nbContainers++;
    }else{
        printf("ERROR : Creation of \"%s\" Impossible \n", docker->containers[docker->nbContainers]->Image);
    }
    return 0;
}

/*
 *  CallBack function status container
 */
size_t default_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
   // printf("%s", ptr);
    return 0;
}

/*
 * Print the reception message
 */
size_t print_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
    printf("%s", ptr);
    return 0;
}

/*************************************************************
 * Start container Function : start the container in parameter
 * and store a copy into the DOCKER struct
 *************************************************************/
int start_container(DOCKER * docker, CONTAINER * container){
    init_curl(docker, "http://localhost/containers/create");
    CURLcode res;
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(docker->curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(docker->curl, CURLOPT_HTTPHEADER, headers);
    
    //If the space to stock containers is too small
    if(docker->nbContainers == docker->sizeTab){
        docker->sizeTab+= 10;
        docker->containers = (CONTAINER **)realloc(docker->containers, docker->sizeTab * sizeof(CONTAINER *));
        for(int i = docker->sizeTab - 10; i < docker->sizeTab; i++)
            docker->containers[i] = new_container();
    }
    
    copy_container(container, docker->containers[docker->nbContainers]);
    
    char * data ;
    get_Json(container, &data);
    int lg = 0;
    if(data != NULL) lg = strlen(data);
    
    curl_easy_setopt(docker->curl, CURLOPT_POST, 1L);
    curl_easy_setopt(docker->curl, CURLOPT_POSTFIELDSIZE, lg);
    curl_easy_setopt(docker->curl, CURLOPT_POSTFIELDS, data);

    //Definition of the callBack Function
    curl_easy_setopt(docker->curl, CURLOPT_WRITEFUNCTION, start_callback);
    curl_easy_setopt(docker->curl, CURLOPT_WRITEDATA, docker);
    res = curl_easy_perform(docker->curl);
    
    free(data);
    return 1;
}

/************************************************************
 * Remove the container at indice in the docker struct
************************************************************/
int rm_container(DOCKER * docker, int indice){
    if(indice >= docker->nbContainers || indice < 0)
        return 0;
    
    //Build the url of the request
    char * url = "http://localhost/containers/";
    int sizeUrl = 28 + ID_SIZE + 1;
    char * urlId = (char *)malloc(sizeUrl * sizeof(char));
    strcpy(urlId, url);
    strcat(urlId, docker->containers[indice]->Id);

    urlId[sizeUrl - 1] = '\0';

    init_curl(docker, urlId);
    CURLcode res;
    curl_easy_setopt(docker->curl, CURLOPT_CUSTOMREQUEST, "DELETE");

    //Definition of the callBack Function
    curl_easy_setopt(docker->curl, CURLOPT_WRITEFUNCTION, default_callback);
    //Execution of the request
    res = curl_easy_perform(docker->curl);

    printf("DELETE : \"%s\" with id : %s\n", docker->containers[indice]->Image, docker->containers[indice]->Id);
    
    for(int i = indice; i < docker->nbContainers - 1; i++){
        CONTAINER *tmp = docker->containers[i];
        docker->containers[i] = docker->containers[i+1]; //Decalage des pointeur
        docker->containers[i+1] = tmp; //Pour éviter d'avoir des pointeurs vide ou deux pointeurs au même endroit
    }
    
    docker->nbContainers--;
    free(urlId);
    return 1;
}

int rm_stopped_containers(DOCKER * docker){
    init_curl(docker, "http://localhost/containers/prune");
    
    CURLcode res;
    curl_easy_setopt(docker->curl, CURLOPT_POST, 1L);
    //Definition of the callBack Function
    
    char * data = NULL;
    int lg = 0;
    
    curl_easy_setopt(docker->curl, CURLOPT_POST, 1L);
    curl_easy_setopt(docker->curl, CURLOPT_POSTFIELDSIZE, lg);
    curl_easy_setopt(docker->curl, CURLOPT_POSTFIELDS, data);
    
    //Definition of the callBack Function
    curl_easy_setopt(docker->curl, CURLOPT_WRITEFUNCTION, rm_All_callback);
    curl_easy_setopt(docker->curl, CURLOPT_WRITEDATA, docker);

    res = curl_easy_perform(docker->curl);
    return 1;
}

/*
 *  CallBack function to use
 */
size_t rm_All_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
    DOCKER * docker = (DOCKER *)userdata;
    int compteur = 23;
    char res[ID_SIZE + 1];

    while(ptr[compteur] != ',' && ptr[compteur] != ']' && ptr[compteur] != '"'){
        for(int i = 0; i < ID_SIZE; i++){
            res[i] = ptr[compteur++];
        }
        res[ID_SIZE] = '\0';
        int indice = get_indice_container(docker, res);
        if(indice >= 0) delete_container_indice(docker, indice);
        else
            printf("DELETE containers not in struct with id : %s", res);
        compteur+=3;
    }
    
    return 0;
}

int get_indice_container(const DOCKER * docker, const char * id){
    for(int i = 0; i < docker->nbContainers; i++)
        if(strncmp(docker->containers[i]->Id, id, ID_SIZE) == 0)
            return i;
    return -1;
}

int delete_container_indice(DOCKER * docker, const indice){
    if(indice >= docker->nbContainers || indice < 0)
        return 0;
    
    printf("DELETE : \"%s\" with id : %s\n", docker->containers[indice]->Image, docker->containers[indice]->Id);
    
    for(int i = indice; i < docker->nbContainers - 1; i++){
        CONTAINER *tmp = docker->containers[i];
        docker->containers[i] = docker->containers[i+1]; //Decalage des pointeur
        docker->containers[i+1] = tmp; //Pour éviter d'avoir des pointeurs vide ou deux pointeurs au même endroit
    }
    
    docker->nbContainers--;
    return 1;
}


/**********************************************************
 *  Get the statut of all containers running
 **********************************************************/
int statut_containers(DOCKER * docker){
    init_curl(docker, "http://localhost/containers/json");
    
    CURLcode res;
    //Definition of the callBack Function
    curl_easy_setopt(docker->curl, CURLOPT_WRITEFUNCTION, default_callback);
    
    res = curl_easy_perform(docker->curl);
    return 1;
}

/*********************************************************
 * Init and Quit function of the docker struct
 *********************************************************/
DOCKER * init_docker(){
    DOCKER * docker = (DOCKER *)malloc(sizeof(DOCKER));
    int i;
    docker->sizeTab = 0;
    docker->nbContainers = 0;
    
    docker->containers = (CONTAINER **)malloc(10 * sizeof(CONTAINER *));
    for(i = 0; i < 10; i++)
        docker->containers[i] = new_container();
    
    docker->sizeTab = 10;
    return docker;
}

void free_docker(DOCKER * docker){
    curl_easy_cleanup(docker->curl);
    //Free all the containers of the tab
    for(int i = 0; i < docker->sizeTab; i++)
        free_container(docker->containers[i]);
    free(docker);
}
