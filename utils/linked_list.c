#include "../lib/linked_list.h"

node *init(void)
{
	return new_node("INIT");
}
node *new_node(char *value)
{
	node *cel = (node *)malloc(sizeof(node));
	if(!cel)
		linked_list_error();
		
	strncpy(cel->dir,value,NUM_MAX_LENGTH);
	cel->next = NULL;
	return cel;
}
void linked_list_error(void){
	perror("Linked list:");
	exit(EXIT_FAILURE);
}
node *insert_begin(node *root,char *value)
{
	if(!root->next)
	{
		root->next = new_node(value);
		return root;
	}
	node *cel = new_node(value);
	node *ptr = root;
	cel->next = ptr->next;
	ptr->next = cel;
	return root; 
}
