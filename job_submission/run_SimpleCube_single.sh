#!/bin/bash
#PBS -N SimpleCube_job
#PBS -q N
#PBS -m n
#PBS -l walltime=10:00:00
#PBS -l select=1:ncpus=1:mem=2500mb
#PBS -l io=1
#PBS -j oe
#PBS -o n

# Load environment
echo "Activating LCG environment..."
source /cvmfs/sft.cern.ch/lcg/views/LCG_105/x86_64-el9-gcc12-opt/setup.sh

# Define paths
RAW="/storage/xenon/{{USER}}/SimpleCube/raw/{{DIRNAME}}/"
PROC="/storage/xenon/{{USER}}/SimpleCube/proc/{{DIRNAME}}/"

# Create output directories if needed
mkdir -p "$RAW" "$PROC"

echo " "
echo "============================================"
echo "=====> Running GEANT4 SimpleCube Sim! <====="
echo "============================================"
echo " "
echo "Raw root file {{OUTFILENAME}} is being simulated.."

cd /srv01/xenon/{{USER}}/SimpleCube/build
./SimpleCube \
    --macro {{MACROFILE}} \
    --primaries {{PRIMARIES}} \
    --outfile "$RAW{{OUTFILENAME}}" \
    --seed {{SEED}}

echo "=====> Processing {{OUTFILENAME}} to {{PROCFILENAME}}"
python ../analysis/post_processing.py \
    --rootfile "$RAW{{OUTFILENAME}}" \
    --outfile  "$PROC{{PROCFILENAME}}"
echo "=====> Saved to {{DIRNAME}}"
