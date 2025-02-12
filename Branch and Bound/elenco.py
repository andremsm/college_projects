#!/usr/bin/env python3
import sys
import timeit

n_personagens = 0
n_grupos = 0
n_atores = 0
custo_otimo = 999999999999
x_otimo = []
atores = []
nos_criados = 0
opcao_A = False

class Ator:
	
	def __init__(self, valor_cobrado, numero_grupos, indice_grupos, id):
		self.valor = valor_cobrado
		self.n_grupos = numero_grupos
		self.grupos = indice_grupos
		self.id = id

def representativo(X):
	global n_grupos
	
	r = False
	k = 1
	grupos = set()
	for i in range(n_grupos):
		grupos.add(k)
		k += 1
	representados = set()
	
	for i in X:
		for j in i.grupos:
			if j not in representados:
				representados.add(j)
	
	if grupos == representados:
		r = True
	
	return r

def custo(X):
	custo_X = 0
	for i in X:
		custo_X += int(i.valor)
	return custo_X

def viavel(X):
	global n_personagens, n_grupos, atores
	
	grupos = set()
	
	for i in X:
		for j in i.grupos:
			if j not in grupos:		#grupos já representados
				grupos.add(j)
	
	i = n_personagens - len(X) + 1
	for j in range(i, len(atores)):	#atores que podem ser escolhidos
		for k in atores[j].grupos:
			if k not in grupos:
				grupos.add(k)
	
	grupo_total = set()
	
	for i in range(n_grupos):
		grupo_total.add(i + 1)
		
	if grupo_total == grupos:
		return True
	return False

def custo_ator(a):
	return a.valor

def otimo(X):
	global n_personagens, atores, custo_otimo, opcao_A
	
	if opcao_A:	#Professor
		custo_escolhidos = custo(X)
		nao_escolhidos = []
		for ator in atores:
			if ator not in X:
				nao_escolhidos.append(ator)
		minimo = 999999999999
		for ator in nao_escolhidos:
			if ator == None:
				continue
			if ator.valor < minimo:
				minimo = ator.valor
		personagens_sem_ator = n_personagens - len(X)
		flimitante = custo_escolhidos + (minimo * personagens_sem_ator)
		if custo_otimo > flimitante:
			return True
		return False
	else:	#Aluno
		custo_escolhidos = custo(X)
		nao_escolhidos = []
		for ator in atores:
			if ator not in X and ator != None:
				nao_escolhidos.append(ator)
		
		nao_escolhidos.sort(key=custo_ator)
		personagens_sem_ator = n_personagens - len(X)
		custo_nao_escolhidos = 0
		for i in range(personagens_sem_ator):
			custo_nao_escolhidos += nao_escolhidos[i].valor
		
		flimitante = custo_escolhidos + custo_nao_escolhidos
		if custo_otimo > flimitante:
			return True
		return False

def branch_and_bound(k, i, X):
	global n_personagens, n_grupos, n_atores, atores, custo_otimo, x_otimo, nos_criados
	
	nos_criados += 1

	if k == n_personagens:
		if representativo(X) and custo(X) < custo_otimo:
			custo_otimo = custo(X)
			x_otimo = X.copy()
		return
	else:
		j = i + 1
		while j <= n_atores:
			X.append(atores[j])
			if not viavel(X) or not otimo(X):
				X.pop()
				return
			k += 1
			branch_and_bound(k, j, X)
			k -= 1
			X.pop(-1)
			j = j + 1

def main():
	global n_personagens, n_grupos, n_atores, atores, nos_criados, opcao_A
	
	for i, arg in enumerate(sys.argv):
		if "-a" in arg:
			opcao_A = True
		
	
	l, m, n = input().split()		#l = |S|, S = Conjunto de Grupos /// m = |A|, A = Conjunto de Atores /// n = |P|, P = Conjunto de Personagens
	
	n_personagens = int(n)
	n_grupos = int(l)
	n_atores = int(m)
	
	#atores = []						#Lista de Atores
	atores.append(None)
	id = 1
	for i in range(int(m)):
		v, s = input().split()		#v = Valor Cobrado /// s = Número de Grupos
		v = int(v)
		grupos = []
		
		for j in range(int(s)):
			grupo = int(input())
			grupos.append(grupo)	#Incluir grupos dos quais o ator faz parte
		
		ator = Ator(v, s, grupos, id)
		atores.append(ator)			#Incluir ator na lista de Atores
		ator = None
		id += 1
	
	X = []

	t0 = timeit.default_timer()
	branch_and_bound(0, 0, X)
	t1 = timeit.default_timer()
	
	if custo_otimo != 999999999999:
		for i in range(len(x_otimo) - 1):
			print(x_otimo[i].id, end=' ')
		if x_otimo:
			print(x_otimo[len(x_otimo) - 1].id)
		print(custo_otimo)
		print(nos_criados, file=sys.stderr)
		print("%.16f" % (t1 - t0), file=sys.stderr)
	else:
		print("Inviável")
		print(nos_criados, file=sys.stderr)
		print("%.16f" % (t1 - t0), file=sys.stderr)
	
if __name__ == '__main__':
	main()
