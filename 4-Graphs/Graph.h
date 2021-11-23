#ifndef __GRAPH_H_
#define __GRAPH_H_
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>
#include "IP.h"

using std::vector;
using std::pair;

class Graph {
  private:
    int numNodes;
    int numEdges;
    // Lista de adyacencia (vector de vectores)
    vector<pair<IP, vector<int>>> adjList;
    void loadGraph(string path);
    void printAdjList();
    vector<IP> ipList;
    void heapSort();
    void heapify(int size, int i);
  public:
    Graph(string path);
    Graph();
    ~Graph();
    void printGraph();
    void addEdge(int v, int w);
    int binarySearch(long int key);
    void writeFile();
    int getNumNodes();
};


Graph::Graph(string path) {
  loadGraph(path);
}


Graph::~Graph() {
  adjList.clear();
}

int Graph::getNumNodes(){ return numNodes;}

void Graph::loadGraph(string path) {
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
  
  string nodes, edges, address, port;
  
  getline(file, nodes, ' ');
  getline(file, edges);
  numNodes = atoi(nodes.c_str());
  numEdges = atoi(edges.c_str());
  // Reservar memoria para la lista de adyacencia
  adjList.resize(numNodes+1);
  
  IP ip;
  int i = 1;
  //Almacena todas las ip
  while(!file.eof() && i <= numNodes){
    getline(file, address);
    ip = IP(address);
    ipList.push_back(ip);
    i++;      
  }
  // Ordena las ip
  heapSort();
  // Inserta las ip en el grafo
  for(i = 1; i <= numNodes; i++){
    vector<int> adjacencies = {};
    pair<IP, vector<int>> node = {ipList[i-1], adjacencies};
    adjList[i] = node;
  }

  i = 0;
  string origin, attacked, trash;
  int oriPos, attPos;
  long int originValue, attackedValue;
  
  while(!file.eof() && i < numEdges){
    getline(file, trash, ' ');
    getline(file, trash, ' ');
    getline(file, trash, ' ');
    getline(file, origin, ':');
    getline(file, trash, ' ');
    getline(file, attacked, ':');
    getline(file, trash);

    originValue = ip.setValue(origin);
    attackedValue = ip.setValue(attacked);
    oriPos = binarySearch(originValue);
    attPos = binarySearch(attackedValue);  
    addEdge(oriPos, attPos);
    i++;
  }
  
  file.close();  
}

// O(log n)
void Graph::heapify(int size, int i){
  int largest = i;
  int l = 2*i+1;
  int r = 2*i+2;

  if(l < size && ipList[l].getValue() > ipList[largest].getValue()){
    largest = l;
  }

  if(r < size && ipList[r].getValue() > ipList[largest].getValue()){
    largest = r;
  }

  if(largest != i){
    std::swap(ipList[i], ipList[largest]);
    heapify(size,largest);
  }
}

// O(n)
void Graph::heapSort(){
  int size = ipList.size();
  for(int i = size/2; i >= 0; i--){
    heapify(size,i);
  }

  for(int i = size-1; i>0; i--){
    std::swap(ipList[0], ipList[i]);
    heapify(i, 0);
  }
}

// O(E+V)
void Graph::printGraph() {
	std::cout << "Adjacency List" << std::endl;
	for (int i = 1; i <= numNodes; i++){
	  std::cout << "vertex " << i <<"  "<<adjList[i].first <<  ": ";
	  for (int j = 0; j < (int)adjList[i].second.size(); j ++){
		 std::cout << " " << adjList[i].second[j];
		}
	  std::cout << std::endl;
  }
}

// O(1)
void Graph::addEdge(int v, int e){
  // Agrega el ataque a la lista de adyacencias
  adjList[v].second.push_back(e);
  // Incrementa el grado de la IP
  adjList[v].first.increment();
}

//Binary Search
//O(log n)
int Graph::binarySearch(long int key){
  //int size = numNodes-1;
  int m;
  int l = 1;
  int h = numNodes;

  while (l <= h) {
    m = (h + l) / 2;
    if (adjList[m].first.getValue() == key){
      return m;
    }
    else if (adjList[m].first.getValue() < key){
      l = m + 1;
    } else {
      h = m - 1;
    }
  }
  return l;
}

// O(n)
void Graph::writeFile() {
  // Realizar registro de las fechas ordenadas
  std::ofstream file;
  file.open("grados_ips.txt",std::ios::out);
 
  for(int i = 1; i <= numNodes; i++)
    file << adjList[i].first << std::endl;
  
  
  file.close();
} 

#endif // __GRAPH_H_ 