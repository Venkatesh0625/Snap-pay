#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "datime.h"
#include "basic.h"
#include<iostream>
#include "datime.h"
#include "json.h"
using namespace std;

class Transaction
{
    protected:

        string mob_no1;
        string mob_no2;
        float amount;

    public:

        Datime Time;
        string get_mob_no1(){
            return mob_no1; }
        string get_mob_no2(){
            return mob_no2; }
        float get_amount(){
            return amount; }
        void put_mob_no1(string mob_no1){
            this->mob_no1 = mob_no1; }
        void put_mob_no2(string mob_no2){
            this->mob_no2 = mob_no2; }
        void put_amount(float amount){
            this->amount = amount; }
        void Create_json(json_class&);
        void retrieve_json(json_class&);
        Transaction();
        friend ostream& operator <<(ostream&,Transaction&);
};

#endif // TRANSACTION_H
