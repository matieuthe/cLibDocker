#include "cLibDocker.h"

void init_curl(CURL *curl, char * url_request){
    //Fix Unix socket on docker socket
    curl_easy_setopt(curl, CURLOPT_UNIX_SOCKET_PATH, "/var/run/docker.sock");
    curl_easy_setopt(curl, CURLOPT_URL, url_request);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
    //Réponse du serveur
    printf("%s\n", ptr);
}
