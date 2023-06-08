#include "util.h"

#define NUM_LINES 3

void usage(char *argv){
	printf("Usage: %s [PID]\n",argv);
	exit(EXIT_FAILURE);
}

queue *filter(queue *list){
	return NULL;
}

queue *read_file(pid_t process_id){
	
	char *pid = calloc(11,sizeof(char));
	char *filename = calloc(32,sizeof(char));

	sprintf(pid,"%d",process_id);
	strcpy(filename, "/proc/");
	filename = strcat(filename,pid);
	filename = strcat(filename,"/status");
	
	FILE * file_handle = fopen(filename,"r");
	if(file_handle == NULL){
		perror(":");
		exit(EXIT_FAILURE);
	}
	
	char ** lines = calloc(NUM_LINES,sizeof(char *));
	char * trash = calloc(64,sizeof(char));
	size_t buff_size = 64;
	
	for(int a = 0; a < NUM_LINES;a++){
		lines[a] = calloc(64,sizeof(char));
	}
	getline(&lines[0],&buff_size,file_handle); // Name
	getline(&trash,&buff_size,file_handle);
	getline(&lines[1],&buff_size,file_handle); // State
	getline(&trash,&buff_size,file_handle);
	getline(&trash,&buff_size,file_handle);
	getline(&trash,&buff_size,file_handle);
	getline(&lines[2],&buff_size,file_handle); // PPid
	
	printf("%s",lines[0]);
	printf("%s",lines[1]);
	printf("%s",lines[2]);
	
	free(pid);
	free(filename);
	
	return NULL;
}

/*
void printppid(pid_t pid) {
    proc_t process_info;
    get_proc_stats(pid, &process_info);
    printf("Parent of pid=%d is pid=%d\n", pid, process_info.ppid);
}

*/
