"""Complete isolation of both shared typed-link and shared-deepen boundaries."""
from pathlib import Path
import argparse,hashlib,importlib.util,json

ROOT=Path(__file__).resolve().parents[1];BASE=ROOT/'references/round13-public-542';NAME='r13-542-abs15-privatecalls'

def sha(b):return hashlib.sha256(b).hexdigest()

def generate():
    loader=importlib.util.spec_from_file_location('r13_isolated',ROOT/'scripts/build-round13-542-isolated.py');m=importlib.util.module_from_spec(loader);loader.loader.exec_module(m);files=m.generate();manifest=json.loads(files['manifest.json'])
    loader=importlib.util.spec_from_file_location('r13_region',ROOT/'scripts/build-round13-542.py');g=importlib.util.module_from_spec(loader);loader.loader.exec_module(g)
    original=(BASE/'parse.rs').read_text();rust=files['parse.rs'].decode();a=rust.index('pub fn r13_542_f_link');_,b=g.function_end(rust,'pc_run1c');section=rust[a:b];assert section.count('pc_f_deepen')==2;changed=section.replace('pc_f_deepen','r13_542_f_deepen');rust=rust[:a]+changed+rust[b:]
    x,y=g.function_end(original,'pc_f_deepen');kept='#[inline(always)]\n'+original[x:y]+'\n\n';marker='/// R13 modular PC predecessor hint;';rust=rust.replace(marker,kept+marker,1)
    assert rust.count('pub fn pc_f_deepen')==1 and rust.count('pub fn r13_542_f_deepen')==1
    lean=files['Parse.lean'].decode();parent=(BASE/'Parse.lean').read_text();a=lean.index('@[local step]\ntheorem f_deepen_spec',lean.index('namespace PC'));b=lean.index('@[local step]\ntheorem f_record3_loop0_spec',a);new=lean[a:b]
    p0=parent.index('@[local step]\ntheorem f_deepen_spec',parent.index('namespace PC'));p1=parent.index('@[local step]\ntheorem f_record3_loop0_spec',p0);old=parent[p0:p1]
    assert new.count('slot.pc_f_deepen')==2;new=new.replace('theorem f_deepen_spec','theorem r13_542_f_deepen_spec').replace('slot.pc_f_deepen','slot.r13_542_f_deepen');lean=lean[:a]+old+new+lean[b:]
    # Inspect every external caller of both original shared functions: the PC
    # modified region no longer calls either one; all PIM calls retain names.
    a=rust.index('pub fn r13_542_f_link');_,b=g.function_end(rust,'pc_run1c');assert 'pc_f_link'not in rust[a:b]and'pc_f_deepen'not in rust[a:b]
    manifest.update(candidate=NAME,hashes={'parse.rs':sha(rust.encode()),'Parse.lean':sha(lean.encode())},failed_predecessor='r13-542-abs15-isolated',failed_run_id='37864386007',
        repair='Both originalU32 link/deepen functions and specs retained for PIM. ModifiedPC region exclusively calls privateU16 variants; all remaining array-taking shared consumers audited by name.',
        proof_status='DRAFT_UNCOMPILED_COMPLETE_SHARED_BOUNDARY_REPAIR; no certificate inherited',source_reversal='Both added original shared-function copies removed; privatePC names/types/stores/reads reversed plus unwrap removed to recover original542.')
    result={'parse.rs':rust.encode(),'Parse.lean':lean.encode(),'manifest.json':(json.dumps(manifest,indent=2)+'\n').encode()};assert all(len(v)<=524288 for f,v in result.items()if f!='manifest.json');return result

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args();files=generate();p=ROOT/'candidates'/NAME
    if args.check:assert all((p/f).read_bytes()==v for f,v in files.items())
    else:
        assert not p.exists();p.mkdir()
        for f,v in files.items():(p/f).write_bytes(v)
    print(json.dumps({'candidate':NAME,'hashes':{f:sha(v)for f,v in files.items()},'status':'REPAIR_NATIVE_FIRST'}))

if __name__=='__main__':main()
