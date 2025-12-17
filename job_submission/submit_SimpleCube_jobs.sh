#!/bin/bash

###########################################
# -----------  GLOBAL DEFAULTS -----------
###########################################

TEMPLATE="run_SimpleCube_single.sh"

###########################################
# ---------------  USAGE -----------------
###########################################
usage() {
    echo "  $0 <num_jobs> <primaries_per_job> <macro_file>"
    exit 1
}

###########################################
# -----------  PARSE ARGUMENTS -----------
###########################################
if [ $# -lt 3 ]; then usage; fi

NUM_JOBS=$1
PRIMARIES=$2
MACROFILE=$3

###########################################
# ------  GENERATE SERIAL NUMBER ----------
###########################################
SERIAL="$(tr -dc 'A-Z' </dev/urandom | head -c3)$(tr -dc '0-9' </dev/urandom | head -c3)_$(date +%d%m%y)"

###########################################
# ------------ BUILD JOBSCRIPT -----------
###########################################
build_jobscript() {
    local jobscript="$1"
    local primaries="$2"
    local outfilename="$3"
    local macro="$4"
    local procfilename="$5"
    local seed="$6"
    local dirname="$7"
    local logfilename="$8"

    sed \
        -e "s|{{PRIMARIES}}|$primaries|g" \
        -e "s|{{OUTFILENAME}}|$outfilename|g" \
        -e "s|{{MACROFILE}}|$macro|g" \
        -e "s|{{PROCFILENAME}}|$procfilename|g" \
        -e "s|{{USER}}|$USER|g" \
        -e "s|{{SEED}}|$seed|g" \
        -e "s|{{DIRNAME}}|$dirname|g" \
        -e "s|{{LOGFILENAME}}|$logfilename|g" \
        "$TEMPLATE" > "$jobscript"

    chmod +x "$jobscript"
}

###########################################
# --------------- SUBMIT JOB -------------
###########################################
submit_job() {
    local jobscript="$1"
    local basename="$2"

    qsub "$jobscript"
}

###########################################
# ---------------- MAIN LOOP -------------
###########################################
TMPDIR=$(mktemp -d)
END_INDEX=$((1 + NUM_JOBS - 1))
MACRO_BASENAME=$(basename "$MACROFILE")
MACRO_TAG="${MACRO_BASENAME%.*}"
MACRO_TAG="${MACRO_TAG#run_}"
DIRNAME="${MACRO_TAG}-${SERIAL}"

mkdir -p "/storage/xenon/$USER/SimpleCube/$DIRNAME/raw"
mkdir -p "/storage/xenon/$USER/SimpleCube/$DIRNAME/proc"
mkdir -p "/storage/xenon/$USER/SimpleCube/$DIRNAME/log"

for ((i = 1; i <= END_INDEX; i++)); do
    JOBID=$(printf "%04d" $i)
    BASENAME="${MACRO_TAG}_${JOBID}"
    OUTFILENAME="${BASENAME}.root"
    LOGFILENAME="${BASENAME}.log"
    PROCFILENAME="${BASENAME}.parquet"
    echo $OUTFILENAME
    echo $PROCFILENAME

    SEED=$((1000000 + i)) 
    echo "Seed: ${SEED}"

    JOBSCRIPT="$TMPDIR/hermeticsub_${JOBID}.sh"
    build_jobscript "$JOBSCRIPT" "$PRIMARIES" "$OUTFILENAME" "$MACROFILE" "$PROCFILENAME" "$SEED" "$DIRNAME" "$LOGFILENAME"
    submit_job "$JOBSCRIPT" "$BASENAME"
done

rm -r "$TMPDIR"
echo "All jobs processed."
