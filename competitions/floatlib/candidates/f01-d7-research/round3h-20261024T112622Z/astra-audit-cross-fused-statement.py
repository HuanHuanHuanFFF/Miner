"""Exact3c5e statement-build caller/ownership audit; not clean-gate machine evidence."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,re,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;CS=HERE.parent.parent;ROOT=CS.parents[2]
EXPECTED='3c5ef024e33f5858ee001f18bde42c2db1857d4513540924e5b750614d2f07e6'
sha=lambda data:hashlib.sha256(data).hexdigest()
ci=CS/'f01-mul-log2-proof1/ci-runs/40094769314';ip=ci/'original-artifact-hashes.json'
index=json.loads(ip.read_bytes());directory=ci/index['directory']
relative='diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r13-cross-fused-output';cap=directory/relative
for name,e in index['files'].items():
    raw=(directory/name).read_bytes();assert sha(raw)==e['sha256'] and len(raw)==e['bytes']
cindex=json.loads((cap/'candidate-c-index.json').read_bytes())
parser=HERE.parent/'round6h-20261024T051445Z/astra-audit-column4.py'
sp=importlib.util.spec_from_file_location('fused_parser',parser);mod=importlib.util.module_from_spec(sp);sp.loader.exec_module(mod)
fs={};texts={}
for e in cindex:
    raw=(cap/e['file']).read_bytes();assert sha(raw)==e['sha256'] and e['kernel_sha256']==EXPECTED
    text=raw.decode();texts[e['file']]=text
    for symbol,f in mod.functions(text,e['file']).items():
        if symbol in fs:assert fs[symbol]['body_sha256']==f['body_sha256']
        fs[symbol]=f
main=mod.paths_from(fs,['_lean_main']);entry='lp_competition_Submission_bmm';assert entry in main
paths=mod.paths_from(fs,[entry]);assert not any('R11CrossRows_words' in n or 'R11CrossRows_core' in n for n in paths)
selected={n:dict(**fs[n],BMM_path=paths[n]) for n in paths if 'R13CrossFused' in n}
assert len(selected)==2
output_name=next(n for n in selected if n.endswith('R13CrossFused_output___redArg'))
loop_name=next(n for n in selected if 'Fin_foldl_loop' in n)
assert selected[output_name]['calls'].get('lean_mk_empty_array_with_capacity')==1
loop=selected[loop_name];calls=loop['calls']
assert calls.get('lp_competition_Submission_R11CrossRows_blockRows___redArg')==1
assert calls.get('lean_array_push')==8 and calls.get('lean_ctor_get_uint32')==8
assert not any(k.startswith('lean_apply_') or 'append' in k or 'wordAt' in k or 'array_fget' in k or 'array_uget' in k or 'nat_div' in k or 'nat_mod' in k for k in calls)
text=texts[loop['artifact']];body='\n'.join(text.splitlines()[loop['line']-1:])[:loop['bytes']]
header=loop['header'];args=re.findall(r'lean_object\*\s+(\w+)',header.split('(',1)[1]);assert len(args)==9
out_arg=args[-2]
assert f'lean_inc_ref({out_arg})' not in body and f'lean_inc({out_arg})' not in body
w=re.search(r'(\w+) = lp_competition_Submission_R11CrossRows_blockRows___redArg\(',body)[1]
release=[dict(line=loop['line']+i,text=s.strip()) for i,s in enumerate(body.splitlines()) if f'lean_dec_ref({w})' in s]
assert len(release)==2
loop['writer_C']=body;loop['input_output_array_parameter']=out_arg;loop['Word8_release_branches']=release
unchanged=[n for n in paths if any(t in n for t in ['R11CrossRows_blockRows','R11CrossRows_blockAt','R11CrossRows_dot8','R11CrossRows_packShared','R11CrossRows_packGeneral','R11CrossRows_wordLoop','R11CrossRows_finish8','R7NaNReplay_replayEarly'])]
assert any('R11CrossRows_packShared' in n for n in unchanged) and any('R11CrossRows_wordLoop' in n for n in unchanged)
ai=json.loads((cap/'native-assembly-index.json').read_bytes());asm=[e['symbol'] for e in ai if e['kind']=='actual-built-object-disassembly']
rec=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='VERIFIED_ACTUAL_STATEMENT_BUILD_C_FUSION_STRUCTURE',run=40094769314,
    candidate_sha256=EXPECTED,index_sha256=sha(ip.read_bytes()),original_members_verified=len(index['files']),
    canonical_directory=str(cap.relative_to(ROOT)).replace('\\','/'),C_index=cindex,MainFull_to_BMM=main[entry],actual_new_callees=selected,
    original_compute_chain_still_reachable=unchanged,old_Cross_words_and_core_reachable=False,
    findings=['Actual diagnostic MainFull/BMM reaches new output and specialized group fold; old Cross all-groups words/core is absent from that call graph.',
      'One final-capacity allocation precedes the fold. Each group calls original blockRows once and has eight direct UInt32 field-to-array-push sites, guarded in row order.',
      'No read callback, per-output quotient/remainder, old Word8-vector lookup, append or intermediate row-array call is present in the actual writer C.',
      'Output array is passed through push-return aliases and loop phi without incrementing its own reference. Together with fresh capacity allocation this supports exclusive reuse; no allocation trace or final machine proof is claimed.',
      'Original W8 is decremented in either final-row branch; in the full-row branch release precedes the final two pushes. It is not retained in an all-groups array. Existing F8-to-W8 reuse is unchanged.',
      'C still computes batch*m once per group and4*g; final optimizer hoisting/cost UNKNOWN. Do not modify frozen source based only on this static observation.'],
    retained_assembly_symbols=asm,
    limits=['Retained assembly is only Packed10Index; no actual new writer assembly is available. No whole speedup, allocator count, peak RSS or final linked layout follows from C alone.',
      'Successful statement/bench-build diagnostic context is distinct from a clean timed gate object. Full gate and clean/per-input performance are pending.'],
    script_sha256=sha(Path(__file__).read_bytes()),parser_sha256=sha(parser.read_bytes()))
(HERE/'astra-cross-fused-statement-codegen.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
print(json.dumps(dict(state=rec['state'],callees=list(selected),old_words_reachable=False,writer_line=loop['line'],Word8_release=release,available_asm=asm),indent=2))
