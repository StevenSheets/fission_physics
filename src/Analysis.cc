

#include "Analysis.hh"


#include "G4RunManager.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Event.hh"
#include "G4Run.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4Step.hh"
#include "G4Types.hh"
#include "G4ThreeVector.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "G4SystemOfUnits.hh"


#include <string>
#include <time.h>
#include <stdio.h>
#include <iostream>

using namespace std;

Analysis::Analysis() {

  // file for the text output
  const std::string timerightnow = currentDateTime();
  //std::string filename = timerightnow + ".dat";
    std::string surffilename = timerightnow+".surf";
  //TString outfile_name = "test.dat";

    surface_file.open(surffilename.c_str(), ios::out);

}

Analysis::~Analysis() {
	surface_file.close();
}


void Analysis::BeginOfEventAction(const G4Event *anEvent)
{
  
  
  EventID = anEvent->GetEventID();
  G4PrimaryVertex* vertex = anEvent->GetPrimaryVertex();
  G4PrimaryParticle *primaryParticle = vertex->GetPrimary();
    G4ThreeVector pvec = primaryParticle->GetMomentum();
	properTime = primaryParticle->GetProperTime();
  

    
 // if(EventID%10==0) std::cout<<EventID<<" " <<primaryParticle->GetMass()<<" " << pvec[0] << " " << pvec[1]<< " " << primaryParticle->GetPz() <<std::endl;
	
}


void Analysis::UserSteppingAction(const G4Step* aStep) {
	const G4VProcess *pr = aStep->GetPostStepPoint()->GetProcessDefinedStep();
	G4String pr_name;
	G4String PrimaryParticleName, SecondaryParticleName;
	// get the track
	G4Track *aTrack=aStep->GetTrack();

  const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	
  if(aTrack->GetCurrentStepNumber()==1&&aTrack->GetTrackID()==1) { //first track, first step

    PrimaryParticleName = aTrack->GetDefinition()->GetParticleName(); // Name of inital particle.
    
  }
	
    if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()=="DUBALL") {
		//std::cout << "In DUBALL!" << std::endl;
        // if it is leaving the 'oxide' volume:
        if(aStep->GetPostStepPoint()->GetStepStatus()==fGeomBoundary) {
            Time = aTrack->GetGlobalTime()/(ns); ///(ns);
           const G4VProcess *process = aTrack->GetCreatorProcess();
            if (!process)
                pr_name = "prim";
            else
                pr_name = process->GetProcessName();
            surface_file << std::setprecision(15) << Time << " " << std::setprecision(7) << aTrack->GetKineticEnergy() << " " << aTrack->GetDefinition()->GetParticleName() << " " << pr_name <<"\n";

            
        }
        
    }
	

}



// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string Analysis::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}