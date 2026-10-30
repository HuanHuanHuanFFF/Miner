"""One independent critical static review of C's selected exact graft.

No alternate queue, no whole upstream source written, no acceptance inference.
"""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json
HERE=Path(__file__).resolve().parent;BASE=HERE.parents[1];C=BASE/'research/board-frontier'
def sha(x):return hashlib.sha256(x).hexdigest()
def load(path,name):
 s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
pins={'build_gemm27_on_public23.py':'a920b7ab2545ad4e7eb4f009b29c5a78da2ae0fa9f41415c9546e0f679049736',
 'build_gemm27_on_public23_v2.py':'01b5405cfb0410396902d7f54c95b48a18789c2d696e31207f09fdee9f8b7c23',
 'compact_public23.py':'4c3dd79284f6701d3b128687f9f973f47d9236f8d9db502d398e2eb4d131e129'}
for n,h in pins.items():assert sha((C/n).read_bytes())==h
a=(BASE/'competition-state/source-private/submission23-Kernel.lean').read_bytes()
b=(BASE/'competition-state/source-private/submission27-Kernel.lean').read_bytes()
result=load(C/'build_gemm27_on_public23_v2.py','r27_selected_gemm_critical').transform(a,23,'gemm27-all-positive-k',donor_raw=b)
assert sha(result)=='6fe5feb6cf0b919a9700f5f05264b1e98e24d7ee74b9d2853c1e55be866d4ada' and len(result)==252719
s=result.decode()
assert s.count('theorem correct:Obligation kernels:=')==1
assert s.count('dense:=⟨YaV,Ya3Q⟩')==1
assert s.count('if k<1||!(A.all finiteWord&&B.all finiteWord) then gemmWith Yn batch m k n A B else')==1
assert s.count('· simpa only[gemmSpec,Zi]')==1
out={'at_utc':datetime.now(timezone.utc).isoformat(),'reply_to':'C-GEMM-ACCEPTED-NO-DUPLICATE.json',
 'candidate_sha256':sha(result),'candidate_bytes':len(result),'state':'INDEPENDENT_STATIC_REVIEW_NO_ACTIONABLE_FINDING_OR_GATE_CLAIM',
 'checks':[
  'Reconstructed selected6fe5feb6 exactly from pinned23/27 and3exact owned recipes; no mutable or hidden source needed',
  'All original runtime retained except final gemm binding; actualall12 correct remains linked to newZc0Q',
  'Only aliasdifferenceCQ resolves to Nat.pos_of_mul_pos_right; Cw already sameNat.mod_mul_right_div_self alias. Own independent audit reproduced sharedYo/Yq/Zy/Z5/Zi/ZbZ equality and ZcC statement equality',
  'Finite allpositivek branch meets originalGsn solek>0 premise; k0/nonfinite retains gemmWithYn. No genericgemmSpec runtime fallback',
  'GEMM-to-linear uses falseReLU, transposedB and -0bias. ExistingfiniteGsn preserves zero sign for nonempty dot; emptyk falls through',
  'Xg/Fw handle extraction/defaultpadding and finite default0; donor proof establishes allshape behavior, but this exact use still requires original gate',
  'Original source23 strongerYaV correctness interface is reused rather than donor27 YaV implementation proof'],
 'difference_from_own_drafts':{'bbd75849':'Unselected threshold20; would lose typical/boundary fast coverage, do notqueue',
 '345ffefe':'Independentk=0 version matches selectedallpositive condition semantically, but uses kernels0 projectionfallback and43extraformatbytes; do notqueue'},
 'remaining_validation':'Fresh fixed original all12 gate and complete Mixer native experiment; current36reportchain onlyINFERRED, no directcurrent source',
 'runtime_risks':['Transpose/slice/rowcache preparation included','Source23 genericaddRelu versus source27 nativeYbf gap included','Positive smallk YaV preparation/dispatch cost unmeasured'],
 'next':'No duplicate source or broad proof work; wait actualcost8 / selected9 compiler goals. Widen review only on changedsource/newevidence/unresolvedrisk',
 'scope':'Bounded independentstaticreview; exact source not Lean compiled by this role. No empirical performance or formal acceptance claim'}
(HERE/'selected-gemm-c9-critical-review.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:out[k] for k in ['at_utc','candidate_sha256','candidate_bytes','state','next']}))
