#include "action.hh"

MyActionInitialization::MyActionInitialization() {}
MyActionInitialization::~MyActionInitialization() {}

void MyActionInitialization::Build() const {
    MyPrimaryGenerator *generator = new MyPrimaryGenerator();
    SetUserAction(generator);

    // once created, we are informing Geant4 that we create user defined actions

    // after creating the run.hh/.cc we can create the RunAction interface
    MyRunAction *runAction = new MyRunAction();
    SetUserAction(runAction);

    //after creating the event.hh/.cc and stepping.hh/.cc we can create the interfaces
    MyEventAction *eventAction = new MyEventAction(runAction);
    SetUserAction(eventAction);
    MySteppingAction *steppingAction = new MySteppingAction(eventAction);
    SetUserAction(steppingAction);
}

MyPrimaryGenerator::MyPrimaryGenerator(){
    fParticleGun = new G4ParticleGun(1);
}
MyPrimaryGenerator::~MyPrimaryGenerator(){
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) {
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "e-";
    G4double particleKEnergy = 10. * MeV;
    G4ThreeVector pos(0., 0., 0.);
    G4ThreeVector momdir(0., 0., 1.);
    G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
    
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(momdir);
    fParticleGun->SetParticleEnergy(particleKEnergy);
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

// and finally inform our application to draw the trajectory -> dose.cc