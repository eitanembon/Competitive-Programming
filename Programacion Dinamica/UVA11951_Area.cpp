/**
 * Ejercicio: UVA 11951 - Area
 * 
 * Autor: Eitan Embon
 * 
 * Tiempo en UVA: 0.050s
 * 
 * Compilado en C++11
*/

#include <bits/stdc++.h>
using namespace std;



int compute_prize(int i_1, int i_2, int j_1,int j_2, vector<vector<int>>& District){
    int cuadrado_izquierdo = j_1-1 < 0? 0 : District[i_2][j_1-1];
    int cuadrado_arriba = i_1-1 < 0? 0 : District[i_1-1][j_2];
    int cuadrdado_interseccion_arriba_izquierda = (i_1 -1 < 0 || j_1 - 1 < 0)? 0 : District[i_1-1][j_1-1]; 
    int cuadrado_entero = District[i_2][j_2];
    return  cuadrado_entero - cuadrado_izquierdo - cuadrado_arriba + cuadrdado_interseccion_arriba_izquierda;
}

int main(){

    
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    int Case = 0;

    
    while (Case++ < T){

        int N;
        int M;
        int K;
        cin >> N >> M >> K;
        vector<vector<int>> District (N, vector<int>(M));

        for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            // Principio de inclusion/exclusion
            int cuadradoArriba = j-1 < 0? 0: District[i][j-1];
            int cuadradoIzquierda = i-1 < 0? 0 : District[i-1][j];
            int cuadradoDiagonal = i-1 <0 || j-1 <0 ? 0 : District[i-1][j-1];

            cin >> District[i][j];
            District[i][j] += cuadradoArriba + cuadradoIzquierda - cuadradoDiagonal; 
        }
        

        int max_area = 0;
        int prize_max_area = 0;
        for (int j_1 = 0; j_1 < M; j_1++)
        for (int j_2 = j_1; j_2 < M; j_2++)
        {
            // Sliding Windows
            int i_1 = 0;
            int i_2 = 0;
            while(i_2 < N)
            {   

                int new_prize_area = compute_prize(i_1, i_2, j_1, j_2, District);
                int new_area = (j_2 + 1 -j_1 ) * (i_2 + 1 - i_1); 
                if ( new_prize_area <= K ){
                    if((new_area >  max_area ) || (new_area == max_area && new_prize_area < prize_max_area)  )
                    {   
                        max_area = new_area;
                        prize_max_area = new_prize_area;
                    }
                    i_2++;
                }
                else i_1 < i_2? i_1++ : i_2++;
            }
            
        }
        
        cout << "Case #" << Case << ": " << max_area << " " << prize_max_area << "\n";

    }
}