#ifndef __HASH_TABLE_H_
#define __HASH_TABLE_H_

#include <vector>
#include <stdexcept>
#include "HashNode.h"
#include "Graph.h"
#include "Resumen.h"

template<class K, class T>
class HashTable {
  private:
    std::vector<HashNode<K,T>> table;
    int size;
    int maxSize; // preferible un numero primo
    int colisiones;
  public:
    HashTable(int selectedMaxSize);
    int getHashIndex(K keyVal);
    int getSize();
    int getColisiones();
    void print();
    void add(K keyVal, T value);
    int find(K keyVal);
    T getDataAt(int index);
    void remove(K keyVal);
    void readGraph(Graph graph);
    void getIPSummary();
};

template<class K, class T>
HashTable<K, T>::HashTable(int selectedMaxSize) {
  maxSize = selectedMaxSize;
  size = 0;
  colisiones = 0;
  table = std::vector<HashNode<K,T>>(maxSize);
}

template<class K, class T>
int HashTable<K, T>::getHashIndex(K keyVal) {
  long int index = keyVal % maxSize;
  return index;
}

template<class K, class T>
int HashTable<K, T>::getSize() {
  return size;
}

template<class K, class T>
int HashTable<K, T>::getColisiones(){
  return colisiones;
}

// O(n)
template<class K, class T>
void HashTable<K,T>::print() {
  std::cout << "Content of the hash table: " << std::endl;
  for (int i = 0; i < maxSize; i++) {
    if (table.at(i).getStatus()==1) // Cell is used
      std::cout << "Cell: " << i << " Key: " << table.at(i).getKey() << ", Value: " << table.at(i).getData() << ", Overflow.size: " << table.at(i).getOverflowSize() << std::endl;
  }
}

// O(n)
template<class K, class T>
void HashTable<K,T>::add(K keyVal, T value) {
  if (size == maxSize) {
    throw std::out_of_range("Hash Table is full");
  }
  // Compute the index of the table using a key and a hash function
  int hashVal = getHashIndex(keyVal); 
  HashNode<K, T> node = table.at(hashVal);
  // The cell in the table is not taken
  if (node.getStatus() != 1) {
    node.setKey(keyVal);
    node.setData(value);
    table.at(hashVal) = node;
  }
  else { // The cell in the table is already taken
    // Find next free space using quadratic probing
    int i = 1;
    int currentHashVal = getHashIndex(hashVal + i * i);
    HashNode<K, T> currentNode = table.at(currentHashVal);
    while (currentNode.getStatus() == 1) {
      i++;
      currentHashVal = getHashIndex(hashVal + i * i);
      currentNode = table.at(currentHashVal);
    }

    colisiones = colisiones + i;

    currentNode.setKey(keyVal);
    currentNode.setData(value);
    node.addToOverflow(currentHashVal);
    table.at(currentHashVal) = currentNode;
    table.at(hashVal) = node;
  }
  size++;
}  

// O(n) worst
template<class K, class T>
int HashTable<K,T>::find(K keyVal) {
  int hashVal = getHashIndex(keyVal); 
  HashNode<K, T> node = table.at(hashVal);
  
  // Cell in the table is taken
  if (node.getStatus() == 1) {
    if (node.getKey() == keyVal) {
      return hashVal;
    }
    for (int i = 0; i < node.getOverflowSize(); i++) {
      int overflowIndex = node.getOverflowAt(i);
      if (table.at(overflowIndex).getKey() == keyVal) {
        return overflowIndex;
      }
    }
    return -1;
  }
  return -1;
}

//O(n)
template<class K, class T>
void HashTable<K,T>::readGraph(Graph graph){
  vector<pair<IP, vector<IP>>> lista = graph.getAdjList();

  for(int i = 1; i <= graph.getNumNodes(); i++){
    Resumen resumen(lista[i].first.getAddress(), lista[i].second, lista[i].first.getAttacks(), lista[i].first.getAttackedBy());
    add(lista[i].first.getValue(), resumen);
  }
}

//O(n log n)
template<class K, class T>
void HashTable<K,T>::getIPSummary(){
  std::cout<<"Ingrese la IP que quiere consultar en un formato como el siguiente \n '240.142.104.114'"<<std::endl;
  std::string addressRequired;
  std::cin>>addressRequired;

  IP ip(addressRequired);

  int index = find(ip.getValue());
  if(index == -1){
    std::cout<<"La IP solicitada no esta en el registro"<<std::endl;
    return;
  }
  
  HashNode<K, T> node = table[index];
  Resumen resumen = node.getData();
  resumen.heapSort();
  std::cout<<resumen<<std::endl;
}


#endif // __HASH_TABLE_H_