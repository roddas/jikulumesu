#include "lib/queue/queue.h"
#include "lib/queue/queue.c"
#include "lib/util/util.h"
#include "lib/util/util.c"

int main(int argc, char **argv){
	
	if(argc < 2)
	{
		usage(argv[0]);
	}
	read_file(atoi(argv[1]));
	
	return EXIT_SUCCESS;
}
