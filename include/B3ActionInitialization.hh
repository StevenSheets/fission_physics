

#ifndef B3ActionInitialization_h
#define B3ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.
///

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class B3ActionInitialization : public G4VUserActionInitialization
{
  public:
    B3ActionInitialization();
    virtual ~B3ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
