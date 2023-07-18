
/**
 * Ejercicio: UVA 10092 - The Problem with the Problem Setter
 *
 * Autor: Eitan Embon, se utilizó la biblioteca de dinics por F.Soulignac
 *
 * Tiempo en UVA: 0.010s
 *
 * Compilado con c++ 11
 */

#include <bits/stdc++.h>

using namespace std;

#ifndef ONLINE_JUDGE
#include "dinics.h"
#else
// copy-paste dinics.h
#endif

using namespace dinics;

/**
 * IDEA:
 * 		Problema de asignación 
 *    Hay p problemas a asignar y k categorías a donde asignar los problemas. 
 * 
 * 		s -> p_i con capacidad 1 (problema i)
 * 		p_i -> k_j con capacidad 1 (problema i a categoría j) sii el problema i pertenece a la categoría j
 * 		k_j -> t con capacidad c_j (cant de problemas requeridos por categoría j)
 * 		
 * 
 * 		Una unidad de flujo representa un problema asignado a una categoría
 * 		s -> p_i -> k_j -> t representa un problema i asignado a la categoría j
 * 
 * 		
 * 		Si el flujo máximo es igual a la suma de la cant de problemas requeridos por las categorías, entonces se puede asignar
 *    
 */

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	
	int P, K, s, t, nro_problemas_requeridos;

	while (cin >> K >> P and P != 0 and K != 0)
	{

		flowgraph<> red(P + K + 2);

		s = P + K;
		t = s + 1;	
		nro_problemas_requeridos = 0;
		// Agrego las aristas desde k_j a t
		for (int j = 0; j < K; j++)
		{
			int c;
			cin >> c;
			red.add_edge(P + j, t, c);
			nro_problemas_requeridos += c;
		}

		// Agrego las aristas desde s a p_i y desde p_i a k_j
		for (int i = 0; i < P; i++)
		{
			int cant_problemas;
			cin >> cant_problemas;
			red.add_edge(s, i, 1);
			for (int j = 0; j < cant_problemas; j++)
			{	
				int k;
				cin >> k; k--;
				red.add_edge(i, P + k, 1);
			}
		}

		vector<vector<int>> solucion(K, vector<int>());
		
		// Calculo el flujo máximo y recupero la solución
		if (red.maxflow(s, t) == nro_problemas_requeridos){
			for (int i = 0; i < P; i++)if (red.get_saturated_edges_of(i).size() > 0){
				flowgraph<>::edge e = red.get_saturated_edges_of(i)[0];
				solucion[e.to - P ].push_back(i + 1);	
			}
			cout << 1 << "\n";
			for (auto &v : solucion){
				for (auto i = 0ul; i < v.size(); i++){
					cout << v[i];
					if (i != v.size() - 1)
						cout << " ";
				}
				cout << "\n";
			}
		}
		else{
			cout << 0 << "\n";
		}
	}
}
