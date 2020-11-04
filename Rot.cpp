#include "Rot.h"

Rot::Rot() :m_npts(0), m_angle(0.f) {
	m_center.x = 0.f;
	m_center.y = 0.f;
	m_M.a = 1.f;
	m_M.b = 0.f;
	m_M.c = 0.f;
	m_M.d = 1.f;
}
Rot::~Rot() {
	;
}

void Rot::setAngleRad(float ang) {
	m_angle = ang;
}
void Rot::setAngleDeg(float ang) {
	float angRad = PI * ang / 180.f;
	setAngleRad(angRad);
}
bool Rot::Run(int innpts, s_pt inpt[], s_pt wallPts[]) {
	setMatrix();
	m_npts = innpts;
	for (int i = 0; i < m_npts; i++) {
		m_pts[i] = rotPt(inpt[i]);
	}
	for (int i = 0; i < NWALLPTS; i++) {
		m_wallPts[i] = setWallPt(wallPts[i]);
	}
	return true;
}
void Rot::setMatrix()
{
	m_M.a = cos(m_angle);
	m_M.b = sin(m_angle);
	m_M.c = -m_M.b;
	m_M.d = m_M.a;
}
s_pt Rot::addPts(s_pt& pt1, s_pt& pt2) {
	s_pt pt;
	pt.x = pt1.x + pt2.x;
	pt.y = pt1.y + pt2.y;
	return pt;
}
s_pt Rot::subPts(s_pt& pt1, s_pt& pt2) {
	s_pt pt;
	pt.x = pt1.x - pt2.x;
	pt.y = pt1.y - pt2.y;
	return pt;
}

s_pt Rot::rotVecToPt(s_pt& vecToPt)
{
	s_pt pt;
	pt.x = m_M.a*vecToPt.x + m_M.b*vecToPt.y;
	pt.y = m_M.c*vecToPt.x + m_M.d*vecToPt.y;
	return pt;
}
s_pt Rot::rotPt(s_pt& pt) {
	s_pt relPt = subPts(pt, m_center);
	s_pt rotPt = rotVecToPt(relPt);
	return addPts(rotPt, m_center);
}
s_pt Rot::setWallPt(s_pt& pt) {
	/*find wall pt location at reduced radius*/
	float radLen = sqrtf(pt.x * pt.x + pt.y * pt.y);
	float scaleFact = spokeLen / radLen;
	s_pt newPt = { pt.x * scaleFact, pt.y * scaleFact };
	return rotPt(newPt);
}