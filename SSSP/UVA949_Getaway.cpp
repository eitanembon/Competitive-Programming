
/**
 * Ejercicio: UVA 949 - Getaway
 * 
 * Autor: Eitan Embon 
 *  
 * Tiempo en UVA: 0.000s
 * 
 * Compilado con c++ 11
 */


#include <bits/stdc++.h>

using namespace std;
using City = vector<vector<unordered_set<int>>>;
using PosiblePos2Move = vector<vector<vector<pair<int, int>>>>;

constexpr int INF = numeric_limits<int>::max()/2;

// Direcciones posibles a moverse
vector<int> dirx = {0, 1, -1, 0};
vector<int> diry = {1, 0, 0, -1};

//devuelvo el priemer tiempo en el que una posicion esta libre el monitoreo a partir del tiempo t 
int first_free_monitoring_time(unordered_set<int>& monitorize_times, int t){
	
	while(monitorize_times.find(t) != monitorize_times.end()) t++;

	return t;
}

// Dijkstra 0-1
int dijkstra_0_1(City& city, PosiblePos2Move& pos2move){
	auto n = city.size(), m = city[0].size();
	vector<vector<bool>> visited(n, vector<bool>(m, false));
	vector<pair<uint, uint>> q[2];
	
	q[0].push_back({0, 0});
	
	int res = first_free_monitoring_time(city[0][0], 0);

	while(not visited[n-1][m-1]){
		if(q[0].empty()){
			res ++;
			swap(q[0], q[1]);
		}
		uint xc, yc; tie(xc,yc) = q[0].back(); // current position
		q[0].pop_back();
		if(visited[xc][yc]) continue;
		visited[xc][yc] = true;
		
		for(auto& npos : pos2move[xc][yc])
		if (not visited[npos.first][npos.second])
		{
			uint xn = npos.first, yn = npos.second; // next position

			// Si no puedo ir a la next pos, entonces, me quedo en la actual esperando
			if (city[xn][yn].find(res +1) != city[xn][yn].end()) {
				xn = xc, yn = yc;
				visited[xn][yn] = false;
			}
			q[1].push_back({xn, yn});
		}

	}
	return res;
}


/**
 * IDEA: 
 * Realizo un dijkstra 0-1. 
 */


int  main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
	cout.tie(0);

	int nv, nh, r, m;
	
	while (cin >> nv >> nh)
	{
		City city(nv, vector<unordered_set<int>>(nh));
		PosiblePos2Move pos2move(nv, vector<vector<pair<int, int>>>(nh));
		

		// Asigno a cada posicion las posibles direcciones a moverse
		
		for(int i = 0; i < nv; i++)
		for(int j = 0; j < nh; j++)
		for(int d = 0; d < 4; d++)
		if (i + dirx[d] >= 0 and i + dirx[d] < nv and j + diry[d] >= 0 and j + diry[d] < nh)
			pos2move[i][j].push_back({i + dirx[d], j + diry[d]});
		
			
			
		// Saco las direcciones que no pueden tomar cada posicion
		cin >> r;
		for (int i = 0; i< r; i++){
			int x1, x2, y1, y2;
			cin >> x1 >> y1 >> x2 >> y2;

			pos2move[x1][y1].erase(find(pos2move[x1][y1].begin(), pos2move[x1][y1].end(), make_pair(x2,y2))); // O(4)
		}
		
		// Cargo los tiempos de monitoreo del input
		
		cin >> m;
		for(int i = 0; i < m; i++){
			int x1,y1,t;
			cin >> t >> x1 >> y1;
			city[x1][y1].insert(t);
		}

		// Calculo las distancia desde 0,0 a nv-1, nh-1

		cout << dijkstra_0_1(city, pos2move) << "\n";

	}
}
