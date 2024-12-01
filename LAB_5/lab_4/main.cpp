#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

class Complex final
{
private: // те можно обраться только внутри методов класса
    double real;
    double imaginary;

public:
    // Конструктор с параметрами по умолчанию
    explicit Complex(double re = 0, double im = 0) : real(re), imaginary(im) {}

    // метод для сложения
    Complex add(const Complex &other)
    {
        return Complex(real + other.real, imaginary + other.imaginary);
    }

    // метод для вычитания//второй конст
    Complex subtract(const Complex &other) // объект,переданный в метод, не мб изменен внутри метода,
    {
        return Complex(real - other.real, imaginary - other.imaginary);
    }

    // метод для умножения
    Complex multiply(const Complex &other)
    {
        return Complex(real * other.real - imaginary * other.imaginary,
                       real * other.imaginary + imaginary * other.real);
    }

    // метод для деления
    Complex divide(const Complex &other)
    {
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        const double eps = 1e-10;
        if (std::abs(denominator) < eps)
        {
            throw std::invalid_argument("Division by zero.");
        }
        return Complex((real * other.real + imaginary * other.imaginary) / denominator,
                       (imaginary * other.real - real * other.imaginary) / denominator);
    }

    // метод для получения модуля
    double modulus() const
    {
        return std::sqrt(real * real + imaginary * imaginary);
    }

    // метод для получения аргумента//угол
    double argument() const
    {
        return std::atan2(imaginary, real) * 180.0 / M_PI;
    }

    // метод для вывода числа
    void print() const
    {
        std::cout << real << (imaginary >= 0 ? " + " : " - ")
                  << std::abs(imaginary) << "i";
    }
};

void demo()
{
    using namespace std;
    try
    {                      // два объекта класса complex
        Complex c1(3, 4);  // 3+4i
        Complex c2(1, -2); // 1−2i

        cout << "Complex numbers:\n";
        cout << "c1: ";
        c1.print();
        cout << "\nc2: ";
        c2.print();
        cout << "\n\n";
        // методы
        Complex sum = c1.add(c2);
        Complex diff = c1.subtract(c2);
        Complex prod = c1.multiply(c2);
        Complex quot = c1.divide(c2);

        cout << "Operations:\n";
        cout << "Sum: ";
        sum.print();
        cout << "\nSubtraction: ";
        diff.print();
        cout << "\nMultiplication: ";
        prod.print();
        cout << "\nDivision: ";
        quot.print();
        cout << "\n\n";

        cout << "c1 modulus: " << c1.modulus() << "\n";
        cout << "c2 modulus: " << c2.modulus() << "\n";
        cout << "c1 argument: " << c1.argument() << " degrees\n";
        cout << "c2 argument: " << c2.argument() << " degrees\n";
    }
    catch (std::exception const &err) // err представляет объект искл
    {
        std::cout << "Error: " << err.what() << std::endl;
    }
}

int main()
{
    demo();
    return 0;
}
