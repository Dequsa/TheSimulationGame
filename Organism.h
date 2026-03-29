//
// Created by Kacper Marciniak on 3/11/26.
//

#ifndef C__1_ORGANISM_H
#define C__1_ORGANISM_H
#include <vector>
#include <memory>
#pragma once

class Organism {
private:
    std::vector<int> pos_;
    int str_;
    int init_;
    std::unique_ptr<int> world_;
    public:
    Organism() = default;
    Organism( const int &str, const int &init, const std::vector<int>& pos);
    Organism(const Organism& org);
    virtual ~Organism() = default;
    virtual void Update() = 0;
    // organism getters
    std::vector<int> GetPosition() const;
    int GetStr();
    int GetInit();
};

#endif //C__1_ORGANISM_H