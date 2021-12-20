#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Player
{
    int m_borderField[12][12]; // ������ ��� ����������� �������� ����
    int m_ships{ 0 }; // ���������� ����� �������� � ���� ����������
    int m_playerField[12][12]; // ������ ��� ������������ �������������� ��������
    string m_name; // ��� ������ �����
    char m_displayField[12][12]; // ������ ������ ����������� ����� ������

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
