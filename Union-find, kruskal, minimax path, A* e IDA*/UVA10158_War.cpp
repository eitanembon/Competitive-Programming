
/**
 * Ejercicio: UVA 10158 - War
 * 
 * Autor: Eitan Embon 
 *  
 * Tiempo en UVA: 0.020s
 * 
 * Compilado con c++ 11
 */


#include <bits/stdc++.h>
using namespace std;


struct DSU{

    void init(int n){
        padre = rank = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }
	// Retorna el padre
    int unite(int u, int v){
        u = find(u), v = find(v);
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = u;
        rank[u] = max(rank[u],rank[v]) + 1;
		return u;
    }

    vector<int> padre;
    vector<int> rank;
};


struct WAR{

	WAR(int n){
		friends.init(2*n);
		enemy = vector<int>(n);
		for(int i = 0; i < n; i++)
			enemy[i] = i + n;
	}
	bool are_friends(int u, int v){
		return friends.find(u) == friends.find(v);
	}
	bool are_enemies(int u, int v){
		return friends.find(enemy[u]) == friends.find(v) or friends.find(enemy[v]) == friends.find(u);
	}
	void set_friends(int u, int v){
		if (are_enemies(u, v))
			cout << -1 << "\n";
		else{
			friends.unite(u, v);
			friends.unite(enemy[u], enemy[v]);
		}
	}
	void set_enemies(int u, int v){
		if (are_friends(u, v))
			cout << -1 << "\n";
		else{
			friends.unite(enemy[u], v);
			friends.unite(enemy[v], u);
		}
	}
	DSU friends;
	vector<int> enemy;
};

/**
 * IDEA:  Usar un DSU pero duplicando la cantidad de persosnas, una para amigos y otra para enemigos.
 * 		- Si A es amigo de B, entonces enemy[A] es amigo de enemy[B] (Es decir que A y B son enemigos de la misma persona)
 * 		- Si A es enemigo de B, entonces A es amigo de enemy[B] y B es amigo de enemy[B]
 * 
 * 		Ser amigos implica estar en la misma componente conexa en el DSU de amigos
 * 		Ser enemigos implica que se encuentran en la misma componente conexa del "enemy" (de uno con respecto al otro) en el DSU de amigos
 * 		
 */


int  main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
	cout.tie(0);


	int  N;

	cin >> N;
	
	WAR people(N);
	int c, i, j;
	while(cin >> c >> i >> j and c != 0){
		if (c == 1)
			people.set_friends(i, j);
		else if (c == 2)
			people.set_enemies(i, j);
		else if (c == 3)
			cout << people.are_friends(i, j) << "\n";
		else if (c == 4)
			cout << people.are_enemies(i, j) << "\n";
	}
}
