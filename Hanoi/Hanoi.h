
#ifndef Hanoi_h
#define Hanoi_h
#include <vector>
#include <string>
#pragma once

using namespace std;

class Hanoi {
private:
    int _num_poles;
    int _num_discs;
    std::vector<vector<vector<string>>> _cache;

    std::string lookup_moves(int num_discs, int src, int dst);
    std::string get_moves(int num_discs, int src, int dst, int tmp);
public:
// Use freebie default constructor
    
    std::string solve(int num_discs, int src, int dst, int tmp);
    friend class Tests; // Don't remove this line
};

#endif /* Hanoi_h */
