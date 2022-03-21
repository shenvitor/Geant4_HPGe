#include "MaSEventAction.h"
#include "MaSAnalysis.h"

#include "G4SDManager.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"


MaSEventAction::MaSEventAction():G4UserEventAction(), fPrintModulo(10000)
{
;
}

MaSEventAction::~MaSEventAction()
{
;
}

G4THitsMap<G4double>* 
MaSEventAction::GetHitsCollection(const G4String& hcName,const G4Event* event) const
{
	G4int hcID = G4SDManager::GetSDMpointer() -> GetCollectionID(hcName);
	G4THitsMap<G4double>* hitsCollection = static_cast<G4THitsMap<G4double>*>(event -> GetHCofThisEvent() -> GetHC(hcID));
	
	if (! hitsCollection) {
		G4cerr << "Cannot access hitsCollection " << hcName << G4endl;
		exit(1);
	}
	
	return hitsCollection;
}

G4double MaSEventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
	G4double sumValue = 0;
	std::map<G4int, G4double*>::iterator it;
	for ( it = hitsMap -> GetMap() -> begin(); it != hitsMap -> GetMap() -> end(); it++) {
		sumValue += *(it -> second);
	}
	return sumValue;
}

void MaSEventAction::PrintEventStatistics(G4double Edep)
{
	G4cout
    << "   Edetector: total energy: " 
    << std::setw(7) << G4BestUnit(Edep, "Energy")
	<< G4endl;
}

void MaSEventAction::BeginOfEventAction(const G4Event* event)
{
	G4int eventID = event->GetEventID();
	if ( eventID % fPrintModulo == 0) { 
		G4cout << "\n---> Begin of event: " << eventID << G4endl;
	}
}

void MaSEventAction::EndOfEventAction(const G4Event* event)
{
	G4double Edep = GetSum(GetHitsCollection("gDetector/Edep", event));
	if(Edep > 0.0) {
		G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
		
		analysisManager->FillNtupleDColumn(0, Edep);
		analysisManager->AddNtupleRow();
	}
	G4int eventID = event->GetEventID();
	if ( eventID % fPrintModulo == 0) {
		G4cout << "---> End of event: " << eventID << G4endl;
		PrintEventStatistics(Edep);
	}
}
