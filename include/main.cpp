#include "stop.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

int main(){
    StopList A;
    A.addstop("Domikovskaya",0,0,10);
    A.addstop("Stanok",10,10,5);
    std::ofstream file("test2.txt");
    A.PrintTable(file);
    file.close();
}
