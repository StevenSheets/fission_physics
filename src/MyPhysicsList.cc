
#include "G4HadronicInteractionRegistry.hh"
#include "G4HadronicProcess.hh"
#include "G4HadronicProcessType.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4Neutron.hh"
#include "G4NeutronHPThermalScattering.hh"
#include "G4NeutronHPThermalScatteringData.hh"
#include <assert.h>
#include "G4FissLib.hh"
#include "G4HadronFissionProcess.hh"
#include "G4ProcessTable.hh"
#include "MyPhysicsList.hh"

void MyPhysicsList::ConstructProcess() {
    G4VModularPhysicsList::ConstructProcess();
    // Get the elastic scattering process for neutrons
    G4ParticleDefinition* nPD = G4Neutron::Definition();
   // G4ProcessManager* pManager = nPD>GetProcessManager();
    
    G4ProcessVector* pvec = nPD->GetProcessManager()->GetProcessList();
    G4HadronicProcess* nElastic = 0;
    
    for (G4int i=0; i<pvec->size(); i++) {
        if ((*pvec)[i]->GetProcessSubType() != fHadronElastic) continue;
        nElastic = dynamic_cast<G4HadronicProcess*>((*pvec)[i]);
        break;
    }
    assert(nElastic != 0);
    // Get the "regular" HP elastic scattering model, exclude thermal scattering region
    
    G4HadronicInteraction* nElasticHP = G4HadronicInteractionRegistry::Instance()->FindModel("NeutronHPElastic");
    
    assert(nElasticHP != 0);
    
    // delete all neutron processes if already registered
    //
    G4ProcessTable* processTable = G4ProcessTable::GetProcessTable();
    G4VProcess* process = 0;
   
    // Get Fission:
    process = processTable->FindProcess("nFission", nPD);
    if (process) nPD->GetProcessManager()->RemoveProcess(process);
    
    
    nElasticHP->SetMinEnergy(4.*eV);
    // Attach HP thermal scattering model and data files to process
    nElastic->RegisterMe(new G4NeutronHPThermalScattering);
    nElastic->AddDataSet(new G4NeutronHPThermalScatteringData);

    G4HadronFissionProcess *theFissionProcess = new G4HadronFissionProcess();
    G4FissLib* theFissionModel = new G4FissLib;
    // cross section data set
    G4NeutronHPFissionData* dataSet4 = new G4NeutronHPFissionData();
    theFissionProcess->AddDataSet(dataSet4);
    
    theFissionProcess->RegisterMe(theFissionModel);
    G4NeutronHPFission* modelfission = new G4NeutronHPFission();
    
    nPD->GetProcessManager()->AddDiscreteProcess(theFissionProcess);
    
    // models
    //G4NeutronHPFission* model4 = new G4NeutronHPFission();
   // theFissionProcess->RegisterMe(model4);
    
}
