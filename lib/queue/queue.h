#include"../includes.h"

#ifndef QUEUE_H
#define QUEUE_H

queue *new_queue(char * );
void error(void);
void init_queue(void);
void push(char * );
char *pop(void);
bool is_empty(void);
void release_queue(void);

#endif

