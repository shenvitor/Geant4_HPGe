// Modified by Vitor Jose Shen
// at Uppsala University
// part of the assignments within course "modelling and simulation of particle transport" 
//
#include "MaSDetectorConstruction.h"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4SubtractionSolid.hh"

MaSDetectorConstruction::MaSDetectorConstruction() : G4VUserDetectorConstruction()
{
}

MaSDetectorConstruction::~MaSDetectorConstruction()
{
}

G4VPhysicalVolume* MaSDetectorConstruction::Construct()
{
  	G4cout<<"Construct"<<G4endl;
  
	G4NistManager* nistManager = G4NistManager::Instance();
	G4bool fromIsotopes = false;
	
  /**
     Create the world solid volume with G4Tubs with, outer radius 0.5 m and length 1 m. 
     the length change to 0.5m	
  **/
	G4double worldOutRadius = 0.5*m;
	G4double worldInRadius = 0.0*m;
	G4double worldLength = 1*m;
	G4double worldStartAngle = 0.;
	G4double worldSpanAngle = 360.*deg;
  
	G4Tubs* worldS = new G4Tubs("worldS", 		//its name
				     worldInRadius, 
				     worldOutRadius, 
				     worldLength/2.,
				     worldStartAngle, 
				     worldSpanAngle);
  /**
     Create a world logical volume composted of air
  **/
 	fWorldMaterial = nistManager->FindOrBuildMaterial("G4_AIR", fromIsotopes);
	G4LogicalVolume* worldL = new G4LogicalVolume(worldS, 		//its solid
						      fWorldMaterial, 	//its material
						      "worldL");	//its name
  
  /**
     Place the world logical volume with help of the "G4VPhysicalVolume *fWorldP" defined in the header file
  **/
	fWorldP = new G4PVPlacement(0, 			//no rotation
				    G4ThreeVector(), 	//at (0,0,0)
				    worldL, 		//its logical volume
				    "World", 		//its name
				    0, 			//its mother volume
				    false, 		//no boolean operations
				    0, 			//copy number
				    false);		//checking overlaps
 
  //*************************************************************************** 
  //*************************************************************************** 
  /**
     Create the active Ge detector solid volume as given in the FLUKA exercise 
  **/
  	G4double detectorOutRadius = 29.75*mm;
	G4double detectorInRadius = 0.0*mm;
	G4double detectorLength = 53.9*mm;
	G4double detectorStartAngle = 0.;
	G4double detectorSpanAngle = 360.*deg;
  
	G4ThreeVector detectorPosition = G4ThreeVector(0,0,31.65*mm); 	//4+0.7+53.9/2 = 31.65mm
	G4ThreeVector holePosition = G4ThreeVector(0,0,39.3*mm);	//4+0.7+14.6+40/2 = 39.3mm
	G4ThreeVector translation = G4ThreeVector(0,0,6.95*mm);		// Relative position of hole the tub: 53.9/2-40/2 = 6.95
	
	// The solid of detector tub without hole
	G4Tubs* detectorS = new G4Tubs("detectorS", 		//its name
				     detectorInRadius, 
				     detectorOutRadius, 
				     detectorLength/2.,
				     detectorStartAngle, 
				     detectorSpanAngle);

	// The solid of hole 
	G4double HoleOutRadius = 6.5*mm;
	G4double HoleInRadius = 0.0*mm;
	G4double HoleLength = 40*mm;

	G4Tubs* detectorHole = new G4Tubs("detectorHole", 		//its name
				     HoleInRadius, 
				     HoleOutRadius, 
				     HoleLength/2.,
				     detectorStartAngle, 
				     detectorSpanAngle);

	G4RotationMatrix* yRot = new G4RotationMatrix;
	yRot->rotateY(0. *rad);
	G4SubtractionSolid* FinalDetectorS = new G4SubtractionSolid("HPGe",detectorS,detectorHole
								    //);
								    ,yRot,
								    translation);
								    //holePosition);

	fDetectorSolid = FinalDetectorS;
 	//fDetectorSolid = detectorS;
 
  /**
     Create a active Ge detector logical volume composted of Ge with help of the "G4LogicalVolume* detectorL" defined in the header file
  **/

	fDetectorMaterial = nistManager -> FindOrBuildMaterial("G4_Ge",fromIsotopes);  

	detectorL = new G4LogicalVolume(fDetectorSolid, 	//its solid
					fDetectorMaterial, 	//its material
					"detectorL");		//its name

 /**
     The physical volume
  **/	
	new G4PVPlacement(0, 			//no rotation
			  detectorPosition, 	//at (x,y,z) 
			  //since we assume the z=0 is the position of Al cap
			  detectorL, 		//its logical volume
			  "detector", 		//its name
			  worldL,		//its mother volume
			  true,		//boolean operation true or false
			  0,			//copy number 
			  false);		//checking overlaps

  /**
	Implement the rest of the geometry as given in the FLUKA exercise
  **/

	// The Ge dead layer
	G4double deadOutRadius = 30.45*mm;  	//60.9/2=30.45

//	not thick enough since using wrong inner radius	(previously -0.35)
//	G4double deadInRadius = 30.1*mm;	//60.2/2=30.1
//	G4double deadInRadius = 29.75*mm;	//30.45-0.7=29.75

//	update the preiovus setting by inner raidus only wrapped the side surface and miss the front side(lid)
//	redefine using the subtraction.
//	update
	G4double deadInRadius = 0.0*mm;	

	G4double deadLength = 54.6*mm;

	G4Tubs* deadS = new G4Tubs("deadS", 		//its name
				     deadInRadius, 
				     deadOutRadius, 
				     deadLength/2.,
				     detectorStartAngle, 
				     detectorSpanAngle);

//	update	
	G4ThreeVector translationD = G4ThreeVector(0,0,0.35*mm);	
// Relative position of deadLayer and Ge crystal: 54.6/2- 53.9/2 =
// 27.3 - 26.95 = 0.35
	G4SubtractionSolid* deadLayerS = new G4SubtractionSolid("deadLayer",deadS,detectorS
								    //);
								    ,yRot,
								    translationD);
								    //holePosition);

	G4LogicalVolume* deadL = new G4LogicalVolume(//deadS, 			//its solid
						     deadLayerS,		//its solid
						     fDetectorMaterial, 	//its material
						     "deadL");			//its name
	
	G4ThreeVector deadPosition = G4ThreeVector(0,0,31.3*mm); 	//1+3+54.6/2 = 31.3mm
	new G4PVPlacement(0, 			//no rotation
			  deadPosition, 	//at (x,y,z) 
			  //since we assume the z=0 is the position of Al cap
			  deadL, 		//its logical volume
			  "dead_layer", 		//its name
			  worldL,		//its mother volume
			  false,		//boolean operation true or false
			  0,			//copy number 
			  false);		//checking overlaps


	// The Aluminium cap
	// This new geometry feature will be save in this separate file 
	G4double capOutRadius = 40.5*mm;	// 81/2 = 40.5

	//wrong thickness: should be 1mm here original divided by 2 and
	//G4double capInRadius = 40.*mm;		// 80/2 = 40
	//G4double capInRadius = 39.5*mm;
	
//	update
//	use subtraction otherwise by inner radius will miss the front surface and only surround the side surface.
	G4double capInRadius = 0.0*mm;

	G4double capLength = 58.6*mm;
	G4Tubs* capS = new G4Tubs("capS", 		//its name
				     capInRadius, 	//0
				     capOutRadius, 	//40.5
				     capLength/2.,
				     detectorStartAngle, 
				     detectorSpanAngle);


	//update
	// add a solid with the volume of Ge crystal plus all the empty volume between it and the cap.
	G4double subOutRadius = 39.5*mm;		//81/2=40.5 --> 40.5-1=39.5mm
	G4double subLength = capLength - 1*mm;

	G4Tubs* subS = new G4Tubs("subS", 		//its name
				     capInRadius, 	// 0 
				     subOutRadius, 	//39.5mm
				     subLength/2.,
				     detectorStartAngle, 
				     detectorSpanAngle);

//	update
	G4ThreeVector translationC = G4ThreeVector(0,0,0.5*mm);	
// Relative position of cap and volume inside the cap: 58.6/2- 57.6/2 =0.5
//	use subtraction otherwise by inner radius will miss the front surface and only surround the side surface.
	G4SubtractionSolid* finalCapS = new G4SubtractionSolid("finalCapS",capS,subS
								    //);
								    ,yRot,
								    translationC);
								    //holePosition);




	fCapMaterial = nistManager -> FindOrBuildMaterial("G4_Al",fromIsotopes);  
	G4LogicalVolume* capL = new G4LogicalVolume(//capS, 			//its solid
						    finalCapS,
						    fCapMaterial, 	//its material
						    "capL");			//its name

	G4ThreeVector capPosition = G4ThreeVector(0,0,29.3*mm); 	//58.6/2 = 29.3mm
	new G4PVPlacement(0, 			//no rotation
			  capPosition, 	//at (x,y,z) 
			  //since we assume the z=0 is the position of Al cap
			  capL, 		//its logical volume
			  "Al_Cap", 		//its name
			  worldL,		//its mother volume
			  false,		//boolean operation true or false
			  0,			//copy number 
			  false);		//checking overlaps

  /**
     This part is used to create a sensitve detector of the active Ge logical volume
  **/
  G4MultiFunctionalDetector* gDetector = new G4MultiFunctionalDetector("gDetector");
  G4VPrimitiveScorer* primitive = new G4PSEnergyDeposit("Edep");
  
  gDetector->RegisterPrimitive(primitive);
  
  G4SDManager::GetSDMpointer()->AddNewDetector(gDetector);
  detectorL -> SetSensitiveDetector(gDetector);
  
  /**
     This part give different colours to world logical volume and the Ge logical volume
  **/
  G4VisAttributes* worldVisAtt = new G4VisAttributes(G4Colour(.5,.5,.5));	//gray
  worldVisAtt->SetVisibility(false);
  worldL -> SetVisAttributes(worldVisAtt);
  
   
  G4VisAttributes* detVisAtt= new G4VisAttributes(G4Colour(1.0,0.0,0.0));	//red
  detVisAtt->SetVisibility(true);
  detectorL -> SetVisAttributes(detVisAtt);
   
  G4VisAttributes* deadVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,0.0));	//green
  deadVisAtt->SetVisibility(true);
  deadL -> SetVisAttributes(deadVisAtt);
    
  G4VisAttributes* capVisAtt= new G4VisAttributes(G4Colour(0.0,0.0,1.0));	//blue
  capVisAtt->SetVisibility(true);
  capL -> SetVisAttributes(capVisAtt);
  /**
     Return the geometry
  **/
  return fWorldP;
}
