#include "stop.hpp"
#include "base64.hpp"

#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <iterator>

//Тесты для Time(), проверяем время маршрута

TEST(RouteTime, EmptyRouteTime)
{
    StopList route;

    EXPECT_EQ(route.Time(), 0);
}

TEST(RouteTime, ThreeStops102030)
{
    StopList route;
    route.addstop("First", 0, 0, 10);
    route.addstop("Second", 10, 0, 20);
    route.addstop("Third", 0, 10, 30);

    EXPECT_EQ(route.Time(), 60);
}

TEST(RouteTime, CycledRoute)
{
    StopList route;
    route.addstop("Gymnasium", 0, 0, 10);
    route.addstop("Church", 10, 10, 20);
    route.addstop("Market", 20, 20, 30);
    route.Cycle();

    EXPECT_EQ(route.Time(), 60);
}

//Тесты для After_N, где автобус окажется спустя N остановок

TEST(After_N_Stops,EmptyRoute)
{
    StopList route;

    EXPECT_EQ(route.After_N(100),nullptr);

}

TEST(After_N_Stops,NegativeNumber)
{
    StopList route;
    route.addstop("Gymnasium", 0, 0, 10);
    route.addstop("Church", 10, 10, 20);
    route.addstop("Market", 20, 20, 30);

    EXPECT_EQ(route.After_N(-5),nullptr);

}

TEST(After_N_Stops,CommonCase)
{
    StopList route;
    route.addstop("Gymnasium", 0, 0, 10);
    route.addstop("Church", 10, 10, 20);
    route.addstop("Market", 20, 20, 30);

    Stop* stop = route.After_N(1);
    ASSERT_NE(stop,nullptr);
    EXPECT_EQ(stop->name,"Church");
    EXPECT_EQ(stop->coord_x,10);
    EXPECT_EQ(stop->coord_y,10);
    EXPECT_EQ(stop->time,20);
}

TEST(After_N_Stops,Cycled)
{
    StopList route;
    route.addstop("Gymnasium", 0, 0, 10);
    route.addstop("Church", 10, 10, 20);
    route.addstop("Market", 20, 20, 30);
    route.Cycle();

    Stop* stop = route.After_N(2);

    ASSERT_NE(stop,nullptr);
    EXPECT_EQ(stop->name,"Market");
    EXPECT_EQ(stop->coord_x,20);
    EXPECT_EQ(stop->coord_y,20);
    EXPECT_EQ(stop->time,30);
    EXPECT_EQ(stop->next_stop->name,"Gymnasium");

}

//Тесты Функции ByTheTime
TEST(ByTheTimeTests,EmptyRoute)
{
    StopList route;

    std::ostringstream buffer;

    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    route.ByTheTime(100);

    std::cout.rdbuf(oldCout);

    std::string result = buffer.str();

    EXPECT_EQ(result,"Маршрут Пуст\n");
    
}

TEST(ByTheTimeTests,TooLittleTime)
{
    StopList route;
    route.addstop("Gymnasium", 0, 0, 10);
    route.addstop("Church", 10, 10, 20);
    route.addstop("Market", 20, 20, 30);
    route.addstop("Home",50,50,50);

    std::ostringstream buffer;

    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    route.ByTheTime(5);

    std::cout.rdbuf(oldCout);

    std::string result = buffer.str();

    EXPECT_EQ(result,"Gymnasium\nНе Доедет До Второй Остановки\n");
    
}

TEST(ByTheTimeTests,CommonCase)
{
    StopList route;
    route.addstop("Gymnasium", 0, 0, 10);
    route.addstop("Church", 10, 10, 20);
    route.addstop("Market", 20, 20, 30);
    route.addstop("Home",50,50,50);

    std::ostringstream buffer;

    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    route.ByTheTime(100);

    std::cout.rdbuf(oldCout);

    std::string result = buffer.str();

    EXPECT_NE(result.find("Gymnasium"),std::string::npos);
    EXPECT_NE(result.find("Church"),std::string::npos);
    EXPECT_NE(result.find("Market"),std::string::npos);
    EXPECT_NE(result.find("Home"),std::string::npos);


}

TEST(ByTheTimeTests,CycledRoute)
{
    StopList route;
    route.addstop("Gymnasium", 0, 0, 10);
    route.addstop("Church", 10, 10, 20);
    route.addstop("Market", 20, 20, 30);
    route.addstop("Home",50,50,50);
    route.Cycle();

    std::ostringstream buffer;

    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    route.ByTheTime(120);

    std::cout.rdbuf(oldCout);

    std::string result = buffer.str();

    std::istringstream input(result);
    std::vector<std::string> printed;

    std::string word;

    while(input>>word){
        printed.push_back(word);
    }

    std::vector<std::string> expected = {
    "Gymnasium", "Church", "Market", "Home", "Gymnasium", "Church"
    };

    EXPECT_EQ(printed,expected);

}

//Тесты для Stopping

TEST(StoppingTests,EmptyRoute)
{
    StopList route;

    std::ostringstream buffer;

    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    route.Stopping(10,10);

    std::cout.rdbuf(oldCout);

    std::string result = buffer.str();

    EXPECT_EQ(result,"Маршрут Пуст\n");
}

TEST(StoppingTests,InvalidTime){

    StopList route;
    route.addstop("Gymnasium", 0, 0, 10);
    route.addstop("Church", 10, 10, 20);
    route.addstop("Market", 20, 20, 30);
    route.addstop("Home",50,50,50);

    std::ostringstream buffer;

    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    route.Stopping(-10,10);

    std::cout.rdbuf(oldCout);

    std::string result = buffer.str();
    EXPECT_EQ(result,"Неверный Формат Времени\n");
}

TEST(StoppingTests, CommonCase)
{
    StopList route;

    route.addstop("Gymnasium", 0, 0, 10);
    route.addstop("Church", 10, 10, 20);
    route.addstop("Market", 20, 20, 30);

    std::ostringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    route.Stopping(10, 30);

    std::cout.rdbuf(oldCout);

    std::string result = buffer.str();

    std::string expected =
        "Gymnasium 10:30\n"
        "Church 10:40\n"
        "Market 11:00\n";

    EXPECT_EQ(result, expected);
}

TEST(StoppingTests, TimeGoesThroughMidnight)
{
    StopList route;

    route.addstop("Stankin", 0, 0, 20);
    route.addstop("Timka", 20, 20, 30);
    route.addstop("Novodachnaya", 0, 100, 10);

    std::ostringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    route.Stopping(23, 50);

    std::cout.rdbuf(oldCout);

    std::string result = buffer.str();

    std::string expected =
        "Stankin 23:50\n"
        "Timka 0:10\n"
        "Novodachnaya 0:40\n";

    EXPECT_EQ(result, expected);
}

TEST(StoppingTests,CycleOnlyOneTime)
{
    StopList route;

    route.addstop("Stankin", 0, 0, 20);
    route.addstop("Timka", 20, 20, 30);
    route.addstop("Novodachnaya", 0, 100, 10);
    route.Cycle();

    std::ostringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    route.Stopping(19, 40);

    std::cout.rdbuf(oldCout);

    std::string result = buffer.str();

    std::string expected =
        "Stankin 19:40\n"
        "Timka 20:00\n"
        "Novodachnaya 20:30\n";

    EXPECT_EQ(result, expected);
}

//Тесты на проверку кодировки Base64

TEST(Base64Tests,EncodeLine)
{
    std::string line = "ABC";

    EXPECT_EQ(Encode(line),"QUJD");
}

TEST(Base64Tests, ExportToFileBase64Test)
{
    StopList route;

    route.addstop("A", 0, 0, 10);
    route.addstop("B", 10, 0, 20);

    std::string filename = "test_base64.txt";

    route.Base64ExportToTheFile(filename);

    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();

    ASSERT_EQ(lines.size(), 2);

    EXPECT_EQ(lines[0], "QSAwIDAgMTA=");
    EXPECT_EQ(lines[1], "QiAxMCAwIDIw");

    std::remove(filename.c_str());
}

TEST(Base64Tests,EmptyRoute)
{
    StopList route;
    std::string filename = "emptyroute.txt";

    route.Base64ExportToTheFile(filename);
    
    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());

    std::string content(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

    file.close();
    EXPECT_EQ(content,"Маршрут Пуст\n");

    std::remove(filename.c_str());
}