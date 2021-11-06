#ifndef REPORT_H
#define REPORT_H

#include <cstdlib>
#include <vector>
#include<string>
#include <iostream>
#include <math.h>

class Report{
  public:
    Report();
    Report(std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);

    std::string getMonth();
    std::string getDay();
    std::string getHour();
    std::string getMin();
    std::string getSeg();
    std::string getIP();
    std::string getFail();
    int getTime();
    int getIP_value();

    std::string setMonth();
    std::string setDay();
    std::string setHour();
    std::string setMin();
    std::string setSeg();
    std::string setIP();
    std::string setFail();
    int setTime();
    int convertTime();
    int setIP_value();
    long int convertIP();

    friend std::ostream& operator <<(std::ostream &out, const Report &r){

      out<<r.month + " "+r.day + " "+r.hour+":"+r.min+":"+r.seg+" "+r.IP+":"+r.puerto+" "+r.fail;

      return out;
    }

  private:
    std::string month;
    std::string day;
    std::string hour;
    std::string min;
    std::string seg;
    std::string IP;
    std::string puerto;
    std::string fail;
    int time;
    int IP_value;

};

Report::Report(){
  month = "0";
  day = "0";
  hour = "0";
  min = "0";
  seg = "0";
  IP = "0";
  puerto = "0";
  fail = "0";
}

Report::Report(std::string month_,std::string day_,std::string hour_,std::string min_, std::string seg_,std::string IP_,std::string puerto_,std::string fail_){
  month = month_;
  day = day_;
  hour = hour_;
  min = min_;
  seg = seg_;
  IP = IP_;
  puerto = puerto_;
  fail = fail_;
}

int Report::getTime() {
  return time;
}

std::string Report::getMonth(){
  return month;
}

std::string Report::getDay(){
  return day;
}

std::string Report::getHour(){
  return hour;
}

std::string Report::getMin(){
  return min;
}

std::string Report::getSeg(){
  return seg;
}

std::string Report::getIP(){
  return IP;
}

std::string Report::getFail(){
  return fail;
}

//O(n)
int Report::convertTime(){
  
  std::vector<std::string> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  std::string num_month;

  for(int i = 0; i < months.size(); i++){
    if(months[i] == month){
      num_month = std::to_string(i);
    }
  }

  std::string time1 = num_month + day + hour + min + seg;
  time = atoi(time1.c_str());

  return time;
}

// O(nlogn)
long int Report::convertIP(){
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