#include "cLibDocker.h"

int main(int argc, const char * argv[]){
	CURL *curl = curl_easy_init();
	if(curl) {
  		CURLcode res;
  		curl_easy_setopt(curl, CURLOPT_HTTPGET, "unix:///var/run/docker.sock/containers/json");
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	return 0;
}
