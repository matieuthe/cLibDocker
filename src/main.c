#include "cLibDocker.h"

int main(int argc, const char * argv[]){
    //char * urlStatut = "http://localhost/containers/json";
    
    struct Docker * docker = (struct Docker *)malloc(sizeof(struct Docker));
    init_docker(docker);
    
    char * data = "{\"Image\":\"myubuntu\"}";
    start_container(docker, data);
    statut_containers(docker);
    rm_container(docker, 0);
    close_docker(docker);
	return 0;
}
