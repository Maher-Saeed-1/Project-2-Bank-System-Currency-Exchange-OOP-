#pragma once
#include <iostream>
#include "InterfaceCommunication.h"

using namespace std;

class clsPerson : public InterfaceCommunication
{
private:

    int _ID = 0;
    string _FirstName;
    string _LastName;
    string _Email;
    string _Phone;


public:

    clsPerson(string FirstName, string LastName, string Email, string Phone)
    {
        
        _FirstName = FirstName;
        _LastName = LastName;
        _Email = Email;
        _Phone = Phone;

    }


    int ID()
    {
        return _ID;
    }

    void setFirstName(string FirstName)
    {
       
        _FirstName = FirstName;
    }

    string GetFirstName()
    {
        return _FirstName;
    }

    _declspec(property(get = GetFirstName, put = setFirstName))string FirstName;

    void setLastName(string LastName)
    {
       
        _LastName = LastName;
    }

    string GetLastName()
    {
        return _LastName;
    }

    _declspec(property(get = GetLastName, put = setLastName))string LastName;

    string FullName()
    {
        return _FirstName + " " + _LastName;
    }

    void setEmail(string Email)
    {
        
        _Email = Email;
    }

    string GetEmail()
    {
        return _Email;
    }
    _declspec(property(get = GetEmail, put = setEmail))string Email;

    void setPhone(string Phone)
    {
       
        _Phone = Phone;
    }

    string GetPhone()
    {
        return _Phone;
    }
    _declspec(property(get = GetPhone, put = setPhone))string Phone;

    void Print()
    {
        cout << "\nInfo:\n";
        cout << "___________________________\n";
        cout << "ID: " << _ID << endl;
        cout << "FristName: " << _FirstName << endl;
        cout << "LastName:  " << _LastName << endl;
        cout << "FullName:  " << FullName() << endl;
        cout << "Email:     " << _Email << endl;
        cout << "Phone:     " << _Phone << endl;
        cout << "___________________________\n";
    }

    void SendEmail(string Title, string Body)
    {

    }
    
    void SendFax(string Title, string Body)
    {

    }

    void SendSMS(string Title, string Body)
    {

    }
    
};

