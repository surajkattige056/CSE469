#include <stdio.h>
#include <iostream>
#include <fstream>
#include <tuple>

#include "mac_conversion.h"


int mac_conversion::command_parser(std::string a, std::string b) {
	if(a == "-T") {
		//TODO Write logic for -T
	}
	else if( a == "-D") {
		//TODO Write logic for -D
	}
	else if (a == "-f") {
		
		std::string  hex_value;
		std::ifstream in_file;
		in_file.open(b);
		in_file >> hex_value;
		//TODO Write logic for -f
	}
	else if(a =="-h") {
		std::string hex_value = b;
		//TODO Write logic when -h is given
	}
	
	//This means the user has given an invalid input
	else {
		return -1;
	}
	return 0;
}	


int main(int argc, char **argv) {

	std::string a, b;
	mac_conversion mc;
	int number;
	for(int i = 1; i < argc ; i++) {
		a = argv[i];
		if((i + 1) < argc) {
			b = argv[i+1];
		}
		number = mc.command_parser(a, b);
		if(number == -1){
			std::cout << "INVALID INPUT";
			return -1;
		}
	}
	std::cout << number;
	return 0;
}
