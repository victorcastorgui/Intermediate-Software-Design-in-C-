
#include <iostream>
#include "Automaton.h"
#include <vector>

size_t Automaton::translate_n_bits_starting_at(const vector<int>& bits, size_t pos, size_t n){
    size_t ans = 0;
    size_t b = 0;
    for(int i = (int)pos+(int)n-1; i >= (int)pos; i--){
        if(n == 0 || i > (int)bits.size()-1)
            return 0;
        ans += bits[i]*pow_2(b);
        b++;
    }
    return ans;
}

string Automaton::generation_to_string(const vector<int>& gen, size_t width){
    string str = "";
    
    if(_is_valid == false){
        return "";
    }
    
    
    for(int i = 0; i< (int)gen.size(); i++){
        if(gen[i]==0){
            str += " ";
        }
        if(gen[i]==1){
            str += '*';
        }
    }
    
    if((int)width % 2 == 0){
        return "";
    }
    
    if (gen.size() < width){
        int pad = (int)width-(int)gen.size();
        string extremeBit = "";
        for(int i = 0; i < (int)(pad/2); i++){
            if(_extreme_bit == 1){
                extremeBit += "*";
            }
            else if(_extreme_bit == 0){
                extremeBit += " ";
                
            }
        }
        str = extremeBit + str + extremeBit;
    }
    
    if(width < gen.size()){
        string deleteSide = "";
        int extras = ((int)gen.size()-(int)width)/2;
        for(int i = (int)extras; i <= (int)str.length()-extras-1; i++){
            deleteSide += str[i];
        }
        str = deleteSide;
    }
    return str;
}

bool Automaton::set_rule(size_t rule){
    _rules.resize(pow_2(_num_parents));
    size_t max_rule = pow_2(pow_2(_num_parents))-1;
    
    if(_num_parents < 0 || _num_parents > MAX_PARENTS || rule > max_rule)
    {
        return false;
    }
    
    for(size_t i=0; i <= pow_2(_num_parents); i++){
        _rules[i] = (1<<i)&rule;
    }
    _is_valid = true;
    
    return true;
}

Automaton::Automaton(size_t num_parents, size_t rule){
    _num_parents = num_parents;
    _extreme_bit = 0;
    if(!set_rule(rule)){
        _is_valid = false;
    }
    return;
}

bool Automaton::equals(const Automaton &that){
    if(_is_valid ==false && that._is_valid==false){
        return true;
    }
    if(_extreme_bit == that._extreme_bit && _rules == that._rules && _num_parents == that._num_parents && _is_valid == true && that._is_valid == true){
        return true;
    }
    return false;
}

bool Automaton::make_next_gen(const vector<int> &current_gen, vector<int> &next_gen){
    
    if(current_gen.size()%2==0 && current_gen.size() != 0){
        return false;
    }
    
    if(_is_valid==false){
        return false;
    }
    
    if(current_gen.size() == 0){
        next_gen.resize(0);
        next_gen.push_back(1);
        return true;
    }
    
    
    
    vector<int> extremeBitsAdd;
    size_t keepSize = current_gen.size() + _num_parents - 1;
    for(int i = 0; i < (int)_num_parents-1; i++){
        extremeBitsAdd.push_back(_extreme_bit);
    }
    for(int i = 0; i < (int)current_gen.size(); i++){
        extremeBitsAdd.push_back(current_gen[i]);
    }
    for(int i = 0; i < (int)_num_parents-1; i++){
        extremeBitsAdd.push_back(_extreme_bit);
    }
    next_gen.resize(keepSize);
    for(int i = 0; i < (int)keepSize; i++){
        size_t translate = translate_n_bits_starting_at(extremeBitsAdd, i, _num_parents);
        if(_rules[translate]==true){
            next_gen[i] = 1;
        }
        if(_rules[translate]==false){
            next_gen[i] = 0;
        }
    }
    if(_extreme_bit == 0){
        _extreme_bit = _rules[0];
    }
    else if(_extreme_bit == 1){
        _extreme_bit = _rules[_rules.size()-1];
    }
    
    return true;
}

string Automaton::get_first_n_generations(size_t n, size_t width){
    string gg = "";
  //  vector<int> firstGen = {0,0,0,0,1,0,0,0,0};
//    vector<int> nextGen;
//    for(int i=1; i < (int)firstGen.size() - 1; i++){
//        make_next_gen(firstGen, nextGen);
//    }
//    generation_to_string(nextGen, width);
//    if(width == 0 || width%2 == 0 ){
//        return "";
//    }
//    string templet = " * \n *** \n *** \n*****\n* * *\n";
    return "*";
}



//
