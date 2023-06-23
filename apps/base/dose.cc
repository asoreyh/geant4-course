// 0. I/O operations
#include <iostream>
// 1. G4RunManager class
#include "globals.hh"
#include "G4RunManager.hh"
// 2. User interface
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
// 3. Visualization
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"

// once the detector construction is ready, include it
#include "construction.hh"
// once the physics list is ready, include it
#include "physics.hh" // comment if you are using PL factory
// #include "G4PhysListFactory.hh" // uncoment if you are using PL factory

// once the action is ready, include it
#include "action.hh"


int main(G4int argc, char** argv) {

    //1. create the G4RunManager object
    G4RunManager *runManager = new G4RunManager();
    // once the detector is created, then define it
    // but we are still not ready for init
    runManager->SetUserInitialization(new MyDetectorConstruction());

    // once the MyPhysicsList() is created, reigster it
    runManager->SetUserInitialization(new MyPhysicsList()); // comment if you are using PL factory

    // PhysicsLists, uncomment if your are not using PhysicsConstructors
    /* 
    const G4String physicsListName = "FTFP_BERT_HP";
    G4PhysListFactory physicsListFactory;
    physicsListFactory.SetVerbose(1);
    G4VModularPhysicsList *physicsList = physicsListFactory.GetReferencePhysList(physicsListName);
    runManager->SetUserInitialization(physicsList);
    */
    // once the action is created, reigster it
    runManager->SetUserInitialization(new MyActionInitialization());

    //5. Initialize the runManager
    runManager->Initialize();  

    //2. create the user interfase
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    //3. visualization manager
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();
    
    G4UImanager *UIManager = G4UImanager::GetUIpointer();
    // after the physics, draw the OGL and set the viewpoint...
    UIManager->ApplyCommand("/vis/open OGL");
    UIManager->ApplyCommand("/vis/viewer/set/viewpointVector 1 0.7 0.7");
    UIManager->ApplyCommand("/vis/ogl/set/displayListLimit 50000");
    // ... draw the volumes
    UIManager->ApplyCommand("/vis/drawVolume");
    // after actions ... draw the particle trajectory
    UIManager->ApplyCommand("/vis/viewver/set/autorefresh true");
    UIManager->ApplyCommand("/vis/scene/add/trajectories smooth");
    // for viewing many trajectories together, comment if no needed
    UIManager->ApplyCommand("/vis/scene/endOfEventAction accumulate 300");
    // display colors by Id instead of charge
    UIManager->ApplyCommand("/vis/modeling/trajectories/create/drawByParticleID");

    // 4. start the session - and compile to see what happens
    ui->SessionStart();

    return 0;
}