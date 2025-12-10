#include "SCPrimaryGenerator.hh"
#include "Randomize.hh"
#include "G4RandomTools.hh"


SCPrimaryGenerator::SCPrimaryGenerator()
{
    ApplyMessengers();

    fParticleGun = new G4ParticleGun(1);
    G4ThreeVector pos(xSource *mm, ySource *mm, zSource* mm);
    fParticleGun->SetParticlePosition(pos);
}

SCPrimaryGenerator::~SCPrimaryGenerator()
{
    delete fParticleGun;
    delete fMessengerSource;
}

void SCPrimaryGenerator::ApplyMessengers() {

    fMessengerSource = new G4GenericMessenger(
        this,
        "/source/",
        "source"
    );

    fMessengerSource->DeclareProperty(
        "isIon",
        isIon,
        "isIon"
    );

    fMessengerSource->DeclareProperty(
        "pdgSource",
        pdgSource,
        "pdgSource"
    );

    fMessengerSource->DeclareProperty(
        "Z",
        Z,
        "Z"
    );
 
    fMessengerSource->DeclareProperty(
        "A",
        A,
        "A"
    );

    fMessengerSource->DeclareProperty(
        "energySource",
        energySource,
        "energySource"
    );

    fMessengerSource->DeclareProperty(
        "xSource",
        xSource,
        "xSource"
    );

    fMessengerSource->DeclareProperty(
        "ySource",
        ySource,
        "ySource"
    );

    fMessengerSource->DeclareProperty(
        "zSource",
        zSource,
        "zSource"
    );
    
    isIon = 1;
    pdgSource = 22;
    Z = 27;
    A = 60;
    energySource = 1.;
    xSource = 0;
    ySource = 0;
    zSource = 0;
}

void SCPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{

    G4ThreeVector pos(xSource *mm, ySource *mm, zSource *mm);
    fParticleGun->SetParticlePosition(pos);

    if (isIon==1) {
        G4ParticleDefinition *ion  = G4IonTable::GetIonTable()->GetIon(Z, A, 0.);
        fParticleGun->SetParticleDefinition(ion);
        fParticleGun->SetParticleEnergy(0.);
    }
    else if (isIon==0) {
        G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
        G4ParticleDefinition* particle = particleTable->FindParticle(pdgSource);
        fParticleGun->SetParticleDefinition(particle);
        fParticleGun->SetParticleEnergy(energySource * MeV);

        // Random isotropic direction
        G4ThreeVector dir = G4RandomDirection();
        fParticleGun->SetParticleMomentumDirection(dir);
    }

    // Create vertex
    fParticleGun->GeneratePrimaryVertex(anEvent);
}