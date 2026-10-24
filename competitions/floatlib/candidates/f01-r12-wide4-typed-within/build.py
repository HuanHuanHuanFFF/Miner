"""E5 exact parent -> one real typed-within entry; no Git/CI or R11 mutation."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json,re,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
CS=HERE.parent
PARENT=CS/'f01-r11-wide4-cross-combined/Kernel.lean'
EXPECTED='e5b279b326e404d210cf2fb254c11a1773f84d2ab39cc853b9172f428c69c2d7'
sha=lambda b:hashlib.sha256(b).hexdigest()

GENERIC='''@[inline] def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (buildTiles : (nativeA : Array Float32) → nativeA.size = A.toArray.size →
      Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch →
      Fin batch → Fin (m / 4) → Tiles p) : Array Binary32 :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  let packedB := Packed10.packB batch n p B
  Fin.foldl batch (writeBatch batch m n p A B lane40 nativeA packedB
    (buildTiles nativeA (by simp only [nativeA, Array.size_map]) packedB))
      (Array.mkEmpty (batch * m * p))
theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (buildTiles : (nativeA : Array Float32) → nativeA.size = A.toArray.size →
      Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch →
      Fin batch → Fin (m / 4) → Tiles p)
    (hproj : ∀ (b : Fin batch) (h : Fin (m / 4)), Projects batch m n p A B lane40 b (4 * h.val)
      (buildTiles (A.toArray.map ExecFloat.Binary.toFloat32) (by simp only [Array.size_map])
        (Packed10.packB batch n p B) b h)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch * m * p)
      (output batch m n p A B lane40 buildTiles) := by
  exact RowStream.foldl_inv batch
    (writeBatch batch m n p A B lane40 (A.toArray.map ExecFloat.Binary.toFloat32)
      (Packed10.packB batch n p B)
      (buildTiles (A.toArray.map ExecFloat.Binary.toFloat32) (by simp only [Array.size_map])
        (Packed10.packB batch n p B)))
    (fun b acc => RowStream.Prefix (RowStream.point batch m n p A B) (b * m * p) acc)
    (fun b acc hacc => writeBatch_prefix batch m n p A B lane40 _ hproj acc b hacc)
    (Array.mkEmpty (batch * m * p))
    ⟨by simp, by intro j hj; simp at hj⟩
'''

ACTUAL='''namespace Submission.R11WideActual
open FloatLib.Floats Competition
/-- Size and machine bounds are Prop inputs, not repeated dynamic tests.
One block base and one batch-B selection precede the column traversal. -/
@[inline] def buildTiles (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (hn0 : 0<n) (hn : n<USize.size) (hAS : A.toArray.size<USize.size)
    (nativeA : Array Float32) (hsize : nativeA.size=A.toArray.size)
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (b : Fin batch) (h : Fin (m / 4)) : R11WideLayout.Tiles p :=
  let base := (b.val*m+4*h.val)*n
  let batchB := packedB.get b
  have hblock : 4*h.val+4≤m := by have hh:=h.isLt; omega
  have hspan : base+3*n+(n-1)<nativeA.size := by
    rw [hsize]
    have hs := R11WideLayout.nativeA_span batch m n A b (4*h.val) hblock ⟨3,by decide⟩ hn0
    simpa only [base, Nat.add_mul, Array.size_map] using hs
  Vector.ofFn fun g => R11WideRows4.within n base nativeA (batchB.get g)
    hn hspan (by rw [hsize]; exact hAS)
theorem buildTiles_projects (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hn0 : 0<n) (hn : n<USize.size) (hAS : A.toArray.size<USize.size)
    (b : Fin batch) (h : Fin (m / 4)) :
    R11WideLayout.Projects batch m n p A B R11WideRows4.lane40 b (4*h.val)
      (buildTiles batch m n p A hn0 hn hAS
        (A.toArray.map ExecFloat.Binary.toFloat32) (by simp only [Array.size_map])
        (Packed10.packB batch n p B) b h) := by
  apply R11WideLayout.Projects_of_row_projection batch m n p A B
    R11WideRows4.projectRow R11WideRows4.lane40 R11WideRows4.lane40_eq
  intro g r
  simp only [buildTiles, Packed10.vector_get_ofFn, R11WideRows4.within_row, Nat.add_mul]
@[inline] def output (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hn0 : 0<n) (hn : n<USize.size) (hAS : A.toArray.size<USize.size) : Array Binary32 :=
  R11WideLayout.output batch m n p A B R11WideRows4.lane40
    (buildTiles batch m n p A hn0 hn hAS)
theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hn0 : 0<n) (hn : n<USize.size) (hAS : A.toArray.size<USize.size) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch*m*p)
      (output batch m n p A B hn0 hn hAS) := by
  exact R11WideLayout.output_prefix batch m n p A B R11WideRows4.lane40
    (buildTiles batch m n p A hn0 hn hAS) (buildTiles_projects batch m n p A B hn0 hn hAS)
def core (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hn0 : 0<n) (hn : n<USize.size) (hAS : A.toArray.size<USize.size) :
    Vector Binary32 (batch*m*p) :=
  ⟨output batch m n p A B hn0 hn hAS, (output_prefix batch m n p A B hn0 hn hAS).1⟩
theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hn0 : 0<n) (hn : n<USize.size) (hAS : A.toArray.size<USize.size) :
    core batch m n p A B hn0 hn hAS = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch*m*p) (output batch m n p A B hn0 hn hAS)
    (output_prefix batch m n p A B hn0 hn hAS)).trans
    (RowStream.points_eq_reference batch m n p A B)
end Submission.R11WideActual'''

def generate():
    raw=PARENT.read_bytes();assert sha(raw)==EXPECTED
    text=raw.decode();edits=[]
    def replace(old,new,label):
        nonlocal text
        assert text.count(old)==1,(label,text.count(old))
        edits.append({'name':label,'old':old,'new':new})
        text=text.replace(old,new,1)
    start=text.index('@[inline] def output (',text.index('namespace Submission.R11WideLayout'))
    end=text.index('end Submission.R11WideLayout',start)
    replace(text[start:end],GENERIC,'Prop_sized_generic_output_and_proof')
    start=text.index('namespace Submission.R11WideActual\n')
    end=text.index('end Submission.R11WideActual',start)+len('end Submission.R11WideActual')
    replace(text[start:end],ACTUAL,'concrete_within_producer_and_all_callers')
    old='''  if 4 ≤ m ∧ 4 < n ∧ 2 < p ∧ n < USize.size ∧ A.toArray.size < USize.size then
    R11WideActual.core batch m n p A B'''
    new='''  if h : 4 ≤ m ∧ 4 < n ∧ 2 < p ∧ n < USize.size ∧ A.toArray.size < USize.size then
    R11WideActual.core batch m n p A B (by have hh:=h.2.1; omega) h.2.2.2.1 h.2.2.2.2'''
    replace(old,new,'outer_existing_wide_guard_supplies_Prop_facts')
    # Only after the actual producer/proof no longer names them may these go.
    assert 'R11WideRows4.run' not in text
    start=text.index('def joinRows (');end=text.index('\ndef within (',start)
    replace(text[start:end]+'\n','','remove_closed_joinRows')
    start=text.index('def run (n base : Nat)',text.index('theorem within_row '))
    end=text.index('end Submission.R11WideRows4',start)
    old=text[start:end]
    assert old.count('\ntheorem run_row ')==1
    replace(old,'','remove_closed_run_and_run_row')
    inverse=text
    work=raw.decode();positions=[]
    for e in edits:
        i=work.index(e['old']);positions.append(i)
        work=work[:i]+e['new']+work[i+len(e['old']):]
    assert work==text
    for e,i in reversed(list(zip(edits,positions))):
        assert inverse[i:i+len(e['new'])]==e['new']
        inverse=inverse[:i]+e['old']+inverse[i+len(e['new']):]
    assert inverse.encode()==raw
    budget_spec=importlib.util.spec_from_file_location('budget_verify',CS/'f01-d7-research/source-budget.py')
    budget=importlib.util.module_from_spec(budget_spec);budget_spec.loader.exec_module(budget)
    old_comments=[raw[a:z] for a,z in budget.comment_spans(raw)]
    new_raw=text.encode();cursor=0
    for comment in old_comments:
        at=new_raw.find(comment,cursor);assert at>=0,'Original comment/notice lost'
        cursor=at+len(comment)
    original=raw.decode()
    for begin,endmark in [('def wordLoop {n : Nat}', 'end Submission.R11WideRows4'),
                          ('def within (n base : Nat)', 'theorem within_row '),
                          ('theorem within_row ', 'def run (n base : Nat)')]:
        a=original.index(begin,original.index('namespace Submission.R11WideRows4'))
        z=original.index(endmark,a)
        assert original[a:z].rstrip() in text
    outer=raw[raw.rfind(b'namespace Submission\nopen FloatLib.Floats Competition\n\n/-- Both short-circuiting scans'):]
    assert len(outer)==1039 and sha(outer)=='b135a8eef0606c7356dc12d5956115d3832aa5cddb5dc5e71e5030380c76062e'
    assert text.encode().endswith(outer)
    a=raw.decode().index('namespace Submission.R11CrossRows\n');z=raw.decode().index('end Submission.R11CrossRows',a)+len('end Submission.R11CrossRows')
    cross=raw.decode()[a:z];assert cross in text
    for marker in ['namespace Submission.DirectContinuous','namespace Submission.UnderflowZero']:
        a=raw.decode().index(marker);z=raw.decode().index('end '+marker[len('namespace '):],a)+len('end '+marker[len('namespace '):])
        assert raw.decode()[a:z] in text
    spec=importlib.util.spec_from_file_location('policy',CS/'f01-r11-crossrow-p2-pack12-proof2/build.py')
    policy=importlib.util.module_from_spec(spec);spec.loader.exec_module(policy);policy.static_check(text)
    # Plain source names after closing all new caller proofs; not an inherited
    # unused-chain assertion on an unmodified parent.
    assert 'def joinRows (' not in text and 'theorem run_row (n base' not in text
    assert len(text.encode())<=256000,len(text.encode())
    return text.encode(),edits,sha(outer),sha(cross.encode())

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--write',action='store_true');args=ap.parse_args()
    data,edits,outer,cross=generate()
    rec={'candidate':HERE.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(data),'candidate_bytes':len(data),
         'created_at_utc':datetime.now(timezone.utc).isoformat(),'parent':PARENT.parent.name,'parent_sha256':EXPECTED,
         'mechanism':'Existingwideguard supplies erased Prop count/size facts; generic producer carries nativeA.size=rawA.size. ConcretebuildTiles computesbase/batchB once, callswithin directly. Allactualcore/output/spec callers closed.',
         'closed_deletions':['R11WideRows4.joinRows','R11WideRows4.run','R11WideRows4.run_row'],
         'preserved':'outer1039, entireCross/DirectContinuous/Underflow namespaces, nativewordLoop arithmetic/within, rawfinish,tail,fallback,alloriginalnoticeblocks',
         'outer_underflow_sha256':outer,'cross_namespace_sha256':cross,'inverse_parent_exact':True,'static_policy':'PASS',
         'size_margin':256000-len(data),'proof_status':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN',
         'validation_mode':'full-gate','formal_submission':'NOT_SUBMITTED','build_script_sha256':sha(Path(__file__).read_bytes()),
         'falsifier':'Originalstatement/full; sameobjectactualcallerC must show per-g run/checks gone, base andbatchB outsideg, no duplicatepreparation orcallbackboxing; thencompletepairedcost vsE5/6c/41. No speedforecast.'}
    if args.write:
        assert not (HERE/'Kernel.lean').exists()
        (HERE/'Kernel.lean').write_bytes(data)
        (HERE/'manifest.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
        (HERE/'exact-inverse.json').write_text(json.dumps({'parent_sha256':EXPECTED,'edits':edits,'inverse_exact':True},ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    elif (HERE/'Kernel.lean').exists():
        assert (HERE/'Kernel.lean').read_bytes()==data
        assert json.loads((HERE/'manifest.json').read_text(encoding='utf-8'))['candidate_sha256']==sha(data)
    print(json.dumps({k:rec[k] for k in ['candidate','candidate_sha256','candidate_bytes','size_margin','static_policy','proof_status']}))
if __name__=='__main__':main()
