#include "MaSRunAction.h"
#include "MaSAnalysis.h"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

MaSRunAction::MaSRunAction():G4UserRunAction()
{
	;
}

MaSRunAction::~MaSRunAction()
{
	;
}

void MaSRunAction::BeginOfRunAction(const G4Run* aRun)
{
	G4cout << "### Run " << aRun -> GetRunID() << " start." << G4endl;
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	char RunId[10];
	sprintf(RunId, "%d", aRun -> GetRunID());
	G4String fileName = "Run";
	fileName += RunId;
	fileName += "depE";
	analysisManager->OpenFile(fileName);

	analysisManager->CreateNtuple("depE","Edep");
	analysisManager->CreateNtupleDColumn("Edep");
	analysisManager->FinishNtuple();
}
void MaSRunAction::EndOfRunAction(const G4Run* aRun)
{
	G4int nofEvents = aRun->GetNumberOfEvent();
	if ( nofEvents == 0 ) return;
	
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->Write();
	analysisManager->CloseFile();
	
	delete G4AnalysisManager::Instance();
}	