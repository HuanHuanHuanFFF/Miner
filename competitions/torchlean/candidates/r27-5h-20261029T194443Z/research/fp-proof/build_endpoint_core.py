from pathlib import Path
import json,hashlib
from datetime import datetime,timezone
H=Path(__file__).parent;ROOT=Path.cwd()
full=(H/'boundary-v1/ActualBoundaryContractOnly.lean').read_text(encoding='utf-8')
start=full.index('namespace Submission.R24PortableF64\n');end=full.index('end Submission.R24PortableF64',start)+len('end Submission.R24PortableF64')
runtime=full[start:end]
new='''
namespace Submission.R27EndpointCore
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
open Submission.R25OrderKey

theorem actual_finite_guards (s r : Float) (q : UInt32)
    (hacc : Submission.R24PortableF64.certify s r s.toBits q = true) :
    finite64 s.toBits = true ∧ finite64 (s - r).toBits = true ∧
      finite64 (s + r).toBits = true := by
  unfold Submission.R24PortableF64.certify at hacc
  split at hacc
  · simp at hacc
  next he =>
    dsimp only at hacc
    split at hacc
    · simp at hacc
    next hf =>
      have hh : Submission.R24PortableF64.finite64 s.toBits = true ∧
          Submission.R24PortableF64.finite64 (s - r).toBits = true ∧
          Submission.R24PortableF64.finite64 (s + r).toBits = true := by
        cases hs : Submission.R24PortableF64.finite64 s.toBits <;>
          cases hl : Submission.R24PortableF64.finite64 (s - r).toBits <;>
          cases hu : Submission.R24PortableF64.finite64 (s + r).toBits <;> simp_all
      exact hh
'''
g=(H/'boundary-v1/GuardedEndpoints.lean.inc').read_text(encoding='utf-8-sig')
a=g.index('private theorem native_finite_eq');z=g.index('/-- Only actual finite radius')
g=g[a:z]
g=g.replace('  have hc : certify s r s.toBits q = true := by\n    simpa only [certify_eq_runtime] using hacc\n  obtain ⟨_, _, hsf, hlof, hhif, _, _⟩ := accepted_components s r s.toBits q hc','  obtain ⟨hsf, hlof, hhif⟩ := actual_finite_guards s r q hacc')
s=(H/'sources-v1/KeyCoreContractOnly.lean').read_text(encoding='utf-8')+'\n'+runtime+'\n'+new+'\n'+g+'\nend Submission.R27EndpointCore\n'
p=H/'boundary-v1/EndpointCoreContractOnly.lean';p.write_text(s,encoding='utf-8',newline='\n');b=p.read_bytes()
r=dict(at_utc=datetime.now(timezone.utc).isoformat(),path=p.relative_to(ROOT).as_posix(),sha256=hashlib.sha256(b).hexdigest(),bytes=len(b),helper_roots=['Submission.R27EndpointCore.actual_finite_guards','Submission.R27EndpointCore.accepted_endpoint_equations'],depends_on=['KeyCore exact4e1ed0b4 included'],scope='Isolates new guard-derived endpoint equations from still-uncompiled Real-strict and midpoint chain.',proof='NOT_RUN')
(H/'boundary-v1/endpoint-core-receipt.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
p=H/'CI-REQUEST.json';d=json.loads(p.read_bytes());d['independent_priority_probe']=dict(name='EndpointCoreContractOnly',**r);d['updated_at_utc']=datetime.now(timezone.utc).isoformat();p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(r,indent=2))
