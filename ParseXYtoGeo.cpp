#include "ParseXYtoGeo.h"

int main()
{
	Parser parseAirfoil;
	std::string in_file_name("IOFiles/airfoilXY.txt");
	std::string ofname("IOFiles/airfoil_NACA_test0.geo"); //"airfoil_pts.obj"
	int pts[6];
	pts[0] = 14;
	pts[1] = 26;
	pts[2] = 38;
	pts[3] = 44;
	pts[4] = 56;
	pts[5] = 68;
	s_XY wallPts[6];
	wallPts[0].x = 4;
	wallPts[0].y = 4;
	wallPts[1].x = -1;
	wallPts[1].y = 4;
	wallPts[2].x = -4;
	wallPts[2].y = 2;
	wallPts[3].x = -4;
	wallPts[3].y = -2;
	wallPts[4].x = -1;
	wallPts[4].y = -4;
	wallPts[5].x = 4;
	wallPts[5].y = -4;
	if (parseAirfoil.Run(in_file_name)) {
		Geogen writeAirfoil;
		//ObjGen writeAirfoil;
		writeAirfoil.Init();
		writeAirfoil.setSpokePoints(pts, wallPts);
		writeAirfoil.Run(parseAirfoil.pt, parseAirfoil.npts, ofname);
		writeAirfoil.Release();
	}
	return 0;
}