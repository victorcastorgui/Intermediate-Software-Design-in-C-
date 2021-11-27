
#include <sstream>
#include <iostream>
#include <vector>
#pragma once

using namespace std;

class Playlist {
public:
    // Inner public class ---------------------------------------------------
    // The client can refer to it by using the qualified name Playlist::Song_Entry
    class Song_Entry {
    private:
        int _id;
        string _name;
        
    public:
        Song_Entry(int id = 0, string name = "Unnamed")
            : _id(id), _name(name) {}
        int get_id() const { return _id; }
        string get_name() const { return _name; }
        
        bool set_id(int id);
        bool set_name(string name);
        
        bool operator==(const Song_Entry& that) {
            return this->_id == that._id && this->_name == that._name;
        }
        bool operator!=(const Song_Entry& that) {
            return !(*this == that);
        }
            
        friend std::ostream& operator<<(ostream& os, const Song_Entry& s) {
            return os << "{ id: "<< s.get_id() << ", name: " << s.get_name() << " }";
        }
        friend class Tests; // Don't remove this line
    };
    
private:
    // This is going to be our inner private class. The client doesn't need to
    // know.
    class Node {
    private:
        Song_Entry _song;
        Node *_next;
    public:
        Node(const Song_Entry& song = Song_Entry()) : _song(song), _next(nullptr) {}
        ~Node(){}
            // Do not do recursive free
        Song_Entry& get_song() { return _song; }
        Node *get_next() { return _next; }
        Node *insert_next(Node *p) {
            p->_next = _next;
            _next = p;
            return p;
        }
        Node *remove_next() {
            Node *keep = _next;
            _next = _next->_next;
            if (keep == nullptr) delete keep;
            return this;
        }
        
        friend class Tests; // Don't remove this line
    };

private:
    Node *_head, *_tail, *_prev_to_current;
    size_t _size;

public:
    Playlist();
    ~Playlist();
    size_t get_size() const { return _size; }
    Song_Entry& get_current_song() const;
    
    // The following return "this" on success, null on failure. See the spec
    // for why.
    
    Playlist *clear();
    Playlist *rewind();
    Playlist *push_back(const Song_Entry& s);
    Playlist *push_front(const Song_Entry& s);
    Playlist *insert_at_cursor(const Song_Entry& s);
    Playlist *remove_at_cursor();
    Playlist *advance_cursor();
    Playlist *circular_advance_cursor();
    
    // The following return the target payload (or sentinel) reference on success
    Song_Entry& find_by_id(int id) const;
    Song_Entry& find_by_name(string songName) const;
    
    string to_string() const;
    
    friend class Tests; // Don't remove this line
};

