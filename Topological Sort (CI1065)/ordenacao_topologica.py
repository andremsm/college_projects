#!/usr/bin/env python3
import pydot
import sys
import re
class Grafo:
	def __init__(self, n_vertices):
		self.vertices = []
		for i in range(n_vertices):
			self.vertices.append({
				"vizinhos": [],
				"estado": 0
			})
		self.V = n_vertices
		self.l = []
	def inserir_aresta(self, u, v):
		self.vertices[u]["vizinhos"].append(v)
	def ordenacao_topologica_recursao(self, v):
		self.vertices[v]["estado"] = 1
		for i in self.vertices[v]["vizinhos"]:
			if self.vertices[i]["estado"] == 0:
				self.ordenacao_topologica_recursao(i)
		self.l.insert(0, v)
		self.vertices[v]["estado"] = 2
	def ordenacao_topologica(self):
		for i in range(self.V):
			if self.vertices[i]["estado"] == 0:
				self.ordenacao_topologica_recursao(i)
		return self.l
	def ciclos_recursao(self, v, visitado):
		self.vertices[v]["estado"] = 1
		visitado[v] = True
		for vizinho in self.vertices[v]["vizinhos"]:
			if self.vertices[vizinho]["estado"] == 0:
				if self.ciclos_recursao(vizinho, visitado) == True:
					return True
			elif visitado[vizinho] == True:
				return True
		self.vertices[v]["estado"] = 2
		visitado[v] = False
		return False
	def ciclos(self):
		visitado = []
		for i in range(self.V + 1):
			visitado.append(False)
		for i in range(self.V):
			if self.vertices[i]["estado"] == 0:
				if self.ciclos_recursao(i, visitado) == True:
					return True
		return False
	def reset(self):
		for i in range(self.V):
			self.vertices[i]["estado"] = 0
if __name__ == '__main__':
	input_graph = sys.stdin.read()
	graphs = pydot.graph_from_dot_data(input_graph)
	for graph in graphs:
		if graph.get_subgraphs():
			subgraphs = graph.get_subgraphs()
			for subgraph in subgraphs:
				edges = subgraph.get_edges()
				source_list = []
				destination_list = []
				letter = ""
				node_list = []
				for edge in edges:
					source,destination = edge.to_string().replace(";","").split(" -> ")
					if source not in node_list:
						node_list.append(source)
					if destination not in node_list:
						node_list.append(destination)
					source = re.split('(\d+)', source)
					destination = re.split('(\d+)', destination)
					source_list.append(int(source[1]))
					destination_list.append(int(destination[1]))
					letter = source[0]
				node_number = max(max(source_list), max(destination_list)) + 1
				g = Grafo(node_number)
				for i in range(len(edges)):
					g.inserir_aresta(source_list[i], destination_list[i])
				if g.ciclos():
					sys.stderr.write("Erro: grafo possui ciclos")
				else:
					g.reset()
					ordenacao_topologica = g.ordenacao_topologica()
					for i in ordenacao_topologica:
						if letter + str(i) not in node_list:
							ordenacao_topologica.remove(i)
					with open('output.txt', 'w') as f:
						for i in range(len(ordenacao_topologica)):
							if i != len(ordenacao_topologica) - 1:
								f.write(str(letter) + str(ordenacao_topologica[i]) + " ")
								print(str(letter) + str(ordenacao_topologica[i]), end=" ")
							else:
								f.write(str(letter) + str(ordenacao_topologica[i]) + "")
								print(str(letter) + str(ordenacao_topologica[i]), end="")
		else:
			edges = graph.get_edges()
			source_list = []
			destination_list = []
			letter = ""
			node_list = []
			for edge in edges:
				source,destination = edge.to_string().replace(";","").split(" -> ")
				if source not in node_list:
					node_list.append(source)
				if destination not in node_list:
					node_list.append(destination)
				source = re.split('(\d+)', source)
				destination = re.split('(\d+)', destination)
				source_list.append(int(source[1]))
				destination_list.append(int(destination[1]))
				letter = source[0]
			node_number = max(max(source_list), max(destination_list)) + 1
			#min_node = min(min(source_list), min(destination_list))
			g = Grafo(node_number)
			for i in range(len(edges)):
				g.inserir_aresta(source_list[i], destination_list[i])
			if g.ciclos():
				sys.stderr.write("Erro: grafo possui ciclos")
			else:
				g.reset()
				ordenacao_topologica = g.ordenacao_topologica()
				for i in ordenacao_topologica:
					if letter + str(i) not in node_list:
						ordenacao_topologica.remove(i)
				with open('output.txt', 'w') as f:
					for i in range(len(ordenacao_topologica)):
						if i != len(ordenacao_topologica) - 1:
							f.write(str(letter) + str(ordenacao_topologica[i]) + " ")
							print(str(letter) + str(ordenacao_topologica[i]), end=" ")
						else:
							f.write(str(letter) + str(ordenacao_topologica[i]) + "")
							print(str(letter) + str(ordenacao_topologica[i]), end="")
