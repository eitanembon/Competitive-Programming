/**
 * Ejercicio: 11212 - Editing a Book
 * 
 * Autor: Eitan Embon
 * 
 * Tiempo en UVA: 0.030s
 * 
 * Compilado en C++11
*/


#include <iostream>
#include <vector>
#include <unordered_set>


using namespace std;
constexpr long long StringOrdered = 123456789;
constexpr long long pow[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

long long CutPaste(long long num, int i, int j, int k){
    
    long long cutted = ((num / pow[i]) % pow[j -i +1 ] ) ;
    int iShift = k;
    int jshift = i-1;
    int kshift = j -i +1 + iShift;
    long long shifted = (num/pow[iShift]) % pow[jshift - iShift +1] ;

    return num - cutted * pow[i] - shifted * pow[iShift] +cutted* pow[k] + shifted * pow[kshift];
}




int BT(int N, long long word){
    long long res = StringOrdered / pow[9 - N];
    if(word == (res)) return 0;
    int steps_left = 0;
    int steps_right = 0;
    unordered_set<long long> Curr_left, Next_left, Curr_right, Next_right;
    Curr_left.insert(word);
    Curr_right.insert(res);   
    
    while (true)
    {
        /*Avanzo en el Arbol Izqierdo*/
        

        //Aumento la cantidad de pasos antes de avanzar en el prox nivel del BFS
        // Pasos es sinonimo de nivel aca
        steps_left ++;
        //Proximo nivel del BFS
        for (auto OldNode_Left : Curr_left)
        for (int i = 0; i < N; i++)         
        for (int j = i; j < N; j++)
        for (int k = 0; k < i; k++){
            long long NewNode = CutPaste( OldNode_Left, i , j, k);
            
            // Chequeo si coincide con algun nodo del otro arbol, si coniceden Poda.
            if (Curr_right.find(NewNode) != Curr_right.end()) return steps_left + steps_right;
            
            // Si no hicieron el "meet" sigo con otro nodo hasta que completo el nivel
            Next_left.insert(NewNode); 
        }            
        //Actualizo el nivel actual
        Curr_left = Next_left;
        Next_left.clear();
        

        /*Avanzo en el Arbol Derecho*/
        
        //Aumento la cantidad de pasos antes de avanzar en el prox nivel del BFS
        // Pasos es sinonimo de nivel aca
        steps_right ++;
        //Proximo nivel del BFS
        for (auto OldNode_Right : Curr_right)
        for (int i = 0; i < N; i++)         
        for (int j = i; j < N; j++)
        for (int k = 0; k < i; k++) {
            long long NewNode = CutPaste( OldNode_Right, i , j, k);
             
            // Chequeo si coincide con algun nodo del otro arbol, si coniceden Poda.
            if (Curr_left.find(NewNode) != Curr_left.end()) return steps_right + steps_left;
            
            // Si no hicieron el "meet" sigo con otro nodo hasta que completo el nivel   
            Next_right.insert(NewNode); 
        }            
        //Actualizo el nivel actual
        Curr_right = Next_right;
        Next_right.clear();
    }
    return -1;
}



int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(0);

    long long word (0); 
    int N;

    int Case = 1;
    long long aux; 
    
    while (cin >> N){
        if (N == 0) break;
        for (int i = 0; i < N; i++)
        {
            cin >> aux;
            word = word * 10 + aux;
        }
        
        int res = BT (N, word);

        cout << "Case " << dec << Case << ": " << res << "\n";
        Case++;
        word = 0;
    }
}