/**
 * Ejercicio: UVA 1252 - Twenty Questions
 * 
 * Autor: Eitan Embon
 * 
 * Tiempo en UVA: 1.120s
 * 
 * Compilado en C++11
*/

#include <bits/stdc++.h>

using namespace std;
using BitMap = bitset<11>;

using Map = unordered_map<long long, unordered_map<long long, int>>;

constexpr int MAX_N = 128; 
constexpr int INF = numeric_limits<int>::max()/2;
vector<int> elements(MAX_N);
int m, n;



/**
 * Función Recursiva:
 * 	
f(preguntas, respuestas) = "Cant min de preguntas (esta seteado el bit k?) que faltan hacer para que un solo 
elemento coincida contestando (afirmativo o negativo). Habiendo preguntado las que estan en preguntas y 
pudiendo preguntar las que no estan en preguntas (preguntas que no se preguntaron aun) "

					
f(preguntas, respuestas) = { 		
	0		cant de elementos que satizfacen las respuestas a las preguntas hechas es 1 o 0
	 
	min {1 + max(f( preguntas inion {i}, respeustas union {i}),   f(preguntas union {i}, respuestas) ) }  
											tal que i pertenece a  [0 m) y i no pertenece a preguntas.
}

 */



Map mem;

int questions_recursive( int preguntas, int respuestas){ 
	
	if (mem.find(preguntas) != mem.end() and mem[preguntas].find(respuestas) != mem[preguntas].end()) 
	return mem[preguntas][respuestas];
	
	int satizfacen_respuestas = 0;
	
	for(auto i = 0; i < n; i ++) if((elements[i] & preguntas ) ==  respuestas) 
		satizfacen_respuestas ++;

	
	if(satizfacen_respuestas <= 1 ) {
		return mem[preguntas][respuestas] = 0;
	}

	int preguntas_faltantes = ~preguntas; 

	// Código para reemplazar el parámetro i
	int Min = INF;
	for(int preg_i = 0; preg_i < m; preg_i++) if (preguntas_faltantes & ( 1 << preg_i)){
		int sig_preguntas = preguntas | ( 1 << preg_i);
		int sig_respuestas_pos = respuestas | ( 1 << preg_i);
		int sig_respuestas_neg = respuestas;
		Min = min( Min, 1 + max (questions_recursive(sig_preguntas, sig_respuestas_pos), questions_recursive(sig_preguntas, sig_respuestas_neg)) );
	}

	return mem[preguntas][respuestas] = Min;

}


int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(0);


	
	while(cin >> m >> n){
		if(m == 0 and n == 0) break;

		mem.clear();

		for (auto i = 0; i < n; i++){
			string aux; 
			cin >> aux;
			elements[i] = (int)BitMap(aux).to_ulong();
			}
		
		cout << questions_recursive(0,0) << "\n";
	}
}
