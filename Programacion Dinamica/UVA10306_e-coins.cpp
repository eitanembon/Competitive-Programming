/**
 * Ejercicio: UVA 10306 - e-coins
 * 
 * Autor: Eitan Embon
 * 
 * Tiempo en UVA: 0.210s
 * 
 * Compilado en C++11
*/

#include <bits/stdc++.h>
using namespace std;

using Num = long long;
constexpr Num UNDEF = -1;
constexpr Num INF = numeric_limits<Num>::max()/2;


int Cases_left;    //n 
Num m;             //m
Num S;             //S



Num change (Num k, Num X, Num Y, vector<vector<vector<Num>>>& mem, vector<pair<Num, Num>>& e_coins_types){
    
    if ( X*X + Y*Y == S*S ) return 0;
    
    if (k == m || (X*X + Y*Y > S*S) ) return INF;
    

    auto x = e_coins_types[k].first;
    auto y = e_coins_types[k].second;
    auto i_bound = S / max(x, y);
    
    if(mem[k][X][Y] == UNDEF){
        Num res = change(k+1, X , Y, mem, e_coins_types); // No uso la moneda   
        for(auto i = 1 ; i <= i_bound; i++){   // Si uso la moneda
            res = min(res, change(k+1, X + i*x, Y+ i*y, mem, e_coins_types) + i);  
        }
        mem[k][X][Y] = res;
    }
    return mem[k][X][Y];
}



int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> Cases_left;

    while (Cases_left-- > 0)
    {
        cin >> m;
        cin >> S;
        vector<vector<vector<Num>>> mem(m +1, vector<vector<Num>>(S + 1, vector<Num> (S + 1, UNDEF)));
        vector<pair<Num, Num>> e_coins_types(m);

        for (auto i = 0; i < m; i++)
        {
            int x, y;
            cin >> x;
            cin >> y;
            e_coins_types[i]= {x,y};
        }
        Num res = change(0, 0, 0, mem, e_coins_types);
        res < INF?
            cout << res << "\n" : cout << "not possible\n"; 
    }
    

}