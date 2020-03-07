#ifndef JSON_H
#define JSON_H
#include<iostream>
using namespace std;

class json_class
{
    public:
        string json;
        unsigned int attributes;
        string attr[20][2];
        json_class()
        {
            json.push_back('{');
            attributes=0;
        }
        int operator ()(string,string);
        string operator [](string);
        void slice();
        void end();
};

#endif // JSON_H
