#include <string>
#include <iostream>

class Stop{
    public:
      std::string name;
      int coord_x=0,time=0,coord_y=0  ;
      Stop* next_stop = nullptr, *prev_stop = nullptr;
      Stop() = default;
      Stop(std::string name,int coord_x,int coord_y,int time):name(name),coord_x(coord_x),coord_y(coord_y),time(time){}
};

class StopList{
    private:
      Stop* end = nullptr;
      Stop* start = nullptr;
    public:
      StopList() = default;

      void addstop(std::string name,int coord_x,int coord_y,int time);
      Stop* After_N(int n);
      int Time();
      void Forw_Route();
      void Back_Route();
      void Cycle();
      void ByTheTime(int time);
      void After_N_Extended(int n);
      ~StopList(){
        end->next_stop = nullptr;
        Stop* current = start;
        while(current != nullptr){
          Stop* next = current->next_stop;
          delete current;
          current = next;
        }
      }
      
};