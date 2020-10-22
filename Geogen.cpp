#include "Geogen.h"
Geogen::Geogen(): m_boxDim(4), m_gridsize(0.), m_Nspoke(0), m_Rspoke(0.f), m_Nstairs(0), m_Rstairs(0.f), m_spokePts(NULL), m_spokeWallPts(NULL), m_NspokePts(6),
m_NCurve_loop(0), m_NSplines(0), m_startSplineN(1000), m_startSpokeLineN(2001), m_startWallSpokeLineN(3000), m_startWallLineN(3400), m_startSurfCurveLoopN(100), m_startWallPtN(100), m_startSpokeWallPtN(200), m_Npts(0) 
{
	;
}
Geogen::~Geogen() { ; }
bool Geogen::Init(
	float boxDim, /*dimension of the box surrounding the airfoil*/
	float gridSize, /*last variable in the 4 float definition of a point for Gmsh*/
	int Nspoke, /*number of radial spokes in grid surrounding airfoil*/
	float Rspoke,
	int Nstairs,/*number of "stairs" grid lines crossing spokes*/
	float Rstairs
)
{
	m_boxDim = boxDim;
	m_gridsize = gridSize;
	m_Nspoke = Nspoke;
	m_Rspoke = Rspoke;
	m_Nstairs = Nstairs;
	m_Rstairs = Rstairs;

	m_spokePts = new int[m_NspokePts];/*currently this will only work with 6 spoke points*/
	m_spokeWallPts = new s_XY[m_NspokePts];
	m_NSplines = m_startSplineN;
	return true;
}
void Geogen::Release()
{
	delete[] m_spokeWallPts;
	delete[] m_spokePts;
}
bool Geogen::Run(s_pt* pt, int npts, std::string& ofname)
{
	npts--;/*don't write last point*/
	if (npts - 2 <= 0)
		return false;
	m_Npts = npts;
	std::ofstream outf(ofname, std::ios::out);
	writeHeader(outf);
	for (int i = 0; i < npts; i++) {
		writePt(outf, pt[i].x, pt[i].y, i);
	}

	writeBox(outf, m_startWallPtN);
	writeSpokeWallPts(outf, m_startSpokeWallPtN);
	writeAirfoilTrans(outf);
	writeLines(outf);
	makeSurfaces(outf);
	setTransSurfs(outf);
	writeRecombSurfs(outf);

	writeFooter(outf, npts);
	outf.close();
	return true;
}
bool Geogen::setSpokePoints(int pts[], s_XY wallPts[])
{
	for (int i = 0; i < m_NspokePts; i++) {
		m_spokePts[i] = pts[i];
	}
	for (int i = 0; i < (m_NspokePts); i++) {
		m_spokeWallPts[i] = wallPts[i];
	}
	return true;
}

bool Geogen::writePt(std::ofstream& outf, float x, float y, int npt)
{
	int ptindex = npt + 1;
	outf << "Point(" << ptindex << ") = {" << x << "," << y << ", 0," << m_gridsize << "};\n";
	return true;
}
bool Geogen::writeLine(std::ofstream& outf, int start_index, int next_index, int line_n)
{
	int start_i = start_index;
	int next_i = next_index;
	outf << "Line(" << line_n << ") = {" << start_i << "," << next_i << "}; ";
	return true;
}
bool Geogen::writeSpline(std::ofstream& outf, int pt1, int pt2)
{
	m_NSplines++;
	outf << "Spline(" << m_NSplines << ") = {" << pt1 << ":" << pt2 << "};\n";
	return true;
}

bool Geogen::writeCurveLoop_wTrans(std::ofstream& outf, int splineN)
{
	outf << "Curve Loop(" << m_NCurve_loop << ") = {" << splineN << "}; Transfinite Curve {" << splineN << "} = Nstairs Using Progression Rstairs;\n";
	m_NCurve_loop++;
	return true;
}
bool Geogen::writeCurveLoop_withSplineNTrans(std::ofstream& outf, int pt1, int pt2)
{
	if (writeSpline(outf, pt1, pt2))
		return writeCurveLoop_wTrans(outf, m_NSplines);
	return false;
}
bool Geogen::writeSpokeLine_wTrans(std::ofstream& outf, int pt1, int pt2, int line_n)
{
	writeLine(outf, pt1, pt2, line_n);
	outf << "Transfinite Curve{ " << line_n << " } = Nspoke Using Progression Rspoke;\n";
	return true;
}
bool Geogen::writeStairLine_wTrans(std::ofstream& outf, int pt1, int pt2, int line_n)
{
	writeLine(outf, pt1, pt2, line_n);
	outf << "Transfinite Curve{ " << line_n << " } = Nstairs Using Progression Rstairs;\n";
	return true;
}

bool Geogen::writeBox(std::ofstream& outf, int start_npt)
{
	/*write the box corner points that are not connected to spokes.*/
	int curPt = start_npt;
	float gridsize = 0.2f;
	//outf << "Point(" << curPt << ") = {" << -m_boxDim << "," << m_boxDim << ",0," << gridsize << "};\n";
	//curPt++;
	outf << "Point(" << curPt << ") = {" << -m_boxDim << "," << m_boxDim << ",0," << gridsize << "};\n";
	curPt++;
	outf << "Point(" << curPt << ") = {" << -m_boxDim << "," << -m_boxDim << ",0," << gridsize << "};\n";
	//curPt++;
	//outf << "Point(" << curPt << ") = {" << -m_boxDim << "," << -m_boxDim << ",0," << gridsize << "};\n";

	return true;
}
bool Geogen::writeSpokeWallPts(std::ofstream& outf, int start_npt)
{
	writePt(outf, m_boxDim, 0.f, start_npt);
	m_startSpokeWallPtN = start_npt+1;
	for (int i = 0; i < m_NspokePts; i++) {
		writePt(outf, m_spokeWallPts[i].x, m_spokeWallPts[i].y, start_npt + i + 1);
	}
	return true;
}
bool Geogen::writeAirfoilTrans(std::ofstream& outf)
{
	int spokeHi = m_NspokePts - 1;
	writeCurveLoop_withSplineNTrans(outf, 1, m_spokePts[0]);
	for (int i = 0; i < spokeHi; i++) {
		writeCurveLoop_withSplineNTrans(outf, m_spokePts[i], m_spokePts[i + 1]);
	}
	m_NSplines++;
	outf << "Spline(" << m_NSplines << ") = {" << m_spokePts[spokeHi] << ":" << m_Npts << "," << 1 << "};\n";
	return writeCurveLoop_wTrans(outf, m_NSplines);
}
bool Geogen::writeLines(std::ofstream& outf)
{
	outf << "\n//spokes directed outward\n";
	writeSpokeLine_wTrans(outf, 1, m_startSpokeWallPtN, m_startSpokeLineN);//line out from tail
	for (int i = 0; i < m_NspokePts; i++) {
		writeSpokeLine_wTrans(outf, m_spokePts[i], m_startSpokeWallPtN + i + 1, m_startSpokeLineN + i + 1);
	}

	outf << "\n//lines accross spoke ends\n";
	for (int i = 0; i < m_NspokePts; i++)
	{
		writeStairLine_wTrans(outf, m_startSpokeWallPtN + i, m_startSpokeWallPtN + i + 1, m_startWallSpokeLineN + i);
	}
	writeStairLine_wTrans(outf, m_startSpokeWallPtN + m_NspokePts, m_startSpokeWallPtN, m_startWallSpokeLineN + m_NspokePts);

	outf << "\n//corner lines\n";/*this is where the number of spokes asside from the back must be 6 (7 total)*/
	writeStairLine_wTrans(outf, m_startSpokeWallPtN + 2, m_startWallPtN, m_startWallLineN);
	writeStairLine_wTrans(outf, m_startWallPtN, m_startSpokeWallPtN + 3, m_startWallLineN + 1);
	writeStairLine_wTrans(outf, m_startSpokeWallPtN + 4, m_startWallPtN + 1, m_startWallLineN + 2);
	writeStairLine_wTrans(outf, m_startWallPtN + 1, m_startSpokeWallPtN + 5, m_startWallLineN + 3);

	return true;
}

bool Geogen::writeCurveLoop4(std::ofstream& outf, int l1, int l2, int l3, int l4, int curve_n)
{
	outf << "Curve Loop(" << curve_n << ") = {" << l1 << ", " << l2 << ", " << l3 << ", " << l4 << "};\n";
	return true;
}
bool Geogen::writeCurveLoop3(std::ofstream& outf, int l1, int l2, int l3, int curve_n)
{
	outf << "Curve Loop(" << curve_n << ") = {" << l1 << ", " << l2 << ", " << l3 << "};\n";
	return true;
}
bool Geogen::writeSurface(std::ofstream& outf, int curve_n, int surf_n) {
	outf << "Plane Surface(" << surf_n << ") = {" << curve_n << "};\n";
	return true;
}

bool Geogen::makeSurfaces(std::ofstream& outf)
{
	outf << "\n//Surfaces around airfoil\n";
	int cur_curve_n = m_startSurfCurveLoopN;
	int cur_surf_n = 1;
	for (int i = 0; i < m_NspokePts; i++) {
		writeCurveLoop4(outf, -(m_startSplineN + i+1), (m_startSpokeLineN + i), (m_startWallSpokeLineN + i), -(m_startSpokeLineN + 1 + i), cur_curve_n + i);
		writeSurface(outf, cur_curve_n + i, cur_surf_n + i);
		outf << "//\n";
	}
	writeCurveLoop4(outf, -(m_startSplineN + 7), (m_startSpokeLineN + 6), (m_startWallSpokeLineN + 6), -(m_startSpokeLineN), cur_curve_n + 6);
	writeSurface(outf, cur_curve_n + 6, cur_surf_n + 6);
	outf << "\n//Corner Surfaces\n";
	writeCurveLoop3(outf, m_startWallLineN, m_startWallLineN + 1, -(m_startWallSpokeLineN + 2), cur_curve_n + 7);
	writeSurface(outf, cur_curve_n + 7, cur_surf_n + 7);
	writeCurveLoop3(outf, m_startWallLineN + 2, m_startWallLineN + 3, -(m_startWallSpokeLineN + 4), cur_curve_n + 8);
	writeSurface(outf, cur_curve_n + 8, cur_surf_n + 8);
	outf << "\n";
	return true;
}
bool Geogen::setTransSurfs(std::ofstream& outf)
{
	outf << "\n//setting surfaces to transfinite\n";
	for (int i = 1; i <= 9; i++) {
		outf << "Transfinite Surface{" << i << "};\n";
	}
	return true;
}
bool Geogen::writeRecombSurfs(std::ofstream& outf)
{
	outf << "\n//recombining transfinite surfaces\n";
	for (int i = 1; i <= 9; i++) {
		outf << "Recombine Surface{" << i << "};\n";
	}
	return true;
}
bool Geogen::writeHeader(std::ofstream& outf)
{
	outf << "boxdim = " << m_boxDim << ";\n";
	outf << "Nspoke = " << m_Nspoke << "; Rspoke = " << m_Rspoke << ";\n";
	outf << "Nstairs = " << m_Nstairs << "; Rstairs = " << m_Rstairs << ";\n";
	return true;
}




bool Geogen::writeFooter(std::ofstream& outf, int npts)
{

	return true;
}