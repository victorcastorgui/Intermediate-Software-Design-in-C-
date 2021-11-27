
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

#pragma once

#ifndef Trie_h
#define Trie_h

class Trie{
private:
    struct Node{
        std::vector<Trie::Node *> next;
        
        ~Node();
        
        void insert(std::string s);
        
        const Node* traverse(std::string s) const{
           const Node* curr = this;
            for(char c:s){
                if(curr->next.size() <= (size_t)c){
                    return nullptr;
                }
                if(curr->next[c] == nullptr){
                    return nullptr;
                }
                curr = curr->next[c];
            }
            return curr;
        }
        
        bool lookup(std::string s) const;
        size_t get_completions(std::vector<std::string>& completions, size_t limit) const{
            struct Continuation {
                const Node *node;
                std::string partial;
                Continuation(const Node *p, std::string s) : node(p), partial(s) {}
            };
            //All string descendants of this node are completions
            std::queue<Continuation> unprocessed_nodes;
            //masukin first one, terus di ->next
            unprocessed_nodes.push(Continuation(this, ""));
            completions.clear();
            while (!unprocessed_nodes.empty()) {
                Continuation cont = unprocessed_nodes.front();
                if(cont.node->next[0] != nullptr && completions.size() < limit){
                    completions.push_back(cont.partial);
                }
                unprocessed_nodes.pop();
                //loop push, queue baru
                std::string keep = "";
                for (int i = 1; i < (int)(cont.node->next.size()); i++){
                    if (cont.node->next[i] != nullptr) {
                        keep = cont.partial + (char)i;
                        unprocessed_nodes.push(Continuation(cont.node->next[i], keep));
                    }
                }
            }
            return completions.size();
        }
    } *_root;
    
    // Private Trie:: helper. Returns the interior node traversing s from _root
    const Node *traverse(std::string s) const{
        return _root->traverse(s);
    }

public:
    Trie();
    ~Trie();
    
    void insert(std::string s){
        _root->insert(s);
    }
    bool lookup(std::string s) const{
        return _root->lookup(s);
    }
    size_t get_completions(std::string s, std::vector<std::string>& completions, size_t limit) const;
    size_t trie_sort(std::vector<std::string>& vec) const;
    
    std::string to_string(size_t n) const{
        std::string temp = "# Trie contents\n";
        std::vector<std::string> output;
        size_t demSize = get_completions("",output, n);
        for(size_t i=0; i<demSize; i++){
            temp += output[i] + "\n";
        }
        if(get_completions("", output, n+1) == n+1){
            temp += "...\n";
        }
        return temp;
    };
    
    std::ostream& operator<<(std::ostream& os){
        return os << to_string(100);
    };
    
    friend class Tests; // Don't remove
    
};


#endif /* Trie_h */
