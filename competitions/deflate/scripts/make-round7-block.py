"""Reuse recorded matches for content-class block refinement in public #361."""
from pathlib import Path
import argparse
import hashlib
import importlib.util
import json
import re

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'references/round7-public-361'
s=importlib.util.spec_from_file_location('r7_table',ROOT/'scripts/make-round7-middle.py')
helpers=importlib.util.module_from_spec(s);s.loader.exec_module(helpers)

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    prov=json.loads((BASE/'PROVENANCE.json').read_text())
    raw={n:(BASE/n).read_bytes() for n in ['parse.rs','Parse.lean']}
    assert all(hashlib.sha256(b).hexdigest()==prov['hashes'][n] for n,b in raw.items())
    source=raw['parse.rs'].decode()
    match=re.search(r'pub const DP_KNOBS: \[\[usize; 11\]; 16\] = \[\n(.*?)\n\];',source,re.S)
    dp=[[int(x.strip()) for x in row.split(',')] for row in re.findall(r'\[([\d ,]+)\]',match[1])]
    assert len(dp)==16
    routes={5:(5,0),6:(5,0),10:(6,2),11:(7,3),12:(8,4),13:(9,5),15:(10,6)}
    recipes=[('block1',1,0,set(routes)),('block2',2,0,set(routes)),
             ('blockmix',1,2,set(routes)),('blockselect',1,0,{11,12,15})]
    for suffix,passes,cost,classes in recipes:
        drows={}
        for cls in classes:
            target,old=routes[cls];v=dp[old]
            drows[target]=v[:6]+[passes,1,16,255,258,1,100,v[3],v[3],258,cost]
        def change_d(row,v):return drows.get(row,v)
        text,edit_d,changes_d=helpers.table(source,'D_KNOBS',17,change_d)
        def change_route(row,v):return [2,routes[row][0]] if row in classes else v
        text,edit_route,changes_route=helpers.table(text,'CLASS_TAB',2,change_route)
        restored=text
        for old,new in [edit_route,edit_d]:assert restored.count(new)==1;restored=restored.replace(new,old,1)
        assert restored==source
        name='r7-mid361-'+suffix
        files={'parse.rs':text.encode(),'Parse.lean':raw['Parse.lean']}
        manifest={'candidate':name,'base_submission_id':'361','parent':'references/round7-public-361',
            'base_hashes':prov['hashes'],'hashes':{n:hashlib.sha256(b).hexdigest() for n,b in files.items()},
            'bytes':{n:len(b) for n,b in files.items()},'attribution':prov['author_hotkey'],
            'mechanism':'Route declared general content classes from the online forward DP into existing engine D: record matches during the same search, then re-plan backward using per-16384-token-block prices. No second match search.',
            'extra_backward_passes':passes,'cost_kind':'actual Huffman lengths' if cost==0 else 'mean of Huffman and entropy prices',
            'content_classes':sorted(classes),'route_changes':changes_route,'D_rows':changes_d,
            'audit':'Reverse only two declared table edits restores original source; all matching, cost, classification, emit and proof bodies unchanged. No filename, exact-length or hash routing added.',
            'proof_status':'UNKNOWN fresh extraction, obligation and axiom gate required; original #361 proof copied byte for byte.',
            'performance_status':'UNKNOWN until paired public tests; private transfer/admission/payment remain unverified.'}
        assert all(len(b)<=524288 for b in files.values())
        files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode()
        target=ROOT/'candidates'/name
        if args.check:assert all((target/n).read_bytes()==b for n,b in files.items())
        else:
            target.mkdir(exist_ok=True)
            for n,b in files.items():assert not (target/n).exists() or (target/n).read_bytes()==b;(target/n).write_bytes(b)
        print(json.dumps({'candidate':name,'hashes':manifest['hashes']}))

if __name__=='__main__':main()
