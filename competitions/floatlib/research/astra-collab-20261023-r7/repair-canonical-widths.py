from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
ROOT=Path(__file__).resolve().parents[4];HERE=Path(__file__).resolve().parent
p=ROOT/'competitions/floatlib/candidates/f01-r7-canonical-bridge-probe-policy1/Kernel.lean'
b=p.read_bytes();assert hashlib.sha256(b).hexdigest()=='a4f26514082e3d35738d253207db9f3127ca16de20e55fc6ac54d075710297a9'
s=b.decode();assert s.count('-1#8')==1 and s.count('0#23')==1
mapping={'-1#8':'-1#(FloatFormat.binary32.toModel.exponentBits)','0#23':'0#(FloatFormat.binary32.toModel.mantissaBitsWithoutImplicit)'}
for a,z in mapping.items():s=s.replace(a,z)
out=s.encode();d=p.parent.with_name('f01-r7-canonical-bridge-probe-policy2');d.mkdir(exist_ok=False);(d/'Kernel.lean').write_bytes(out)
m=json.loads(p.with_name('manifest.json').read_text());m.update(candidate=d.name,candidate_sha256=hashlib.sha256(out).hexdigest(),candidate_bytes=len(out),parent=p.parent.name,parent_sha256=hashlib.sha256(b).hexdigest(),created_at_utc=datetime.now(timezone.utc).isoformat(),proof_status='NOT_RUN_EXACT_NAMESPACE_INTEGRATION',repair='W12 actually reproduced concrete8/23 rewrite matching failure. Preserve BitVec literal constructors and exact binary32 format field widths as compiled in W12. Only two width expressions changed; original a4 retained. No exact candidate compile or fullgate inherited.',web_source='web/R7-W12/original-extracted/R7-W12/evidence/W05-explicit-widths.diff')
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n')
block=HERE/'canonical-native-block.lean';old=block.read_bytes();(HERE/'canonical-native-block.policy1.lean').write_bytes(old)
bs=old.decode()
for a,z in mapping.items():bs=bs.replace(a,z)
block.write_text(bs)
status=HERE/'research-status.json';st=json.loads(status.read_text(encoding='utf-8'))
for key in ['ready_candidates']:
 for item in st[key]:
  if item['candidate']==p.parent.name:
   item.update(candidate=d.name,kernel=str((d/'Kernel.lean').relative_to(ROOT)).replace('\\','/'),sha256=m['candidate_sha256'],bytes=len(out),proof_status=m['proof_status'],requested_action='Replace olda4 with this exact field-width repair before any authorized compile. W12 fullsource accepted, this candidate integration NOT_RUN.')
st['canonical_bridge_probe_ready']=next(x for x in st['ready_candidates'] if x['candidate']==d.name)
st['urgent_proof_notice']='W12 actualweb compile found explicitnumeric8/23 width rewrite mismatch. Replace a4 with canonical-policy2 '+m['candidate_sha256']+'. Runtime unchanged; exactmappedcandidate NOT_RUN. Full W12 closure recovered separately; see checkpoint17 appendix.'
st['recovered_web'].append('R7-W12 ZIP47576c2e/report5049e749 CRC182manifestPASS. Complete6baa0a80 fixedLean269declarations/235theorems/62newcore; actualnative image/fullrawsumdotBMM/raw classifier. Exactcandidate NOT_RUN.')
st['active_web_jobs']=['R7-W12b publicdecoder branch andrawoperand single-step corollaries, started23:18UTC,15min bound','R7-W11 recovery only, original8.8MB ZIP downloads stalled; splitfiles requested, no new research']
st['active_browser_tabs'][0].update(job='R7-W12b',state='ACTIVE_15MIN_BOUND')
st['active_browser_tabs'][1].update(job='R7-W11-recovery',state='ACTIVE_FILE_RECOVERY_ONLY')
st['updated_at_utc']=datetime.now(timezone.utc).isoformat()
status.write_text(json.dumps(st,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(m,indent=2))
