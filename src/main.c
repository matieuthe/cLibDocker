#include "cLibDocker.h"

int main(int argc, const char * argv[]){
    
    CONTAINER * container = new_container();
    set_Image(container, "ubuntu");
    add_Command_Container(container, "date");
    add_Command_Container(container, "ls");

    char * res = NULL;
    get_Json(container,&res);
    DOCKER * docker = init_docker();
    for(int i = 0; i < 35; i++)
        start_container(docker, container);
    
    
    //for(int i = 0; i < 40; i++)
    //    rm_container(docker, 0);
    rm_stopped_containers(docker);
    free_docker(docker);
    free_container(container);
	return 0;
}
