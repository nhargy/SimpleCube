#include "SCPrimaryGenerator.hh"

SCPrimaryGenerator::SCPrimaryGenerator()
{
    ApplyMessengers();

    fParticleGun = new G4ParticleGun(1);

    // Particle position
    //G4double x = 0. * cm;
    //G4double y = 0. * cm;
    //G4double z = 0. * cm;

    G4ThreeVector pos(xIon *mm, yIon *mm, zIon* mm);

    // Particle direction
    G4double px = 0.;
    G4double py = 0.;
    G4double pz = 0.;

    G4ThreeVector mom(px, py, pz);

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
}

SCPrimaryGenerator::~SCPrimaryGenerator()
{
    delete fParticleGun;
    delete fMessengerIon;
}

void SCPrimaryGenerator::ApplyMessengers() {

    fMessengerIon = new G4GenericMessenger(
        this,
        "/ion/",
        "ion"
    );

    fMessengerIon->DeclareProperty(
        "Z",
        Z,
        "Z"
    );
 
    fMessengerIon->DeclareProperty(
        "A",
        A,
        "A"
    );

    fMessengerIon->DeclareProperty(
        "xIon",
        xIon,
        "xIon"
    );

    fMessengerIon->DeclareProperty(
        "yIon",
        yIon,
        "yIon"
    );

    fMessengerIon->DeclareProperty(
        "zIon",
        zIon,
        "zIon"
    );
       
    Z = 27;
    A = 60;
    xIon = 0;
    yIon = 0;
    zIon = 0;
}

void SCPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{

    G4ThreeVector pos(xIon *mm, yIon *mm, zIon *mm);
    fParticleGun->SetParticlePosition(pos);

    // Particle type
    //G4int Z = 27;
    //G4int A = 60;

    G4double charge = 0. * eplus;
    G4double energy = 0. * keV;

    G4ParticleDefinition *ion  = G4IonTable::GetIonTable()->GetIon(Z, A, energy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(charge);
    fParticleGun->SetParticleEnergy(energy);

    // Create vertex
    fParticleGun->GeneratePrimaryVertex(anEvent);
}