#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double Function(double x);

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << setprecision(10); //Определяем точность выводимых значений
    const int n = 6; //Количество узлов интерполирования
    //Выберем узлы интерполирования, взяв за первое значение начало интервала, а за конечное - конец, остальные находятся равноудалённо с отступом 0.8
    //Значение было найдено по формуле (1 - (-3))\5
    double X[n] = { -3,  -2.2, -1.4, -0.6, 0.2, 1 };
    double x = -0.2;
    //Найдём значения функции
    double Y[n];
    for (int i = 0; i < n; i++)
        Y[i] = Function(X[i]);
    
    cout << "Значения функции в узлах и сами узлы: " << endl;
    for (int i = 0; i < n; i++)
        cout << "Y: " << Y[i] << "\tX: " << X[i] << endl;

    //Построим полином Лагранжа
    double A[n] = { 0 }; //Отвечает за значение у х (в разных степенях) в формуле полинома Лагранжа
    int Index[n - 1] = { 1, 2, 3, 4, 5 };
    double Znam[n] = { 1, 1, 1, 1, 1, 1 }; //Отвечает за значения в формуле полинома Лагранжа, которые можно спокойно посчитать
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

            if (j == i)
                continue;
            Znam[i] *= (X[i] - X[j]);
        }

        for (int j = 0; j < n - 1; j++)
        {
            if (Index[j] == i)
                Index[j] -= 1;
        }
        A[0] += (X[Index[0]] * X[Index[1]] * X[Index[2]] * X[Index[3]] * X[Index[4]]) * (-1) / Znam[i] * Y[i];
        A[1] += (X[Index[0]] * X[Index[1]] * X[Index[2]] * X[Index[3]] + X[Index[0]] * X[Index[1]] * X[Index[2]] * X[Index[4]] +
            X[Index[0]] * X[Index[1]] * X[Index[3]] * X[Index[4]] + X[Index[1]] * X[Index[2]] * X[Index[3]] * X[Index[4]] +
            X[Index[0]] * X[Index[2]] * X[Index[3]] * X[Index[4]]) / Znam[i] * Y[i];
        A[2] += (X[Index[0]] * X[Index[1]] * X[Index[2]] + X[Index[0]] * X[Index[1]] * X[Index[3]] + X[Index[1]] * X[Index[2]] * X[Index[3]] +
            X[Index[0]] * X[Index[2]] * X[Index[3]] + X[Index[0]] * X[Index[1]] * X[Index[4]] + X[Index[1]] * X[Index[2]] * X[Index[4]] +
            X[Index[0]] * X[Index[2]] * X[Index[4]] + X[Index[1]] * X[Index[3]] * X[Index[4]] + X[Index[0]] * X[Index[3]] * X[Index[4]] +
            X[Index[2]] * X[Index[3]] * X[Index[4]]) * (-1) / Znam[i] * Y[i];
        A[3] += (X[Index[0]] * X[Index[1]] + X[Index[1]] * X[Index[2]] + X[Index[0]] * X[Index[2]] + X[Index[1]] * X[Index[3]] +
            X[Index[0]] * X[Index[3]] + X[Index[2]] * X[Index[3]] + X[Index[1]] * X[Index[4]] + X[Index[0]] * X[Index[4]] +
            X[Index[2]] * X[Index[4]] + X[Index[3]] * X[Index[4]]) / Znam[i] * Y[i];
        A[4] += (X[Index[0]] + X[Index[1]] + X[Index[2]] + X[Index[3]] + X[Index[4]]) * (-1) / Znam[i] * Y[i];
        A[5] += Y[i] / Znam[i];
    }
    cout << "Полином Лагранжа: ";
    for (int i = n - 1; i >= 0; i--)
    {
        cout << A[i] << "X^" << i << " ";
        if (i == 3 || i == 2 || i == 1)
            cout << " + ";
    }

    //Найдём абсолютную погрешность в точке х
    double P = A[5] * pow(x, 5) + A[4] * pow(x, 4) + A[3] * pow(x, 3) + A[2] * pow(x, 2) + A[1] * pow(x, 1) + A[0];
    cout << endl << "Полином Лагранжа равен: " << P << endl;

    cout << "Действительноe значение: " << Function(x) << endl;

    cout << "Aбсолютная погрешность: " << fabs(Function(x) - P) << endl;

    //Найдём полином Ньютона (строить не будем, т.к. уже был построен полином Лагранжа, сделано это было исключительно для графика, который будет схож)

    //Разделённые разности
    double Razn2[5] = { 0 }; //2 аргумента
    double Razn3[4] = { 0 }; //3
    double Razn4[3] = { 0 }; //4
    double Razn5[2] = { 0 }; //5
    double Razn6; //6

    cout << endl << "Разделённые разности: " << endl;
    
    for (int i = 0; i < 5; i++)
        Razn2[i] = (Function(X[i + 1]) - Function(X[i])) / (X[i + 1] - X[i]);

    for (int i = 0; i < 5; i++)
        cout << Razn2[i] << "\t";
    cout << endl;

    for (int i = 0; i < 4; i++)
        Razn3[i] = (Razn2[i + 1] - Razn2[i]) / (X[i + 2] - X[i]);

    for (int i = 0; i < 4; i++)
        cout << Razn3[i] << "\t";
    cout << endl;

    for (int i = 0; i < 3; i++)
        Razn4[i] = (Razn3[i + 1] - Razn3[i]) / (X[i + 3] - X[i]);

    for (int i = 0; i < 3; i++)
        cout << Razn4[i] << "\t";
    cout << endl;

    for (int i = 0; i < 2; i++)
        Razn5[i] = (Razn4[i + 1] - Razn4[i]) / (X[i + 4] - X[i]);

    for (int i = 0; i < 2; i++)
        cout << Razn5[i] << "\t";
    cout << endl;

    Razn6 = (Razn5[1] - Razn5[0]) / (X[5] - X[0]);

    cout << Razn6 << endl;

    //Найдём значение полинома Ньютона в точке х
    double P2 = Function(X[0]) + Razn2[0] * (x - X[0]) + Razn3[0] * (x - X[0]) * (x - X[1]) + Razn4[0] * (x - X[0]) * (x - X[1]) * (x - X[2]) + 
        Razn5[0] * (x - X[0]) * (x - X[1]) * (x - X[2]) * (x - X[3]) + Razn6 * (x - X[0]) * (x - X[1]) * (x - X[2]) * (x - X[3]) * (x - X[4]);

    cout << "Полином Ньютона равен: " << P2 << endl;
    cout << "Действительное значение: " << Function(x) << endl;
    cout << "Абсолютная погрешность равна: " << fabs(Function(x) - P2);
    return 0;
}

double Function(double x)
{
    double y = 1.3 * cos(-3.3 * x + 2.2) - 0.7 * pow(x, 3) - 0.4 * pow(x, 2) - 0.6 * x + 3.5; //Данная по условию функция
    return y;
}