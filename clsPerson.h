#pragma once
#include <iostream>
#include <string>
#include "InterfaceCommunication.h"
using namespace std;

class clsPerson : public InterfaceCommunication
{
private:
    string _firstName;
    string _lastName;
    string _email;
    string _phone;

public:

    clsPerson(string firstName, string lastName, string email, string phone)
    {
        _firstName = firstName;
        _lastName = lastName;
        _email = email;
        _phone = phone;
    }

    void setFirstName(string firstName)
    {
        _firstName = firstName;
    }

    string getFirstName()
    {
        return _firstName;
    }

    _declspec(property(get = getFirstName, put = setFirstName)) string firstName;

    void setLastName(string lastName)
    {
        _lastName = lastName;
    }

    string getLastName()
    {
        return _lastName;
    }

    _declspec(property(get = getLastName, put = setLastName)) string lastName;


    void setEmail(string email)
    {
        _email = email;
    }

    string getEmail()
    {
        return _email;
    }

    _declspec(property(get = getEmail, put = setEmail)) string email;


    void setPhone(string phone)
    {
        _phone = phone;
    }

    string getPhone()
    {
        return _phone;
    }

    _declspec(property(get = getPhone, put = setPhone)) string phone;

    string fullName()
    {
        return _firstName + " " + _lastName;
    }

    void sendEmail(string subject, string body)
    {
        /*cout << "\nThe following message sent successfully to email: " << _email << "\n\n";
        cout << "Subject: " << subject << "\n\n";
        cout << "Body: " << body << "\n"*/;
    }

    void sendSMS(string textMessage)
    {
       /* cout << "\nThe following SMS sent successfully to phone: " << _phone << "\n";
        cout << textMessage << "\n";*/
    }
};

