#ifndef IP_H
#define IP_H
#include <string>
#include <iostream>
#include <cmath>
#include <vector>


using std::string;
using std::vector;

class IP{
  private:
    std::string address;
    int attacks;
    int attacked_by;
    long int value;
  public:
    long int setValue(string address_);
    IP(string address_);
    IP(string address_, string attacks_);
    IP();
    string getAddress() const;
    long int getValue();
    int getAttacks();
    int getAttackedBy();
    bool operator<(const IP& other);
    bool operator>(const IP& other);
    bool operator ==(const IP& other);
    friend std::ostream& operator<<(std::ostream & os, const IP& ip);
    void increment();
    void attack();
    
    
};

//O(1)
IP::IP(){
  address = "";
  attacks = 0;
  value = 0;
  attacked_by = 0;
}

//O(1)
IP::IP(string address_){
  address = address_;
  attacks = 0;
  value = setValue(address);
  attacked_by = 0;
}


IP::IP(string address_, string attacks_){
  address = address_;
  attacks = atoi(attacks_.c_str());
}

string IP::getAddress() const {return address;}

int IP::getAttacks(){ return attacks;}

int IP::getAttackedBy(){return attacked_by;}

//O(1)
void IP::increment(){
  attacks++;
}

//O(1)
void IP::attack(){
  attacked_by++;
}

//O(1)
//Turns address into decimal value
long int IP::setValue(string address_){
  string octet;
  int power = 3;
  long int ipValue=0;
  for(char c : address_){
    if (c == '.'){
      ipValue += atoi(octet.c_str()) * std::pow(256, power);
      power--;
      octet = "";    
    } else {
      octet += c;
    }
  }
  ipValue += atoi(octet.c_str()) * std::pow(256, power);
  return ipValue;
}

// O(1)
long int IP::getValue(){
  return value;
}

//O(1)
bool IP::operator<(const IP& other){
  bool result = (value < other.value) ? true : false;
  return result;
}

//O(1)
bool IP::operator>(const IP& other){
  bool result = (value > other.value) ? true : false;
  return result;
}

//O(1)
bool IP::operator ==(const IP& other){
  bool result = (value == other.value) ? true: false;
  return result;
}

//O(1)
std::ostream& operator<< (std::ostream & os, const IP& ip){
  os << ip.address;
  return os;
}

#endif //IP_H