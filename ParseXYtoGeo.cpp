#include "ParseXYtoGeo.h"

int main()
{
	Parser parseAirfoil;
	std::string in_file_name("IOFiles/airfoilXY.txt");
	std::string ofname("IOFiles/airfoil_NACA.geo"); //"airfoil_pts.obj"
	if (parseAirfoil.Run(in_file_name)) {
		Geogen writeAirfoil;
		//ObjGen writeAirfoil;
		writeAirfoil.Run(parseAirfoil.pt, parseAirfoil.npts, ofname);
	}
	return 0;
}