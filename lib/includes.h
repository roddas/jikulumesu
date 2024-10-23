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

#define NUM_LINES 4
#define NAME_MAX_LENGTH 21
#define FILENAME_MAX_LENGTH 64
#define NUM_MAX_LENGTH 11

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
