#include "physics.hh"

// 1. Create the constructor
MyPhysicsList::MyPhysicsList() {
    RegisterPhysics (new G4EmStandardPhysics()); // EM constructor
    RegisterPhysics (new G4OpticalPhysics()); // for optical processes
 }

// 2. Create the destructor
MyPhysicsList::~MyPhysicsList() {
}
// 3. Register in the main app file ->