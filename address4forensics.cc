#include "stdafx.h"
#include "address4forensics.h"
#include <stdio.h>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <tuple>
#include <iostream>


output_pairs L;
output_pairs P;
output_pairs C;

output_pairs b;
output_pairs B;
output_pairs s;
output_pairs l;
output_pairs p;

output_pairs c;
output_pairs k;
output_pairs r;
output_pairs t;
output_pairs f;

int counter = 0;


//This function separates the comment with numbers, as some of the arguments are in the format "--command==12344".
//outString outputs the command, while the number string outputs the number
//If number returned is -1, then the command is of the format -command

int longFormCommand(string command)
{
	for (int i = 0; i < command.length(); i++)
	{
		if (command[i] == '=')
		{
			return (i + 1);
		}
	}
	return -1;
}

long long number_retriever(string s)
{
	int loc = longFormCommand(s);
	string number = "";
	if (loc > 0)
	{
		for (int i = loc; i < s.length(); i++)
		{
			number = number + s[i];
		}
		return stoll(number);
	}
	return -1;
}
string returnCommand(string s, int loc)
{
	string str = "";
	for (int i = 0; i < (loc-1); i++)
	{
		str = str + s[i];
	}
	return str;
}

//This function parses the particular command-line argument given
//op.flag is used to indicate whether the command needs to take the second argument into consideration.
void argument_analyzer(string a, long long parm)
{
	string command = a;
	int number = 0;
	long long par = number_retriever(a);
	if (par > 0)
	{
		parm = par;
		command = returnCommand(a, longFormCommand(a));
	}
	else
	{
		counter++;
	}


	if ( (command.compare("-L") == 0) || (command.compare("--logical") == 0))
	{
		L.flag = true;
		//TODO Write logic for -L
	}
	else if ((command.compare("-P") == 0) || (command.compare("--physical") == 0))
	{
		P.flag = true;
		//TODO Write logic for -P
	}
	else if ((command.compare("-C") == 0) || (command.compare("--cluster") == 0))
	{
		C.flag = true;
		//TODO Write logic for -C
	}
	else if ((command.compare("-b") == 0) || (command.compare("--partition-start") == 0))
	{
		b.flag = true;
		b.number = parm;
		//TODO Write logic for -b
		
	}
	else if ((command.compare("-B") == 0) || (command.compare("--byte-address") == 0))
	{
		B.flag = true;
		B.number = 512;
		counter--;
		//TODO Write logic for -B
	}
	else if ((command.compare("-s") == 0) || (command.compare("--sector-size") == 0))
	{
		s.flag = true;
		s.number = parm;
		B.number = parm;
		//TODO Write logic for -s
		
	}
	else if ((command.compare("-l") == 0) || (command.compare("--logical-known") == 0) )
	{
		l .flag = true;
		l.number = parm;
		//TODO Write logic for -l
		
	}
	else if ((command.compare("-p") == 0) || (command.compare("--physical-known") == 0 ))
	{
		p.flag = true;
		p.number = parm;
		//TODO Write logic for -p
		
	}
	else if ((command.compare("-c") == 0) || (command.compare("--cluster-known") == 0))
	{
		c.flag = true;
		c.number = parm;
		//TODO Write logic for -c
		
	}
	else if ((command.compare("-k") == 0) || (command.compare("--cluster-size") == 0))
	{
		k.flag = true;
		k.number = parm;
		//TODO Write logic for -k
		
	}
	else if ((command.compare("-r") == 0) || (command.compare("--reserved") == 0))
	{
		r.flag = true;
		r.number = parm;
		//TODO Write logic for -r 
		
	}
	else if ((command.compare("-t") == 0) || (command.compare("--fat-tables") == 0))
	{
		t.flag = true;
		t.number = parm;
		//TODO Write logic for -t
		
	}
	else if ((command.compare("-f") == 0) || (command.compare("--fat-length") == 0))
	{
		f.flag = true;
		f.number = parm;
		//TODO Write logic for -f
		
	}
	//If none of the arguments match, then throw an error to indicate invalid comment
	else 
	{
		throw runtime_error("Non-valid arguement");
	}
	
}


int main(int argc, char **argv) 
{
	argument_analyzer(argv[1], 0);
	string bk;
	for (counter = 2; counter<argc; counter++) 
	{
		bk = argv[counter];
		if (number_retriever(argv[counter]) < 0 && bk.compare("-B") != 0 )
		{
			argument_analyzer(argv[counter], stoll(argv[counter + 1]));
		}
		else
		{
			argument_analyzer(argv[counter], 0);
		}
	}

	long output;
	if (L.flag)
	{
		if (c.flag)
		{
			output = r.number + (t.number * f.number) + (c.number - 2) * k.number;
		}
		else if (p.flag)
		{
			output = p.number - b.number;
		}
		else
		{
			throw "Either -c or -p have to be given for the -L option";
		}
	}
	else if (P.flag)
	{
		if (c.flag)
		{
			output = b.number + r.number + (t.number * f.number) + (c.number - 2) * k.number;
		}
		else if(l.flag)
		{
			output = b.number + l.number;
		}
		else
		{
			throw "Either -c or -l have to be given for the -P option";
		}
	}
	else if (C.flag)
	{
		if (l.flag)
		{
			output = ((l.number - r.number - (t.number * f.number)) / k.number) + 2;
		}
		else if (p.flag)
		{
			output = ( ( p.number - b.number - r.number - (t.number * f.number)) / k.number) + 2;
		}
		else
		{
			cout << "Either -l or -p must be given for the -C option\n";
			exit(EXIT_FAILURE);
		}
	}

	if (B.flag)
	{
		output = output * B.number;
	}

	cout << output << "\n";

	return 0;
}
