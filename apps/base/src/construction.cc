#include "construction.hh"

// as always, first the constructor and destructor
MyDetectorConstruction::MyDetectorConstruction() {
}
MyDetectorConstruction::~MyDetectorConstruction() {
}

// now the construction function
G4VPhysicalVolume *MyDetectorConstruction::Construct() {
   // 1. your system is build using materials... 
   // 1.1 let's create hydrogen gas (H_2)
   // create the natural ocurring isotopes of H
   G4Isotope *H = new G4Isotope("H", 1, 1, 1.*g/mole);
   G4Isotope *D = new G4Isotope("D", 1, 2, 2.*g/mole);
   // create the natural element as a mix of isotopes
   G4Element *elH = new G4Element("Hydrogen", "H", 2);
   elH->AddIsotope(H, 99.985*perCent);
   elH->AddIsotope(D,  0.015*perCent);
   // create the H2 molecule as a material
   G4Material *matH2 = new G4Material("H2", 0.08375 * kg/m3, 1);
   matH2->AddElement(elH, 2);

    // instanciate the NIST manager:
    G4NistManager *nist = G4NistManager::Instance();
    // usually (but not always, world is made by Air, ie, G4_AIR)
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    // G4Material *worldMat2 = nist->FindOrBuildMaterial("G4_WATER");
    
    // 2. your world should have a shape. Let's do a box.
    // It always you have three volumes: 
    // solid (the shapes), logical (the materials), physicals (the magic)
    // 2.1 solid: name, x/2, y/2, z/2, use the units!!!
    G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
    // 2.2 logical: assesing the material: solid, material, name
    G4LogicalVolume *logicWorld = new G4LogicalVolume(
        solidWorld, worldMat, "logicWorld"
    );

    // 2.3 physical: where the magic occurs: rotation, position(x,y,z), 
    //     associated logical volume, name, motherVolume?, bools (negate 
    //     volumes!), numberOfCopies, check for overlaps(always)
    G4VPhysicalVolume *physWorld = new G4PVPlacement(
        0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true
    );
    return physWorld;
}
