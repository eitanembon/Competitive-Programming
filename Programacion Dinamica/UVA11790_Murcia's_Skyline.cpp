/**
 * Ejercicio: UVA 11790 - Murcia's Skyline
 * 
 * Autor: Eitan Embon
 * 
 * Tiempo en UVA: 0.080s
 * 
 * Compilado en C++11
*/

#include <bits/stdc++.h>
using namespace std;

using ii = pair<int, int>;

constexpr int UNDEF = -1;

int lis_resolve(int k, vector<int>& mem, vector<ii>& skylines){
    if(k == 0) return (skylines[0].second);
    if (mem[k] == UNDEF){
        int Max = skylines[k].second;
        for(int j=0 ; j < k; j++) if(skylines[j].first < skylines[k].first){
        Max =  max(skylines[k].second + lis_resolve(j, mem, skylines), Max);   
        } 
        mem[k] = Max;
    }
    return mem[k];
}

int lds_resolve(int k, vector<int>& mem, vector<ii>& skylines){
    if(k == 0) return skylines[0].second;
    if (mem[k] == UNDEF){
        int Max = skylines[k].second;
        for(int j=0 ; j < k; j++) if(skylines[j].first > skylines[k].first){
        Max =  max(skylines[k].second + lds_resolve(j, mem, skylines), Max);   
        } 
        mem[k] = Max;
    }
    return mem[k];
}


int lis(vector<int>& mem, vector<ii>& skylines, int n){
    int res = 0;
    for(int k = 0; k < n; k++)
        res = max(res, lis_resolve(k, mem, skylines));
    return res;
}


int lds(vector<int>& mem, vector<ii>& skylines, int n){
    int res = 0;
    for(int k = 0; k < n; k++)
        res = max(res, lds_resolve(k, mem, skylines));
    return res;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    uint cases;
    cin >> cases;
    uint curr_case = 0;
    while(curr_case++ < cases) {
        uint n;
        cin >> n;
        vector<ii> skylines(n);
        for(auto i = 0u; i < n; ++i) cin >> skylines[i].first ;
        for(auto i = 0u; i < n; ++i) cin >> skylines[i].second;
        
        
        vector<int> mem_lis (n, UNDEF);
        vector<int> mem_lds (n, UNDEF);
        


        int increasing = lis( mem_lis, skylines, n);
        int decreasing = lds( mem_lds, skylines, n);
        
        cout << "Case " << curr_case << ". ";
        if(increasing >= decreasing){
            cout << "Increasing (" << increasing << ").";
            cout << " Decreasing (" << decreasing << ").\n";
        }else{
            cout << "Decreasing (" << decreasing << ").";
            cout << " Increasing (" << increasing << ").\n";
        }
    }


    return 0;
}