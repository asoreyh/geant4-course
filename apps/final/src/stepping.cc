#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction){
    fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction() {}

void MySteppingAction::UserSteppingAction(const G4Step *step) {
    // deposited energy is stored at each step
    G4double stepEDep = step->GetTotalEnergyDeposit(); // this is for all volumes
    fEventAction->AddEDep(stepEDep);
}