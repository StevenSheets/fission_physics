

#include "B3ActionInitialization.hh"
#include "B3PrimaryGeneratorAction.hh"
#include "B3RunAction.hh"
#include "B3StackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B3ActionInitialization::B3ActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B3ActionInitialization::~B3ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B3ActionInitialization::BuildForMaster() const
{
  SetUserAction(new B3RunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B3ActionInitialization::Build() const
{
  SetUserAction(new B3PrimaryGeneratorAction);
  //SetUserAction(new B3RunAction);
  SetUserAction(new B3StackingAction);
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
