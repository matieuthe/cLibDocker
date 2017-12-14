#include "cLibDocker.h"

int init_curl(struct Docker * docker, char * url_request);
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata, void * pass);

int init_curl(struct Docker * docker, char * url_request){
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
 *  CallBack function
 */
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata, void * temp){
    //struct Docker * docker = (struct Docker *)temp;
    printf("%s\n", ptr);
    //docker->nbContainers = 45;
    return 0;
}

/*
 *  Start the containers specify in data
 */
int start_container(struct Docker * docker, char * data){
    printf("Creation of container\n");
    
    init_curl(docker, "http://localhost/containers/create");
    
    CURLcode res;
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    
    curl_easy_setopt(docker->curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(docker->curl, CURLOPT_HTTPHEADER, headers);
    
    //Post Operation
    int lg = strlen(data);
    curl_easy_setopt(docker->curl, CURLOPT_POST, 1L);
    curl_easy_setopt(docker->curl, CURLOPT_POSTFIELDSIZE, lg);
    curl_easy_setopt(docker->curl, CURLOPT_POSTFIELDS, data);
    //Definition of the callBack Function
    curl_easy_setopt(docker->curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(docker->curl, CURLOPT_WRITEDATA, docker);
    res = curl_easy_perform(docker->curl);
    
    return 1;
}

/*
 *  Get the staut of all containers running
 */
int statut_containers(struct Docker * docker){
    init_curl(docker->curl, "http://localhost/containers/json");
    
    CURLcode res;
    //Definition of the callBack Function
    curl_easy_setopt(docker->curl, CURLOPT_WRITEFUNCTION, write_callback);
    
    res = curl_easy_perform(docker->curl);
    return 1;
}

/*
 * Initialise Docker struct
 */
void init_docker(struct Docker * docker){
    printf("Initialisation of docker Struct\n");
    int i;
    docker->sizeTab = 0;
    docker->nbContainers = 0;
    
    //Allocate memory to idContainers for 10 containers
    docker->idContainers = (char **)malloc(10 * sizeof(char *));
    for(i = 0; i < 10; i++)
    {
        docker->idContainers[i] = (char *)malloc( 64 * sizeof(char));
        //To unvalid the line
        docker->idContainers[i][0] = 0;
    }
    docker->sizeTab = 10;
}

/*
 * Function to call to free memory before quitt
 */
void close_docker(struct Docker * docker){
    int i;
    curl_easy_cleanup(docker->curl);
    
    for( i = 0; i < docker->sizeTab; i++)
        free(docker->idContainers[i]);
    
    free(docker->idContainers);
}






