#include "utils/utils.c"

int main(int argc, char **argv){
	
/*
 * 	if(argc < 2)
	{
		usage(argv[0]);
	}
	show_process(get_process(atoi(argv[1])));
 * */
	directory dir = directory_list();
	display_pids(dir);
	free_directory_list_memory(dir);	
	return EXIT_SUCCESS;
}
