#pragma once
#include "Parser.h"

class ObjGen {
public:
	ObjGen() { ; }
	~ObjGen() { ; }

	bool Run(s_pt* pt, int npts, std::string& ofname);
private:
	bool writeVertex(std::ofstream& outf, float x, float y);
};

bool ObjGen::Run(s_pt* pt, int npts, std::string& ofname)
{
	npts--;/*dont write last point*/
	if (npts - 2 <= 0)
		return false;
	std::ofstream outf(ofname, std::ios::out);
	for (int i = 0; i < npts; i++) {
		writeVertex(outf, pt[i].x, pt[i].y);
	}
	outf.close();
	return true;
}
bool ObjGen::writeVertex(std::ofstream& outf, float x, float y)
{
	outf << "v " << x << " " << y << " " << 0.0 << " " << 1.0 << "\n";
	return true;
}