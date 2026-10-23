"""One long-thin machine-index candidate; default verifies exact saved bytes."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, ast, hashlib, importlib.util, json, re

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[3]
CS=HERE.parent
ROUND=CS/'f01-d7-research/round2h-20261023T170031Z'
PARENT=CS/'f01-r8-combined-result-guard/Kernel.lean'

def sha(b):return hashlib.sha256(b).hexdigest()

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--write',action='store_true');args=ap.parse_args()
    raw=PARENT.read_bytes();assert sha(raw)=='41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7'
    old=raw.decode();inc=(HERE/'increment.lean').read_bytes().decode();assert '\r' not in old and '\r' not in inc
    assert 'R10DirectMachine' not in old and 'bmmBeforeR10Machine' not in old
    a=old.rindex('\ndef bmm (batch m n p : Nat)');z=old.index('\nend Submission',a);block=old[a:z]
    rename=re.sub(r'\bbmm_spec\b','bmmBeforeR10Machine_spec',block)
    rename=re.sub(r'\bbmm\b','bmmBeforeR10Machine',rename)
    assert rename.replace('bmmBeforeR10Machine_spec','bmm_spec').replace('bmmBeforeR10Machine','bmm')==block
    renamed=old[:a]+rename+old[z:];new=renamed+'\n\n'+inc;data=new.encode();assert len(data)<=256000
    assert new[:a]==old[:a] and new[a+len(rename):len(renamed)]==old[z:]
    inverse=new[:a]+block+new[a+len(rename):len(renamed)];assert inverse.encode()==raw
    sp=old[old.index('namespace R7SinglePassSum\n'):];assert new.count(sp)==1
    modspec=importlib.util.spec_from_file_location('r8_source_inventory',CS/'f01-r8-combined-result-guard/build.py')
    module=importlib.util.module_from_spec(modspec);modspec.loader.exec_module(module);decl=module.declarations(new)
    names=['Submission.'+n for n in ['add','add_spec','mul','mul_spec','sum','sum_spec','bmm','bmm_spec']]
    assert all(len(decl.get(n,[]))==1 for n in names)
    assert all(len(v)==1 for k,v in decl.items() if k.startswith('Submission.R10DirectMachine.'))
    gate=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py';assert sha(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
    tree=ast.parse(gate.read_text())
    def val(n):return next(x.value for x in tree.body if isinstance(x,ast.Assign) and any(isinstance(t,ast.Name) and t.id==n for t in x.targets))
    assert not re.compile(ast.literal_eval(val('BANNED').args[0])).search(new)
    assert [ln for ln in new.splitlines() if re.search(r'\bimport\b',ln)]==['import ContractTensor']
    env={'re':re,'OPTIONS':ast.literal_eval(val('OPTIONS'))};fn=next(x for x in tree.body if isinstance(x,ast.FunctionDef) and x.name=='options')
    exec(compile(ast.Module(body=[fn],type_ignores=[]),str(gate),'exec'),env);assert env['options'](new) is None
    attrs=ast.literal_eval(val('ATTRIBUTES'))
    for group in re.findall(r'@\[([^\]]*)\]',new):
        for attr in group.split(','):assert attr.split()[-1] in attrs
    now=datetime.now(timezone.utc).isoformat()
    manifest={'candidate':HERE.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(data),'candidate_bytes':len(data),'created_at_utc':now,'parent':PARENT.parent.name,'parent_sha256':sha(raw),'validation_mode':'full-gate','proof_status':'NOT_RUN_NEW_USIZE_LOOP_AND_ALL_INPUT_BOUNDS',
              'mechanism':'Onlyn>4,p<=2 with n,p,andbotharraylengths<USize.size use machinecount/base/stride anduget. Sixguards evaluatedonce perBMM, per-output basecasts, perMAC machineindex arithmetic. Exactnative multiplythenadd, +0,finalNaNguard/rawreplay retained. Allother/oversized paths retain41.',
              'proof':'row-major bounds for everydecodedq andk; no-wrap machineaddition/multiplication; uget=getD; loop equality tooriginalNativeFinal.dotLoop; actualcore equality toDirectSmall andoriginalfour-spec package. No abstractpremiseleftatentry.',
              'source_boundary':'All41 bytes retained except reversible bmm/spec rename. NativeFinal.dotLoop,DirectSmall,packed,scalar,sum andlicences unchanged. Newnamespace/dispatcher append only.',
              'increment_sha256':sha(inc.encode()),'build_sha256':sha(Path(__file__).read_bytes()),'full_gate':'NOT_RUN','codegen':'NOT_RUN','performance':'UNKNOWN','formal_submission':'NOT_SUBMITTED'}
    if args.write:
        assert not (HERE/'Kernel.lean').exists() and not (HERE/'manifest.json').exists()
        (HERE/'Kernel.lean').write_bytes(data);(HERE/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
        p=ROUND/'astra-bmm.json';r=json.loads(p.read_text());r['usize_route']={**r.get('usize_route',{}),'state':'BUILT_STATIC_ONLY_PENDING_FINAL_REVIEW','candidate':manifest,'old_dispatcher':block,'new_dispatcher':rename,'parent_inverse_sha256':sha(inverse.encode()),'unchanged_prefix_bytes':len(old[:a].encode()),'unchanged_suffix_bytes':len(old[z:].encode()),'new_append_bytes':len(inc.encode()),'namespace_balance':True,'four_exports_specs':{n:decl[n] for n in names},'static_policy':'PASS_IMPORT_SIZE_BANNED_OPTIONS_ATTRIBUTES','remaining':['newexactLean','originalkernel/axioms/checksums','pairedfullcostandthreeindependentinputgroups'],'gain':'UNKNOWN'};p.write_text(json.dumps(r,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    else:
        assert (HERE/'Kernel.lean').read_bytes()==data
        assert json.loads((HERE/'manifest.json').read_text())['candidate_sha256']==sha(data)
    print(json.dumps({'sha256':sha(data),'bytes':len(data),'margin':256000-len(data),'static':'PASS','parent_inverse':True,'exact_Lean':'NOT_RUN'}))

if __name__=='__main__':main()
