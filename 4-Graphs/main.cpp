/* 
Gael Rodríguez Gómez A01639279
Emilio González Martínez A01640120

Este programa lee un archivo con ips y ataques
para formar un grafo y contabilizar los ataques de cada
red para detectar a posibles boot masters

* Compilacion:  
    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
    valgrind --leak-check=full ./main
* Ejecucion:
    ./main
*/

#include <iostream>
#include "Graph.h"
#include "maxHeap.h"

int main() {
  std::cout << "Actividad Integradora de Grafos\n\n";

  // Construye un grafo con el archivo
  Graph ipAttacks ("bitacoraGrafos.txt");
  ipAttacks.writeFile();

  
  //Construye el heap para obtener las ip de mayor grado
  int numIPs = ipAttacks.getNumNodes();
  maxHeap<IP> topIP(numIPs);
  topIP.readIPs("grados_ips.txt");
  topIP.Top5();
  
} 