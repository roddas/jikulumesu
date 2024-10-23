#include "utils/utils.c"

int main(int argc, char **argv){
	
	directory dir = directory_list();
	display_pids(dir);
	free_directory_list_memory(dir);
	return EXIT_SUCCESS;
}
