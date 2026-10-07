"""Cheaper forward warm starts before cached backward block optimization."""
from pathlib import Path
import argparse
import hashlib
import importlib.util
import json

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'candidates/r7-mid361-block1'
s=importlib.util.spec_from_file_location('r7_table',ROOT/'scripts/make-round7-middle.py')
helpers=importlib.util.module_from_spec(s);s.loader.exec_module(helpers)

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    origin=json.loads((BASE/'manifest.json').read_text())
    raw={n:(BASE/n).read_bytes() for n in ['parse.rs','Parse.lean']}
    assert all(hashlib.sha256(b).hexdigest()==origin['hashes'][n] for n,b in raw.items())
    source=raw['parse.rs'].decode()
    for passes in [1,2]:
        def transform(row,v):
            if 5<=row<=10:
                v[6]=passes
                v[8]=3
                v[12]=0
            return v
        text,(old,new),changes=helpers.table(source,'D_KNOBS',17,transform)
        assert text.replace(new,old,1)==source
        name=f'r7-mid361-seed{passes}'
        files={'parse.rs':text.encode(),'Parse.lean':raw['Parse.lean']}
        manifest={'candidate':name,'base_submission_id':'361','parent':'candidates/r7-mid361-block1',
            'base_hashes':origin['hashes'],'hashes':{n:hashlib.sha256(b).hexdigest() for n,b in files.items()},
            'bytes':{n:len(b) for n,b in files.items()},'attribution':origin['attribution'],
            'mechanism':'Make the forward seed cheaper: try only length-code endpoints above length 3 and omit backward extension in the initial price relaxation. Retain the recorded-match backward optimizer and its 255-byte candidate extensions.',
            'backward_passes':passes,'table_changes':changes,
            'audit':'Only D_KNOBS rows used by the newly refined general text classes change. Original content router, matchfinder/record functions, backward optimizer, emitters and proof bytes retained.',
            'proof_status':'UNKNOWN fresh full gate; copied proof is not verification.',
            'performance_status':'UNTESTED until public paired benchmark. Expected compute redistribution is a hypothesis.'}
        files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode()
        target=ROOT/'candidates'/name
        if args.check:assert all((target/n).read_bytes()==b for n,b in files.items())
        else:
            target.mkdir(exist_ok=True)
            for n,b in files.items():assert not (target/n).exists() or (target/n).read_bytes()==b;(target/n).write_bytes(b)
        print(json.dumps({'candidate':name,'hashes':manifest['hashes'],'status':'UNTESTED'}))

if __name__=='__main__':main()
