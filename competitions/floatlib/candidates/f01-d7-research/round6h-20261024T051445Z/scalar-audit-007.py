"""007 cold-selector full-gate accounting, dependency audit and no-write composition preflight."""
from pathlib import Path
import hashlib,importlib.util,json,random,statistics

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
CANDIDATES=HERE.parents[1]
CN='f01-d12-scalar-cold-nan-select-proof2'
BN='f01-d11-bmm-combined-classifier'
sha=lambda raw:hashlib.sha256(raw).hexdigest()


def load(path,name):
    spec=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m


def native(raw):
    begin=raw.index(b'@[inline] def nativeMul (x y : Binary32)')
    end=raw.index(b'\n@[inline] def mul (x y : Binary32)',begin)
    return begin,end,raw[begin:end]


def namespace(raw,name):
    a=('namespace '+name+'\n').encode();z=('end '+name+'\n').encode()
    assert raw.count(a)==raw.count(z)==1
    i=raw.index(a);j=raw.index(z,i)+len(z);return raw[i:j]


def main():
    guard=load(HERE.parent/'adoption-guard.py','r12_007_guard')
    p=guard.load_run(ROOT,HERE.parent,40072436647,(CN,BN,'f01-r8-combined-result-guard'))
    assert not p['codegen_present']
    vs=p['verdicts'];assert all(v['passed'] and v['stage']=='score' and len(v['rounds'])==25 for v in vs.values())
    c,b=vs[CN],vs[BN]
    total=lambda v,k:sum(v['classes'][n][k+'_ns']*w for n,w in p['cell_work'].items())
    correction=total(b,'incumbent')/total(c,'incumbent');baseline_cost=total(b,'submission')
    cells={};contributions={}
    for name,w in p['cell_work'].items():
        cv,bv=c['classes'][name],b['classes'][name]
        cells[name]={'work':w,'baseline_submission_ns':bv['submission_ns'],'candidate_submission_ns':cv['submission_ns'],
            'baseline_reference_ns':bv['incumbent_ns'],'candidate_reference_ns':cv['incumbent_ns'],
            'raw_submission_ratio':cv['submission_ns']/bv['submission_ns'],
            'raw_reference_ratio':cv['incumbent_ns']/bv['incumbent_ns'],'normalized_ratio':cv['ratio']/bv['ratio']}
        contributions[name]=(bv['submission_ns']*w-cv['submission_ns']*w*correction)/baseline_cost
    op={}
    for name in ('add','mul','sum','bmm'):
        sums={n:{k:sum(v['classes'][cell][k+'_ns']*w for cell,w in p['cell_work'].items()if cell.startswith(name+':'))for k in ('submission','incumbent')}for n,v in vs.items()}
        op[name]={'normalized_ratio':(sums[CN]['submission']/sums[CN]['incumbent'])/(sums[BN]['submission']/sums[BN]['incumbent']),
                  'raw_submission_ratio':sums[CN]['submission']/sums[BN]['submission'],'raw_reference_ratio':sums[CN]['incumbent']/sums[BN]['incumbent']}
    values=[[s/i for i,s in vs[n]['rounds']]for n in (CN,BN)];rng=random.Random(90423)
    gains=sorted(1-statistics.median(values[0][rng.randrange(25)]for _ in range(25))/statistics.median(values[1][rng.randrange(25)]for _ in range(25)) for _ in range(2000))
    k=.05*1999;lo=int(k);p05=gains[lo]+(gains[lo+1]-gains[lo])*(k-lo)
    cold=(CANDIDATES/CN/'Kernel.lean').read_bytes();base=(CANDIDATES/BN/'Kernel.lean').read_bytes()
    assert sha(cold)=='3ff4eb8e3f9be968592a05f3d934b679705a3bbdeb655afb7596951611f36221'
    tail=b'@[inline] def mul (x y : Binary32) : Binary32 :=\n  let ex := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField x.raw.1'
    assert base.count(tail)==cold.count(tail)==1
    assert base[base.index(tail):]==cold[cold.index(tail):]
    parser=load(CANDIDATES/'f01-r8-combined-result-guard/build.py','r12_007_inventory')
    base_decl,cold_decl=parser.declarations(base.decode()),parser.declarations(cold.decode())
    dependencies={}
    for name in ('Submission.R7SinglePassSum.loop','Submission.R7SinglePassSum.natLoop','Submission.R7SinglePassSum.run',
                 'Submission.R7SumRepair.suffixLoop','Submission.R7NaNReplay.replayStep','Submission.R7NaNReplay.replayLoop',
                 'Submission.NativeFinal.dot','Submission.Packed10.finish','Submission.referenceBmm','Submission.sum','Submission.bmm'):
        if name in cold_decl:
            dependencies[name]={'candidate_line':cold_decl[name][0],'baseline_line':base_decl[name][0]}
    # Capacity/interface projection only: build no Kernel and mutate no candidate.
    convert=(CANDIDATES/'f01-d12-mul-existing-convert/Kernel.lean').read_bytes()
    assert sha(convert)=='59de0e17223abebdd802bba98347ad8a4a7d6e90bfdca5ffd94bed3ad7005ce4'
    bs,be,bnative=native(base);_,_,dnative=native(convert)
    cs,ce,cnative=native(cold)
    # Exact converter donor native block differs from cold only at its two cold leaves.
    transplanted=dnative.replace(b'else FastMul.mul x y',b'else ScalarNaN.mul x y').replace(
        b'exact FastMul.mul_spec x y',b'exact ScalarNaN.mul_spec x y')
    assert b'else ScalarNaN.mul x y' in transplanted and b'exact ScalarNaN.mul_spec x y' in transplanted
    projected=cold[:cs]+transplanted+cold[ce:]
    inverse=projected[:cs]+cnative+projected[cs+len(transplanted):];assert inverse==cold
    # Construct the same projection independently from59de with only cold-side
    # source blocks/leaves, not a new candidate or an unvalidated proof shortcut.
    alternate=convert.replace(namespace(convert,'TunedAdd'),b'')
    alternate=alternate.replace(b'  else TunedAdd.add x y\n',b'  else ScalarNaN.add x y\n').replace(
        '  · exact TunedAdd.add_spec x y\n'.encode(),'  · exact ScalarNaN.add_spec x y\n'.encode())
    ns,ne,old_native=native(alternate)
    patched=old_native.replace(b'else FastMul.mul x y',b'else ScalarNaN.mul x y').replace(
        b'exact FastMul.mul_spec x y',b'exact ScalarNaN.mul_spec x y')
    alternate=alternate[:ns]+patched+alternate[ne:]
    notice=b'/- Word NaN selection: fixed public binary32 fields and exact quieting/priority.\n   Newly integrated statement probe; NOT_RUN in the official compiler. -/\n'
    insertion=b'\n'+notice+namespace(cold,'DWordNaN')+b'\n'+namespace(cold,'ScalarNaN')+b'\n'
    alternate=alternate.replace(b'end R7Native\n',b'end R7Native\n'+insertion)
    assert alternate==projected and len(projected)<=256000
    projected_decl=parser.declarations(projected.decode());assert set(projected_decl)==set(cold_decl)
    preflight={'state':'IN_MEMORY_ONLY_NO_KERNEL_WRITTEN','cold_sha256':sha(cold),'convert_sha256':sha(convert),
        'projected_sha256':sha(projected),'projected_bytes':len(projected),'headroom_bytes':256000-len(projected),
        'two_independent_composition_orders_byte_identical':True,'inverse_converter_recovers_exact_cold':True,
        'namespace_declaration_inventory_unchanged':True,
        'interface_seam':'Reuse exact59de nativeMul positive converter/proof block but retain ScalarNaN.mul/ScalarNaN.mul_spec cold leaves. Do not blindly overwrite the whole nativeMul with59de and restore its old FastMul fallback.',
        'combined_acceptance':'NOT_RUN','combined_performance':'UNKNOWN_NOT_ADDITIVE','decision':'WAIT_009; no combined Kernel generated'}
    (HERE/'scalar-cold-convert-preflight.json').write_text(json.dumps(preflight,indent=2)+'\n',encoding='utf-8',newline='\n')
    report={'run':40072436647,'seed':p['seed'],'source_commit':p['evidence']['source_commit'],'evidence':p['evidence'],
        'kernel_hashes':p['kernel_hashes'],'all_three_original_full25':'PASS','observer_present':False,
        'relative_normalized_ratio':c['ratio']/b['ratio'],'gain_p05':p05,'per_operation':op,'per_cell':cells,
        'reference_ratio_range':[min(x['raw_reference_ratio']for x in cells.values()),max(x['raw_reference_ratio']for x in cells.values())],
        'global_reference_correction':correction,'headline_gain_contribution_by_cell':contributions,
        'specials_total_gain_contribution':sum(x for n,x in contributions.items()if n.endswith(':specials')),
        'contribution_definition':'Baseline weighted submission cost minus globally reference-corrected candidate weighted submission cost, divided by baseline weighted submission cost. Scores add to1-whole_ratio; this is observed accounting, not causal stage profiling.',
        'source_dependency_lines':dependencies,
        'entire_source_tail_from_public_mul_dispatcher_byte_identical_to6c':True,
        'sum_reachability':'Public sum→R7SinglePassSum.run→machine/nat loop. At first raw-NaN input only, call Submission.add(ofFloat32 native acc,q), then original R7SumRepair.suffixLoop uses R7W02.step. Cold scalar add can affect the repair transition; the suffix is not a repeated scalar-add saving. Ordinary prefix uses native arithmetic directly.',
        'bmm_reachability':'NativeFinal.dot or Packed10.finish reject a native-NaN endpoint→R7NaNReplay.replayEarly→replayLoop→replayStep which calls Submission.mul then Submission.add. The referenceBmm exceptional/fallback path also directly uses exported add/mul. Normal packed/native inner loops do not call new scalar helpers perMAC.',
        'actual_baseline_C_corroboration':'Exact6c original Submission C86af0ce5: R7SinglePassSum_loop_redArg C40508–40715 retains actual TunedAdd_add cold call40583 and suffix40584. The007 clean run has no captured newC/asm, so new codegen/layout/inlining/cycle shares remain UNKNOWN.',
        'drift_assessment':'Not consistent with a large uniform reference/submission frequency scaling: reference percell remains withinabout0.55percent; submission drops concentrate in special cells. CPU frequency counters were not measured, so system/layout/instruction-cache effects on unchanged paths remain UNKNOWN.',
        'unchanged_path_boundary':'All sum/BMM runtime definitions are source-byte-preserved by cold composition, but their cold callees changed and may be inlined. They are not behaviorally isolated performance controls. Non-special mul gains and remaining warm-cell movements cannot be assigned to NaN selection without actual new caller/profile evidence.',
        'conclusion':'sum/BMM aggregate gains have a concrete cold dependency and are concentrated in specials, not a uniform gain over unchanged ordinary loops. This supports the cold-route explanation but does not identify an exact causal gain fraction or establish independent confirmation.',
        'composition_preflight':preflight,'state_writes':'NONE; no candidate/model/dashboard/CI/Git mutation'}
    (HERE/'scalar-007-audit.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'relative':report['relative_normalized_ratio'],'p05':p05,'reference_ratio_range':report['reference_ratio_range'],
        'specials_whole_gain_contribution':report['specials_total_gain_contribution'],'combination':preflight},indent=2))


if __name__=='__main__':
    main()
