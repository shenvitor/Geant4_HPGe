// Modified by Vitor Jose Shen
// at Uppsala University
// part of the assignments within course "modelling and simulation of particle transport" 
//
#ifndef MaSDetectorConstruction_h
#define MaSDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"

class MaSDetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		MaSDetectorConstruction();
		virtual ~MaSDetectorConstruction();
		virtual G4VPhysicalVolume* Construct();
		
	private:
		G4VPhysicalVolume* fWorldP;
		G4Material *fWorldMaterial;

		G4VSolid* fDetectorSolid;
		G4Material *fDetectorMaterial;
		G4LogicalVolume* detectorL;

		G4Material *fCapMaterial;
};
#endif
