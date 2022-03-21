// Modified by Vitor Jose Shen
// at Uppsala University
// part of the assignments within course "modelling and simulation of particle transport" 
//
#ifndef MaSPrimaryGeneratorAction_h
#define MaSPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "Randomize.hh"

#include "G4ParticleGun.hh"
#include "G4Event.hh"

class G4ParticleGun;
class G4Event;
class G4GeneralParticleSource;


class MaSPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
	public:
		MaSPrimaryGeneratorAction();
		virtual ~MaSPrimaryGeneratorAction();
		virtual void GeneratePrimaries(G4Event* );
		
		G4GeneralParticleSource* GetGeneralParticleSource() {return fGPS;}

		void SetRandomFlag(G4bool);

	private:
		//G4ParticleGun* fParticleGun;
		G4GeneralParticleSource* fGPS;
};
#endif

	
