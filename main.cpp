#include <iostream>
#include <vector>
#include <locale>// ����� ����� ������������ ���������
#include <numbers>
#include <cmath>

double pi = std::numbers::pi_v<double>;


// ������� ��� ���������� ���� x_i (��� i �� 0 �� m)
static std::vector<double> X_i(int m)
{
    double a = 0.0; // ��������� �������� x
    double b = 2.0; // �������� �������� x
    double h = 0.2; // ���
    std::vector<double> x_values; // ������ ��� �������� �������� x_i

    for (int i = 0; i <= m; ++i)
    {
        double x_i = a + i * h;
        x_values.push_back(x_i); // ��������� x_i � ������
    }

    return x_values;
}

static double Sum(double x)
{
    double sum = 0.0;
    int n = 0;
    double epsilon = 1e-6;

    // ��������� ���� ���� (a_0)
    double a_n = x;

    do
    {
        sum += a_n;

        // ��������� ��������� ���� ���� a_n+1 = a_n * q_n
        a_n *= (-1 * pow(x, 2) * (2 * n + 1)) / (2 * pow(n, 2) + 5 * n + 3);
        n++;
    } while (fabs(a_n) >= epsilon);
   
    return sum;
}

int main()
{
    setlocale(LC_ALL, "");
    int m = 5; // ���������� �����
    std::vector<double> x_values = X_i(m); // ������ �� ����� x

    std::cout << "�������� x_i � f_i:" << std::endl;
    for (int i = 0; i <= m; ++i)
    {
        double x_i = x_values[i]; // �������� ���������� x_i
        double f_i = (2 / sqrt(pi)) * Sum(x_i); // ��������� f_i ��� ����������� x_i

        std::cout << "x_" << i << " = " << x_i << ", ";
        std::cout << "f_" << i << " = " << f_i << std::endl;
    }

    return 0;
}











//////////////2 ����� � �������������� ����������, �� ���� �������� ������� ��� ����� ���� ��� �_n+1 = a_n*q_n////////////////
/*
#include <iostream>
#include <vector> // ��� ������������� �������
#include <locale> //����� ��������� ��������� � ������� ������������
#include <numbers>

double pi = std::numbers::pi_v<double>;

using namespace std;

// ������� ��� ���������� ����������
double Factorial(int n)
{
    if (n <= 1) return 1;
    return n * Factorial(n - 1);
}


//������� ��� ���������� ���� x_i(��� i �� 0 �� m = 5)
vector<double> X_i(int m)
{
    double a = 0.0; // ��������� �������� x
    double b = 2.0; // �������� �������� x
    int n = 5;
    double h = 0.2; // ���
    vector<double> x_values; // ������ ��� �������� �������� x_i

    // ���������� �������� x_i ��� i �� 0 �� m
    for (int i = 0; i <= m; ++i)
    {
        double x_i = a + i * h;
        x_values.push_back(x_i); // ��������� x_i � ������
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
        // ���� ���� ��� ������� x
        a_n = (pow(-1, n) * pow(x, 2 * n + 1)) / (Factorial(n) * (2 * n + 1));
        sum += a_n;
        n++;
    } while (fabs(a_n) >= epsilon); // ���������� ���� ���� ���� �� ������ ������ epsilon

    return sum;
}

int main()
{
    setlocale(LC_ALL, "");
    double pi = std::numbers::pi_v<double>;
    int m = 5; // ���������� �����
    vector<double> x_values = X_i(m); //������ �� ����� �


    cout << "�������� x_i � f_i:" << endl;
    for (int i = 0; i <= m; ++i)
    {
        double x_i = x_values[i]; // �������� ���������� x_i
        double f_i = (2 / sqrt(pi)) * SumForXi(x_i); // ��������� f_i ��� ����������� x_i

        cout << "x_" << i << " = " << x_i << ", ";
        cout << "f_" << i << " = " << f_i << endl;
    }
}
*/
