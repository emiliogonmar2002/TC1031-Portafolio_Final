#ifndef MAXHEAP
#define MAXHEAP

#include <vector>
#include <fstream>
#include <algorithm>
#include "IP.h"

template<class T>
class maxHeap {
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
    maxHeap(int cantidad);
    ~maxHeap();
    bool isEmpty();
    int getSize();
    int getCapacity();
    void printPriority_queue();
    void push(T key);
    T pop();
    T top();
    void readIPs(std::string path);
    void Top5();
    void heapify(int size, int i);
    void sort();
};

//O(1)
template <class T> 
maxHeap<T>::maxHeap(int cantidad) {
  size = 0;
  maxSize = cantidad+1;
  data.resize(maxSize);
}

  //O(1)
template <class T> 
maxHeap<T>::~maxHeap() {
  data.clear();
}
  
//O(1)
template <class T> 
bool maxHeap<T>::isEmpty() {
  return (size <= 0);
}
  
  //O(1)
  template <class T> 
int maxHeap<T>::getSize() {
  return size;
}

  //O(1)
template <class T> 
int maxHeap<T>::getCapacity() {
  return maxSize;
}

//O(n)
template <class T> 
void maxHeap<T>::printPriority_queue() {
  for (int i=0; i < size; i++)
    std::cout << data[i] << std::endl;
}
  
//O(1)
template <class T> 
int maxHeap<T>::parent(int i) {
  return (i-1)/2; 
}

//O(1)
template <class T> 
int maxHeap<T>::left(int i) {
  return (2*i + 1); 
}

//O(1)
template <class T> 
int maxHeap<T>::right(int i) {
  return (2*i + 2);
}

//O(log n)
template <class T> 
void maxHeap<T>::push(T key) {
  if (size == maxSize) {
    std::cout << "Overflow: no se puede insertar la llave: " << key << std::endl;
    return;
  }
  // Insertamos la nueva llave al final del vector
  int i = size;
  data[i] = key;
  size++;
  // Reparar las propiedades del max heap si son violadas
  while (i != 0 && data[parent(i)] < data[i]) {
    std::swap(data[i], data[parent(i)]);
    i = parent(i);
  }
}

  
//O(1)
template <class T> 
T maxHeap<T>::top() {
  T result = IP();
  if (isEmpty()) {
      std::cout << "El MaxHeap está vacio" << std::endl;
      return result;
  }
  return data[0];
}

//O(log n)
template <class T>
T maxHeap<T>::pop(){
  //Verifica que el heap no esté vacío
  T out = IP();
  if (isEmpty()) {
    std::cout << "El MaxHeap está vacio" << std::endl;
    return out;
  }
  //Extrae el dato con prioridad
  out = data[0];
  size--;
  std::swap(data[0], data[size]);
  data[size] = IP();
  
  //Variables para reajustar el heap
  int smallest, l, r;
  bool swaped;
  int ref = 0;

  //Ciclo para reajustar el heap
  do{
    swaped = false;
    l = left(ref);
    r = right(ref);
    smallest = ref;
    
    if(data[smallest] < data[r] && r < size){
      smallest = r;
    }
    if(data[smallest] < data[l] && l < size){
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
template <class T>
void maxHeap<T>::readIPs(std::string path){
  std::ifstream file;
  //Reads file and catches exceptions
  try{
    file.open(path, std::ios::in);
    if(file.fail()){
        throw "Path error. The address or filename is incorrect\n";
    }
  } catch(char const* message){
    std::cerr<<message<<std::endl;
    exit(0);
  }

  std::string address, attacks;
  IP temp;
  while(!file.eof()){
    //Read data
    getline(file, address,' ');
    getline(file, attacks);
    if(address != "" && attacks!= "")
      push(IP(address, attacks));
  }
  file.close();
}

// O(1)
template <class T>
void maxHeap<T>::Top5(){
  std::ofstream file;
  // Opens file and catches exceptions
  try{
    file.open("mayores_grados_ips.txt",std::ios::out);
    if(file.fail()){
      throw "Path error. The address or filename is incorrect\n";
    }
  } catch(char const* message){
    std::cerr<<message<<std::endl;
    exit(0);
  }

  vector<IP> bootMasters;
  // Displays the top element and stores it in the file
  std::cout<< "\nDireccion      Grado" <<std::endl;
  for(int i = 0; i < 5; i++){
    T ref = pop();
    file << ref << std::endl;
    std::cout << ref << std::endl;
    bootMasters.push_back(ref);
  }
  file.close();
  
  std::cout<< "\nPotenciales boot master" << std::endl;
  for(int i = 0; i < 5; i++){
    if(bootMasters[i] == bootMasters[0])
      std::cout << bootMasters[i] << std::endl;
  }
}


#endif // __MAXHEAP_H_