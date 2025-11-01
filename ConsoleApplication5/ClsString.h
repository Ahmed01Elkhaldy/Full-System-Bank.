#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

enum EnWhtaYouCount { CapitalLetter = 1, SmallLetter = 2 };

class ClsString
{
private:
	string _Name;
	char _Ch;
public:
	ClsString()
	{
		_Name = "";
	}
	ClsString(string name, char Ch)
	{
		_Name = name;
		_Ch = Ch;
	}
	void setname(string name)
	{
		_Name = name;
	}
	string Getname()
	{
		return _Name;
	}
	void setchar(char Ch)
	{
		_Ch = Ch;
	}
	char Getchar()
	{
		return _Ch;
	}

	static short Lenght(string S1)
	{
		return S1.length();
	}
	short Lenght()
	{
		return _Name.length();
	}
	static short CountWords(string S1)
	{
		string Del = " ";
		string Word = "";
		short Pos = 0;
		int Counter = 0;

		while ((Pos = S1.find(Del)) != std::string::npos)
		{
			Word = S1.substr(0, Pos);

			if (Word != "")Counter++;

			S1.erase(0, Pos + Del.size());

		}

		if (S1 != "") Counter++;

		return Counter;
	}
	short CountWords()
	{
		return CountWords(_Name);
	}

	static vector<string>Split(string S1, string Delim = " ")
	{
		vector<string>Words;
		string Word = "";
		short Pos;
		while ((Pos = S1.find(Delim)) != std::string::npos)
		{
			Word = S1.substr(0, Pos);

			if (Word != "") // "/##/Khaled"
			{
				Words.push_back(Word);
			}
			S1.erase(0, Pos + Delim.size());
		}

		if (S1 != "")Words.push_back(S1);

		return Words;
	}
	vector<string>Split2(string S1, string Delim = " ")
	{
		vector<string>Words;
		string Word = "";
		short Pos;
		while ((Pos = S1.find(Delim)) != std::string::npos)
		{
			Word = S1.substr(0, Pos);

			if (Word != "") // "/##/Khaled"
			{
				Words.push_back(Word);
			}
			S1.erase(0, Pos + Delim.size());
		}

		if (S1 != "")Words.push_back(S1);

		return Words;
	}

	/*static void PrintVector(string V)
	{
		vector<string>Words = Splitstring(V);
		for (string S : Words)
		{
			cout << S << endl;
		}
		return;
	}*/


	static void PrintFirstLetterFromWord(string S1)
	{
		bool isfirstletterinstring = true;

		cout << "First Letter From Each Word Is: \n";
		//Ahmed Mohmed Said Khaled

		for (int t = 0;t < S1.size(); t++)
		{
			if (S1[t] != ' ' && isfirstletterinstring)
			{
				cout << S1[t] << endl;
			}

			isfirstletterinstring = (S1[t] == ' ') ? true : false;
		}

	}

	static string ConverFirstLetterToUpperCase(string S1)
	{
		bool isfirstletterinstring = true;

		cout << "Conver First Letter From Each Word To Upper Case Is: \n";
		//Ahmed Mohmed Said Khaled

		for (int t = 0;t < S1.size(); t++)
		{
			if (S1[t] != ' ' && isfirstletterinstring)
			{
				S1[t] = toupper(S1[t]);
			}

			isfirstletterinstring = (S1[t] == ' ') ? true : false;
		}

		return S1;

	}
	void ConverFirstLetterToUpperCase()
	{
		_Name = ConverFirstLetterToUpperCase(_Name);
	}

	static string ConverFirstLetterToLowerCase(string S1)
	{
		bool isfirstletterinstring = true;

		cout << "Conver First Letter From Each Word To Lower Case Is: \n";

		//Ahmed Mohmed Said Khaled

		for (int t = 0;t < S1.size(); t++)
		{
			if (S1[t] != ' ' && isfirstletterinstring)
			{
				S1[t] = tolower(S1[t]);
			}

			isfirstletterinstring = (S1[t] == ' ') ? true : false;
		}

		return S1;

	}
	void ConverFirstLetterToLowerCase()
	{
		_Name = ConverFirstLetterToLowerCase(_Name);
	}

	static string ConverAllStringToLowerCase(string S1)
	{
		// bool isfirstletterinstring = true;

		cout << "Convert All String To Lower Case Is: \n";
		for (int t = 0;t < S1.size(); t++)
		{
			S1[t] = tolower(S1[t]);
		}
		return S1;
	}
	void ConverAllStringToLowerCase()
	{
		_Name = ConverAllStringToLowerCase(_Name);
	}

	static string ConverAllStringToUpperCase(string S1)
	{
		// bool isfirstletterinstring = true;

		cout << "Convert All String To Upper Case Is: \n";

		for (int t = 0;t < S1.size(); t++)
		{
			S1[t] = toupper(S1[t]);
		}
		return S1;
	}
	void ConverAllStringToUpperCase()
	{
		_Name = ConverAllStringToUpperCase(_Name);
	}

	static char InverCharToUpperCase(char Ch)
	{
		return isupper(Ch) ? tolower(Ch) : toupper(Ch);
	}


	static string InverAllLetterscase(string S1)
	{
		for (int i = 0;i < S1.size();i++)
		{
			S1[i] = InverCharToUpperCase(S1[i]);
		}
		return S1;
	}
	void InverAllLetterscase()
	{
		_Name = InverAllLetterscase(_Name);
	}


	static short WhatDoYouCount(string S1, EnWhtaYouCount WhatYoucount)
	{
		short Count;

		WhatYoucount == EnWhtaYouCount::CapitalLetter ?
			Count = CountCapitalLetter(S1) : Count = CountSmallLetter(S1);

		return Count;
	}

	static int CountCapitalLetter(string S1)
	{
		short Counter = 0;

		for (int i = 0;i < S1.size();i++)
		{
			if (isupper(S1[i]))Counter++;
		}

		return Counter;
	}
	void CountCapitalLetter()
	{
		_Name = CountCapitalLetter(_Name);
	}

	static int CountSmallLetter(string S1)
	{
		short Counter = 0;

		for (int i = 0;i < S1.size();i++)
		{
			if (islower(S1[i]))Counter++;
		}

		return Counter;
	}
	short CountSmallLetter()
	{
		return CountSmallLetter(_Name);
	}

	static short CountAllCharInString(string S1, char ch, bool Matchcase = true)
	{
		short Counter = 0;
		for (int t = 0;t < S1.size(); t++)
		{
			if (Matchcase)
			{
				if (S1[t] == ch)Counter++;
			}
			else
			{
				if (toupper(S1[t]) == toupper(ch))Counter++;
			}

		}

		return Counter;
	}
	short CountAllCharInString()
	{
		return CountAllCharInString(_Name, Ch);
	}

	static bool IsVowelsChar(char ch)
	{
		string Vowels = "a,e,i,o,u";

		ch = tolower(ch);
		return (ch == 'a' || ch == 'i' || ch == 'u' || ch == 'e' || ch == 'o');

	}

	static short CountOfVowels(string s1)
	{
		short Counter = 0;
		for (int t = 0; t < s1.size();t++)
		{
			if (IsVowelsChar(s1[t])) Counter++;

		}
		return Counter;
	}
	short CountOfVowels()
	{
		return CountOfVowels(_Name);
	}


	/*static void PrintVowelsCase(char ch)
	{
		if (IsVowelsChar(ch))
		{
			cout << "\nYES Letter \ '" << ch << "\' is vowel\n";
		}
		else
		{
			cout << "\nNO Letter \'" << ch << "\' is NOT vowel\n";
		}
	}*/

	static void PrintAllVowels(string S1)
	{
		for (int t = 0; t < S1.size();t++)
		{
			if (IsVowelsChar(S1[t]))cout << S1.at(t) << " ";

		}
		cout << endl;

	}

	static void PrintEachWordInString(string S1)
	{
		string Del = " ";
		string Word = "";
		short Pos = 0;
		//int Counter = 0;

		while ((Pos = S1.find(Del)) != std::string::npos)
		{
			Word = S1.substr(0, Pos);

			if (Word != "") cout << Word << endl;

			S1.erase(0, Pos + Del.size());

		}
		// "Programming Advices Mohamed Abo-Hadhoud" 
		if (S1 != "") cout << S1 << endl;

		return;
	}

	static string TrimLeft(string S1)
	{
		for (int i = 0; i < S1.size();i++)
		{
			if (S1[i] != ' ')return S1.substr(i, S1.size()); //"    Programming Advices    "
		}
	}
	void TrimLeft()
	{
		_Name = TrimLeft(_Name);
	}

	static string TrimRight(string S1)
	{
		for (int i = S1.size() - 1; i >= 0;i--)
		{
			if (S1[i] != '*')return S1.substr(0, i + 1); //"    Programming Advices******"
		}

	}
	void TrimRight()
	{
		_Name = TrimRight(_Name);
	}

	static string Trim(string S1)
	{

		return TrimRight(TrimLeft(S1));
	}
	void Trim()
	{
		_Name = Trim(_Name);
	}

	static string JoinString(vector<string>Words, string Delim = ",")
	{
		string Word = "";
		for (string S : Words)
		{
			Word += S + Delim; // Ahmed,+ Monmed+,+Said+, - > Ahmed,Mohmed,Said
		}

		return Word.substr(0, Word.size() - 1);
	}
	static string JoinString(string Words[], int WordsSize, string Delim = ",")
	{
		string Word = "";
		for (int w = 0;w < WordsSize;w++)
		{
			Word += Words[w] + Delim; // Ahmed,+ Monmed+,+Said+, - > Ahmed,Mohmed,Said
		}

		return Word.substr(0, Word.size() - 1);

		return Word;
	}

	static string ReversingString(string S1)
	{
		vector<string>Words = Split(S1, " ");
		string Statment;

		vector<string>::iterator iter = Words.end();

		while (iter != Words.begin())
		{
			iter--;
			Statment += *iter + " ";

		}



		return Statment;
	}

	static string RepalceString(string S1, string stringToRepalce, string ReplaceTo)
	{
		short Pos = S1.find(stringToRepalce);

		while (Pos != std::string::npos)
		{

			S1 = S1.replace(Pos, stringToRepalce.size(), ReplaceTo);
			Pos = S1.find(stringToRepalce); // find Next 
		}
		return S1;
	}
	string RepalceString(string stringToRepalce, string ReplaceTo)
	{
		return RepalceString(_Name, stringToRepalce, ReplaceTo);
	}

	static string ReplaceStringUsingSplit(string S1, string StringToRplace, string SReplaceTo, bool Matchcase = true)
	{
		vector<string>Words = Split(S1);

		for (string& S : Words)
		{
			if (Matchcase)
			{// Jorden   ---> jorden
				if (S == StringToRplace) S = SReplaceTo;
			}
			else
			{
				if (ConverAllStringToLowerCase(S1) == ConverAllStringToLowerCase(StringToRplace))
					S = SReplaceTo;
			}
		}

		S1 = JoinString(Words, " ");

		return S1;
	}

	static string RemovePunctuationFromstring(string S1)
	{
		string S2;
		for (int s = 0; s < S1.size();s++)
		{
			if (!ispunct(S1[s]))S2 += S1[s];
		}
		return S2;
	}
	__declspec(property(get = Getname, put = setname)) string value;
	__declspec(property(get = Getchar, put = setchar)) char Ch;
};



