//GRR20182593 André Miguel Sikora Marques



//LEMBRAR DE ALOCAR OS PONTEIROS




#include "ppos.h"
#include "ppos_data.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

#define STACKSIZE 64*1024

task_t *ContextMain;
task_t dispatcherT;
char *stack;
unsigned long int idCounter = 1;
unsigned long int userTasks = 0;
queue_t *fila;
queue_t *tarefasProntas;
queue_t *tarefasAdormecidas;

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
	if (temp1 == NULL) return NULL;
	
	
	
//	fila = fila->next;
	
	//encontra maior prioridade
	do{
//		printf("P %d %d \n", systime(), ((task_t *)fila)->id);
		if (((task_t*)fila)->prioridade < ((task_t*)temp1)->prioridade)
			temp2 = fila;
		fila = fila->next;
	}while(fila != temp1);
	fila = temp2;
	fila = fila->next;
//	printf("\n");
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

int testQueue(){
//printf("\ntestando tamanho da fila\n");
	queue_t *temp1 = fila;
	if (temp1->next == temp1)
		return 1;
	else return 0;
}

int buscarFilaPronta(task_t *task){
	queue_t *temp1 = tarefasProntas;
	queue_t *temp2 = tarefasProntas;
	if (temp1 == NULL)
		return 0;
	//temp1 = temp1->next;
	
	//procura task na lista de filas prontas
	do{
		void *ptr = temp1;
		if ((ptr) == &(task->context))
			return 1;
		temp1 = temp1->next;
	}while(temp1 != temp2);
	
	/*while(temp1 != temp2){
		if (((task_t*)temp1) == (task))
			return 1;
		temp1 = temp1->next;
	}*/
	return 0;
}

int task_join (task_t *task){
	task_t *temp = tarefaCorrente-24;
//	printf("%p\n%p\n", temp, &temp);
	if (task == NULL || buscarFilaPronta(task))
		return -1;
	ContextMain->suspenso = 1;
	temp->suspenso = 1;
//	printf("\n%d\n", temp->id);
//	printf("\n%p %p\n", &ContextMain.context, &temp->context);
	queue_t *q = task->aguardando;										//essa variável não serve pra nada, mas se tirar dá segfault ao rodar
//	printf("\n_%p_%p_\n", temp, ContextMain);
	queue_append((queue_t **) &(task->aguardando), (queue_t*) &temp);
	q = q->next;
	
	temp->suspenso = 1;
//	printf("%p\n%p\n", temp, (task_t *)fila);
	temp = tarefaCorrente-24;
	queue_remove((queue_t **) &fila, (queue_t*) temp);
	queue_append((queue_t **) &tarefasAdormecidas, (queue_t*) temp);
//	printf("%p\n%p\n%p\n", temp, tarefasAdormecidas, ContextMain);
	//printf("\n%d\n", temp->suspenso);
	while (temp->suspenso == 1){
		if (buscarFilaPronta(task) || task == NULL){
			temp->suspenso = 0;
			ContextMain->suspenso = 0;
			break;
		}
//	printf("a");
	}
//	queue_remove((queue_t **) &tarefasAdormecidas, (queue_t*) temp);
//	queue_append((queue_t **) &fila, (queue_t*) temp);
	return task->id;
}

void task_sleep (int t){
	if (t > 0){
		task_t *temp = tarefaCorrente-24;
		temp->acordar = t + systime();
		queue_remove((queue_t **) &fila, (queue_t*) temp);
		queue_append((queue_t **) &tarefasAdormecidas, (queue_t*) temp);
		task_yield();
	}
}

void dispatcher(){
	while (1){
		if (testQueue())
			task_switch(ContextMain);
		else
			break;
	}
	while (userTasks >= 0){
//		printf(" %d ", systime());
		dispatcherT.ativacoes++;
		dispatcherT.process = systime();//////////////////////////////////////////////////////////////////////////////////
																														//
																														//
		
		if (tarefasAdormecidas != NULL){
			queue_t *temp2 = tarefasAdormecidas;
			//tarefasAdormecidas = tarefasAdormecidas;
			do{
	//			printf("D %d %d %d \n", systime(), ((task_t *)tarefasAdormecidas)->id, ((task_t *)tarefasAdormecidas)->acordar);
				if (systime() >= ((task_t *)tarefasAdormecidas)->acordar && ((task_t *)tarefasAdormecidas)->suspenso == 0){
					task_t *t1 = (task_t *)tarefasAdormecidas;
					tarefasAdormecidas = tarefasAdormecidas->next;
					queue_remove((queue_t **) &tarefasAdormecidas, (queue_t*) t1);
					queue_append((queue_t **) &fila, (queue_t*) t1);
					break;
		//			task_switch(t1);
				}
				else
					tarefasAdormecidas = tarefasAdormecidas->next;
			}while (tarefasAdormecidas != temp2 && tarefasAdormecidas != NULL);
	//		printf("\n");
		}
		
		proximaTarefa = scheduler();																					//
		if (&((task_t *)proximaTarefa)->context == &ContextMain->context){
			if (ContextMain->suspenso == 1){
				dispatcherT.ativacoes--;
				//continue;
			}
		}												//
			//printf ("\n%d\n", ((task_t *)proximaTarefa)->suspenso);													//
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
		//else if (((task_t *)proximaTarefa)->suspenso == 1)															//
		//	((task_t *)proximaTarefa)->prioridade++;																	//
		if (proximaTarefa == NULL && tarefasAdormecidas != NULL)
			dispatcherT.ativacoes--;
		dispatcherT.acumulador += systime() - dispatcherT.process;////////////////////////////////////////////////////////
		if (proximaTarefa == NULL && tarefasAdormecidas == NULL) break;
	}
//	printf("\ntest\n");
	tarefaCorrente = &dispatcherT.context;
	task_exit(0);
}

void tratador (int signum){
	tempo++;
	
	
	if (quantum < 19){
		quantum++;
		return;
	}
	
	quantum = 0;
	//tarefaCorrente sempre recebe o endereço do contexto, que subtraído de 24 (id, prev, e next; 8+8+8) resulta no endereço da estrutura completa.
	//Como ContextMain não foi definido como task_t é preciso desse OR. 	NÃO É MAIS NECESSÁRIO
	if (((task_t *)(tarefaCorrente-24))->sistema == 1){
	//	printf("tentando preemptar uma tarefa de sistema\n");
		return;
	}
	
	task_switch(&dispatcherT);
}

void task_setprio (task_t *task, int prio){
	task_t *temp = tarefaCorrente-24;
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
	ContextMain = malloc (sizeof (task_t *));
	ContextMain->context.uc_stack.ss_sp = stack;
	ContextMain->context.uc_stack.ss_size = STACKSIZE;
	ContextMain->context.uc_stack.ss_flags = 0;
	ContextMain->context.uc_link = 0;
	ContextMain->sistema = 0;
	ContextMain->suspenso = 0;
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
	tarefaCorrente = &ContextMain->context;
	//tarefas que forem de sistema terão valor 1
	dispatcherT.sistema = 1;
	dispatcherT.suspenso = 0;
	
	queue_append((queue_t **) &fila, (queue_t*) ContextMain);
	
	task_create(&dispatcherT, dispatcher, NULL);
	task_yield();
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
		task->suspenso = 0;
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
	//if (tarefaCorrente == &ContextMain.context)
//		printf("\nTASK_EXIT DO MAIN\n");
//	ContextMain->suspenso = 0;
	if (tarefaCorrente != &dispatcherT.context){
		((task_t *)(tarefaCorrente-24))->fim = systime();
		printf("Task %d exit: execution time %d ms. processor time %d ms. %d activations\n", ((task_t *)(tarefaCorrente-24))->id, ((task_t *)(tarefaCorrente-24))->fim - ((task_t *)(tarefaCorrente-24))->inicio, ((task_t *)(tarefaCorrente-24))->acumulador, ((task_t *)(tarefaCorrente-24))->ativacoes); 
	//	if (tarefaCorrente != &ContextMain.context)
			userTasks--;
	//	queue_append((queue_t **) &tarefasProntas, (queue_t*) tarefaCorrente);
		
		ContextMain->suspenso = 0;
		task_t *temp = tarefaCorrente-24;
		queue_t *temp1 = temp->aguardando;
		//queue_t *temp2 = temp1;
		//temp2 = temp2->next;
	//	printf("\n%d\n", queue_size(temp->aguardando));
		if (queue_size(temp->aguardando) > 0){
		//	temp->aguardando = temp->aguardando->next;
			do{
		//		printf(" %d ", ((task_t *)temp->aguardando)->suspenso);
				((task_t *)temp->aguardando)->suspenso = 0;
				task_t **temp3 = (task_t **)temp->aguardando;
			//	printf("\n\n%p\n\n", temp3);
			//	queue_remove((queue_t **) &(temp->aguardando), (queue_t*) &(temp->aguardando));
				temp->aguardando = temp->aguardando->next;
				//printf("\n%p\n%p\n%p\n%p\n\n", temp, temp3, *(temp->aguardando), ContextMain);
//				printf("\n\ntemp: %p\n", temp);
//				printf("*(temp3): %p\n", (queue_t*) *(temp3));
	/*			printf("tarefasAdormecidas: %p\n", tarefasAdormecidas->next);
				printf("tarefasAdormecidas: %p\n", tarefasAdormecidas->next->next);
				printf("tarefasAdormecidas: %p\n", tarefasAdormecidas->next->next->next);
				printf("tarefasAdormecidas: %p\n", tarefasAdormecidas->next->next->next->next);
				printf("tarefasAdormecidas: %p\n", tarefasAdormecidas->next->next->next->next->next);
				printf("tarefasAdormecidas: %p\n", tarefasAdormecidas->next->next->next->next->next->next);
				printf("tarefasAdormecidas: %p\n", tarefasAdormecidas->next->next->next->next->next->next->next);*/
//				printf("ContextMain: %p\n\n", ContextMain);
				queue_remove((queue_t **) &tarefasAdormecidas, (queue_t*) *(temp3));
				queue_append((queue_t **) &fila, (queue_t*) *(temp3));
			}while (temp->aguardando != temp1);
		}
		task_t *t = tarefaCorrente-24;
		queue_remove((queue_t **) &fila, (queue_t*) t);
		swapcontext(tarefaCorrente, &dispatcherT.context);
	}
	else if (tarefaCorrente == &dispatcherT.context){
		ContextMain->suspenso = 0;
		((task_t *)(tarefaCorrente-24))->fim = systime();
		printf("Task %d exit: execution time %d ms. processor time %d ms. %d activations\n", ((task_t *)(tarefaCorrente-24))->id, ((task_t *)(tarefaCorrente-24))->fim - ((task_t *)(tarefaCorrente-24))->inicio, ((task_t *)(tarefaCorrente-24))->acumulador, ((task_t *)(tarefaCorrente-24))->ativacoes); 
//		queue_append((queue_t **) &tarefasProntas, (queue_t*) tarefaCorrente);
//		printf("\ntest\n");
		swapcontext(tarefaCorrente, &ContextMain->context);
//		printf("\ntest\n");
	}
}

int task_id (){
	if (tarefaCorrente == &ContextMain->context)
		return 0;
	else{
		int *ptr = tarefaCorrente - (sizeof (unsigned long int));	//tamanho do int, para encontrar int id
		return *ptr;
	}
}





void task_yield (){
	task_switch(&dispatcherT);
}