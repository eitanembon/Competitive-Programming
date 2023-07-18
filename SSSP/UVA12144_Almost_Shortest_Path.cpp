
/**
 * Ejercicio: UVA 12144 - Almost Shortest Path
 * 
 * Autor: Eitan Embon 
 *  
 * Tiempo en UVA: 0.040s
 * 
 * Compilado con c++ 11
 */


#include <bits/stdc++.h>


using namespace std;
using Graph = vector<vector<pair<int, long long>>>;

constexpr long long INF = numeric_limits<long long>::max()/2;

Graph adyacencias;
Graph adyacencias_T;



// Dijkstra, versión con priority_queue
void dijkstra(int s, Graph& ady, vector<long long>& dist ){
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
	pq.push({0, s});

	while(not pq.empty()){
		int v = pq.top().second; 
		long long d = pq.top().first;
		pq.pop();
		if (dist[v] < d) continue; // Chequeo si ya lo procesé con menor distancia

		for (auto e : ady[v]){
			int u = e.first;
			long long p = e.second;
			if (dist[u] > dist[v] + p){
				dist[u] = dist[v] + p;
				pq.push({dist[u], u});
			}
		}
	}

}


/**
 * IDEA: 
 * Armo el grafo que no tenga aristas st_eficientes y luego calculo las distancias minimas desde s en ese grafo. Devuelvo la distancia hacia t. 
 */


int  main(){
    ios::sync_with_stdio(false);
    cin.tie(0);


	int  N, M, s, t;

	while (cin >> N >> M and N != 0 and M != 0)
	{
		adyacencias.clear(); adyacencias_T.clear();
		adyacencias.resize(N); adyacencias_T.resize(N);
		
		cin >> s >> t;


		// Armo el grafo de adyacencias
		for (int  i = 0; i < M; i++)
		{
			int  u, v, p;
			cin >> u >> v >> p;
			adyacencias[u].push_back({v, p});
			adyacencias_T[v].push_back({u, p});
		}
		
		// Calculo las distancias minimas desde s
		vector<long long> dist_s(N, INF);
		dist_s[s] = 0;
		dijkstra(s, adyacencias, dist_s);

		// Calculo las distancias minimas hacia t
		vector<long long> dist_t(N, INF);
		dist_t[t] = 0;
		dijkstra(t, adyacencias_T, dist_t);


		// Armo un nuevo grafo sin las aristas st_eficientes
		Graph adyacencias_sin_st_eficientes(N);
		for (int v = 0; v < N; v++)
		for (auto e : adyacencias[v])
		{
			int u = e.first;
			long long p = e.second;
			if (dist_s[v] + p + dist_t[u] != dist_s[t])
				adyacencias_sin_st_eficientes[v].push_back({u, p});
		}
		
		// Calculo las distancias minimas desde s en el nuevo grafo
		dist_s.assign(N, INF);
		dist_s[s] = 0;
		dijkstra(s, adyacencias_sin_st_eficientes, dist_s);

		if (dist_s[t] == INF)
			cout << -1 << '\n';
		else
			cout << dist_s[t] << '\n';
		
	}
}
