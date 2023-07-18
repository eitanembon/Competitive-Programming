
/**
 * Ejercicio: UVA 12228 - Transportation System
 * 
 * Autor: Eitan Embon 
 *  
 * Tiempo en UVA: 0.010s
 * 
 * Compilado con c++ 11
 */


#include <bits/stdc++.h>

using namespace std;

using ll = long long;
constexpr ll INF = numeric_limits<ll>::max()/2;
constexpr ll UNVISITED = numeric_limits<ll>::max();
constexpr ll VISITED = UNVISITED - 1;

int n, r;
vector<vector<ll>> dist;
struct DSU{

    DSU(int N){
        padre = rank = vector<int>(N);
        for(int v = 0; v < N; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }
	// Esta funcion me devuelve la cantidad de componentes conexas que hay hasta ahora
	int count(){
		int res = 0;
		for(auto v = 0; v < (int)padre.size(); v++)
			if(v == padre[v]) res++;
		return res;
	}

    vector<int> padre;
    vector<int> rank;
	
};
//Devuelve en prim[w] el peso de la arista entre w y padre[w] en el AGM
// Devuelve en este caso el costo de las aristas roads y de las arisas railroads
pair<double, double> prim_n2(vector<ll>& prim){
    
    prim[0] = 0;
    double roads_cost = 0, railroads_cost=0;
    for(int e = 0; e < n; ++e) {
        auto v = min_element(prim.begin(), prim.end()) - prim.begin();
        // Sumo los costos, tomo raiz cuadrada ya que no lo toma antes para no perder precision
        if(prim[v] <= r*r) roads_cost += sqrt(prim[v]);
        else railroads_cost += sqrt(prim[v]);
        
        prim[v] = VISITED;
        for(int w = 0; w < n; ++w) if(prim[w] != VISITED) {
            prim[w] = min(prim[w], dist[v][w]);
        }
    }
    return {roads_cost, railroads_cost};
}

int main() {
	int Cases, Case=0;
    cin >> Cases;
    
	while(Cases--){
		cin>>n>>r;
		vector<pair<ll,ll>> city(n);
		
		dist = vector<vector<ll>>(n,vector<ll>(n,INF));
		for(int i = 0; i < n; i++)
			cin >> city[i].first >> city[i].second;
		

		DSU dsu(n); // dsu para contar la cantidad de estados

		for(auto i = 0; i < n; i++)
		for(auto j = 0; j < n; j++)
		{
			if (i == j ) dist[i][j] = 0;
			ll dist_2 = (city[i].first - city[j].first)*(city[i].first - city[j].first) + (city[i].second - city[j].second)*(city[i].second - city[j].second);
			dist[i][j] = dist_2;
			if (dist_2 <= r*r) dsu.unite(i,j); // pertenecen a un mismo estado
		}
		// Calculamos los pesos de las aristas del AGM en el grafo de dists
        vector<ll> prim(n, UNVISITED);
        pair<double, double> res = prim_n2(prim);

        // Imprimimos la respuesta
        cout << "Case #" << ++Case << ": ";
        cout << dsu.count() << " " << llrint(res.first) << " " << llrint(res.second) << '\n';
	}
}