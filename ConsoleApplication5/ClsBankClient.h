#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"ClsString.h"
#include"ClsDate.h"
#include"ClsPerson.h"
class ClsBankClient : public ClsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float  _AccountBalance;

   static ClsBankClient _ConvertLineToObject(string Line , string Seprator = "/##/")
    {
        vector<string>DataClient;
        DataClient = ClsString::Split(Line, "#//#");

      return ClsBankClient(enMode::UpdateMode,DataClient[0],
      DataClient[1], DataClient[2], DataClient[3],
          DataClient[4], DataClient[5], stof(DataClient[6]));
    }

   static ClsBankClient _GetEmptyClientOpject()
   {
       return ClsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
   }

public:
    ClsBankClient(enMode Mode, string FirstName, string LastName,
    
        string Email ,string Phone ,string AccountNumber , string PinCode,
    float AccountBalance)
	:ClsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_PinCode = PinCode;
		_AccountNumber = AccountNumber;
        _AccountBalance = AccountBalance;
	}
	bool Empty()
	{
		return (_Mode == enMode::EmptyMode);
	}
    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << FirstName;
        cout << "\nLastName    : " << LastName;
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << Email;
        cout << "\nPhone       : " << Phone;
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n___________________\n";

    }

    static ClsBankClient Find(string AccNumber)
    {
        vector<ClsBankClient>Clients;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line = "";
            while (getline(MyFile, Line))
            {
            ClsBankClient Client = _ConvertLineToObject(Line);
            if (Client.AccountNumber() == AccNumber)
            {
                MyFile.close();
                return Client;
            }
            Clients.push_back(Client);
            }

        }
        MyFile.close();
        return _GetEmptyClientOpject();
    }

    static ClsBankClient Find(string AccNumber , string Pass)
    {
        vector<ClsBankClient>Clients;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line = "";
            while (getline(MyFile, Line))
            {
                ClsBankClient Client = _ConvertLineToObject(Line);
                if (Client.AccountNumber() == AccNumber&&
                    Client.PinCode == Pass)
                {
                    MyFile.close();
                    return Client;
                }
                Clients.push_back(Client);
            }

        }
        MyFile.close();
        return _GetEmptyClientOpject();

    }
   
    static bool IsClientExist(string AccNumber)
    {
        ClsBankClient Client = ClsBankClient::Find(AccNumber);
        return (!Client.Empty());
    }

};

