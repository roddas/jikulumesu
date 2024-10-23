#include"includes.h"

#ifndef UTIL_H
#define UTIL_H

process_info get_process(pid_t );
void show_process(process_info );
void usage(char *);
pid_t filter_process_id(char *);
process_info filter_process(char **);
char *filter_process_name(char *);
char filter_process_state(char *);
int first_occurence(char *, char );
directory directory_list(void );
void display_pids(directory );
void free_directory_list_memory(directory );

#endif
