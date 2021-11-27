
#include <iostream>
#include <vector>
#include "Hanoi.h"
#include <string>
#include <algorithm>

using namespace std;

string Hanoi::get_moves(int num_discs, int src, int dst, int tmp){
    string arrow = std::to_string(src) + "->" + std::to_string(dst) + "\n";
    
    if(num_discs == 0)
    {
        return "";
    }
    
    if(num_discs >= 1){
        if(lookup_moves(num_discs, src, dst) != ""){
            return lookup_moves(num_discs, src, dst);
        }
        
        string step = get_moves(num_discs-1, src, tmp, dst) + arrow + get_moves(num_discs-1, tmp, dst, src);
        if((int)_cache.size() < num_discs + 1){
            _cache.resize(num_discs + 1);
        }
        if((int)_cache[num_discs].size() < src + 1){
            _cache[num_discs].resize(src +1);
        }
        if((int)_cache[num_discs][src].size() < dst+1){
            _cache[num_discs][src].resize(dst+1);
        }
        _cache[num_discs][src][dst] = step;
        _cache[num_discs-1].clear();
        return step;
    }
    
    int total = 1;
    for(int i = 0; i < num_discs; i++){
        total = (total * 2);
    }
    
    return "";
};

string Hanoi::solve(int num_discs, int src, int dst, int tmp){

    string s = "# Below, 'A->B' means 'move the top disc on pole A to pole B'\n";
    return s + get_moves(num_discs, src, dst, tmp);
};

string Hanoi::lookup_moves(int num_discs, int src, int dst){
    if((int)_cache.size() < num_discs + 1){
        return "";
    }
    if((int)_cache[num_discs].size() < src + 1){
        return "";
    }
    if((int)_cache[num_discs][src].size() < dst + 1){
        return "";
    }
    return _cache[num_discs][src][dst];
};
