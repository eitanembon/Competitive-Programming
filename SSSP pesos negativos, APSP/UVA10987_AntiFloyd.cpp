
/**
 * Ejercicio: UVA 10987 - AntiFloyd
 * 
 * Autor: Eitan Embon 
 *  
 * Tiempo en UVA: 0.050s
 * 
 * Compilado con c++ 11
 */


#include <bits/stdc++.h>

using namespace std;

constexpr long long INF = numeric_limits<long long>::max()/2;



/**
 * IDEA: 
 * Tenemos la clausura transitiva, debo buscar lo contrario, la minima cantidad de aristas tal que las distancias se sigan respetando
 */


int  main(){
    ios::sync_with_stdio(false);
    cin.tie(0);	
	cout.tie(0);


	int cases, Case = 0, N; 
	cin >> cases;

	while (cases--)
	{
		cin >> N;

		vector<vector<long long>> dist(N, vector<long long>(N));
		vector<tuple<int, int, long long>> aristas; 
		int ans = 0;
		
		// Recibo las distnacias por input
		for (int i = 1; i < N; ++i)
		for (int j = 0; j < i ; ++j){
			cin >> dist[i][j];
			dist[j][i] = dist[i][j];
		}


		// Reviso que las distancias ya son mínimas, si no lo son, fueron mal medidas
		for (int k = 0; k < N; ++k)
		for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
		if (dist[i][k] + dist[k][j] < dist[i][j]){
			cout << "Case #" << ++Case << ":\n" << "Need better measurements.\n\n";
			goto next_case; // Salto al siguiente caso
		}
		// Aplico la "inversa" de Floyd para obtener lo contrario de la clausura transitiva
		for (int k = 0; k < N; ++k)
		for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j) if (i != j and i != k and j != k)
		if (dist[i][k] + dist[k][j] == dist[i][j])
			dist[i][j] = INF; // Quito la arista i-j, si es que puedo llegar de i a j pasando por k
		

		// Cuento la cantidad de aristas que quedaron en el grafo y las imprimo		
		for (int i = 0; i < N-1; ++i)
		for (int j = i+1; j < N ; ++j)
		if (dist[i][j] != INF){
			++ans;
			aristas.push_back({i, j, dist[i][j]});
		}
		
		cout << "Case #" << ++Case << ":\n" << ans << '\n';
		for (auto& arista : aristas)
			cout << get<0>(arista) + 1 << ' ' << get<1>(arista) + 1 << ' ' << get<2>(arista) << '\n';
		
		cout << '\n'; // Linea en blanco entre casos
		
		next_case:;


		
	}
}
