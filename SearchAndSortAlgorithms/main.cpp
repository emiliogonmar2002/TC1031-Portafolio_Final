/* Banderas de compilación
g++ -std=c++17 main.cpp
./a.out
*/

//Librerías
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

#include "Reporte.h"


// Quick Sort

int partition(std::vector<Reporte> &registro, int l, int h){
    Reporte pivot = registro[h];
    int partition_I = l-1;
    Reporte temp;
    
    for(int j = l; j < h; j++){
        if(registro[j].getTime() < pivot.getTime()){
            partition_I++;

            temp = registro[partition_I];
            registro[partition_I] = registro[j];
            registro[j] = temp; 
        }
    }
    //Swaps pivot into its place
    temp = registro[partition_I+1];
    registro[partition_I+1] = registro[h];
    registro[h] = temp;

    return partition_I+1;
}

void quickSort(std::vector<Reporte> &registro, int l, int h){
    if(l < h){
        int partition_I = partition(registro, l, h);
        quickSort(registro, l, partition_I-1);
        quickSort(registro, partition_I+1, h);
    }
}

//----------------------------------


int convertTime(std::string month, std::string day, std::string hour, std::string min, std::string sec){
  
  std::vector<std::string> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  std::string num_month;

  for(int i = 0; i < months.size(); i++){
    if(months[i] == month){
      num_month = std::to_string(i);
    }
  }

  std::string time = num_month + day + hour + min + sec;

  //Retorna el string concatenado y convertido a entero

  return atoi(time.c_str());

}

//Binary Search
int binarySearch(std::vector<Reporte> registro, int fecha){
    int size = registro.size();
    int m;
    int l = 0;
    int h = size - 1;

    while (l <= h) {
        m = (h + l) / 2;
        if (registro[m].getTime() == fecha){
            return m;
        }
        else if (registro[m].getTime() < fecha){
            l = m + 1;
        } else {
            h = m - 1;
        }
    }
    return l;
}

//Leer el archivo, recibiendo el nombre del texto y retornando el vector con los reportes
std::vector<Reporte> readArchivo(std::string nombre){
  
  std::ifstream archivo(nombre);
  std::string month,day,hour,IP,fail,min,sec;
  std::vector<Reporte> registro;


  while(!archivo.eof()){
      getline(archivo, month, ' ');
      getline(archivo, day, ' ');
      getline(archivo, hour, ':');
      getline(archivo, min, ':');
      getline(archivo, sec, ' ');
      getline(archivo,IP,' ');
      getline(archivo, fail);
      int time = convertTime(month, day, hour, min, sec);

      registro.push_back(Reporte(month, day, hour, min, sec, IP, fail, time));
  }

  return registro;

}


int main() {
  //Declarar el vector de reportes
  std::vector<Reporte> registro = readArchivo("bitacora.txt");

  //Ordenar el vector
  quickSort(registro,0,registro.size()-1);

  //Realizar registro de las fechas ordenadas
  std::ofstream archivo;
  archivo.open("bitacora_ord.txt",std::ios::out);

  for(int i = 0; i < registro.size(); i++){
      archivo << registro[i] << std::endl;
  }

  //Inicializamos las variables
  std::string month1, day1, hour1, min1, seg1;
  std::string month2, day2, hour2, min2, seg2;
  int fecha1, fecha2;

  //Input fecha inicial
  std::cout << "Ingresa la fecha incial: " << std::endl;
  getline(std::cin, month1,' ');
  getline(std::cin, day1,' ');
  getline(std::cin, hour1,':');
  getline(std::cin, min1,':');
  getline(std::cin, seg1);
  fecha1 = convertTime(month1, day1, hour1, min1, seg1);

  //Input fecha final
  std::cout << "Ingresa la fecha final: " << std::endl;
  getline(std::cin, month2,' ');
  getline(std::cin, day2,' ');
  getline(std::cin, hour2,':');
  getline(std::cin, min2,':');
  getline(std::cin, seg2);
  fecha2 = convertTime(month2, day2, hour2, min2, seg2);

  //Busqueda del índice de ambas fechas en el vector
  int fecha_indice1, fecha_indice2;
  fecha_indice1 = binarySearch(registro, fecha1);
  fecha_indice2 = binarySearch(registro, fecha2);

  // std::cout<<fecha_indice1<<std::endl;
  // std::cout<<fecha_indice2<<std::endl; 

  //Mostrar los reportes en el rango indicado
  std::cout<<"-------------------------------------------------------"<<std::endl;
  std::cout<<"Registros desde: "<<fecha_indice1<<"; Hasta: "<<fecha_indice2<<std::endl;
  
  for(int i=fecha_indice1; i<=fecha_indice2; i++){
    std::cout<<"Registro [ "<< i <<" ]: "<<registro[i].getMonth()<<" "<<registro[i].getDay()<<" "<<registro[i].getHour()<<":"<<registro[i].getMin()<<":"<<registro[i].getSeg()<<" "<<registro[i].getIP()<<" "<<registro[i].getFail()<<std::endl;
  }

  std::cout<<"-------------------------------------------------------"<<std::endl;
  std::cout<<"Resultado: "<<fecha_indice2-fecha_indice1+1<<" registros."<<std::endl;
  
  return 0;
}