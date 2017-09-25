

#include "SteppingAction.hh"
#include "G4Track.hh"
#include "globals.hh"
#include "G4SteppingManager.hh"

//#include "AnalysisManager.hh"

#include "Analysis.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

SteppingAction::SteppingAction()
{

	ana = new Analysis();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

SteppingAction::~SteppingAction()
{
	delete ana;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void SteppingAction::UserSteppingAction(const G4Step* fStep)
{
  
   pSM = fpSteppingManager;
   fTrack = pSM->GetTrack();
   // G4Step* fStep = pSM->GetStep();
  //G4int TrackID = fTrack->GetTrackID();
    G4int StepNo = fTrack->GetCurrentStepNumber();
  //  if(StepNo >= 10000) fTrack->SetTrackStatus(fStopAndKill);

  

  

  // Analysis
  if (ana) ana->UserSteppingAction(fStep);
  
}

