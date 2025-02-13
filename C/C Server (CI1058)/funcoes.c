#include "main.h"

unsigned int sequencia = 0;

pacote* criarPacote (int origem, int destino, int tamanho, int tipo, unsigned char *dados){
	//Essa função organiza os dados do pacote em uma só estrutura.
	pacote *p;

	p = (pacote*)malloc(sizeof(pacote));

	p->inicio = INICIO;
	p->origem = origem;
	p->destino = destino;
	p->tamanho = tamanho;
	p->sequencia = sequencia;
	p->tipo = tipo;
	p->dados = dados;
	p->paridade = 0;

	return p;
	
}

unsigned char* colocarBuffer (pacote* p){
	//Essa função é usada para colocar as informações do pacote em um buffer. Posteriormente
	//Esse buffer é usado no envio.
	//Como destino, origem, tamanho, sequência, e tipo são menores que 1 byte, é preciso fazer
	//esses shift's e or's deles antes de colocá-los no buffer.
	int i;
	unsigned char *buffer = (unsigned char*)malloc(sizeof(unsigned char) * (p->tamanho + 4));

	buffer[0] = p->inicio;
										//ex: origem=client, destino=server, tamanho=15
	buffer[1] = p->destino << 6;		//0000.0010 << 6 = 1000.0000
	buffer[1] |= p->origem << 4;		//0000.0001 << 4 = 0001.0000 | 1000.0000 = 1001.0000
	buffer[1] |= p->tamanho;			//1001.0000 | 0000.1111 = 1001.1111
	
	buffer[2] = p->sequencia << 4;		//0000.xxxx << 4 = xxxx.0000
	buffer[2] |= p->tipo;				//xxxx.0000 | 0000.yyyy = xxxx.yyyy

	p->paridade = buffer[1] ^ buffer[2];
	
	for(i=0; i < p->tamanho; i++){
		buffer[i+3] = p->dados[i];
		p->paridade = p->paridade ^ p->dados[i];
	}
	
	buffer[i+3] = p->paridade;

	return buffer;
	
}

pacote* tirarBuffer(unsigned char *buffer){
	//Essa função faz o contrário de colocarBuffer, ou seja, tira as informações do buffer e 
	//coloca no pacote.
	int i;
	pacote *p = (pacote*)malloc(sizeof(pacote));
	
	p->inicio = buffer[0];
	
	p->destino = buffer[1] >> 6;		//1001.1111 >> 6 = 0000.0010
	p->origem = buffer[1] >> 4 & 3;		//1001.1111 >> 4 = 0000.1001 & 0011 = 0000.0001
	p->tamanho = buffer[1] & 15;		//1001.1111 & 0000.1111 = 1111
	
	p->sequencia = buffer[2] >> 4;		//xxxx.yyyy >> 4 = 0000.xxxx
	p->tipo = buffer[2] & 15;			//xxxx.yyyy & 0000.1111 = 0000.yyyy

	p->dados = (unsigned char*)malloc(p->tamanho);
	for(i=0; i < p->tamanho; i++){
		p->dados[i] = buffer[i+3];
	}
	
	p->paridade = buffer[i+3];

	return p;
}

int enviar(int socket, pacote *p, int server){
	//Essa função envia um pacote.
	int temp1, temp2;
	if (server == 1){
		temp1 = SERVER;
		temp2 = CLIENT;
	}
	else{
		temp1 = CLIENT;
		temp2 = SERVER;
	}

	unsigned char *buffer = colocarBuffer(p);
	
	int i = send (socket, buffer, MAX_PACOTE, 0);
	
	if (i == -1)
		perror("send");
	
	
	if (p->tipo == ACK)
		sequencia = (sequencia%15) + 1;
	if (p->tipo == ACK || p->tipo == NACK)
		return 1;
		
	pacote* resposta = receber(socket, temp1);
	if (resposta == NULL)	//timeout
		return 0;
		
	if (resposta->tipo == NACK)
		printf("nack retornado\n");
		
	return 1;
		
	
}

pacote* receber(int socket, int server){
	//Essa função recebe um pacote. Ao receber um ACK, a sequência é incrementada, e ao chegar
	//em 15, o valor máximo, volta para 0.
	int temp1, temp2;
	if (server == 1){
		temp1 = SERVER;
		temp2 = CLIENT;
	}
	else{
		temp1 = CLIENT;
		temp2 = SERVER;
	}
	
	int tentativas = 0;
	pacote *p;
	unsigned char *buffer = malloc (MAX_PACOTE * sizeof(char));
	
	while(1){
		int i = recv(socket,buffer,MAX_PACOTE,0);

		if (i < 0){
			if (server == 1)
				continue;
			tentativas++;
			printf("tentativa numero %d falhou\n", tentativas);
			if (tentativas == 5){
				printf("timeout\n");
				return NULL;
			}
			continue;
		}
		
		p = tirarBuffer(buffer);
		if (p->inicio != INICIO){
			free(p->dados);
			free(p);
			continue;
		}
		if (p->sequencia != sequencia){
			free(p->dados);
			free(p);
			continue;
		}
		if (p->tipo == ACK){
			sequencia = (sequencia%15)+1;
			return p;
		}
		if (p->tipo != NACK && p->tipo != ACK){
			pacote *ack = criarPacote(temp1, temp2, 0, ACK, NULL);
			if (enviar(socket, ack,temp1))
				return p;
		}
		
	}
	
	
}

comando* lerComando(){
	//Essa função lê o input do usuário e organiza essa informação em uma estrutura.
	int i = 0;
	int j = 0;
	comando *cmd = malloc(sizeof(comando));
	cmd->arg1 = NULL;
	cmd->arg2 = NULL;
	cmd->arg3 = NULL;
	char *input = malloc(sizeof(char) * 1024);
	char *temp = malloc(sizeof(char) * 1024);
	
	fgets(input, 1024, stdin);
	if (input[strlen(input) - 1] == '\n')
		input[strlen(input) - 1] = '\0';
	cmd->entrada = malloc(sizeof(char) * strlen(input));
	strcpy(cmd->entrada, input);
	
	
	while(input[i] != ' ' && input[i] != '\0'){
		temp[i] = input[i];
		i++;
	}
	
	if (!strcmp(temp, "cd")){
		cmd->tipo = CD;
		if (input[i] != '\0'){
			i++;
			while(input[i] != '\0'){
				temp[j] = input [i];
				i++;
				j++;
			}
			temp[j] = '\0';
			cmd->arg1 = malloc(sizeof(char) * strlen(temp));
			strcpy(cmd->arg1, temp);
		}
		else cmd->tipo = INVALIDO;
	}
	
	else if (!strcmp(temp, "lcd")){
		cmd->tipo = LCD;
		if (input[i] != '\0'){
			i++;
			while(input[i] != '\0'){
				temp[j] = input [i];
				i++;
				j++;
			}
			temp[j] = '\0';
			cmd->arg1 = malloc(sizeof(char) * strlen(temp));
			strcpy(cmd->arg1, temp);
		}
		else cmd->tipo = INVALIDO;
	}
	else if (!strcmp(temp, "ls"))
		cmd->tipo = LS;
	else if (!strcmp(temp, "lls"))
		cmd->tipo = LLS;
	else if (!strcmp(temp, "ver")){
		cmd->tipo = VER;
		if (input[i] != '\0'){
			i++;
			while(input[i] != '\0'){
				temp[j] = input [i];
				i++;
				j++;
			}
			temp[j] = '\0';
			cmd->arg1 = malloc(sizeof(char) * strlen(temp));
			strcpy(cmd->arg1, temp);
		}
		else cmd->tipo = INVALIDO;
	}
	else if (!strcmp(temp, "linha")){
		if (input[i] != '\0'){
			cmd->tipo = LINHA;
			i++;
			while(input[i] != ' ' && input[i] != '\0'){
				temp[j] = input [i];
				i++;
				j++;
			}
			temp[j] = '\0';
			cmd->arg1 = malloc(sizeof(char) * strlen(temp));
			strcpy(cmd->arg1, temp);
			
			i++;
			j = 0;
			if (input[i] != '\0'){
				while(input[i] != '\0'){
					temp[j] = input[i];
					i++;
					j++;
				}
				temp[j] = '\0';
				cmd->arg2 = malloc(sizeof(char) * strlen(temp));
				strcpy(cmd->arg2, temp);
			}
			else cmd->tipo = INVALIDO;
		}
		else cmd->tipo = INVALIDO;
		
	}
	else if (!strcmp(temp, "linhas")){
		if (input[i] != '\0'){
			cmd->tipo = LINHAS;
			i++;
			while(input[i] != ' ' && input[i] != '\0'){
				temp[j] = input [i];
				i++;
				j++;
			}
			temp[j] = '\0';
			cmd->arg1 = malloc(sizeof(char) * strlen(temp));
			strcpy(cmd->arg1, temp);
			
			i++;
			j = 0;
			if (input[i] != '\0'){
				while(input[i] != ' ' && input[i] != '\0'){
					temp[j] = input[i];
					i++;
					j++;
				}
				temp[j] = '\0';
				cmd->arg2 = malloc(sizeof(char) * strlen(temp));
				strcpy(cmd->arg2, temp);
				
				i++;
				j = 0;
				if (input[i] != '\0'){
					while(input[i] != '\0'){
						temp[j] = input[i];
						i++;
						j++;
					}
					temp[j] = '\0';
					cmd->arg3 = malloc(sizeof(char) * strlen(temp));
					strcpy(cmd->arg3, temp);
				}
				else cmd->tipo = INVALIDO;
			}
			else cmd->tipo = INVALIDO;
		}
		else cmd->tipo = INVALIDO;
		
	}
	else if (!strcmp(temp, "edit"))
		if (input[i] != '\0'){
			cmd->tipo = EDIT;
			i++;
			while(input[i] != ' ' && input[i] != '\0'){
				temp[j] = input [i];
				i++;
				j++;
			}
			temp[j] = '\0';
			cmd->arg1 = malloc(sizeof(char) * strlen(temp));
			strcpy(cmd->arg1, temp);
			
			i++;
			j = 0;
			if (input[i] != '\0'){
				while(input[i] != ' ' && input[i] != '\0'){
					temp[j] = input[i];
					i++;
					j++;
				}
				temp[j] = '\0';
				cmd->arg2 = malloc(sizeof(char) * strlen(temp));
				strcpy(cmd->arg2, temp);
				
				i++;
				j = 0;
				if (input[i] != '\0'){
					while(input[i] != '\0'){
						temp[j] = input[i];
						i++;
						j++;
					}
					temp[j] = '\0';
					cmd->arg3 = malloc(sizeof(char) * strlen(temp));
					strcpy(cmd->arg3, temp);
				}
				else cmd->tipo = INVALIDO;
			}
			else cmd->tipo = INVALIDO;
		}
		else cmd->tipo = INVALIDO;
		
	else{
		cmd->tipo = INVALIDO;
		return cmd;
	}
	
	
	return cmd;
	
}

void cd(int socket, comando *cmd){
	//Executa o cd, saindo do cliente. a primeira parte verifica se o tamanho do nome do diretório
	//de destino é maior que o tamanho máximo do pacote (15 bytes). Se for, quebra em pedaços
	//menores para enviar. Após isso, a função recebe um pacote do servidor. Se for nulo o cd foi
	//executado corretamente. Se não, o pacote traz uma mensagem com o erro ocorrido.
	unsigned char* parcial;
	if (strlen(cmd->arg1) > MAX_DADOS){
		int i, j = 0, k = 0, l;
		if (strlen(cmd->arg1) % MAX_DADOS == 0)
			l = 0;
		else
			l = 1;
		int nPartes = strlen(cmd->arg1)/MAX_DADOS + l;
		
		for (i = 0; i < nPartes; i++){
			j = 0;
			parcial = malloc(MAX_DADOS + 1);
			while(k < strlen(cmd->arg1) && j < MAX_DADOS){
				parcial[j] = cmd->arg1[k];
				k++;
				j++;
			}
			if (k == strlen(cmd->arg1) && l == 1)
				parcial[j] = '\0';
			pacote *p = criarPacote(CLIENT, SERVER, strlen(parcial), CD, parcial);
			if(!enviar(socket, p, 0))
				return;
			free(p->dados);
			free(p);
		}
		
	}
	else{
		pacote *p = criarPacote(CLIENT, SERVER, (int)strlen(cmd->arg1), CD, cmd->arg1);
		enviar(socket,p,0);
	}
	pacote *f = criarPacote(CLIENT,SERVER,0,FIM,NULL);
	if (!enviar(socket,f,0))
		return;


	free(f->dados);
	free(f);

	f = receber(socket,0);
	if (f == NULL)
		return;
	
	unsigned char* temp = "2";
	
	if (f->dados[0] == '2')
		printf("erro 2: diretorio %s inexistente no servidor\n", cmd->arg1);
}

void serverCd(int socket, unsigned char* diretorio){
	//Essa função executa o cd no server. Se o pacote for menor que 15 bytes, o nome do diretório
	//já vem de server.c, e o pacote recebido dentro desta função é do tipo FIM, então a função
	//não precisa tentar receber mais partes do nome. Após isso o server efetua o cd com o nome
	//recebido, enviando de volta um erro se o diretório não existir.
	unsigned char* d = (unsigned char*)malloc(sizeof(unsigned char) * 4096);
	strcat(d,diretorio);
	pacote *p;
	
	p = receber(socket,0);
	if (p == NULL)
		return;

	if (p->tipo == FIM){}
	else{
		do{

			if (strlen(p->dados) > 1)
				strcat(d, p->dados);
			else{
				d[strlen(d)] = p->dados[0];
				d[strlen(d)+1] = '\0';
			}
				
			free(p->dados);
			free(p);
			p = receber(socket,1);
			if (p == NULL)
				return;

		}while (p->tipo == CD);
	}

	char *erro = malloc (sizeof(char));
	if ((chdir ((char*) d)) == 0){
		erro[0] = '0';
		p = criarPacote(SERVER,CLIENT, 1, ACK, erro);
		enviar(socket, p,1);
	}
	else{
		erro[0] = '2';
		p = criarPacote(SERVER,CLIENT, 1, ERRO, erro);
		enviar(socket, p,1);
	}
		
}

void lcd(comando *cmd){
	//Efetua o cd no client.
	if ((chdir ((char*) cmd->arg1)) == 0){}
	else printf("diretorio %s nao existe\n", cmd->arg1);
}

void ls(int socket, comando *cmd){
	//Envia ao server um pedido de ls. Depois recebe o(s) pacote(s) com a informação do que está
	//contido no diretório do server.
	pacote *p = criarPacote(CLIENT, SERVER, 0, LS, NULL);
	enviar(socket,p,0);
	free(p);
	p = receber(socket,0);
	
	if (p == NULL)
		return;
	do{
		printf("%s", p->dados);
		free(p->dados);
		free(p);
		p = receber(socket,0);
		if (p == NULL)
			return;
	}while (p->tipo == LS);
}

void serverLs(int socket, unsigned char* dados){
	//Executa a função listar(), que retorna o conteúdo do diretório em um char*. Após isso, se
	//for necessário, quebra em partes menores antes de enviar.
	unsigned char* ls = listar();
	unsigned char* parcial;

	if (strlen(ls) > MAX_DADOS){
		int i, j = 0, k = 0, l;
		if (strlen(ls) % MAX_DADOS == 0)
			l = 0;
		else
			l = 1;
		int nPartes = strlen(ls)/MAX_DADOS + l;
		
		for (i = 0; i < nPartes; i++){
			j = 0;
			parcial = malloc(MAX_DADOS + 1);
			while(k < strlen(ls) && j < MAX_DADOS){
				parcial[j] = ls[k];
				k++;
				j++;
			}
			if (k == strlen(ls) && l == 1)
				parcial[j] = '\0';
			pacote *p = criarPacote(SERVER, CLIENT, strlen(parcial), LS, parcial);
			if(!enviar(socket, p,1))
				return;
			free(p->dados);
			free(p);
		}
		
	}
	else{
		pacote *p = criarPacote(SERVER, CLIENT, (int)strlen(ls), LS, ls);
		if (!enviar(socket,p,1))
			return;
	}
	pacote *f = criarPacote(SERVER,CLIENT,0,FIM,NULL);
	if (!enviar(socket,f,1))
		return;
	
}

void lls(comando *cmd){
	//Imprime o retorno da função listar().
	printf("%s\n", listar());
}

void ver(int socket, comando *cmd){
	//Envia um pedido de ver ao servidor, quebrando o nome do arquivo em menores partes se preciso,
	//e recebe o conteúdo do arquivo requisitado. Imprime erro caso o arquivo não exista.
	unsigned char* parcial;
	if (strlen(cmd->arg1) > MAX_DADOS){
		int i, j = 0, k = 0, l;
		if (strlen(cmd->arg1) % MAX_DADOS == 0)
			l = 0;
		else
			l = 1;
		int nPartes = strlen(cmd->arg1)/MAX_DADOS + l;
		
		for (i = 0; i < nPartes; i++){
			j = 0;
			parcial = malloc(MAX_DADOS + 1);
			while(k < strlen(cmd->arg1) && j < MAX_DADOS){
				parcial[j] = cmd->arg1[k];
				k++;
				j++;
			}
			if (k == strlen(cmd->arg1) && l == 1)
				parcial[j] = '\0';
			pacote *p = criarPacote(CLIENT, SERVER, strlen(parcial), VER, parcial);
			if(!enviar(socket, p,0))
				return;
			free(p->dados);
			free(p);
		}
		
	}
	else{
		pacote *p = criarPacote(CLIENT, SERVER, (int)strlen(cmd->arg1), VER, cmd->arg1);
		enviar(socket,p,0);
	}
	pacote *f = criarPacote(CLIENT,SERVER,0,FIM,NULL);
	if (!enviar(socket,f,0))
		return;
	free(f->dados);
	free(f);
	
	f = receber(socket,0);
	if (f == NULL)
		return;
	if (f->tipo == ERRO){
		printf("erro 3: arquivo %s inexistente no servidor\n", cmd->arg1);
		return;
	}
	int ab = 1;
	printf("%d- ", ab);
	ab++;
	do{
		
		for (int cd = 0; cd < strlen(f->dados); cd++){
			if (f->dados[cd] == '\n'){
				printf("%c", f->dados[cd]);
				printf("%d- ", ab);
				ab++;
				continue;
			}
			printf("%c", f->dados[cd]);
		}
		free(f->dados);
		free(f);
		f = receber(socket,0);
		if (f == NULL)
			return;
	}while (f->tipo == CONTEUDOARQUIVO);
	
	printf("\n");	//esse printf é usado para a última linha do arquivo não ser exibida
					//grudada no path do client.
	
}

void serverVer(int socket, unsigned char* arquivo){
	//Recebe o pedido de ver, recebendo vários pacotes caso o nome do arquivo seja maior que 15B.
	//Em seguida verifica se o arquivo existe, enviando um pacote de erro de volta caso necessário.
	//Em seguida usa a função lerArquivo para colocar o conteúdo em um char*. Após isso quebra o
	//Conteúdo do arquivo em partes menores para enviar ao client.
	unsigned char* d = (unsigned char*)malloc(sizeof(unsigned char) * 4096);
	strcat(d,arquivo);
	pacote *p;
	
	p = receber(socket,0);
	if (p == NULL)
		return;
	if (p->tipo == FIM){}
	else{
		do{
			strcat(d, p->dados);
			free(p->dados);
			free(p);
			p = receber(socket,1);
			if (p == NULL)
				return;
		}while (p->tipo == VER);
	}
		
	
	
	unsigned char* file = lerArquivo(d);
	if (file == NULL){
		//send pacote arquivo não existe
		char *erro = malloc (sizeof(char));
		erro[0] = '3';
		p = criarPacote(SERVER,CLIENT, 1, ERRO, erro);
		enviar(socket, p,1);
		return;
	}
	
	unsigned char* parcial;
	if (strlen(file) > MAX_DADOS){
		int i, j = 0, k = 0, l;
		if (strlen(file) % MAX_DADOS == 0)
			l = 0;
		else
			l = 1;
		int nPartes = strlen(file)/MAX_DADOS + l;
		
		for (i = 0; i < nPartes; i++){
			j = 0;
			parcial = malloc(MAX_DADOS + 1);
			while(k < strlen(file) && j < MAX_DADOS){
				parcial[j] = file[k];
				k++;
				j++;
			}
			if (k == strlen(file) && l == 1)
				parcial[j] = '\0';
			pacote *p = criarPacote(SERVER, CLIENT, strlen(parcial), CONTEUDOARQUIVO, parcial);
			if(!enviar(socket, p,1))
				return;
			free(p->dados);
			free(p);
		}
		
	}
	else{
		pacote *p = criarPacote(SERVER, CLIENT, (int)strlen(file), CONTEUDOARQUIVO, file);
		if (!enviar(socket,p,1))
			return;
	}
	pacote *f = criarPacote(SERVER,CLIENT,0,FIM,NULL);
	if (!enviar(socket,f,1))
		return;
	
	
	
}

void linha(int socket, comando *cmd){
	//Envia o pedido do comando linha ao server. Primeiro o nome do arquivo é enviado, sendo
	//quebrado em partes menores caso necessário. Após isso o número da linha é enviado, sendo
	//também quebrado em partes menores, embora isso dificilmente ocorra. Em seguida verifica
	//se foi recebido pacote de erro, sendo possível que a linha e/ou o arquivo não existam.
	//Caso não ocorram erros, recebe os pacotes da linha pedida.
	unsigned char* parcial;
	pacote *p;
	pacote *f;
	
	//envia arg2 == nome do arquivo
	if (strlen(cmd->arg2) > MAX_DADOS){
		int i, j = 0, k = 0, l;
		if (strlen(cmd->arg2) % MAX_DADOS == 0)
			l = 0;
		else
			l = 1;
		int nPartes = strlen(cmd->arg2)/MAX_DADOS + l;
		
		for (i = 0; i < nPartes; i++){
			j = 0;
			parcial = malloc(MAX_DADOS + 1);
			while(k < strlen(cmd->arg2) && j < MAX_DADOS){
				parcial[j] = cmd->arg2[k];
				k++;
				j++;
			}
			if (k == strlen(cmd->arg2) && l == 1)
				parcial[j] = '\0';
			p = criarPacote(CLIENT, SERVER, strlen(parcial), LINHA, parcial);
			if(!enviar(socket, p,0))
				return;
			free(p->dados);
			free(p);
		}
		
	}
	else{
		p = criarPacote(CLIENT, SERVER, (int)strlen(cmd->arg2), LINHA, cmd->arg2);
		enviar(socket,p,0);
	}
	f = criarPacote(CLIENT,SERVER,0,FIM,NULL);
	if (!enviar(socket,f,0))
		return;
	free(f->dados);
	free(f);
	
	//envia arg1 == numero da linha
	if (strlen(cmd->arg1) > MAX_DADOS){
		int i, j = 0, k = 0, l;
		if (strlen(cmd->arg1) % MAX_DADOS == 0)
			l = 0;
		else
			l = 1;
		int nPartes = strlen(cmd->arg1)/MAX_DADOS + l;
		
		for (i = 0; i < nPartes; i++){
			j = 0;
			parcial = malloc(MAX_DADOS + 1);
			while(k < strlen(cmd->arg1) && j < MAX_DADOS){
				parcial[j] = cmd->arg1[k];
				k++;
				j++;
			}
			if (k == strlen(cmd->arg1) && l == 1)
				parcial[j] = '\0';
			p = criarPacote(CLIENT, SERVER, strlen(parcial), INFIM, parcial);
			if(!enviar(socket, p,0))
				return;
			free(p->dados);
			free(p);
		}
		
	}
	else{
		p = criarPacote(CLIENT, SERVER, (int)strlen(cmd->arg1), INFIM, cmd->arg1);
		enviar(socket,p,0);
	}
	f = criarPacote(CLIENT,SERVER,0,FIM,NULL);
	if (!enviar(socket,f,0))
		return;
	free(f->dados);
	free(f);
	
	f = receber(socket,0);
	if (f == NULL)
		return;
	
	if (f->tipo == ERRO){
		if (f->dados[0] == '3')
			printf("erro 3: arquivo %s inexistente no servidor\n", cmd->arg2);
		else if (f->dados[0] == '4')
			printf("erro 4: linha %s inexistente no arquivo %s\n", cmd->arg1, cmd->arg2);
		return;
	}
	
	do{
		printf("%s", f->dados);
		free(f->dados);
		free(f);
		f = receber(socket,0);
		if (f == NULL)
			return;
	}while (f->tipo == CONTEUDOARQUIVO);
	
	
}

void serverLinha(int socket, unsigned char* arquivo){
	//Executa o comando linha no servidor. Primeiro recebe o nome do arquivo, depois o número da
	//linha requisitada. Em seguida coloca o conteúdo do arquivo em um char* através de 
	//lerArquivo(). Se o arquivo não existir envia um pacote de erro. Em seguida o número de linhas
	//do arquivo é calculado. Se a linha requisitada não existir envia pacote de erro. Após isso
	//busca pela linha requisitada, copia o conteúdo desta linha para outro char*, e envia o(s)
	//pacote(s) de volta para o client.
	unsigned char* d = (unsigned char*)malloc(sizeof(unsigned char) * 4096);
	strcat(d,arquivo);
	pacote *p;
	
	p = receber(socket,0);
	if (p == NULL)
		return;
	if (p->tipo == FIM){}
	else{
		do{
			strcat(d, p->dados);
			free(p->dados);
			free(p);
			p = receber(socket,1);
			if (p == NULL)
				return;
		}while (p->tipo == VER);
	}
	free(p->dados);
	free(p);
	
	unsigned char* e = (unsigned char*)malloc(sizeof(unsigned char) * 4096);
	p = receber(socket,0);
	if (p == NULL)
		return;
	if (p->tipo == FIM){}
	else{
		do{
			strcat(e, p->dados);
			free(p->dados);
			free(p);
			p = receber(socket,1);
			if (p == NULL)
				return;
		}while (p->tipo == INFIM);
	}
	int numeroLinha = atoi(e);
	
	unsigned char* file = lerArquivo(d);
	
	if (file == NULL){
		//send pacote arquivo não existe
		char *erro = malloc (sizeof(char));
		erro[0] = '3';
		p = criarPacote(SERVER,CLIENT, 1, ERRO, erro);
		enviar(socket, p,1);
		return;
	}
	
	int totalLinhas = 1;
	//encontra o número total de linhas no arquivo
	for (int xyz = 0; xyz < strlen(file); xyz++){
		if (file[xyz] == '\n')
			totalLinhas++;
	}
	
	if (numeroLinha > totalLinhas){
		//send pacote linha não existe
		char *erro = malloc (sizeof(char));
		erro[0] = '4';
		p = criarPacote(SERVER,CLIENT, 1, ERRO, erro);
		enviar(socket, p,1);
		return;
	}
	
	int i, j = 0, k, l, m = 0;
	
	for (i = 1; i < numeroLinha; i++){
		//busca o caractere onde começa a linha requisitada.
		while (file[j] != '\n'){
			j++;
			if (j > strlen(file))
				break;
		}
		j++;
		
	}
	
	k = j;
	
	while (file[k] != '\n' && file[k] != '\0')	//encontra o final da linha
		k++;
	
	unsigned char* f = (unsigned char*)malloc(sizeof(unsigned char) * (k-j+2));
	
	for (l = j; l < k; l++){
		//copia a linha para f
		if (file[l] == '\0')
			break;
		f[m] =file[l];
		m++;
	}
	f[m] = '\n';
	f[m+1] = '\0';
	
	unsigned char* parcial;
	if (strlen(f) > MAX_DADOS){
		int i, j = 0, k = 0, l;
		if (strlen(f) % MAX_DADOS == 0)
			l = 0;
		else
			l = 1;
		int nPartes = strlen(f)/MAX_DADOS + l;
		
		for (i = 0; i < nPartes; i++){
			j = 0;
			parcial = malloc(MAX_DADOS + 1);
			while(k < strlen(f) && j < MAX_DADOS){
				parcial[j] = f[k];
				k++;
				j++;
			}
			if (k == strlen(f) && l == 1)
				parcial[j] = '\0';
			pacote *p = criarPacote(SERVER, CLIENT, strlen(parcial), CONTEUDOARQUIVO, parcial);
			if(!enviar(socket, p,1))
				return;
			free(p->dados);
			free(p);
		}
		
	}
	else{
		pacote *p = criarPacote(SERVER, CLIENT, (int)strlen(f), CONTEUDOARQUIVO, f);
		if (!enviar(socket,p,1))
			return;
	}
	pacote *g = criarPacote(SERVER,CLIENT,0,FIM,NULL);
	if (!enviar(socket,g,1))
		return;
	
}

void linhas(int socket, comando *cmd){
	//Envia o pedido de linhas para o servidor. Primeiro envia o nome do arquivo, depois a linha
	//inicial, e depois a linha final. Em seguida verifica se foi recebido pacote de erro. Caso
	//o arquivo exista e a linha inicial seja válida, recebe as linhas requisitadas.
	unsigned char* parcial;
	//envia arg3 == nome arquivo
	if (strlen(cmd->arg3) > MAX_DADOS){
		int i, j = 0, k = 0, l;
		if (strlen(cmd->arg3) % MAX_DADOS == 0)
			l = 0;
		else
			l = 1;
		int nPartes = strlen(cmd->arg3)/MAX_DADOS + l;
		
		for (i = 0; i < nPartes; i++){
			j = 0;
			parcial = malloc(MAX_DADOS + 1);
			while(k < strlen(cmd->arg3) && j < MAX_DADOS){
				parcial[j] = cmd->arg3[k];
				k++;
				j++;
			}
			if (k == strlen(cmd->arg3) && l == 1)
				parcial[j] = '\0';
			pacote *p = criarPacote(CLIENT, SERVER, strlen(parcial), LINHAS, parcial);
			if(!enviar(socket, p,0))
				return;
			free(p->dados);
			free(p);
		}
		
	}
	else{
		pacote *p = criarPacote(CLIENT, SERVER, (int)strlen(cmd->arg3), LINHAS, cmd->arg3);
		enviar(socket,p,0);
	}
	pacote *f = criarPacote(CLIENT,SERVER,0,FIM,NULL);
	if (!enviar(socket,f,0))
		return;
	free(f->dados);
	free(f);
	
	//envia arg1 == numero da linha inicial
	if (strlen(cmd->arg1) > MAX_DADOS){
		int i, j = 0, k = 0, l;
		if (strlen(cmd->arg1) % MAX_DADOS == 0)
			l = 0;
		else
			l = 1;
		int nPartes = strlen(cmd->arg1)/MAX_DADOS + l;
		
		for (i = 0; i < nPartes; i++){
			j = 0;
			parcial = malloc(MAX_DADOS + 1);
			while(k < strlen(cmd->arg1) && j < MAX_DADOS){
				parcial[j] = cmd->arg1[k];
				k++;
				j++;
			}
			if (k == strlen(cmd->arg1) && l == 1)
				parcial[j] = '\0';
			pacote *p = criarPacote(CLIENT, SERVER, strlen(parcial), INFIM, parcial);
			if(!enviar(socket, p,0))
				return;
			free(p->dados);
			free(p);
		}
		
	}
	else{
		pacote *p = criarPacote(CLIENT, SERVER, (int)strlen(cmd->arg1), INFIM, cmd->arg1);
		enviar(socket,p,0);
	}
	f = criarPacote(CLIENT,SERVER,0,FIM,NULL);
	if (!enviar(socket,f,0))
		return;
	free(f->dados);
	free(f);
	
	//envia arg2 == numero da linha final
	if (strlen(cmd->arg2) > MAX_DADOS){
		int i, j = 0, k = 0, l;
		if (strlen(cmd->arg2) % MAX_DADOS == 0)
			l = 0;
		else
			l = 1;
		int nPartes = strlen(cmd->arg2)/MAX_DADOS + l;
		
		for (i = 0; i < nPartes; i++){
			j = 0;
			parcial = malloc(MAX_DADOS + 1);
			while(k < strlen(cmd->arg2) && j < MAX_DADOS){
				parcial[j] = cmd->arg2[k];
				k++;
				j++;
			}
			if (k == strlen(cmd->arg2) && l == 1)
				parcial[j] = '\0';
			pacote *p = criarPacote(CLIENT, SERVER, strlen(parcial), INFIM, parcial);
			if(!enviar(socket, p,0))
				return;
			free(p->dados);
			free(p);
		}
		
	}
	else{
		pacote *p = criarPacote(CLIENT, SERVER, (int)strlen(cmd->arg2), INFIM, cmd->arg2);
		enviar(socket,p,0);
	}
	f = criarPacote(CLIENT,SERVER,0,FIM,NULL);
	if (!enviar(socket,f,0))
		return;
	free(f->dados);
	free(f);
	
	f = receber(socket,0);
	if (f == NULL)
		return;
	
	if (f->tipo == ERRO){
		if (f->dados[0] == '3')
			printf("erro 3: arquivo %s inexistente no servidor\n", cmd->arg3);
		else if (f->dados[0] == '4')
			printf("erro 4: linha %s inexistente no arquivo %s\n", cmd->arg1, cmd->arg3);
		return;
	}
	
	do{
		printf("%s", f->dados);
		free(f->dados);
		free(f);
		f = receber(socket,0);
		if (f == NULL)
			return;
	}while (f->tipo == CONTEUDOARQUIVO);
	
	
}

void serverLinhas(int socket, unsigned char* arquivo){
	//Executa o pedido de linhas no servidor. Primeiro recebe o nome do arquivo, em seguida a
	//linha inicial e depois a linha final. Em seguida verifica se o arquivo existe e se a linha
	//inicial é válida, enviando erro caso contrário. Após isso busca o conteúdo pedido, e envia
	//ao client.
	pacote *p;
	unsigned char* f = (unsigned char*)malloc(sizeof(unsigned char) * 4096);
	p = receber(socket,0);
	strcat(f,arquivo);
	if (p == NULL)
		return;
	if (p->tipo == FIM){}
	else{
		do{
			strcat(f, p->dados);
			free(p->dados);
			free(p);
			p = receber(socket,1);
			if (p == NULL)
				return;
		}while (p->tipo == LINHAS);
	}
	free(p->dados);
	free(p);
	
	unsigned char* d = (unsigned char*)malloc(sizeof(unsigned char) * 4096);
	
	p = receber(socket,0);
	if (p == NULL)
		return;
	if (p->tipo == FIM){}
	else{
		do{
			strcat(d, p->dados);
			free(p->dados);
			free(p);
			p = receber(socket,1);
			if (p == NULL)
				return;
		}while (p->tipo == INFIM);
	}
	free(p->dados);
	free(p);
	int numeroLinhaInicial = atoi(d);
	unsigned char* e = (unsigned char*)malloc(sizeof(unsigned char) * 4096);
	p = receber(socket,0);
	if (p == NULL)
		return;
	if (p->tipo == FIM){}
	else{
		do{
			strcat(e, p->dados);
			free(p->dados);
			free(p);
			p = receber(socket,1);
			if (p == NULL)
				return;
		}while (p->tipo == INFIM);
	}
	free(p->dados);
	free(p);
	int numeroLinhaFinal = atoi(e);
	
	
	
	unsigned char* file = lerArquivo(f);
	if (file == NULL){
		//send pacote arquivo não existe
		char *erro = malloc (sizeof(char));
		erro[0] = '3';
		p = criarPacote(SERVER,CLIENT, 1, ERRO, erro);
		enviar(socket, p,1);
		return;
	}
	int totalLinhas = 1;
	for (int xyz = 0; xyz < strlen(file); xyz++){
		if (file[xyz] == '\n')
			totalLinhas++;
	}
	
	if (numeroLinhaInicial > totalLinhas){
		//send pacote linha não existe
		char *erro = malloc (sizeof(char));
		erro[0] = '4';
		p = criarPacote(SERVER,CLIENT, 1, ERRO, erro);
		enviar(socket, p,1);
		return;
	}
	
	int i, j = 0, k, l, m = 0;
	
	for (i = 1; i < numeroLinhaInicial; i++){
		//busca o caractere onde começa a linha inicial
		while (file[j] != '\n'){
			j++;
			if (j > strlen(file))
				break;
		}
		j++;
		
	}
	
	k = j;
	for (i; i < numeroLinhaFinal+1; i++){
		//busca o caractere onde termina a linha final
		while (file[k] != '\n'){
			k++;
			if (k > strlen(file))
				break;
		}
		k++;
	}
	
	
	
	unsigned char* g = (unsigned char*)malloc(sizeof(unsigned char) * (k-j+2));
	
	for (l = j; l < k; l++){
		// coloca o conteúdo em g
		if (file[l] == '\0')
			break;
		g[m] =file[l];
		m++;
	}
	g[m] = '\n';
	g[m+1] = '\0';
	
	unsigned char* parcial;
	if (strlen(g) > MAX_DADOS){
		int i, j = 0, k = 0, l;
		if (strlen(g) % MAX_DADOS == 0)
			l = 0;
		else
			l = 1;
		int nPartes = strlen(g)/MAX_DADOS + l;
		
		for (i = 0; i < nPartes; i++){
			j = 0;
			parcial = malloc(MAX_DADOS + 1);
			while(k < strlen(g) && j < MAX_DADOS){
				parcial[j] = g[k];
				k++;
				j++;
			}
			if (k == strlen(g) && l == 1)
				parcial[j] = '\0';
			pacote *p = criarPacote(SERVER, CLIENT, strlen(parcial), CONTEUDOARQUIVO, parcial);
			if(!enviar(socket, p,1))
				return;
			free(p->dados);
			free(p);
		}
		
	}
	else{
		pacote *p = criarPacote(SERVER, CLIENT, (int)strlen(g), CONTEUDOARQUIVO, g);
		if (!enviar(socket,p,1))
			return;
	}
	pacote *a = criarPacote(SERVER,CLIENT,0,FIM,NULL);
	if (!enviar(socket,a,1))
		return;
	
}

void edit(int socket, comando *cmd){
	//Envia o pedido de edit ao servidor. Primeiro envia o nome, depois o número da linha, e por
	//último o novo texto. Após isso a função recebe um novo pacote para verificar se ocorreu
	//algum erro. Essa função tem um bug estranho, em que após editar uma linha de um arquivo,
	//se for usado o comando ls, será impresso em tela o arquivo que foi editado, além do ls.
	unsigned char* parcial;
	
	//envia arg2 == nome do arquivo
	if (strlen(cmd->arg2) > MAX_DADOS){
		int i, j = 0, k = 0, l;
		if (strlen(cmd->arg2) % MAX_DADOS == 0)
			l = 0;
		else
			l = 1;
		int nPartes = strlen(cmd->arg2)/MAX_DADOS + l;
		
		for (i = 0; i < nPartes; i++){
			j = 0;
			parcial = malloc(MAX_DADOS + 1);
			while(k < strlen(cmd->arg2) && j < MAX_DADOS){
				parcial[j] = cmd->arg2[k];
				k++;
				j++;
			}
			if (k == strlen(cmd->arg2) && l == 1)
				parcial[j] = '\0';
			pacote *p = criarPacote(CLIENT, SERVER, strlen(parcial), EDIT, parcial);
			if(!enviar(socket, p,0))
				return;
			free(p->dados);
			free(p);
		}
		
	}
	else{
		pacote *p = criarPacote(CLIENT, SERVER, (int)strlen(cmd->arg2), EDIT, cmd->arg2);
		enviar(socket,p,0);
	}
	pacote *f = criarPacote(CLIENT,SERVER,0,FIM,NULL);
	if (!enviar(socket,f,0))
		return;
	free(f->dados);
	free(f);
	
	//envia arg1 == numero da linha
	if (strlen(cmd->arg1) > MAX_DADOS){
		int i, j = 0, k = 0, l;
		if (strlen(cmd->arg1) % MAX_DADOS == 0)
			l = 0;
		else
			l = 1;
		int nPartes = strlen(cmd->arg1)/MAX_DADOS + l;
		
		for (i = 0; i < nPartes; i++){
			j = 0;
			parcial = malloc(MAX_DADOS + 1);
			while(k < strlen(cmd->arg1) && j < MAX_DADOS){
				parcial[j] = cmd->arg1[k];
				k++;
				j++;
			}
			if (k == strlen(cmd->arg1) && l == 1)
				parcial[j] = '\0';
			pacote *p = criarPacote(CLIENT, SERVER, strlen(parcial), EDIT, parcial);
			if(!enviar(socket, p,0))
				return;
			free(p->dados);
			free(p);
		}
		
	}
	else{
		pacote *p = criarPacote(CLIENT, SERVER, (int)strlen(cmd->arg1), EDIT, cmd->arg1);
		enviar(socket,p,0);
	}
	f = criarPacote(CLIENT,SERVER,0,FIM,NULL);
	if (!enviar(socket,f,0))
		return;
	free(f->dados);
	free(f);
	
	//envia arg3 == texto
	if (strlen(cmd->arg3) > MAX_DADOS){
		int i, j = 0, k = 0, l;
		if (strlen(cmd->arg3) % MAX_DADOS == 0)
			l = 0;
		else
			l = 1;
		int nPartes = strlen(cmd->arg3)/MAX_DADOS + l;
		
		for (i = 0; i < nPartes; i++){
			j = 0;
			parcial = malloc(MAX_DADOS + 1);
			while(k < strlen(cmd->arg3) && j < MAX_DADOS){
				parcial[j] = cmd->arg3[k];
				k++;
				j++;
			}
			if (k == strlen(cmd->arg3) && l == 1)
				parcial[j] = '\0';
			pacote *p = criarPacote(CLIENT, SERVER, strlen(parcial), EDIT, parcial);
			if(!enviar(socket, p,0))
				return;
			free(p->dados);
			free(p);
		}
		
	}
	else{
		pacote *p = criarPacote(CLIENT, SERVER, (int)strlen(cmd->arg3), EDIT, cmd->arg3);
		enviar(socket,p,0);
	}
	f = criarPacote(CLIENT,SERVER,0,FIM,NULL);
	if (!enviar(socket,f,0))
		return;
	free(f->dados);
	free(f);
	f = receber(socket,0);
	
	if (f == NULL)
		return;
	
	if (f->tipo == ERRO){
		if (f->dados[0] == '3')
			printf("erro 3: arquivo %s inexistente no servidor\n", cmd->arg3);
		else if (f->dados[0] == '4')
			printf("erro 4: linha %s inexistente no arquivo %s\n", cmd->arg1, cmd->arg3);
		return;
	}
}

void serverEdit (int socket, unsigned char* arquivo){
	//Executa o edit no arquivo pedido. Recebe primeiro o nome, depois a linha, por último o texto.
	//em seguida verifica possíveis erros se o arquivo ou a linha não existirem. Em seguida é
	//feita a concatenação do que vem antes da linha a ser editada, a nova linha, e o que vem
	//depois da nova linha, e por fim a função reescreve o arquivo.
	//Essa função tem o bug mais inexplicável de todos: se for recebido um texto de 25 caracteres
	//(incluindo aspas), a última aspa não é removida, ao contrário de outros tamanhos de texto. 
	//É preciso um if específico pra isso.
	
	unsigned char* d = (unsigned char*)malloc(sizeof(unsigned char) * 4096);
	
	strcpy(d,arquivo);
	pacote *p;
	
	p = receber(socket,0);
	if (p == NULL)
		return;

	if (p->tipo == FIM){}
	else{
		do{
			strcat(d, p->dados);
			free(p->dados);
			free(p);
			p = receber(socket,1);
			if (p == NULL)
				return;
		}while (p->tipo == EDIT);
	}
	free(p->dados);
	free(p);

	unsigned char* e = (unsigned char*)malloc(sizeof(unsigned char) * 4096);
	p = receber(socket,0);

	if (p == NULL)
		return;

	if (p->tipo == FIM){}
	else{
		do{
			strcat(e, p->dados);
			free(p->dados);
			free(p);
			p = receber(socket,1);
			if (p == NULL)
				return;
		}while (p->tipo == EDIT);
	}
	free(p->dados);
	free(p);
	int numeroLinha = atoi(e);
	
	unsigned char* f = (unsigned char*)malloc(sizeof(unsigned char) * 4096);
	p = receber(socket,0);

	if (p == NULL)
		return;

	if (p->tipo == FIM){}
	else{
		do{
			strcat(f, p->dados);
			free(p->dados);
			free(p);
			p = receber(socket,1);
			if (p == NULL)
				return;
		}while (p->tipo == EDIT);
	}
	free(p->dados);
	free(p);
	
	unsigned char* file = lerArquivo(d);
	if (file == NULL){
		//send pacote arquivo não existe
		char *erro = malloc (sizeof(char));
		erro[0] = '3';
		p = criarPacote(SERVER,CLIENT, 1, ERRO, erro);
		enviar(socket, p,1);
		return;
	}
	int totalLinhas = 1;
	for (int xyz = 0; xyz < strlen(file); xyz++){
		if (file[xyz] == '\n')
			totalLinhas++;
	}
	
	if (numeroLinha > totalLinhas){
		//send pacote linha não existe
		char *erro = malloc (sizeof(char));
		erro[0] = '4';
		p = criarPacote(SERVER,CLIENT, 1, ERRO, erro);
		enviar(socket, p,1);
		return;
	}
	
	int i = 0, j = 0, k = 0, l, m = 0, n = 0;
	
	while(f[i] != '\0'){
		//tira as aspas
		f[i] = f[i+1];
		i++;
		
	}
	if (i == 25)		//
		f[i-3] = '\0';	//BUG OCORRE SEM ESSE IF
	else				//
		f[i-2] = '\0';	//
	
	for (i = 1; i < numeroLinha; i++){
		
		while (file[j] != '\n'){
			j++;
			if (j > strlen(file))
				break;
		}
		j++;
		
	}
	
	k = j;
	while (file[k] != '\n'){
		k++;
		if (k > strlen(file))
			break;
	}
	
	unsigned char* g = (unsigned char*)malloc(sizeof(unsigned char) * (strlen(file)+strlen(f)+2));
	
	for (i = 0; i < j; i++){
		
		g[i] = file[i];
		
	}

	int x = 0,y = 0,z = 0;
	if (k > strlen(file)){
		while (f[x] != '\0'){
			g[i] = f[x];
			i++;
			x++;
		}
		g[i] = '\0';
	}
	else{
		while (f[x] != '\0'){
			g[i] = f[x];
			i++;
			x++;
		}
		while (file[k] != '\0'){
			g[i] = file[k];
			i++;
			k++;
		}
		g[i] = '\0';
	}

	FILE * fp;
	if ((fp = fopen (d, "w")) == NULL)
		return;
	fputs(g, fp);
	fclose(fp);
	pacote *t = criarPacote(SERVER,CLIENT, 0, ACK, NULL);
	enviar(socket, t,1);

}

unsigned char* listar(){
	//Armazena o conteúdo do diretório em um char*.
	unsigned char* ls = (unsigned char*)malloc(sizeof(unsigned char) * 4096);
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if (d){
		while ((dir = readdir(d)) != NULL){
			strcat(ls, dir->d_name);
			strcat(ls, "\n");
		}
		closedir(d);
		
	}
	return ls;
}

unsigned char* lerArquivo(unsigned char* nome){
	//Armazena o conteúdo de um arquivo em um char*.
	unsigned char* conteudo;
	FILE * fp;
	if ((fp = fopen (nome, "r")) == NULL)
		return NULL;
	int i = 0;
	char c[1];
	while (1){
		c[0] = fgetc(fp);
		if (feof(fp))
			break;
		i++;
	}
	fclose(fp);
	conteudo = (unsigned char*)malloc(sizeof(unsigned char) * i);
	conteudo[0] = '\0';
	fp = fopen (nome, "r");
	c[0] = 0;
	int j = 0;
	while (1){
		c[0] = fgetc(fp);
		if(feof(fp))
			break;
		strcat(conteudo, c);
	}
	if (fp == NULL)
		fclose(fp);
	return conteudo;
}


