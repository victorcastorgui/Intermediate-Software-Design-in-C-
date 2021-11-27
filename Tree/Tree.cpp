

#include "Tree.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <iostream>
#pragma once

using namespace std;

Tree::Node *Tree::Node::insert_sibling(Node *p){
    Node* sib = this;
    while(sib -> get_sibling() != nullptr){
        sib = sib -> get_sibling();
    }
    sib->set_sibling(p);
    return p;
}

Tree::Node *Tree::Node::insert_child(Node *p){
    if(get_child()!=nullptr){
        get_child()->insert_sibling(p);
    }
    else{
        _child = p;
    }
    return p;
}

const Tree::Node& Tree::Node::operator=(const Tree::Node &that){
    if (this != &that) {
        _data = that._data;
        Tree::Node* thatChild = that._child;
        Tree::Node* thatSibling = that._sibling;
        if(thatChild!=nullptr){
            Node* temp = new Node(*thatChild);
            insert_child(temp);
        }
        if(thatSibling!= nullptr){
            Node* temp = new Node(*thatSibling);
            insert_sibling(temp);
        }
    }
    return *this;
}

Tree::Node::Node(const Tree::Node &that){
    _data = "";
    _child = nullptr;
    _sibling = nullptr;
    *this = that;
    return;
}

bool Tree::Node::is_equal(const Tree::Node *p1, const Tree::Node *p2){
    if(p1->get_data() == p2->get_data()){
        return true;
    }
    return false;
}

bool Tree::Node::operator==(const Node &that) const{
    if(is_equal(this, &that)==false){
        return false;
    }
    if(_sibling != nullptr && that._sibling!=nullptr){
        if(*_sibling != *that._sibling){
            return false;
        }
    }
    if(_child != nullptr && that._child!=nullptr){
        if(*_child != *that._child){
            return false;
        }
    }
    if((_child == nullptr && that._child != nullptr) || (_child != nullptr && that._child == nullptr)){
        return false;
    }
    if((_sibling == nullptr && that._sibling != nullptr)|| (_sibling != nullptr && that._sibling == nullptr)){
        return false;
    }
    return true;
}

bool Tree::Node::operator!=(const Node &that) const{
    if(*this == that){
        return false;
    }
    return true;
}

string Tree::Node::to_string() const{
    string tmp = this->get_data() + " " + ":";
    Tree::Node* node =this->_child;
    while(node != nullptr){
        tmp += " " + node->get_data();
        node = node ->get_sibling();
    }
    tmp += "\n";
    
    Tree::Node* child = this -> _child;
    if(child != nullptr){
        tmp += "# Child of " + get_data() + "\n";
        tmp += _child -> to_string();
    }
    Tree::Node* sibling = this -> _sibling;
    if(sibling != nullptr){
        tmp += "# Next sib of " + get_data() + "\n";
        tmp += _sibling -> to_string();
    }
    return tmp;
}

Tree::Node::~Node(){
    _child = nullptr;
    _sibling = nullptr;
    _data = "";
    delete _child;
    delete _sibling;
}

Tree::Tree(){
    _root = new Node("ROOT");
}

Tree::~Tree(){
    _root=nullptr;
    delete _root;
}

Tree& Tree::operator=(const Tree& that){
    if(this != &that){
        *(_root) = *(that._root);
    }
    return *this;
}

bool Tree::operator==(const Tree& that) const{
    if(*_root != *(that._root)){
        return false;
    }
    return true;
}

bool Tree::operator!=(const Tree& that) const{
    if(*this == that){
        return false;
    }
    return true;
}

string Tree::to_string() const{
    string tmp = "# Tree rooted at " + _root->get_data() + "\n";
    tmp += "# The following lines are of the form:\n";
    tmp += "#   node: child1 child2...\n";
    tmp += _root->to_string();
    tmp += "# End of Tree\n";
    return tmp;
}

void Tree::make_special_config_1(const vector<string>& names){
};




