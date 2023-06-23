#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "g4root.hh"  //always! root geant4 standalone libraries

class MyRunAction : public G4UserRunAction {
public:
    MyRunAction();
    ~MyRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

#endif