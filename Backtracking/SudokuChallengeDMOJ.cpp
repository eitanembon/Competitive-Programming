
/**
 * Ejercicio: Sudoku Challenge DMOJ
 * 
 * Autor: Eitan Embon
 * 
 * Tiempo en DMOJ:  0,942s
 * 
 * Compilado en C++11
*/

#include <bits/stdc++.h>

using namespace std;

using MapBit = bitset<10>;


struct UsedPos
{
    int i;
    int j;
    MapBit* col;
    MapBit* row;
    MapBit* square;
};


class Compare
{
public:
    bool operator() (UsedPos l, UsedPos r)
    {
        return (l.row->count() + l.col->count() + l.square->count()) <
               (r.row->count() + r.col->count() + r.square->count());
    }
}comparer;



bool BT(int p, vector<UsedPos>& orderToFill,  vector<vector<int>>& Sudoku){
    
    if(p == int(orderToFill.size())){
        return true;
    }
    
    auto iter = max_element(orderToFill.begin(), orderToFill.end() - p, comparer); // O(n^2)
    iter_swap(iter, orderToFill.end() - p - 1);
    auto pos = orderToFill[orderToFill.size() - p - 1];
    bool aux = false;
    for(int k=1; k<=9 && !aux ;k++) 
    if(!pos.row->test(k) && !pos.col->test(k) && !pos.square->test(k)){
        Sudoku[pos.i][pos.j]=k;
        pos.row->set(k);
        pos.col->set(k);
        pos.square->set(k);
        aux = BT(p+1, orderToFill, Sudoku);
        pos.row->set(k,false);
        pos.col->set(k,false);
        pos.square->set(k, false);   
    }
    
	return aux;
}



int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N = 9;
    int sqr_n = 3;

    vector<MapBit> cols (N, MapBit(0));
    vector<MapBit> rows (N, MapBit(0));
    vector<vector<MapBit>> squares (sqr_n, vector<MapBit> ( sqr_n, MapBit(0)));
    vector<vector<int>> Sudoku (N, vector<int>(N,0));
    vector<UsedPos> PosToFill = {}; 
    string aux;
    
    for (int i = 0; i < N; i++){
        if(!(cin >> aux)) return 0;
        for (int j = 0; j < N; j++)
        {   
            if(aux[j] != '.'){
                int value = int(aux[j]) - 48;
                rows[i].set(value);
                cols[j].set(value);
                squares[i/sqr_n][j/sqr_n].set(value);
                Sudoku[i][j] = value;
            } 
            else
                PosToFill.push_back({i,j, &rows[i], &cols[j], &squares[i/sqr_n][j/sqr_n]});
        }
    }
      
    if(BT(0, PosToFill, Sudoku))
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++)
        {    
            cout << Sudoku[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}