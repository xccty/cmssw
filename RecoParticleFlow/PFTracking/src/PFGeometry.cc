#include "RecoParticleFlow/PFTracking/interface/PFGeometry.h"
#include "DataFormats/GeometrySurface/interface/BoundCylinder.h"
#include "DataFormats/GeometrySurface/interface/BoundDisk.h"
#include "DataFormats/GeometrySurface/interface/SimpleCylinderBounds.h"
#include "DataFormats/GeometrySurface/interface/SimpleDiskBounds.h"

std::vector< float > PFGeometry::innerRadius_;
std::vector< float > PFGeometry::outerRadius_;
std::vector< float > PFGeometry::innerZ_;
std::vector< float > PFGeometry::outerZ_;
std::vector< ReferenceCountingPointer<BoundCylinder> > PFGeometry::cylinder_;
std::vector< ReferenceCountingPointer<BoundPlane> > PFGeometry::negativeDisk_;
std::vector< ReferenceCountingPointer<BoundPlane> > PFGeometry::positiveDisk_;
std::vector< float > PFGeometry::tanTh_;

PFGeometry::PFGeometry()
{
  if (!innerRadius_.size()) {
    // All distances are in cm
    // BeamPipe
    innerRadius_.push_back(2.5);
    outerRadius_.push_back(2.5);
    innerZ_.push_back(0.);
    outerZ_.push_back(500.);
    // PS1
    innerRadius_.push_back(45.0);
    outerRadius_.push_back(125.0);
    innerZ_.push_back(303.16);
    outerZ_.push_back(303.16);
    // PS2
    innerRadius_.push_back(45.0);
    outerRadius_.push_back(125.0);
    innerZ_.push_back(307.13);
    outerZ_.push_back(307.13);
    // ECALBarrel
    innerRadius_.push_back(129.0);
    outerRadius_.push_back(175.0);
    innerZ_.push_back(0.);
    outerZ_.push_back(304.5);
    // ECALEndcap
    innerRadius_.push_back(31.6);
    outerRadius_.push_back(171.1);
    innerZ_.push_back(317.0);
    outerZ_.push_back(388.0);
    // HCALBarrel
    innerRadius_.push_back(183.0);
    outerRadius_.push_back(285.0);
    innerZ_.push_back(0.);
    outerZ_.push_back(433.2);
    // HCALEndcap
    innerRadius_.push_back(31.6); // !!! Do not use : Probably wrong !!!    
    outerRadius_.push_back(285.0); // !!! Do not use : Probably wrong !!! 
    innerZ_.push_back(388.0);
    outerZ_.push_back(560.0);
    // HO Barrel
    innerRadius_.push_back(387.6);
    outerRadius_.push_back(410.2);
    innerZ_.push_back(0.);
    outerZ_.push_back(700.25);
    // HGC ECAL
    innerRadius_.push_back(31.3);
    outerRadius_.push_back(168.1);
    innerZ_.push_back(317.3);
    outerZ_.push_back(349.72);
    // HGC HCALF
    innerRadius_.push_back(35.38); 
    outerRadius_.push_back(227.582);
    innerZ_.push_back(360.63);
    outerZ_.push_back(425.89);
    // HGC HCALB
    innerRadius_.push_back(43.03);
    outerRadius_.push_back(266.88);
    innerZ_.push_back(439.65);
    outerZ_.push_back(524.1);


    // Define reference surfaces
    const float epsilon = 0.001; // should not matter at all
    Surface::RotationType rot;
    // BeamPipe
    cylinder_.push_back(new BoundCylinder(Surface::PositionType(0,0,0), rot, 
					  SimpleCylinderBounds(innerRadius_[BeamPipe], innerRadius_[BeamPipe], -outerZ_[BeamPipe], outerZ_[BeamPipe])));
    negativeDisk_.push_back(new Disk(Surface::PositionType(0,0,-outerZ_[BeamPipe]), rot, 
						    SimpleDiskBounds(0., innerRadius_[BeamPipe], -epsilon, epsilon)));
    positiveDisk_.push_back(new Disk(Surface::PositionType(0,0,outerZ_[BeamPipe]), rot, 
						    SimpleDiskBounds(0., innerRadius_[BeamPipe], -epsilon, epsilon)));
    tanTh_.push_back(innerRadius_[BeamPipe]/outerZ_[BeamPipe]);
    // PS1Wall
    cylinder_.push_back(new BoundCylinder(Surface::PositionType(0,0,0), rot, 
					  SimpleCylinderBounds(outerRadius_[PS1], outerRadius_[PS1], -outerZ_[PS1], outerZ_[PS1])));
    negativeDisk_.push_back(new Disk(Surface::PositionType(0,0,-outerZ_[PS1]), rot, 
						    SimpleDiskBounds(0., outerRadius_[PS1], -epsilon, epsilon)));
    positiveDisk_.push_back(new Disk(Surface::PositionType(0,0,outerZ_[PS1]), rot, 
						    SimpleDiskBounds(0., outerRadius_[PS1], -epsilon, epsilon)));
    tanTh_.push_back(outerRadius_[PS1]/outerZ_[PS1]);
    // PS2Wall
    cylinder_.push_back(new BoundCylinder(Surface::PositionType(0,0,0), rot, 
					  SimpleCylinderBounds(outerRadius_[PS2], outerRadius_[PS2], -outerZ_[PS2], outerZ_[PS2])));
    negativeDisk_.push_back(new Disk(Surface::PositionType(0,0,-outerZ_[PS2]), rot, 
						    SimpleDiskBounds(0., outerRadius_[PS2], -epsilon, epsilon)));
    positiveDisk_.push_back(new Disk(Surface::PositionType(0,0,outerZ_[PS2]), rot, 
						    SimpleDiskBounds(0., outerRadius_[PS2], -epsilon, epsilon)));
    tanTh_.push_back(outerRadius_[PS2]/outerZ_[PS2]);
    // ECALInnerWall
    cylinder_.push_back(new BoundCylinder(Surface::PositionType(0,0,0), rot, 
					  SimpleCylinderBounds(innerRadius_[ECALBarrel], innerRadius_[ECALBarrel], -innerZ_[ECALEndcap], innerZ_[ECALEndcap])));
    negativeDisk_.push_back(new Disk(Surface::PositionType(0,0,-innerZ_[ECALEndcap]), rot, 
						    SimpleDiskBounds(0., innerRadius_[ECALBarrel], -epsilon, epsilon)));
    positiveDisk_.push_back(new Disk(Surface::PositionType(0,0,innerZ_[ECALEndcap]), rot, 
						    SimpleDiskBounds(0., innerRadius_[ECALBarrel], -epsilon, epsilon)));
    tanTh_.push_back(innerRadius_[ECALBarrel]/innerZ_[ECALEndcap]);

    // HCALInnerWall
    cylinder_.push_back(new BoundCylinder(Surface::PositionType(0,0,0), rot, 
					  SimpleCylinderBounds(innerRadius_[HCALBarrel], innerRadius_[HCALBarrel], -innerZ_[HCALEndcap], innerZ_[HCALEndcap])));
    negativeDisk_.push_back(new Disk(Surface::PositionType(0,0,-innerZ_[HCALEndcap]), rot, 
						    SimpleDiskBounds(0., innerRadius_[HCALBarrel], -epsilon, epsilon)));
    positiveDisk_.push_back(new Disk(Surface::PositionType(0,0,innerZ_[HCALEndcap]), rot, 
						    SimpleDiskBounds(0., innerRadius_[HCALBarrel], -epsilon, epsilon)));
    tanTh_.push_back(innerRadius_[HCALBarrel]/innerZ_[HCALEndcap]);
    // HCALOuterWall
    cylinder_.push_back(new BoundCylinder(Surface::PositionType(0,0,0), rot, 
					  SimpleCylinderBounds(outerRadius_[HCALBarrel], outerRadius_[HCALBarrel], -outerZ_[HCALEndcap], outerZ_[HCALEndcap])));
    negativeDisk_.push_back(new Disk(Surface::PositionType(0,0,-outerZ_[HCALEndcap]), rot, 
						    SimpleDiskBounds(0., outerRadius_[HCALBarrel], -epsilon, epsilon)));
    positiveDisk_.push_back(new Disk(Surface::PositionType(0,0,outerZ_[HCALEndcap]), rot, 
						    SimpleDiskBounds(0., outerRadius_[HCALBarrel], -epsilon, epsilon)));
    tanTh_.push_back(outerRadius_[HCALBarrel]/outerZ_[HCALEndcap]);

    // HGCAL EE InnerWall
    cylinder_.push_back(new BoundCylinder(Surface::PositionType(0,0,0), rot, 
					  SimpleCylinderBounds(innerRadius_[ECALBarrel], innerRadius_[ECALBarrel], -innerZ_[HGC_ECAL], innerZ_[HGC_ECAL])));
    negativeDisk_.push_back(new Disk(Surface::PositionType(0,0,-innerZ_[HGC_ECAL]), rot, 
						    SimpleDiskBounds(0., innerRadius_[ECALBarrel], -epsilon, epsilon)));
    positiveDisk_.push_back(new Disk(Surface::PositionType(0,0,innerZ_[HGC_ECAL]), rot, 
						    SimpleDiskBounds(0., innerRadius_[ECALBarrel], -epsilon, epsilon)));
    tanTh_.push_back(innerRadius_[ECALBarrel]/innerZ_[HGC_ECAL]);
    // HGCAL EE OuterWall
    cylinder_.push_back(new BoundCylinder(Surface::PositionType(0,0,0), rot, 
					  SimpleCylinderBounds(outerRadius_[HGC_ECAL], outerRadius_[HGC_ECAL], -outerZ_[HGC_ECAL], outerZ_[HGC_ECAL])));
    negativeDisk_.push_back(new Disk(Surface::PositionType(0,0,-outerZ_[HGC_ECAL]), rot, 
						    SimpleDiskBounds(0., outerRadius_[HGC_ECAL], -epsilon, epsilon)));
    positiveDisk_.push_back(new Disk(Surface::PositionType(0,0,outerZ_[HGC_ECAL]), rot, 
						    SimpleDiskBounds(0., outerRadius_[HGC_ECAL], -epsilon, epsilon)));
    tanTh_.push_back(outerRadius_[HGC_ECAL]/outerZ_[HGC_ECAL]);

    // HGCAL HEF InnerWall
    cylinder_.push_back(new BoundCylinder(Surface::PositionType(0,0,0), rot, 
					  SimpleCylinderBounds(outerRadius_[HGC_ECAL], outerRadius_[HGC_ECAL], -innerZ_[HGC_HCALF], innerZ_[HGC_HCALF])));
    negativeDisk_.push_back(new Disk(Surface::PositionType(0,0,-innerZ_[HGC_HCALF]), rot, 
						    SimpleDiskBounds(0., outerRadius_[HGC_ECAL], -epsilon, epsilon)));
    positiveDisk_.push_back(new Disk(Surface::PositionType(0,0,innerZ_[HGC_HCALF]), rot, 
						    SimpleDiskBounds(0., outerRadius_[HGC_ECAL], -epsilon, epsilon)));
    tanTh_.push_back(outerRadius_[HGC_ECAL]/innerZ_[HGC_HCALF]);
    // HGCAL HEF OuterWall
    cylinder_.push_back(new BoundCylinder(Surface::PositionType(0,0,0), rot, 
					  SimpleCylinderBounds(outerRadius_[HGC_HCALF], outerRadius_[HGC_HCALF], -outerZ_[HGC_HCALF], outerZ_[HGC_HCALF])));
    negativeDisk_.push_back(new Disk(Surface::PositionType(0,0,-outerZ_[HGC_ECAL]), rot, 
						    SimpleDiskBounds(0., outerRadius_[HGC_HCALF], -epsilon, epsilon)));
    positiveDisk_.push_back(new Disk(Surface::PositionType(0,0,outerZ_[HGC_ECAL]), rot, 
						    SimpleDiskBounds(0., outerRadius_[HGC_HCALF], -epsilon, epsilon)));
    tanTh_.push_back(outerRadius_[HGC_HCALF]/outerZ_[HGC_HCALF]);

    // HGCAL HEB InnerWall
    cylinder_.push_back(new BoundCylinder(Surface::PositionType(0,0,0), rot, 
					  SimpleCylinderBounds(outerRadius_[HGC_HCALF], outerRadius_[HGC_HCALF], -innerZ_[HGC_HCALB], innerZ_[HGC_HCALB])));
    negativeDisk_.push_back(new Disk(Surface::PositionType(0,0,-innerZ_[HGC_HCALB]), rot, 
						    SimpleDiskBounds(0., outerRadius_[HGC_HCALF], -epsilon, epsilon)));
    positiveDisk_.push_back(new Disk(Surface::PositionType(0,0,innerZ_[HGC_HCALB]), rot, 
						    SimpleDiskBounds(0., outerRadius_[HGC_HCALF], -epsilon, epsilon)));
    tanTh_.push_back(outerRadius_[HGC_HCALF]/innerZ_[HGC_HCALB]);
    // HGCAL HEB OuterWall
    cylinder_.push_back(new BoundCylinder(Surface::PositionType(0,0,0), rot, 
					  SimpleCylinderBounds(outerRadius_[HGC_HCALB], outerRadius_[HGC_HCALB], -outerZ_[HGC_HCALB], outerZ_[HGC_HCALB])));
    negativeDisk_.push_back(new Disk(Surface::PositionType(0,0,-outerZ_[HGC_HCALB]), rot, 
						    SimpleDiskBounds(0., outerRadius_[HGC_HCALB], -epsilon, epsilon)));
    positiveDisk_.push_back(new Disk(Surface::PositionType(0,0,outerZ_[HGC_HCALB]), rot, 
						    SimpleDiskBounds(0., outerRadius_[HGC_HCALB], -epsilon, epsilon)));
    tanTh_.push_back(outerRadius_[HGC_HCALB]/outerZ_[HGC_HCALB]);
    
  }
}
