#include "main.h"

int ConexaoRawSocket (char *);

int main (){
	int socket = ConexaoRawSocket("lo");
	printf("client conectado\n");
	comando *cmd;
	char *cwd = malloc(sizeof(char) * 1024);
	while (1){
		cwd = getcwd(cwd, 1024);
		printf("%s$ ", cwd);
		cmd = lerComando();
		
		if (cmd->tipo == CD)
			cd(socket, cmd);
		else if (cmd->tipo == LCD)
			lcd(cmd);
		else if (cmd->tipo == LS)
			ls(socket, cmd);
		else if (cmd->tipo == LLS)
			lls(cmd);
		else if (cmd->tipo == VER)
			ver(socket, cmd);
		else if (cmd->tipo == LINHA)
			linha(socket, cmd);
		else if (cmd->tipo == LINHAS)
			linhas(socket, cmd);
		else if (cmd->tipo == EDIT)
			edit(socket, cmd);
		else printf("comando invalido\n");
		
	}
}
