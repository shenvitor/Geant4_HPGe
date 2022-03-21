#include "MaSDetectorConstruction.h"
#include "MaSPrimaryGeneratorAction.h"
#include "MaSRunAction.h"
#include "MaSEventAction.h"

#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QGSP_BERT_HP.hh"
#include "G4SystemOfUnits.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "Randomize.hh"

int main(int argc, char** argv)
{

	G4RunManager * runManager = new G4RunManager;
	
	runManager -> SetUserInitialization(new MaSDetectorConstruction());
	
	G4PhysListFactory factory;
	G4VModularPhysicsList* physicsList = factory.GetReferencePhysList("QGSP_BERT_HP");
	physicsList -> SetVerboseLevel(1);
	physicsList -> SetDefaultCutValue(.01*mm);
	runManager -> SetUserInitialization(physicsList);
	
	runManager -> SetUserAction(new MaSPrimaryGeneratorAction());

	runManager -> SetUserAction(new MaSEventAction());
	
	runManager -> SetUserAction(new MaSRunAction());
	
	runManager -> Initialize();

#ifdef G4VIS_USE
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();
#endif

	G4UImanager* UImanager = G4UImanager::GetUIpointer();
	if (argc != 1) {
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		G4cout<<argv[1]<<G4endl;
		UImanager->ApplyCommand(command+fileName);
	}
	else {
#ifdef G4UI_USE
	G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
	UImanager->ApplyCommand("/control/execute init_vis.mac"); 
#else
	UImanager->ApplyCommand("/control/execute init.mac"); 
#endif
	ui->SessionStart();
	delete ui;
#endif
	}	
	
#ifdef G4VIS_USE
	delete visManager;
#endif
	delete runManager;

	return 0;
}
