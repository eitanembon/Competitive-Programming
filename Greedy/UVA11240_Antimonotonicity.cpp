
/**
 * Ejercicio: UVA 11240 - Antimonotonicity
 * 
 * Autor: Eitan Embon 
 *  
 * Tiempo en UVA: 0.040
 * 
 * Compilado con c++ 11
 */


#include <bits/stdc++.h>


using namespace std;

int Fred [3 * 10 * 10 * 10 * 10];
int N;


/**
 * IDEA: 
 * Dada una secuencia fred: 
 * 
 * Fred: a_1 ... a_k ,b_1, ..., b_k', c_1, ..., c_k'' .... 
 * 
 * Donde la secuencia a es creciente. La secunecia b es decreciente. La secuencia c es creciente.  
 * Podemos armarnos la subsecuencia Mary mas larga como
 * 
 * Mary = a_k, b_k', c_k'', d_k'''  ...... 
 * 
 * Es decir, el elemento mas grande de de la secuencia a, el elemento más chico de la secuencia b, y asi sucesivamente.
 */


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

	
	int Cases; cin >> Cases;

	while(Cases --){

		cin >> N;
	

		for (int i = 0; i < N; i++)
		cin >> Fred[i];
		
		int res = 0;
		int actual = 0;
		bool secu_creciente = false;
		for (int i = 0; i < N; i++) {
			if( secu_creciente? actual < Fred[i] :  actual > Fred[i])
				actual = Fred[i];
			else {
				res++;
				secu_creciente = (secu_creciente? false : true);
				actual = Fred[i];
			}
		}

		cout << res << "\n";

		
	}
}
