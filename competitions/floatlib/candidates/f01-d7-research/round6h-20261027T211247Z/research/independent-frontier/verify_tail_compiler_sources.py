from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
D=Path(__file__).resolve().parent
idx=json.loads((D/'tail-compiler-source-index.json').read_bytes());rows=[]
for item in idx['source_files']:
    p=D/item['file'];b=p.read_bytes();blob=hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()
    assert blob==item['git_blob'],item['file']
    rows.append({**item,'bytes':len(b),'sha256':hashlib.sha256(b).hexdigest()})
basic=(D/'tail-PreDefinition-Basic.lean').read_text()
wf=(D/'tail-WF-Main.lean').read_text()
borrow=(D/'tail-LCNF-InferBorrow.lean').read_text()
emit=(D/'codec-LCNF-EmitC.lean').read_text()
scc=(D/'tail-LCNF-SplitSCC.lean').read_text()
assert 'addAndCompilePartialRec docCtx preDefs' in wf
assert 'type        := preDef.type' in basic and 'value       := preDef.value' in basic
assert 'we currently support TCO for self-calls only' in borrow
assert '(← read).currDecl == f && x == ret' in borrow
assert '(← getCurrFn) == declName' in emit and 'emitLn "goto _start;"' in emit
assert 'return newSccs.toArray.map (fun scc => scc.toArray.map declMap.get!)' in scc
old=json.loads((D/'codec-source-index.json').read_bytes())
item=next(x for x in old['files'] if x['name']=='codec-LCNF-EmitC.lean')
eb=(D/'codec-LCNF-EmitC.lean').read_bytes();assert hashlib.sha256(eb).hexdigest()==item['sha256']
out={'verified_utc':datetime.now(timezone.utc).isoformat(),'state':'HOLD_ABI_UNMEASURED_NO_LEAN_MUTUAL_TCO_GUARANTEE',
     'fixed_commit':idx['fixed_commit'],'source_files':rows,
     'emitter':{'file':'codec-LCNF-EmitC.lean','sha256':hashlib.sha256(eb).hexdigest(),'bytes':len(eb)},
     'logical_PSumpack_not_runtime_allocation_proof':True,'self_tail_goto_confirmed_from_source':True,
     'mutual_machine_tail_jumps':'UNKNOWN_REQUIRES_EXACT_CODEGEN','new_runtime_or_CI':False,
     'note_sha256':hashlib.sha256((D/'TAIL-CONTINUATION-ABI-PREMISE.md').read_bytes()).hexdigest()}
(D/'tail-compiler-source-verification.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({'files':len(rows)+1,'new_source_bytes':sum(x['bytes'] for x in rows),'state':out['state']}))
