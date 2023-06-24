#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

// 1. System of Units and Physical Constants (not mandatory, but... always!)
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
// 2. NIST class, needed for standard materiales (idem)
#include "G4NistManager.hh"
// 3. detector construction class
#include "G4VUserDetectorConstruction.hh"
// 6. Volumes: physical, logicals and placements
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
// some standard shapes
#include "G4Box.hh"
// #include "G4Sphere.hh"
// #include "G4Tubs.hh"

// 4. choose the name of your class
class MyDetectorConstruction : public G4VUserDetectorConstruction {
// 5. The class constructor and destructors, they are public
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();
// 6. the constructor of the physical volume
//    it will construct the physical volume of your system
    G4VPhysicalVolume *Construct();

// ONCE the deposited energy is calculated for the world, we could 
// proceed to define the sensitive volume
    G4LogicalVolume *GetSensitiveVolume() const {
        return fSensitiveVolume;
    }

private: 
    G4LogicalVolume *fSensitiveVolume;
};
#endif