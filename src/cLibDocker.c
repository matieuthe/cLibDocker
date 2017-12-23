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
    if(strlen(ptr)>64){
        char res[ID_SIZE + 1];
        for(int i = 0; i < ID_SIZE; i++){
            res[i] = ptr[i+7];
        }
        res[ID_SIZE] = '\0';
        printf("%s\n", res);
        set_Id(&docker->containers[0], res);
    }
    docker->nbContainers++;
    return 0;
}

/*
 *  CallBack function status container
 */
size_t default_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
    printf("%s", ptr);
    return 0;
}

/*
 *  Start the containers specify in data
 */
int start_container(DOCKER * docker, CONTAINER * container){
    printf("Creation of container\n");
    init_curl(docker, "http://localhost/containers/create");
    
    CURLcode res;
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(docker->curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(docker->curl, CURLOPT_HTTPHEADER, headers);
    
    copy_container(container, &docker->containers[0]);
    
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
    if(indice >= docker->nbContainers)
        return 0;
    
    //Build the url of the request
    char * url = "http://localhost/containers/";
    int sizeUrl = strlen(url) + ID_SIZE + 1;
    char * urlId = (char *)malloc(sizeUrl);
    strcpy(urlId, url);
    strcat(urlId, docker->idContainers[indice]);
    urlId[sizeUrl - 1] = '\0';
    printf("%s\n", urlId);
    init_curl(docker, urlId);
    //Free memory of curlId
    free(urlId);
    
    CURLcode res;
    curl_easy_setopt(docker->curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    
    //Definition of the callBack Function
    curl_easy_setopt(docker->curl, CURLOPT_WRITEFUNCTION, default_callback);
    //Execution of the request
    res = curl_easy_perform(docker->curl);
    
    //Reorganize id in the tab
    for(int i = 0; i < docker->nbContainers - 1; i++){
        strcpy(docker->idContainers[i], docker->idContainers[i+1]);
    }
    docker->idContainers[docker->nbContainers - 1][0] = '\0';
    docker->nbContainers--;
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
    printf("Initialisation of docker Struct\n");
    int i;
    docker->sizeTab = 0;
    docker->nbContainers = 0;
    
    docker->containers = (CONTAINER *)malloc(10 * sizeof(CONTAINER));
    for(i = 0; i < 10; i++)
        init_container(&docker->containers[i]);
    
    //Allocate memory to idContainers for 10 containers
    docker->idContainers = (char **)malloc(10 * sizeof(char *));
    for(i = 0; i < 10; i++)
    {
        docker->idContainers[i] = (char *)malloc( (ID_SIZE + 1) * sizeof(char));
        //To unvalid the line
        docker->idContainers[i][0] = '\0';
    }
    docker->sizeTab = 10;
    return docker;
}

/*
 * Function to call to free memory before quitt
 */
void free_docker(DOCKER * docker){
    int i;
    curl_easy_cleanup(docker->curl);
    
    for( i = 0; i < docker->sizeTab; i++)
        free(docker->idContainers[i]);
    
    free(docker->idContainers);
    free(docker);
}
