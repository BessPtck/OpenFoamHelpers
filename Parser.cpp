#include "Parser.h"
Parser::Parser() : npts(0)
{
	;
}
bool Parser::Run(std::string& filename)
{
	std::ifstream inf(filename, std::ios::out);
	if (!inf.is_open()) {
		std::cerr << "ERROR: couldn't open file";
		return false;
	}
	std::string fline;
	while (std::getline(inf, fline)) {
		sendLineToPt(fline);
	}
	inf.close();
	return true;
}

bool Parser::sendLineToPt(std::string& fline)
{
	size_t startN = find0Or1(fline, 0);
	if (startN < 0 || startN>3)
		return false;
	size_t past_endN = fline.find(' ', startN);
	size_t endN = past_endN - 1;
	if (endN < 1)
		return false;
	float X = getNumber(fline, startN);
	startN = find0Or1(fline, past_endN);
	if (startN < 1)
		return false;
	startN--;
	float Y = getNumber(fline, startN);
	pt[npts].x = X;
	pt[npts].y = Y;
	if (npts < (MAXNUMPTS - 1))
		npts++;
	return true;
}
size_t Parser::find0Or1(std::string& fline, size_t pos) {
	size_t fpos = fline.find("1.", pos);
	if (fpos > 0 && fpos<3000)
		return fpos;
	return fline.find("0.", pos);
}
float Parser::getNumber(std::string& fline, size_t startN)
{
	std::string nStr = fline.substr(startN, NUMBERLEN);
	return std::stof(nStr);
}