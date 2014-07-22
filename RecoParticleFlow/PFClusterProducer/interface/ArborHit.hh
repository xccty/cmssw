#ifndef _POINT_H_
#define _POINT_H_

#include "TVector3.h"
#include <iostream>

namespace arbor{

class ArborHit
{
	double m_hitTime; 
	int m_hitLayer; 
	TVector3 m_hitPos; 
	int m_subD; 
	int m_stave; 

	public:
	
	// ArborHit();
	ArborHit( TVector3 hitPos, int hitLayer, double hitTime, int stave, int subD );
	
	void setHit( TVector3 hitPos, int hitLayer, double hitTime, int stave, int subD );

	double GetTime()
	{
		return m_hitTime;
	} 
	int GetLayer()
	{
		return m_hitLayer;
	} 
	TVector3 GetPosition()
	{ 
		return m_hitPos;
	}
	int GetSubD()
	{
		return m_subD; 
	}
	int GetStave()
	{
		return m_stave; 
	}
};

}
#endif
