﻿#include <iostream>
#include <iomanip>
#include <stdlib.h> //Для функции max()

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    cout << setprecision(10); //Определяем точность выводимых значений
    //В матрицах cначала строки, а потом столбцы!
    double A[3][3] = { {-10.1, -8.8, -0.3}, {-9.4, 12.1, -1.9}, {2.1, -5.7, -10.0} };
    //double A[3][3] = { {-9.4, 3.3, 5.4}, {-7.0, -11.8, 2.6}, {-9.1, -9.5, 19.9} };
    double B[3][1] = { {-118.1}, {-40.1}, {-76.0} };
    //double B[3][1] = { {122.7}, {-19.8}, {147.3} };
    double X[3][1] = { {0}, {0}, {0} };
    double opr = 0.0; //Определитель
    cout << " Исходная матрица: " << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << setw(6) << A[i][j] << " ";
        cout << " | ";
        cout << setw(6) << B[i][0] << endl;

        double diagDOWN= A[0][2]*A[1][1]*A[2][0]; //рассчитываем нижнюю (побочную) диагональ
        double diagUP = A[0][0]*A[1][1]*A[2][2]; //рассчитываем верхнюю (главную) диагональ
        opr = diagUP - diagDOWN; //находим определитель матрицы
    }
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Применим метод Гаусса" << endl;
    cout << "Определитель матрицы: " << opr << ", не равен нулю, а значит система имеет единственное решение." << endl;


    cout << "Применим прямой ход метода Гаусса: " << endl;
    double AB[3][4];

    cout << "Расширенная матрица: " << endl;
    for (int i = 0; i < 3; i++) //создаём расширенную матрицу
    {
        for (int j = 0; j < 3; j++)
        {
            AB[i][j] = A[i][j];
            cout << setw(6) << AB[i][j] << " ";
        }
        AB[i][3] = B[i][0];
        cout << setw(8) << AB[i][3] << endl;
    }

    cout << "Расширенная матрица после прямого хода: " << endl;
    double first = 0.0, second = 0.0;
    for(int i = 0; i < 3; i++) //приводим матрицу к ступенчатому виду
    {
        for (int j = 0; j < 3; j++) //определяем "опорный" элемент в нужной строке
        {
            if (AB[i][j] != 0)
            {
                first = AB[i][j];
                break;
            }
        }
        for (int j = 0; j < 4; j++) //делим всё на "опорный" элемент, чтобы получить единицу в нужном столбце и облегчить дальнейшие вычисления
        {
            AB[i][j] /= first;
        }
        for (int k = i + 1; k < 3; k++) //перебираем строки, ниже текущей
        {
            for (int j = 0; j < 3; j++) //определяем второй "опорный" элемент
            {
                if (AB[k][j] != 0) 
                {
                    second = AB[k][j];
                    break;
                }
            }
            for (int j = 0; j < 4; j++) //сам процесс "Обнуления"
            {
                AB[k][j] = AB[k][j] - AB[i][j] * second;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
            cout << setw(15) << AB[i][j] << " ";
        cout << endl;
    }

    cout << "Применим обратный ход метода Гаусса и найдём корни:  " << endl;
    //решаем полученную при прямом ходе систему
    X[2][0] = AB[2][3];
    X[1][0] = AB[1][3] - AB[1][2] * X[2][0];
    X[0][0] = AB[0][3] - AB[0][2] * X[2][0] - AB[0][1] * X[1][0];
    cout << "x1 = " << X[0][0] << "    x2 = " << X[1][0] << "   x3 = " << X[2][0] << endl;

    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Применим итерационные методы." << endl;
    double E = 1e-6; //Точность
    //изменнная матрица под итерационные методы (выражая х1 из первого уравнения, х2 из второго и х3 из третьего):
    double C[3][3] = { {0, -0.87128713, -0.02970297}, {0.77685950, 0, 0.15702479}, {0.21, -0.57, 0} };
    //double C[3][3] = { {0, -0.35106383, -0.57446809}, {0.59322034, 0, -0.22033898}, {-0.45728693, -0.47738693, 0} };
    //матрица свободных членов:
    double D[3][1] = { {11.69306931}, {-3.31404959}, {7.6} };
    //double D[3][1] = { {-13.05319149}, {1.67796610}, {7.40201005} };

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << setw(15) << C[i][j] << " ";
        cout << " | ";
        cout << setw(15) << D[i][0] << endl;
    }
    
    double KubNorm = 0.0;
    //Определим кубическую норму
    KubNorm = max(fabs(C[0][0] + C[0][1] + C[0][2]), fabs(C[1][0] + C[1][1] + C[1][2]) );
    KubNorm = max(KubNorm, fabs(C[2][0] + C[2][1] + C[2][2]) );
    //Т.к. функция max() принимает только два значения, сравнение пришлось проводить дважды
    cout << "Кубическая норма матрицы равна: " << KubNorm << " меньше 1, значит итерационные методы сходятся к точному решению" << endl;

    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Применим метод простых итераций" << endl;
    double nev = 0.0; //Переменная для невязки
    double X0[3] = { 0 }; //Начальное приближение
    double X1[3] = { 0 }; //Следующая итерация
    double razn = 0.0; //Понадобится для условия остановки цикла
    int iter = 0; //подсчёт итераций
    do //Сам процесс
    { 
        X1[0] = 1 / A[0][0] * (B[0][0] - A[0][1] * X0[1] - A[0][2] * X0[2]);
        X1[1] = 1 / A[1][1] * (B[1][0] - A[1][0] * X0[0] - A[1][2] * X0[2]);
        X1[2] = 1 / A[2][2] * (B[2][0] - A[2][0] * X0[0] - A[2][1] * X0[1]);
        razn = max(fabs(X1[0] - X0[0]), fabs(X1[1] - X0[1]));
        razn = max(razn, fabs(X1[2] - X0[2]));
        X0[0] = X1[0];
        X0[1] = X1[1];
        X0[2] = X1[2];
        iter++;
    } while (KubNorm / (1 - KubNorm) * razn > E); // Условие продолжения цикла
    cout << "x1 = " << X1[0] << "   x2 = " << X1[1] << "    x3 = " << X1[2] << endl;
    cout << "Количество итераций: " << iter << endl;
    cout << "Невязка функции: ";
    nev = max(fabs(B[0][0] - A[0][0] * X1[0] - A[0][1] * X1[1] - A[0][2] * X1[2]), fabs(B[1][0] - A[1][0] * X1[0] - A[1][1] * X1[1] - A[1][2] * X1[2]));
    nev = max(nev, fabs(B[2][0] - A[2][0] * X1[0] - A[2][1] * X1[1] - A[2][2] * X1[2]));
    cout << nev << endl;

    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Применим метод Зейделя" << endl;
    for (int i = 0; i < 3; i++)
    {
        X0[i] = 0;
        X1[i] = 0;
    }
    //Изменённая матрица под метод Зейделя (разложим на две треугольные (C = C1 + C2))
    double C2[3][3] = { {0, -0.87128713, -0.02970297}, {0, 0, 0.15702479}, {0, 0, 0} };
    //double C2[3][3] = { {0, -0.35106383, -0.57446809}, {0, 0, -0.22033898}, {0, 0, 0} };
    double KubNorm2 = 0.0; //Кубическая норма матрицы С2
    KubNorm2 = max(fabs(C2[0][0] + C2[0][1] + C2[0][2]), fabs(C2[1][0] + C2[1][1] + C2[1][2]));
    //Т.к. 3 строка вся в нулях, поэтому достаточно одной функции max()
    iter = 0; //Обнуление счётчика
    do //Сам процесс метода
    {
        X1[0] = 1 / A[0][0] * (B[0][0] - A[0][1] * X0[1] - A[0][2] * X0[2]);
        X1[1] = 1 / A[1][1] * (B[1][0] - A[1][0] * X1[0] - A[1][2] * X0[2]);
        X1[2] = 1 / A[2][2] * (B[2][0] - A[2][0] * X1[0] - A[2][1] * X1[1]);
        razn = max(fabs(X1[0] - X0[0]), fabs(X1[1] - X0[1]));
        razn = max(razn, fabs(X1[2] - X0[2]));
        X0[0] = X1[0];
        X0[1] = X1[1];
        X0[2] = X1[2];
        iter++;
    } while (KubNorm2 / (1 - KubNorm) * razn > E); // Условие продолжения цикла
    cout << "x1 = " << X1[0] << "   x2 = " << X1[1] << "    x3 = " << X1[2] << endl;
    cout << "Количество итераций: " << iter << endl;

    cout << "Невязка функции: ";
    nev = max(fabs(B[0][0] - A[0][0] * X1[0] - A[0][1] * X1[1] - A[0][2] * X1[2]), fabs(B[1][0] - A[1][0] * X1[0] - A[1][1] * X1[1] - A[1][2] * X1[2]) );
    nev = max(nev, fabs(B[2][0] - A[2][0] * X1[0] - A[2][1] * X1[1] - A[2][2] * X1[2]) );
    cout << nev << endl;
    return 0;
}
