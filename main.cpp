//main.cpp
#include <iostream>
#include "ministry.h"
#include <stdexcept>

using namespace std;

int main() {
    try {
        Ministry ministry;

        cout << "=== Система оптимизации взяток в министерстве ===" << endl;
        cout << "Введите количество чиновников: ";

        int n;
        cin >> n;

        if (n <= 0) {
            throw invalid_argument("Количество чиновников должно быть положительным числом");
        }

        cout << "Введите размеры взяток для каждого чиновника (через пробел): ";

        for (int i = 1; i <= n; ++i) {
            int bribe;
            cin >> bribe;

            if (bribe < 0) {
                throw invalid_argument("Размер взятки не может быть отрицательным");
            }

            ministry.AddOfficial(i, bribe);
        }

        cout << "\nТеперь введите иерархию подчинения." << endl;
        cout << "Формат: [ID начальника] [ID подчиненного]" << endl;
        cout << "Пример: 1 2 означает что чиновник 1 - начальник чиновника 2" << endl;
        cout << "Для завершения ввода введите -1:\n";

        int boss, sub;
        while (true) {
            cout << "> ";
            cin >> boss;

            if (boss == -1) {
                break;
            }

            cin >> sub;
            ministry.SetHierarchy(boss, sub);
        }

        ministry.CalculateAndPrintSolution();
    }
    catch (const exception& e) {
        cerr << "\n[ОШИБКА] " << e.what() << endl;
        cerr << "Программа завершена с ошибкой." << endl;
        return 1;
    }

    cout << "\nРасчет завершен успешно. Нажмите Enter для выхода...";
    cin.ignore();
    cin.get();

    return 0;
}