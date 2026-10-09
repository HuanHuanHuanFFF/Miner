"""Repair shared-link boundary without changing PIM's original32-bit helper."""
from pathlib import Path
import argparse,hashlib,importlib.util,json

ROOT=Path(__file__).resolve().parents[1];BASE=ROOT/'references/round13-public-542';NAME='r13-542-abs15-isolated'

def sha(b):return hashlib.sha256(b).hexdigest()

def generate():
    loader=importlib.util.spec_from_file_location('r13_542_draft',ROOT/'scripts/build-round13-542.py');m=importlib.util.module_from_spec(loader);loader.loader.exec_module(m);files=m.generate();old_manifest=json.loads(files['manifest.json'])
    original=(BASE/'parse.rs').read_text();rust=files['parse.rs'].decode();a=rust.index('pub fn pc_f_link');_,b=m.function_end(rust,'pc_run1c');section=rust[a:b];assert section.count('pc_f_link')==7;repaired=section.replace('pc_f_link','r13_542_f_link');rust=rust[:a]+repaired+rust[b:]
    x,y=m.function_end(original,'pc_f_link');kept='#[inline(always)]\n'+original[x:y]+'\n\n';marker='/// R13 modular PC predecessor hint;';assert rust.count(marker)==1;rust=rust.replace(marker,kept+marker,1)
    assert rust.count('pub fn pc_f_link')==1 and rust.count('pub fn r13_542_f_link')==1
    # All unchanged PIM callers retain the original shared U32 signature.
    lean=files['Parse.lean'].decode();parent=(BASE/'Parse.lean').read_text();pc=lean.index('namespace PC');a=lean.index('@[local step]\ntheorem f_link_spec',pc);b=lean.index('theorem MatchAt.of_try',a);new_spec=lean[a:b];p0=parent.index('@[local step]\ntheorem f_link_spec',parent.index('namespace PC'));p1=parent.index('theorem MatchAt.of_try',p0);old_spec=parent[p0:p1]
    assert new_spec.count('slot.pc_f_link')==2 and new_spec.count('theorem f_link_spec')==1
    new_spec=new_spec.replace('theorem f_link_spec','theorem r13_542_f_link_spec').replace('slot.pc_f_link','slot.r13_542_f_link');lean=lean[:a]+old_spec+new_spec+lean[b:]
    manifest={**old_manifest,'candidate':NAME,'hashes':{'parse.rs':sha(rust.encode()),'Parse.lean':sha(lean.encode())},'failed_predecessor':'r13-542-abs15','failed_run_id':'37863273684',
        'repair':'Original pc_f_link U32 helper and PC.f_link_spec retained for unchanged PIM callers. Only modified PC region uses independent r13_542_f_link U16 and proof bridge. No attempted performance result from failed predecessor is inherited.',
        'proof_status':'DRAFT_UNCOMPILED_AFTER_SHARED_BOUNDARY_REPAIR; new exact original gate remains mandatory',
        'source_reversal':'U16 PC region and private link name reversed; added unwrap and copied old shared-link declaration removed to recover original parent. PIM bytes remain original.'}
    result={'parse.rs':rust.encode(),'Parse.lean':lean.encode(),'manifest.json':(json.dumps(manifest,indent=2)+'\n').encode()};assert all(len(v)<=524288 for f,v in result.items()if f!='manifest.json');return result

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args();files=generate();p=ROOT/'candidates'/NAME
    if args.check:assert all((p/f).read_bytes()==v for f,v in files.items())
    else:
        assert not p.exists();p.mkdir()
        for f,v in files.items():(p/f).write_bytes(v)
    print(json.dumps({'candidate':NAME,'hashes':{f:sha(v)for f,v in files.items()},'status':'REPAIR_DRAFT_NOT_RUN'}))

if __name__=='__main__':main()
