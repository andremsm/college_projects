//GRR20182593 André Miguel Sikora Marques

#include "queue.h"
#include <stdio.h>

int queue_size (queue_t *queue){
	int tam = 0;
	
	if (queue == NULL) return 0;
	else if (queue->next == queue) return 1;
	else{
		queue_t *temp = queue;
		tam++;
		temp = temp->next;
		while (temp != queue){
			tam++;
			temp = temp->next;
		}

		return tam;
	}
	
}

void queue_print (char *name, queue_t *queue, void print_elem (void*) ) {
	queue_t *temp = queue;
	print_elem(temp);
	if (temp != NULL)
		temp = temp->next;
	while (temp != queue){
		print_elem(temp);
		temp = temp->next;
	}
}

int queue_append (queue_t **queue, queue_t *elem) {
	queue_t *temp = *queue;
	if (queue == NULL){
		fprintf(stderr, "fila nao existe\n");
		return -1;
	}
	else if (elem == NULL){
		fprintf(stderr, "elemento nao existe\n");
		return -1;
	}
	else if (elem->next != NULL){
		temp = temp->next;
		do{
			if (temp == elem){
				fprintf(stderr, "elemento ja existe nessa fila\n");
				return -1;
			}
		} while (temp != *queue);
		fprintf(stderr, "elemento esta em outra fila\n");
		return -1;
	}
	if (temp == NULL){
		*queue = elem;
		elem->next = elem;
		elem->prev = elem;
		return 0;
	}
	elem->next = temp;
	elem->prev = temp->prev;
	
	temp = temp->prev;
	temp->next = elem;
	temp = elem->next;
	temp->prev = elem;
	return 0;
}

int queue_remove (queue_t **queue, queue_t *elem) {
	queue_t *temp = *queue;
	if (queue == NULL){
		fprintf(stderr, "fila nao existe\n");
		return -1;
	}
	else if (temp == NULL){
		fprintf(stderr, "fila vazia\n");
		return -1;
	}
	else if (elem == NULL){
		fprintf(stderr, "elemento nao existe\n");
		return -1;
	}
	
	temp = temp->next;
	while (temp != elem && temp != *queue)
		temp = temp->next;
	if (temp != elem){
		fprintf(stderr, "elemento nao pertence a fila\n");
		return -1;
	}
	
	if (temp->next == temp){
		temp->prev = NULL;
		temp->next = NULL;
		temp = NULL;
		*queue = NULL;
		return 0;
	}

	if (elem == *queue)
		*queue = elem->next;
	temp = temp->prev;
	temp->next = temp->next->next;
	temp = elem->next;
	temp->prev = temp->prev->prev;
	temp = *queue;
	elem->next = NULL;
	elem->prev = NULL;
	
	return 0;
	
	
}