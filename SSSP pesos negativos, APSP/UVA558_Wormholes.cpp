
/**
 * Ejercicio: UVA 558 - Wormholes
 * 
 * Autor: Eitan Embon 
 *  
 * Tiempo en UVA: 0.020s
 * 
 * Compilado con c++ 11
 */


#include <bits/stdc++.h>


using namespace std;
using Graph = vector<vector<pair<int, long long>>>;

constexpr long long INF = numeric_limits<long long>::max()/2;

Graph adyacencias;



// Bellman-Ford

bool negative_cicles(int s){
	auto N = adyacencias.size();
	vector<long long> dist(N, INF);
	dist[s] = 0;

	for (int i = 1; i <= N; i++)
	for (int u = 0; u < N; u++)
	for (auto v : adyacencias[u])
	if (dist[u] + v.second < dist[v.first]) {
		dist[v.first] = dist[u] + v.second;
		if (i == N)  	// Si estoy en la ultima iteracion y todavia puedo relajar, hay un ciclo negativo
			return true;
	}
	return false;
}

/**
 * IDEA: 
 *  - Si hay ciclos negativos, puedo viajar en el tiempo indefinidamente. Busco ciclos negativos conn Bellman-Ford
 */


int  main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
	cout.tie(0);

	int cases, N, M;
	cin >> cases;

	while (cases --)
	{
		
		adyacencias.clear();

		cin >> N >> M;

		adyacencias.resize(N);

		// Armo el grafo de adyacencias
		for (int  i = 0; i < M; i++)
		{
			int  u, v, p;
			cin >> u >> v >> p;
			adyacencias[u].push_back({v, p});
		}
		
		// Si hay ciclos negativos, puedo viajar en el tiempo indefinidamente
		if (negative_cicles(0))
			cout << "possible\n";
		else
			cout << "not possible\n";
	}
}
