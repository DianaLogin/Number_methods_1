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
    double h = (b - a) / m; // ���
    std::vector<double> x_values; // ������ ��� �������� �������� x_i

    for (int i = 0; i <= m; ++i)
    {
        double x_i = a + i * h;
        x_values.push_back(x_i); // ��������� x_i � ������
    }

    return x_values;
}

static std::vector<double> X_i_Chebyshev(int n)
{
    double a = 0.0; // ��������� �������� ���������
    double b = 2.0; // �������� �������� ���������
    std::vector<double> chebyshev_values; // ������ ��� �������� ����� ��������

    for (int i = 0; i <= n; ++i)
    {
        double x_i = (a + b) / 2.0 + (b - a) / 2.0 * cos((2.0 * i + 1.0) / (2.0 * (n + 1)) * pi);
        chebyshev_values.push_back(x_i); // ��������� ���� �������� � ������
    }

    return chebyshev_values;
}

// ������� ��� ���������� ����� ����
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

// ������� ��� ���������� ����������������� �������� ��������
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

    // ���� ������������
    int m = 5; // ���������� �����
    std::vector<double> x_nodes = X_i(m);
    std::vector<double> y_nodes;

    // ��������� �������� ������� � �����
    for (double x : x_nodes)
    {
        y_nodes.push_back((2 / sqrt(pi)) * Sum(x));
    }

    // ����� �������� ������������ (11 �����)
    int testPoints = 10; // m = 10 ��� 11 �����
    std::vector<double> x_test = X_i(testPoints);

    std::cout << "����� ������������ (����):\n";
    for (size_t i = 0; i < x_nodes.size(); ++i)
    {
        std::cout << x_nodes[i] << ";" << y_nodes[i] << std::endl;
    }

    std::cout << "\n������� ������:\n";
    std::cout << "x;f(x);L(x);|f(x) - L(x)|\n";

    double max_error = 0.0;

    for (double x : x_test)
    {
        double f_x = (2 / sqrt(pi)) * Sum(x); // ������ �������� �������
        double L_x = LagrangePolynomial(x_nodes, y_nodes, x); // �������� ��������
        double abs_error = fabs(f_x - L_x); // ���������� ������

        if (abs_error > max_error)
        {
            max_error = abs_error;
        }

        // ����� � �������
        std::cout << x << ";" << abs_error << std::endl;

    }

    std::cout << "\n������������ ������ ������������: " << max_error << std::endl;

    // ����������� � ����������� ����� �����
    std::cout << "\n�����������: ����������� ������������ ������ �� ����� ����� (����������� ����)\n";
    std::cout << "����� �����\t������������ ������\n";

    for (int nodes = 2; nodes <= 45; ++nodes)
    {
        std::vector<double> exp_x_nodes = X_i(nodes);
        std::vector<double> exp_y_nodes;

        for (double x : exp_x_nodes)
        {
            exp_y_nodes.push_back((2 / sqrt(pi)) * Sum(x));
        }

        double exp_max_error = 0.0;
        for (double x : X_i(10)) // �������� ����� (11 �����)
        {
            double f_x = (2 / sqrt(pi)) * Sum(x);
            double L_x = LagrangePolynomial(exp_x_nodes, exp_y_nodes, x);
            double abs_error = fabs(f_x - L_x);

            if (abs_error > exp_max_error)
            {
                exp_max_error = abs_error;
            }
        }

        // ��������� ���� � ������� ������������
        if (exp_max_error > 0 && exp_max_error < 1)
        {
            std::cout << nodes + 1 << ";" << exp_max_error << std::endl;
        }
    }




    // ���� ��������
    int n = 5; // ���������� �����
    std::vector<double> chebyshev_nodes = X_i_Chebyshev(n);
    std::vector<double> chebyshev_y_nodes;

    // ��������� �������� ������� � ����� ��������
    for (double x : chebyshev_nodes)
    {
        chebyshev_y_nodes.push_back((2 / sqrt(pi)) * Sum(x));
    }

    std::cout << "\n����� ������������ (���� ��������):\n";
    for (size_t i = 0; i < chebyshev_nodes.size(); ++i)
    {
        std::cout << chebyshev_nodes[i] << ";" << chebyshev_y_nodes[i] << std::endl;
    }

    std::cout << "\n������� ������ ��� ����� ��������:\n";
    std::cout << "x;f(x);L(x);|f(x) - L(x)|\n";

    double chebyshev_max_error = 0.0;

    for (double x : X_i(10)) // ���������� 11 �������� �����
    {
        double f_x = (2 / sqrt(pi)) * Sum(x); // ������ �������� �������
        double L_x = LagrangePolynomial(chebyshev_nodes, chebyshev_y_nodes, x); // �������� ��������
        double abs_error = fabs(f_x - L_x); // ���������� ������

        if (abs_error > chebyshev_max_error)
        {
            chebyshev_max_error = abs_error;
        }

        // ����� � �������
        std::cout << x << ";" << abs_error << std::endl;
    }

    std::cout << "\n������������ ������ ������������ ��� ����� ��������: " << chebyshev_max_error << std::endl;

    // ����������� � ����������� ����� ����� ��������
    std::cout << "\n�����������: ����������� ������������ ������ �� ����� ����� (���� ��������)\n";
    std::cout << "����� �����\t������������ ������\n";

    for (int nodes = 2; nodes <= 45; ++nodes)
    {
        std::vector<double> exp_chebyshev_nodes = X_i_Chebyshev(nodes);
        std::vector<double> exp_chebyshev_y_nodes;

        for (double x : exp_chebyshev_nodes)
        {
            exp_chebyshev_y_nodes.push_back((2 / sqrt(pi)) * Sum(x));
        }

        double exp_chebyshev_max_error = 0.0;
        for (double x : X_i(10)) // �������� ����� (11 �����)
        {
            double f_x = (2 / sqrt(pi)) * Sum(x);
            double L_x = LagrangePolynomial(exp_chebyshev_nodes, exp_chebyshev_y_nodes, x);
            double abs_error = fabs(f_x - L_x);

            if (abs_error > exp_chebyshev_max_error)
            {
                exp_chebyshev_max_error = abs_error;
            }
        }

        // ��������� ���� � ������� ������������
        if (exp_chebyshev_max_error > 0 && exp_chebyshev_max_error < 1)
        {
            std::cout << nodes + 1 << ";" << exp_chebyshev_max_error << std::endl;
        }
    }


    return 0;

}
