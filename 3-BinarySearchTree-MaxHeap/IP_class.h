#ifndef IP_CLASS_H
#define IP_CLASS_H

#include<string>
#include <iostream>

class IP_class{
  public:
    IP_class();
    IP_class(std::string,int);
    std::string getIP();
    std::string getFirst();
    std::string getSecond();
    std::string getThird();
    std::string getFourth();
    int getValue();
    int getCantidad();
    void setCantidad(int);
    void separarIP();
    long int convertIP();

    friend std::ostream& operator <<(std::ostream &out, const IP_class &r){
      out<<"IP: " + r.IP + " - Frecuency: " + std::to_string(r.cantidad);
      return out;
    }

  private:
    std::string IP;
    std::string first;
    std::string second;
    std::string third;
    std::string fourth;
    int value;
    int cantidad;
};


IP_class::IP_class(){
  IP = "";
  first = "";
  second = "";
  third = "";
  fourth = "";
  value = 0;
  cantidad = 0;
}

IP_class::IP_class(std::string IP_, int cantidad_){
  IP = IP_;
  first = "";
  second = "";
  third = "";
  fourth = "";
  value = convertIP();
  cantidad = cantidad_;
}

//Getters y Setters
std::string IP_class::getIP(){return IP;}
std::string IP_class::getFirst(){return first;}
std::string IP_class::getSecond(){return second;}
std::string IP_class::getThird(){return third;}
std::string IP_class::getFourth(){return fourth;}
int IP_class::getValue(){return value;}
int IP_class::getCantidad(){return cantidad;}
void IP_class::setCantidad(int cantidad_){cantidad = cantidad_;}

// Encontrar las diferentes partes de la IP
// O(n)
  void IP_class::separarIP(){
    int c = 1, init = 0, end = 0;
    while( end = IP.find(".", init), end >= 0 )
    {
      if(c == 1){
        first = IP.substr(init, end - init);
      }
      else if(c == 2){
        second = IP.substr(init, end - init);
      }
      else if(c == 3){
        third = IP.substr(init, end - init);
      }
      init = end + 1;
      c++;
    }
    fourth = IP.substr(init, end - init);
  }

// Convertir dirección IP a numero decimal
// O(nlogn)  
  long int IP_class::convertIP(){
    std::string first="", second="", third="", fourth="";
    int c=1;
    long int IP_value;

    int init = 0;
    int end = 0;
    while( end = IP.find(".", init), end >= 0 )
    {
      if(c == 1){
        first = IP.substr(init, end - init);
      }
      else if(c == 2){
        second = IP.substr(init, end - init);
      }
      else if(c == 3){
        third = IP.substr(init, end - init);
      }
      init = end + 1;
      c++;
    }
    fourth = IP.substr(init, end - init);


    IP_value = (atoi(first.c_str())*pow(256,3)) + (atoi(second.c_str()) * pow(256,2)) + (atoi(third.c_str())*pow(256,1)) + (atoi(fourth.c_str())*1);

    return IP_value;

  }

#endif