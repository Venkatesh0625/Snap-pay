#include<iostream>
#include<stdio.h>
#include "json.h"
//For inputing key and values for creating json string
int json_class::operator ()(string str,string val)
{
    json = json + "\"";
    json = json + str;
    json = json + "\":\"";
    json = json + val;
    json = json + "\",";
    attributes+=1;
    return 0;
}

//For getting the result based upon the given key value
string json_class::operator [](string str)
{
    for(int i=0;i<attributes;i++)
    {
        if(attr[i][0]==str)
            return attr[i][1];
    }
}
void json_class::slice()
{
    attributes=0;
    int f=0,k=0;
    string temp,att[2];
    int count=0;
    for(int i=1;i<json.size()-1;i++)
    {

        if(json[i]=='\"')
            count++;
        if(count%2==1)
        {
            if(json[i]!='\"')
                temp.push_back(json[i]);
        }

        else if(json[i]=='\"')
        {
            if(f==0)
            {
                att[f]=temp;
                f=1;
            }
            else
            {
                att[f]=temp;
                k++;
                f=0;
                attr[attributes][0] = att[0];
                attr[attributes][1] = att[1];
                attributes++;
            }
            temp.clear();
        }
        //cout<<temp<<endl;
    }

}

void json_class::end()
{
    json[json.size()-1] = '}';
}
