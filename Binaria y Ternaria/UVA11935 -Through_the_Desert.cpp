/**
 * Ejercicio: UVA 11935 - Through the Desert
 * 
 * Autor: Eitan Embon
 * 
 * Tiempo en UVA: 0.000s
 * 
 * Compilado en C++11
*/

#include<bits/stdc++.h>

using namespace std;

constexpr int MIN_N = 1;
constexpr int MAX_N = 30;

enum events  {Fuel_Consumption = 1, Leak, Gas_Station, Mechanic, Goal};
unordered_map<string, events> Str2Events = {{"Fuel consumption", Fuel_Consumption}, {"Leak", Leak}, {"Gas station", Gas_Station},
									{"Mechanic", Mechanic}, {"Goal", Goal} };


struct EventInJourney
{
	long long kilometre;
	events event;
	long long consumtpion;
}Struct;

vector<EventInJourney> Journey(50);


//Decide if its possible to ended the journey with a tank of volume T 
bool succeed_the_journy(long long T){
	long long consumption_per_1KM = Journey[0].consumtpion * 10; 
	long long leaks = 0;
	long long distance_done = 0;
	long long Fuel = T ;
	if (Fuel < 0) return false;
	int actual = 1;
	Fuel -= (Journey[actual].kilometre - distance_done) * (leaks + consumption_per_1KM);
	while( Fuel >= 0 and Journey[actual].event != Goal )
	{
		auto actual_event = Journey[actual];
		if( actual_event.event == Fuel_Consumption) consumption_per_1KM = Journey[actual].consumtpion * 10;
		else if (actual_event.event == Leak) leaks += 1000; 
		else if (actual_event.event == Mechanic) leaks = 0;	
		if (actual_event.event == Gas_Station) Fuel = T;
		distance_done = actual_event.kilometre;
		
		actual++;
		Fuel -= (Journey[actual].kilometre - distance_done) * (leaks + consumption_per_1KM);
	
	}

	return Fuel >= 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);



	bool finish = false;
	while (true){
		//Recibo la entrada
		long long kilometre;
		string event;
		long long consumption;
		int nro_of_event = -1;
		while(true){
			nro_of_event++;
			cin >> kilometre;
			cin >> event; 
			if(Str2Events[event] == 0) {
				string aux; cin >> aux; event += " " + aux;	
			}
			events Event = Str2Events[event];
			if(Event == Fuel_Consumption) cin >> consumption;

			if(kilometre == 0 and Event == Fuel_Consumption and consumption == 0){finish = true; break;}
			Journey[nro_of_event] = {kilometre  ,Event, Event == Fuel_Consumption? consumption  : -1};

			if(Event == Goal) break;
		}

		if(finish) break;

		// Busqueda Binaria
		long long high = 1 << 24;
		long long low  = 0;

		while(low + 1 < high){
			long long mid = (high + low)/2;
			if(succeed_the_journy(mid))
				high = mid;
			else 
				low = mid ;	
		}
		cout << fixed << setprecision(3) << ((float)(high)/ 1000) << "\n";
		
	}

	
	}
