"""Build the first complete cross-row prototype, never overwrite a saved Kernel."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, ast, hashlib, importlib.util, json, re

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[3]
CS=HERE.parent
ROUND=CS/'f01-d7-research/round7h-20261023T193125Z'
PARENT=CS/'f01-d10-bmm-direct-rows/Kernel.lean'
EXPECTED='a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78'

def sha(b):return hashlib.sha256(b).hexdigest()

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--write',action='store_true');args=ap.parse_args()
    raw=PARENT.read_bytes();assert sha(raw)==EXPECTED
    old=raw.decode('utf-8');addition=(HERE/'increment.lean').read_bytes().decode('utf-8')
    assert '\r' not in old and '\r' not in addition
    assert 'R11CrossRows' not in old and 'bmmBeforeR11Cross' not in old
    a=old.rindex('\ndef bmm (batch m n p : Nat)');z=old.index('\nend Submission',a)
    block=old[a:z];renamed=re.sub(r'\bbmm_spec\b','bmmBeforeR11Cross_spec',block)
    renamed=re.sub(r'\bbmm\b','bmmBeforeR11Cross',renamed)
    assert renamed.replace('bmmBeforeR11Cross_spec','bmm_spec').replace('bmmBeforeR11Cross','bmm')==block
    prefix=old[:a]+renamed+old[z:];result=prefix+'\n\n'+addition;data=result.encode('utf-8')
    assert len(data)<=256000, f'OVERSIZE_NOT_READY: {len(data)}'
    inverse=prefix[:a]+block+prefix[a+len(renamed):];assert inverse.encode()==raw
    inventory_spec=importlib.util.spec_from_file_location('r8_inventory',CS/'f01-r8-combined-result-guard/build.py')
    inventory=importlib.util.module_from_spec(inventory_spec);inventory_spec.loader.exec_module(inventory)
    declarations=inventory.declarations(result)
    exports=['Submission.'+n for n in ['add','add_spec','mul','mul_spec','sum','sum_spec','bmm','bmm_spec']]
    assert all(len(declarations.get(n,[]))==1 for n in exports)
    assert all(len(lines)==1 for n,lines in declarations.items() if n.startswith('Submission.R11CrossRows.'))
    gate=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
    assert sha(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
    tree=ast.parse(gate.read_text())
    def assignment(name):return next(n.value for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id==name for t in n.targets))
    banned=re.compile(ast.literal_eval(assignment('BANNED').args[0]));assert not banned.search(result)
    assert [line for line in result.splitlines() if re.search(r'\bimport\b',line)]==['import ContractTensor']
    env={'re':re,'OPTIONS':ast.literal_eval(assignment('OPTIONS'))};fn=next(n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name=='options')
    exec(compile(ast.Module(body=[fn],type_ignores=[]),str(gate),'exec'),env);assert env['options'](result) is None
    attrs=ast.literal_eval(assignment('ATTRIBUTES'))
    for group in re.findall(r'@\[([^\]]*)\]',result):
        for item in group.split(','):assert item.split()[-1] in attrs
    now=datetime.now(timezone.utc).isoformat()
    manifest={'candidate':HERE.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(data),'candidate_bytes':len(data),'created_at_utc':now,'parent':PARENT.parent.name,'parent_sha256':EXPECTED,'retained_control_sha256':'41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7',
              'mechanism':'p=2 positive-n matrices with>=4flattenedrows: localP12 packets forfour independentrows,8orderedFloat32accumulators, exactrawNaN finish intoW8,flatfinal output. EachrowA conversion sharedbetweencolumns; fouridenticalBbases reuse twoconversions, crossingbatch bases remainseparate.',
              'actual_guard':'p=2 AND4<=batch*m AND0<n ANDn<USize.size ANDA.size<USize.size ANDB.size<USize.size ANDbatch*m*p<USize.size',
              'tail':'ceilrows/4 groups; up to3 extra rows computedusingtotalgetD,notreturned. Empty/n0/otherp/hugecases fall backtoa066.',
              'proof_chain':'Concretepacketreads -> eachF8lane equalsoriginalordered NativeFinal.dotLoop -> originalfinish/NaNreplay -> losslessW8wordrebuild ->crossbatch/tail mapping -> DirectRows.core ->originalbmm_spec. No unclosedexternalpremise intended.',
              'preservation':'Originala066 bytes retained except reversiblefinalbmm/spec rename. Allpriorruntime/proof/licence blocks remain; no pruning/minification.',
              'validation_mode':'full-gate','proof_status':'NOT_RUN_FIRST_COMPLETE_CROSSROW_PROTOTYPE','full_gate':'NOT_RUN','codegen':'NOT_RUN','performance':'UNKNOWN','formal_submission':'NOT_SUBMITTED','increment_sha256':sha(addition.encode()),'build_script_sha256':sha(Path(__file__).read_bytes())}
    report={'candidate':manifest,'namespace_balance':'PASS_LEXICAL_ONLY','exports_and_specs':{n:declarations[n] for n in exports},'static_policy':'PASS_SIZE_IMPORT_BANNED_OPTIONS_ATTRIBUTES','source_margin_bytes':256000-len(data),'rename':{'old_start_char':a,'old_end_char':z,'old':block,'new':renamed},'parent_inverse_sha256':sha(inverse.encode()),'new_block_bytes':len(addition.encode()),'source_before_rename_sha256':sha(old[:a].encode()),'source_after_rename_sha256':sha(old[z:].encode()),'scope':'Static/full-source preparation only. No Lean,hardware,C/asm or performance evidence inherited.'}
    if args.write:
        assert not (HERE/'Kernel.lean').exists() and not (HERE/'manifest.json').exists()
        (HERE/'Kernel.lean').write_bytes(data)
        (HERE/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
        (HERE/'source-review.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    else:
        assert (HERE/'Kernel.lean').read_bytes()==data
        assert json.loads((HERE/'manifest.json').read_text())['candidate_sha256']==sha(data)
    print(json.dumps({'sha256':sha(data),'bytes':len(data),'margin':256000-len(data),'static':'PASS','exact_Lean':'NOT_RUN','parent_inverse':True}))

if __name__=='__main__':main()
