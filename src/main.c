#include "cLibDocker.h"

int main(int argc, const char * argv[]){
    
    struct CONTAINER * container = NULL;
    container = init_container();
    
    set_Image(container, "ubuntu");
    printf("%s\n", container->Image);
    
    char * res = (char *)malloc(1 * sizeof(char));
    get_Json(container, &res);
    printf("%s\n", res);
    get_Json(container, &res);

    set_Id(container, "IdContainer");
    get_Json(container, &res);

    set_MacAddress(container, "102.32.232.23");
    set_StopSignal(container, "SIGKILL");

    get_Json(container, &res);
    printf("%s\n", res);
    
    set_Id(container, "IdContainerPMPMMMMMmdsdsdsnfcdskncdkcnsdlcnsdkcnsdckndvnfskvnfkvnkflvnfvnflknvfdknvfknvkfvnf");

    get_Json(container, &res);
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
