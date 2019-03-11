#include <iostream>
#include <fstream>.
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;
struct Book
{
    short leni;
    char isbn[6];
    short lent;
    char title[50];
    short lena;
    char auth[50];
    short leny;
    char year[6];
    short lenp;
    int price;
    short lenn;
    char nop[5];

    char dilim;
};
istream& operator>>(istream& in,Book& f)
{
    cout<<"Enter the ISBN : ";
    in>>f.isbn;
    f.leni = strlen(f.isbn);
    in.ignore();
    cout<<"Enter the Title : ";
    in.getline(f.title,50,'\n');
    f.lent = strlen(f.title);
    cout<<"Enter the Author name : ";
    in.getline(f.auth,50,'\n');
    f.lena = strlen(f.auth);
    cout<<"Enter the Year : ";
    in>>f.year;
    f.leny = strlen(f.year);
    cout<<"Enter the Price : ";
    in>>f.price;
    f.lenp = sizeof(f.price);
    cout<<"Enter the Number of pages : ";
    in>>f.nop;
    f.lena = strlen(f.nop);
    f.dilim ='$';
    return in;
}

void Addbook(fstream& _file)
{
    Book b;
    cin>>b;
    _file.write((char*)&b,sizeof(b));
}

void Updatebook(fstream& _file)
{
    Book c;
    char ch[6];
    bool value =true;
    short co=0;
    cout<<"Enter the ISBN of the book : ";
    cin>>ch;
    _file.seekg(0,ios::end);
    long x=_file.tellg();
    _file.seekg(0,ios::beg);
    char *buffer = new char[x];
    _file.read(buffer,x);
    _file.seekg(0,ios::beg);
    _file.read((char*)&c,sizeof(c));
    do
    {
        co++;
        value=true;
        for(int i=0; i<strlen(ch); i++)
        {
            if(c.isbn[i]!=ch[i])
            {
                value=false;
                break;
            }
        }
        if(value)
        {
            _file.seekg((co-1)*sizeof(c),ios::beg);
            long y=_file.tellg();
            _file.close();
            fstream fout("list of books.txt",ios::out|ios::trunc);
            cout<<"\nEnter new data.\n\n";
            cin>>c;
            fout.write(buffer,x);
            fout.seekp(y,ios::beg);
            fout.write((char*)&c,sizeof(c));
            fout.close();
            break;
        }
        _file.read((char*)&c,sizeof(c));
    }
    while(!_file.eof());
    if(!value)
        cout<<"\nThe book is not exist..."<<endl;
    delete []buffer;
}
//************************************************************
void Deletebook(fstream& _file)
{
    Book c;
    char ch[6];
    bool value =true;
    vector<string> vec;
    string str;
    short co=0;
    _file.seekg(0,ios::beg);
    getline(_file,str,'$');
    str+='$';
    while(!_file.eof())
    {
        vec.push_back(str);
        str.clear();
        getline(_file,str,'$');
        str+='$';
    }
    _file.clear();//****************
    _file.seekg(0);
    cout<<"Enter the ISBN of the book : ";
    cin>>ch;
    _file.read((char*)&c,sizeof(c));
    do
    {
        co++;
        value=true;
        for(int i=0; i<strlen(ch); i++)
        {
            if(c.isbn[i]!=ch[i])
            {
                value=false;
                break;
            }

        }
        if(value)
        {
            _file.close();
            fstream fout("list of books.txt",ios::out|ios::trunc);
            for(int i=0;i<vec.size();i++)
            {
                if(i != co-1)
                {
                    fout<<vec[i];
                }
            }
            fout.close();
            break;
        }
        _file.read((char*)&c,sizeof(c));
    }
    while(!_file.eof());
    if(!value)
        cout<<"\nThe book is not exist..."<<endl;
}
//************************************************************

void Printbook(fstream& _file)
{
    Book c;
    _file.seekg(0,ios::beg);//***************************************************
    char ch[50];
    bool value=true;
    cin.ignore();
    cout<<"Enter the title of the book : ";
    cin.getline(ch,50);
    _file.read((char*)&c,sizeof(c));
    do
    {
        value=true;
        for(int i=0; i<strlen(ch); i++)
        {
            if(c.title[i]!=ch[i])
            {
                value=false;
                break;
            }
        }
        if(value)
        {
            cout<<endl;
            cout<<"ISBN : "<<c.isbn<<endl;
            cout<<"Title : "<<c.title<<endl;
            cout<<"Author : "<<c.auth<<endl;
            cout<<"Year : "<<c.year<<endl;
            cout<<"Price : "<<c.price<<endl;
            cout<<"Number of pages : "<<c.nop<<endl;
            break;
        }
        _file.read((char*)&c,sizeof(c));
    }
    while(!_file.eof());
    if(!value)
        cout<<"\nThe book not exist..."<<endl;
}
void Printallbooks(fstream& _file)
{
    Book c;
    _file.seekg(0,ios::beg);
    _file.read((char*)&c,sizeof(c));
    do
    {
        cout<<endl;
        cout<<"ISBN : "<<c.isbn<<endl;
        cout<<"Title : "<<c.title<<endl;
        cout<<"Author : "<<c.auth<<endl;
        cout<<"Year : "<<c.year<<endl;
        cout<<"Price : "<<c.price<<endl;
        cout<<"Number of pages : "<<c.nop<<endl<<endl;
        _file.read((char*)&c,sizeof(c));
    }
    while(!_file.eof());
    system("pause");
    system("cls");
}
int main()
{
    fstream file;
    file.open("list of books.txt",ios::app|ios::binary|ios::in|ios::out);

    int choice;
    while(1)
    {
        cout<<"\t\t\t\t\t    ** List of operations **\n\n\n";
        cout<<"1- Add book.\n2- Update book.\n3- Delete book.\n4- Print book.\n5- Print all books.\n6- Exit.\n\n";
        cout<<"Enter the number of operation : ";
        cin>>choice;
        system("cls");

        if(choice==1)
        {
            Addbook(file);
            file.close();
        }
        else if(choice==2)
        {
            Updatebook(file);
            file.close();
        }
        else if(choice==3)
        {
            Deletebook(file);
            file.close();
        }
        else if(choice==4)
        {
            Printbook(file);
            file.close();
        }
        else if(choice==5)
        {
            Printallbooks(file);
            file.close();
        }
        else if(choice==6)
            break;
        else
            cout<<"Error,try again..."<<endl;
        file.open("list of books.txt",ios::app|ios::binary|ios::in|ios::out);
    }
    file.close();

    return 0;
}
