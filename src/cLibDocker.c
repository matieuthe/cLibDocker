#include "cLibDocker.h"
#define ID_SIZE 64

int init_curl(DOCKER * docker, char * url_request);
size_t default_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

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
    
    if(strlen(ptr)>64 && ptr[6] == '"'){
        char res[ID_SIZE + 1];
        for(int i = 0; i < ID_SIZE; i++){
            res[i] = ptr[i+7];
        }
        res[ID_SIZE] = '\0';
        printf("Creation \"%s\" with id : %s \n", docker->containers[docker->nbContainers]->Image, res);
        set_Id(docker->containers[docker->nbContainers], res);
    }
    docker->nbContainers++;
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
 *  Start the containers specify in data
 */
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

/*
 * Remove a container
 */
int rm_container(DOCKER * docker, int indice){
    if(indice > docker->nbContainers || indice < 0)
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

    printf("Delete \"%s\" with id : %s\n", docker->containers[indice]->Image, docker->containers[indice]->Id);
    
    for(int i = indice; i < docker->nbContainers - 1; i++){
        CONTAINER *tmp = docker->containers[i];
        docker->containers[i] = docker->containers[i+1]; //Decalage des pointeur
        docker->containers[i+1] = tmp; //Pour éviter d'avoir des pointeurs vide ou deux pointeurs au même endroit
    }
    
    docker->nbContainers--;
    free(urlId);
    return 1;
}

/*
 *  Get the staut of all containers running
 */
int statut_containers(DOCKER * docker){
    init_curl(docker, "http://localhost/containers/json");
    
    CURLcode res;
    //Definition of the callBack Function
    curl_easy_setopt(docker->curl, CURLOPT_WRITEFUNCTION, default_callback);
    
    res = curl_easy_perform(docker->curl);
    return 1;
}

/*
 * Initialise Docker struct
 */
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

/*
 * Function to call to free memory before quitt
 */
void free_docker(DOCKER * docker){
    curl_easy_cleanup(docker->curl);
    //Free all the containers of the tab
    for(int i = 0; i < docker->sizeTab; i++)
        free_container(docker->containers[i]);
    free(docker);
}
