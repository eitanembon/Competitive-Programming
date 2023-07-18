/**
 * Ejercicio: UVA 10385 - Duathlon
 * 
 * Autor: Eitan Embon
 * 
 * Tiempo en UVA: 0.000s
 * 
 * Compilado en C++11
*/

#include <bits/stdc++.h>

using namespace std;

constexpr double INF = numeric_limits<double>::max()/2;


double t;
int n;
vector<pair<double, double>> contestants(20);



double race_margin(double r, double k){
	double time_cheater = r * contestants[n-1].first + k * contestants[n-1].second;

	double best_time_others = INF;
	for (int i = 0; i < n-1; i++)
		best_time_others  = min(r * contestants[i].first + k * contestants[i].second, best_time_others);
	
	return best_time_others - time_cheater;
}


int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(0);


	
	
	while(cin >> t){
		cin >> n;

		for (auto i = 0; i < n; i++){
			double aux1, aux2; 
			cin >> aux1 >> aux2;
			contestants[i] = {3600/aux1 ,3600/aux2};
			}

	
	
		double right_r = t;
		double left_r = 0;

		while (fabs(right_r - left_r) > 1e-10)
		{
			auto mid_left = left_r + (right_r -left_r)/3;
			auto mid_right = right_r - (right_r - left_r)/3;

			if (race_margin(mid_left , t - mid_left) < race_margin(mid_right , t - mid_right) )
				left_r = mid_left;
			else
				right_r = mid_right;
		}
		
		auto res = race_margin(right_r , t - right_r);
		if (res <= - 0.005)
		cout << "The cheater cannot win.\n";
		else
		cout << "The cheater can win by " << fixed << setprecision(0) << fabs(res) << 
		" seconds with r = " << fixed << setprecision(2) << right_r << "km and k = " 
		<< t - right_r << "km.\n";
		
	}
}
