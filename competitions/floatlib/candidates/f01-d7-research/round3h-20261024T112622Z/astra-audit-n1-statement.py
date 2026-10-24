"""Actual8661 statement-diagnostic C audit, with scalar fa dataflow binding."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,re,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;CS=HERE.parent.parent;ROOT=CS.parents[2]
EXPECTED='8661a3a5a1988b2d6b3d827aa37a7abeb81c50fffabcc38f8c8476961b425e0c'
sha=lambda raw:hashlib.sha256(raw).hexdigest()
ci=CS/'f01-mul-log2-proof1/ci-runs/40097476072';ip=ci/'original-artifact-hashes.json';idx=json.loads(ip.read_bytes());directory=ci/idx['directory']
sub='diagnostics/f01-d7-public-suite/public-suite/';cap=directory/sub/'diagnostics/f01-r13-n1-prepared-row-output'
for name,e in idx['files'].items():
    raw=(directory/name).read_bytes();assert sha(raw)==e['sha256'] and len(raw)==e['bytes']
summary=json.loads((directory/sub/'summary.json').read_bytes());row=next(r for r in summary['results'] if r['candidate']=='f01-r13-n1-prepared-row-output');vp=directory/sub/row['verdict'];verdict=json.loads(vp.read_bytes())
assert row['kernel_sha256']==EXPECTED and row['statement_pass'] and not row['full_gate'] and verdict['passed'] and not verdict['rounds']
assert sha(vp.read_bytes())==row['verdict_sha256']
sp=importlib.util.spec_from_file_location('n1_statement_parser',HERE.parent/'round6h-20261024T051445Z/astra-audit-column4.py');mod=importlib.util.module_from_spec(sp);sp.loader.exec_module(mod)
cindex=json.loads((cap/'candidate-c-index.json').read_bytes());fs={};texts={}
for e in cindex:
    raw=(cap/e['file']).read_bytes();assert sha(raw)==e['sha256'] and e['kernel_sha256']==EXPECTED
    text=raw.decode();texts[e['file']]=text
    for name,f in mod.functions(text,e['file']).items():
        if name in fs:assert fs[name]['body_sha256']==f['body_sha256']
        fs[name]=f
main=mod.paths_from(fs,['_lean_main']);bmm='lp_competition_Submission_bmm';assert bmm in main
allpaths=mod.paths_from(fs,[bmm]);output='lp_competition_Submission_R13N1Prepared_output';assert output in allpaths
paths=mod.paths_from(fs,[output]);assert not any('NativeFinal_dotLoop' in n or n.endswith('NativeFinal_dot') for n in paths)
selected={n:dict(**fs[n],path_from_selected_n1_output=paths[n]) for n in paths if 'R13N1Prepared_' in n}
col=next(n for n,f in selected.items() if re.search(r'\bfloat\s+\w+',f['header']))
rowfn=next(n for n,f in selected.items() if n!=col and f['calls'].get(col)==1)
def body(n):
    f=fs[n];return '\n'.join(texts[f['artifact']].splitlines()[f['line']-1:])[:f['bytes']]
cb=body(col);rb=body(rowfn)
fa_param=re.search(r'\bfloat\s+(\w+)',fs[col]['header'])[1]
fa_value=re.search(r'(\w+) = lean_float32_of_bits\(',rb)[1]
call_args=re.search(re.escape(col)+r'\(([^;]+)\);',rb)[1].split(',')
assert call_args[2].strip()==fa_value
assert f'lean_float32_mul({fa_param},' in cb
for n in [rowfn,col]:
    calls=fs[n]['calls'];assert calls.get('lean_float32_of_bits')==1
    assert not any(k.startswith('lean_apply_') or k in ['lean_alloc_closure','lean_box_float32'] for k in calls)
assert fs[col]['calls'].get('lean_float32_mul')==1 and fs[col]['calls'].get('lean_float32_add')==1
assert fs[col]['calls'].get('lean_float32_beq')==1 and fs[col]['calls'].get('lean_float32_to_bits')==1
assert fs[col]['calls'].get('lp_competition_Submission_R7NaNReplay_replayEarly')==1
assert fs[output]['calls'].get('lean_mk_empty_array_with_capacity')==1
for n,f in selected.items():
    f['C_body']=body(n)
    f['sensitive_calls']={k:v for k,v in f['calls'].items() if any(t in k for t in ['float32','array_push','closure','apply_','dotLoop','replayEarly'])}
ai=json.loads((cap/'native-assembly-index.json').read_bytes()) if (cap/'native-assembly-index.json').exists() else []
rec=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='VERIFIED_STATEMENT_PASS_AND_ACTUAL_N1_C_DATAFLOW',run=40097476072,
    source_commit=summary['source_commit'],official_commit=summary['official_commit'],candidate_sha256=EXPECTED,
    verdict_sha256=row['verdict_sha256'],statement_seconds=verdict['seconds'],full_gate=False,actual_rounds=0,
    original_index_sha256=sha(ip.read_bytes()),all_original_members_verified=len(idx['files']),
    canonical_directory=str(cap.relative_to(ROOT)).replace('\\','/'),C_index=cindex,MainFull_to_BMM=main[bmm],BMM_to_selected_n1=allpaths[output],
    actual_selected_functions=selected,prepared_fa=dict(row_function=rowfn,row_decode_value=fa_value,column_function=col,column_float_parameter=fa_param),
    findings=['The actual row specialization decodes A once and passes that native scalar directly as the third C argument to the column specialization, whose parameter type is float.',
      'The ordinary selected column body reads/converts B once, performs oneFloat32 multiply then oneFloat32 add with the original+0, checks result with self-BEq, and serializes or calls original raw replayEarly1.',
      'No NativeFinal.dot/dynamicdotLoop is reachable from the selected n1 output chain. The output still has its necessary row/column loops, and other dispatch routes retain their original dynamic dots.',
      'Neither row nor column C has lean_apply, closure allocation or Float32 boxing. Two static array-push sites in the column belong to mutually exclusive normal/NaN branches, not two pushes per output.',
      'One final-capacity Array allocation precedes row traversal. No global A map, B pack/F10, rowVector/flatMap or Cross-fused component is introduced.'],
    available_assembly_symbols=[e['symbol'] for e in ai if e.get('kind')=='actual-built-object-disassembly'],
    limits=['This is the successful statement/bench-build diagnostic C, not the clean timed gate object. Full axioms/replay/checksums and25-round performance remain pending.',
      'No new actual row/column machine assembly is retained here. Live-fa spills around BofBits/outputtoBits, zero-thunk checks, final inlining/layout, allocation counts and cycles remain UNKNOWN.',
      'C elimination of a repeat decode/loop does not establish complete-call benefit or inherited f448 performance.'],
    script_sha256=sha(Path(__file__).read_bytes()))
(HERE/'astra-n1-statement-codegen-1324008.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
print(json.dumps(dict(state=rec['state'],statement_seconds=rec['statement_seconds'],prepared_fa=rec['prepared_fa'],available_asm=rec['available_assembly_symbols']),indent=2))
