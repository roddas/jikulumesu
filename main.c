#include "utils/utils.c"
#include "utils/config.c"

int main(int argc, char **argv){

	maximize_u_limit();
	
	directory dir = directory_list();
	display_pids(dir);
	free_directory_list_memory(dir);
	return EXIT_SUCCESS;
}
