import numpy as np
import pandas as pd
import uproot
import sys
from tqdm import tqdm
import argparse

def read_root_file(
        fn,
        treename='Hits'
        ):

    with uproot.open(fn) as f:
        tree = f[f"{treename}"]
        branches = ['eventID',
                    'ptrackID',
                    'trackID',
                    'pdgID',
                    'isEntry',
                    'isExit',
                    'preProcName',
                    'postProcName',
                    'creatorProc',
                    'fX1', 
                    'fY1', 
                    'fZ1',
                    'fX2', 
                    'fY2', 
                    'fZ2', 
                    'fK1',
                    'fK2',
                    'fEdep',
                    'fSec'
                    ]
        
        data = tree.arrays(
            branches, 
            filter_name='nsteps', 
            library='np'
            )

    return data

parser = argparse.ArgumentParser(description="Process ROOT file")
parser.add_argument("--rootfile", type=str,  help="Rootfile")
parser.add_argument("--outfile", type=str, default='output.parquet', help="Output file")

args = parser.parse_args()

print(f"Processing rootfile ==> {args.rootfile}")
data = read_root_file(args.rootfile)
df = pd.DataFrame(data)
print(f"Processing rootfile ==> {args.rootfile}")

# Sum edep per event in one pass
edep_by_event = df.groupby("eventID")["fEdep"].sum()

# Keep only events with total edep > 0
good_events = edep_by_event[edep_by_event > 0].index

# Filter original df
eDf = df[df["eventID"].isin(good_events)]

print(f"Saving DataFrame as parquet: {args.outfile}")
eDf.to_parquet(args.outfile)
