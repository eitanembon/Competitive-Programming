
/**
 * Ejercicio: UVA 12321 - Gas Stations
 * 
 * Autor: Eitan Embon 
 *  
 * Tiempo en UVA: 0.030s
 * 
 * Compilado con c++ 11
 */


#include <bits/stdc++.h>

using namespace std;


pair<long long, long long> Gas_stations [10 * 10 * 10 * 10];
long long L, G;



/**
 * IDEA: 
 * Decir cuál es la mínima cantidad de intervalos que cubren todo el intervalo [0,L] -> Optimo
 * Luego la maxima cantidad de intervalos que dejo afuera, son la cant total de intervalos menos el optimo, encontrado arriba
 * 
 * Para esto. Sea Gas_Stations los intervalos (a,b). Los ordenamos por primer componente. 
 * En cada iteración buscamos el intervalo que cubra más y que además cubra o interseque el punto final ya cubierto.
 * 
 */	


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

	


	while(cin >> L >> G){
		if (L == 0 and G == 0) break;
		
		for (int i = 0; i < G; i++){
			long long x, r;	cin >> x >> r;
			Gas_stations[i] = {x - r, x + r};
		}
		

		sort(Gas_stations, Gas_stations + G);

		long long covered = 0;
		int min_quantity = 0;
		for (int i = 0; i < G and covered < L;){
			long long max_covered = -1;
			while(i < G and Gas_stations[i].first <= covered){ 
				max_covered =  max( Gas_stations[i].second, max_covered);
				i++;
			}
			if(max_covered < 0) break;
			covered = max_covered;
			min_quantity++;
		}

		cout <<  (covered >= L?  (G - min_quantity) :  -1) << "\n";

		}
}
