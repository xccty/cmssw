import FWCore.ParameterSet.Config as cms

# Base configurations for HGCal digitizers

# ECAL
hgceeDigitizer = cms.PSet( accumulatorType   = cms.string("HGCDigiProducer"),
                           hitCollection     = cms.string("HGCHitsEE"),
                           digiCollection    = cms.string("HGCDigisEE"),
                           maxSimHitsAccTime = cms.uint32(100),
                           bxTime            = cms.int32(25),
                           digitizationType  = cms.uint32(0),
                           makeDigiSimLinks  = cms.bool(False),
                           digiCfg = cms.PSet( mipInKeV      = cms.double(55.1),
                                               lsbInMIP      = cms.double(0.25),
                                               mip2noise     = cms.double(7.0),
                                               adcThreshold  = cms.uint32(2),
                                               doTimeSamples = cms.bool(True)
                                               )
                           )

# HCAL front
hgchefrontDigitizer = cms.PSet( accumulatorType   = cms.string("HGCDigiProducer"),
                                hitCollection  = cms.string("HGCHitsHEfront"),
                                digiCollection = cms.string("HGCDigisHEfront"),
                                maxSimHitsAccTime = cms.uint32(100),
                                bxTime            = cms.int32(25),
                                digitizationType  = cms.uint32(0),
                                makeDigiSimLinks  = cms.bool(False),
                                digiCfg = cms.PSet( mipInKeV      = cms.double(85.0),
                                                    lsbInMIP      = cms.double(0.25),
                                                    mip2noise     = cms.double(7.0),
                                                    adcThreshold  = cms.uint32(2),
                                                    doTimeSamples = cms.bool(True) )
                                )
                                                    

# HCAL back
hgchebackDigitizer = cms.PSet( accumulatorType   = cms.string("HGCDigiProducer"),
                               hitCollection = cms.string("HGCHitsHEback"),
                               digiCollection = cms.string("HGCDigisHEback"),
                               maxSimHitsAccTime = cms.uint32(100),
                               bxTime            = cms.int32(25),
                               digitizationType  = cms.uint32(1),
                               makeDigiSimLinks  = cms.bool(False),
                               digiCfg = cms.PSet( mipInKeV = cms.double(1498.4),
                                                   lsbInMIP = cms.double(0.25),
                                                   mip2noise = cms.double(5.0),
                                                   adcThreshold  = cms.uint32(4),
                                                   doTimeSamples = cms.bool(True),
                                                   caliceSpecific = cms.PSet( nPEperMIP = cms.double(11.0),
                                                                              nTotalPE  = cms.double(1156),
                                                                              xTalk     = cms.double(0.25),
                                                                              sdPixels  = cms.double(3.0) )
                                                   )
                               )



                           


