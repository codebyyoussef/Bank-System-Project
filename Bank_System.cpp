#include <iostream>
#include "clsLoginScreen.h"
using namespace std;

int main()
{
	while (true)
	{
		if (!clsLoginScreen::showLoginScreen())
		{
			break;
		}
	}
	//while (clsLoginScreen::showLoginScreen());
	return 0;
}
