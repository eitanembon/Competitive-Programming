
/**
 * Ejercicio: UVA 11478 - Halum
 * 
 * Autor: Eitan Embon 
 *  
 * Tiempo en UVA: 1.400s
 * 
 * Compilado con c++ 11
 */


#include <bits/stdc++.h>


using namespace std;
using Graph = vector<vector<pair<int, long long>>>;

constexpr long long INF = numeric_limits<long long>::max()/2;

Graph G, G_k;


// Bellman Ford devuelve true si hay un ciclo negativo
bool bellman_ford(int s, Graph& Ady, vector<long long>& dist){
	auto n = Ady.size();
	dist.assign(n, INF);
	dist[s] = 0;
	bool cambio = true;
	for (auto i = 0u; i < n - 1 and cambio; i++)
	{
		cambio = false;
		for (auto u = 0u; u < n; u++)
		for (auto e : Ady[u])
		{
			int v = e.first;
			long long p = e.second;
			if (dist[u] + p < dist[v])
			{
				dist[v] = dist[u] + p;
				cambio = true;
			}
		}
	}
	return cambio;
}

bool tiene_un_ciclo(int v, Graph& Ady, vector<bool>& visitado){
	if(visitado[v])
		return true;
	visitado[v] = true;
	
	for(auto e : Ady[v]){
		int u = e.first;
		if(tiene_un_ciclo(u, Ady, visitado))
			return true;
	}
	return false;
}

//Creo el grafo G_k segun un K
void construir_G_k(long long K){
	G_k.clear();
	G_k.resize(G.size());
	for(auto i = 1u; i < G.size(); i++)
	for(auto e : G[i]){
		int j = e.first;
		long long cij = e.second;
		G_k[i].push_back({j, cij - K});
	}
	for (auto i = 1u; i < G.size(); i++)
		G_k[0].push_back({i, 0});	
}



// Busqueda binaria para en econtrar el maximo k 
long long maximo_k(long long izq, long long der){
	while (izq < der)
	{
		long long medio = (der + izq + 1)/2 ;
		vector<long long> dist;
		
		construir_G_k(medio);
		bool funciona = not bellman_ford(0, G_k, dist);

		if(der == izq + 1 )
			return funciona ? der : izq;
		if(funciona)
			izq = medio;
		else
			der = medio - 1;
	}
	return der;

	
}

/**
 * IDEA: 
 * Armo el sistema de SRD con ecuaciones de la forma dj - di <= cij - k para una arista (i, j) con peso cij. Hago 
 * busqueda binaria en los distintos 1 <= K <= 10000 para encontrar el maximo K tal que el sistema de ecuaciones 
 * tenga solucion.
 */


int  main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
	cout.tie(0);


	int  N, M;

	while (cin >> N >> M )
	{
		G.clear(); 
		G.resize(N+1);

		// recibo el input y armo el grafo 
		for(auto ignore = 0; ignore < M; ignore++){
			int i, j;
			long long cij;
			cin >> i >> j >> cij;
			G[i].push_back({j, cij});
		}

		// Chequeo si el grafo orginal es un dag
		vector<bool> visitado(N+1, false);
		if(not tiene_un_ciclo(1, G, visitado)){
			cout << "Infinite\n";
			continue;
		}

		// resuelvo el sistema de ecuaciones para K = 1, Si no funciona asi, entonces no funciona para ningun K
		construir_G_k(1);

		vector<long long> dist;

		bool hay_ciclo_negativo = bellman_ford(0, G_k, dist);

		if(hay_ciclo_negativo){
			cout << "No Solution\n";
			continue;
		}

		//Hago busqueda binaria en los distintos 1 <= K <= 10000
		long long d_min = 0, d_max = 10000;
		cout << maximo_k(d_min, d_max) << "\n";	


		
	}
}
