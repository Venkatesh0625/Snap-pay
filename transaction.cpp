#include "transaction.h"
#include "datime.h"
#include<iomanip>
//For Creating json Format
void Transaction::Create_json(json_class& js)
{
    basic b;
    js("Mobile1",mob_no1);
    js("Mobile2",mob_no2);
    js("Amount",b.digitalize(amount));
    js("Time",Time.form_time());
    js.end();
}

Transaction::Transaction()
{
    mob_no1 = "\0";
    mob_no2 = "\0";
    amount  = 0.0;
}
//For Retrieving Data from  Json Format
void Transaction::retrieve_json(json_class& js)
{
    basic b;
    mob_no1 = js["Mobile1"];
    mob_no2 = js["Mobile2"];
    amount = b.redigit(js["Amount"]);
    Time.retime(js["Time"]);
}

ostream& operator <<(ostream& out,Transaction& t)
{
    out<<"\n\n\tFrom : "<<t.mob_no2<<"   To : "<<t.mob_no1<<" The Amount of "<<setw(6)<<t.amount<<"  Time : "<<t.Time.dd<<"/"<<t.Time.m<<"/"<<t.Time.yy<<" | "<<t.Time.hh<<":"<<t.Time.mm<<":"<<t.Time.ss<<"\n";
    return out;
}
