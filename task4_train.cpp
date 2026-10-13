#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

class Train {
private:
    string destination;
    int number{};
    string departureTime;

    int timeInMinutes() const {
        int h = stoi(departureTime.substr(0, 2));
        int m = stoi(departureTime.substr(3, 2));
        return h * 60 + m;
    }

public:
    Train() = default;

    void input() {
        cout << "Пункт призначення: ";
        getline(cin >> ws, destination);
        cout << "Номер поїзда: ";
        cin >> number;
        cout << "Час відправлення (HH:MM): ";
        cin >> departureTime;
    }

    const string& getDestination() const { return destination; }
    int getNumber() const { return number; }
    int getTimeInMinutes() const { return timeInMinutes(); }

    void print() const {
        cout << left << setw(20) << destination
             << setw(12) << number
             << departureTime << '\n';
    }
};

int main() {
    const int N = 5;
    vector<Train> trains(N);

    cout << "Введення даних про 5 поїздів\n";
    for (int i = 0; i < N; ++i) {
        cout << "\nПоїзд " << i + 1 << ":\n";
        trains[i].input();
    }

    sort(trains.begin(), trains.end(),
         [](const Train& a, const Train& b) {
             return a.getNumber() < b.getNumber();
         });

    cout << "\nСписок за зростанням номерів поїздів:\n";
    for (const Train& t : trains) t.print();

    string query;
    cout << "\nВведіть пункт призначення для пошуку: ";
    getline(cin >> ws, query);

    cout << "\nПоїзди до пункту \"" << query << "\":\n";
    bool found = false;
    for (const Train& t : trains) {
        if (t.getDestination() == query) {
            t.print();
            found = true;
        }
    }
    if (!found) cout << "Поїздів не знайдено.\n";

    sort(trains.begin(), trains.end(),
         [](const Train& a, const Train& b) {
             if (a.getDestination() != b.getDestination())
                 return a.getDestination() < b.getDestination();
             return a.getTimeInMinutes() < b.getTimeInMinutes();
         });

    cout << "\nСписок за пунктами призначення і часом відправлення:\n";
    for (const Train& t : trains) t.print();

    return 0;
}
