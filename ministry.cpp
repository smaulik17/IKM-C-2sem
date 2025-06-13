//ministry.cpp
#include "ministry.h"
#include <algorithm>
#include <limits>

using namespace std;

Official::Official(int id, int bribe) : Id(id), Bribe(bribe) {}

//возвращает id чиновника
int Official::GetId() const { return Id; }

//устанавливает чиновника как главного
void Official::SetHead() { IsHead = true; }

//проверяет является ли чиновник главным
bool Official::GetHead() const { return IsHead; }

//добавляет подчиненного
void Official::AddSubordinate(Official* subordinate) {
    Subordinates.push_back(subordinate);
}

//вычисляет минимальную взятку и путь подписей
pair<int, vector<int>> Official::CalculateMinBribe() const {
    if (Subordinates.empty()) {
        return {Bribe, {Id}};
    }

    if (IsHead) {
        int minBribe = numeric_limits<int>::max();
        vector<int> bestPath;

        for (int i = 1; i < (1 << Subordinates.size()); ++i) {
            int currentBribe = 0;
            vector<int> currentPath;

            for (int j = 0; j < Subordinates.size(); ++j) {
                if ((i >> j) & 1) {
                    auto subResult = Subordinates[j]->CalculateMinBribe();
                    currentBribe += subResult.first;
                    currentPath.insert(currentPath.end(), subResult.second.begin(), subResult.second.end());
                }
            }

            currentBribe += Bribe;
            currentPath.push_back(Id);

            if (currentBribe < minBribe) {
                minBribe = currentBribe;
                bestPath = currentPath;
            }
        }

        return {minBribe, bestPath};
    } else {
        int option1 = Bribe;
        vector<int> path1 = {Id};

        int option2 = 0;
        vector<int> path2;

        for (Official* sub : Subordinates) {
            auto subResult = sub->CalculateMinBribe();
            option2 += subResult.first;
            path2.insert(path2.end(), subResult.second.begin(), subResult.second.end());
        }

        return (option1 < option2) ? make_pair(option1, path1) : make_pair(option2, path2);
    }
}

//очищает память от чиновников
Ministry::~Ministry() {
    for (Official* official : Officials) {
        delete official;
    }
}

//добавляет нового чиновника
void Ministry::AddOfficial(int id, int bribe) {
    Official* newOfficial = new Official(id, bribe);
    Officials.push_back(newOfficial);

    if (!Head) {
        Head = newOfficial;
        Head->SetHead();
    }
}

//устанавливает иерархию подчинения
void Ministry::SetHierarchy(int bossId, int subordinateId) {
    Official* boss = FindOfficial(bossId);
    Official* subordinate = FindOfficial(subordinateId);

    if (!boss || !subordinate) {
        throw invalid_argument("Неверные ID чиновников");
    }

    boss->AddSubordinate(subordinate);
}

//находит чиновника по id
Official* Ministry::FindOfficial(int id) const {
    for (Official* official : Officials) {
        if (official->GetId() == id) {
            return official;
        }
    }
    return nullptr;
}

//вычисляет и выводит решение
void Ministry::CalculateAndPrintSolution() {
    if (!Head) {
        cout << "В министерстве нет чиновников!" << endl;
        return;
    }

    auto result = Head->CalculateMinBribe();

    cout << "\n=== Результаты расчета ===" << endl;
    cout << "Минимальная сумма взяток: " << result.first << " у.е." << endl;
    cout << "Оптимальный порядок получения подписей: ";

    for (int id : result.second) {
        cout << id << " ";
    }

    cout << "\n==========================" << endl;
}