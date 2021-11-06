#ifndef __BITACORA_H_
#define __BITACORA_H_

  #include<vector>
  #include<iostream>
  #include <fstream>
  #include "Report.h"

  template<class T>
  class Bitacora {
    private:
      // Elementos de la bitacora
      std::vector<T> data; 
      // tamaño actual del heap   
      int size;   

    public:
      Bitacora();
      ~Bitacora();
      bool isEmpty();
      int getSize();
      std::vector<T> getData();
      void printBitacora();
      void readFile(std::string name);
      void heapify(int n, int i);
      void heapSort();
      void writeFile();
  };

  template <class T> 
  Bitacora<T>::Bitacora() {
      std::cout << "--->Creando una Bitacora: " <<  this << std::endl;
      size = 0;
  }

  template <class T> 
  Bitacora<T>::~Bitacora() {
      std::cout << "--->Liberando memoria de la Bitacora: " <<  this << std::endl;
      data.clear();
  }
  
  // O(1)
  template <class T> 
  bool Bitacora<T>::isEmpty() {
    return (size <= 0);
  }

  // O(1)
  template <class T> 
  int Bitacora<T>::getSize() {
    return size;
  }
  

  // O(1)
  template <class T>
  std::vector<T> Bitacora<T>::getData(){
    return data;
  }

  // O(n)
  template <class T> 
  void Bitacora<T>::printBitacora() {
    for (int i=0; i < size; i++)
      std::cout << data[i] << " " << std::endl;
    std::cout << std::endl;
  }

  // O(n)
  //Realizar el registro de las IP previamente ordenadas, en un archivo.
  template<class T>
  void Bitacora<T>::readFile(std::string name){
    std::ifstream archivo(name);
    std::string month,day,hour,IP,puerto,fail,min,sec;

    while(!archivo.eof()){
        getline(archivo, month, ' ');
        getline(archivo, day, ' ');
        getline(archivo, hour, ':');
        getline(archivo, min, ':');
        getline(archivo, sec, ' ');
        getline(archivo,IP,':');
        getline(archivo,puerto,' ');
        getline(archivo, fail);

        data.push_back(Report(month, day, hour, min, sec, IP, puerto, fail));
    }
    size = data.size();
  }

  // O(nlogn)
  template<class T>
  void Bitacora<T>::heapify(int n, int i)
  {
      int largest = i; // Initialize largest as root
      int l = 2 * i + 1; // left = 2*i + 1
      int r = 2 * i + 2; // right = 2*i + 2
  
      // If left child is larger than root
      if (l < n && data[l].convertIP() > data[largest].convertIP())
          largest = l;
  
      // If right child is larger than largest so far
      if (r < n && data[r].convertIP() > data[largest].convertIP())
          largest = r;
  
      // If largest is not root
      if (largest != i) {
          std::swap(data[i], data[largest]);
  
          // Recursively heapify the affected sub-tree
          heapify(n, largest);
      }
  }

  // O(n)
  template<class T>
  void Bitacora<T>::heapSort()
  {
      // Build heap (rearrange array)
      for (int i = size / 2 - 1; i >= 0; i--)
          heapify(size, i);
  
      // One by one extract an element from heap
      for (int i = size - 1; i > 0; i--) {
          // Move current root to end
          std::swap(data[0], data[i]);
  
          // call max heapify on the reduced heap
          heapify(i, 0);
      }
  }


  // O(n)
  template<class T>
  void Bitacora<T>::writeFile() {
      //Realizar registro de las fechas ordenadas
      std::ofstream archivo;
      archivo.open("bitacoraHeap_ord.txt",std::ios::out);
      for(int i=0; i<size; i++) {
          archivo << data[i] << "\n";
      }
      archivo.close();
  } 

#endif // __Bitacora_H_