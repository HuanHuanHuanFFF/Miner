"""Byte/dependency review only. Never writes a Kernel or proof fragment."""
from pathlib import Path
import datetime,hashlib,json,re

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
ROUND=HERE.parent.parent.parent
PROOF=ROUND/'astra-workers/exact-arithmetic/bias-frontier'
BASE=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
ACTUAL=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40420540388/download-dc507616807e4785a2f3fef3abb4fb38/diagnostics/f01-d7-public-suite/public-suite/inputs/f01-r19-dev-direct-bias-runtime1/Kernel.lean'
EXPECTED={
 'Retained-BranchlessRNE-seed.lean.inc':'5a06c12700e015d3aecbfdbcd2abe879d2bbd68f0d7ed8d75f29289806652279',
 'PostBias.lean.inc':'f60bed0349b0a2ad255636098cde7e9b28a2d874b7bb68fa6ee668b2d83cbc7e',
 'WordBias.lean.inc':'cb6f3c2ed48eeef7cd65fc527abda1f7b8377f1ac11c74d89a5db4b201381c48',
 'FastMulBoundary.lean.inc':'9b5543c69820376f0281dee69aa46f48c470fec1a4d985cb7c351b4a2fe275ca'}
SHA=lambda b:hashlib.sha256(b).hexdigest()

def bind(path,expected=None):
    b=path.read_bytes();h=SHA(b)
    if expected:assert h==expected,(path,h,expected)
    return {'path':str(path.relative_to(ROOT)).replace('\\','/'),'bytes':len(b),'sha256':h}

def declarations(text):
    ns=[];out=[]
    for lineno,line in enumerate(text.splitlines(),1):
        if line.startswith('namespace '):ns.append(line[10:])
        elif line.startswith('end '):ns.pop()
        else:
            m=re.match(r'(?:@\[[^\n]+\]\s*)?(private\s+)?(theorem|def)\s+(\w+)',line)
            if m:out.append({'name':'.'.join(ns+[m[3]]),'private':bool(m[1]),'kind':m[2],'line':lineno})
    assert not ns
    return out

def main():
    base=BASE.read_bytes();actual=ACTUAL.read_bytes()
    bindings=[bind(BASE,'622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'),
              bind(ACTUAL,'74899988939a056a40675aefe8c63f2f9db1c7b4728f3d496bf140ede6ad85dc')]
    assert actual.startswith(base)
    runtime=actual[len(base):];assert len(runtime)==1358
    local_runtime=(PROOF/'Runtime-direct-bias.lean.inc').read_bytes()
    assert runtime.rstrip()==local_runtime.rstrip()
    parts=[];decls={}
    for name,expected in EXPECTED.items():
        bindings.append(bind(PROOF/name,expected));b=(PROOF/name).read_bytes();parts.append(b)
        decls[name]=declarations(b.decode())
    runtime_decls=declarations(runtime.decode())
    assert len(runtime_decls)==3 and all(x['kind']=='def' for x in runtime_decls)
    seed=parts[0].decode();start=seed.index('@[inline] def grouped');end=seed.index('end BranchlessRNESeed')
    cut=(seed[:start]+seed[end:]).encode()
    excluded=('grouped','word_grouped','grouped_eq_existing_rse')
    for frag in parts[1:]+[runtime]:
        assert not re.search(r'\b(?:grouped|word_grouped|grouped_eq_existing_rse)\b',frag.decode())
    all_bytes=base+b''.join(parts)+runtime
    pruned_bytes=base+cut+b''.join(parts[1:])+runtime
    assert len(all_bytes)==247600 and len(pruned_bytes)==245311
    # Simulate namespace-only adaptation in memory; no public wrapper is created.
    renamed=all_bytes.replace(b'Submission',b'R19Base')
    renamed_pruned=pruned_bytes.replace(b'Submission',b'R19Base')
    public=['Submission.'+x+'_spec' for x in ('add','mul','sum','bmm')]
    proof_roots=[x['name'] for ds in decls.values() for x in ds if x['kind']=='theorem' and not x['private']]
    runtime_roots=[x['name'] for x in runtime_decls]
    assert len(proof_roots)==25
    complete=public+proof_roots+runtime_roots
    adapted=public+[n.replace('Submission.','R19Base.') for n in proof_roots+runtime_roots]
    pruned_roots=[n for n in complete if n.rsplit('.',1)[-1] not in excluded]
    assert len(complete)==32 and len(pruned_roots)==30
    (HERE/'HelperAudit-current32.lean.inc').write_text('\n'.join('#print axioms '+x for x in complete)+'\n',encoding='utf-8',newline='\n')
    (HERE/'helper-roots.json').write_text(json.dumps({'scope':'Current named declarations only, not a public-completeness certificate; new bridge roots must be added.',
      'unrenamed_current32':complete,'public_adapter_current32':adapted,'dependency_subset_current30':pruned_roots,
      'private_quotient':'covered transitively through BranchlessRNESeed.nat_bias; do not invent its mangled name'},indent=2)+'\n',encoding='utf-8',newline='\n')
    upstream=ROUND.parent/'round8h-20261024T190259Z'
    indexes=[json.loads((upstream/f).read_text()) for f in ('astra-upstream-index.json','astra-upstream-index2.json')]
    requested=['FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Finite/Runtime.lean','FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Finite/Proof.lean','FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Base/Runtime.lean']
    primary=[]
    for name in requested:
        rows=[row for idx in indexes for row in idx['files'] if row['path']==name];assert rows,name
        row=rows[-1];p=ROOT/row['dest'];b=p.read_bytes()
        assert hashlib.sha1(('blob '+str(len(b))+'\0').encode()+b).hexdigest()==row['git_blob_sha1']
        primary.append({**bind(p),'ref':'0d91825727839f597fd06b22fdd038ea21480f0c','git_blob_sha1':row['git_blob_sha1']})
    primary.append({**bind(HERE/'NativeFPU-Runtime.lean.primary','73f4ee403c934f6df27912a621a4c56069b77bbc2a49f9a4f41f47c59beca12c'),
      'ref':'0d91825727839f597fd06b22fdd038ea21480f0c','git_blob_sha1':'484127a091c11b941939db66c652fa5568da6ea7',
      'url':'https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/NativeFPU/Runtime.lean'})
    gate=HERE.parent/'static-dispatch-frontier/primary/gate-4b7.py'
    bindings.append(bind(gate));assert '_MAX_BYTES = 256_000' in gate.read_text()
    assert 'namespace R14ExponentShift' not in base.decode() and 'namespace Submission.R14ExponentShift' not in base.decode()
    budget={}
    for k,b in [('all_current_fragments',all_bytes),('all_after_namespace_simulation',renamed),('seed_dependency_subset',pruned_bytes),('subset_after_namespace_simulation',renamed_pruned)]:
        budget[k]={'bytes':len(b),'remaining_to_256000_before_public_bridge_wrapper':256000-len(b),'assembly_in_memory_only':True}
    result={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'state':'READ_ONLY_INTERFACE_REVIEW_NO_LEAN_EXECUTION',
      'toolchain':'Lean4.34.0 / 293d5d0c0c3f3dded4688b3ccd6a33939ac5102b','bindings':bindings,'primary_fixed_sources':primary,
      'proof_status':'All current fragments together NOT_RUN; prior exact seed-containing attempts failed and do not supply accepted theorem evidence.',
      'runtime':{'bytes':len(runtime),'sha256':SHA(runtime),'exact_suffix_of_7489':True,'body_matches_actor1359_ignoring_trailing_newlines':True},
      'declarations':decls,'runtime_declarations':runtime_decls,'budget':budget,
      'seed_subset':{'bytes':len(cut),'sha256':SHA(cut),'saves_bytes':len(parts[0])-len(cut),'excluded_declarations':excluded,
        'scope':'Dependency-closed for current PostBias/WordBias/Shape route only; not global minimal proof nor authority to prune actor source.'},
      'roots':{'current_named':len(complete),'subset_named':len(pruned_roots),'missing_future_bridge_roots':'Not yet declared; append actual names from future source, never invent placeholders.'},
      'B2_missing_R14ExponentShift_support':True,'candidate_written':False,'public_wrapper_written':False}
    (HERE/'audit.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'budget':budget,'roots':len(complete),'audit_sha256':SHA((HERE/'audit.json').read_bytes())}))

if __name__=='__main__':main()
