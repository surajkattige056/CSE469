#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

bool T = false; 
bool D = false;
bool f = false;
bool h = false;

using namespace std;

int command_parser(string a)
{
	//choice between -T and -D output
	if (a == "-T") // Time output
	{
		T = true;
	}
	else if (a == "-D") // Date output
	{
		D = true;
	}
	//choice between -f and -h input
	else if (a == "-f") // file input
	{
		f = true;
	}
	else if (a == "-h") // hex input
	{
		h = true;
	}
	else 
	{
		cout << "Invalid arguement\n";
		exit(EXIT_FAILURE);
	}
	return 0;
}

//convert string hex input of the notation 0x0000 to little endian format
string toLittleEndian(string s)
{
	string str = "";

	//str = str + s[4] + s[5] + s[2] + s[3];// 0x4a81 -> 0x814a
	str = str + s[2] + s[3] + s[4] + s[5];
	return str;
}

string parseFile(string fileName)
{
	ifstream inputFile(fileName.c_str());
	if(inputFile.fail())
	{
		cout << "file does not exist\n"
		exit(EXIT_FAILURE);
	}
	string str;
	getline(inputFile, str);

	return str;
}
//convert hex to binary
string hexToBinary(string s)
{
	string str = "";
	for (int i = 0; i < s.length(); i++)
	{
		switch (s[i])
		{
			case '0':
				str = str + "0000";
				break;
			case '1':
				str = str + "0001";
				break;
			case '2':
				str = str + "0010";
				break;
			case '3':
				str = str + "0011";
				break;
			case '4':
				str = str + "0100";
				break;
			case '5':
				str = str + "0101";
				break;
			case '6':
				str = str + "0110";
				break;
			case '7':
				str = str + "0111";
				break;
			case '8':
				str = str + "1000";
				break;
			case '9':
				str = str + "1001";
				break;
			case 'A':
			case 'a'://10
				str = str + "1010";
				break;
			case 'B':
			case 'b'://11
				str = str + "1011";
				break;
			case 'C':
			case 'c'://12
				str = str + "1100";
				break;
			case 'D':
			case 'd': //13
				str = str + "1101";
				break;
			case 'E':
			case 'e': //14
				str = str + "1110";
				break;
			case 'F':
			case 'f': //15
				str = str + "1111";
				break;
		}
	}
	return str;
}

//Converting binary to a date
void dateOutput(string binary)
{
	int year = 1980 + strtoull(binary.substr(0, 7).c_str(), NULL, 2);
	int month = strtoull(binary.substr(7, 4).c_str(), NULL, 2);
	int day = strtoull(binary.substr(11, 5).c_str(), NULL, 2);

	string monthAbb = "";

	switch (month)
	{
		case 1: monthAbb = "Jan"; break;
		case 2: monthAbb = "Feb"; break;
		case 3: monthAbb = "Mar"; break;
		case 4: monthAbb = "Apr"; break;
		case 5: monthAbb = "May"; break;
		case 6: monthAbb = "June"; break;
		case 7: monthAbb = "July"; break;
		case 8: monthAbb = "Aug"; break;
		case 9: monthAbb = "Sept"; break;
		case 10: monthAbb = "Oct"; break;
		case 11: monthAbb = "Nov"; break;
		case 12: monthAbb = "Dec"; break;
	}

	cout << "Date: " << monthAbb << " " << day << ", " << year << "\n";


}

//Converting binary to time
void timeOutput(string binary)
{
	string amPm = "AM";
	int hours = strtoull(binary.substr(0, 5).c_str(), NULL, 2);
	int minutes = strtoull(binary.substr(5, 6).c_str(), NULL, 2);
	int seconds = 2 * strtoull(binary.substr(11, 5).c_str(), NULL, 2);

	if (hours >= 12)
	{
		if (hours > 12)
		{
			hours = hours % 12;
		}
		amPm = "PM";
	}

	cout << "Time: " << hours << ":" << minutes << ":" << seconds << " " << amPm << "\n";
}


int main(int argc, char **argv) 
{

	if (argc < 4 )
	{
		cout << "Invalid number of arguements\n";
		exit(EXIT_FAILURE);

	}

	string hexInput = argv[3], input;
	for (int i = 1; i < (argc - 1); i++)
	{
		command_parser(argv[i]);	
	}
	
	//parsing if file
	if (f)
	{
		hexInput = parseFile(hexInput);
	}
	
	hexInput = toLittleEndian(hexInput);
	input = hexToBinary(hexInput);

	//parsing binary as if it's time
	if (T)
	{
		timeOutput(input);
	}
	//parsing binary as if it's a date
	else
	{
		dateOutput(input);
	}

	return 0;
}

