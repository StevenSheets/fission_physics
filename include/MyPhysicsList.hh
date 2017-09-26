#include "QGSP_BIC_HP.hh"

class MyPhysicsList : public QGSP_BIC_HP {
	public:
    MyPhysicsList(G4int verbose=1) : QGSP_BIC_HP(){};
    virtual ~MyPhysicsList() {;};
	  	virtual void ConstructProcess();
};
