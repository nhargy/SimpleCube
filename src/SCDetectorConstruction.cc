#include "SCDetectorConstruction.hh"

SCDetectorConstruction::SCDetectorConstruction()
{
}

SCDetectorConstruction::~SCDetectorConstruction()
{
}

G4VPhysicalVolume* SCDetectorConstruction::Construct()
{
    DefineMaterials();
    ConstructLab();
    ConstructCube();

    return phys_Lab;
}

void SCDetectorConstruction::DefineMaterials()
{
    G4NistManager *nist = G4NistManager::Instance();

    Air = nist->FindOrBuildMaterial("G4_AIR");
    LiF = nist->FindOrBuildMaterial("G4_LITHIUM_FLUORIDE");
}

void SCDetectorConstruction::ConstructLab()
{
    G4double xLab = 30 *cm;
    G4double yLab = 30 *cm;
    G4double zLab = 30 *cm;

    G4Box* solid_Lab = new G4Box(
        "solid_Lab", 
        xLab/2, 
        yLab/2, 
        zLab/2
    );

    logic_Lab = new G4LogicalVolume(
        solid_Lab, 
        Air, 
        "logic_Lab"
    );

    auto vector_Lab = G4ThreeVector(0., 0., 0.);
    phys_Lab = new G4PVPlacement(
        0, 
        vector_Lab, 
        logic_Lab, 
        "phys_Lab", 
        nullptr, 
        false, 
        0, 
        checkOverlaps
    );
}

void SCDetectorConstruction::ConstructCube()
{
    G4double xCube = 1. *cm;
    G4double yCube = 1. *cm;
    G4double zCube = 1. *cm;

    G4Box* solid_Cube = new G4Box(
        "solid_Cube", 
        xCube/2, 
        yCube/2, 
        zCube/2
    );

    logic_Cube = new G4LogicalVolume(
        solid_Cube, 
        LiF, 
        "logic_Cube"
    );

    auto vector_Cube = G4ThreeVector(4.*cm, 0., 0.);
    phys_Cube = new G4PVPlacement(
        0, 
        vector_Cube, 
        logic_Cube, 
        "phys_Cube", 
        logic_Lab, 
        false, 
        0, 
        checkOverlaps
    );

    /* VisAttributes */
    auto colour_Cube = G4Colour(0., 1., 1.);
    G4VisAttributes *vis_Cube = new G4VisAttributes(colour_Cube);
    vis_Cube   ->SetVisibility(true);
    vis_Cube   ->SetForceSolid(true);
    logic_Cube ->SetVisAttributes(vis_Cube);
}

void SCDetectorConstruction::ConstructSDandField()
{
    SCSensitiveDetector *sensDet = new SCSensitiveDetector("SensitveDetector");
    logic_Cube->SetSensitiveDetector(sensDet);
}