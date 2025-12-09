#!/bin/bash

# Load environment
echo "Activating LCG environment..."
source /cvmfs/sft.cern.ch/lcg/views/LCG_105/x86_64-el9-gcc12-opt/setup.sh

echo " "
echo "=====> Running GEANT4 SimpleCube Sim! <====="    
cd /srv01/xenon/{{USER}}/SimpleCube/build
./SimpleCube --macro {{MACROFILE}} --primaries {{PRIMARIES}} --outfile /storage/xenon/{{USER}}/SimpleCube/{{OUTFILENAME}}