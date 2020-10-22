#pragma once
#include "Parser.h"
struct s_XY {
	float x;
	float y;
};
class Geogen {
public:
	Geogen();
	~Geogen();
	bool Init(
		float boxDim = 4.f, /*dimension of the box surrounding the airfoil*/
		float gridSize = 0.01f, /*last variable in the 4 float definition of a point for Gmsh*/
		int Nspoke = 201, /*number of radial spokes in grid surrounding airfoil*/
		float Rspoke = 1.00f,
		int Nstairs = 41,/*number of "stairs" grid lines crossing spokes*/
		float Rstairs = 1.00f
	);
	void Release();
	bool setSpokePoints(int pts[], s_XY wallPts[]);
	bool Run(s_pt* pt, int npts, std::string& ofname);
private:
	float m_boxDim;
	float m_gridsize;
	int   m_Nspoke;
	float m_Rspoke;
	int   m_Nstairs;
	float m_Rstairs;

	int* m_spokePts;
	s_XY* m_spokeWallPts;
	int m_NspokePts;
	int m_NCurve_loop;
	int m_NSplines;

	int m_startWallPtN;
	int m_startSpokeWallPtN;
	int m_startSplineN;
	int m_startSpokeLineN;
	int m_startWallLineN;
	int m_startWallSpokeLineN;
	int m_startSurfCurveLoopN;

	int m_Npts;

	bool writePt(std::ofstream& outf, float x, float y, int npt);/*Point(#) = {1.4, 0.4, 0., 1.0}; for 2d 0. & 1.0 repeat at end*/
	bool writeLine(std::ofstream& outf, int start_index, int next_index, int line_n);/*Line(#) = {pt#, pt#}; Line(2) = {2, 3};*/
	bool writeSpline(std::ofstream& outf, int pt1, int pt2); /*Spline(3000) = {'pt1':'pt2'};*/
	bool writeCurveLoop_wTrans(std::ofstream& outf, int splineN);/*Curve Loop(1) = {3000}; Transfinite Curve {3000} = Nair Using Progression Rair;*/
	bool writeCurveLoop_withSplineNTrans(std::ofstream& outf, int pt1, int pt2);/*uses writeSpline, makes a spline between points into a transfinite curve
															Spline(3000) = {38:44}; where 38=pt1, 44=pt2
															Curve Loop(1) = {3000}; Transfinite Curve {3000} = Nair Using Progression Rair;*/
	bool writeSpokeLine_wTrans(std::ofstream& outf, int pt1, int pt2, int line_n);
	bool writeStairLine_wTrans(std::ofstream& outf, int pt1, int pt2, int line_n);


	bool writeBox(std::ofstream& outf, int start_npt);
	bool writeSpokeWallPts(std::ofstream& outf, int start_npt);
	bool writeAirfoilTrans(std::ofstream& outf);
	bool writeLines(std::ofstream& outf);

	bool writeCurveLoop4(std::ofstream& outf, int l1, int l2, int l3, int l4, int curve_n);/*Curve Loop(8) = {3007, 1003, -3001, -1001};*/
	bool writeCurveLoop3(std::ofstream& outf, int l1, int l2, int l3, int curve_n);
	bool writeSurface(std::ofstream& outf, int curve_n, int surf_n);/*Plane Surface(1) = {8};*/
	bool makeSurfaces(std::ofstream& outf);

	bool setTransSurfs(std::ofstream& outf);
	bool writeRecombSurfs(std::ofstream& outf);
	
	bool writeHeader(std::ofstream& outf);
	bool writeFooter(std::ofstream& outf, int npts);
};

