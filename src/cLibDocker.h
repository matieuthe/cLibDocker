#ifndef cLibDocker_h
#define cLibDocker_h

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>

void init_curl(CURL *curl, char * url_request);
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

#endif
