import FWCore.ParameterSet.Config as cms

#### PF CLUSTER HGCEF ####

#cleaning 

#seeding
_noseeds_HGCHEF = cms.PSet(
    algoName = cms.string("PassThruSeedFinder")   
)

#topo clusters
#for arbor this is more a pre-clustering step to find little clusters
_arborTopoClusterizer_HGCHEF = cms.PSet(
    algoName = cms.string("IntraLayerClusteringAlgorithm"),    
    IntraLayerMaxDistance = cms.double( 96.0 ), # hit separation in mm
    ShouldSplitClusterInSingleCaloHitClusters = cms.bool(False), # splitsmall clusters
    MaximumSizeForClusterSplitting = cms.uint32( 3 ), #largest of small clusters to split
    thresholdsByDetector = cms.VPSet( )
)

#the real arbor clusterizer
_manqiArborClusterizer_HGCHEF = cms.PSet(
    algoName = cms.string("SimpleArborClusterizer"), 
    # use basic pad sizes in HGCEE
    cellSize = cms.double(10.0),
    layerThickness = cms.double(55.0),
    killNoiseClusters = cms.bool(True),
    maxNoiseClusterSize = cms.uint32(3),
    thresholdsByDetector = cms.VPSet( )
)

#weights for layers from P.Silva (26 June 2014)
weight_vec = [0.0902 for x in range(12)]
weight_vec.extend([0.1051 for x in range(10)])

# MIP effective to 1.0/GeV (from fit to data of P. Silva) for HEF
#f(x) = a/(1-exp(-bx - c))
# x = cosh(eta)
# a = 11.33333 <--- from straight average of Pedro's data
# b = 1e6 
# c = 1e6

#for HEB
# a = 1.0 <--- from straight average of Pedro's data
# b = 1e6 
# c = 1e6

_HGCHEF_HadronEnergy = cms.PSet(
    algoName = cms.string("HGCHEHadronicEnergyCalibrator"),
    weights = cms.vdouble(weight_vec),
    effMip_to_InverseGeV_a_HEF = cms.double(1.0), #11.33333
    effMip_to_InverseGeV_b_HEF = cms.double(1e6),
    effMip_to_InverseGeV_c_HEF = cms.double(1e6),
    MipValueInGeV_HEF = cms.double(85.0*1e-6),
    effMip_to_InverseGeV_a_HEB = cms.double(1.0),
    effMip_to_InverseGeV_b_HEB = cms.double(1e6),
    effMip_to_InverseGeV_c_HEB = cms.double(1e6),
    MipValueInGeV_HEB = cms.double(1498.4*1e-6)
)

particleFlowClusterHGCHEF = cms.EDProducer(
    "PFClusterProducer",
    recHitsSource = cms.InputTag("particleFlowRecHitHGCHEF"),
    recHitCleaners = cms.VPSet(),
    seedFinder = _noseeds_HGCHEF,
    initialClusteringStep = _manqiArborClusterizer_HGCHEF,
    pfClusterBuilder = cms.PSet( ),
    positionReCalc = cms.PSet(),
    energyCorrector = _HGCHEF_HadronEnergy
)

