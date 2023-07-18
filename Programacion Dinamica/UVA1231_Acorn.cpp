/**
 * Ejercicio: UVA 1231 - Acorn
 * 
 * Autor: Eitan Embon
 * 
 * Tiempo en UVA: 1.120s
 * 
 * Compilado en C++11
*/

#include <bits/stdc++.h>

using namespace std;

using Num = long long;
constexpr Num UNDEF = -1;
constexpr Num MINUS_INF = -numeric_limits<Num>::max()/2;
using Map = unordered_map<Num, Num> ;

int Cases_left;    
Num f;
Num T;
Num H;
        

/**
 * Funcion recursiva:
 * acorns(h, t) = Maxima cantidad de bellotas que puede obtener jayjay partiendo desde el arbol t en la altura h
 * 
 *              
 *               acorns(h, t){
 *                           0            h <= 0
 *                           
 *                           max(acorns(h-1, t), acorns(h-f, t_max(h-f)))  tq  t_max(h-f) = arbol t que maximiza acorns(h-f, t) 
 *
 *                      }
 */



Num acorns_itev( vector<Map>& forest){
    
    vector<vector<Num>> mem_acorn (H+1, vector<Num>(T, UNDEF)); // Me guardo acorns(h, t) = maxima cant de bellotas partinedo en una altura h y el arbol t
    vector<Num> max_tree (H+1, UNDEF); // Me guardo en max_tree[h] el arbol t que maximiza acorns(h, t). 

    for(int t = 0; t < T ; t++)
    {
        mem_acorn[0][t] = 0;
    }
    max_tree[0] = 0;
    
    for (int h = 1; h < H+1; h++)
    for(int t = 0; t < T ; t++)
    {   
         //  Si h no existe en el map, forest[t][h] devuelve 0;
        Num gotten_acorns = forest[t][h];
        Num option1 = gotten_acorns + mem_acorn[h-1][t]; 
        Num option2 = gotten_acorns + ((h-f < 0)? MINUS_INF : mem_acorn[h-f][max_tree[h-f]] );

        // Actualizo los mems
        Num res = max(option1,option2);
        mem_acorn[h][t] = res;

        if (max_tree[h] == UNDEF || res > mem_acorn[h][max_tree[h]]) max_tree[h] = t; 
    }   


    return mem_acorn[H][max_tree[H]];
}






int main(){

    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> Cases_left;

    while (Cases_left-- > 0)
    {             
        
        cin >> T >> H >> f;


        vector<Map> forest;
        for (Num i = 0; i < T; i++)
        {   
            Num j;
            cin >> j;
            Map tree(j); 
            while(j--){
                Num height;
                cin >> height;
                if(tree.find(height) == tree.end())
                tree.insert({height, 1});
                else tree[height]++;
            }
            forest.push_back(tree);
        }
        

        cout << acorns_itev(forest) << "\n";
        
        
    }
    

}