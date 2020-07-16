#pragma once
#include <iostream>
#include <fstream>
#include <string>

#define MAXNUMPTS 300
#define NUMBERLEN 8
struct s_pt {
	float x;
	float y;
};
class Parser
{
public:
	s_pt pt[MAXNUMPTS];
	int npts;

	Parser();
	~Parser() { ; }
	bool Run(std::string& filename);
private:

	bool sendLineToPt(std::string& fline);
	size_t find0Or1(std::string& fline, size_t pos);
	float getNumber(std::string& fline, size_t startN);
};

