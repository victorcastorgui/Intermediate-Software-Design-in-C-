
#ifndef Tree_h
#define Tree_h
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


class Tree {
private:
    struct Node { // Inner class
        std::string _data;
        Node *_sibling, *_child;
        static bool is_equal(const Node *p1, const Node *p2);
    
        Node(std::string s = "") {
            _data = s;
            _child = nullptr;
            _sibling = nullptr;
        }
        Node(const Node& that);
        const Node& operator=(const Node& that); //Deep clone
        ~Node();
    
        std::string get_data() const { return _data; }
        void set_data(std::string s) { _data = s; }
    
        Node *insert_sibling(Node *p);
        Node *insert_child(Node *p);
        
        void set_child(Node *p){_child = p;}
        void set_sibling(Node *p){_sibling = p;}
        
        Node *get_sibling(){return _sibling;}
        Node *get_child(){return _child;}
        
        std::string to_string() const;
    
        bool operator==(const Node& that) const;
        bool operator!=(const Node& that) const;
    };
    
    Node *_root;
    
public:
    Tree();
    ~Tree();
    
    Tree(const Tree& that) {
        _root = new Node("");
        *this = that; }
    Tree& operator=(const Tree& that); // Deep clone
    
    std::string to_string() const;
    void make_special_config_1(const std::vector<std::string>& names);
    
    bool operator==(const Tree& that) const;
    bool operator!=(const Tree& that) const;
    friend std::ostream& operator<<(std::ostream& os, const Tree& tree){
        os<<tree.to_string();
        return os;
    };
    friend class Tests; // Don't remove this line
};

#endif /* Tree_h */
