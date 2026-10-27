"""Read-only source/patch/dependency audit. Does not compile or read CI19/D17."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib
import json
import re

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
R19=ROOT/'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z'
DRAFT=R19/'development-workers/astra-row-fusion/broad-draft'
PARENT=ROOT/'competitions/floatlib/candidates/f01-r19-dev-dual-temporal-a4-5/Kernel.lean'
BASE=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
RETAINED=R19/'development-column4-broad-retained.lean'
CORE=R19/'development-workers/astra-row-fusion/repair1/Kernel-core-repair1.lean'
FRAGMENT=CORE.parent/'Column4Temporal-repair1.lean.inc'
sha=lambda raw:hashlib.sha256(raw).hexdigest()
def save(name,value):(HERE/name).write_bytes((json.dumps(value,ensure_ascii=False,indent=2)+'\n').encode())
def span(raw,name):
    start=raw.index(('namespace '+name+'\n').encode());end=raw.index(('end '+name).encode(),start)+len('end '+name)
    return start,end
def ns(raw,name):a,b=span(raw,name);return raw[a:b]
def apply_patch(raw,patch):
    source=raw.decode().splitlines(True);lines=patch.decode().splitlines(True);out=[];pos=0;i=2
    while i<len(lines):
        m=re.match(r'@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@',lines[i]);assert m,lines[i]
        start=int(m[1])-1;assert start>=pos;out.extend(source[pos:start]);pos=start;i+=1;old=0;new=0
        while i<len(lines) and not lines[i].startswith('@@ '):
            line=lines[i];tag=line[0];text=line[1:]
            if tag in (' ','-'):assert source[pos]==text,(pos,source[pos],text);pos+=1;old+=1
            if tag in (' ','+'):out.append(text);new+=1
            assert tag in (' ','+','-');i+=1
        assert old==int(m[2] or 1) and new==int(m[4] or 1)
    out.extend(source[pos:]);return ''.join(out).encode()
def declarations(block):return set(re.findall(rb'^(?:@\[[^\n]*\]\s*)?(?:def|theorem|abbrev|structure)\s+(\w+)',block,re.M))

def main():
    a=(DRAFT/'Kernel-column4-broad.draft.lean').read_bytes();p=PARENT.read_bytes();b=BASE.read_bytes();r=RETAINED.read_bytes();c=CORE.read_bytes();f=FRAGMENT.read_bytes()
    assert (sha(a),len(a))==('a87f560a5944a778ca93dfb9a9d2dcd59895edc56b0ae7e498dbcf873fce8f19',255600)
    assert sha(p)=='c36bc2502904bf946d442de1a4646e09689f016643f09ab0b6788f9bdd375250'
    assert sha(b)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
    assert sha(c)=='118d8efc9e8c3d92189913c0aae3d66bca1394a677ec09957174c9d9e97eb1fc'
    assert (sha(r),len(r))==('7f1d4ec3f724526b83b17c28a6b392c7d4acb31e830fd141fae5ba5ea7429084',255655)
    assert apply_patch(p,(DRAFT/'from-parent.patch').read_bytes())==a
    assert apply_patch(a,(DRAFT/'inverse.patch').read_bytes())==p
    assert apply_patch(a,(R19/'development-column4-retained-forward.patch').read_bytes())==r
    assert apply_patch(r,(R19/'development-column4-retained-inverse.patch').read_bytes())==a
    # The imported core/proof body is exactly repair118d's fragment, apart from its label comment.
    core_a=ns(a,'Submission.R19Column4Temporal');core_r=ns(r,'Submission.R19Column4Temporal');core_f=ns(f,'Submission.R19Column4Temporal')
    assert core_a==core_r==core_f
    entry=(DRAFT/'Column4Entry-broad.draft.lean.inc').read_bytes();assert entry in a
    old_rt=b'else R19DualTemporal.dispatch b m n p A B';new_rt=b'else R15PackedB2.dispatch b m n p A B'
    old_pf=b'exact R19DualTemporal.dispatch_spec b m n p A B';new_pf=b'exact R15PackedB2.dispatch_spec b m n p A B'
    assert a.count(old_rt)==a.count(old_pf)==1 and r.count(new_rt)==r.count(new_pf)==1
    restored=ns(b,'Submission.R15PackedB2');stub=ns(a,'Submission.R15PackedB2');assert restored==ns(r,'Submission.R15PackedB2')
    assert b'def dispatch ' not in stub and b'theorem dispatch_spec ' not in stub
    predicted=a.replace(stub,restored,1);removed=[]
    for name in ('Submission.R19Temporal','Submission.R19DualTemporal'):
        start,end=span(predicted,name);cut=predicted.index(b'@[inline] def group (',start,end);closing=predicted.index(('end '+name).encode(),cut,end)
        cut_raw=predicted[cut:closing];removed.append({'namespace':name,'bytes':len(cut_raw),'sha256':sha(cut_raw),'declarations':sorted(x.decode() for x in declarations(cut_raw))})
        predicted=predicted[:cut]+predicted[closing:]
    predicted=predicted.replace(old_rt,new_rt).replace(old_pf,new_pf);assert predicted==r
    # Full retained fallback prelude, not a mathematically-correct but slower alias.
    end_b=span(b,'Submission.R15PackedB2')[1];end_r=span(r,'Submission.R15PackedB2')[1];assert end_b==end_r==225870 and b[:end_b]==r[:end_r]
    declared={name:declarations(ns(r,'Submission.'+name)) for name in ('R19Temporal','R19DualTemporal','R15PackedB2')}
    unresolved={}
    for name,defs in declared.items():
        refs=set(re.findall(rb'\b'+name.encode()+rb'\.(\w+)',r));missing=refs-defs
        assert not missing,(name,missing);unresolved[name]=[]
    roots=re.findall(rb'^#print axioms (\S+)',(DRAFT/'HelperAudit.lean.inc').read_bytes(),re.M);assert len(roots)==len(set(roots))==19
    col_decls=declarations(core_r)|declarations(entry)
    for root in roots:
        s=root.decode();leaf=root.split(b'.')[-1]
        if s.startswith('Submission.R19Column4Temporal.'):assert leaf in col_decls,s
        else:assert root in (b'Submission.add_spec',b'Submission.mul_spec',b'Submission.sum_spec',b'Submission.bmm_spec') and re.search(rb'^theorem '+leaf+rb'\b',r,re.M)
    # Exact public wrapper: only the dispatch/spec target changed versus c36.
    marker=b'namespace Submission\nopen FloatLib.Floats Competition\n\ndef bmm '
    pa=p[p.rindex(marker):];aa=a[a.rindex(marker):];rr=r[r.rindex(marker):];assert aa==rr
    assert aa.replace(b'R19Column4Temporal.dispatch (b := batch) (m := m) (n := n) (p := p) A B',b'R19DualTemporal.dispatch batch m n p A B').replace(
        b'R19Column4Temporal.dispatch_spec (b := batch) (m := m) (n := n) (p := p) A B',b'R19DualTemporal.dispatch_spec batch m n p A B')==pa
    assert b'  if 0<m \xe2\x88\xa7 1<n \xe2\x88\xa7 3\xe2\x89\xa4p \xe2\x88\xa7 4*((p+3)/4)=2*((p+1)/2) then core A B' in r
    assert b'UnderflowZero.small' in rr and b'UnderflowZero.zeros batch m p' in rr
    # Finite ordered-address checks buy wiring evidence only; they are not Lean acceptance.
    checked=0;ghost_examples=[]
    for batch in range(3):
      for m in range(1,5):
       for n in range(2,9):
        for width in list(range(3,17))+[23,27,43,60]:
         if 4*((width+3)//4)!=2*((width+1)//2):continue
         T=(n+3)//4;G=(width+3)//4
         for row in range(batch*m):
          bi=row//m;emitted=[]
          for group in range(G):
           q=bi*G+group;base=(q//G)*n*width+4*(q%G);assert base==bi*n*width+4*group
           for lane in range(min(4,width-4*group)):
            column=4*group+lane;chain=[]
            for t in range(T):
             qa=row*T+t;assert qa//T==row and qa%T==t
             for s in range(4):
              k=4*t+s
              if k<n:chain.append((row*n+k,base+lane+k*width))
            assert chain==[(row*n+k,bi*n*width+column+k*width)for k in range(n)]
            emitted.append((row,column,base+lane));checked+=1
          assert [x[1] for x in emitted]==list(range(width))
    for width in (3,4,7,8,12,23,27,43,60):ghost_examples.append({'p':width,'new_B16_lanes':4*((width+3)//4),'old_B8_lanes':2*((width+1)//2),'old_DC_real_lanes':width,
        'new_ghost_vs_DC':4*((width+3)//4)-width})
    inputs=[DRAFT/'Kernel-column4-broad.draft.lean',DRAFT/'receipt.json',DRAFT/'from-parent.patch',DRAFT/'inverse.patch',DRAFT/'HelperAudit.lean.inc',PARENT,BASE,CORE,FRAGMENT,RETAINED,
        R19/'development-column4-retained-build.json',R19/'development-column4-retained-forward.patch',R19/'development-column4-retained-inverse.patch']
    save('input-bindings.json',{'scope':'Source/patch/receipt bindings only; receipt experiment-status claims not used as acceptance. No CI19/D17/confirmation data read.',
        'files':[{'path':x.relative_to(ROOT).as_posix(),'sha256':sha(x.read_bytes()),'bytes':x.stat().st_size}for x in inputs]})
    report={'at_utc':datetime.now(timezone.utc).isoformat(),'draft':{'sha256':sha(a),'bytes':len(a),'exact_parent_patch_inverse':True,'fallback':'c36 Dual'},
        'retained_successor':{'sha256':sha(r),'bytes':len(r),'remaining_bytes':256000-len(r),'inverse_exact_to_a87f':True,'restored_B2_namespace_bytes':len(restored),'stub_bytes':len(stub),
            'restored_B2_namespace_sha256':sha(restored),'exact_B2_prelude_prefix_bytes':end_b,'removed_outer_shells':removed,'missing_known_namespace_refs':unresolved,
            'two_line_only_repair_sufficient':False,'two_line_only_failure':'a87f has no R15PackedB2.dispatch/spec; restored fullnamespace and dead-shell removal are necessary source changes, now independently reconstructed exactly.'},
        'core118d_body_byte_identical':True,'core_typed_status':'UNKNOWN_NOT_READ_OR_INFERRED_FROM_INFLIGHT_CI19',
        'nineteen_roots':[x.decode()for x in roots],'root_declaration_connections_present':True,'full_source_typed_replay_axioms_C':'NOT_RUN',
        'semantic_source_checks':{'outer_UnderflowZero_guard_and_zero_branch_exact':True,'other3_public_ops_protected_in_exact225870B_prelude':True,
            'true_guard':'m>0,n>1,p>=3 and4ceil(p/4)=2ceil(p/2),no upperp/m>=4 restriction','false_guard_successor':'exact retainedPackedB2.dispatch/spec, no newA4 preparation on miss',
            'A_address':'row=r; baseA=r*n; packedA packet=r*ceil(n/4)+t,field s correspondsA[r*n+4t+s]',
            'B_address':'bi=r/m; q=bi*ceil(p/4)+g; packetbase=bi*n*p+4g; lanej field atbase+j+(4t+s)*p',
            'output_order':'row ascending,then group ascending,then j=0..min(4,p-4g)-1; exactly rowmajor realp outputs, no pad writes/set/tiles',
            'NaN':'Each real lane invokes originalPacked10.finish with its ownFloat32 result and exactbaseA/baseB+j; fallback replayEarly uses originalrawA/B, not one shared fourlaneNaN decision',
            'empty_cases':'m0/n<=1/p<3 andpmod4=1or2 miss to retained; batch0 may hitguard but emptyPA/PB/output folds avoid invalid row/packet accesses',
            'finite_ordered_address_and_output_checks':checked,'finite_checks_not_Lean_proof':True},
        'cost_scope':{'old_Dual_overlap':'A4 already present only in oldDual true domain; combines twoB8 packets/twoF2 chains intoB16/F4, with actualnewcodegen stillUNKNOWN',
            'new_DC_and_wide_routes':'A4 plus B16 preparation/residency/destruction are new lifecycle work; cannot borrow existingA4 claim. Some oldprepared layouts may be replaced, actualnet changes require truecallerC.',
            'ceil_equality_limit':'Equal padded width is relativeB8 pair schedule only; DC previously computes realp lanes, so p=3mod4 adds one unusedlane (not emitted). Width equation is not no-extraMAC versusall originalroutes.',
            'ghost_lane_examples':ghost_examples,'old_scope_only':'Previously verifiedCI12 nonUnderflow shape coverage7.2887%/5.9742%whole is selection context, not removablecost/generalized gain.',
            'actual_closures_boxes_spills_cleanup_timing':'UNKNOWN_GENERATED_C_NOT_RUN'},
        'decision':'AFTER_ACTUAL_CORE_ACCEPTANCE_WORTH_ONE_EXACT_RETAINED_SUCCESSOR_FULL_SOURCE_STATEMENT_REPLAY19ROOTS_AND_ACTUAL_CALLER_C_NOT_FULL_D_YET',
        'reason':'No source wiring counterexample found; missingB2 fallback repair is real and the7f1d reconstruction closes its static dependencies within256000. New lowrow/wide lifecycles differ enough to justify one cost-premise/codegen check, not a gain prediction.',
        'minimum_remaining_obligations':'Exactsource typed wholemodule/VerifyFull replay+all19 roots+textpolicy, then true publicBMM→guard→packA/packB16→actualfourlane caller; verify no low/high helper constructors, dynamicapply, perFloat boxes, repeatedpreparation or hidden lifecycle exclusion.',
        'not_done':'No source edits, no Git/CI/Lean, no D17 or confirmation inputs/results read; no incompleteCI19 acceptance claim.'}
    save('review.json',report)
    print(json.dumps({'a87f_inverse':True,'7f1d_inverse':True,'source_bytes':len(r),'B2_prelude_exact':end_b,'missing_namespace_refs':unresolved,'roots':19,'address_checks':checked,'decision':report['decision']},indent=2))
if __name__=='__main__':main()
