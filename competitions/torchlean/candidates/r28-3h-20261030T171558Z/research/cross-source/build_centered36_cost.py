"""Complete-runtime diagnostic for unsigned affine dot, intentionally unproved.

Retains every original runtime declaration and all original fallback/endpoint
choices. Drops only the old prepared-engine proof block and final correct;
new kernels has no correctness theorem and cannot be adopted/submitted.
Full source remains private. The cost gate is measurement, not acceptance.
"""
from pathlib import Path
import argparse
from datetime import datetime, timezone
import hashlib
import json
import re

HERE=Path(__file__).resolve().parent
BASE="595a90fa2b6bc5d3657434fae7d1292b27910ef653da2b7f409ed9c34c956e2b"
DECL=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(def|lemma|theorem|abbrev|structure)\s+([\w.']+)")


def once(s,a,b):
    assert s.count(a)==1,(a,s.count(a))
    return s.replace(a,b)


def extract(s,name):
    matches=list(DECL.finditer(s))
    for i,m in enumerate(matches):
        if m.group(2)==name:return s[m.start():matches[i+1].start()]
    raise KeyError(name)


def build(raw):
    assert hashlib.sha256(raw).hexdigest()==BASE
    source=raw.decode('utf-8')
    additions=(HERE/'CenteredDotRuntime.leanfrag').read_text(encoding='utf-8')
    pair=extract(source,'MVj')
    pair=once(pair,'def MVj ','def R28CPj ')
    pair=once(pair,'(XP WP:Array (Array Nat))','(XP WP:Array (Array Nat)) (CX CW:Array R28CRow)')
    pair=once(pair,'  let wp:=WP[j]!\n','  let wp:=WP[j]!\n  let cx1:=CX[i]!\n  let cx2:=CX[i+1]!\n  let cw:=CW[j]!\n  let d1:=Yk (bx1>>>16)+Yk (bv>>>16)-lo1\n  let d2:=Yk (bx2>>>16)+Yk (bv>>>16)-lo2\n')
    a=pair.index('    MD2 X W b')
    b=pair.index('\n   else ',a)
    old=pair[a:b]
    fallback='\n'.join(' '+line for line in old.split('\n'))
    replacement='''    if hc:cx1.1.size=inW∧cx2.1.size=inW∧cw.1.size=inW∧cx1.2.2+cw.2.2<=61∧cx2.2.2+cw.2.2<=61∧d1.toNat<64∧d2.toNat<64 then
     R28CPair X W b inW outW relu i j inW.toUSize cx1.1 cx2.1 cw.1
      (by rw [hc.1];exact Nat.mod_le _ _) (by rw [hc.2.1];exact Nat.mod_le _ _) (by rw [hc.2.2.1];exact Nat.mod_le _ _)
      cx1.2.2 cx2.2.2 cw.2.2 cx1.2.1 cx2.2.1 cw.2.1 d1 d2 lo1 lo2 bw 0 0 0 0 0 out
    else
'''+fallback
    pair=pair[:a]+replacement+pair[b:]
    pair=once(pair,'  MVj X W b inW outW relu BX BV XP WP i (j+1) out','  R28CPj X W b inW outW relu BX BV XP WP CX CW i (j+1) out')
    outer=extract(source,'MVi')
    outer=once(outer,'def MVi ','def R28CPi ')
    outer=once(outer,'(XP WP:Array (Array Nat))','(XP WP:Array (Array Nat)) (CX CW:Array R28CRow)')
    outer=once(outer,'then MVi X W b inW outW rows relu BX BV XP WP (i+2) (MVj X W b inW outW relu BX BV XP WP i 0 out)',
               'then R28CPi X W b inW outW rows relu BX BV XP WP CX CW (i+2) (R28CPj X W b inW outW relu BX BV XP WP CX CW i 0 out)')
    top=extract(source,'YaVM')
    top=once(top,'def YaVM ','def R28CenteredLinear ')
    top=once(top,'  MVi X W b inW outW rows relu BX BV XP WP 0 (Θ (rows*outW) 0)',
             '  let CX:Array R28CRow:=Array.ofFn (n:=rows) (fun i=>R28CPrep XP[i.val]! BX[i.val]!)\n  let CW:Array R28CRow:=Array.ofFn (n:=outW) (fun j=>R28CPrep WP[j.val]! BV[j.val]!)\n  R28CPi X W b inW outW rows relu BX BV XP WP CX CW 0 (Θ (rows*outW) 0)')
    additions+='\n'+pair+outer+top
    gemm_dot=extract(source,'MaG')
    gemm_dot=once(gemm_dot,'def MaG ','def R28CMaG ')
    gemm_dot=once(gemm_dot,'(ap bp:Array Nat)','(ap bp:Array Nat) (ca cb:R28CRow)')
    original_call="  let r':=MD kژ ap bp (by rw [h.1];exact Ϥ _ _) (by rw [h.2.1];exact Ϥ _ _) (Yk (ba>>>16)+Yk (bc>>>16)-lo) lo ((loڇ:Int)-298) 0 0 0 0"
    replacement="""  let d:=Yk (ba>>>16)+Yk (bc>>>16)-lo
  let r':=if hc:ca.1.size=k∧cb.1.size=k∧ca.2.2+cb.2.2<=61∧d.toNat<64 then
    R28COne k.toUSize ca.1 cb.1 (by rw [hc.1];exact Nat.mod_le _ _) (by rw [hc.2.1];exact Nat.mod_le _ _)
     ca.2.2 cb.2.2 ca.2.1 cb.2.1 d lo 0 0 0 0
   else MD kژ ap bp (by rw [h.1];exact Ϥ _ _) (by rw [h.2.1];exact Ϥ _ _) d lo ((loڇ:Int)-298) 0 0 0 0"""
    gemm_dot=once(gemm_dot,original_call,replacement)
    gemm_top=extract(source,'Ya3M')
    gemm_top=once(gemm_top,'def Ya3M ','def R28CenteredGemm ')
    gemm_top=once(gemm_top,'   YT (batch*m) n λ r j=>MaG A B k n r (r/m*k) j BA[r]! bb BC[r/m*n+j]! hk AP[r]! BP[r/m*n+j]!',
        '   let CA:Array R28CRow:=Array.ofFn (n:=batch*m) (fun r=>R28CPrep AP[r.val]! BA[r.val]!)\n   let CB:Array R28CRow:=Array.ofFn (n:=batch*n) (fun j=>R28CPrep BP[j.val]! BC[j.val]!)\n   YT (batch*m) n λ r j=>R28CMaG A B k n r (r/m*k) j BA[r]! bb BC[r/m*n+j]! hk AP[r]! BP[r/m*n+j]! CA[r]! CB[r/m*n+j]!')
    additions+='\n'+gemm_dot+gemm_top
    correct_start=source.index('theorem correct:Obligation kernels')
    correct_end=source.index('end Submission',correct_start)
    source=source[:correct_start]+source[correct_end:]
    first=source.index('@[inline] def MxA ')
    end=source.index('lemma ZLj ',first)
    region=source[first:end]
    matches=list(DECL.finditer(region))
    entries=[]
    for i,match in enumerate(matches):
        body=region[match.start():matches[i+1].start() if i+1<len(matches) else len(region)]
        entries.append((match.group(1),match.group(2),body))
    proof_names={name for kind,name,body in entries if kind in ['lemma','theorem']}
    # Norm's mutation proofs later in the source share ZSb/ZQe utilities with
    # the prepared engine. Preserve their lexical transitive closure instead
    # of deleting that unrelated proof support along with obsolete roots.
    tokens=lambda text:set(re.findall(r"[\w.']+",text))
    used=tokens(source[:first]+source[end:]+''.join(body for kind,name,body in entries if kind not in ['lemma','theorem']))
    retain=used&proof_names
    while True:
        expanded=retain|set().union(*(tokens(body)&proof_names for kind,name,body in entries if name in retain))
        if expanded==retain:break
        retain=expanded
    kept=[];removed=[]
    for kind,name,body in entries:
        if kind in ['lemma','theorem'] and name not in retain:removed.append(name)
        else:kept.append(body)
    source=source[:first]+''.join(kept)+source[end:]
    source=once(source,'def kernels:Kernels where',additions+'\ndef kernels:Kernels where')
    source=once(source,'dense:=⟨YaVM,Ya3M⟩','dense:=⟨R28CenteredLinear,R28CenteredGemm⟩')
    result=source.encode('utf-8')
    assert len(result)<=256000,len(result)
    assert not re.search(r'(?m)^(theorem|lemma) correct\b',source)
    assert source.count('import ')==1 and source.startswith('import ContractExact\n')
    assert not (set(removed)&tokens(source)), "Deleted proof still textually referenced"
    return result,{'removed_old_proof_names':removed,'retained_cross_region_proof_support':sorted(retain),'new_fragment_bytes':len(additions.encode()),'original_runtime_definitions_retained':True}


def transform(raw,submission=36,variant='centered36-cost'):
    assert submission==36 and variant=='centered36-cost'
    return build(raw)[0]


def main():
    p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True);a=p.parse_args()
    raw=a.source.read_bytes();result,details=build(raw);a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'UNPROVED_COMPLETE_RUNTIME_COST_ONLY_NOT_ADOPTABLE',
             'base_submission':36,'base_sha256':hashlib.sha256(raw).hexdigest(),'candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),
             'recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'fragment_sha256':hashlib.sha256((HERE/'CenteredDotRuntime.leanfrag').read_bytes()).hexdigest(),**details,
             'mechanism':'Positive affine per-row cache + cached sum; carry-only paired dot. Three terminal power-of-two corrections then one scale shift; original YL/YD bias and zero fallback retained.',
             'fallback':'Every original runtime definition remains byte-identical; original signed MD2 or MD used whenever positive guards fail; original oddrow/smallK/native add/LayerNorm untouched. Both paired linear and scalar prepared GEMM now have positive alternatives.',
             'cost_included':'Existing metadata+preparation and extra positive caches/sums, all array lifetime/drop, new guards, paired loop, finish corrections, bias and fallback are all inside actual kernel.',
             'proof':'No Submission.correct exists for this source. Original prepared proof block removed solely for diagnostic byte budget. Algebra/finite model do not establish all12.',
             'next':'Only if full cost useful: integrate producer bounds, array getters, unsigned128 accumulation, terminal congruence and source-bound complete all12 within256000B. Do not submit/adopt now.',
             'publication':'Own runtime fragment/recipe/receipt only; full upstream/reconstruction private/ephemeral'}
    a.receipt.write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8');print(json.dumps({k:receipt[k]for k in ['candidate_sha256','candidate_bytes','new_fragment_bytes','state']}))


if __name__=='__main__':main()
