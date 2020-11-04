#include "ParseXYtoGeo.h"

int main()
{
	Parser parseAirfoil;
	std::string in_file_name("IOFiles/airfoilXY.txt");
	std::string ofname("IOFiles/airfoil_NACA_test1_20.geo"); //"airfoil_pts.obj"
	int pts[7];
	pts[0] = 1;
	pts[1] = 17;
	pts[2] = 26;
	pts[3] = 38;
	pts[4] = 44;
	pts[5] = 56;
	pts[6] = 65;
	s_pt wallPts[7];
	wallPts[0].x = 4;
	wallPts[0].y = 0;
	wallPts[1].x = 4;
	wallPts[1].y = 4;
	wallPts[2].x = -1;
	wallPts[2].y = 4;
	wallPts[3].x = -4;
	wallPts[3].y = 2;
	wallPts[4].x = -4;
	wallPts[4].y = -2;
	wallPts[5].x = -1;
	wallPts[5].y = -4;
	wallPts[6].x = 4;
	wallPts[6].y = -4;
	if (parseAirfoil.Run(in_file_name)) {
		Rot rotAirfoil;
		rotAirfoil.setAngleDeg(0.0f);
		rotAirfoil.Run(parseAirfoil.npts, parseAirfoil.pt, wallPts);
		Geogen writeAirfoil;
		//ObjGen writeAirfoil;
		writeAirfoil.Init();
		writeAirfoil.setSpokePoints(pts, rotAirfoil.m_wallPts);
		writeAirfoil.Run(rotAirfoil.m_pts, rotAirfoil.m_npts, ofname);
		writeAirfoil.Release();
	}
	return 0;
}