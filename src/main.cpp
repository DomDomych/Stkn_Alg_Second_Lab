#include "stop.hpp"

#include <iostream>
#include <fstream>

int main()
{
    StopList route;

    route.addstop("Gymnasium", 0, 0, 10);
    route.addstop("Church", 10, 10, 20);
    route.addstop("Market", 20, 20, 30);
    route.addstop("Home", 50, 50, 50);

    std::cout << "=== Прямой маршрут ===\n";
    route.Forw_Route();

    std::cout << "\n=== Обратный маршрут ===\n";
    route.Back_Route();

    std::cout << "\n=== Общее время маршрута ===\n";
    std::cout << route.Time() << " минут\n";

    std::cout << "\n=== Где будет автобус через N остановок ===\n";
    int n = 2;
    Stop* stop = route.After_N(n);

    if (stop != nullptr)
    {
        std::cout << "Через " << n << " остановки автобус будет на остановке: "
                  << stop->name << '\n';
    }
    else
    {
        std::cout << "Остановка через " << n << " переходов не найдена\n";
    }

    std::cout << "\n=== Остановки, до которых автобус доедет за 100 минут ===\n";
    route.ByTheTime(100);

    std::cout << "\n=== Время прибытия при старте в 10:30 ===\n";
    route.Stopping(10, 30);

    std::cout << "\n=== Сохранение таблицы маршрута ===\n";
    std::ofstream tableFile("route_table.txt");
    route.PrintTable(tableFile);
    tableFile.close();
    std::cout << "Файл route_table.txt создан\n";

    std::cout << "\n=== Сохранение подробного отчета ===\n";
    route.ExportToTheFile("route_report.txt");
    std::cout << "Файл route_report.txt создан\n";

    std::cout << "\n=== Сохранение маршрута в Base64 ===\n";
    route.Base64ExportToTheFile("route_base64.txt");
    std::cout << "Файл route_base64.txt создан\n";

    std::cout << "\n=== Кольцевой маршрут ===\n";
    route.Cycle();

    Stop* cycleStop = route.After_N(5);

    if (cycleStop != nullptr)
    {
        std::cout << "Через 5 остановок в кольцевом маршруте автобус будет на: "
                  << cycleStop->name << '\n';
    }

    std::cout << "\n=== Работа завершена ===\n";

    return 0;
}