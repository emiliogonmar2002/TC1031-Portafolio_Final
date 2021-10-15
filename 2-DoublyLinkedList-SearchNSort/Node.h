#ifndef NODE_H
#define NODE_H

template <class T>
class Node{

    public:
      T data;
      Node<T>* next;
      Node<T>* prev;
      Node();
      Node(T);
};

  //O(1)
  template<class T>
  Node<T>::Node(){
      data = 0;
      next = nullptr;
      prev = nullptr;
  }

  //O(1)
  template<class T>
  Node<T>::Node(T val){
      data = val;
      next = nullptr;
      prev = nullptr;
  }



#endif //NODE_H