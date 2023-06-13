#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <dirent.h>


#ifndef INCLUDES_H
#define INCLUDES_H

typedef struct dirent dirent;

typedef struct {
	pid_t pid;
	pid_t ppid;
	char name[21];
	char state;
}process_info;

typedef struct {
	dirent **dir;
	int number_of_files;
}directory;
#endif
