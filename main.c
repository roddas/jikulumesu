#include "utils/utils.c"
#include "utils/config.c"

int main(int argc, char **argv){

	maximize_u_limit();
	size_t counter = 1;
	
	while(1){
		printf("Running for the %lu time:\n",counter++);
		directory dir = directory_list();
		display_pids(dir);
		free_directory_list_memory(dir);
		sleep(1);
		system("clear");
	}
	
	return EXIT_SUCCESS;
}
