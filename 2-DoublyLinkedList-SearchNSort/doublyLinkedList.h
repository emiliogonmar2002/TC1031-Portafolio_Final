#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "Node.h"
#include "Reporte.h"
#include "Stack.h"
#include <fstream>
#include <algorithm>

template <class T>
class doublyLinkedList{
    private:
      Node<T>* head;
      int size;
      Node<T>* tail;
      
    public:
      doublyLinkedList();
      ~doublyLinkedList();
      int getSize();
      void addFirst(T value);
      void addLast(T value);
      void printList();
      void printListIndices(int indice1, int indice2);
      void writeList();
      void writeListIndices(int indice1, int indice2);
      T getData(int posicion);
      void clear();
      void readArchivo(std::string nombre);
      void swap (Node<T> *a, Node<T> *b );
      Node<T>* lastNode(Node<T> *root);
      Node<T>* partition(Node<T> *l, Node<T> *h);
      int binarySearch(int time_);
      void quickSortIterative();

      Node<T>* operator[](T index);
};

//O(1)
template<class T>
doublyLinkedList<T>::doublyLinkedList(){
    head = nullptr;
    size = 0;
    tail = nullptr;
}

//O(n)
template<class T>
doublyLinkedList<T>::~doublyLinkedList(){
    Node<T> *p, *q;
    p = head;
    while(p != nullptr){
        q = p->next;
        delete p;
        p = q;
    }
    head = nullptr;
    size = 0;
    tail = nullptr;
}

//O(1)
template<class T>
int doublyLinkedList<T>::getSize(){
    return size;
}

//O(1)
template<class T>
void doublyLinkedList<T>::addFirst(T value){
    Node<T> *ptr = new Node<T>(value);
    ptr->next = head;
    if(head == nullptr){
        tail = ptr;
    } else {
        head->prev = ptr;
    }
    head = ptr;
    size++;
}

//O(1)
template<class T>
void doublyLinkedList<T>::addLast(T value){
    if(head == nullptr){
        addFirst(value);
    } else{
        Node<T> *last = new Node<T>(value);
        tail->next = last;
        last->prev = tail;
        tail = last;
        size++;
    }
}
    
//O(n)
template<class T>
 void doublyLinkedList<T>::printList() {
    Node<T> *ptr = head;
    while (ptr != nullptr) {
        std::cout << ptr->data << std::endl;
        ptr = ptr->next;
    }
    std::cout << std::endl;
} 

//O(n)
template<class T>
 void doublyLinkedList<T>::printListIndices(int indice1, int indice2) {
    Node<T> *ptr = head;
    int c = 0;
    while (ptr != nullptr && c <= indice2) {
        if(c >= indice1 && c<=indice2){
          std::cout << ptr->data << std::endl;        
        }
      ptr = ptr->next;  
      c++;
    }
    std::cout << std::endl;
} 

//O(n)
template<class T>
 void doublyLinkedList<T>::writeList() {
    Node<T> *ptr = head;
    //Realizar registro de las fechas ordenadas
    std::ofstream archivo;
    archivo.open("bitacora_ord.txt",std::ios::out);
    while (ptr != nullptr) {
        archivo << ptr->data << "\n";
        ptr = ptr->next;
    }
    archivo.close();
} 

//O(n)
template<class T>
 void doublyLinkedList<T>::writeListIndices(int indice1, int indice2) {
    Node<T> *ptr = head;
    int c = 0;
    //Realizar registro de las fechas ordenadas
    std::ofstream archivo;
    archivo.open("resultado_busqueda.txt",std::ios::out);
    while (ptr != nullptr && c <= indice2) {
        if(c >= indice1 && c<=indice2){
          archivo << ptr->data << "\n";       
        }
      ptr = ptr->next;  
      c++;
    }
    archivo.close();
} 

//O(n)
template<class T>
T doublyLinkedList<T>::getData(int position) {
  Reporte vacio;
  if (position < 0 || position >= size) {
    std::cout << "Indice fuera de rango" << std::endl;
    return vacio;
  }
  else {
    if (position == 0)
      return head->data;
    Node<T> *p = head;
    int index = 0;
    while (p != nullptr) {
      if (index == position)
        return p->data;
      index++;
      p = p->next;
    }
    return vacio;
  }
}

//O(n)
template<class T>
void doublyLinkedList<T>::clear(){
    Node<T> *p, *q;
    p = head;
    while(p != nullptr){
        q = p->next;
        delete p;
        p = q;
    }
    head = nullptr;
    size = 0;
    tail = nullptr;  
}

//O(n)
template<class T>
void doublyLinkedList<T>::readArchivo(std::string nombre){
  
  std::ifstream archivo(nombre);

  //Manejo de excepciones al leer el archivo
  try{
    if(archivo.fail()){
      
      throw "Error al leer el archivo";
    }
  } catch(const char* msg){
    std::cerr<<msg<<std::endl;
  }
  
  std::string month,day,hour,IP,fail,min,sec;


  while(!archivo.eof()){
      getline(archivo, month, ' ');
      getline(archivo, day, ' ');
      getline(archivo, hour, ':');
      getline(archivo, min, ':');
      getline(archivo, sec, ' ');
      getline(archivo,IP,' ');
      getline(archivo, fail);

      addLast(Reporte(month, day, hour, min, sec, IP, fail));
  }

}


//-------------------------------------------------------
//Quick Sort

//O(1)
template<class T>
void doublyLinkedList<T>::swap(Node<T> *a, Node<T> *b )
{ 
  Reporte t = a->data; 
  a->data = b->data;
  b->data = t; 
}
 
//O(n)
template<class T>
Node<T>* doublyLinkedList<T>::lastNode(Node<T> *root)
{
    while (root && root->next)
        root = root->next;
    return root;
}

//O(n)
template<class T>
Node<T>* doublyLinkedList<T>::partition(Node<T> *l, Node<T> *h)
{
    //Pivot
    int x = h->data.convertTime();
 
    Node<T> *i = l->prev;
 
    for (Node<T> *j = l; j != h; j = j->next)
    {
        if (j->data.convertTime() <= x)
        {
            i = (i == NULL)? l : i->next;
 
            swap(i, j);
        }
    }
    i = (i == NULL)? l : i->next;
    swap(i, h);
    return i;
}

//O(n^2)
template<class T>
void doublyLinkedList<T>::quickSortIterative()
{

    Node<T> *l = head;
    Node<T> *h = tail;

    // Crear stack
    Stack<Node<T>*> stack;
 
    //Hacer push de valores iniciales
    stack.push(l);
    stack.push(h);
 
    //Quitar elementos del stack hasta que quede vacío
    while (stack.getNumElements() > 0) {
        h = stack.pop();
        l = stack.pop();
 
        //Poner pivote en su posicion correcta
        Node<T>* p = partition(l, h);

        //Push de elementos a la izquierda del pivote
        if (p->data.getTime() > l->data.getTime()) {
            stack.push(l);
            stack.push(p->prev);
        }
 
        //Push de elementos a la derecha del pivote
        if (p->data.getTime() < h->data.getTime()) {
            stack.push(p->next);
            stack.push(h);
        }
    }
}


//-------------------------------------------------------


//-------------------------------------------------------
//Binary Search

//O(log n)
template<class T>
int doublyLinkedList<T>::binarySearch(int time_){
  //Inicializamos limites
  int low=0, high=size-1;
  //Ciclo que recorrerá la lista ordenada
  while(low<=high){
    //Partición
    int m = (low+high)/2;
    //Comprobar si el dato es el buscado
    if(time_ == this->getData(m).getTime()){
      return m;
    }
    else if(time_ < this->getData(m).getTime()){
      high = m-1;
    }
    else{
      low = m+1;
    }
  }
  //Regresar si no se encuentra ninguno
  return -1;
}

//-------------------------------------------------------

#endif //DOUBLYLINKEDLIST_H