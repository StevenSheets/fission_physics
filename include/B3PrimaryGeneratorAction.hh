

#ifndef B3PrimaryGeneratorAction_h
#define B3PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;



class B3PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    B3PrimaryGeneratorAction();    
    virtual ~B3PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);         

    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4double Time;
	G4double rate;
    G4ParticleGun*  fParticleGun;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


