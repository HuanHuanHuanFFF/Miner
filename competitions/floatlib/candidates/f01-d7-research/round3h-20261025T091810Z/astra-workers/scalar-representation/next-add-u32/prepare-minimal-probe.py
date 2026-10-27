"""Assemble a proof-only append to exact statement-PASS c972, without changing its runtime.
No access to current CI inputs/results; frozen worker source only. No Lean/CI.
"""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
parent=HERE.parent/'Kernel-native-repack.lean'
sha=lambda b:hashlib.sha256(b).hexdigest()
base=parent.read_bytes();assert sha(base)=='c972fd72694d4d7db4660d2dbcd640d766d013d58bd9c9a27a6c68d47010b7ac'
pieces=[HERE/'UInt32NativeRound-interface.lean',HERE/'LowNormalization-probe.lean']
out=HERE/'Probe-native-add-shape.lean'
data=base+b'\n'+b'\n'.join(p.read_bytes() for p in pieces)
assert len(data)<=256000,len(data)
out.write_bytes(data)
screen=json.loads((HERE/'screen.json').read_bytes());rows=[]
for r in screen['coverage']:
    groups={}
    for name,g in r['groups'].items():
        high=g['accepted']-g['zero']-g['small_cancellation']
        assert high>=0 and high>=g['old_software_domain']
        groups[name]={'samples':g['samples'],'original_accepted':g['accepted'],
          'high_only_accepted':high,'original_fraction':g['accepted_fraction'],
          'high_only_fraction':high/g['samples'],
          'lost_fraction':(g['zero']+g['small_cancellation'])/g['samples'],
          'old_software_domain_count':g['old_software_domain']}
    rows.append({'run':r['run'],'groups':groups})
(HERE/'high-only-coverage.json').write_text(json.dumps({'created_utc':datetime.now(timezone.utc).isoformat(),
 'source_screen_sha256':sha((HERE/'screen.json').read_bytes()),'state':'EXACT_REAGGREGATION_OF_EXISTING_COUNTS_NO_NEW_SAMPLING',
 'guard_change':'Keep initial normal/gap<=7 and full normal-output guard, additionally N>=2^23; low nonzero/zero all original ADD fallback',
 'mathematical_loss_scope':'Only opposite-sign gap0/1 can have N<2^23. Same sign N>=2^24; opposite gap>=2 has N>2^24.',
 'coverage':rows,'timing':'UNKNOWN; no subset cost assigned'},indent=2)+'\n',encoding='utf-8')
manifest={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'DEPENDENCY_CLOSED_SOURCE_PROBE_NOT_COMPILED',
 'parent':{'path':str(parent.relative_to(ROOT)),'sha256':sha(base),'bytes':len(base),'statement_pass_run':40182114389},
 'pieces':[{'path':p.name,'sha256':sha(p.read_bytes()),'bytes':p.stat().st_size} for p in pieces],
 'probe':{'path':out.name,'sha256':sha(data),'bytes':len(data)},
 'runtime_delta':'NONE: original four public entry definitions/proofs and all original bytes retained as exact prefix; appended new helper declarations only',
 'depends_on':['B2 R2W01c arbitrary UInt32 model theorem and raw/native model maps','fixed ContractTensor import provides NativeBinary32 field and roundDyadic interfaces','new uint32_bits_eq_roundDyadic and projection theorem precede low normalization in same concatenated probe'],
 'future_owner_check':['Statement compile under original gate/caps','Explicit replay/axiom audit of uint32_bits_eq_roundDyadic, native_round_low, uint32_native_low_fields, low_scaled_round_fields; original four specs do not reference the appended helpers'],
 'not_claimed':['Standalone ADD Kernel','All-input ADD spec','Timing','Current c972 performance','Formal acceptance of appended helpers']}
(HERE/'probe-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'probe':manifest['probe'],'pieces':manifest['pieces'],'coverage':[{'run':r['run'],
 'fractions':{k:(v['original_fraction'],v['high_only_fraction']) for k,v in r['groups'].items()}} for r in rows]},indent=2))
