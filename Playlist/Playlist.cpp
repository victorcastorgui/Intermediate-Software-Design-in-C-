

#include <iostream>
#include <sstream>
#include <vector>

#include "Playlist.h"

using namespace std;

bool Playlist::Song_Entry::set_id(int id) {
    if (id < 0) {
        return false;
    }
    _id = id;
    return true;
}

bool Playlist::Song_Entry::set_name(string name){
    if (name == "") {
        return false;
    }
    _name = name;
    return true;
}

//1
Playlist::Playlist() {
    Song_Entry hed = Song_Entry(-1,"HEAD");
    Node *het = new Node(hed);
    _head = het;
    _tail = het;
    _prev_to_current = het;
    _size = 0;
}

//2
Playlist::~Playlist() {
    _size = 0;
    delete _head;
}


//3
Playlist *Playlist::insert_at_cursor(const Song_Entry &s) {
    _prev_to_current->insert_next(new Node(s));
    _size++;
    if (_prev_to_current == _tail) {
        _tail = _prev_to_current->get_next();
    }
    return this;
}

//4
Playlist *Playlist::push_back(const Song_Entry &s) {
    Node *simpen = _prev_to_current;
    _prev_to_current = _tail;
    insert_at_cursor(s);
    _prev_to_current = simpen;
    return this;
}

//5
Playlist *Playlist::push_front(const Song_Entry &s) {
    Node *simpen = _prev_to_current;
    _prev_to_current = _head;
    insert_at_cursor(s);
    _prev_to_current = simpen;
    return this;
}

//6
Playlist *Playlist::advance_cursor() {
    if (_prev_to_current == _tail) {
        return nullptr;
    }
    _prev_to_current = _prev_to_current->get_next();
    return this;
}

//7
Playlist *Playlist::circular_advance_cursor() {
    if (_prev_to_current->get_next() == _tail) {
        _prev_to_current = _head;
        return this;
    }
    _prev_to_current = _prev_to_current->get_next();
    return this;
}

//8
Playlist::Song_Entry& Playlist::get_current_song() const{
    if (_prev_to_current == _tail) {
        return this->_head->get_song();
    }
    return _prev_to_current->get_next()->get_song();;
}

//9
Playlist *Playlist::remove_at_cursor() {
    if (_prev_to_current == _tail) {
        return nullptr;
    }
    _prev_to_current->remove_next();
    _size--;
    return this;
}

//11
Playlist *Playlist::rewind() {
    _prev_to_current = _head;
    return this;
}

//12
Playlist *Playlist::clear() {
    while (_head->get_next() != nullptr) {
        _head->remove_next();
        _size--;
    }
    _prev_to_current = _head;
    _tail = _head;
    return this;
}

//13
Playlist::Song_Entry& Playlist::find_by_id(int id) const {
    Node *curr;
    curr = _head->get_next();
    while (curr != nullptr) {
        if (curr->get_song().get_id() == id) {
            return curr->get_song();
        }
        curr = curr->get_next();
    }
    return this->_head->get_song();
}

Playlist::Song_Entry& Playlist::find_by_name(string id) const {
    Node *curr;
    curr = _head->get_next();
    while (curr != nullptr) {
        if (curr->get_song().get_name() == id) {
            return curr->get_song();
        }
        curr = curr->get_next();
    }
    return this->_head->get_song();
}

string Playlist::to_string() const {
    string stringify = "Playlist: " + std::to_string(get_size()) + " entries.\n";
    Node *curr;
    curr = _head->get_next();
    size_t size = 0;
    
    if (get_size() < 25) {
        size = get_size();
    }
    else if (get_size() > 25) {
        size = 25;
    }
    
    for(int i = 0; i < (int)size; i++) {
        string theID = std::to_string(curr->get_song().get_id());
        string theName = curr->get_song().get_name();
        stringify += "{ id: " + theID + ", name: " + theName + " }";
        
        if (_prev_to_current == curr) {
            stringify += " [P]";
        }
        if (_tail == curr) {
            stringify += " [T]";
        }
        curr = curr -> get_next();
        stringify += "\n";
    }
    if(get_size() > 25){
        stringify += "...\n";
    }
    return stringify;
}



