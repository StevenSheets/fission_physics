
#ifndef Analysis_h
#define Analysis_h 1

class G4VPhysicalVolume;
class G4Event;
class G4Track;
class G4Step;

#include <fstream>
#include <time.h>


class Analysis {
	public:
		Analysis();
		~Analysis();
	
	void BeginOfEventAction( const G4Event*);
	  void EndOfEventAction(const G4Event*);

	  void UserSteppingAction(const G4Step*);

	
	private:

	std::ofstream surface_file;
    double Time;
	double properTime;
	int EventID;

     const std::string currentDateTime();


};

#endif
