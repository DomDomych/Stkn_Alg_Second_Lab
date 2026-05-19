#include "stop.h"
#include <iostream>
#include <string>

void StopList::addstop(std::string name, int coord_x, int coord_y, int time)
{
    Stop *new_stop = new Stop(name, coord_x, coord_y, time);

    if (end == nullptr)
    {
        end = new_stop;
        start = new_stop;
    }
    else
    {
        end->next_stop = new_stop;
        new_stop->prev_stop = end;
        end = new_stop;
    }
}
void StopList::Cycle(){
    
}
Stop *StopList::After_N(int n)
{
    Stop *current = start;
    while (n)
    {
        n--;
        current = current->next_stop;
    }
    return current;
}

int StopList::Time()
{
    int sum = 0;
    Stop *current = start;
    while (true)
    {
        if (current->next_stop == nullptr)
            break;
        sum += current->time;
        current = current->next_stop;
    }
    return sum;
}

void StopList::Forw_Route()
{
    Stop *current = start;
    while (current != nullptr)
    {
        std::cout << current->name << ' ';
        current = current->next_stop;
    }
    std::cout << '\n';
    return;
}
void StopList::Back_Route()
{
    Stop *current = end;
    while (current != nullptr)
    {
        std::cout << current->name << ' ';
        current = current->prev_stop;
    }
    std::cout << '\n';
    return;
}