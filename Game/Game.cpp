#include <iostream>
#include <vector>
using namespace std;

//Игра - версия 1.0
/*
    В первй версии у нас есть поле, по которому мы можем ходить, меняя свое положение
    Игровое поле составляет из себяя матрицу 3x3
    Также мы модем задвать место своего появления на поле, где точка (0,0) - верхний левый угол
    Размер поля у нас константный, пожтому в циклах печати мы задаем только число три, потому что нет инета и я не могу загуглить как это нормально сделать
    сделал передвижение на 4 стороны, но пока не сделал проверок движения
*/

//Что нужно будет сделать для версии 2.0
/*
    Добавить проверку движнией в виде просто сталкивания со стеной
    Добавить монетки на поле
    Добавить кастомный размер поля
    Добавить перемещение с помощью стрелочек, а не ввода
*/

//Игра - версия 2.0
/*
    Первое с чего начну - сделай кастомно задаваемое поле и начальную позицию!
    Добавил, теперь сделаю так, чтобы он был яркого цвета!
    Добавлена проверка положения, теперь при попытке зайти за границы - персонаж будет оставаться на месте.
    Добавлена проверка положения спавна, тепреь если заспавниться вне карты, то тебя перенесет на ближайшую точку на ней.
*/

//Идеи для версии 2.1
/*
    Добавить врагов, которые ходят после твоего хода! (будет сложно)
    Правила для врагов: если они наступают на тебя в течении своего хода, то убивают тебя, 
    если ты на них, то ты убиваешь. Как шахматы короче.
*/

//Что нужно будет сделать для версии 3.0
/*
    Сделать движение не ограниченным, а цикличным, мы появляемся на другом конце поля.
*/

void printSpace(pair<int, int> currPos, const vector<vector<string>>& space, pair<int, int> spaceWL) {

    int spaceWidth = spaceWL.first;
    int spaceHeight = spaceWL.second;

    for (int i = 0; i != spaceHeight; i++) {
        for (int j = 0; j != spaceWidth; j++) {
            if (j == spaceWidth - 1) {
                if ((i == currPos.second) and (j == currPos.first)) {
                    cout << "\033[35m" << "@" << "\033[0m" << endl;
                    continue;
                }
                cout << "O" << endl;
            }
            else {
                if ((i == currPos.second) and (j == currPos.first)) {
                    cout << "\033[35m" << "@" << "\033[0m" << " ";
                    continue;
                }
                cout << "O" << " ";
            }
        }
    }
};

vector<vector<string>> space = { {"O", "O", "O"},
                                {"O", "O", "O"},
                                {"O", "O", "O"} };

void gameStart(vector<vector<string>>& space) {
    bool playing = true;

    pair<int, int> spaceWL;
    pair<int, int> currPos;

    cout << "Введите размер поля, сначала ширину, потом высоту." << endl;
    cin >> spaceWL.first; //Ширина
    cin >> spaceWL.second; //Высота

   
    cout << "Теперь введите начальную позицию, сначала x, потом y (0,0 - верхний левый угол)" << endl;
    cin >> currPos.first; //Задаем позицию по x
    cin >> currPos.second; //Задаем позицию по y

    // Блок двойных направлений!
    if (currPos.first < 0 && currPos.second < 0) { //Слева сверху оказался
        currPos.second = 0;
        currPos.first = 0;
        cout << "\033[31m" << "Ты зашел слишком далеко на северо-запад, переносим тебя на ближайшую точку" << "\033[0m" << endl;
    }

    else if (currPos.first < 0 && currPos.second > spaceWL.second - 1) { //Слева снизу оказался
        currPos.second = spaceWL.second - 1;
        currPos.first = 0;
        cout << "\033[31m" << "Ты зашел слишком далеко на юго-запад, переносим тебя на ближайшую точку" << "\033[0m" << endl;
    }

    else if (currPos.first > spaceWL.first - 1 && currPos.second > spaceWL.second - 1) { //Справа снизу оказался
        currPos.second = spaceWL.second - 1;
        currPos.first = spaceWL.first - 1;
        cout << "\033[31m" << "Ты зашел слишком далеко на юго-восток, переносим тебя на ближайшую точку" << "\033[0m" << endl;
    }

    else if (currPos.first > spaceWL.first - 1 && currPos.second < 0) { //Справа сверху оказался
        currPos.second = 0;
        currPos.first = spaceWL.first - 1;
        cout << "\033[31m" << "Ты зашел слишком далеко на северо-восток, переносим тебя на ближайшую точку" << "\033[0m" << endl;
    }

    //Блок одинарных направлений
    else if (currPos.first < 0) { //Слева оказался
        currPos.first = 0;
        cout << "\033[31m" << "Ты зашел слишком далеко на запад, переносим тебя на ближайшую точку" << "\033[0m" << endl;
    }

    else if (currPos.first > spaceWL.first - 1) { //Справа оказался
        currPos.first = spaceWL.first - 1;
        cout << "\033[31m" << "Ты зашел слишком далеко на восток, переносим тебя на ближайшую точку" << "\033[0m" << endl;
    }

    else if (currPos.second < 0) { //Сверху оказался
        currPos.second = 0;
        cout << "\033[31m" << "Ты зашел слишком далеко на север, переносим тебя на ближайшую точку" << "\033[0m" << endl;
    }

    else if (currPos.second > spaceWL.second - 1) { //Снизу оказался
        currPos.second = spaceWL.second - 1;
        cout << "\033[31m" << "Ты зашел слишком далеко на юг, переносим тебя на ближайшую точку" << "\033[0m" << endl;
    }
    

    while (playing) {
        printSpace(currPos, space, spaceWL);
        cout << endl << "Выберете действие: 1 - влево; 2 - вправо; 3 - вверх, 4 - вниз, 0 - выйти" << endl;
        int inut;
        cin >> inut;

        switch (inut)
        {
        case 1:
            currPos.first -= 1; //Влево
            if (currPos.first < 0) { //Если позиция меньше края слева (0, y), то не пускает
                currPos.first += 1; 
                cout << "\033[31m" << "Дальше делать нечего" << "\033[0m" << endl;
            }
            break;
        case 2:
            currPos.first += 1; //Вправо
            if (currPos.first > spaceWL.first - 1) { //Если позиция меньше края справа (ширина - 1, y), то не пускает
                currPos.first -= 1;
                cout << "\033[31m" << "Дальше делать нечего" << "\033[0m" << endl;
            }
            break;
        case 3:
            currPos.second -= 1; //Вверх
            if (currPos.second < 0) { //Если позиция меньше края сверху (x, 0), то не пускает
                currPos.second += 1;
                cout << "\033[31m" << "Дальше делать нечего" << "\033[0m" << endl;
            }
            break;
        case 4:
            currPos.second += 1; //Вниз
            if (currPos.second > spaceWL.second - 1) { //Если позиция меньше края снизу (x, высота - 1), то не пускает
                currPos.second -= 1;
                cout << "\033[31m" << "Дальше делать нечего" << "\033[0m" << endl;
            }
            break;
        default:
            break;
        }

        if (inut == 0) {
            playing = false; //Конец игры если игрок нажал 0
        }
    }
    
};

int main()
{
    setlocale(LC_ALL, "RU");
    gameStart(space);
}
