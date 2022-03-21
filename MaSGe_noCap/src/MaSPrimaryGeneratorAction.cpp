// Modified by Vitor Jose Shen
// at Uppsala University
// part of the assignments within course "modelling and simulation of particle transport" 
//
#include "MaSPrimaryGeneratorAction.h"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"

MaSPrimaryGeneratorAction::MaSPrimaryGeneratorAction()
	: G4VUserPrimaryGeneratorAction()
{
	G4int nofParticles = 1;
	fParticleGun = new G4ParticleGun(nofParticles);
	G4ParticleDefinition* particleDefinition 
	= G4ParticleTable::GetParticleTable()->FindParticle("gamma"); 
	fParticleGun->SetParticleDefinition(particleDefinition);
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
	fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -250.*mm));
	fParticleGun->SetParticleEnergy(661.7*keV);
}

MaSPrimaryGeneratorAction::~MaSPrimaryGeneratorAction()
{
	delete fParticleGun;
}

void MaSPrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
	fParticleGun->GeneratePrimaryVertex(anEvent);
}



  
