
/**
 * Ejercicio: UVA 13082 - High School Assembly
 * 
 * Autor: Eitan Embon 
 *  
 * Tiempo en UVA: 0.010s
 * 
 * Compilado con c++ 11
 */


#include <bits/stdc++.h>


using namespace std;

int Heghts [10 * 10 * 10 * 10 + 1];
int n;


/**
 * IDEA:
 * Recorro las alturas de izquierda a derecha, y encuentro la subsecuencia mas larga siendo esta una escalera
 *  y  empezando desde 1. Que sea de la forma 1 2 3 4 .... n.
 * El ultimo elemento k que  esté en la escalera determina que el resultado es N - k. Es decir tengo que hacer N - k 
 * movimientos hasta el final de forma ordenada (moviendo el elemento mas chico primero) para que la secuencia quede 
 * ordenada crecientemente.
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

	
	int T; cin >> T;
	int Case = 0;
	while(++Case <= T){

		cin >> 	n;
		
		// Input 
		for (int i = 1; i <= n; i++){
			cin >> Heghts[i];
		}
		

		// Encuentro la escalera.
		int ultimo_en_escalera = 0;
		for (int i = 1; i <  n +1; i++) if (Heghts[i] == ultimo_en_escalera + 1)
			ultimo_en_escalera ++;

		cout << "Case " << Case << ": " << (n - ultimo_en_escalera) << "\n";

	}
}
