#include <string>

class Stop{
    public:
      std::string name;
      int coord=0,time=0  ;
      Stop* next_stop = nullptr, *prev_stop = nullptr;
      Stop() = default;
      Stop(std::string name,int coord,int time,Stop* previous):name(name),coord(coord),time(time),prev_stop(previous){}
      Stop(std::string name,int coord,int time):name(name),coord(coord),time(time){}
};

class Stoplist{
    public:
      Stoplist() = default;
      void addstop(std::string name,int coord,int time){
        Stop* new_stop = new Stop(name,coord,time);
      }
};