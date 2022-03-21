#ifndef MaSEventAction_h
#define MaSEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include "G4THitsMap.hh"

class MaSEventAction : public G4UserEventAction
{
	public:
		MaSEventAction();
		virtual ~MaSEventAction();
		virtual void BeginOfEventAction(const G4Event* );
		virtual void EndOfEventAction(const G4Event* );
		void SetPrintModulo(G4int value);
	private:
		G4THitsMap<G4double>* GetHitsCollection(const G4String& hcName, const G4Event* event) const;
		G4double GetSum(G4THitsMap<G4double>* hitsMap) const;
		void PrintEventStatistics(G4double Edep);
		G4int fPrintModulo;
};

inline void MaSEventAction::SetPrintModulo(G4int value)
{
	fPrintModulo = value;
}
#endif