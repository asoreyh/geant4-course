#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "g4root.hh"
#include "run.hh"
#include "G4SystemOfUnits.hh"

class MyEventAction : public G4UserEventAction {
public:
    MyEventAction(MyRunAction*);
    ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    void AddEDep(G4double EDep);
    void GetMass(G4double mass);

private: 
    G4double fEDep;
    G4double fMass;
};


#endif