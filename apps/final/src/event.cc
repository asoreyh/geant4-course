#include "event.hh"

MyEventAction::MyEventAction(MyRunAction*) {
    fEDep = 0.;
}

MyEventAction::~MyEventAction(){}

void MyEventAction::BeginOfEventAction(const G4Event*) {
    // we want to get the deposited energy for each event, then 
    // we need to put it to 0. each time the event starts.
    // Otherwise, we will get the total accumulated Ed (later)

    //comment if you want the total accumulated energy
    // first test in an event basis
    // fEDep = 0.; // final! we want the accumulated energy, so comment 
}

void MyEventAction::EndOfEventAction(const G4Event*) {

    // once the discussion on fEDep is over, change it
    G4double fAbsDose = 0.;
    if (fMass > 0)
        fAbsDose = (fEDep / joule) / fMass;
     
    G4cout << "Energy deposition: " << fEDep << " MeV. Mass: " << fMass << " kg. Dose: " << fAbsDose << " Gy." << G4endl;

    G4AnalysisManager *root = G4AnalysisManager::Instance();
    root->FillNtupleDColumn(0, fEDep);
    root->AddNtupleRow(0);
}

void MyEventAction::AddEDep(G4double EDep) {
    fEDep += EDep;  
}

void MyEventAction::GetMass(G4double mass) {
    fMass = mass;
}