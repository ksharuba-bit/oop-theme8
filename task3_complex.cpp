#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>

using namespace std;

class Complex {
private:
    double re;
    double im;

public:
    Complex(double r = 0.0, double i = 0.0) : re(r), im(i) {}

    Complex add(const Complex& other) const {
        return Complex(re + other.re, im + other.im);
    }

    Complex subtract(const Complex& other) const {
        return Complex(re - other.re, im - other.im);
    }

    Complex multiply(const Complex& other) const {
        return Complex(re * other.re - im * other.im,
                       re * other.im + im * other.re);
    }

    Complex divide(const Complex& other) const {
        double d = other.re * other.re + other.im * other.im;
        if (d == 0.0) throw runtime_error("Ділення на нуль неможливе");
        return Complex((re * other.re + im * other.im) / d,
                       (im * other.re - re * other.im) / d);
    }

    Complex conjugate() const {
        return Complex(re, -im);
    }

    Complex power(int n) const {
        double r = hypot(re, im);
        double phi = atan2(im, re);
        if (n < 0 && r == 0.0) throw runtime_error("Нуль не можна піднести до від'ємного степеня");
        double rn = pow(r, n);
        return Complex(rn * cos(n * phi), rn * sin(n * phi));
    }

    Complex squareRoot() const {
        double r = hypot(re, im);
        double realPart = sqrt((r + re) / 2.0);
        double imagPart = (im >= 0 ? 1 : -1) * sqrt((r - re) / 2.0);
        return Complex(realPart, imagPart);
    }

    void print() const {
        cout << fixed << setprecision(3) << re;
        if (im >= 0) cout << " + " << im << "i";
        else cout << " - " << -im << "i";
    }
};

int main() {
    double a, b, c, d;
    int n;

    cout << "Введіть дійсну та уявну частини z1: ";
    cin >> a >> b;
    cout << "Введіть дійсну та уявну частини z2: ";
    cin >> c >> d;
    cout << "Введіть цілий степінь n: ";
    cin >> n;

    Complex z1(a, b), z2(c, d);

    cout << "\nz1 + z2 = "; z1.add(z2).print();
    cout << "\nz1 - z2 = "; z1.subtract(z2).print();
    cout << "\nz1 * z2 = "; z1.multiply(z2).print();

    try {
        cout << "\nz1 / z2 = "; z1.divide(z2).print();
        cout << "\nz1^" << n << " = "; z1.power(n).print();
    } catch (const exception& e) {
        cout << "\nПомилка: " << e.what();
    }

    cout << "\nСпряжене до z1 = "; z1.conjugate().print();
    cout << "\nКвадратний корінь із z1 = "; z1.squareRoot().print();
    cout << '\n';

    return 0;
}
