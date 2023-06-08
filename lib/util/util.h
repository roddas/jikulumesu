#include"../includes.h"

#ifndef UTIL_H
#define UTIL_H

queue *filter(queue * );
process get_process(pid_t );
void show_process(process );
void usage(char *);
pid_t filter_process_id(char *);
process filter_process(char **);
char *filter_process_name(char *);
char filter_process_state(char *);
int first_occurence(char *, char );
#endif
