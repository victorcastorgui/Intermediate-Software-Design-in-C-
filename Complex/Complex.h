
#include <cmath>
#include <math.h>
#include <exception>
#include <iostream>
#pragma once
#ifndef Header_h
#define Header_h


using namespace std;

class Complex{
private:
    double _real, _imag;
    
public:
    static constexpr double FLOOR = 1e-10; // Threshold

    Complex(double re=0.0, double im=0.0): _real(re), _imag(im){};
    double get_real() const { return _real;}
    double get_imag() const { return _imag;}
    void set_real(double re) {_real=re;}
    void set_imag(double im) {_imag=im;}
    
    std::string to_string()const{
        char buf[69];
        sprintf(buf, "(%.11g,%.11g)", _real, _imag);
        return string(buf);
    };
    
    double norm_squared() const {return _real * _real + _imag * _imag;}
    double norm() const {return sqrt(norm_squared());}
    
    Complex reciprocal() const{
        if (norm_squared() <= FLOOR) // watch for round-off
            throw Div_By_Zero_Exception();
        return Complex(get_real()/norm_squared(), -get_imag()/norm_squared());
    }
    
    Complex& operator=(const Complex & rhs){
        this->_real = rhs._real;
        this->_imag = rhs._imag;
        return *this;
    };
        
    class Div_By_Zero_Exception{
    public:
        std::string to_string(){return "Divide by zero exception";};
        std::string what(){return to_string();};
    };

    Complex operator+(const Complex& that)const{
        Complex total;
        total._real= _real+ that._real;
        total._imag= _imag+ that._imag;
        return total;
    }

    Complex operator-(const Complex& that)const{
        Complex total;
        total._real= _real-that._real;
        total._imag= _imag-that._imag;
        return total;
    }

    Complex operator*(const Complex& that)const{
        Complex total;
        total._real= _real * that._real - _imag * that._imag;
        total._imag= _imag * that._real + _real * that._imag;
        return total;
    }

    Complex operator/(const Complex& that)const{
        //return Complex((this->get_real() * that.get_real() + this->get_imag() * that.get_imag()) / (that.get_real() * that.get_real() + that.get_imag() * that.get_imag()), (this->get_imag() * that.get_real() - this->get_real() * that.get_imag()) / (that.get_real() * that.get_real() + that.get_imag() * that.get_imag()));
        return (*this)*that.reciprocal();
    }

    bool operator==(const Complex& that)const{
        if(abs(this->get_real() - that.get_real()) > FLOOR){
            return false;
        }
        if(abs(this->get_imag() - that.get_imag()) > FLOOR){
            return false;
        }
        return true;
    };

    bool operator!=(const Complex& that)const {return !(*this==that);}

    bool operator<(const Complex& that)const {return this->norm()<that.norm();}

    friend std::ostream& operator<<(ostream& os, const Complex& x){
        os << x.to_string();
        return os;
    };

    friend class Tests; // Don't remove this line
};

#endif /* Header_h */
