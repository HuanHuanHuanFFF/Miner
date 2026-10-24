"""Repair only within_row after exact run926; preserve all runtime bytes."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json
HERE=Path(__file__).resolve().parent
CS=HERE.parent
PARENT=CS/'f01-r11-wide4-inline/Kernel.lean'
EXPECTED='43aaf31f905b71a976501f8cef170c9425d28c904b73079acc6e3f16a47dd8a5'
RESULT=CS/'f01-mul-log2-proof1/ci-runs/40042639860/download-bea9a0a07ca247008a2f2a6830d4e6f8/diagnostics/f01-d7-public-suite/public-suite'
sha=lambda b:hashlib.sha256(b).hexdigest()

def repair_body():
    lines=[]
    for i,b in enumerate(['base','base+n','base+2*n','base+3*n']):
        lines.append(f'  have h{i} : {b} < USize.size := by omega')
    lines += ["  have hproj := wordLoop_row (USize.ofNat n) (USize.ofNat base)",
              "    (USize.ofNat (base+n)) (USize.ofNat (base+2*n)) (USize.ofNat (base+3*n))",
              "    A B (USize.toNat_ofNat_of_lt' hn)"]
    for i in range(4):
        lines.append(f"    (by simp only [USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' h{i}]; omega)")
    lines += ['    hAS 0 '+' '.join(['zero32']*40)+' r',
              '  change projectRow (within n base A B hn hA hAS) r = _ at hproj',
              '  rw [hproj]', '  clear hproj', '  dsimp only',
              '  rw [Packed10Index.loop_eq, Packed10Index.runDot_eq]',
              '  rcases r with ⟨r,hr⟩',
              '  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega',
              '  rcases h with rfl|rfl|rfl|rfl <;>',
              '    simp only [projectRow, baseAt,',
              "      USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' h0,",
              "      USize.toNat_ofNat_of_lt' h1, USize.toNat_ofNat_of_lt' h2,",
              "      USize.toNat_ofNat_of_lt' h3, USize.toNat_zero, Nat.zero_mul, Nat.one_mul, Nat.add_zero]",'']
    return '\n'.join(lines)

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--write',action='store_true');a=ap.parse_args()
    raw=PARENT.read_bytes();assert sha(raw)==EXPECTED
    source=raw.decode();start=source.index('theorem within_row ',source.index('namespace Submission.R11WideRows4'))
    end=source.index('\ndef run (',start)
    block=source[start:end];body=block.index(':= by\n')+len(':= by\n')
    fixed=block[:body]+repair_body()
    text=source[:start]+fixed+source[end:];data=text.encode()
    assert text.replace(fixed,block,1).encode()==raw
    assert len(data)<=256000
    vd=RESULT/'f01-r11-wide4-inline-verdict.json'
    assert sha(vd.read_bytes())=='1dcd85ac2d0f33c3ddf9021b2c6cb1c7cebf2fd5b30847e96879e188db0ccc8d'
    verdict=json.loads(vd.read_text());assert verdict['passed'] is False and verdict['stage']=='statement'
    log=RESULT/'diagnostics/f01-r11-wide4-inline/replay.log'
    assert '6106:53: unsolved goals' in log.read_text(encoding='utf-8')
    spec=importlib.util.spec_from_file_location('p',CS/'f01-r11-crossrow-p2-pack12-proof2/build.py')
    p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p);p.static_check(text)
    rec={'candidate':HERE.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(data),'candidate_bytes':len(data),
         'parent':PARENT.parent.name,'parent_sha256':EXPECTED,'created_at_utc':datetime.now(timezone.utc).isoformat(),
         'repair':'Only theorem within_row: instantiate proven wordLoop_row explicitly before any Fin4 cases/projectRow unfolding, transport equality to within, then rewrite existing loop_eq/runDot_eq and normalize four bases.',
         'trigger_run':40042639860,'trigger_seed':926,'trigger_verdict_sha256':sha(vd.read_bytes()),
         'trigger_log_sha256':sha(log.read_bytes()),'runtime_bytes':'EXACTLY_UNCHANGED_OUTSIDE_ONE_THEOREM',
         'exact_inverse_parent':True,'proof_status':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN',
         'validation_mode':'full-gate','formal_submission':'NOT_SUBMITTED','static_policy':'PASS','size_margin':256000-len(data),
         'build_script_sha256':sha(Path(__file__).read_bytes())}
    if a.write:
        assert not (HERE/'Kernel.lean').exists()
        (HERE/'Kernel.lean').write_bytes(data)
        (HERE/'manifest.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
        (HERE/'proof-repair-review.json').write_text(json.dumps({'old_theorem':block,'new_theorem':fixed,'inverse_sha256':EXPECTED,'runtime_changed':False},ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    else:
        assert (HERE/'Kernel.lean').read_bytes()==data
        assert json.loads((HERE/'manifest.json').read_text(encoding='utf-8'))['candidate_sha256']==sha(data)
    print(json.dumps({k:rec[k] for k in ['candidate','candidate_sha256','candidate_bytes','size_margin','static_policy','proof_status']}))
if __name__=='__main__':main()
