import FWCore.ParameterSet.Config as cms

#### PF CLUSTER HGCEE ####

#cleaning 

#seeding
_noseeds_HGCEE = cms.PSet(
    algoName = cms.string("PassThruSeedFinder")   
)

#for arbor this is more a pre-clustering step to find little clusters
_arborTopoClusterizer_HGCEE = cms.PSet(
    algoName = cms.string("IntraLayerClusteringAlgorithm"),    
    IntraLayerMaxDistance = cms.double( 19.0 ), # hit separation in mm
    ShouldSplitClusterInSingleCaloHitClusters = cms.bool(False), # splitsmall clusters
    MaximumSizeForClusterSplitting = cms.uint32( 3 ), #largest of small clusters to split
    thresholdsByDetector = cms.VPSet( )
)
_simplePosCalcHGCEE =  cms.PSet(
    algoName = cms.string("SimplePositionCalc"),
    minFractionInCalc = cms.double(0.0)
)

#the real arbor clusterizer
_manqiArborClusterizer_HGCEE = cms.PSet(
    algoName = cms.string("SimpleArborClusterizer"), 
    # use basic pad sizes in HGCEE
    cellSize = cms.double(10.0),
    layerThickness = cms.double(16.0),
    killNoiseClusters = cms.bool(True),
    maxNoiseClusterSize = cms.uint32(3),
    thresholdsByDetector = cms.VPSet( )
)

_arborClusterizer_HGCEE = cms.PSet(
    algoName = cms.string("ArborConnectorClusteringAlgorithm"), 
    # these are taken from the settings for Fine Granularity in ArborPFA
    MaximumForwardDistanceForConnection = cms.double(60.0), #in mm
    MaximumTransverseDistanceForConnection = cms.double(40.0), #in mm
    AllowForwardConnectionForIsolatedObjects = cms.bool(False),
    ShouldUseIsolatedObjects = cms.bool(True),
    MaximumNumberOfKeptConnectors = cms.uint32(5),
    OrderParameterAnglePower = cms.double(1.0),
    OrderParameterDistancePower = cms.double(0.5),
    minFractionToKeep = cms.double(1e-7)
)

#weights for layers from P.Silva (24 June 2014)
weight_vec = [0.42]
weight_vec.extend([1.00 for x in range(10)])
weight_vec.extend([1.61 for x in range(10)])
weight_vec.extend([2.44 for x in range(10)])

# MIP effective to 1.0/GeV (from fit to data of P. Silva)
#f(x) = a/(1-exp(-bx - c))
# x = cosh(eta)
# a = 168.0
# b = 0.6871
# c = 0.9038

_HGCEE_ElectronEnergy = cms.PSet(
    algoName = cms.string("HGCEEElectronEnergyCalibrator"),
    weights = cms.vdouble(weight_vec),
    effMip_to_InverseGeV_a = cms.double(168.0),
    effMip_to_InverseGeV_b = cms.double(0.6871),
    effMip_to_InverseGeV_c = cms.double(0.9038),
    MipValueInGeV = cms.double(55.1*1e-6)
)

particleFlowClusterHGCEE = cms.EDProducer(
    "PFClusterProducer",
    recHitsSource = cms.InputTag("particleFlowRecHitHGCEE"),
    recHitCleaners = cms.VPSet(),
    seedFinder = _noseeds_HGCEE,
    initialClusteringStep = _manqiArborClusterizer_HGCEE,
    pfClusterBuilder = cms.PSet( ), #_arborClusterizer_HGCEE,
    positionReCalc = cms.PSet( ), #_simplePosCalcHGCEE,
    energyCorrector = _HGCEE_ElectronEnergy
)

