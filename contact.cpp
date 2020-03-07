#include "contact.h"
#include<fstream>
#include "json.h"
#include "snap.h"
Contact::Contact()
{
    string buf;
    nbr_cont = 0;
    bool flag=0;
    int n,i=0;
    fstream file;
    file.open("E:/Contacts.txt",ios::in);
    file>>n;
    nbr_cont = n;
    cout<<n<<endl<<nbr_cont;
    contacts = new user[2*n];
    while(!file.eof())
    {
        getline(file,buf);
        getline(file,contacts[i].name);
        cout<<contacts[i].name<<endl;
        getline(file,contacts[i].mob_no);
        cout<<contacts[i].mob_no<<endl;
        i++;
    }
    file.close();
}
void Contact::add_contact()
{
    int n;
    Snap_Accnt snap;
    bool flag=0;
    fstream file;
    string mob,str;
    json_class json;
    user *p;
    p = contacts;
    contacts = new user[nbr_cont+1];
    for(int i=0;i<nbr_cont;i++)
    {
        contacts[i].mob_no = p[i].mob_no;
        contacts[i].name = p[i].name;
    }
    cout<<"\n\n\tEnter The Contact Name : ";
    cin>>contacts[nbr_cont].name;
    do
    {
        bool f=0;
        flag=0;
        try
        {
            cout<<"\n\n\tEnter Mobile Number : ";
            cin>>mob;
            for(int i=0;i< mob.size();i++)
                if((!(mob[i]>47 && mob[i]<58)) && mob.size()!=10)
                    throw(1);
            //for checking whether the mobile no exist in snap accnt
            file.open("E:/Snap.txt",ios::in);
            while(getline(file,json.json))
            {
                json.slice();
                snap.retrieve_json(json);
                if(snap.mob_no == mob)
                {
                    f=1;
                    break;
                }
            }
            file.close();
            if(f==0)
            {
                throw(4.1100989);
            }
        }
        catch(int)
        {
            cout<<"\n\n\tInvalid Mobile Number ";
            flag=1;
        }
        catch(float)
        {
            cout<<"\n\n\tContact Already Exists ";
            flag=1;
        }
        catch(double)
        {
            cout<<"\n\tThis Mobile Number is Not Registered with Snap ";
            flag=1;
        }
    }
    while(flag==1);
    contacts[nbr_cont].mob_no = mob;
    file.open("E:/Contacts.txt",ios::in | ios::out);
    file<<(nbr_cont+1);
    file.close();
    file.open("E:/Contacts.txt",ios::out | ios::app);
    file<<"\n";
    file<<"\n";
    file<<contacts[nbr_cont].get_name();
    file<<"\n";
    file<<contacts[nbr_cont].get_mob_no();
    file.close();
}

string Contact::operator [](int index)
{
    return contacts[index].mob_no;
}

