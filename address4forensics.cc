#include "address4forensics.h"
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include <tuple>
#include <iostream>


//This function separates the comment with numbers, as some of the arguments are in the format "--command==12344".
//outString outputs the command, while the number string outputs the number
//If number returned is -1, then the command is of the format -command
std::tuple<std::string, std::string, int> address4forensics::number_retriever(std::string s){
	std::string outString = "", number = "-1";
	for(int i = 0; i < s.length(); i++){
		if(s[i] == '='){
			number = "";
			for(int j = i + 1; j < s.length(); j++){
				number = number + s[j];
			}
			return std::make_tuple(outString, number, std::stoi(number));
		}
		outString = outString + s[i];
	}
	return std::make_tuple(outString, number, std::stoi(number));
}

//This function parses the particular command-line argument given
//op.flag is used to indicate whether the command needs to take the second argument into consideration.
output_pairs address4forensics::argument_analyzer(std::string a, std::string b){
	output_pairs op;
	std::string command, number_string;
	int number;
	std::tie(command, number_string, number) = number_retriever(a);

	//This check is done to see if the command is of the type '-command'
	if(number < 0){
		op.flag = true;
		number = std::stoi(b);
	}
	
	if((command=="-L") or (command =="--logical")){
		//TODO Write logic for -L
	}
	else if((command =="-P") or (command =="--physical")){
		//TODO Write logic for -P
	}
	else if((command =="-C") or (command =="--cluster")){
		//TODO Write logic for -C
	}
	else if((command =="-b") or (command =="--partition-start")){

		//TODO Write logic for -b
		return op;
	}
	else if((command =="-B") or (command == "--byte-address")){
		//TODO Write logic for -B
	}
	else if((command =="-s") or (command == "--sector-size")){
		//TODO Write logic for -s
		return op;
	}
	else if((command == "-l") or (command == "--logical-known")){
		//TODO Write logic for -l
		return op;
	}
	else if((command == "-p") or (command == "--physical-known")){
		//TODO Write logic for -p
		return op;
	}
	else if((command == "-c") or (command == "--cluster-known")){
		//TODO Write logic for -c
		return op;
	}
	else if((command =="-k") or (command == "--cluster-size")){
		//TODO Write logic for -k
		return op;
	}
	else if((command =="-r") or (command == "--reserved")){
		//TODO Write logic for -r 
		return op;
	}
	else if((command == "-t") or (command == "--fat-tables")){
		//TODO Write logic for -t
		return op;
	}
	else if((command == "-f") or (command == "--fat-length")){
		//TODO Write logic for -f
		return op;
	}
	//If none of the arguments match, then throw an error to indicate invalid comment
	else{
		op.error = true;
	}
	return op;
}


int main(int argc, char **argv) {
	std::string a, b;
	int output = 0;
	output_pairs op;
	address4forensics addFor;
	for(int i=1; i<argc; i++){
		a=argv[i];
		if((i + 1) < argc){
			b = argv[i+1];
		}
		op = addFor.argument_analyzer(a, b);

	//If the input comment is invalid, then return -1
		if(op.error == true){
			return -1;
		}
		if(op.flag==true){
			i = i + 1;
		}
		output = output + op.number;
		std::cout<<a<<"\n";
	}
	return output;
}
