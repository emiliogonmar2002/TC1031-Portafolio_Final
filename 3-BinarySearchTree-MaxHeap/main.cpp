#include <iostream>
#include "Bitacora.h"
#include "MaxHeapIP.h"
#include "IP_class.h"

int main() {
  
  // Crear la bitácora que contiene los reportes ordenados por valor de IP
  Bitacora<Report> bitacora;
  bitacora.readFile("bitacoraHeap.txt");
  bitacora.heapSort();
  bitacora.writeFile();

  // Crear MaxHeap con las IP más accesadas y registrar las 5 primeras en un archivo
  MaxHeapIP<IP_class> MaxHeap_IPs(bitacora.getSize()+1);
  MaxHeap_IPs.readFile("bitacoraHeap_ord.txt");
  MaxHeap_IPs.writeFile();

  return 0;
}