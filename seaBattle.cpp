#include "Player.h"
#include <ctime>
#include "Windows.h" //для функции Sleep
#include <cstdlib>



int getRandomNumber(int min, int max) // генерируем случайное число с помощью этой фунции
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}



void isWin(Player & ch, Player & def) // для проверки на наличие неуничтоженных кораблей. Конец игры и вывод победителя если не осталось целый кораблей.
{
    if (def.placedShips() == 0)
    {
        cout << ch.getName() << " has destroyed all opponents ships! Congratulations!\n";
        exit(0);
    }
}

int convertChar(char letter) // конверируем букву в цифру для использовния в массиве
{
    switch (letter)
    {
    case 'A': return 1;
    case 'B': return 2;
    case 'C': return 3;
    case 'D': return 4;
    case 'E': return 5;
    case 'F': return 6;
    case 'G': return 7;
    case 'H': return 8;
    case 'I': return 9;
    case 'J': return 10;
    }
}

bool isCorrect(int row, char column) // проверка пользовательского ввода
{
    if (row < 1 || row > 10 || column < 'A' || column > 'J')
    {
        if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n');
        }

        return false;
    }

    return true;
}

void placeShips(Player &p) // расстановка кораблей 
{
    p.set(); // инициализируем поле
    p.printEmpty(); // выводим пустое поле

    cout << p.getName() << " places ships.";

    while (p.placedShips() < 10)
    {
        
        int ship = p.generateShip(); // возвращаем количество палуб
        p.addShips(); // увеличиваем переменную m_ships

        cout << "\n\n\n\n\n\n\n\nPlace " << ship << "-deck ship>\n";

        cout << "\n";

        while (1) // ставим корабль на позицию
        {
            int row; char column; char position;
           
                if (ship > 1)
                {
                    cout << "Row:";
                    cin >> row;
                    cout << "Column:"; 
                    cin >> column;
                    cout << "Position ('h' horisontal / 'v' vertical):";
                    cin >> position;          
                }
                else
                {
                    cout << "Row:";
                    cin >> row;
                    cout << "Column:";
                    cin >> column;
                    position = 'h';
                }

                if (column >= 'a' && column <= 'j') // конвертиурем букву в заглавную если она строчная
                    column = column - 32;

                if (position == 'H' || position == 'V') 
                    position = position + 32;

                if (position != 'h' && position != 'v') // проверка ввода
                {
                    cin.clear();
                    std::cin.ignore(32767, '\n');
                    p.printPlayerField();
                    cout << "\n\n\n\n\n\n\n\n\n\n";
                    continue;
                }

                if (!isCorrect(row, column)) //проверка ввода
                {
                    cout << "\n\n\n\n\n\n\n\n\n\n";
                    p.printPlayerField();
                    cout << "\n\n\n\n\n\n\n\n\n\n";
                    continue;
                }

            
            

            if (p.placeShip(row, convertChar(column), position, ship)) // проверка на корректность выбранной позиции и установка корабля
                break;
            else
            {
                p.printPlayerField();
                cout << "\n\n\n\n\n\n\n\n\n\n";
                cout << "You can't place the ship at this position\n";
            }
        }

        cout << "\n\n\n";

        p.printPlayerField();
    }
}

/*void placeRandomly(Player & p) // фунция для случайной расстановки кораблей (нужна была в процессе разработки, полезна при модификации игры)
{
    p.set();

    while (p.placedShips() < 10)
    {
        int ship = p.generateShip();
        p.addShips();

        while (1)
        {
            int row(getRandomNumber(1, 10));
            int column(getRandomNumber(1, 10));
            char position;

            if (getRandomNumber(0, 1))
                position = 'h';
            else
                position = 'v';

            if (p.placeShip(row, convertChar(column), position, ship))
                break;
        }
    }
}*/

void round(Player & ch, Player & def) // основая функция игры. Выполняеться циклично до завершения игры.
{
    int row; char column;

    def.display();
    cout << ch.getName() << " attacks.\n";

    while (1)
    {
        while (1)
        {
            cout << "Row: ";
            cin >> row;
            cout << "Column: ";
            cin >> column;

            if (column >= 'a' && column <= 'j')
                column = column - 32;

            if (!isCorrect(row, column))
            {
                cout << "\n\n";
                def.display();
            }
            else
                break;
        }

        if (def.isAlreadyShot(row, convertChar(column))) // проверка была ли координата уже проверенна. Переходим к следующей итерации если уже стреляли сюда.
        {
            def.display();
            cout << "Already shot there! Try another spot.\n";
            Sleep(2000);
            continue;
        }

        if (!def.hitOrMiss(row, convertChar(column))) // проверка было ли попадание по этой координате. Если не попали то завершаем цикл.
        {
            cout << ch.getName() << " Missed!\n";
            Sleep(2000);
            break;
        }
        else
        {
            Sleep(2000);
            isWin(ch, def); // проверяем нет ли еще победителя
            cout << ch.getName() << " attacks.\n";
            cin.clear();
        }
    }
}

int main()
{
    srand(static_cast<int>(time(0))); 
    rand();

    Player p1; 
    p1.setName("first"); // просим игроков ввести имена
    Player p2;
    p2.setName("second");
    
    placeShips(p1); // расставляем корабли
    placeShips(p2);
    cout << "\n\n";
    
    /*placeRandomly(p1);
    placeRandomly(p2);
    p1.printPlayerField();
    cout << "\n\n";
    p2.printPlayerField();
    */

    while (1) // основной цикл игры. Выход из цикла с помощью функции exit(0) после проверки условия победы игрока в функции isWin()
    {
        round(p1, p2);
        round(p2, p1);
    }
 
    return 0;
}

