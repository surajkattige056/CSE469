#include <stdio.h>
#include <string>
#include <iostream>
#include <tuple>

struct output_pairs{
	int number = 0;
	bool flag = false;
	bool error = false;	
};

class address4forensics{
	public:
		output_pairs argument_analyzer(std::string a, std::string b);
		std::tuple<std::string, std::string, int> number_retriever(std::string s);   
        
};
