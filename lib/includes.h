#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef INCLUDES_H
#define INCLUDES_H

typedef struct {
	pid_t pid;
	pid_t ppid;
	char name[21];
	char state;
}process;

#endif
