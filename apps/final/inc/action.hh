#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

class MyActionInitialization : public G4VUserActionInitialization {
public:
    MyActionInitialization();
    ~MyActionInitialization();

    virtual void Build() const; // our main function
};

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction {
public:
   MyPrimaryGenerator();
   ~MyPrimaryGenerator(); 

   virtual void GeneratePrimaries(G4Event*);

private: 
    G4ParticleGun *fParticleGun;

};
#endif
