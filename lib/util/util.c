#include "util.h"

#define NUM_LINES 4
#define NAME_MAX 21
#define FILENAME_MAX_LENGTH 32
#define NUM_MAX_LENGTH 11

void usage(char *argv){
	printf("Usage: %s [PID]\n",argv);
	exit(EXIT_FAILURE);
}

queue *filter(queue *list){
	return NULL;
}
void show_process(process p){
	printf("Name : %s\n",p.name);
	printf("State : %c\n",p.state);
	printf("ID : %d\n",p.pid);
	printf("Parent ID : %d\n",p.ppid);
}
int first_occurence(char *string, char ch){
	
	for(int a = 0 ; string[a] != '\0';a++ )
		if(string[a] == ch)
			return a;
	return 0;
}
char *filter_process_name(char *raw_data){
	
	int counter = 0;
	char *filtered_name = calloc(NAME_MAX,sizeof(char));
	
	if(!filtered_name){
		perror("Memory :");
	}
	for(int a = first_occurence(raw_data,'\t') + 1; raw_data[a] != '\n';a++){
		filtered_name[counter++] = raw_data[a];
	}
	return filtered_name;
}
char filter_process_state(char *raw_data){
	return raw_data[first_occurence(raw_data,'\t') + 1];
}
pid_t filter_process_id(char *raw_data){
	
	int counter = 0;
	char *pid = calloc(NUM_MAX_LENGTH,sizeof(char));
	
	if(!pid){
		perror("Memory :");
	}
	for(int a = first_occurence(raw_data,'\t') + 1; raw_data[a] != '\n';a++){
		pid[counter++] = raw_data[a];
	}
	
	pid_t process_id = atoi(pid);
	free(pid);
	
	return process_id;
}
process get_process(pid_t process_id){
	
	char *pid = calloc(NUM_MAX_LENGTH,sizeof(char));
	char *filename = calloc(FILENAME_MAX,sizeof(char));
	char ** lines = calloc(NUM_LINES,sizeof(char *));
	char * trash = calloc(64,sizeof(char));
	size_t buff_size = 64;
	process new_process;
	
	sprintf(pid,"%d",process_id);
	strncpy(filename, "/proc/",FILENAME_MAX_LENGTH);
	filename = strcat(filename,pid);
	filename = strcat(filename,"/status");
	
	FILE * file_handle = fopen(filename,"r");
	if(file_handle == NULL){
		fprintf(stderr,"The process [%d] does not exists\n", process_id);
		exit(EXIT_FAILURE);
	}
	
	
	for(int a = 0; a < NUM_LINES;a++){
		lines[a] = calloc(64,sizeof(char));
	}
	
	getline(&lines[0],&buff_size,file_handle); // Name
	getline(&trash,&buff_size,file_handle);
	getline(&lines[1],&buff_size,file_handle); // State
	getline(&trash,&buff_size,file_handle);
	getline(&trash,&buff_size,file_handle);
	getline(&lines[2],&buff_size,file_handle); // Pid
	getline(&lines[3],&buff_size,file_handle); // PPid
	
	/*
	printf("%s",lines[0]);
	printf("%s",lines[1]);
	printf("%s",lines[2]);
	printf("%s\nFiltered values:\n",lines[3]);
	*/
	
	strncpy(new_process.name,filter_process_name(lines[0]),NAME_MAX);
	new_process.state = filter_process_state(lines[1]);
	new_process.pid = filter_process_id(lines[2]);
	new_process.ppid = filter_process_id(lines[3]);
	
	for(int a = 0; a < NUM_LINES;a++){
		free(lines[a]);
	}
	
	free(lines);
	free(pid);
	free(trash);
	free(filename);
	
	return new_process;
}
