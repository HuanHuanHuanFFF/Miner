"""Independent B2 static-table representation experiment. No compiler execution."""
from pathlib import Path
import hashlib,json,datetime,struct
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
BASE=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
sha=lambda b:hashlib.sha256(b).hexdigest()
raw=BASE.read_bytes(); assert sha(raw)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
s=raw.decode(); frag=(HERE/'Compact-scales.lean.inc').read_text(encoding='utf-8')
marker='end R2W01c\n\n\nnamespace Submission'
assert s.count(marker)==1
modified=s.replace(marker,'end R2W01c\n\n'+frag+'\nnamespace Submission')
edits=[]
for name,op,helper in [('add','+','addNative'),('nativeMul','*','mulNative')]:
    decl=f'@[inline] def {name} (x y : Binary32) : Binary32 :='
    source=f'let result := R2W01b.convert x.raw.1 {op} R2W01b.convert y.raw.1'
    entry=decl+'\n  '+source
    assert modified.count(entry)==1
    start=modified.index(entry)
    stop=modified.index('\n\n@[inline] def ',start+len(decl))
    old=modified[start:stop]
    assert old.count(source)==1
    new=old.replace(source,f'let result := R19CompactScales.{helper} x.raw.1 y.raw.1')
    proof='  dsimp only\n  split'
    assert new.count(proof)==1
    new=new.replace(proof,f'  dsimp only\n  simp only [R19CompactScales.{helper}_eq]\n  split')
    modified=modified[:start]+new+modified[stop:]
    edits.append((old,new))
b=modified.encode(); assert len(b)<=256000
out=HERE/'Kernel-compact-scales.lean';out.write_bytes(b)
undo=modified
for old,new in reversed(edits):
    assert undo.count(new)==1;undo=undo.replace(new,old)
undo=undo.replace('end R2W01c\n\n'+frag+'\nnamespace Submission',marker)
assert undo.encode()==raw
for j in range(512):
    e=j&255;sgn=(j&256)<<23
    bits=sgn|((e-23)<<23) if 24<=e<=254 else sgn
    f=struct.unpack('<f',struct.pack('<I',bits))[0]
    again=struct.unpack('<I',struct.pack('<f',float(f)))[0]
    assert bits==again,(j,bits,again)
manifest={
 'created_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
 'state':'COMPLETE_SOURCE_PROOF_ATTEMPT_NOT_RUN',
 'candidate':{'path':str(out),'bytes':len(b),'sha256':sha(b)},
 'baseline':{'path':str(BASE),'sha256':sha(raw)},
 'fragment':{'path':'Compact-scales.lean.inc','sha256':sha(frag.encode())},
 'inverse_splice_exact':True,
 'scope':'Selected scalar add/nativeMul decoder calls and any transitive tensor repair calls through them. SUM/BMM bodies and LowScale source are preserved; this is not a claim of identical generated tensor code.',
 'mechanism':'Globally checked 512-entry FloatArray scale table: remove one boxed-element pointer chase per table read; add one double-to-float cast and one global validity guard per scalar call.',
 'complete_costs':['512 original widening operations to build packed table','512 widening/narrowing/raw equality validations','original scaleTable remains live','global flag/initialization checks','packed global access and Float64 narrowing per hit','unchanged original fallback if valid=false','unchanged input classifier, mantissa conversion, scale multiply, arithmetic, output codec and NaN fallback'],
 'initialization_boundary':'Static module constants under the unchanged official build/bench. No input preprocessing. Actual eager/lazy initialization and first-call inclusion must be recorded from candidate C and official benchmark boundary.',
 'model':{'entries':512,'raw_roundtrip_mismatches':0,'engine':'Python struct host binary32/double; not Lean proof or pinned runtime test'},
 'lean':'NOT_RUN','codegen':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN',
 'stop_conditions':['Cannot prove checked_entry using imported safe FloatArray definitions','Hot path calls FloatArray.data or builds/checks table repeatedly','Extra branch/initialization/cast work removes plausible pointer-load savings','Original full discovery fails'],
 'CI_owner':'D','CI_occupancy':0,'tokens':'UNKNOWN','cached_input_tokens':'UNKNOWN'
}
(HERE/'compact-scales-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'bytes':len(b),'sha256':sha(b),'constant_entries_checked':512,'inverse_splice_exact':True}))
