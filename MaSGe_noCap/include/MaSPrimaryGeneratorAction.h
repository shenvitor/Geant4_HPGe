#ifndef MaSPrimaryGeneratorAction_h
#define MaSPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "Randomize.hh"

#include "G4ParticleGun.hh"
#include "G4Event.hh"

class MaSPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
	public:
		MaSPrimaryGeneratorAction();
		virtual ~MaSPrimaryGeneratorAction();
		virtual void GeneratePrimaries(G4Event* );
		
	private:
		G4ParticleGun* fParticleGun;
};
#endif

	