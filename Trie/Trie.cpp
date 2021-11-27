

#include <iostream>
#include "Trie.h"
#include <queue>

using namespace std;;

Trie::Trie(){
    _root = new Node;
    return;
}

void Trie::Node::insert(string s){
    Trie::Node* curr = this;
    for(const char *str = s.c_str(); *str; str++){
        char ch = *str;
        if(curr->next.size() < (size_t)ch+1) {
            curr->next.resize((size_t)ch+1);
        }
        if(curr->next[ch] != nullptr){
            curr = curr ->next[ch];
        }else{
            curr = curr->next[ch]=new Trie::Node;
        }
    }
    if(curr->next.size()==0){
        curr->next.resize(1);
    }
    curr->next[0] = new Trie::Node;
}

bool Trie::Node::lookup(string s) const{
    const Trie::Node* temp = traverse(s);
    return (temp != nullptr && temp->next[0] != nullptr);
}

Trie::~Trie(){
    delete _root;
}

Trie::Node::~Node(){
}

size_t Trie::get_completions(std::string s, std::vector<std::string> &completions, size_t limit) const{
    const Trie::Node* tired = _root->traverse(s);
    completions.clear();
    if(tired!=nullptr){
        tired->get_completions(completions, limit);
    }
    return completions.size();
}

size_t Trie::trie_sort(vector<string>& vec) const{
    return get_completions("", vec, 2000000000);
}
