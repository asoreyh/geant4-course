#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

// after create the run.hh/.cc, include it 
#include "run.hh"

// after create the event.hh/.cc and stepping.hh/.cc include them
#include "event.hh"
#include "stepping.hh"

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
