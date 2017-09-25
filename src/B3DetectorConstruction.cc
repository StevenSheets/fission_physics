

#include "B3DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4Sphere.hh"
#include "G4Orb.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B3DetectorConstruction::B3DetectorConstruction()
: G4VUserDetectorConstruction(),
  fCheckOverlaps(true)
{
  DefineMaterials();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B3DetectorConstruction::~B3DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B3DetectorConstruction::DefineMaterials()
{
  G4NistManager* man = G4NistManager::Instance();
  
  G4bool isotopes = false;
  G4String name, symbol;             // a=mass of a mole;
	G4double a, z, density;            // z=mean number of protons;
	G4int iz, n;                       //iz=nb of protons  in an isotope;
                                   // n=nb of nucleons in an isotope;

	G4int ncomponents, natoms;
	G4double abundance, fractionmass;
	//G4double temperature, pressure;
  
  G4Element*  O = man->FindOrBuildElement("O" , isotopes); 
 
  

	
	auto U5 = new G4Isotope(name="U235", iz=92, n=235, a=235.01*g/mole);
	auto U8 = new G4Isotope(name="U238", iz=92, n=238, a=238.03*g/mole);

	auto elU  = new G4Element(name="Uranium", symbol="U", ncomponents=2);
	elU->AddIsotope(U5, abundance= .1*perCent);
	elU->AddIsotope(U8, abundance= 99.9*perCent);
	auto DU = new G4Material("DU", 19.1*g/cm3, 1);
	DU->AddElement(elU, 1);
	
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B3DetectorConstruction::Construct()
{  

  G4NistManager* nist = G4NistManager::Instance();
  G4Material* default_mat = nist->FindOrBuildMaterial("G4_AIR");
	
  auto target_material = nist->FindOrBuildMaterial("DU");
        
  //     
  // World
  //
  G4double world_sizeXY = 2.0*m;
  G4double world_sizeZ  = 2.0*m;
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ); //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        default_mat,         //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      fCheckOverlaps);       // checking overlaps 
                 
  //
  // DU sphere
  //
  auto du_sphere =
    new G4Orb("du_sphere", 2.54*cm);
      
  auto logicDU =
    new G4LogicalVolume(du_sphere,           //its solid
                        target_material,         //its material
                        "DUBALL");             //its name
                    

	
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicDU,           //its logical volume
                    "DUBALL",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    fCheckOverlaps);         // checking overlaps 
                 

  // Visualization attributes
  //
  logicDU->SetVisAttributes (G4VisAttributes::Invisible);
  //logicDetector->SetVisAttributes (G4VisAttributes::Invisible);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl; 

  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B3DetectorConstruction::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  
  // declare crystal as a MultiFunctionalDetector scorer
  //  
  G4MultiFunctionalDetector* cryst = new G4MultiFunctionalDetector("du");
  G4VPrimitiveScorer* primitiv1 = new G4PSEnergyDeposit("edep");
  cryst->RegisterPrimitive(primitiv1);
  SetSensitiveDetector("DUBALL",cryst);
  
  // declare patient as a MultiFunctionalDetector scorer
  //
  /*
  G4MultiFunctionalDetector* patient = new G4MultiFunctionalDetector("patient");
  G4VPrimitiveScorer* primitiv2 = new G4PSDoseDeposit("dose");
  patient->RegisterPrimitive(primitiv2);
  SetSensitiveDetector("PatientLV",patient); */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
