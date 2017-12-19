#include "cLibDocker.h"
#include "container.h"

int main(int argc, const char * argv[]){
    
    struct CONTAINER * container = init_container();
    
    set_Image(container, "ubuntu");
    printf("%s\n", container->Image);
    
    char * res = (char *)malloc(2000 * sizeof(char));
    get_Json(container, res);
    printf("%s\n", res);

    set_Id(container, "IdContainer");
    set_MacAddress(container, "102.32.232.23");
    set_StopSignal(container, "SIGKILL");

    get_Json(container, res);
    printf("%s\n", res);
    
    free(res);
    free_container(container);
    
    /*
    struct Docker * docker = (struct Docker *)malloc(sizeof(struct Docker));
    init_docker(docker);
    
    char * data = "{\"Image\":\"ubuntu\"}";
    start_container(docker, data);
    statut_containers(docker);
    //rm_container(docker, 0);
    close_docker(docker);*/
	return 0;
}
