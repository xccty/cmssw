#include "SimpleArborClusterizer.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "RecoParticleFlow/PFClusterProducer/interface/Arbor.hh"
#include "RecoParticleFlow/PFClusterProducer/interface/ArborHit.hh"
#include "RecoParticleFlow/PFClusterProducer/interface/ArborTool.hh"

#ifdef PFLOW_DEBUG
#define LOGVERB(x) edm::LogVerbatim(x)
#define LOGWARN(x) edm::LogWarning(x)
#define LOGERR(x) edm::LogError(x)
#define LOGDRESSED(x) edm::LogInfo(x)
#else
#define LOGVERB(x) LogTrace(x)
#define LOGWARN(x) edm::LogWarning(x)
#define LOGERR(x) edm::LogError(x)
#define LOGDRESSED(x) LogDebug(x)
#endif

using namespace arbor;

namespace {
  bool greaterByEnergy(const std::pair<unsigned,double>& a,
		       const std::pair<unsigned,double>& b) {
    return a.second > b.second;
  }
}

void SimpleArborClusterizer::
buildClusters(const edm::Handle<reco::PFRecHitCollection>& input,
	      const std::vector<bool>& rechitMask,
	      const std::vector<bool>& seedable,
	      reco::PFClusterCollection& output) {  
  const reco::PFRecHitCollection& hits = *input;
//  std::vector<TVector3> arbor_points;
  std::vector< ArborHit > inputABHit;
  std::vector<unsigned> hits_for_arbor;
  arbor::branchcoll branches;  
  TVector3 currHitPos; 
  int LayerNum = 0;
  int StaveNum = 0;  

  // get the seeds and sort them descending in energy
  inputABHit.reserve(hits.size());
  hits_for_arbor.reserve(hits.size());  
  for( unsigned i = 0; i < hits.size(); ++i ) {
    if( !rechitMask[i] ) continue;
    const math::XYZPoint& pos = hits[i].position();
    hits_for_arbor.emplace_back(i);
    //inputABHit.emplace_back(10*pos.x(),10*pos.y(),10*pos.z());
	
    currHitPos.SetXYZ(10*pos.x(),10*pos.y(),10*pos.z()); 
    LayerNum = int(abs(pos.z())); //forgive me!

    ArborHit a_abhit(currHitPos, LayerNum, 0, StaveNum, 0);	//Assume always in the same stave... last arguement refers to subdetectorID
    inputABHit.emplace_back(a_abhit);

  }

  branches = arbor::Arbor(inputABHit, _cellSize, _layerThickness, _NCellThreshold);
  output.reserve(branches.size());
  
  for( auto& branch : branches ) {
    if( _killNoiseClusters && branch.size() <= _maxNoiseClusterSize ) {
      continue;
    }
    // sort hits by radius
    std::sort(branch.begin(),branch.end(),
	      [&](const arbor::branch::value_type& a,
		  const arbor::branch::value_type& b) {
		return ( hits[hits_for_arbor[a]].position().Mag2() <
			 hits[hits_for_arbor[b]].position().Mag2()   );
	      });
    const reco::PFRecHit& inner_hit = hits[hits_for_arbor[branch[0]]];
    PFLayer::Layer inner_layer = inner_hit.layer();
    const math::XYZPoint& inner_pos = inner_hit.position();    
    output.emplace_back(inner_layer,branch.size(),
			inner_pos.x(),inner_pos.y(),inner_pos.z());
    reco::PFCluster& current = output.back();
    current.setSeed(inner_hit.detId());
    for( const auto& hit : branch ) {
      const reco::PFRecHitRef& refhit = 
	reco::PFRecHitRef(input,hits_for_arbor[hit]);
      current.addRecHitFraction(reco::PFRecHitFraction(refhit,1.0));
    }
    LogDebug("SimpleArborClusterizer")
      << "Made cluster: " << current << std::endl;
  }
}
