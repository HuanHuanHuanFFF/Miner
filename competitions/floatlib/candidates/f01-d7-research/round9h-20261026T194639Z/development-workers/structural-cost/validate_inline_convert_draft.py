"""Static exact delta and eligibility interpretation only; never Lean/numeric proof."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,difflib,re

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda b:hashlib.sha256(b).hexdigest()
delta=json.loads((HERE/'inline-convert-exact-delta.json').read_text(encoding='utf-8'))
parent=(ROOT/delta['parent']['path']).read_bytes()
draft=(ROOT/delta['draft']['path']).read_bytes()
assert sha(parent)==delta['parent']['sha256']=='9f7f96d71c153681c6a2500fd229e0627cd2ea38a3ad375afdeee25a1657eee1'
assert sha(draft)==delta['draft']['sha256']=='f84ea2dbffbf0406f453bbc20b4335288ba5d77bb787ae33db203665016ac384'
old,new=parent.decode('utf-8'),draft.decode('utf-8')
inverse=new
for edit in reversed(delta['edits']):
    assert inverse.count(edit['new'])==1
    inverse=inverse.replace(edit['new'],edit['old'])
assert inverse.encode('utf-8')==parent
changes=[(tag,a,b,c,d)for tag,a,b,c,d in difflib.SequenceMatcher(None,old.splitlines(),new.splitlines(),autojunk=False).get_opcodes()if tag!='equal']
assert len(changes)==2 and all(r[0]=='replace'for r in changes)
s=new.index('namespace Indexed\n',new.index('namespace Submission.R15PackedB2\n'))
runtime=new[new.index('def wordLoop',s):new.index('theorem wordLoop_eq',s)]
proof=new[new.index('theorem wordLoop_eq',s):new.index('@[inline] def within',s)]
assert runtime.count('R2W01b.convert')==1 and 'Submission.R2W01b'not in runtime
assert runtime.count('A.uget')==runtime.count('B.toArray.uget')==1
assert runtime.count('(s0 + a * b.s0) (s1 + a * b.s1)')==1
assert 'Array.map'not in runtime and 'Array.ofFn'not in runtime and 'Vector.ofFn'not in runtime
assert proof.count('R2W01c.convert_eq')==1
assert new.count('def convert (u : UInt32)')==old.count('def convert (u : UInt32)')
assert new.count('namespace R2W01b')==old.count('namespace R2W01b')
assert len(draft)<=256000
for token in ('sorry','axiom ','unsafe ','implemented_by ','extern '):assert new.count(token)==old.count(token)

MASK=(1<<32)-1
def gate(u):
    a=u&0x7fffffff
    return 0x0bffffff<=((a-1)&MASK) and a<0x7f800000
def domain(u):
    a=u&0x7fffffff
    return a==0 or 0x0c000000<=a<0x7f800000
boundary=[];tests=0
for sign in (0,0x80000000):
    for exponent in range(256):
        for fraction in (0,1,0x3fffff,0x400000,0x7fffff):
            u=sign|(exponent<<23)|fraction
            assert gate(u)==domain(u)
            tests+=1
    for magnitude in (0,1,0x007fffff,0x00800000,0x0bffffff,0x0c000000,0x7f7fffff,0x7f800000,0x7f800001,0x7fc00000):
        u=sign|magnitude;assert gate(u)==domain(u)
        boundary.append(dict(raw=f'0x{u:08x}',eligible=gate(u)))
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='EXACT_INVERSE_AND_DIRECTED_GATE_INTERPRETATION_PASS',
            parent_sha256=sha(parent),draft_sha256=sha(draft),bytes=len(draft),changed_line_regions=changes,
            inverse_byte_exact=True,only_runtime_change='Raw A conversion expression in Indexed.wordLoop',
            only_proof_change='Existing convert_eq added to wordLoop_eq simp-only list',
            gate_interpretation_checks=tests,boundaries=boundary,
            proof_obligations=['Ordinary compilation of entire new Kernel',
                               'Original complete Submission/VerifyFull kernel replay',
                               'Retain parent actual15 helper roots, especially changed Indexed.wordLoop_eq',
                               'Optional explicit existing root R2W01c.convert_eq; never nonexistent Indexed.runDot_eq',
                               'Original complete gate and checksums, then own firstD and unchanged confirmation policy'],
            status=dict(Lean='NOT_RUN',kernel_replay='NOT_RUN',axioms='NOT_RUN',selected_MainFull_C='NOT_RUN',
                        ASM='NOT_RUN',full_gate='NOT_RUN',performance='NOT_RUN'),
            limits=['Finite gate checks establish only interpretation of eligibility on directed words',
                    'Existing global convert_eq is the intended proof bridge; new caller proof has not been checked',
                    'No incoming40398675395 result, future holdout, or model-derived timing was used'])
(HERE/'inline-convert-validation.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:record[k]for k in ('state','draft_sha256','bytes','changed_line_regions','gate_interpretation_checks')},indent=2))
