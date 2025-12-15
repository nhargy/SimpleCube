#include "SCDetectorConstruction.hh"

SCDetectorConstruction::SCDetectorConstruction()
{
    ApplyMessengers();
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

void SCDetectorConstruction::ApplyMessengers()
{
    fMessengerCube = new G4GenericMessenger(this, "/cube/", "cube");

    fMessengerCube->DeclareProperty( "xCube", xCube, "xCube");
    fMessengerCube->DeclareProperty("yCube", yCube, "yCube");
    fMessengerCube->DeclareProperty("zCube", zCube, "zCube");
    fMessengerCube->DeclareProperty("Cube_Width", Cube_Width, "Cube_Width");
    fMessengerCube->DeclareProperty("Cube_Length", Cube_Length, "Cube_Length");
    fMessengerCube->DeclareProperty("Cube_Height", Cube_Height, "Cube_Height");
    fMessengerCube->DeclareProperty("Li7_percent", Li7_percent, "Li7_percent");
    fMessengerCube->DeclareProperty("Li6_percent", Li6_percent, "Li6_percent");

    // Default Values
    xCube = 40.;
    yCube = 0.;
    zCube = 0.;

    Cube_Width  = 10.;
    Cube_Length = 10.;
    Cube_Height = 10.;

    // Natural abundance ~ Li7 (93%), Li6 (7%)
    Li7_percent = 93.;
    Li6_percent = 7.;
}

void SCDetectorConstruction::DefineMaterials()
{
    G4NistManager *nist = G4NistManager::Instance();

    Air = nist->FindOrBuildMaterial("G4_AIR");
    //LiF = nist->FindOrBuildMaterial("G4_LITHIUM_FLUORIDE");

    Li7 = new G4Isotope(
        "Li7",
        3,
        7,
        7.016 * g/mole
    );

    Li6 = new G4Isotope(
        "Li6",
        3,
        6,
        6.015 * g/mole
    );

    enLi = new G4Element(
        "enriched Li", 
        "enLi", 
        2
    );
    enLi->AddIsotope(Li7, Li7_percent * perCent);
    enLi->AddIsotope(Li6, Li6_percent * perCent);

    F19 = nist->FindOrBuildElement("F");

    G4double density = 2.635 * g/cm3; // https://physics.nist.gov/cgi-bin/Star/compos.pl?matno=185
    enLiF = new G4Material("enriched LiF", density, 2);

    enLiF->AddElement(enLi, 1);  // 1 Li atom
    enLiF->AddElement(F19,  1);  // 1 F atom
}

void SCDetectorConstruction::ConstructLab()
{
    G4double Lab_Width  = 300. *mm;
    G4double Lab_Length = 300. *mm;
    G4double Lab_Height = 300. *mm;

    G4Box* solid_Lab = new G4Box(
        "solid_Lab", 
        Lab_Width/2, 
        Lab_Length/2, 
        Lab_Height/2
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
    G4Box* solid_Cube = new G4Box(
        "solid_Cube", 
        Cube_Width/2, 
        Cube_Length/2, 
        Cube_Height/2
    );

    logic_Cube = new G4LogicalVolume(
        solid_Cube, 
        enLiF, 
        "logic_Cube"
    );

    auto vector_Cube = G4ThreeVector(xCube *mm, yCube *mm, zCube *mm);
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
    auto colour_Cube = G4Colour(Li7_percent/100, 0., Li6_percent/100);
    G4VisAttributes *vis_Cube = new G4VisAttributes(colour_Cube);
    vis_Cube   ->SetVisibility(true);
    vis_Cube   ->SetForceSolid(true);
    vis_Cube   ->SetForceAuxEdgeVisible(true);
    logic_Cube ->SetVisAttributes(vis_Cube);
}

void SCDetectorConstruction::ConstructSDandField()
{
    SCSensitiveDetector *sensDet = new SCSensitiveDetector("SensitveDetector");
    logic_Cube->SetSensitiveDetector(sensDet);
}
