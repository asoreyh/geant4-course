#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction){
    fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction() {}

void MySteppingAction::UserSteppingAction(const G4Step *step) {
    //ONCE the fSensitiveVolume is defined
    // *volume is the LogicalVolume where the particle is located
    G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

    // we need  to get an object including the volumes we constructed
    const MyDetectorConstruction *detectorConstruction = 
        static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    // and *fSensitiveVolume is our selected sensitive volume
    G4LogicalVolume *fSensitiveVolume = detectorConstruction->GetSensitiveVolume();
    // only get deposited energy if we are in the sensitive volume
    if(volume != fSensitiveVolume)
        return;
    
    // original
    // deposited energy is stored at each step
    G4double stepEDep = step->GetTotalEnergyDeposit(); // this is for all volumes
    fEventAction->AddEDep(stepEDep);
}