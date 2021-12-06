/** 
* Ejemplo que implementa una Tabla Hash
* Esta emplea metodo de Dirección Abierta (Hashing Cerrado)
* con Muestreo Cuadrático para manejo de colisiones
*
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    valgrind --leak-check=full ./main
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -O3 -o main *.cpp 
* Ejecucion:
*    ./main
**/
#include <iostream>
#include "HashTable.h"


int main() {
  std::cout << "Actividad Integradora de Hash\n\n";

  // Construye un grafo con el archivo
  Graph ipAttacks ("bitacoraGrafos.txt");
  std::cout<<"Grafo hecho"<<std::endl;
  int tableSize = ipAttacks.getNumNodes();
  HashTable<long int, Resumen> ipHash(13381);
  ipHash.readGraph(ipAttacks);
  
  std::cout<<"Numero de colisiones: "<<ipHash.getColisiones()<<std::endl;
  ipHash.getIPSummary();
} 