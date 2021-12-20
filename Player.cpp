#include "Player.h"


    void Player::set() //�������������� ������� ����
    {
        for (int row = 0; row < 12; ++row)
        {
            for (int column = 0; column < 12; ++column)
            {
                if (row == 0 || row == 11 || column == 0 || column == 11)
                    m_borderField[row][column] = 0;
                else
                    m_borderField[row][column] = 1;
            }
        }

        for (int row = 0; row < 12; ++row)
        {
            for (int column = 0; column < 12; ++column)
            {
                m_playerField[row][column] = 0;
            }
        }

        for (int row = 0; row < 12; ++row)
        {
            for (int column = 0; column < 12; ++column)
            {
                m_displayField[row][column] = ' ';
            }
        }
    }

    void Player::setName(std::string number) // ����������� ��� ������
    {
        cout << "Enter " << number << " player's name: ";
        cin >> m_name;
    }

    int Player::placedShips() // ���������� ���������� ����� ��������
    {
        return m_ships;
    }

    void Player::addShips() // ��������� �������
    {
        ++m_ships;
    }

    int Player::generateShip() // ��������� ���������� ����� ��� ���������� �������
    {
        if (m_ships < 1) { return 4; }
        if (m_ships < 3) { return 3; }
        if (m_ships < 6) { return 2; }
        
        return 1;
    }

    void Player::printEmpty() // ����� ������� ���� � ������ ����
    {
        cout << "\n\n\n\n\n\n\n\n                                                A B C D E F G H I J\n\n                                            1  | | | | | | | | | | |\n"
            << "                                            2  | | | | | | | | | | |\n                                            3  | | | | | | | | | | |\n"
            << "                                            4  | | | | | | | | | | |\n                                            5  | | | | | | | | | | |\n"
            << "                                            6  | | | | | | | | | | |\n                                            7  | | | | | | | | | | |\n"
            << "                                            8  | | | | | | | | | | |\n                                            9  | | | | | | | | | | |\n"
            << "                                           10  | | | | | | | | | | |\n";
    }

    bool Player::checkAdjacent(int y, int x, char pos, int ship) // �������� �� ������������� �� ������� � ������ 
    {
        if (pos == 'h')
        {
            for (int count = 0; count < ship; ++count)
            {
                for (int it = 0; it < 3; ++it)
                {
                    for (int i = 0; i < 3; ++i)
                        if (m_playerField[(y + 1) - i][(x + 1) - it] != 0)
                            return false;
                }
                ++x;
            }
        }
        else if (pos == 'v')
        {
            for (int count = 0; count < ship; ++count)
            {
                for (int it = 0; it < 3; ++it)
                {
                    for (int i = 0; i < 3; ++i)
                        if (m_playerField[(y + 1) - i][(x + 1) - it] != 0)
                            return false;
                }
                ++y;
            }
        }

        return true;
    }

    bool Player::placeShip(int y, int x, char pos, int ship) // ������������� �������
    {
        if (!checkAdjacent(y, x, pos, ship)) // �������� ������� ������������ ��� ������� 
            return false;

        if (pos == 'h')
        {
            for (int i = 0; i < ship; ++i)
            {
                if (m_borderField[y][x + i] == 0)
                    return false;
            }

            for (int i = 0; i < ship; ++i)
                m_playerField[y][x + i] = 1;
            
        }
        else if (pos == 'v')
        {
            for (int i = 0; i < ship; ++i)
            {
                if (m_borderField[y + i][x] == 0)
                    return false;
            }


            for (int i = 0; i < ship; ++i)
                m_playerField[y + i][x] = 1;
        }

        return true;
    }

    void Player::printPlayerField() // ����� �������� ���� 
    {
        cout << "\n\n\n\n\n\n\n\n                                               A B C D E F G H I J\n";
        for (int row = 0; row < 12; ++row)
        {
            if (row == 0 || row == 11);
            else if (row == 10)
                cout << "                                           " << row << " ";
            else
                cout << "                                           " << row << "  ";

            for (int column = 0; column < 12; ++column)
            {
                if (row == 0 || row == 11 || column == 0 || column == 11);
                else
                {
                    if (m_playerField[row][column] == 0)
                        cout << "|" << " ";
                    else
                        cout << "|" << m_playerField[row][column];
                }
            }

            if (row == 0 || row == 11);
            else
                cout << "|\n";
        }
    }

    std::string Player::getName() // ������� ����� ������
    {
        return m_name;
    }

    void Player::display() // ����� ���� �������� ������
    {
        cout << "\n\n\n\n\n\n\n\n\n\n\n                                               A B C D E F G H I J\n";
        for (int row = 0; row < 12; ++row)
        {
            if (row == 0 || row == 11);
            else if (row == 10)
                cout << "                                           " << row << " ";
            else
                cout << "                                           " << row << "  ";

            for (int column = 0; column < 12; ++column)
            {
                if (row == 0 || row == 11 || column == 0 || column == 11);
                else
                {
                    if (m_displayField[row][column] == 0)
                        cout << "|" << " ";
                    else
                        cout << "|" << m_displayField[row][column];
                }
            }

            if (row == 0 || row == 11);
            else
                cout << "|\n";
        }
        cout << "\n\n\n\n\n\n\n\n";
    }

    void Player::markAsDestroyed(int y, int x) // ����������� ��������� ������ ������������� �������
    {
        int ii = 0;
        while ((y + ii) < 11)
        {
            if (!m_playerField[y + ii][x])
                break;

            if (m_playerField[y + ii][x] == 2)
            {
                for (int it = 0; it < 3; ++it)
                {
                    for (int i = 0; i < 3; ++i)
                        if (m_displayField[(y + ii + 1) - i][(x + 1) - it] != 'X')
                            m_displayField[(y + ii + 1) - i][(x + 1) - it] = '*';
                }
                m_playerField[y + ii][x] = 0;
            }

            ++ii;
        }
        ii = 1;
        while ((y - ii) > 0)
        {

            if (!m_playerField[y - ii][x])
                break;

            if (m_playerField[y - ii][x] == 2)
            {
                for (int it = 0; it < 3; ++it)
                {
                    for (int i = 0; i < 3; ++i)
                        if (m_displayField[(y - ii + 1) - i][(x + 1) - it] != 'X')
                            m_displayField[(y - ii + 1) - i][(x + 1) - it] = '*';
                }
                m_playerField[y - ii][x] = 0;
            }
 
            ++ii;
        }
        ii = 1;
        while ((x + ii) < 11)
        {
            if (!m_playerField[y][x + ii])
                break;

            if (m_playerField[y][x + ii] == 2)
            {
                for (int it = 0; it < 3; ++it)
                {
                    for (int i = 0; i < 3; ++i)
                        if (m_displayField[(y + 1) - i][(x + ii + 1) - it] != 'X')
                            m_displayField[(y + 1) - i][(x + ii + 1) - it] = '*';
                }
                m_playerField[y][x + ii] = 0;
            }

            ++ii;
        }
        ii = 1;
        while ((x - ii) > 0)
        {

            if (!m_playerField[y][x - ii])
                break;

            if (m_playerField[y][x - ii] == 2)
            {
                for (int it = 0; it < 3; ++it)
                {
                    for (int i = 0; i < 3; ++i)
                        if (m_displayField[(y + 1) - i][(x - ii + 1) - it] != 'X')
                            m_displayField[(y + 1) - i][(x - ii + 1) - it] = '*';
                }
                m_playerField[y][x - ii] = 0;
            }

            ++ii;
        }
    }

    bool Player::isDestroyed(int y, int x) // ��������� ��� �� ������� ��������� 
    {
        int i = 0;
        while ((y + i) < 11)
        {
            ++i;
            if (m_playerField[y + i][x] == 0)
                break;
            if (m_playerField[y + i][x] == 1) // ���� ���� ���� ���� ����� ������ �� ���������� false
                return false;
        }
        i = 0;
        while ((y - i) > 0)
        {
            ++i;
            if (m_playerField[y - i][x] == 0)
                break;
            if (m_playerField[y - i][x] == 1)
                return false;
        }
        i = 0;
        while ((x + i) < 11)
        {
            ++i;
            if (m_playerField[y][x + i] == 0)
                break;
            if (m_playerField[y][x + i] == 1)
                return false;
        }
        i = 0;
        while ((x - i) > 0)
        {
            ++i;
            if (m_playerField[y][x - i] == 0)
                break;
            if (m_playerField[y][x - i] == 1)
                return false;
        }
                   
        markAsDestroyed(y, x); // ���� ����� ���� ������ ������� ���������, ������� ��� ��� ������������ ��� ������


        return true;
    }

    bool Player::hitOrMiss(int y, int x) // ��������� ������ ��� ������������
    {
        if (m_playerField[y][x] == 1)
        {
            m_playerField[y][x] = 2; // ���� ������ �� ������ � 1 �� 2 (���������: �������� ������)
            m_displayField[y][x] = 'X'; // �������� ��� �������� ������

            if (isDestroyed(y, x)) // ��������� �� ���������� �� ������� ����� ����� ���������
            {
                --m_ships; // ���� ���������� �� ������� 1 ������� �� ����������
                display();
                cout << "Ship has been destroyed!\n";
            }
            else
            {
                display();
                cout << "The ship has been hit!\n";
            }

            return true;
        }
        else
        {
            m_displayField[y][x] = '*'; // ���� �� ������ �� �������� ������ ������ ���������� 
            display();
            return false;
        }
    }

    bool Player::isAlreadyShot(int y, int x) // �������� ��� �� ��� ������� �� ���� ����������
    {
        if (m_displayField[y][x] != ' ')
            return true;

        return false;
    }
