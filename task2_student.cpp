#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

class Student {
private:
    string surnameInitials;
    string group;
    array<int, 5> grades{};

public:
    Student() = default;

    void input() {
        cout << "Прізвище та ініціали: ";
        getline(cin >> ws, surnameInitials);
        cout << "Група: ";
        getline(cin, group);
        cout << "Введіть 5 оцінок: ";
        for (int &grade : grades) cin >> grade;
    }

    double average() const {
        double sum = 0;
        for (int grade : grades) sum += grade;
        return sum / grades.size();
    }

    bool hasOnlyFourAndFive() const {
        for (int grade : grades) {
            if (grade != 4 && grade != 5) return false;
        }
        return true;
    }

    void print() const {
        cout << left << setw(24) << surnameInitials
             << setw(10) << group
             << "середній бал: " << fixed << setprecision(2) << average() << '\n';
    }
};

int main() {
    const int N = 5;
    vector<Student> students(N);

    cout << "Введення даних про 5 студентів\n";
    for (int i = 0; i < N; ++i) {
        cout << "\nСтудент " << i + 1 << ":\n";
        students[i].input();
    }

    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) {
             return a.average() < b.average();
         });

    cout << "\nСтуденти за зростанням середнього бала:\n";
    for (const Student& s : students) s.print();

    cout << "\nСтуденти, які мають тільки оцінки 4 або 5:\n";
    bool found = false;
    for (const Student& s : students) {
        if (s.hasOnlyFourAndFive()) {
            s.print();
            found = true;
        }
    }
    if (!found) cout << "Таких студентів немає.\n";

    return 0;
}
