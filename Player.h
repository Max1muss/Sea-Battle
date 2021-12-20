#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Player
{
    int m_borderField[12][12]; // массив для ограничения игрового поля
    int m_ships{ 0 }; // количество целых короблей в этой переменной
    int m_playerField[12][12]; // массив для отслеживания местоположения кораблей
    string m_name; // имя игрока здесь
    char m_displayField[12][12]; // массив вывода проверенных ранее клеток

public:


    void set();
    void setName(string number);
    int placedShips();
    int generateShip();
    void printEmpty();
    bool checkAdjacent(int y, int x, char pos, int ship);
    bool placeShip(int y, int x, char pos, int ship);
    void printPlayerField();
    string getName();
    void display();
    void markAsDestroyed(int y, int x);
    bool isDestroyed(int y, int x);
    bool hitOrMiss(int y, int x);
    bool isAlreadyShot(int y, int x);
    void addShips();

    


};
