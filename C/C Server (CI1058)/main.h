#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define INICIO 126				//Marcador de início – 01111110
#define CLIENT 1				//O cliente deve ter endereço 01
#define SERVER 2				//O servidor deve ter endereço 10

#define CD 0					//cd – nome do diretório viaja na área de dados
#define LS 1					//ls
#define VER 2					//ver – nome arquivo viaja na área de dados
#define LINHA 3					//linha – nome arquivo viaja na área de dados
#define LINHAS 4				//linhas – nome arquivo viaja na área de dados
#define EDIT 5					//edit – nome arquivo viaja na área de dados
#define ACK 8					//ACK
#define NACK 9					//NACK
#define INFIM 10				//linha inicial e final – área da dados carrega um ou dois inteiros
#define CONTEUDOLS 11			//Conteúdo ls
#define CONTEUDOARQUIVO 12		//Conteúdo Arquivo
#define FIM 13					//Fim transmissão – área da dados sempre vazia
#define ERRO 15					//erro – campo de dados contém código do erro
								//
#define EAPROIBIDO 1			//acesso proibido / sem permissão
#define EDINEXISTENTE 2			//diretório inexistente
#define EAINEXISTENTE 3			//arquivo inexistente
#define ELINEXISTENTE 4			//linha inexistente

#define INVALIDO 20
#define LCD 21
#define LLS 22

#define MAX_PACOTE 19
#define MAX_DADOS 15

typedef struct pacote{
	unsigned char inicio;
	unsigned char destino;
	unsigned char origem;
	unsigned char tamanho;
	unsigned char sequencia;
	unsigned char tipo;
	unsigned char *dados;
	unsigned char paridade;
}pacote;

typedef struct comando{
	int tipo;
	char *entrada;
	char *arg1;
	char *arg2;
	char *arg3;
}comando;

pacote* criarPacote (int origem, int destino, int tamanho, int tipo, unsigned char *dados);
unsigned char* colocarBuffer (pacote* p);
pacote* tirarBuffer(unsigned char *buffer);
pacote* receber(int socket, int server);
comando* lerComando();
void cd(int socket, comando *cmd);
void serverCd(int socket, unsigned char* diretorio);
void lcd(comando *cmd);
void ls(int socket, comando *cmd);
void serverLs(int socket, unsigned char* dados);
void lls(comando *cmd);
void ver(int socket, comando *cmd);
void serverVer(int socket, unsigned char* arquivo);
void linha(int socket, comando *cmd);
void serverLinha(int socket, unsigned char* arquivo);
void linhas(int socket, comando *cmd);
void serverLinhas(int socket, unsigned char* arquivo);
void edit(int socket, comando *cmd);
void serverEdit (int socket, unsigned char* arquivo);
unsigned char* listar();
unsigned char* lerArquivo(unsigned char* nome);
