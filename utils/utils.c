#include "../lib/utils.h"

#define NUM_LINES 4
#define NAME_MAX_LENGTH 21
#define FILENAME_MAX_LENGTH 32
#define NUM_MAX_LENGTH 11

directory directory_list(const char *base_dir){
	
	struct dirent **namelist;
	int number_of_files = scandir("/proc/", &namelist, NULL, alphasort);
	
	if (number_of_files == -1) {
	   perror("scandir");
	   exit(EXIT_FAILURE);
	}
	return (directory){namelist, number_of_files};
}

void display_files(directory dir){
	while (dir.number_of_files--) {
	   printf("%s\n", dir.dir[dir.number_of_files]->d_name);
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
	printf("Name : %s\n",p.name);
	printf("State : %c\n",p.state);
	printf("ID : %d\n",p.pid);
	printf("Parent ID : %d\n",p.ppid);
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
	
	char *pid = calloc(NUM_MAX_LENGTH,sizeof(char));
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
	
	free(lines);
	free(pid);
	free(trash);
	free(filename);
	
	return new_process;
}
