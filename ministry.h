//ministry.h
#ifndef MINISTRY_H
#define MINISTRY_H

#include <iostream>
#include <vector>
#include <stdexcept>

//класс представляющий чиновника
class Official {
private:
    int Id;
    int Bribe;
    std::vector<Official*> Subordinates;
    bool IsHead = false;

public:
    Official(int id, int bribe);
    int GetId() const;
    void SetHead();
    bool GetHead() const;
    void AddSubordinate(Official* subordinate);
    std::pair<int, std::vector<int>> CalculateMinBribe() const;
};

//класс представляющий министерство
class Ministry {
private:
    std::vector<Official*> Officials;
    Official* Head = nullptr;

public:
    ~Ministry();
    void AddOfficial(int id, int bribe);
    void SetHierarchy(int bossId, int subordinateId);
    Official* FindOfficial(int id) const;
    void CalculateAndPrintSolution();
};

#endif // MINISTRY_H