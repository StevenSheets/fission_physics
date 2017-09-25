
#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4Track.hh"
#include "Analysis.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//
class SteppingAction : public G4UserSteppingAction
{
  public:
      SteppingAction();
	virtual ~SteppingAction();

	virtual void UserSteppingAction(const G4Step*);

	const G4SteppingManager* pSM;
	G4Track* fTrack;
  private:
	Analysis *ana;

};

#endif
