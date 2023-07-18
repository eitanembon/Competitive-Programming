/**
 * Ejercicio: UVA 10819 - Trouble of 13-Dots
 * 
 * Autor: Eitan Embon
 * 
 * Tiempo en UVA: 0.810s
 * 
 * Compilado en C++11
*/

#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

constexpr int UNDEF = -1;
constexpr int MINUS_INF = - numeric_limits<int>::max()/2;
uint m, n;


int favour(uint i, uint c,  vector<ii>& items, vector<vector<int>>& mem){
    if(c > m+200) return  MINUS_INF;
    if(i == n){
        if(c <= m) return 0;
        else if ( c <= (m + 200)  && c > 2000) return 0;
        else return MINUS_INF;
    } 
    
    if(mem[i][c] != UNDEF) return mem[i][c];

    
    int lo_agrego = items[i].second + favour(i+1, c + uint(items[i].first) , items, mem);

    int no_lo_agrego = favour(i+1, c, items, mem);

    return mem[i][c] = max(lo_agrego, no_lo_agrego);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    while(cin >> m >> n) {

        vector<ii> items;
        
        ii aux;
        for(uint i = 0; i < n; ++i) {
            cin >> aux.first >> aux.second;
            items.push_back(aux);
        }

       
        // Estructura de memorizacion.
        
        vector<vector<int>> mem (n, vector<int>(m+ 201, UNDEF));
        
        
        cout <<  favour(0, 0, items, mem) << '\n';
        
        
    }
}