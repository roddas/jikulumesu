#include "includes.h"

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node 
{
	char dir[NUM_MAX_LENGTH];
	struct node *next;
	
}node;

node *new_node(char *);
node *init(void);
node *insert(node *,char *);
node *find(node *,char *);
node *remove_element(node *,char *);
void erase(node *);
void linked_list_error(void);
void view(node *);

#endif
