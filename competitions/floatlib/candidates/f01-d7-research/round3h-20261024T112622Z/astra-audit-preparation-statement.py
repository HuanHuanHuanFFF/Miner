"""Audit708's actual statement-diagnostic build, not the clean timing object."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,re,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
CS=HERE.parent.parent
ROOT=CS.parents[2]
EXPECTED='7086031b8164647e199f52c6b44fc7f54233ec4e75e2221fa95d30a676270d57'
sha=lambda b:hashlib.sha256(b).hexdigest()
run=CS/'f01-mul-log2-proof1/ci-runs/40091246795'
index_path=run/'original-artifact-hashes.json'
index=json.loads(index_path.read_bytes());directory=run/index['directory']
relative='diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r13-preparation-convert'
cap=directory/relative
for name,entry in index['files'].items():
    data=(directory/name).read_bytes();assert len(data)==entry['bytes'] and sha(data)==entry['sha256']
ci=json.loads((cap/'candidate-c-index.json').read_bytes())
ai=json.loads((cap/'native-assembly-index.json').read_bytes())
parser=HERE.parent/'round6h-20261024T051445Z/astra-audit-column4.py'
spec=importlib.util.spec_from_file_location('preparation_parser',parser);mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
fs={};texts={}
for e in ci:
    assert e['kernel_sha256']==EXPECTED
    data=(cap/e['file']).read_bytes();assert sha(data)==e['sha256']
    texts[e['file']]=data.decode()
    for name,item in mod.functions(data.decode(),e['file']).items():
        if name in fs:assert fs[name]['body_sha256']==item['body_sha256']
        fs[name]=item
paths=mod.paths_from(fs,['_lean_main'])
selected={}
for name,f in fs.items():
    relevant=(name.endswith('Packed10_packB___lam__0') or name.endswith('Packed10_packB___lam__1') or name.endswith('RowStream_output') or ('RowStream_output' in name and 'mapMUnsafe_map' in name and not name.endswith('___boxed')))
    if not relevant:continue
    assert name in paths
    text=texts[f['artifact']];body='\n'.join(text.splitlines()[f['line']-1:])[:f['bytes']]
    selected[name]={**f,'statement_build_MainFull_path':paths[name],
        'interesting_lines':[dict(line=f['line']+i,text=l.strip()) for i,l in enumerate(body.splitlines()) if any(t in l for t in ['lean_float32_of_bits(', 'lean_uint32_to_float32(', 'lean_float32_mul(', 'lean_box_float32(', 'lean_alloc_ctor(', 'lean_ctor_set_float32(', 'R2W01b_scaleTable', 'lean_dec_ref(v_nativeA', 'lean_dec_ref(v_packedB'])]}
    if name.endswith('Packed10_packB___lam__0') or 'mapMUnsafe_map' in name:
        assert f['calls'].get('lean_float32_of_bits')==1
        assert f['calls'].get('lean_uint32_to_float32')==1
        assert f['calls'].get('lean_float32_mul')==1
        selected[name]['manual_control_flow']='The fastOK conjunction selects fallback of_bits only on false. True selects numeric mantissa conversion, scaleTable read, Float32 multiply. A rejoins its existing box/array-set path; B returns a native Float32. Padding is handled before the converter.'
assert len(selected)==4
assembly=[]
for e in ai:
    data=(cap/e['file']).read_bytes();assert sha(data)==e['sha256']
    if e['kind']!='actual-built-object-disassembly':continue
    assert e['kernel_sha256']==EXPECTED and e['exit_code']==0
    text=data.decode();pattern=r'^0+ <'+re.escape(e['symbol'])+r'>:\n(.*?)(?=\nDisassembly|\Z)'
    found=re.search(pattern,text,re.M|re.S);assert found,e['symbol']
    body=found[1];hot=[]
    if e['symbol'].endswith('___redArg'):
        for line in body.splitlines():
            m=re.match(r'\s*([0-9a-f]+):\s+(.*)',line)
            if m and 0x40<=int(m[1],16)<0x79:hot.append(m[2])
        assert sum('mulps' in l for l in hot)==3 and sum('addps' in l for l in hot)==3
        assert not any('call' in l or 'rsp' in l for l in hot)
    assembly.append({**e,'body':body,'hot_0x40_to_0x77':hot})
trace=json.loads((cap/'build-trace-2.txt').read_bytes())
assert not trace['synthetic']
trace_text=json.dumps(trace)
assert '-O3' in trace_text and '-ffp-contract=off' in trace_text and '293d5d0c0c3f3dded4688b3ccd6a33939ac5102b' in trace_text
rec=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='VERIFIED_STATEMENT_DIAGNOSTIC_C_MECHANISM_NOT_PERFORMANCE',run=40091246795,
    candidate_sha256=EXPECTED,original_index_sha256=sha(index_path.read_bytes()),original_members_verified=len(index['files']),
    canonical_directory=str(cap.relative_to(ROOT)).replace('\\','/'),C_index=ci,selected_C=selected,loop_assembly=assembly,
    findings=['Both actual diagnostic-build preparation bodies contain numeric fast branch and retained of_bits fallback; no new predicate or loop appears in the MAC recurrence.',
      'A still boxes one Float32 result per source-level iteration. B packet still stores ten Float32 scalar fields in one record with40-byte scalar payload; valid B and zero padding remain distinct.',
      'Diagnostic MainFull closure graph reaches these preparation bodies. The two retained assembly files cover the unchanged Packed10Index loop, not Amap or Bpack.',
      'The redArg diagnostic loop hot interval0x40..0x77 has three separate mulps/addps pairs, no call or rsp access; 4+4+2 lanes are unchanged.'],
    limitations=['No A-map or B-pack machine assembly retained here: the C warm path is verified, but final foreign-call absence, new spills/inlining and cycles remain UNKNOWN.',
      'This is successful statement/bench-build diagnostic context, not a cleaned-up timed original gate object. Full axioms/replay/checksums, clean25-round performance and independent confirmations remain separate.',
      'Old da09 source-equal preparation C is not exact df5c machine code; no per-instruction parent speed comparison or whole-gain inference.'],
    trace=trace,script_sha256=sha(Path(__file__).read_bytes()))
(HERE/'astra-preparation-statement-codegen.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
print(json.dumps(dict(state=rec['state'],selected=list(selected),assembly_count=len(assembly),original_members_verified=rec['original_members_verified']),indent=2))
