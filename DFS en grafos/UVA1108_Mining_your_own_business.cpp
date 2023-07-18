/**
 * Ejercicio: UVA 1108 - Mining Your Own Business
 * 
 * Autor: Eitan Embon 
 *  
 * Tiempo en UVA: 0.820s
 * 
 * Compilado con c++ 11
 */


#include <bits/stdc++.h>

using namespace std;
using Edge = pair<int, int>;

int N, M;


vector<unordered_set<int>> Graph;

vector<int> CCS;


/**
 * Observacion: Si hay dos puntos de articulacion adyacentes a una componente, entonces si se destruye un punto de articulacion se puede escapar por el otro.
 * 
 * Minimas rutas de escape de la mina = cantidad de componentes conexas que quedan al sacar los puntos de articulacion y que solo esten adyacentes a un punto de articulacion. 
 * 
 * Cant de formas de establecer las rutas de escape = prod #CCi  tal que CCi es una componente conexa que resulta de quitar los puntos de articulacion y
 * 													  tiene solo un punto de articulacion adyacente
*/
set<int> adjs_art_points;

int count_ccs(int u, vector<bool>& visited, vector<bool>& is_articulation){
	visited[u] = true;
	int cc = 1;
	for (int v : Graph[u]) if (not visited[v]){
		if(is_articulation[v]) {
			adjs_art_points.insert(v);
			continue;
		}
		cc += count_ccs(v, visited, is_articulation);
		
	}
	return cc;
}

int low(int v, vector<int>& nivel, vector<int>& mem, vector<vector<int>>& hijos, vector<vector<int>>& back_edges){
	if (mem[v] != -1) return mem[v];

	int res = nivel[v];
	for (int u : hijos[v]){
		res = min(res, low(u, nivel, mem, hijos, back_edges));
	}

	for (int u : back_edges[v]){
		res = min(res, nivel[u]);
	}

	return mem[v] = res;
}



void dfs(int u, vector<int>& color, vector<vector<int>>& hijos, vector<int>& padre, vector<vector<int>>& back_edges, vector<int>& nivel){
	color[u] = 1;
	for (int v : Graph[u]) if (color[v] == 0){
		nivel[v] = nivel[u] + 1;
		padre[v] = u;
		hijos[u].push_back(v);
		dfs(v, color, hijos, padre, back_edges, nivel);
	}else if (v != padre[u] and color[v] == 1){
		back_edges[u].push_back(v);
	}
	color[u] = 2;
}


void puntos_de_articulacion(vector<bool>& is_articulation){
	vector<int> color(N, 0);
	vector<vector<int>> hijos(N);
	vector<vector<int>> back_edges(N);
	vector<int> padre(N, -1);
	vector<int> nivel(N, 0);
	
	for (int i = 0; i < N; i++) if(color[i] == 0)
		dfs(i, color, hijos, padre, back_edges, nivel);
	
	

	vector<int> mem(N, -1);
	for(int i = 0; i < N; ++i){
		if(padre[i] == -1 and hijos[i].size() > 1) is_articulation[i] = true;
	}
	
	
	for(int i = 0; i < N; ++i){
		for(int hijo : hijos[i]){
			if (low(hijo, nivel, mem, hijos, back_edges) >= nivel[i] and padre[i] != -1){
				is_articulation[i] = true;
			}
		}
	}

}

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(0);


	int Case = 1;
	while(cin >> M ){
		if (M == 0) break;
		
		CCS.clear();
		Graph.clear();
		vector<pair<int, int>> aristas;
		// Paso 1: Leo el input y construyo el grafo
		N = 0;
		for (int i = 0; i < M; ++i){
			int u, v;
			cin >> u >> v; N = max({N, u, v});

			aristas.push_back({--u, --v});
		}

		Graph.resize(N);
		for (auto arista : aristas) if(arista.first != arista.second) {
			Graph[arista.first].insert(arista.second);
			Graph[arista.second].insert(arista.first);
		}

		// Paso 2: Calculo los puntos de articulacion
		vector<bool> is_articulation(N, false);
		puntos_de_articulacion(is_articulation);



		//Paso 3: Calculo la cantidad de componentes conexas que quedan al sacar los puntos de articulacion y que solo esten adyacentes a un punto de articulacion.
		vector<bool> visited(N, false);

		for (int i = 0; i < N; i++) if ( not visited[i] and not is_articulation[i]){
			adjs_art_points.clear();
			int cc = count_ccs(i, visited, is_articulation);
			if (adjs_art_points.size() == 1)
				CCS.push_back(cc);
		}
		
		// Paso 4: Calculo la cantidad de formas de establecer las rutas de escape
		long long cant_formas = 1;
		for (int cc : CCS){
			cant_formas *= cc;
		}
		if (CCS.size() != 0) 
			cout << "Case " << Case << ": " << CCS.size() << " " << cant_formas << "\n";
		else 
			cout << "Case " << Case << ": " << 2 << " " << ((long long) (N) * (long long)(N - 1)) / 2 << "\n"; 

		Case++;

	}
}
