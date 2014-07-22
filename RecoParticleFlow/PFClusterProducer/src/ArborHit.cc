#include <RecoParticleFlow/PFClusterProducer/interface/Arbor.hh>
#include <iostream>
#include <vector>

namespace arbor{

ArborHit::ArborHit( TVector3 hitPos, int hitLayer, double hitTime, int stave, int subD )
{
	setHit( hitPos, hitLayer, hitTime, stave, subD );
}

void ArborHit::setHit(TVector3 hitPos, int hitLayer, double hitTime, int stave, int subD )
{
	m_hitTime = hitTime;
	m_hitLayer = hitLayer; 
	m_hitPos = hitPos; 
	m_subD = subD; 
	m_stave = stave; 
}

}
