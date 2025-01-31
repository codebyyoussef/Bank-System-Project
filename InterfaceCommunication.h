#pragma once
#include <iostream>
#include <string>
using namespace std;

class InterfaceCommunication
{
public:
	virtual void sendEmail(string subject, string body) = 0;
	virtual void sendSMS(string textMessage) = 0;
};

