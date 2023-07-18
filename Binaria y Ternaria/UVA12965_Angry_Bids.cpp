
/**
 * Ejercicio: UVA 12965 - Angry Bids
 * 
 * Autor: Eitan Embon 
 *  
 * Tiempo en UVA: 0.220s
 * 
 * Compilado con c++ 11
 */


#include <bits/stdc++.h>


using namespace std;

long long Producers [10 * 10 * 10 * 10];
long long Consumers [10 * 10 * 10 * 10];
int P, C;



int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

	
	int Cases; cin >> Cases;

	while(Cases --){

		cin >> P >> C;
		

		for (int i = 0; i < P; i++)
		cin >> Producers[i];
		 for (int i = 0; i < C; i++)
		cin >> Consumers[i];
		

		sort(Producers, Producers + P);
		sort(Consumers, Consumers + C);


		// Busco la minimo precio de algun productor que me minimice la suma de los productores y consumidores enojados
		// Complejidad: P x C   <= 10**8 
		long long producer_prize = 0;
		int angry_consumers  = 0;
		int angry_producers = P;

		for (int producer = 0; producer < P; producer++) if( Producers[producer] >= producer_prize)
		{
			long long producer_prize_now = Producers[producer];
			
			int angry_producers_now = P - 1 - producer ;

			int angry_consumers_now = 0;
			for(int consumer = 0; consumer < C and Consumers[consumer] < producer_prize_now; consumer++) {
				angry_consumers_now++;
			}

			if(angry_consumers_now + angry_producers_now < angry_consumers + angry_producers ){
				angry_consumers = angry_consumers_now;
				angry_producers = angry_producers_now;
				producer_prize = producer_prize_now;
			}
		}
		
		cout << producer_prize << " " << (angry_consumers + angry_producers) << "\n";
		}
}
