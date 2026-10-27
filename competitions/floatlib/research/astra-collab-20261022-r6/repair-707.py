from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
ROOT=Path(__file__).resolve().parents[4]
def emit(name,s,reason):
    d=ROOT/'competitions/floatlib/candidates'/name
    b=(d/'Kernel.lean').read_bytes();dest=d.with_name(name.replace('-proof1','-proof2'));dest.mkdir(exist_ok=True)
    out=s.encode();(dest/'Kernel.lean').write_bytes(out)
    m=json.loads((d/'manifest.json').read_text());m.update(candidate=dest.name,candidate_sha256=hashlib.sha256(out).hexdigest(),candidate_bytes=len(out),parent=name,parent_sha256=hashlib.sha256(b).hexdigest(),created_at_utc=datetime.now(timezone.utc).isoformat(),proof_status='NOT_RUN',repair=reason)
    (dest/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
name='f01-r6-web-absorption26-proof1'
s=(ROOT/'competitions/floatlib/candidates'/name/'Kernel.lean').read_text()
old='  rw [← Configured.Backend.wordAdd_eq_spec]'
assert s.count(old)==2
s=s.replace(old,'  rw [← TunedAdd.add_spec x y, TunedAdd.add_eq_word]')
emit(name,s,'707 only two final bridges fail syntactic Configured.Spec/ExecFloat.Spec rewrite. Go through exact already accepted TunedAdd.add_spec and add_eq_word. Runtime and dyadic proofs unchanged.')
name='f01-r6-active-bias-proof1'
s=(ROOT/'competitions/floatlib/candidates'/name/'Kernel.lean').read_text()
for k in range(26,49):
    a=s.index(f'private theorem fixed_{k} ')
    z=s.index(f'private theorem fixed_{k+1} ',a) if k<48 else s.index('/-- The machine-word result',a)
    block=s[a:z]
    block=block.replace('    rw [UInt64.toNat_shiftRight, Nat.shiftRight_eq_div_pow]','    rw [UInt64.toNat_shiftRight, Nat.shiftRight_eq_div_pow]\n    norm_num')
    d=1<<k;bias=(1<<(k-1))-1;M=1<<64
    old='''    norm_num only [UInt64.toNat_ofNat] at *
    omega'''
    new=f'''    norm_num only [UInt64.toNat_ofNat] at *
    have hdiv : p.toNat / {d} ≤ p.toNat := Nat.div_le_self _ _
    have hpar : p.toNat / {d} % 2 < 2 := Nat.mod_lt _ (by decide)
    have hadd1 : p.toNat + {bias} < {M} := by omega
    have hadd2 : p.toNat + {bias} + p.toNat / {d} % 2 < {M} := by omega
    have haddq : p.toNat / {d} + 1 < {M} := by omega
    simp only [Nat.mod_eq_of_lt hadd1, Nat.mod_eq_of_lt hadd2, Nat.mod_eq_of_lt haddq]
    omega'''
    assert block.count(old)==1,k
    block=block.replace(old,new)
    s=s[:a]+block+s[z:]
a=s.index('  generalize hn : k.toNat = n at hklo hkhi',s.index('theorem rseBias_eq_rse '))
z=s.index('\nend R6BiasBridge',a)
dispatch='  generalize hn : k.toNat = n at hklo hkhi\n  interval_cases n\n'
for k in range(26,49):
    dispatch+=f'''  · have hk : k = ({k} : UInt64) := by
      apply UInt64.toNat_inj.mp
      exact hn
    cases hk
    exact fixed_{k} p hp
'''
s=s[:a]+dispatch+s[z:]
old='  rw [UInt64.toNat_sub_of_le _ _ hsw]\n'
assert s.count(old)==1
s=s.replace(old,old+'  norm_num\n')
old='  unfold Submission.FastMul.rse\n  split <;> (try split) <;> (try split)'
assert s.count(old)==1
s=s.replace(old,'  unfold Submission.FastMul.rse\n  dsimp only\n  split <;> (try split) <;> (try split)')
emit(name,s,'707 actual failures: normalize closed shift/149 constants; explicitly discharge both modulo2^64 addition bounds and quotient increment bound before omega; replace recursively rewriting dispatcher with23 separate equality cases; dsimp let-bound rse before split. Only proofs change, runtime remains frozen.')
