#include <iostream>
#include <fstream>
#include <string>
#include"ClsBankClient.h"
using namespace std;




int main()
{
	ClsBankClient Client1 = ClsBankClient::Find("A101");
	Client1.Print();

	ClsBankClient Client2 = ClsBankClient::Find("A102","12345");
	Client2.Print();

	
}