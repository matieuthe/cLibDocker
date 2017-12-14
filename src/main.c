#include "cLibDocker.h"

int main(int argc, const char * argv[]){
	CURL *curl = curl_easy_init();
	if(curl) {
        CURLcode res;
        char * urlCreation = "http://localhost/containers/create";
        char * urlStatut = "http://localhost/containers/json";
        init_curl(curl, urlCreation);
        
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        //Post Operation
        char * data = "{\"Image\":\"myubuntu\"}";
        int lg = strlen(data);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, lg);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        
        //Definition of the callBack Function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	return 0;
}


