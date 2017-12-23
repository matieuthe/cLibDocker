#include "cLibDocker.h"

int main(int argc, const char * argv[]){
    
    CONTAINER * container = new_container();
    set_Image(container, "ubuntu");
    
    DOCKER * docker = init_docker();
    start_container(docker, container);
    start_container(docker, container);
    
   /* for(int i = 0; i < docker->nbContainers; i++)
        printf("%s\n", docker->containers[i]->Id);*/
    //statut_containers(docker);
    //rm_container(docker, 0);
    free_docker(docker);
    //free_container(container);

	return 0;
}
