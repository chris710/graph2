#ifndef EXCEPTION_H
#define EXCEPTION_H


#include<iostream>
#include<string>
#include<exception>

using namespace std;

class Cyclicgraphexception: public exception
{
public:
    const char* what() const throw()
    {
        return "Graf zawiera cykl!!!";
    }
};

#endif // EXCEPTION_H