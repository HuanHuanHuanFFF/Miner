"""One unused CODEGEN_ONLY four-row/F10 machine loop. Active parent unchanged."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json
HERE=Path(__file__).resolve().parent
CS=HERE.parent
PARENT=CS/'f01-d10-bmm-direct-rows/Kernel.lean'
EXPECTED='a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78'
sha=lambda b:hashlib.sha256(b).hexdigest()
def generate():
    names=[f'c{j}r{i}' for j in range(10) for i in range(4)]
    lines=['/- CODEGEN_ONLY: unused machine-loop probe; original four entry points remain unchanged. -/',
           'namespace Submission.R11WideRows4','open FloatLib.Floats Competition','',
           '/-- Column-major: four independent rows per column, ten columns. -/','structure F40 where']
    lines += [f'  {name} : Float32' for name in names]
    lines += ['', 'def wordLoop {n : Nat} (count a0 a1 a2 a3 : USize)',
              '    (A : Array Float32) (B : Vector Packed10.F10 n)',
              '    (hn : count.toNat = n)']
    for i in range(4):lines.append(f'    (h{i} : a{i}.toNat + (count.toNat - 1) < A.size)')
    lines += ['    (hAS : A.size < USize.size) (k : USize)']
    for j in range(10):lines.append('    ('+' '.join(f'c{j}r{i}' for i in range(4))+' : Float32)')
    lines += ['    : F40 :=','  if hk : k < count then',
              '    have hkn : k.toNat < n := by',
              '      rw [← hn]',
              '      exact USize.lt_iff_toNat_lt.mp hk']
    for i in range(4):
        lines += [f'    have ha{i} := Packed10Index.boundA a{i}.toNat count.toNat k.toNat A.size h{i}',
                  '      (USize.lt_iff_toNat_lt.mp hk)',
                  f'    let x{i} := A.uget (a{i} + k)',
                  f'      (by rw [Packed10Index.addNat a{i} k (Nat.lt_trans ha{i} hAS)]; exact ha{i})']
    lines += ['    let v := B.toArray.uget k (by simpa only [B.size_toArray] using hkn)']
    lines += [f'    let b{j} := v.s{j}' for j in range(10)]
    lines += ['    wordLoop count a0 a1 a2 a3 A B hn h0 h1 h2 h3 hAS (k + 1)']
    for j in range(10):lines.append('      '+' '.join(f'(c{j}r{i} + x{i} * b{j})' for i in range(4)))
    lines += ['  else ⟨'+', '.join(names)+'⟩',
              'termination_by count.toNat - k.toNat',
              'decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)',
              '', 'end Submission.R11WideRows4','']
    return '\n'.join(lines)
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--write',action='store_true');args=ap.parse_args()
    raw=PARENT.read_bytes();assert sha(raw)==EXPECTED
    addition=generate().encode();data=raw+b'\n\n'+addition
    assert len(data)<=256000 and data[:len(raw)]==raw
    sp=importlib.util.spec_from_file_location('r11_policy',CS/'f01-r11-crossrow-p2-pack12-proof2/build.py')
    c=importlib.util.module_from_spec(sp);sp.loader.exec_module(c);c.static_check(data.decode())
    # The only new branch is inside an unreferenced function after the entire parent.
    assert raw.count(b'R11WideRows4')==0 and addition.count(b'def wordLoop')==1
    assert addition.count(b'A.uget')==4 and addition.count(b'B.toArray.uget')==1
    manifest={'candidate':HERE.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(data),'candidate_bytes':len(data),
              'created_at_utc':datetime.now(timezone.utc).isoformat(),'parent':PARENT.parent.name,'parent_sha256':EXPECTED,
              'experiment_type':'CODEGEN_ONLY_UNUSED_EXPORTED_MACHINE_LOOP',
              'mechanism':'4nativeArows x one existingF10Bpacket,40scalarFloat32accumulators,onePpacketreadperiteration. Column-major40fields reuse R11F8 four-row alignment; terminalF40constructoronly.',
              'layout_decision':'One layout, no grid. Column-major prefers10 groups of4 independentrows; row-major3vectorsperrow wouldneed12accumulators. ActualSLP/registerallocation UNKNOWN.',
              'active_four_specs_and_bmm':'Entirea066prefix byte-identical; probe nevercalled byactiveentries.',
              'probe_preconditions':'SameverifiedPacked10Index boundA/addNat/next_decreases pattern forfourbases. Allproofsareexplicittypedarguments,erasedatruntime; no actualBMMwiringclaimed.',
              'validation_mode':'full-gate','proof_status':'NOT_RUN_NEW_MACHINE_LOOP_TYPECHECK','full_gate':'NOT_RUN',
              'matrix_algorithm_acceptance':'NOT_APPLICABLE_PROBE_UNUSED','performance':'NOT_APPLICABLE_NEW_LOOP_UNUSED',
              'codegen':'NOT_RUN','formal_submission':'NOT_SUBMITTED',
              'capture_required':['R11WideRows4.wordLoop','R11WideRows4_wordLoop___redArg'],
              'falsifier':'InspectactualhotloopforSIMD,foreigncalls,perMACallocationorhotstackspill; entry40argstackloadsandterminalF40allocationarenothotspill. Badmachinecode parksbeforefulloutputproof.',
              'future_missing':'No40laneprojection-to-originaldot proof,rawNaNfinish,tailrowrouting,column-groupF40buffer/outputorder orwhole-entrymeasurement. Needallbeforeanynewalgorithmclaim.',
              'build_script_sha256':sha(Path(__file__).read_bytes()),'increment_sha256':sha(addition)}
    review={'manifest':manifest,'prefix_identity':True,'prefix_bytes':len(raw),'source_margin':256000-len(data),
            'new_names':['Submission.R11WideRows4.F40','Submission.R11WideRows4.wordLoop'],
            'input_reads_per_iteration':{'nativeA':4,'existing_F10_B':1},'scalar_MAC_chains':40,'loop_accumulator_record_allocations_source':0,
            'result_construction':'OneF40onlywhenk>=count','static_policy':'PASS','scope':'Source-levelshape only; compiler can spill/reorderloads. Probe gate performance would be old activea066, not thisloop.'}
    if args.write:
        assert not (HERE/'Kernel.lean').exists()
        (HERE/'Kernel.lean').write_bytes(data);(HERE/'increment.lean').write_bytes(addition)
        for n,x in [('manifest.json',manifest),('source-review.json',review)]:
            (HERE/n).write_text(json.dumps(x,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    else:
        assert (HERE/'Kernel.lean').read_bytes()==data
        assert json.loads((HERE/'manifest.json').read_text())['candidate_sha256']==sha(data)
    print(json.dumps({'candidate':HERE.name,'sha256':sha(data),'bytes':len(data),'increment_bytes':len(addition),
                      'prefix_unchanged':True,'static':'PASS','mode':'CODEGEN_ONLY','new_algorithm':'NOT_CONNECTED'}))
if __name__=='__main__':main()
