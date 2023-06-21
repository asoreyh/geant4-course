#ifndef PHYSICS_HH
#define PHYSICS_HH

// 1. As usual, include the corresponding G4 classes, using standard constructors
#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"

// 2. Class definition
class MyPhysicsList : public G4VModularPhysicsList {
public:
    MyPhysicsList();
    ~MyPhysicsList();
};

#endif