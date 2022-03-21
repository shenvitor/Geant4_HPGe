#ifndef MaSRunAction_h
#define MaSRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include "G4Run.hh"

class MaSRunAction : public G4UserRunAction
{
	public:
		MaSRunAction();
		virtual ~MaSRunAction();
		virtual void BeginOfRunAction(const G4Run* run);
		virtual void EndOfRunAction(const G4Run* run);
};
#endif