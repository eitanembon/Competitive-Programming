
/**
 * Ejercicio: UVA 563 - Crimewave
 * 
 * Autor: Eitan Embon, se utilizó la biblioteca de dinics por F.Soulignac
 *  
 * Tiempo en UVA: 0.070s
 * 
 * Compilado con c++ 11
 */


#include <bits/stdc++.h>

using namespace std;
constexpr int UNDEF = -1;

#ifndef ONLINE_JUDGE
#include "../dinics.h"
#else
//copy-paste dinics.h
#endif

using namespace dinics;

vector<int> dx = {0, 0, 1, -1};
vector<int> dy = {1, -1, 0, 0};

/**
 * IDEA:  
 * 	Caminos disjuntos en vertices, convertir vertices a aristas de capacidad uno y correr flujo maximo desde los bancos hasta los vertices de salida (los extremos de la matriz)
 */


int  main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
	cout.tie(0);

	int cases, dim_x, dim_y, banks; cin >> cases;


	while(cases--){
		cin >> dim_x >> dim_y >> banks;

		flowgraph<> red(2*dim_x * dim_y + 2);

		int s = 2*dim_x * dim_y; 
		int t = s + 1;

		// vertex (x,y)_in = x * dim_y + y  y vertex (x,y)_out = x * dim_y + y + dim_x * dim_y
		for (int x = 0; x < dim_x; ++x)
		for (int y = 0; y < dim_y; ++y){
			int vertex_in = x * dim_y + y;
			int vertex_out = vertex_in + dim_x * dim_y;
			red.add_edge(vertex_in, vertex_out, 1);
			for (int dir = 0; dir < 4; ++dir){
				int nx = x + dx[dir];
				int ny = y + dy[dir];
				int vertex_in_n = nx * dim_y + ny;

				if(nx >= 0 and nx < dim_x and ny >= 0 and ny < dim_y){
					red.add_edge(vertex_out, vertex_in_n, 1);
				}
			}
		}
		
		// Agregamos aristas de s a los vertices de los bancos
		for(int i = 0; i < banks; ++i){
			int x, y; cin >> x >> y; --x; --y;
			int vertex_in = x * dim_y + y;
			red.add_edge(s, vertex_in, 1);
		}

		// Agregamos aristas de los vertices de salida (los extremos de la matriz) a t
		for (int x = 0; x < dim_x; ++x){
			int y_derecha = dim_y - 1, y_izquierda = 0;
			int vertex_out_derecha = x * dim_y + y_derecha + dim_x * dim_y;
			int vertex_out_izquierda = x * dim_y + y_izquierda + dim_x * dim_y;
			red.add_edge(vertex_out_derecha, t, 1);
			red.add_edge(vertex_out_izquierda, t, 1); 
		}
		for (int y = 0; y < dim_y; ++y){
			int x_arriba = 0, x_abajo = dim_x - 1;
			int vertex_out_arriba = x_arriba * dim_y + y + dim_x * dim_y;
			int vertex_out_abajo = x_abajo * dim_y + y + dim_x * dim_y;
			red.add_edge(vertex_out_arriba, t, 1);
			red.add_edge(vertex_out_abajo, t, 1); 
		}


		if (red.maxflow(s, t) == banks){
			cout << "possible" << endl;
		} else {
			cout << "not possible" << endl;
		}
	}
		
}

