#ifndef __RESUMEN_H_
#define __RESUMEN_H_
#include "IP.h"


using std::string;
using std::vector;

class Resumen{
  public:
    Resumen(string address, vector<IP> accesos, int n_accesos, int n_recibidos);
    Resumen();    
    void heapSort();
    friend std::ostream& operator<<(std::ostream & os,  const Resumen& resumen);
  private:
    string ip;
    vector<IP> adyacencias;
    int ataques;
    int recibidos;
    vector<string> strAdyacencias;
    void heapify(int size, int i);    
    
};


Resumen::Resumen(string address, vector<IP> accesos, int n_accesos, int n_recibidos){
  ip = address;
  adyacencias = accesos;  
  ataques = n_accesos;
  recibidos = n_recibidos;
}

Resumen::Resumen(){
  ip = "";
  adyacencias = {};
  ataques = 0;
  recibidos = 0;
}

// O(log n)
void Resumen::heapify(int size, int i){
  int largest = i;
  int l = 2*i+1;
  int r = 2*i+2;

  if(l < size && adyacencias[l] > adyacencias[largest]){
    largest = l;
  }

  if(r < size && adyacencias[r] > adyacencias[largest]){
    largest = r;
  }

  if(largest != i){
    std::swap(adyacencias[i], adyacencias[largest]);
    heapify(size,largest);
  }
}

// O(n)
void Resumen::heapSort(){
  int size = adyacencias.size();
  for(int i = size/2; i >= 0; i--){
    heapify(size,i);
  }

  for(int i = size-1; i>0; i--){
    std::swap(adyacencias[0], adyacencias[i]);
    heapify(i, 0);
  }

  for(int i = 0; i < adyacencias.size(); i++){
    strAdyacencias.push_back(adyacencias[i].getAddress());
  }
}


//O(1)
std::ostream& operator<< (std::ostream & os,  const Resumen& resumen){
  os << "Resumen de la direccion: " << resumen.ip << std::endl;
  os << "Numero de ataques hechos: " << resumen.ataques << std::endl;
  os << "Numero de ataques recibidos: " << resumen.recibidos << std::endl;
  os << "Lista de direcciones atacadas:" << std::endl;
  for(int i = 0; i < resumen.ataques; i++){
    os << "\t" << resumen.adyacencias[i] << std::endl;
  }
  return os;
}


#endif //Resumen_H