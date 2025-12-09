#ifndef SCPHYSICSLISTS_HH
#define SCPHYSICSLISTS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"

class SCPhysicsList : public G4VModularPhysicsList
{
public:
    SCPhysicsList();
    ~SCPhysicsList();
};

#endif