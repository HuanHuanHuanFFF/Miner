"""Bounded repair-entry feasibility only; write reports, never a Kernel/candidate."""
from pathlib import Path
import hashlib,importlib.util,json

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
CANDIDATES=HERE.parents[1]
sha=lambda raw:hashlib.sha256(raw).hexdigest()


def load(path,name):
    spec=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m


def main():
    base=(CANDIDATES/'f01-d12-scalar-combined/Kernel.lean').read_bytes()
    assert sha(base)=='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
    text=base.decode();start=text.index('namespace R7SinglePassSum\n');stop=text.index('end R7SinglePassSum\n',start)
    sum_block=text[start:stop]
    old_call='(Submission.add (ExecFloat.Binary.ofFloat32 acc) q)'
    parser=load(CANDIDATES/'f01-r8-combined-result-guard/build.py','r12_repair_inventory')
    decl=parser.declarations(text);lines=text.splitlines(keepends=True);starts=sorted(v[0]for v in decl.values())
    runtime={}
    projected=text
    for name in ('Submission.R7SinglePassSum.natLoop','Submission.R7SinglePassSum.loop'):
        row=decl[name][0];end=next(x-1 for x in starts if x>row)
        chunk=''.join(lines[row-1:end]);assert chunk.count(old_call)==1
        edited=chunk.replace(old_call,'(ScalarNaN.add (ExecFloat.Binary.ofFloat32 acc) q)')
        assert projected.count(chunk)==1;projected=projected.replace(chunk,edited)
        runtime[name]={'line':row,'old_sha256':sha(chunk.encode()),'new_sha256':sha(edited.encode()),'runtime_call_substitutions':1}
    lemma='''theorem cold_add_eq (x y : Binary32) :
    ScalarNaN.add x y = Submission.add x y := by
  exact (ScalarNaN.add_spec x y).trans (Submission.add_spec x y).symm

'''
    anchor='/-- Preserve existing decoder decisions; classify Inf versus NaN only in its high cold branch. -/'
    assert projected.count(anchor)==1;projected=projected.replace(anchor,lemma+anchor)
    old_leaf='''        · rename_i hinf
          exact R7SumRepair.suffixLoop_eq x (k + 1) _
'''
    new_leaf='''        · rename_i hinf
          rw [cold_add_eq]
          exact R7SumRepair.suffixLoop_eq x (k + 1) _
'''
    assert projected.count(old_leaf)==1;projected=projected.replace(old_leaf,new_leaf)
    pdecl=parser.declarations(projected);assert set(pdecl)==set(decl)|{'Submission.R7SinglePassSum.cold_add_eq'}
    assert all(len(v)==1 for v in pdecl.values())
    signature=lambda source,row:'\n'.join(source.splitlines()[row-1:]).split(':=',1)[0]
    for name in ('Submission.add','Submission.add_spec','Submission.mul','Submission.mul_spec',
                 'Submission.sum','Submission.sum_spec','Submission.bmm','Submission.bmm_spec'):
        assert signature(text,decl[name][0])==signature(projected,pdecl[name][0]),name
    assert len(projected.encode())<=256000
    audit=json.loads((HERE/'scalar-007-audit.json').read_bytes());cells=audit['per_cell']
    current_total=sum(v['candidate_submission_ns']*v['work'] for v in cells.values())
    shares={n:v['candidate_submission_ns']*v['work']/current_total for n,v in cells.items()if n.endswith(':specials')}
    run=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40072436647'
    idx=json.loads((run/'original-artifact-hashes.json').read_bytes())
    plan_path=run/idx['directory']/'diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'
    plan_raw=plan_path.read_bytes();plan=json.loads(plan_raw)
    nonspecial=[c for c in plan['cases']if c['timed']and c['kernel']=='sum'and not c['name'].startswith('sum:specials:')]
    assert all(c['mag']!=2 and c['specRate']==0 for c in nonspecial)
    history_names=('round1h-20261023T110107Z/compiled-context-review.md','word-route-frontier-review.md','exceptional-composition-feasibility.md','scalar-nan-select-review.md')
    history={n:sha((HERE.parent/n).read_bytes())for n in history_names}
    report={'state':'BOUNDED_PREFLIGHT_NO_KERNEL_WRITTEN','parent':'f01-d12-scalar-combined','parent_sha256':sha(base),
        'selected_minimal_recipe':'SUM_FIRST_RAW_NAN_DIRECT_EXISTING_COLD_ADD',
        'reason':'This branch already proved q rawNaN. ScalarNaN.add has unconditional all-input exact spec, so bypassing Submission.add avoids its two input conversions/native add/self-result guard. No extra classifier is added to ordinary prefix; raw metadata priority stays in the existing selector.',
        'runtime_sites':runtime,'proof_draft_only':lemma,'proof_leaf_change':{'before':old_leaf,'after':new_leaf},
        'projected_bytes':len(projected.encode()),'projected_sha256':sha(projected.encode()),'headroom_bytes':256000-len(projected.encode()),
        'projection_is_not_a_candidate':True,'public_entry_types':'UNCHANGED_IN_PROJECTION','new_runtime_guards':0,
        'proof_boundary':'Local cold_add_eq derives immediately from the two existing full-input specs. Only natLoop_eq cold leaf needs rewriting; machine loop_eq compares the same changed call on both sides. Actual Lean/elaboration and original full gate remain NOT_RUN.',
        'semantics_cautions':['Do not directly return right q payload: acc may already be canonicalNaN after Inf cancellation. Existing signaling-first selector preserves exact left/right priority.',
            'Keep suffixLoop and its later raw sNaN scan; one cold repair per vector does not authorize another suffix early stop.'],
        'historical_status':'Prior compiled-context review explicitly identified this known-rawNaN duplicate native work. Checked current candidate manifests/Kernel hooks contain no direct ScalarNaN.add(ofFloat32 acc,q) runtime repair candidate. This is conditional reuse of established math, not a new NaN algorithm; unindexed-history exhaustiveness UNKNOWN.',
        'history_sha256':history,
        '007_accounting':{'observed_whole_gain_points_already_realized':audit['specials_total_gain_contribution']*100,
            'remaining_whole_cost_shares_after3ff4':shares,'all_specials_remaining_share':sum(shares.values()),
            'sum_full_cell_removal_upper_bound':shares['sum:specials'],'bmm_full_specials_cell_removal_upper_bound':shares['bmm:specials'],
            'scope':'007 cold3ff4 observed workload, not df5c timing. Entire-cell residual shares are loose upper bounds, not removable-stage costs. The9.7409points are already realized relative6c and cannot be claimed again.'},
        'current007_non_special_sum_generation':{'drawn_plan_sha256':sha(plan_raw),'timed_cases_checked':len(nonspecial),
            'all_specRate_zero_and_non_raw_mag':True,'consequence':'Known-rawNaN repair is confined to sum:specials in this sampled public plan; other timed sum cells have no rawNaN input generator.'},
        'BMM_options':{'direct_all_replay_cold_helpers':'PARK: NaN final endpoint does not make each replay prefix input nonfinite. ScalarNaN.mul None falls to FastMul and add None to ExecFloat; replacing all replay arithmetic sends finite prefix through software and can regress heavily.',
            'raw_first_None_native':'PARK_PENDING_CURRENT_PREFIX_COST: semantically composable via selected_add/mul on Some and original Submission operation on None. But every replay prefix step pays raw selection, invalid non-NaN cases pay it twice, and current exact hit/miss timings/counts are UNKNOWN. Old807 prefix counts are not current007/df5c evidence.',
            'early_stop':'UNCHANGED; current quiet absorption already stops replay. No newly claimed saved suffix work.'},
        'investment_decision':'Sum-only direct cold entry is the best justified minimal implementation seam if011 succeeds and Root authorizes one cheap extension. Its entire-cell opportunity is under0.61percent of007 postcold whole cost, with actual repair subset smaller. Do not treat it as a new3percent whole-gain route or divert frozen confirmation budget; BMM preclassification remains parked.',
        'falsification':['Actual combined original C must no longer route the knownrawNaN repair through native add/selfguard, while ordinary prefix decoder/loop remains intact.',
            'Exact source must pass pinned Lean4.34 specs/kernel/axiom/checksum gate; preserve canonical-left-qNaN/right-sNaN witnesses.',
            'Complete no-observer same-input comparison against exactdf5c must show net gain beyond control movement; if not, park without a grid.'],
        'actual_Lean':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN','Kernel_generation':'NOT_AUTHORIZED_NOT_DONE'}
    (HERE/'scalar-cold-repair-preflight.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'state':report['state'],'selected_recipe':report['selected_minimal_recipe'],'bytes':report['projected_bytes'],
        'headroom':report['headroom_bytes'],'sum_loose_upper_bound':shares['sum:specials'],'Kernel_written':False},indent=2))


if __name__=='__main__':
    main()
