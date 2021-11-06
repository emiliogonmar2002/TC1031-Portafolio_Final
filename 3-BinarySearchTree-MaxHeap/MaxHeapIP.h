#ifndef __MAXHEAPIP_H_
#define __MAXHEAPIP_H_

  #include<vector>
  #include<iostream>
  #include <algorithm>
  #include "IP_class.h"
  #include "Report.h"

  template<class T>
  class MaxHeapIP {
    private:
      // contiene los elementos del heap
      std::vector<T> data; 
      // capacidad maxima del heap
      int maxSize;
      // tamaño actual del heap   
      int size;   

      int parent(int i);
      int left(int i);
      int right(int i);

    public:
      MaxHeapIP(int capacity);
      ~MaxHeapIP();
      bool isEmpty();
      int getSize();
      int getCapacity();
      void printMaxHeap();
      void push(T key);
      void readFile(std::string name);
      void writeFile();
      T pop();

  };

  template <class T> 
  MaxHeapIP<T>::MaxHeapIP(int capacity) {
      std::cout << "--->Creando un MaxHeapIP: " <<  this << std::endl;
      size = 0;
      maxSize = capacity;
      data.resize(maxSize);
  }

  template <class T> 
  MaxHeapIP<T>::~MaxHeapIP() {
      std::cout << "--->Liberando memoria del MaxHeapIP: " <<  this << std::endl;
      data.clear();
  }
  
  // O(1)
  template <class T> 
  bool MaxHeapIP<T>::isEmpty() {
    return (size <= 0);
  }

  // O(1)
  template <class T> 
  int MaxHeapIP<T>::getSize() {
    return size;
  }

  // O(1)
  template <class T> 
  int MaxHeapIP<T>::getCapacity() {
    return maxSize;
  }

  // O(n)
  template <class T> 
  void MaxHeapIP<T>::printMaxHeap() {
    for (int i=0; i < size; i++){
      std::cout << data[i] << " ";
    std::cout << std::endl;
    }
  }

  // O(1)
  template <class T> 
  int MaxHeapIP<T>::parent(int i) {
    return (i-1)/2; 
  }
  
  // O(1)
  template <class T> 
  int MaxHeapIP<T>::left(int i) {
    return (2*i + 1); 
  }

  // O(1)
  template <class T> 
  int MaxHeapIP<T>::right(int i) {
    return (2*i + 2);
  }

  // O(logn)
  template <class T>
  void MaxHeapIP<T>::push(T key) {
    if (size == maxSize) {
        std::cout << "Overflow: no se puede insertar la llave " << std::endl;
        return;
    }
    int i = size;
    data[i] = key;
    size++;
    while (i != 0 && data[parent(i)].getCantidad() < data[i].getCantidad()) {
       std::swap(data[i], data[parent(i)]);
       i = parent(i);
    }
  }

  template<class T>
  void MaxHeapIP<T>::readFile(std::string name){
    std::ifstream archivo(name);
    std::string month,day,hour,IP,fail,min,sec,puerto;

    getline(archivo, month, ' ');getline(archivo, day, ' ');getline(archivo, hour, ':');getline(archivo, min, ':');getline(archivo, sec, ' ');getline(archivo,IP,':');getline(archivo,puerto,' ');getline(archivo, fail, ' ');

    std::string IP_actual = IP;

    int c = 1;
    while(!archivo.eof()){
        getline(archivo, month, ' ');
        getline(archivo, day, ' ');
        getline(archivo, hour, ':');
        getline(archivo, min, ':');
        getline(archivo, sec, ' ');
        getline(archivo,IP,':');
        getline(archivo,puerto,' ');
        getline(archivo, fail, ' ');

      if(IP==IP_actual){
        c++;
      }
      else{
        push(IP_class(IP_actual,c));
        c = 1;
      }
      IP_actual = IP;  
    }

    size = data.size();
    maxSize = data.size();

  }


  //O(log n)
  template <class T>
  T MaxHeapIP<T>::pop(){
    // Heap no vacío
    T out = IP_class();
    if (isEmpty()) {
        std::cout << "El MaxHeap está vacio" << std::endl;
        return out;
    }

    // Dato con prioridad
    out = data[0];
    size--;
    std::swap(data[0], data[size]);
    data[size] = IP_class();

    // Variables para reajustar el heap
    int smallest, l, r;
    bool swaped;
    int ref = 0;

    // Reajustar el Heap
    do{
      swaped = false;
      l = left(ref);
      r = right(ref);
      smallest = ref;

      if(data[smallest].getCantidad() < data[r].getCantidad() && r < size){
        smallest = r; 
      }
      if(data[smallest].getCantidad() < data[l].getCantidad() && l < size){
        smallest = l;
      }
      if(smallest != ref){
        std::swap(data[smallest], data[ref]);
        swaped = true;
        ref = smallest;
      }
    } while(swaped);

    return out;
  }

  //O(n)
  template<class T>
  void MaxHeapIP<T>::writeFile() {
      //Realizar registro de las fechas ordenadas
      std::ofstream archivo;
      archivo.open("ips_con_mayor_acceso.txt",std::ios::out);
      std::cout<<"\n\n------IP sort and frecuency------\n\n";
      for(int i=0; i<5; i++) {
        IP_class s = pop();
        std::cout<< s <<"\n";
        archivo << s << "\n";
      }
      std::cout<<"\n\n";
      archivo.close();
  } 


#endif // __MAXHEAPIP_H_