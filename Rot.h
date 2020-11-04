#pragma once
#ifndef ROT_H
#define ROT_H
#include "Parser.h"

constexpr auto PI = 3.14159f;
constexpr auto spokeLen = 3.f;
/*matrix 
a b
c d
*/
struct s_M {
	float a;
	float b;
	float c;
	float d;
};
class Rot {
public:
	s_pt m_pts[MAXNUMPTS];
	int m_npts;
	s_pt m_wallPts[NWALLPTS];

	Rot();
	~Rot();

	void setAngleRad(float ang);
	void setAngleDeg(float ang);
	bool Run(int innpts, s_pt inpt[], s_pt wallPts[]);
private:
	s_pt m_center;
	float m_angle;/*rotation angle in radians*/
	s_M m_M;

	/*initalization*/
	void setMatrix();
	/*utility*/
	s_pt addPts(s_pt& pt1, s_pt& pt2);
	s_pt subPts(s_pt& pt1, s_pt& pt2);
	/*       */
	/* rotation */
	s_pt rotVecToPt(s_pt& vecToPt);
	s_pt rotPt(s_pt& pt);
	s_pt setWallPt(s_pt& pt);
	/*          */

};
#endif