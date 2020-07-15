#include <global.h>
#include <checkArgs.hpp>

uint64_t* ArregloParalelo = nullptr;
uint64_t* ArregloSerie = nullptr;
uint64_t* Arreglo = nullptr;
uint64_t Suma = 0;
std::vector<std::thread *> threads;
std::vector<std::thread *> threadsSuma;
std::mutex Cerrojo;
void Llenado(size_t Izquierda, size_t Derecha, size_t RandType){
	for(size_t i = Izquierda; i < Derecha; ++i){		
		switch(RandType){
			case 0: 
			ArregloSerie[i] = Arreglo[i]; 
				break;
			case 1:
				ArregloParalelo[i] = Arreglo[i];
				break;
		}
	}
}
void SumaParalela(uint32_t Izquierda, uint32_t Derecha){
	Cerrojo.lock();
	for(uint32_t i = Izquierda; i < Derecha; i++){
		Suma += ArregloParalelo[i];
	}
	Cerrojo.unlock();
}

int main(int argc, char** argv){
	
	uint64_t TamanioArreglo;
	uint32_t NumThreads;
	uint32_t LimiteInf;
	uint32_t LimiteSup;

	auto p = (std::shared_ptr<checkArgs>) new checkArgs(argc, argv);
	
	TamanioArreglo = p->getArgs().TamanioArreglo;
	NumThreads     = p->getArgs().NumThreads;
	LimiteInf	   = p->getArgs().LimiteInf;
	LimiteSup 	   = p->getArgs().LimiteSup;
	std::cout << "Conjunto de Numeros Del Arreglo: " << TamanioArreglo << std::endl;
	std::cout << "Numero de Hilos  : " << NumThreads     << std::endl;
	std::cout << "Limite Inferior Rango Aleatorio: "<< LimiteInf << std::endl;
	std::cout << "Limite Superior Rango Aleatorio: "<< LimiteSup << std::endl;

	Arreglo = new uint64_t[TamanioArreglo];
	std::srand(std::time(0)); 
	std::random_device device;
	std::mt19937 rng(device());
	std::uniform_int_distribution<> unif(LimiteInf, LimiteSup);
	for(uint32_t i = 0; i < TamanioArreglo; i++){
		Arreglo[i] = unif(rng);
	}
	ArregloSerie = new uint64_t[TamanioArreglo];
	Llenado(0,TamanioArreglo,0);	
	ArregloParalelo = new uint64_t[TamanioArreglo];
	for (size_t i= 0; i < NumThreads ; i++){
		threads.push_back(new std::thread(Llenado, i*(TamanioArreglo)/NumThreads, (i+1)*(TamanioArreglo)/NumThreads,1));
	}
	auto start = std::chrono::high_resolution_clock::now();
	for(auto &thLlenado : threads){
		thLlenado->join();
	}
	auto end     = std::chrono::high_resolution_clock::now(); 
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto TiempoLlenadoParalela = elapsed.count();

	for (size_t i = 0; i < NumThreads;i++){
		threadsSuma.push_back(new std::thread(SumaParalela, i*(TamanioArreglo)/NumThreads,(i+1)*(TamanioArreglo)/NumThreads));
	}
	start     = std::chrono::high_resolution_clock::now();
	for(auto &thS : threadsSuma){
		thS->join();
	}
	end     = std::chrono::high_resolution_clock::now(); 
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto TiempoSumaParalela = elapsed.count();
	auto tiempototal = TiempoLlenadoParalela + TiempoSumaParalela;
	std::cout << "Suma Total en Paralelo: " << Suma << std::endl;
	std::cout << "TiempoLLenadoParalelo:"  << TiempoLlenadoParalela << "[ms]" << std::endl;
	std::cout << "TiempoSumaParalelo:"  << TiempoSumaParalela << "[ms]" << std::endl;
	std::cout << "TiempoEjecucionTotal:"  << tiempototal << "[ms]" << std::endl;
	return(EXIT_SUCCESS);
}
