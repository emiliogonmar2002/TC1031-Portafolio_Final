#ifndef REPORTE_H
#define REPORTE_H

#include<string>

class Reporte{
  public:
    Reporte();
    Reporte(std::string,std::string,std::string,std::string,std::string,std::string,std::string,int);

    std::string getMonth();
    std::string getDay();
    std::string getHour();
    std::string getMin();
    std::string getSeg();
    std::string getIP();
    std::string getFail();
    int getTime();

    std::string setMonth();
    std::string setDay();
    std::string setHour();
    std::string setMin();
    std::string setSeg();
    std::string setIP();
    std::string setFail();
    int setTime();

    friend std::ostream& operator <<(std::ostream &out, const Reporte &r){

      out<<r.month + " "+r.day + " "+r.hour+":"+r.min+":"+r.seg+" "+r.IP+" "+r.fail;

      return out;
    }

  private:
    std::string month;
    std::string day;
    std::string hour;
    std::string min;
    std::string seg;
    std::string IP;
    std::string fail;

    int time;

};

Reporte::Reporte(){
  month = "0";
  day = "0";
  hour = "0";
  min = "0";
  seg = "0";
  IP = "0";
  fail = "0";
  time = 0;
}

Reporte::Reporte(std::string month_,std::string day_,std::string hour_,std::string min_, std::string seg_,std::string IP_,std::string fail_,int time_){
  month = month_;
  day = day_;
  hour = hour_;
  min = min_;
  seg = seg_;
  IP = IP_;
  fail = fail_;
  time = time_;
}

int Reporte::getTime() {
  return time;
}

std::string Reporte::getMonth(){
  return month;
}

std::string Reporte::getDay(){
  return day;
}

std::string Reporte::getHour(){
  return hour;
}

std::string Reporte::getMin(){
  return min;
}

std::string Reporte::getSeg(){
  return seg;
}

std::string Reporte::getIP(){
  return IP;
}

std::string Reporte::getFail(){
  return fail;
}


#endif