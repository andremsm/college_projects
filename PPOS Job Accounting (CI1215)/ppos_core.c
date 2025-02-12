//GRR20182593 André Miguel Sikora Marques

#include "ppos.h"
#include "ppos_data.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

#define STACKSIZE 64*1024

ucontext_t ContextMain;
task_t dispatcherT;
char *stack;
unsigned long int idCounter = 1;
unsigned long int userTasks = 0;
queue_t *fila;
queue_t *tarefasProntas;

void *tarefaCorrente;
void *proximaTarefa;

struct sigaction action;

struct itimerval timer;
unsigned int quantum = 0;
unsigned int tempo = 0;

unsigned int systime (){
	
	return tempo;
	
}

task_t *scheduler(){
	queue_t *temp1 = fila;
	queue_t *temp2 = fila;
	fila = fila->next;
	
	//encontra maior prioridade
	while(fila != temp1){
		if (((task_t*)fila)->prioridade < ((task_t*)temp1)->prioridade)
			temp2 = fila;
		fila = fila->next;
	}
	fila = temp2;
	fila = fila->next;
	
	//aumenta a prioridade de todos outros
	while (fila != temp2){
		if (((task_t *)fila)->prioridade > -20)
			((task_t *)fila)->prioridade--;
		fila = fila->next;
	}
	fila = temp1;
	fila = fila->next;
	
	return (task_t*) temp2;
}

void dispatcher(){
	while (userTasks > 0){
		dispatcherT.ativacoes++;
		dispatcherT.process = systime();//////////////////////////////////////////////////////////////////////////////////
		proximaTarefa = scheduler();																					//
		if (proximaTarefa != NULL){																						//
																														//
			((task_t *)proximaTarefa)->ativacoes++;																		//
			((task_t *)proximaTarefa)->process = systime();/*******************************************///				//		barras e asteriscos para indicar o que junta com o que
			dispatcherT.acumulador += systime() - dispatcherT.process;////////////////////////////// ** //////////////////
																								  // ** //				//
			task_switch(proximaTarefa);															  // **	//				//
																								  // ** //				//
			dispatcherT.process = systime();//////////////////////////////////////////////////////// ** //////////////////
			((task_t *)proximaTarefa)->acumulador += systime() - ((task_t *)proximaTarefa)->process;/**///				//
																														//
																														//
		}																												//
		dispatcherT.acumulador += systime() - dispatcherT.process;////////////////////////////////////////////////////////
	}
	tarefaCorrente = &dispatcherT.context;
	task_exit(0);
}

void tratador (int signum){
	tempo++;
	if (quantum < 20){
		quantum++;
		return;
	}
	
	quantum = 0;
	//tarefaCorrente sempre recebe o endereço do contexto, que subtraído de 24 (id, prev, e next; 8+8+8) resulta no endereço da estrutura completa.
	//Como ContextMain não foi definido como task_t é preciso desse OR.
	if (((task_t *)(tarefaCorrente-24))->sistema == 1 || tarefaCorrente == &ContextMain){
		printf("tentando preemptar uma tarefa de sistema\n");
		return;
	}
	
	task_switch(&dispatcherT);
}

void task_setprio (task_t *task, int prio){
	task_t *temp = tarefaCorrente;
	if (task == NULL){
		temp->prioridade = prio;
		return;
	}
	task->prioridade = prio;
	
}

int task_getprio (task_t *task){
	task_t *temp = tarefaCorrente-24;	//tamanho do int + tamanho dos 2 ponteiros (8+8+8), para encontrar o inicio da estrutura de dados
	if (task == NULL) return temp->prioridade;
	return task->prioridade;
}

void ppos_init (){
	setvbuf (stdout, 0, _IONBF, 0);
	ContextMain.uc_stack.ss_sp = stack;
	ContextMain.uc_stack.ss_size = STACKSIZE;
	ContextMain.uc_stack.ss_flags = 0;
	ContextMain.uc_link = 0;
	action.sa_handler = tratador;
	sigemptyset (&action.sa_mask);
	action.sa_flags = 0;
	if (sigaction (SIGALRM, &action, 0) < 0){
		perror ("Erro em sigaction: ");
		exit (1);
	}

	//temporizador
	timer.it_value.tv_usec = 1000;
	timer.it_value.tv_sec  = 0;
	timer.it_interval.tv_usec = 1000;
	timer.it_interval.tv_sec  = 0;

	if (setitimer (ITIMER_REAL, &timer, 0) < 0){
		perror ("Erro em setitimer: ");
		exit (1);
	}
	tarefaCorrente = &ContextMain;
	//tarefas que forem de sistema terão valor 1
	dispatcherT.sistema = 1;
	
	task_create(&dispatcherT, dispatcher, NULL);
}

int task_create (task_t *task, void (*start_func)(void *), void *arg){
	task->inicio = systime();
	char *stack;
	getcontext (&task->context);
	stack = malloc (STACKSIZE);
	if (stack){
		task->context.uc_stack.ss_sp = stack;
		task->context.uc_stack.ss_size = STACKSIZE;
		task->context.uc_stack.ss_flags = 0;
		task->context.uc_link = 0;
		task->id = idCounter;
		idCounter++;
		if (task != &dispatcherT){
			userTasks++;
			queue_append((queue_t **) &fila, (queue_t*) task);
		}
	}
	else{
		perror ("Erro na criação da pilha: ");
		return -1;
	}
	makecontext (&task->context, (void*)(*start_func), 1, arg);
	return task->id;
}

int task_switch (task_t *task){
	void *temp = tarefaCorrente;
	tarefaCorrente = &task->context;
	if (!(swapcontext (temp, &task->context))){
		//perror ("Erro no task_switch\n");
		return -1;
	}
	tarefaCorrente = temp;
	return 0;
}

void task_exit (int exitCode){
	if (tarefaCorrente != &dispatcherT.context){
		((task_t *)(tarefaCorrente-24))->fim = systime();
		printf("Task %d exit: execution time %d ms. processor time %d ms. %d activations\n", ((task_t *)(tarefaCorrente-24))->id, ((task_t *)(tarefaCorrente-24))->fim - ((task_t *)(tarefaCorrente-24))->inicio, ((task_t *)(tarefaCorrente-24))->acumulador, ((task_t *)(tarefaCorrente-24))->ativacoes); 
		userTasks--;
		swapcontext(tarefaCorrente, &dispatcherT.context);
	}
	else if (tarefaCorrente == &dispatcherT.context){
		((task_t *)(tarefaCorrente-24))->fim = systime();
		printf("Task %d exit: execution time %d ms. processor time %d ms. %d activations\n", ((task_t *)(tarefaCorrente-24))->id, ((task_t *)(tarefaCorrente-24))->fim - ((task_t *)(tarefaCorrente-24))->inicio, ((task_t *)(tarefaCorrente-24))->acumulador, ((task_t *)(tarefaCorrente-24))->ativacoes); 
		swapcontext(tarefaCorrente, &ContextMain);
	}
}

int task_id (){
	if (tarefaCorrente == &ContextMain)
		return 0;
	else{
		int *ptr = tarefaCorrente - (sizeof (unsigned long int));	//tamanho do int, para encontrar int id
		return *ptr;
	}
}





void task_yield (){
	task_switch(&dispatcherT);
}