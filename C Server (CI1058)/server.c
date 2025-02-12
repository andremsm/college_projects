#include "main.h"
int ConexaoRawSocket (char *);

int main (){
	pacote *p;
	int socket = ConexaoRawSocket("lo");
	printf("server conectado\n");
	char *cwd = malloc(sizeof(char) * 1024);
	while (1){
		cwd = getcwd(cwd, 1024);
		printf("%s$", cwd);
		p = receber(socket,1);
		printf("\n");
		
		if (p->tipo == CD)
			serverCd(socket, p->dados);
		else if (p->tipo == LS)
			serverLs(socket, p->dados);
		else if (p->tipo == VER)
			serverVer(socket, p->dados);
		else if (p->tipo == LINHA)
			serverLinha(socket, p->dados);
		else if (p->tipo == LINHAS)
			serverLinhas(socket, p->dados);
		else if (p->tipo == EDIT)
			serverEdit(socket,p->dados);
	}
	
}
