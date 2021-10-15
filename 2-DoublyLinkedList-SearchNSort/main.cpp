/*
Emilio González Martínez A01640120
Tecnológico de Monterrey
Act 2.3 - Actividad Integral estructura de datos lineales (Evidencia Competencia)
*/

#include <iostream>
#include "doublyLinkedList.h"
#include "Reporte.h"


int main() {

  //Test01
  /*fecha 1: Jun 01 00:22:36
  fecha 2: Jun 01 08:23:57

  Resultado: 45 Registros*/

  /*Test02
  fecha 1: Oct 26 13:37:41
  fecha 2: Oct 30 23:48:41

  Resultado: 474 Registros*/

  /*Test03
  fecha 1: Oct 20 23:45:19
  fecha 2: Oct 21 00:29:14

  Resultado: 3 Registros*/


  //Declarar el vector de reportes
  doublyLinkedList<Reporte> registro;
  registro.readArchivo("bitacora.txt");

  //Ordenar el vector
  registro.quickSortIterative();

  //Realizar registro de las fechas ordenadas 
  registro.writeList();

  //Inicializamos las variables
  std::string month1, day1, hour1, min1, seg1;
  std::string month2, day2, hour2, min2, seg2;
  int fecha1, fecha2;

  //Input fecha inicial
  std::cout << "Ingresa la fecha incial en el formato (Oct 09 06:41:52): " << std::endl;
  getline(std::cin, month1,' ');
  getline(std::cin, day1,' ');
  getline(std::cin, hour1,':');
  getline(std::cin, min1,':');
  getline(std::cin, seg1);
  Reporte reporte1(month1,day1,hour1,min1,seg1,"","");
  reporte1.convertTime();

  fecha1 = reporte1.getTime();
  
  //Input fecha final
  std::cout << "Ingresa la fecha final en el formato (Oct 09 06:41:52): " << std::endl;
  getline(std::cin, month1,' ');
  getline(std::cin, day1,' ');
  getline(std::cin, hour1,':');
  getline(std::cin, min1,':');
  getline(std::cin, seg1);
  Reporte reporte2(month1,day1,hour1,min1,seg1,"","");
  reporte2.convertTime();

  fecha2 = reporte2.getTime();

  //Busqueda del índice de ambas fechas en el vector
  int fecha_indice1, fecha_indice2;
  fecha_indice1 = registro.binarySearch(fecha1);
  fecha_indice2 = registro.binarySearch(fecha2);

  //Mostrar los reportes en el rango indicado
  std::cout<<"-------------------------------------------------------"<<std::endl;
  std::cout<<"Registros desde: "<<fecha_indice1<<"; Hasta: "<<fecha_indice2<<std::endl;
  
  registro.printListIndices(fecha_indice1,fecha_indice2);

  std::cout<<"-------------------------------------------------------"<<std::endl;
  std::cout<<"Resultado: "<<fecha_indice2-fecha_indice1+1<<" registros."<<std::endl;
  
  //Escribir el archivo con el registro deseado
  registro.writeListIndices(fecha_indice1,fecha_indice2);

  return 0;
}