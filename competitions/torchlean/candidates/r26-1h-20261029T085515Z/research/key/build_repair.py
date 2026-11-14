from pathlib import Path
import hashlib,json,re,ast
from datetime import datetime,timezone
ROOT=Path('D:/CodingProject/Bitget')
HERE=ROOT/'competitions/torchlean/candidates/r26-1h-20261029T085515Z/research/key'
OLD=ROOT/'competitions/torchlean/candidates/r25-90m-20261029T064916Z/research/order-key'
s=(OLD/'v2/OrderKey.lean.inc').read_text(encoding='utf-8')
s=s.replace('''  simp only [finite64, bne_iff_ne, ← UInt64.toNat_inj]
  rw [expMask_nat]
  change exponent w * 4503599627370496 ≠ 9218868437227405312 ↔ _
  omega''','''  change (w &&& 0x7ff0000000000000 != 0x7ff0000000000000) = true ↔ _
  rw [bne_iff_ne]
  constructor
  · intro hn
    have hnNat : (w &&& 0x7ff0000000000000).toNat ≠ 9218868437227405312 := by
      intro heq
      apply hn
      apply UInt64.toNat_inj.mp
      exact heq
    rw [expMask_nat] at hnNat
    omega
  · intro hexp heq
    have hnNat := congrArg UInt64.toNat heq
    rw [expMask_nat] at hnNat
    change exponent w * 4503599627370496 = 9218868437227405312 at hnNat
    omega''')
s=s.replace('(m % 4503599627370496 : Real)', '((m % 4503599627370496 : Nat) : Real)')
core=s.split('noncomputable def magnitudeReal',1)[0]+'\nend Submission.R25OrderKey\n'
c=(OLD/'v2/ActualChecker.lean.inc').read_text(encoding='utf-8')
c=c.replace('Append after R25OrderKey; no import, new axiom, or arithmetic-policy change.', 'Append after R25OrderKey; arithmetic behavior is unchanged.')
c=c.replace('''        simpa only [Bool.not_eq_true, Bool.not_eq_false, Bool.and_eq_true] using hf''','''        cases hsum : finite64 sumWord <;>
          cases hlo : finite64 (sum - radius).toBits <;>
          cases hhi : finite64 (sum + radius).toBits <;> simp_all''')
c=c.replace('''    simpa only [Nat.mul_one] using (Nat.two_pow_add_eq_or_of_lt h 1).symm''','''    have hp : w.toNat < 2 ^ 63 := h
    simpa only [Nat.mul_one] using (Nat.two_pow_add_eq_or_of_lt hp 1).symm''')
outputs={'KeyCoreContractOnly.lean':'import ContractExact\n'+core,'RealStrictContractOnly.lean':'import ContractExact\n'+s,'ActualCheckerContractOnly.lean':'import ContractExact\n'+s+'\n'+c,'OrderKey.lean.inc':s,'ActualChecker.lean.inc':c}
for n,t in outputs.items(): (HERE/n).write_text(t,encoding='utf-8',newline='\n')
P=OLD.parents[1]/'development/contract-port/policy-source'
d={};exec(compile((P/'duplicates.py').read_text(encoding='utf-8'),'pinned_duplicates','exec'),d)
t=ast.parse((P/'sandbox.py').read_text(encoding='utf-8'))
names={'_MAX_BYTES','OPTIONS','ATTRIBUTES','BANNED','GLOBAL'}; funcs={'intake','policy','global_declarations','options'}
sel=[n for n in t.body if (isinstance(n,ast.Assign) and any(isinstance(x,ast.Name) and x.id in names for x in n.targets)) or (isinstance(n,ast.FunctionDef) and n.name in funcs)]
ns={'Path':Path,'Verdict':object,'re':re,'normalized':d['normalized']};exec(compile(ast.Module(body=sel,type_ignores=[]),'pinned_policy','exec'),ns)
rows=[]
for n in outputs:
 p=HERE/n; raw=p.read_bytes(); rows.append(dict(path=p.relative_to(ROOT).as_posix(),sha256=hashlib.sha256(raw).hexdigest(),bytes=len(raw),policy=ns['policy'](p,None) if n.endswith('.lean') else 'FRAGMENT',intake=ns['intake'](p,None) if n.endswith('.lean') else 'FRAGMENT'))
rec=dict(at_utc=datetime.now(timezone.utc).isoformat(),source_old_sha256=hashlib.sha256((OLD/'policy1/Kernel.lean').read_bytes()).hexdigest(),files=rows,proof_status='NOT_RUN',kernel='NOT_RUN',actual_goals='R25 retained verdict contains diagnostic headers only; no full Lean goals saved',diagnosis=['finite64 rewrite replaced with explicit congrArg/toNat bridge','Real remainder annotation was Real.mod; changed to Nat remainder explicitly cast to Real','Bool guard solved by finite case split','signed_magnitude power exponent supplied as explicit 63 via typed hypothesis'],local_Lean=False,tokens='UNKNOWN',cached_input_tokens='UNKNOWN')
(HERE/'repair-receipt.json').write_text(json.dumps(rec,indent=2)+'\n',encoding='utf-8')
print(json.dumps(rec,indent=2))
