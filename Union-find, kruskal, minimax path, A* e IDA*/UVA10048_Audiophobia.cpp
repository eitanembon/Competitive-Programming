/**
 * Ejercicio: UVA 10048 - Audiophobia
 * 
 * Autor: Eitan Embon 
 *  
 * Tiempo en UVA: 0.050s
 * 
 * Compilado con c++ 11
 */


#include <bits/stdc++.h>


using namespace std;

using ll = long long;
using Graph = vector<tuple<long long, int, int>>;
using Arbol = vector<vector<pair<ll, int>>>;

constexpr long long INF = numeric_limits<long long>::max()/2;
constexpr ll UNDEF = -1 ;


struct DSU
{
	void MAKE_SET( int n){
		padre = tamano = vector<int>(n);
		for(int v = 0; v < n; v++) {
			padre[v] = v;
			tamano[v] = 1;
		}
	}

	int FIND(int v){
		if(padre[v] == v) return v;

		return padre[v] = FIND(padre[v]);
	}

	void UNION(int v, int w){
		v = FIND(v); w = FIND(w);

		if(tamano[v] < tamano[w]) swap(v, w);
		 
		tamano[v] = tamano[v] + tamano[w];
		padre[w] = v;
	}
	
	vector<int> padre;
	vector<int> tamano;
};



Graph Aristas;

/**
 * Arista max en el camino minimo en un arbol desde desde a v pasando por u
 * max_edge_in_path(u, hasta, desde) = 	c(desde,hasta) 			si u == hasta
 * 											
 * 					max_{w/ w adyacente de u y w!=desde y hay camino desde "desde" hasta "hasta" pasando por u}
 * 							(c(u, w), max_edge_in_path(w, v, u))
*/

ll dfs_min_max(Arbol& arbol, int u, int hasta, int desde){
	if (desde == hasta) return 0;

	ll max_edge = UNDEF;

	for(auto w : arbol[u]) if(not (w.second == desde)){	
		
		if (w.second == hasta) return w.first; // Si llegue a v, devuelvo el peso de la arista
		ll aux = dfs_min_max(arbol, w.second, hasta, u);
		if (aux != UNDEF) max_edge = max(max_edge, max(aux, w.first));
	}

	return max_edge;	

}

void kruskal( Arbol& AGM, int n = -1){
	sort(Aristas.begin(), Aristas.end());

	DSU dsu;
	dsu.MAKE_SET(n);

	for (auto e : Aristas )
	{
        ll c; int v, w;
        tie(c, v, w) = e;
		
		if(dsu.FIND(v) != dsu.FIND(w)){
			dsu.UNION(v,w);
			AGM[v].push_back({c, w});
			AGM[w].push_back({c, v});
		}
	}
	
}


int main() {

    int C, S, Q;
	int caso = 1;
    while(cin >> C >> S >> Q and C != 0 and S != 0 and Q != 0){
        
		if(caso != 1) cout << "\n";
		
		Aristas.clear();
        for(int i = 0; i < S; i++){
            int u,v; 
			ll c;
            cin>>u>>v>>c;
            u--, v--;
            Aristas.push_back({c,u,v});
        }

        Arbol AGM(C);

        kruskal(AGM, C);

		// Recibo las queries
		cout << "Case #" << caso++ << "\n";


		for(int i = 0; i < Q; i++){
			int u, v;
			cin >> u >> v;
			u--, v--;
			ll max_edge = dfs_min_max(AGM, u, v, u);

			if (max_edge == UNDEF) cout << "no path\n";
			else cout << max_edge << "\n";
		}

    }
}