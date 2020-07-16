#pragma once
#include "Parser.h"

class Geogen {
public:
	Geogen():m_lineTag(1), m_doInnerLines(false), m_doLines(false), m_boxDim(4),m_gridsize(0.) { ; }
	~Geogen() { ; }
	bool Run(s_pt* pt, int npts, std::string& ofname);
private:
	int m_lineTag;
	bool m_doInnerLines;
	bool m_doLines;
	float m_boxDim;
	float m_gridsize;
	bool writeHeader(std::ofstream& outf);
	bool writePt(std::ofstream& outf, float x, float y, int npt);/*Point(#) = {1.4, 0.4, 0., 1.0}; for 2d 0. & 1.0 repeat at end*/
	bool writeLine(std::ofstream& outf, int start_index, int next_index);/*Line(#) = {pt#, pt#}; Line(2) = {2, 3};*/
	bool writePtFooter(std::ofstream& outf,int npts);
	bool writeBox(std::ofstream& outf, int start_npt);
	bool writeFooter(std::ofstream& outf, int npts);
};
bool Geogen::writeHeader(std::ofstream& outf)
{
	outf << "boxdim = " << m_boxDim<<";\n";
	m_gridsize = 0.01;//m_boxDim / 20.f;
	return true;
}
bool Geogen::Run(s_pt* pt, int npts, std::string& ofname)
{
	npts--;/*don't write last point*/
	if (npts - 2 <= 0)
		return false;
	std::ofstream outf(ofname, std::ios::out);
	writeHeader(outf);
	for (int i = 0; i < npts; i++) {
		writePt(outf, pt[i].x, pt[i].y, i);
	}
	if (m_doLines) {
		for (int i = 0; i < (npts - 1); i++) {
			writeLine(outf, i, i + 1);
		}
		writeLine(outf, npts - 1, 0);
		/*write the internal lines*/
		if (m_doInnerLines) {
			int halfpt = npts / 2;/*40 out of 81*/
			for (int i = 1; i < (halfpt); i++) {/*2 to 40*/
				int ops_i = npts - 1 - i;/*80 to 41*/
				writeLine(outf, i, ops_i);
			}
		}
	}
	writePtFooter(outf, npts);
	writeBox(outf, 100);
	writeFooter(outf, npts);
	outf.close();
	return true;
}
bool Geogen::writePt(std::ofstream& outf, float x, float y, int npt)
{
	int ptindex = npt + 1;
	outf << "Point(" << ptindex << ") = {" << x << "," << y << ", 0,"<<m_gridsize<<"};\n";
	return true;
}
bool Geogen::writeLine(std::ofstream& outf, int start_index, int next_index)
{
	int start_i = start_index + 1;
	int next_i = next_index + 1;
	outf << "Line(" << m_lineTag << ") = {" << start_i << "," << next_i << "};\n";
	m_lineTag++;
	return true;
}
bool Geogen::writePtFooter(std::ofstream& outf,int npts)
{
	outf << "\nSpline(1000) = {1:" << npts << ",1};\n";
	outf << "\nCurve Loop(1) = {1000};\n\n";
	return true;
}
bool Geogen::writeBox(std::ofstream& outf, int start_npt)
{
	int curPt = start_npt;
	float gridsize = 0.2;
	outf << "Point(" << curPt << ") = {" << -m_boxDim << "," << m_boxDim << ",0," << gridsize << "};\n";
	curPt++;
	outf << "Point(" << curPt << ") = {" << m_boxDim << "," << m_boxDim << ",0," << gridsize << "};\n";
	curPt++;
	outf << "Point(" << curPt << ") = {" << m_boxDim << "," << -m_boxDim << ",0," << gridsize << "};\n";
	curPt++;
	outf << "Point(" << curPt << ") = {" << -m_boxDim << "," << -m_boxDim << ",0," << gridsize << "};\n";

	for (int i = start_npt; i < curPt; i++) {
		outf << "Line(" << m_lineTag << ") = {" << i << "," << i + 1 << "};\n";
		m_lineTag++;
	}
	outf << "Line(" << m_lineTag << ") = {" << curPt << "," << start_npt << "};\n";
	m_lineTag++;
	outf << "Curve Loop(2) = {1, 2, 3, 4};\n";
	return true;
}
bool Geogen::writeFooter(std::ofstream& outf, int npts)
{
	outf << "\nPlane Surface(1) = {2, 1};\n";
	outf << "Extrude{0, 0, 1} {\n";
	outf << "  Surface{1};\n  Layers{1};\n  Recombine;\n}\n";
	return true;
}