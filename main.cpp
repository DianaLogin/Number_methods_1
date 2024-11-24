#include <iostream>
#include <vector>
#include <locale>// Чтобы верно отображалась кодировка
#include <numbers>
#include <cmath>

double pi = std::numbers::pi_v<double>;


// Функция для нахождения всех x_i (для i от 0 до m)
static std::vector<double> X_i(int m)
{
    double a = 0.0; // Начальное значение x
    double b = 2.0; // Конечное значение x
    double h = 0.2; // Шаг
    std::vector<double> x_values; // Вектор для хранения значений x_i

    for (int i = 0; i <= m; ++i)
    {
        double x_i = a + i * h;
        x_values.push_back(x_i); // Добавляем x_i в вектор
    }

    return x_values;
}

static double Sum(double x)
{
    double sum = 0.0;
    int n = 0;
    double epsilon = 1e-6;

    // Начальный член ряда (a_0)
    double a_n = x;

    do
    {
        sum += a_n;

        // Вычисляем следующий член ряда a_n+1 = a_n * q_n
        a_n *= (-1 * pow(x, 2) * (2 * n + 1)) / (2 * pow(n, 2) + 5 * n + 3);
        n++;
    } while (fabs(a_n) >= epsilon);
   
    return sum;
}

int main()
{
    setlocale(LC_ALL, "");
    int m = 5; // Количество шагов
    std::vector<double> x_values = X_i(m); // Вектор со всеми x

    std::cout << "Значения x_i и f_i:" << std::endl;
    for (int i = 0; i <= m; ++i)
    {
        double x_i = x_values[i]; // Получаем конкретное x_i
        double f_i = (2 / sqrt(pi)) * Sum(x_i); // Вычисляем f_i для конкретного x_i

        std::cout << "x_" << i << " = " << x_i << ", ";
        std::cout << "f_" << i << " = " << f_i << std::endl;
    }

    return 0;
}











//////////////2 МЕТОД с использованием ФАКТОРИАЛА, то есть напрямую считать без учета того что а_n+1 = a_n*q_n////////////////
/*
#include <iostream>
#include <vector> // Для использования вектора
#include <locale> //Чтобы кодировка корректно в консоли отображалась
#include <numbers>

double pi = std::numbers::pi_v<double>;

using namespace std;

// Функция для вычисления факториала
double Factorial(int n)
{
    if (n <= 1) return 1;
    return n * Factorial(n - 1);
}


//Функция для нахождения всех x_i(для i от 0 до m = 5)
vector<double> X_i(int m)
{
    double a = 0.0; // Начальное значение x
    double b = 2.0; // Конечное значение x
    int n = 5;
    double h = 0.2; // Шаг
    vector<double> x_values; // Вектор для хранения значений x_i

    // Вычисление значений x_i для i от 0 до m
    for (int i = 0; i <= m; ++i)
    {
        double x_i = a + i * h;
        x_values.push_back(x_i); // Добавляем x_i в вектор
    }

    return x_values;
}


double SumForXi(double x)
{
    double sum = 0.0;
    int n = 0;
    double epsilon = pow(10, -6);
    double a_n = 0.0;

    do
    {
        // Член ряда для каждого x
        a_n = (pow(-1, n) * pow(x, 2 * n + 1)) / (Factorial(n) * (2 * n + 1));
        sum += a_n;
        n++;
    } while (fabs(a_n) >= epsilon); // Продолжаем пока член ряда не станет меньше epsilon

    return sum;
}

int main()
{
    setlocale(LC_ALL, "");
    double pi = std::numbers::pi_v<double>;
    int m = 5; // Количество шагов
    vector<double> x_values = X_i(m); //вектор со всеми х


    cout << "Значения x_i и f_i:" << endl;
    for (int i = 0; i <= m; ++i)
    {
        double x_i = x_values[i]; // Получаем конкретное x_i
        double f_i = (2 / sqrt(pi)) * SumForXi(x_i); // Вычисляем f_i для конкретного x_i

        cout << "x_" << i << " = " << x_i << ", ";
        cout << "f_" << i << " = " << f_i << endl;
    }
}
*/
