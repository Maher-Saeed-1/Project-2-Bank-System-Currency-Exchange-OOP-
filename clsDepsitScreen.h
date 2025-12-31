#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsClient.h"



class clsDepsitScreen : protected  clsScreen
{

private:

	static void _PrintClient(clsBankClient Client)
	{
        cout << "\nClient Card:";
        cout << "\n_";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n_\n___________________";
	}

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease Enter Account Number?";
        cin >> AccountNumber;
        return AccountNumber;
    }

public:

    static void ShowDepsitScreen()
    {
        _DrawScreenHeader("\t   Depsit Screen");

        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        double Amount = 0;
        cout << "\n Please Enter Depsit Amount? ";
        cin >> Amount;

        cout << "\nAry you sury you want to prtform this transactions? y/n";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Client.Depsit(Amount);
            cout << "\nAmount Depsit Successfully.\n";
            cout << "\nNew Balances is :" << Client.AccountBalance;
        }
        else
        {
            cout << "\nOperation was canselled.\n";
        }
    }
};

