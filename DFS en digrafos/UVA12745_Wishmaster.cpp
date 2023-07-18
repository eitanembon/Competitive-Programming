
/**
 * Ejercicio: UVA 12745 - Wishmaster
 * 
 * Autor: Eitan Embon 
 *  
 * Tiempo en UVA: 1.490s
 * 
 * Compilado con c++ 11
 */


#include <bits/stdc++.h>


using namespace std;
using Graph = vector<vector<long long >>;
using Components_list = vector< unordered_set<long long >>;
using Coordenate = pair<long long , long long >;
using Node = unordered_map<long long, unordered_map<long long, long long> >;


	


void dfs_toposort(long long  v, Graph& Adyacencias, vector<bool>& visitado, vector<long long>& order) {
	visitado[v] = true;
	for (long long  u : Adyacencias[v]) 
		if (not visitado[u] ){
			dfs_toposort(u, Adyacencias, visitado, order);
		}
	
	order.push_back(v);
}

void dfs_find_cc(long long  v, Graph& Adyacencias, vector<bool>& visitado, unordered_set<long long>& order) {
	visitado[v] = true;
	for (long long  u : Adyacencias[v]) 
		if (not visitado[u] ){
			dfs_find_cc(u, Adyacencias, visitado, order);
		}
	
	order.insert(v);
}
//Encuentra las componentes fuermente conexas de un grafo
// En componentes me quedan las SCC en orden topologico
void SCC(Graph& Adyacencias, Components_list& componentes){	
	auto N = Adyacencias.size();
	vector<long long > orden;
	vector<bool> visitado(N, false);
	
	// Hago topological sort de los nodos del grafo
	for (auto i = 0u; i < N; i++) if ( not visitado[i])
		dfs_toposort(i, Adyacencias, visitado, orden);
	reverse(orden.begin(), orden.end());
	
	// Hago el grafo transpuesto
	Graph Adyacencias_T(N);
	for (auto i = 0u; i < N; i++) for (long long  j : Adyacencias[i])
		Adyacencias_T[j].push_back(i);
	
	// Hago dfs en el grafo transpuesto en el orden topologico
	visitado.assign(N, false);	
	for (long long  i : orden) if (not visitado[i]) {
		componentes.push_back({});
		dfs_find_cc(i, Adyacencias_T, visitado, componentes.back());
	}
}



/**
 * IDEA:
 * Se resuelve con 2-SAT. 
 * Los literales logicos son de la forma...
 * Sea x_i e y_i los deseos de la persona i. Quiero que no se cumplan los dos deseos.
 * 
 * (not x_1 or not y_1) and (not x_2 or not y_2) and ... and (not x_n or not y_n)
 *  
 * Para transformalos a grafo de adyacencias, hago lo siguiente:
 * Transformo los literales en implicaciones logicas de la forma: not x_i U not y_i <-> (x_i -> not y_i) and (y_i -> not x_i)
 * 
 * Detecto las componentes conexas, y si construir y no construir estan en la misma componente, entonces no es posible.	  
 */


int  main(){
    ios::sync_with_stdio(false);
    cin.tie(0);


	long long  N, M, cases, Case(0); cin >> cases;

	while (cases--)
	{
		
		cin >> N >> M;

		Components_list componentes;
		Node nodo;
		Graph Adyacencias(2*N);

		//Paso 1: Leo el input y armo el grafo de adyacencias
		for (auto  i = 0; i < M; i++)
		{
			long long x, y; cin >> x >> y;
			if(x < 0) x = -x + N -1; else x--;	
			if(y < 0) y = -y + N -1; else y--;
			long long not_x = (x + N) % (2*N), not_y = (y + N) % (2*N);  // Son formulas de la forma: not x U not y. Las transformo: en x -> not y and y -> not x
			Adyacencias[x].push_back(not_y);
			Adyacencias[y].push_back(not_x);
		}


		//Paso 2: Encuentro las componentes fuertemente conexas
		SCC(Adyacencias, componentes);

		// //Paso 3: Busco si not x y x estan en la misma componente fuertemente conexa
		bool es_posible = true;
		for (auto& componente : componentes)
		for (auto& x : componente)
			if (componente.find(x + N) != componente.end()){
				es_posible = false;
				break;
			}
		
		cout << "Case " << ++Case << ": " << (es_posible ? "Yes" : "No") << "\n";	
	}
}
