#include "queue.h"

void init_queue(void)
{
	fileira = new_queue("init");
	fileira->proximo = fileira;
}
queue *new_queue(char *elemento)
{
	queue *novo = (queue *)malloc(sizeof(queue));
	strcpy(novo->elemento,elemento);
	novo->proximo = NULL;
	return novo;
}
void push(char *elemento)
{
	queue *novo = new_queue(elemento);
	
	if(!novo)
		error();
	
	novo->proximo = fileira->proximo;
	fileira->proximo = novo;
	strcpy(fileira->elemento,elemento);
	fileira = novo;
}
void error(void)
{
	perror("");
	printf("Insira qualquer tecla para sair ..\n");
	scanf("%*c");
	exit(EXIT_FAILURE);
}
char *pop(void)
{
	queue *lixo = fileira->proximo;
	char *ret = malloc(11 * sizeof(char));
	fileira->proximo = lixo->proximo;
	strcpy(ret,lixo->elemento);
	free(lixo);
	return ret;
}
bool is_empty(void)
{
	return fileira->proximo == fileira;
}
void release_queue(void)
{
	free(fileira);
}
