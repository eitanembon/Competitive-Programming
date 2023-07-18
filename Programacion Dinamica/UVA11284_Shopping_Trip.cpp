/**
 * Ejercicio: UVA 11284 - Shopping Trip
 * 
 * Autor: Eitan Embon
 * 
 * Tiempo en UVA: 0.120s
 * 
 * Compilado en C++11
*/

#include <bits/stdc++.h>

using namespace std;
using DiGraph = vector<vector<long long>>; 
using Vertex = int;
using Cost = long long;
using VertexSet = bitset<32>;
using Map = vector<unordered_map<VertexSet, Cost>>;

constexpr long long INF = numeric_limits<long long>::max()/2;
int M, N, P;




/**
 * @brief 
 * 	
f(from, visited) =   " Minimo costo de realizar un camino hasta el nodo destino empezando desde from, dado que ya visite
					  visited "

					
f(from, visited) = { 		
	0		destino esta en visited
	INF 	si visite todos menos destino y no hay arista from -> destino    // Este segundo caso no hace falta
	min {f (next, visited + from) + costo(from -> next)}  
									tal que next no fue visitado.
}
 *
 */
Cost camino_minimo(Vertex from, VertexSet visited, Vertex end, DiGraph& digraph, Map& mem){

	if (visited.test(end)) return 0;


	auto inserted = mem[from].insert({visited, INF});
    Cost* Min = &inserted.first->second;
	bool ingresado = inserted.second; 

	if(ingresado){
	for (int next = 1u; next < P+2; next++) if(not visited.test(next))
		*Min = min(*Min, digraph[from][next] + camino_minimo(next, visited | VertexSet().set(next), end, digraph, mem));
	}

	return *Min;
	
}

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(0);

	int Cases;
	cin >> Cases;
	while(Cases --){
		cin >> N >> M;
		N++;
		DiGraph dist(N, vector<long long> (N, INF));



	
		// Asigno distancias a Digrafo original
		for (int i = 0; i < N; i++)
		dist[i][i] =  0;
		
		for (int i = 0; i < M; i++)
		{

			int v, w;
			float cost;
			cin >> v >> w >> cost;
		
			dist[v][w] = dist[w][v] = min({dist[v][w], dist[w][v] ,llrint(cost * 100)});
		}

		// FLOYD

		for (int k = 0; k < N; k++)
    	for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++){
        	if (dist[i][j] > dist[i][k] + dist[k][j]) 
                dist[i][j] = dist[i][k] + dist[k][j];
		}


		cin >> P;


		DiGraph DigrafoTSP(P+2, vector<long long> (P+2, INF));
		vector<int> TSPtoOriginalNodes(P+1); 
		Map mem (P+2);
		

		TSPtoOriginalNodes[0] = 0;
		// Reasigno pesos para nodos que son tiendas con operas.
		for (int i = 0; i < P; i++)
		{

			int v;
			float cost;
			cin >> v >>  cost;
			TSPtoOriginalNodes[i+1] = v;

			for (int w = 0; w < N; w++) if(v != w )
				dist[w][v] -= llrint(cost * 100);
		}

		DigrafoTSP[P+1][P+1] = 0;
		DigrafoTSP[0][0] = 0;
		for (int v = 0; v < P +1; v++)
		{
			for (int w  = 1; w < P+1; w++) 
			{	
				if(v == w )
				DigrafoTSP[v][w] = 0;
				else if(v!= 0)
				DigrafoTSP[v][w] = dist[TSPtoOriginalNodes[v]][TSPtoOriginalNodes[w]];
				else{ // v == 0
				DigrafoTSP[v][w] = dist[TSPtoOriginalNodes[v]][TSPtoOriginalNodes[w]];
				DigrafoTSP[w][P+1] = dist[TSPtoOriginalNodes[w]][TSPtoOriginalNodes[v]];
				} 
				
			}
			
		}

		
		Cost res = -camino_minimo(0, 0ul, P+1, DigrafoTSP, mem);
		if (res > 0) cout << "Daniel can save $" << fixed << setprecision(2) << ((float)(res)/100) << "\n";
		else cout << "Don't leave the house\n";

	}
}
