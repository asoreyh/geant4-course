#include "run.hh"

MyRunAction::MyRunAction() {}

MyRunAction::~MyRunAction() {}

void MyRunAction::BeginOfRunAction(const G4Run*){
    G4AnalysisManager *root = G4AnalysisManager::Instance();

    root->OpenFile("dose.root");
    root->CreateNtuple("EDep", "EDep");
    root->CreateNtupleDColumn("fEDep");
    root->FinishNtuple(0);
}

void MyRunAction::EndOfRunAction(const G4Run*){
    G4AnalysisManager *root = G4AnalysisManager::Instance();
    root->Write(); // always write before to close
    root->CloseFile();
}