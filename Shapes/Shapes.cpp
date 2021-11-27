
#include <iostream>
#include "Shapes.h"
#include <sstream>
#include <vector>

using namespace std;

void Screen::fill(char c){
    for(int i=0; i<(int)get_h(); i++){
        for(int j=0; j<(int)get_w(); j++){
            _pix[i][j]=c;
        }
    }
}

string Screen::to_string() const{
    string ans = "";
    for(int i = (int)get_h()-1; i>=0; i--){
        for(int j=0;j<(int)get_w();j++){
            ans += _pix[i][j];
        }
        ans +="\n";
    }
    return ans;
}

bool Point::draw(Screen &screen, char c){
    if (_x >= screen.get_w() || _y >= screen.get_h()) {
        return false;
    }
    screen.get_pix()[_y][_x] = c;
    return true;
}

bool Line::draw_by_x(Screen &screen, char c, size_t x1, size_t y1, size_t x2, size_t y2){
    if(x1>x2){
        return draw_by_x(screen, c, x2, y2, x1, y1);
    }
    
    double b = ((double)y2-y1)/((double)x2-x1);
    bool contained = true;
    double x=x1, y=y1;
    
    while(x<=x2){
        contained &= Point ((size_t)x, (size_t)y).draw(screen,c);
        x+=1;
        y+=b;
    }
    
    return contained;
}

bool Line::draw_by_y(Screen &screen, char c, size_t x1, size_t y1, size_t x2, size_t y2){
    if(y1>y2){
        return draw_by_y(screen, c, x2, y2, x1, y1);
    }
    
    double b = ((double)x2-x1)/((double)y2-y1);
    bool contained = true;
    double x=x1, y=y1;
    
    while(y<=y2){
        contained &= Point ((size_t)x, (size_t)y).draw(screen,c);
        y+=1;
        x+=b;
    }
    
    return contained;
}

bool Line::draw(Screen &screen, char c){
    bool contained = true;
    if(abs((int)(_x2-_x1)) > abs((int)(_y2-_y1))){
        contained &= draw_by_x(screen, c, _x1, _y1, _x2, _y2);
    }
    else {
        contained &= draw_by_y(screen, c, _x1, _y1, _x2, _y2);
    }
    return contained;
}

bool Quadrilateral::draw(Screen &screen, char c){
    bool contained = true;
    contained &= Line(_x1,_y1,_x2,_y2).draw(screen,c);
    contained &= Line(_x2,_y2,_x3,_y3).draw(screen,c);
    contained &= Line(_x3,_y3,_x4,_y4).draw(screen,c);
    contained &= Line(_x4,_y4,_x1,_y1).draw(screen,c);
    return contained;
}

Stick_Man::Stick_Man(size_t x, size_t y, size_t w, size_t h){
    _parts.clear();
    if (h < 2) {
        h = DEFAULT_H;
    }
    if (w < 2){
        w = DEFAULT_W;
    }
    
    _x = x;
    _y = y;
    _w = w;
    _h = h;
    
    _parts.push_back(new Upright_Rectangle(x+0, y+h/2, x+w-1, y+h-1)); //head
    _parts.push_back(new Line(x+w/2,y+h/2,x+w/2,y+h/4)); //torso
    _parts.push_back(new Line(x+w/2,y+h/2,x+w/4,y+h/4)); //left arm
    _parts.push_back(new Line(x+w/2,y+h/2,x+3*w/4,y+h/4)); //right arm
    _parts.push_back(new Line(x+w/2,y+h/4,x,y)); //left leg
    _parts.push_back(new Line(x+w/2,y+h/4,x+w-1,y)); //right leg
}

bool Stick_Man::draw(Screen &screen, char c){
    bool contained = true;
    for(int i = 0; i<(int)_parts.size(); i++) {
        contained &= _parts[i]->draw(screen,c);
    }
    return contained;
}

Stick_Man::~Stick_Man(){
    for(int i=0; i<(int)_parts.size(); i++) {
        delete _parts[i];
    }
    _parts.clear();
}


