#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef INCLUDES_H
#define INCLUDES_H

typedef struct queue 
{
	char elemento[11];
	struct queue *proximo;
}queue;

typedef struct {
	pid_t pid;
	pid_t ppid;
	char name[21];
	char state;
}process;

queue *fileira;

#endif
