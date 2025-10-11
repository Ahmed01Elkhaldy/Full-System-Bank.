#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const string ClientsFileName = "DClients.txt";
const string UsersFileName = "Users.txt";
void Login();
void ShowTransactionsMenue();
void PrintMainMenu();
void  ShowManageUsersMenue();
enum PermissionUser
{
	PAll = -1,
	PShowClientList = 1,
	PAddNewCLient = 2,
	PDeleteCLient = 4,
	PUpdateClientInfo = 8,
	PFindCLient = 16,
	PTransactions = 32,
	PManageUSers = 64,

};

enum EnChoice
{
	ShowClientList = 1,
	AddNewCLient = 2,
	DeleteCLient = 3,
	UpdateClientInfo = 4,
	FindCLient = 5,
	Transactions = 6,
	ManageUSers = 7,
	Logout = 8
};
enum EnChoiceTransctions
{
	Deposit = 1,
	Withdraw = 2,
	TotalBalance = 3,
	MainMeune = 4
};

struct StUsers
{
	string Name;
	string Password;
	int Permission = 0;
	bool DeleteMark = false;
};
StUsers Currentuser;
struct StClinet
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	bool MarkDelete = false;
	double AccountBalance = 0.0;
};
struct StTransactions
{
	double Deposit;
	double Withdraw;
};
EnChoice ReadNumberOfchoiec()
{
	int ch;
	do
	{
		cout << "Chooce What Do You Want To Do From [1] To [8]\n";
		cin >> ch;

	} while (ch < 1 || ch > 8);

	return EnChoice(ch);
}
void LoadDataTofile(string FileName)
{
	fstream Myfile;
	string Line;

	Myfile.open(FileName, ios::out);

	if (Myfile.is_open())
	{
		Myfile << Line << endl;
	}

}
vector<string>SplitString(string Line, string Del = "#//#")
{
	vector<string>Words;
	string Word;
	short Pos = 0;

	while ((Pos = Line.find(Del)) != std::string::npos)
	{
		Word = Line.substr(0, Pos);
		if (Word != "") Words.push_back(Word);
		Line.erase(0, Pos + Del.size());

	}

	if (Line != "")Words.push_back(Line);
	return Words;

}
bool CheckPermissionToUsers(PermissionUser Permission)
{
	if (Currentuser.Permission == PermissionUser::PAll
	|| (Currentuser.Permission & Permission) == Permission)return true;


	return false;
}
void ShowDeniedMessage()
{
	cout << "-------------------------\n";
	cout << "Denied Access\n";
	cout << "Cant Access To This Permission\n";
	cout << "Contact Admin\n";
	cout << "-------------------------\n";
}
StClinet ConverLineToRecord(string Line)
{
	vector<string>Data = SplitString(Line);

	StClinet St;

	St.AccountNumber = Data[0];
	St.PinCode = Data[1];
	St.Name = Data[2];
	St.Phone = Data[3];
	St.AccountBalance = stod(Data[4]);


	return St;

}
vector<StClinet>SaveDataTovector(string FileName)
{
	vector<StClinet>StData;

	fstream Myfile;

	Myfile.open(FileName, ios::in);

	if (Myfile.is_open())
	{
		StClinet St;
		string Dataline;
		while (getline(Myfile, Dataline))

		{
			St = ConverLineToRecord(Dataline);
			StData.push_back(St);
		}

		Myfile.close();
	}

	return StData;

}
StUsers ConverLineToUsersRecord(string Line)
{

	vector<string>Data = SplitString(Line);
	StUsers User;

	User.Name = Data[0];
	User.Password = Data[1];
	User.Permission = stoi(Data[2]);

	return User;
}
vector<StUsers>SaveDataUserTovector(string FileName)
{
	vector<StUsers>StData;

	fstream Myfile;

	Myfile.open(FileName, ios::in);

	if (Myfile.is_open())
	{
		StUsers St;
		string Dataline;
		while (getline(Myfile, Dataline))

		{
			St = ConverLineToUsersRecord(Dataline);
			StData.push_back(St);
		}

		Myfile.close();
	}

	return StData;

}
void BackScreen()
{
	cout << "\nEnter Eny Press To Back Main\n";
	system("pause>0");
	system("cls");
	PrintMainMenu();
}
void PrintCleintData(StClinet st)
{
	cout << "| " << left << setw(15) << st.AccountNumber;
	cout << "| " << left << setw(10) << st.PinCode;
	cout << "| " << left << setw(30) << st.Name;
	cout << "| " << left << setw(12) << st.Phone;
	cout << "| " << left << setw(8) << st.AccountBalance;
}
void PrintAllClientsData(vector<StClinet>st)
{
	if (!CheckPermissionToUsers(PermissionUser::PShowClientList))
	{
		ShowDeniedMessage();
		BackScreen();
		return;
	}
	cout << "\t\t\t\t Clients List (" << st.size() << ") Client(s)." << endl;
	cout << "---------------------------------------------------------------------------------------------\n";
	cout << "| " << left << setw(15) << "Account Number ";
	cout << "| " << left << setw(10) << "PinCode";
	cout << "| " << left << setw(30) << "Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(8) << "Account Balance";
	cout << "\n---------------------------------------------------------------------------------------------\n";
	for (StClinet& StD : st)
	{
		PrintCleintData(StD);
		cout << endl;
	}

}
int ReadPermission()
{
	int Per = 0;

	char OP2 = 'N';
	char OP = 'Y';
	cout << "Do You Want Access To All System\n";
	cin >> OP;
	if (toupper(OP) == 'Y')
	{
		return -1;
	}
	else
	{
		cout << "Do You Want Give Access To: ";
		cout << "Show Client List y/n: ";
		cin >> OP2;
		if (toupper(OP2) == 'Y')
		{
			Per += PermissionUser::PShowClientList;
		}
		else
		{
			Per += 0;
		}
		cout << "Add New Client List y/n: ";
		cin >> OP2;

		if (toupper(OP2) == 'Y')
		{
			Per += PermissionUser::PAddNewCLient;
		}
		else
		{
			Per += 0;
		}

		cout << "Delete Client  y/n: ";
		cin >> OP2;
		if (toupper(OP2) == 'Y')
		{
			Per += PermissionUser::PDeleteCLient;
		}
		else
		{
			Per += 0;
		}
	
		cout << "Update Client  y/n: ";
		cin >> OP2;
		if (toupper(OP2) == 'Y')
		{
			Per += PermissionUser::PUpdateClientInfo;
		}
		else
		{
			Per += 0;
		}
	
		cout << "Find Client  y/n: ";
		cin >> OP2;
		
		if (toupper(OP2) == 'Y')
		{
			Per += PermissionUser::PFindCLient;
		}
		else
		{
			Per += 0;
		}
		cout << "Transactions Client  y/n: ";
		cin >> OP2;
		
		if (toupper(OP2) == 'Y')
		{
			Per += PermissionUser::PTransactions;
		}
		else
		{
			Per += 0;
		}

		cout << "Manager Users y/n: ";
		cin >> OP2;
		if (toupper(OP2) == 'Y')
		{
			Per += PermissionUser::PManageUSers;
		}
		else
		{
			Per += 0;
		}
	
	}

	

	return Per;
}
bool ExistUserData(string Name, vector<StUsers>U)
{
	for (StUsers& St : U)
	{
		if (St.Name == Name)return true;
	}
	return false;
}
StUsers ReadNewDataTiNewUsers(vector<StUsers>U)
{
	StUsers St;
	cout << "Enter User Name: ";
	getline(cin >> ws, St.Name);
	while (ExistUserData(St.Name, U))
	{
	cout << "Enter User Name: ";
	getline(cin >> ws, St.Name);
	}

	cout << "Enter Password: ";
	getline(cin, St.Password);

	St.Permission = ReadPermission();

	return St;
}
StClinet ReadNewDataTiNewClient()
{
	StClinet St;
	cout << "Enter Account Number: ";
	getline(cin >> ws, St.AccountNumber);
	
	cout << "Enter PinCode: ";
	getline(cin, St.PinCode);
	
	cout << "Enter Your Name: ";
	getline(cin, St.Name);
	
	cout << "Enter Phone: ";
	getline(cin, St.Phone);

	cout << "Enter Account Balance: ";
	cin >> St.AccountBalance;


	

	return St;
}
string ConvertRecordToLine(StClinet st, string Del = "#//#")
{
	string Line;

	Line += st.AccountNumber + Del;
	Line += st.PinCode + Del;
	Line += st.Name + Del;
	Line += st.Phone + Del;
	Line += to_string(st.AccountBalance);

	return Line;

}
void SaveDataToFile(string FileName, string Line)
{
	fstream Myfile;
	Myfile.open(FileName, ios::out | ios::app);

	if (Myfile.is_open())
	{
		Myfile << Line << endl;
	}

	Myfile.close();
}
void AddingNewClient()
{
	if (!CheckPermissionToUsers(PermissionUser::PAddNewCLient))
	{
		ShowDeniedMessage();
		BackScreen();
		return;
	}
	cout << "--------------------------------------\n";
	cout << "\t\t Add New Client Screen\t\t\n";
	cout << "--------------------------------------\n";

	cout << "Adding New Client:-) \n";

	StClinet st;
	st = ReadNewDataTiNewClient();
	SaveDataToFile(ClientsFileName, ConvertRecordToLine(st));
	cout << "The Client Is Adding Successfully\n";



}
string ConvertRecordUserToLine(StUsers User, string Del = "#//#")
{
	string Line = "";

	Line = User.Name + Del;
	Line += User.Password + Del;
	Line += to_string(User.Permission);

	return Line;
}

void AddingNewUsers(vector<StUsers>U)
{
	cout << "--------------------------------------\n";
	cout << "\t\t Add New User Screen\t\t\n";
	cout << "--------------------------------------\n";

	cout << "Adding New User:-) \n";

	char Op='y';
	do
	{
	StUsers st;
	st = ReadNewDataTiNewUsers(U);
	SaveDataToFile(UsersFileName, ConvertRecordUserToLine(st));
	cout << "The Client Is Adding Successfully\n";

	} while (Op == 'Y');


}
void BackScreenTrans()
{
	cout << "\nEnter Eny Press To Back Main\n";
	system("pause>0");
	system("cls");
	ShowTransactionsMenue();
}
void BackScreenManage()
{
	cout << "\nEnter Eny Press To Back Main\n";
	system("pause>0");
	system("cls");
	ShowManageUsersMenue();
}
bool findClinetThatWant(string Acc, StClinet& str, vector<StClinet>ST)
{
	for (StClinet& C : ST)
	{
		if (C.AccountNumber == Acc)
		{
			str = C;
			return true;
		}
	}
	return false;
}
string ReadAccountNumber(string Message)
{
	string Acc;
	cout << Message << endl;;
	cin >> Acc;
	return Acc;
}
void PrintCardData(StClinet st)
{

	cout << "Account Number: " << st.AccountNumber << endl;
	cout << "PinCode: " << st.PinCode << endl;
	cout << "Name: " << st.Name << endl;
	cout << "Phone: " << st.Phone << endl;
	cout << "Account Balance: " << st.AccountBalance << endl;

	cout << endl;

}
void FindClientSearch(string Acc, vector<StClinet>St)
{
	if (!CheckPermissionToUsers(PermissionUser::PFindCLient))
	{
		ShowDeniedMessage();
		BackScreen();
		return;
	}
	for (StClinet& C : St)
	{
		if (C.AccountNumber == Acc)
		{
			PrintCardData(C);

		}

	}
}
bool FindUSersDataToDelete(string Uname, StUsers& User, vector<StUsers>VU)
{
	for (StUsers& St : VU)
	{
		if (St.Name == Uname)
		{
			User = St;
			return true;
		}

	}
	return false;
}
void PrintUsersData(StUsers ST)
{
	cout << "The Following Users Details: \n";
	cout << "-------------------------------------------------\n";
	cout << "Username  : " << ST.Name << endl;
	cout << "Password  : " << ST.Password << endl;
	cout << "Permission: " << ST.Permission << endl;
	cout << "-------------------------------------------------\n";
}
void FindUserSearch(string Username, vector<StUsers>St)
{
	StUsers Us;
	if (FindUSersDataToDelete(Username, Us, St))
	{
			PrintUsersData(Us);

	}
	else
	{
		cout << "Don't Find Any Data To [" << Username << "] \n";
	}
}
bool MarkClientToDelete(string Acc, vector<StClinet>& StD)
{
	for (StClinet& C : StD)
	{
		if (C.AccountNumber == Acc)
		{
			C.MarkDelete = true;
			return true;
		}

	}

	return false;
}
void SavaUpdateDataToFile(string fileName, vector<StClinet>StD)
{
	fstream Myfile;

	string Line;
	Myfile.open(fileName, ios::out);

	if (Myfile.is_open())
	{
		for (StClinet& C : StD)
		{
			if (C.MarkDelete == false)
			{
				Line = ConvertRecordToLine(C);
				Myfile << Line << endl;
			}
		}
		Myfile.close();
	}
}
void SavaUpdateDataSerToFile(string fileName, vector<StUsers>StD)
{
	fstream Myfile;

	string Line;
	Myfile.open(fileName, ios::out);

	if (Myfile.is_open())
	{
		for (StUsers & C : StD)
		{
			if (C.DeleteMark == false)
			{
				Line = ConvertRecordUserToLine(C);
				Myfile << Line << endl;
			}
		}
		Myfile.close();
	}
}
bool CleintDeleteFromFile(string FileName, string Acc, vector<StClinet>StD)
{
	if (!CheckPermissionToUsers(PermissionUser::PDeleteCLient))
	{
		ShowDeniedMessage();
		BackScreen();
		return true;
	}
	char OP = 'n';
	string Line;
	StClinet DataC;

	if (findClinetThatWant(Acc, DataC, StD))
	{
		PrintCardData(DataC);

		cout << "Do You Want Delete This Client Y/N\n";
		cin >> OP;

		if (toupper(OP) == 'Y')
		{
			MarkClientToDelete(Acc, StD);
			SavaUpdateDataToFile(ClientsFileName, StD);

			cout << "Data Is Delete Successfully\n";

			StD = SaveDataTovector(ClientsFileName);
		}


		return true;
	}
	else
	{
		cout << "Sorry, Not Found Any Data To [" << Acc << "] \n";
		return false;
	}



}
bool MarkUserToDelete(string Username, vector<StUsers>&VU)
{
	for (StUsers& St : VU)
	{
		if (St.Name == Username)
		{
			St.DeleteMark = true;
			return true;
		}

	}
	return false;
}
string ReadFilename()
{
	string UserName;
	cout << "Enter The Username That Want Delete It: ";
	cin >> UserName;

	return UserName;
}
bool UserDeleteFromFile(string FileName, string Username, vector<StUsers>StD)
{

	char OP = 'n';
	string Line;
	StUsers DataC;
	if (Username == "Admin")
	{
		cout << "Can't Delete This User...\n ";
		return false;
	}
	if (FindUSersDataToDelete(Username, DataC, StD))
	{
		PrintUsersData(DataC);

		cout << "Do You Want Delete This Users Y/N\n";
		cin >> OP;

		if (toupper(OP) == 'Y')
		{
			MarkUserToDelete(Username, StD);
			SavaUpdateDataSerToFile(UsersFileName, StD);

			cout << "Data Is Delete Successfully\n";

			StD = SaveDataUserTovector(UsersFileName);
		}


		return true;
	}
	else
	{
		cout << "Sorry, Not Found Any Data To [" << Username << "] \n";
		return false;
	}



}
StClinet ChangeDataToClient(string Acc)
{
	StClinet StD;

	StD.AccountNumber = Acc;

	cout << "Enter The New Data: \n";

	cout << "Enter PinCode: ";
	getline(cin >> ws, StD.PinCode);

	cout << "Enter Name: ";
	getline(cin, StD.Name);

	cout << "Enter Phone Number: ";
	getline(cin, StD.Phone);

	cout << "Enter Account Balance: ";
	cin >> StD.AccountBalance;


	return StD;
}
StUsers ChangeDataToUser(string Username)
{
	StUsers StD;

	StD.Name = Username;

	cout << "Enter a New Password: ";
	getline(cin >> ws, StD.Password);

	StD.Permission = ReadPermission();


	return StD;
}
bool UpdateDataClinet(string Acc, string FileName, vector<StClinet>& Str)
{
	if (!CheckPermissionToUsers(PermissionUser::PUpdateClientInfo))
	{
		ShowDeniedMessage();
		BackScreen();
		return true;
	}
	StClinet StD;

	if (findClinetThatWant(Acc, StD, Str))
	{
		PrintCardData(StD);
		char OP = 'n';

		cout << "Do You Want Update This Details: ";
		cin >> OP;
		if (toupper(OP) == 'Y')
		{

			for (StClinet& C : Str)
			{
				if (C.AccountNumber == Acc)
				{
					C = ChangeDataToClient(Acc);
				}
			}
		}

		SavaUpdateDataToFile(ClientsFileName, Str);
		cout << "The Data Is Update Successfully: \n";

		Str = SaveDataTovector(FileName);

		return true;
	}
	else
	{
		cout << "Not Found This Data To[" << Acc << "] \n";
		return false;
	}
}
bool UpdateDataUser(string UserName, string FileName, vector<StUsers>& Str)
{
	StUsers StD;

	if (FindUSersDataToDelete(UserName, StD, Str))
	{
		PrintUsersData(StD);
		char OP = 'n';

		cout << "Do You Want Update This Details: ";
		cin >> OP;
		if (toupper(OP) == 'Y')
		{

			for (StUsers& C : Str)
			{
				if (C.Name == UserName)
				{
					C = ChangeDataToUser(UserName);
				}
			}
		}

		SavaUpdateDataSerToFile(UsersFileName, Str);
		cout << "The Data Is Update Successfully: \n";

		//Str = SaveDataTovector(FileName);.

		return true;
	}
	else
	{
		cout << "Not Found This Data To[" << UserName << "] \n";
		return false;
	}
}
int ReadNumberOfTransactions()
{
	int Choose;

	cout << "Choose What Do You Want To Do[1 To 4]: ";
	cin >> Choose;


	return Choose;
}
bool ExistClientData(string Acc, string fileName)
{
	fstream Myfile;
	Myfile.open(fileName, ios::in);
	vector<StClinet>str;
	if (Myfile.is_open())
	{
		string Line;
		StClinet St;
		while (getline(Myfile, Line))
		{
			St = ConverLineToRecord(Line);
			if (St.AccountNumber == Acc)
			{
				Myfile.close();
				return false;
			}
			str.push_back(St);
		}
		Myfile.close();
	}

	return true;
}
bool DepositOperation(string Acc, vector<StClinet>& str)
{
	StTransactions De;

	cout << "Enter The Amount To Deposit \n";
	cin >> De.Deposit;
	char Op = 'Y';

	cout << "Are You Sure Deposit This Amount To Account: ";
	cin >> Op;
	if (toupper(Op) == 'Y')
	{

		for (StClinet& C : str)
		{
			if (C.AccountNumber == Acc)
			{
				C.AccountBalance += De.Deposit;
				SavaUpdateDataToFile(ClientsFileName, str);
				cout << "Successfully Operation << The Balance Is: " << C.AccountBalance << endl;
				return true;
			}
		}

	}

	return false;
}
void DepositByAccountNumber(vector<StClinet>st)
{

	StClinet Str;
	string Acc = "";
	Acc = ReadAccountNumber("Enter The Account Number That You Want Deposit To It\n");

	while (ExistClientData(Acc, ClientsFileName))
	{
		Acc = ReadAccountNumber("Enter The Account Number That You Want Deposit To It\n");
		cout << "Enter Another Number This Number [" << Acc << "] Is Exist\n\n";

	}
	if (findClinetThatWant(Acc, Str, st))
	{

		cout << "The Following Client Details\n\n";
		PrintCardData(Str);

		DepositOperation(Acc, st);
	}

	else
	{
		cout << "Don't Find Any Data To [" << Acc << "] Number\n";
	}


}
void WithdrawByAccountNumber(vector<StClinet>st)
{

	StClinet Str;
	StTransactions De;
	string Acc;
		Acc = ReadAccountNumber("Enter The Account Number That You Want Deposit To It\n");
	while (ExistClientData(Acc, ClientsFileName))
	{
		Acc = ReadAccountNumber("Enter The Account Number That You Want Deposit To It\n");
		cout << "Enter Another Number This Number [" << Acc << "] Is Exist\n\n";

	}
	if (findClinetThatWant(Acc, Str, st))
	{

		cout << "The Following Client Details\n\n";
		PrintCardData(Str);
		cout << "Enter The Amount To Withdraw \n";
		cin >> De.Withdraw;
		char Op = 'Y';

		cout << "Are You Sure Withdraw This Amount From Account: ";
		cin >> Op;
		if (toupper(Op) == 'Y' && De.Withdraw < Str.AccountBalance)
		{

			for (StClinet& C : st)
			{
				if (C.AccountNumber == Acc)
				{
					C.AccountBalance -= De.Withdraw;
				}
			}
			SavaUpdateDataToFile(ClientsFileName, st);
			cout << "Successfully Operation\n\n";
		}
		else
		{
			cout << "Don't Find This Amount in Account Number Try Again \n";
		}


	}
	else
	{
		cout << "Don't Find Any Data To [" << Acc << "] Number\n";
	}

}
void PrintClientData(StClinet C)
{
	cout << "| " << left << setw(15) << C.AccountNumber;
	cout << "| " << left << setw(30) << C.Name;
	cout << "| " << left << setw(10) << C.AccountBalance;
}
void PrintBalancsOfClients(vector<StClinet>st)
{
	double TotalBalances = 0;
	cout << "\t\tBalances Lists[" << st.size() << "] Clients(s)" << endl;
	cout << "------------------------------------------------------------\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(30) << "Clinets Name";
	cout << "| " << left << setw(10) << "Balances\n";
	cout << "-----------------------------------------------------------\n";

	for (StClinet& C : st)
	{
		PrintClientData(C);
		cout << endl;
		TotalBalances += C.AccountBalance;
	}

	cout << "------------------------------------------------------------\n";

	cout << "Total Account Balance Is [" << TotalBalances << "]\n";
}
void StartTransactionsMenue(EnChoiceTransctions Ch)
{
	vector<StClinet>str = SaveDataTovector(ClientsFileName);

	switch (Ch)
	{
	case EnChoiceTransctions::Deposit:
		system("cls");
		DepositByAccountNumber(str);
		BackScreenTrans();
		break;

	case EnChoiceTransctions::Withdraw:
		system("cls");
		WithdrawByAccountNumber(str);
		BackScreenTrans();
		break;

	case EnChoiceTransctions::TotalBalance:
		system("cls");
		PrintBalancsOfClients(str);
		BackScreenTrans();

	case EnChoiceTransctions::MainMeune:
		system("cls");
		PrintMainMenu();
		BackScreen();
	}


}
void ShowTransactionsMenue()
{
	if (!CheckPermissionToUsers(PermissionUser::PTransactions))
	{
		ShowDeniedMessage();
		BackScreen();
		return;
	}
	cout << "=====================================\n";
	cout << "\t Transactions Menue Screen\n";
	cout << "=====================================\n\n";

	cout << "[1] Deposit.\n";
	cout << "[2] Withdraw.\n";
	cout << "[3] Total Balances.\n";
	cout << "[4] Back To Main Menue.\n";

	StartTransactionsMenue(EnChoiceTransctions(ReadNumberOfTransactions()));

}
enum EnChoiceManageUsers
{
	ListUSer = 1,
	AddNewUser = 2,
	DeleteUser = 3,
	UpdateUser=4,
	FindUser = 5,
	BackMainMenue = 6,

};
EnChoiceManageUsers ReadManageChice(string Message)
{

	short Ch;
	do
	{
		cout << "Enter Your Choice From [1]To[5]\n";
		cin >> Ch;
	} while (Ch < 1 || Ch > 6);

	return EnChoiceManageUsers(Ch);
}
void PrintUserData(StUsers User)
{
	cout << "| " << left << setw(20) << User.Name;
	cout << "| " << left << setw(20) << User.Password;
	cout << "| " << left << setw(20) << User.Permission;
	cout << endl;
}
void PrintDataUsers(vector<StUsers>Users)
{
	cout << "\t\tUsers List(" << Users.size() << ") User(s)\n";
	cout << "---------------------------------------------------------\n";
	cout << "| " << left << setw(20) << "User Name";
	cout << "| " << setw(20) << left << "Password";
	cout << "| " << setw(20) << left << "Permission";
	cout << "\n---------------------------------------------------------\n";

	for (StUsers& St : Users)
	{
		PrintUserData(St);
	}
}
vector<StUsers>SaveDataUSersToVector(string FileName)
{
	vector<StUsers>vData;

	StUsers User;
	string Line;

	fstream Myfile;
	Myfile.open(FileName, ios::in);

	if (Myfile.is_open())
	{
		while (getline(Myfile, Line))
		{
			User = ConverLineToUsersRecord(Line);
			vData.push_back(User);
		}
		Myfile.close();
	}

	return vData;

}



void StartManageMenue(EnChoiceManageUsers Ch)
{
	vector<StUsers>UData = SaveDataUSersToVector(UsersFileName);

	switch (Ch)
	{
	case EnChoiceManageUsers::ListUSer:
		system("cls");
		PrintDataUsers(UData);
        BackScreenManage();
	case EnChoiceManageUsers::AddNewUser:
		system("cls");
		AddingNewUsers(UData);
		BackScreenManage();
	case EnChoiceManageUsers::DeleteUser:
		system("cls");
		UserDeleteFromFile(UsersFileName, ReadFilename(), UData);
		BackScreenManage();
	case EnChoiceManageUsers::UpdateUser:
		system("cls");
		UpdateDataUser(ReadFilename(),UsersFileName,UData);
		BackScreenManage();
	case EnChoiceManageUsers::FindUser:
		system("cls");
		FindUserSearch(ReadFilename(), UData);
		BackScreenManage();
	case EnChoiceManageUsers::BackMainMenue:
		system("cls");
		PrintMainMenu();


	}
}
void  ShowManageUsersMenue()
{
	if (!CheckPermissionToUsers(PermissionUser::PManageUSers))
	{
		ShowDeniedMessage();
		BackScreen();
		return;
	}
	cout << "=====================================\n";
	cout << "\t Manage Users Menue\n";
	cout << "=====================================\n\n";

	cout << "[1] List Users.\n";
	cout << "[2] Add New Users.\n";
	cout << "[3] Delete Users.\n";
	cout << "[4] Update Users.\n";
	cout << "[5] Find Users\n";
	cout << "[6] Back To Main Menue.\n";

	StartManageMenue(ReadManageChice("Enter You Choice [1]TO[5]"));
}

void StartTheSystem(EnChoice Ch)
{
	vector<StClinet>DataC = SaveDataTovector(ClientsFileName);


	switch (Ch)
	{
	case EnChoice::ShowClientList: 

		system("cls");
		PrintAllClientsData(DataC);
		BackScreen();

		break;
	case EnChoice::AddNewCLient:

		system("cls");
		AddingNewClient();
		BackScreen();

		break;

	case EnChoice::DeleteCLient:
		system("cls");
		CleintDeleteFromFile(ClientsFileName,
		ReadAccountNumber("Enter Account Number That You Want Delete It: "), DataC);
		BackScreen();
		break;

	case EnChoice::UpdateClientInfo:
		system("cls");
		UpdateDataClinet(ReadAccountNumber
		("Enter Account Number That You Want Update It: "), ClientsFileName, DataC);
		BackScreen();

	case EnChoice::FindCLient:
		system("cls");
		FindClientSearch(ReadAccountNumber
		("Enter Account Number That You Want search It: "), DataC);
		BackScreen();
		break;
	case EnChoice::Transactions:
		system("cls");
		ShowTransactionsMenue();
	case EnChoice::ManageUSers:
		system("cls");
		ShowManageUsersMenue();
	case EnChoice::Logout:
		system("cls");
		Login();
	}
}
void PrintMainMenu()
{

	cout << "===========================================================\n";
	cout << "\t\t\tMain Menue Screen\t\t\t\n";
	cout << "===========================================================\n";
	cout << "[1] Show Client List. \n";
	cout << "[2] Add New CLient. \n";
	cout << "[3] Delete CLient. \n";
	cout << "[4] Update Client Info.\n";
	cout << "[5] Find CLient.\n";
	cout << "[6] Transactions.\n";
	cout << "[7] Manage Users. \n";
	cout << "[8] Logout. \n\n";

	StartTheSystem(EnChoice(ReadNumberOfchoiec()));
}
bool findUserByUsernameAndPassword(string Name, string Pass, StUsers& User ,vector<StUsers>VData)
{
	for (StUsers& St : VData)
	{
		if (St.Name == Name && St.Password == Pass)
		{
			User = St;
			return false;
		}
		}
	return true;
}
void Login()
{
	vector<StUsers>vData = SaveDataUSersToVector(UsersFileName);
	cout << "---------------------\n";
	cout << "\tLogin Screen\n";
	cout << "---------------------\n";

	string Username = "", Password = "";

	cout << "Enter User Name\n";
	cin >> Username;
	cout << "Enter Password\n";
	cin >> Password;

	while (findUserByUsernameAndPassword(Username, Password, Currentuser,vData))
	{
		system("cls");
		cout << "In valid Data\n";

		cout << "Enter User Name\n";
		cin >> Username;
		cout << "Enter Password\n";
		cin >> Password;

	}
	system("cls");

	PrintMainMenu();

}
int main()
{
	
	
	Login();

	return 0;
}