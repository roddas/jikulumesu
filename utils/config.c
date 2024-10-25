#include "../lib/config.h"
#include <sys/resource.h>

/* This function maximize the number of files 
 * that a operating system allows to a process
 * */
void maximize_u_limit(void){
	
	struct rlimit limit;
	limit.rlim_cur = 65535;
	limit.rlim_max = 65535;
	
	if(setrlimit(RLIMIT_NOFILE,&limit) != 0){
		perror("::");
		exit(EXIT_FAILURE);
	}
}
