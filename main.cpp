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
    double h = (b - a) / m; // Шаг
    std::vector<double> x_values; // Вектор для хранения значений x_i

    for (int i = 0; i <= m; ++i)
    {
        double x_i = a + i * h;
        x_values.push_back(x_i); // Добавляем x_i в вектор
    }

    return x_values;
}

static std::vector<double> X_i_Chebyshev(int n)
{
    double a = 0.0; // Начальное значение интервала
    double b = 2.0; // Конечное значение интервала
    std::vector<double> chebyshev_values; // Вектор для хранения узлов Чебышева

    for (int i = 0; i <= n; ++i)
    {
        double x_i = (a + b) / 2.0 + (b - a) / 2.0 * cos((2.0 * i + 1.0) / (2.0 * (n + 1)) * pi);
        chebyshev_values.push_back(x_i); // Добавляем узел Чебышева в вектор
    }

    return chebyshev_values;
}

// Функция для вычисления суммы ряда
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

// Функция для вычисления интерполяционного полинома Лагранжа
static double LagrangePolynomial(const std::vector<double>& x_nodes, const std::vector<double>& y_nodes, double x)
{
    int n = x_nodes.size();
    double result = 0.0;

    for (int i = 0; i < n; ++i)
    {
        double term = y_nodes[i];
        for (int j = 0; j < n; ++j)
        {
            if (i != j)
            {
                term *= (x - x_nodes[j]) / (x_nodes[i] - x_nodes[j]);
            }
        }
        result += term;
    }

    return result;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout.imbue(std::locale("Russian"));

    // Узлы интерполяции
    int m = 5; // Количество узлов
    std::vector<double> x_nodes = X_i(m);
    std::vector<double> y_nodes;

    // Вычисляем значения функции в узлах
    for (double x : x_nodes)
    {
        y_nodes.push_back((2 / sqrt(pi)) * Sum(x));
    }

    // Точки проверки интерполяции (11 точек)
    int testPoints = 10; // m = 10 для 11 точек
    std::vector<double> x_test = X_i(testPoints);

    std::cout << "Точки интерполяции (узлы):\n";
    for (size_t i = 0; i < x_nodes.size(); ++i)
    {
        std::cout << x_nodes[i] << ";" << y_nodes[i] << std::endl;
    }

    std::cout << "\nТаблица ошибок:\n";
    std::cout << "x;f(x);L(x);|f(x) - L(x)|\n";

    double max_error = 0.0;

    for (double x : x_test)
    {
        double f_x = (2 / sqrt(pi)) * Sum(x); // Точное значение функции
        double L_x = LagrangePolynomial(x_nodes, y_nodes, x); // Значение полинома
        double abs_error = fabs(f_x - L_x); // Абсолютная ошибка

        if (abs_error > max_error)
        {
            max_error = abs_error;
        }

        // Вывод в консоль
        std::cout << x << ";" << abs_error << std::endl;

    }

    std::cout << "\nМаксимальная ошибка интерполяции: " << max_error << std::endl;

    // Эксперимент с увеличением числа узлов
    std::cout << "\nЭксперимент: зависимость максимальной ошибки от числа узлов (равномерные узлы)\n";
    std::cout << "Число узлов\tМаксимальная ошибка\n";

    for (int nodes = 2; nodes <= 45; ++nodes)
    {
        std::vector<double> exp_x_nodes = X_i(nodes);
        std::vector<double> exp_y_nodes;

        for (double x : exp_x_nodes)
        {
            exp_y_nodes.push_back((2 / sqrt(pi)) * Sum(x));
        }

        double exp_max_error = 0.0;
        for (double x : X_i(10)) // Тестовые точки (11 точек)
        {
            double f_x = (2 / sqrt(pi)) * Sum(x);
            double L_x = LagrangePolynomial(exp_x_nodes, exp_y_nodes, x);
            double abs_error = fabs(f_x - L_x);

            if (abs_error > exp_max_error)
            {
                exp_max_error = abs_error;
            }
        }

        // Исключаем узлы с нулевой погрешностью
        if (exp_max_error > 0 && exp_max_error < 1)
        {
            std::cout << nodes + 1 << ";" << exp_max_error << std::endl;
        }
    }




    // Узлы Чебышева
    int n = 5; // Количество узлов
    std::vector<double> chebyshev_nodes = X_i_Chebyshev(n);
    std::vector<double> chebyshev_y_nodes;

    // Вычисляем значения функции в узлах Чебышева
    for (double x : chebyshev_nodes)
    {
        chebyshev_y_nodes.push_back((2 / sqrt(pi)) * Sum(x));
    }

    std::cout << "\nТочки интерполяции (узлы Чебышева):\n";
    for (size_t i = 0; i < chebyshev_nodes.size(); ++i)
    {
        std::cout << chebyshev_nodes[i] << ";" << chebyshev_y_nodes[i] << std::endl;
    }

    std::cout << "\nТаблица ошибок при узлах Чебышева:\n";
    std::cout << "x;f(x);L(x);|f(x) - L(x)|\n";

    double chebyshev_max_error = 0.0;

    for (double x : X_i(10)) // Используем 11 тестовых точек
    {
        double f_x = (2 / sqrt(pi)) * Sum(x); // Точное значение функции
        double L_x = LagrangePolynomial(chebyshev_nodes, chebyshev_y_nodes, x); // Значение полинома
        double abs_error = fabs(f_x - L_x); // Абсолютная ошибка

        if (abs_error > chebyshev_max_error)
        {
            chebyshev_max_error = abs_error;
        }

        // Вывод в консоль
        std::cout << x << ";" << abs_error << std::endl;
    }

    std::cout << "\nМаксимальная ошибка интерполяции при узлах Чебышева: " << chebyshev_max_error << std::endl;

    // Эксперимент с увеличением числа узлов Чебышева
    std::cout << "\nЭксперимент: зависимость максимальной ошибки от числа узлов (узлы Чебышева)\n";
    std::cout << "Число узлов\tМаксимальная ошибка\n";

    for (int nodes = 2; nodes <= 45; ++nodes)
    {
        std::vector<double> exp_chebyshev_nodes = X_i_Chebyshev(nodes);
        std::vector<double> exp_chebyshev_y_nodes;

        for (double x : exp_chebyshev_nodes)
        {
            exp_chebyshev_y_nodes.push_back((2 / sqrt(pi)) * Sum(x));
        }

        double exp_chebyshev_max_error = 0.0;
        for (double x : X_i(10)) // Тестовые точки (11 точек)
        {
            double f_x = (2 / sqrt(pi)) * Sum(x);
            double L_x = LagrangePolynomial(exp_chebyshev_nodes, exp_chebyshev_y_nodes, x);
            double abs_error = fabs(f_x - L_x);

            if (abs_error > exp_chebyshev_max_error)
            {
                exp_chebyshev_max_error = abs_error;
            }
        }

        // Исключаем узлы с нулевой погрешностью
        if (exp_chebyshev_max_error > 0 && exp_chebyshev_max_error < 1)
        {
            std::cout << nodes + 1 << ";" << exp_chebyshev_max_error << std::endl;
        }
    }


    return 0;

}
