#ifndef SCDETECTORCONSTRUCTION_HH   
#define SCDETECTORCONSTRUCTION_HH 1

#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4GenericMessenger.hh"

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

    void ApplyMessengers();

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
    G4Material* enLiF;

    // Isotop definitions
    G4Isotope* Li7;
    G4Isotope* Li6;
    G4Element* enLi;
    G4Element* F19;

    // Messengers
    G4GenericMessenger* fMessengerCube;
    G4double xCube;
    G4double yCube;
    G4double zCube;

    G4double Cube_Width;
    G4double Cube_Length;
    G4double Cube_Height;

    G4double Li7_percent;
    G4double Li6_percent;
};

#endif