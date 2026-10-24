"""Verify old actual capture as a scoped reference, never as new-code evidence."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
import sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
CS=HERE.parent.parent
ROOT=CS.parents[2]
sha=lambda b:hashlib.sha256(b).hexdigest()
run=CS/'f01-mul-log2-proof1/ci-runs/40080782614'
index=json.loads((run/'original-artifact-hashes.json').read_bytes())
directory=run/index['directory']
relative='diagnostics/f01-d7-public-suite/public-suite/codegen/f01-r12-column4-narrow/capture-6cd6a140f1db4f6a85d4c8b6d4584c6d'
cap=directory/relative
for name in ['snapshot.json','capture-record.json','compiled-Submission.lean','file-0-MainFull.c','file-3-Submission.c','file-6-BenchSuite.c']:
    data=(cap/name).read_bytes();entry=index['files'][relative+'/'+name]
    assert sha(data)==entry['sha256'] and len(data)==entry['bytes']
record=json.loads((cap/'capture-record.json').read_bytes())
assert record['kernel_sha256']=='da09fb59fa456b498af6bde48d54adcd37f85c4ba7df272163b184a2b83038c4'
old=(cap/'compiled-Submission.lean').read_bytes()
assert sha(old)==record['kernel_sha256']
parent=(CS/'f01-d12-scalar-combined/Kernel.lean').read_bytes()
assert sha(parent)=='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
same=[]
for name,ns,start,end in [('Packed10.packB','namespace Packed10\n\nstructure F10','def packB (batch n p : Nat)','\ntheorem packB_get'),('RowStream.output','namespace Submission.RowStream','def output (batch m n p : Nat)','\ntheorem output_prefix')]:
    def fragment(raw):
        s=raw.decode();assert s.count(ns)==1
        a=s.index(start,s.index(ns));b=s.index(end,a);return s[a:b].encode()
    a,b=fragment(old),fragment(parent);assert a==b
    same.append(dict(name=name,bytes=len(a),sha256=sha(a)))
parser=HERE.parent/'round6h-20261024T051445Z/astra-audit-column4.py'
spec=importlib.util.spec_from_file_location('old_readonly_parser',parser)
mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
fs={}
for name in ['file-0-MainFull.c','file-3-Submission.c','file-6-BenchSuite.c']:
    for symbol,item in mod.functions((cap/name).read_text(),name).items():
        if symbol in fs:assert fs[symbol]['body_sha256']==item['body_sha256']
        fs[symbol]=item
paths=mod.paths_from(fs,['_lean_main'])
chosen={n:{**f,'path_from_actual_MainFull':paths.get(n)} for n,f in fs.items()
        if ('RowStream_output' in n and ('mapMUnsafe_map' in n or n.endswith('RowStream_output')))
        or n.endswith('Packed10_packB___lam__0') or n.endswith('Packed10_packB___lam__1')}
print(json.dumps({n:bool(v['path_from_actual_MainFull']) for n,v in chosen.items()},indent=2))
assert any('mapMUnsafe_map' in n and v['path_from_actual_MainFull'] for n,v in chosen.items())
assert any(n.endswith('Packed10_packB___lam__0') and v['path_from_actual_MainFull'] for n,v in chosen.items())
for n,v in chosen.items():
    if n.endswith('Packed10_packB___lam__0') or ('mapMUnsafe_map' in n and not n.endswith('___boxed')):
        assert v['calls'].get('lean_float32_of_bits')==1
asm=[]
for obj in record.get('disassembly',{}).get('objects',[]):
    for symbol in obj.get('symbols',[]):
        if symbol['symbol'] in chosen:asm.append(symbol)
out=dict(state='VERIFIED_OLD_ACTUAL_CAPTURE_SCOPED_REFERENCE_ONLY',at_utc=datetime.now(timezone.utc).isoformat(),
    run=40080782614,captured_candidate_sha256=sha(old),current_parent_sha256=sha(parent),
    current_candidate_sha256='7086031b8164647e199f52c6b44fc7f54233ec4e75e2221fa95d30a676270d57',
    canonical_capture=str(cap.relative_to(ROOT)).replace('\\','/'),
    original_index_sha256=sha((run/'original-artifact-hashes.json').read_bytes()),
    matching_runtime_source_definitions=same,chosen_C=chosen,available_chosen_assembly=asm,
    parser_sha256=sha(parser.read_bytes()),script_sha256=sha(Path(__file__).read_bytes()),
    findings=['Actual MainFull reaches old RowStream preparation; A map and valid B read each contain a foreign of_bits call.',
      'RowStream C retains raw A and B, prepares nativeA and packedB, folds output, then decrements both prepared buffers. Input lifetime/ownership is unchanged in708.',
      'A map still has Float32 boxing; B packet has ten scalar fields in one record. No per-float F10 boxes asserted.',
      'Existing R2 scaleTable is shared with already-present scalar/sum conversion. No new table definition or claim of eliminating table initialization.'],
    limitations='Exact df5c/new708 actual machine code, dynamic branch counts, cost and final linked layout remain UNKNOWN. Old da09 C and equal source fragments do not establish unchanged new compiler output.')
(HERE/'astra-preparation-reference.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
print(json.dumps(dict(source_matches=same,chosen_count=len(chosen),chosen_asm_count=len(asm),chosen_symbols=list(chosen)),indent=2))
