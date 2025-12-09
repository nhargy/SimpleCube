#ifndef SCDETECTORCONSTRUCTION_HH   
#define SCDETECTORCONSTRUCTION_HH 1

#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include "SCSensitiveDetector.hh"

class SCDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    SCDetectorConstruction();
    virtual ~SCDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

private:
    void DefineMaterials();
    void ConstructLab();
    void ConstructCube();

    virtual void ConstructSDandField();

    G4bool checkOverlaps = true;

    /* Lab */
    G4LogicalVolume*   logic_Lab;
    G4VPhysicalVolume* phys_Lab;

    /* Cube */
    G4LogicalVolume*   logic_Cube;
    G4VPhysicalVolume* phys_Cube;

    // Material definitions
    G4Material* Air;
    G4Material* LiF;
};

#endif