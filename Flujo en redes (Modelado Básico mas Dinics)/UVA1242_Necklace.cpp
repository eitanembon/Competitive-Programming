
/**
 * Ejercicio: UVA 1242 - Necklace
 *
 * Autor: Eitan Embon, se utilizó la biblioteca de dinics por F.Soulignac
 *
 * Tiempo en UVA: 0.250s
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
 *  Hay collar de ciclos sii hay dos caminos disjuntos (en aristas) que van desde s hasta t implica
 * 	Demo:
 * 	 =>) Hay un collar de ciclos que solo coinciden en un vértice en los extremos.
 * 			- En cada ciclo hay dos caminos desde un "extremo" al otro.
 * 			- Si ponemos a s en un extremo y a t en el otro, entonces hay dos caminos disjuntos desde s hasta t.
 * 				que pasen por todos los vertices de los ciclos.
 * 	<=) Hay dos caminos disjuntos desde s hasta t que pasan por todos los vertices de los ciclos.
 * 	        - En partiuclar dichos caminos podría o no coincidir e en un vértice intermiedio.
 * 			   * Si el primer vértice que coinciden no es t, entonces hallamos un primer "extremo" que cierra un ciclo
 * 			   * Si el que coinciden es t, entonces hallamos el cierre del collar de ciclos.
 *
 * ALGORITMO:
 * 		En el mismo grafo de la entrada, ponemos todas las aristas en capacidad 1, y chequeamos si hay un flujo de valor >= 2
 * 		(El valor del flujo maximo indica la cantidad de caminos disjuntos (en aristas) de s a t)
 */

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int N, M, s, t, Case = 1;

	while (cin >> N >> M and N != 0 and M != 0)
	{

		flowgraph<> red(N);

		for (int i = 0; i < M; ++i)
		{
			int u, v;
			cin >> u >> v;
			red.add_edge(u - 1, v - 1, 1);
			red.add_edge(v - 1, u - 1, 1);
		}

		cin >> s >> t;
		s--;
		t--;

		cout << "Case " << Case++ << ": " << (red.maxflow(s, t) >= 2 ? "YES" : "NO") << '\n';
	}
}
