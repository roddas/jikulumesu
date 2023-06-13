#include "utils/utils.c"

int main(int argc, char **argv){
	
	if(argc < 2)
	{
		usage(argv[0]);
	}
	show_process(get_process(atoi(argv[1])));
	
	return EXIT_SUCCESS;
}
