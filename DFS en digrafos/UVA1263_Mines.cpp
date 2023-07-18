
/**
 * Ejercicio: UVA 1263 - Mines
 * 
 * Autor: Eitan Embon 
 *  
 * Tiempo en UVA: 0.620s
 * 
 * Compilado con c++ 11
 */


#include <bits/stdc++.h>


using namespace std;
using Graph = vector< vector<long long >>;
using Components_list = vector< vector<long long >>;
using Coordenate = pair<long long , long long >;
using Node = unordered_map<long long, unordered_map<long long, long long> >;


	


void dfs(long long  v, Graph& Adyacencias, vector< bool>& visitado, vector<long long >& order) {
	visitado[v] = true;
	for (long long  u : Adyacencias[v]) 
		if (not visitado[u] ){
			dfs(u, Adyacencias, visitado, order);
		}
	
	order.push_back(v);
}

//Encuentra las componentes fuermente conexas de un grafo
// En componentes me quedan las SCC en orden topologico
void SCC(Graph& Adyacencias, vector< vector<long long >>& componentes){	
	auto N = Adyacencias.size();
	vector<long long > orden;
	vector<bool> visitado(N, false);
	
	// Hago topological sort de los nodos del grafo
	for (auto i = 0u; i < N; i++) if ( not visitado[i])
		dfs(i, Adyacencias, visitado, orden);
	reverse(orden.begin(), orden.end());
	
	// Hago el grafo transpuesto
	Graph Adyacencias_T(N);
	for (auto i = 0u; i < N; i++) for (long long  j : Adyacencias[i])
		Adyacencias_T[j].push_back(i);
	
	// Hago dfs en el grafo transpuesto en el orden topologico
	visitado.assign(N, false);
	for (long long  i : orden) if (not visitado[i]) {
		componentes.push_back({});
		dfs(i, Adyacencias_T, visitado, componentes.back());
	}
}



/**
 * IDEA: 
 * Detectar las componentes fuertemente conexas. Encontrar los nodos que tienen grado de entrada 0 en el grafo de SCC y sumarlos. 
 */


int  main(){
    ios::sync_with_stdio(false);
    cin.tie(0);


	long long  N, cases; cin >> cases;

	while (cases--)
	{
		cin >> N;

		Components_list componentes;
		Node nodo;
		Graph Adyacencias(N);
		vector<Coordenate> coordenadas(N);
		vector<long long> square_size(N);



		//Paso 1: Leo el input y armo el grafo de adyacencias
		for (auto  i = 0; i < N; i++)
		{
			long long x, y, d; cin >> x >> y >> d;
			x = 2*x; y = 2*y; 						// Multiplico por 2 para no tener que dividir d por 2
			nodo[x][y] = i;
			coordenadas[i] = {x, y};
			square_size[i] = d;
		}

		for(auto i = 0; i < N; i++)
		for(auto j = 0; j < N; j++)
		{
			if (i == j) continue;
			auto x1 = coordenadas[i].first, y1 = coordenadas[i].second;
			auto x2 = coordenadas[j].first, y2 = coordenadas[j].second;
			auto d = square_size[i];
			if (x1 + d >= x2 and x1 <= x2 + d and y1 + d >= y2 and y1 <= y2 + d)
				Adyacencias[i].push_back(j);
		}


		//Paso 2: Encuentro las componentes fuertemente conexas
		SCC(Adyacencias, componentes);

		//Paso 3: Busco las componentes que tienen grado entrada 0 en el grafo de SCC
		int grados_entrada_nulo = 0;
		vector<bool> visitado(N, false);

		for(auto& componente : componentes)
		if (not visitado[componente[0]])
		{
			grados_entrada_nulo++;
			vector<long long > order;
			dfs(componente[0], Adyacencias, visitado, order);
			
		}
		
		cout << grados_entrada_nulo << "\n";
		
	}
}
