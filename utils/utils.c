#include "../lib/utils.h"
#include "linked_list.c"
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

directory directory_list(void){
	
	struct dirent **namelist = NULL;
	int number_of_files = scandir("/proc/", &namelist, NULL, alphasort);
	
	if (number_of_files == -1) {
	   perror("scandir: ");
	   exit(EXIT_FAILURE);
	}
	return (directory){namelist, number_of_files};
}

void free_directory_list_memory(directory dir){
	size_t number_of_files = dir.number_of_files;
	
	for(size_t i = 0; i < number_of_files;i++){
		if(dir.dir[i] != NULL)
		{
			free(dir.dir[i]);
		}
	}
}

void display_pids(directory dir){
	while (dir.number_of_files--) {
		const char *pid = dir.dir[dir.number_of_files]->d_name;
		if(isdigit(pid[0])){
			
			process_info current_process = get_process((pid_t)atoi(pid));
			if(strcmp(current_process.name,"bash") == 0){
				show_process(current_process);
				printf("--------------------------------\n");
			}
		}
	}
}

/*
 * This functions displays the usage program
 * */
void usage(char *argv){
	printf("Usage: %s [PID]\n",argv);
	exit(EXIT_FAILURE);
}
/*
 * This function displays the processes information.
 * */
void show_process(process_info p){
	
	struct passwd *pw = getpwuid(getuid());
	
    if (pw == NULL) {
        perror("getpwuid: ");
        return;
    }
	
	printf("Name : %s\n",p.name);
	printf("State : %c\n",p.state);
	printf("ID : %d\n",p.pid);
	printf("Parent ID : %d\n",p.ppid);
    printf("User: %s\n", pw->pw_name);
	//printf("Password: %s\n", pw->pw_passwd);
}
/*
 * This function gets the first occurence of a given char
 * */
int first_occurence(char *string, char ch){
	
	for(int a = 0 ; string[a] != '\0';a++ )
		if(string[a] == ch)
			return a;
	return 0;
}
/*
 * This function retrieves a process name
 * */
char *filter_process_name(char *raw_data){
	
	int counter = 0;
	char *filtered_name = calloc(NAME_MAX_LENGTH,sizeof(char));
	
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
process_info get_process(pid_t process_id){
	
	char pid[NUM_MAX_LENGTH];
	memset(pid,'\0',NUM_MAX_LENGTH);
	
	char *filename = calloc(FILENAME_MAX,sizeof(char));
	char ** lines = calloc(NUM_LINES,sizeof(char *));
	char * trash = calloc(64,sizeof(char));
	
	size_t buff_size = 64;
	process_info new_process;
	
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
		if(lines[a] == NULL){
			perror("Memory: ");
			exit(EXIT_FAILURE);
		}
	}
	
	getline(&lines[0],&buff_size,file_handle); // Name
	getline(&trash,&buff_size,file_handle);
	getline(&lines[1],&buff_size,file_handle); // State
	getline(&trash,&buff_size,file_handle);
	getline(&trash,&buff_size,file_handle);
	getline(&lines[2],&buff_size,file_handle); // Pid
	getline(&lines[3],&buff_size,file_handle); // PPid
	
	strncpy(new_process.name,filter_process_name(lines[0]),NAME_MAX_LENGTH);
	new_process.state = filter_process_state(lines[1]);
	new_process.pid = filter_process_id(lines[2]);
	new_process.ppid = filter_process_id(lines[3]);
	
	for(int a = 0; a < NUM_LINES;a++){
		free(lines[a]);
	}
	
	return new_process;
}
