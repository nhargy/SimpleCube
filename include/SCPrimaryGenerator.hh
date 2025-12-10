#ifndef SCPRIMARYGENERATOR_HH
#define SCPRIMARYGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"
#include "G4GenericMessenger.hh"

class SCPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
    SCPrimaryGenerator();
    ~SCPrimaryGenerator();

    virtual void GeneratePrimaries(G4Event *);

private:

    void ApplyMessengers();

    G4ParticleGun *fParticleGun;
    
    G4GenericMessenger* fMessengerSource;
    G4int    isIon;
    G4int    pdgSource;
    G4int    Z;
    G4int    A;
    G4double energySource;
    G4double xSource;
    G4double ySource;
    G4double zSource;
};

#endif