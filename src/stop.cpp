#include "stop.hpp"
#include "base64.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>


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

void StopList::Cycle()
{
    if(start==nullptr || end==nullptr){
        std::cout<<"Маршрут Пуст\n";
        return;
    }
    end->next_stop = start;
    start->prev_stop = end;
}

Stop *StopList::After_N(int n)
{
    if(start==nullptr || n<0){
        return nullptr;
    }

    Stop *current = start;
    while (n>0 && current!=nullptr)
    {
        current = current->next_stop;
        n--;
    }
    return current;
}

int StopList::Time()
{
    if(start==nullptr){
        return 0;
    }
    int sum = 0;
    Stop *current = start;
    do
    {
        sum += current->time;
        current = current->next_stop;
    } while (current != nullptr && current != start);
    return sum;
}

void StopList::Forw_Route()
{
    if(start==nullptr){
        std::cout<<"Маршрут Пуст\n";
        return;
    }
    Stop *current = start;
    do
    {
        std::cout << current->name << ' ';
        current = current->next_stop;
    } while (current != nullptr && current != start);
    std::cout << '\n';
    return;
}
void StopList::Back_Route()
{
    if(end==nullptr){
        std::cout<<"Маршрут Пуст\n";
        return;
    }
    Stop *current = end;
    do
    {
        std::cout << current->name << ' ';
        current = current->prev_stop;
    } while (current != nullptr && current != end);
    std::cout << '\n';
    return;
}

void StopList::ByTheTime(int time)
{
    if(start==nullptr){
        std::cout<<"Маршрут Пуст\n";
        return;
    }
    if (time < start->time)
    {
        std::cout << start->name << '\n';
        std::cout << "Не Уедет С Первой Остановки\n";
        return;
    }
    Stop *current = start;
    while (true)
    {
        if (current!=nullptr && time >= current->time)
        {
            std::cout << current->name << ' ';
            time -= current->time;
            current=current->next_stop;
        }
        else
        {
            std::cout << '\n';
            break;
        }
    }
}

void StopList::Stopping(int hour, int minute)
{
    if(start==nullptr){
        std::cout<<"Маршрут Пуст\n";
        return;
    }
    int now = hour * 60 + minute;
    Stop *current = start;

    do
    {
        int nhour = (now / 60) % 24;
        int nminute = now % 60;

        std::cout << current->name << ' '
                  << nhour << ':';

        if (nminute < 10) std::cout << '0';
        std::cout << nminute << '\n';

        now += current->time;
        current = current->next_stop;
    } while (current != nullptr && current != start);
}

void StopList::ExportToTheFile(std::string filename)
{
    std::ofstream file(filename);
    if(start==nullptr){
        file<<"Маршрут Пуст\n";
        return;
    }
    Stop *current = start;
    file << "Первой Остановкой Является " << '"' << start->name << '"\n';
    file << "Последней Остановкой Является " << '"' << end->name << '"\n';
    if (end->next_stop == start)
    {
        file << "Маршрут Является Кольцевым\n";
    }
    else
    {
        file << "Маршрут Не Является Кольцевым\n";
    }
    file << "Общее Время Маршрута В Одну Сторону:" << Time() << '\n\n';
    file << "Полный Список Остановок Со Времен Пути До Следующей Остановки:\n";
    int i = 0;
    do
    {
        file << i << ')' << current->name << '\n';
        i++;
        current = current->next_stop;
    } while (current != nullptr && current != start);
    file.close();
}

void StopList::PrintTable(std::ostream &out)
{
    if (start == nullptr)
    {
        out << "Маршрут Пуст\n";
        return;
    }
    out << std::string(59,'-')<<'\n';
    out << std::left
        << "| "
        << std::setw(20) << "Stop"
        << "| "
        << std::setw(10) << "X"
        << "| "
        << std::setw(10) << "Y"
        << "| "
        << std::setw(10) << "Time"
        << '|'
        << '\n';
    out<<std::string(59,'-')<<'\n';
    Stop* current = start;
    do{
        out << std::left
        << "| "
        << std::setw(20) << current->name
        << "| "
        << std::setw(10) << current->coord_x
        << "| "
        << std::setw(10) << current->coord_y
        << "| "
        << std::setw(10) << current->time
        << "|"
        << '\n';
        out<<std::string(59,'-')<<'\n';
        current = current->next_stop;
    }while(current != nullptr && current!=start);

}

void StopList::Base64ExportToTheFile(std::string filename){
    std::ofstream file(filename);
    Stop* current = start;
    if(current == nullptr){
        file<<"Маршрут Пуст\n";
        file.close();
        return;
    }
    do{
        std::string dom = create_line(current);
        std::string s = Encode(dom);
        file<<s<<'\n';
        current =  current->next_stop;
    }while(current!=start && current!=nullptr);
    file.close();
}
