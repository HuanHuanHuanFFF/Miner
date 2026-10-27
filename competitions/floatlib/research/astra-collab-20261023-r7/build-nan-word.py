from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
ROOT=Path(__file__).resolve().parents[4];HERE=Path(__file__).resolve().parent
base=ROOT/'competitions/floatlib/candidates/f01-r7-nan-replay-fullpath/Kernel.lean'
b=base.read_bytes();assert hashlib.sha256(b).hexdigest()=='9a2a05cd8e033d3cc079744ade77dd42464926d04ef5c9a8e7c050a1605ec854'
web=HERE/'web/R7-W01b/original-extracted/R7-W01b/R7W01bAppend.lean';wb=web.read_bytes()
receipt=json.loads((HERE/'web/R7-W01b/receipt.json').read_text())
expected=next(x['sha256'] for x in receipt['files'] if x['file']=='R7-W01b/R7W01bAppend.lean')
assert hashlib.sha256(wb).hexdigest()==expected
prefix=wb.decode().split('/- R7-W01b finite witnesses.')[0]
assert prefix.rstrip().endswith('end R7W01b')
prefix=re.sub(r'^#print.*\n','',prefix,flags=re.M)
prefix=re.sub(r'\bimport\b','dependency',prefix)
s=b.decode();marker='end R7NaNProof';assert s.count(marker)==1
s=s.replace(marker,marker+'\n\nsection R7WordQuietProof\n'+prefix+'\nend R7WordQuietProof\n')
a=s.index('namespace R7NaNReplay');z=s.index('end R7NaNReplay',a)
block=s[a:z].replace('R7W01.execQuietGuard','R7W01b.rawExecQuietGuard')
old='''  exact R7W01.exec_add_mul_absorb _ _ _
    (R7W01.quietGuard_nan _ hq) (R7W01.quietGuard_not_signaling _ hq)'''
new='''  obtain ⟨hn, hs⟩ := (R7W01b.rawExecQuietGuard_true_iff acc).mp hq
  exact R7W01.exec_add_mul_absorb _ _ _ hn hs'''
assert block.count(old)==1;block=block.replace(old,new)
s=s[:a]+block+s[z:]
out=s.encode();d=ROOT/'competitions/floatlib/candidates/f01-r7-nan-replay-word';d.mkdir(exist_ok=False)
(d/'Kernel.lean').write_bytes(out)
m=json.loads(base.with_name('manifest.json').read_text());m.update(candidate=d.name,candidate_sha256=hashlib.sha256(out).hexdigest(),candidate_bytes=len(out),parent=base.parent.name,parent_sha256=hashlib.sha256(b).hexdigest(),created_at_utc=datetime.now(timezone.utc).isoformat(),proof_status='NOT_RUN_INTEGRATED_SOURCE',mechanism='Replace each exact NaN replay-loop generic model guard with rawUInt32 mask0x7fc00000 equality, via the concrete all-input codec/classifier theorem. Same Nat early loop, tuned scalar prefix, NaN-only replay and both NativeFinal.dot/Packed10.finish hooks.',word_bridge_original_sha256=expected,proof_derivation='Use original W01b prefix through rawExecQuietGuard_true_iff without audit commands; no arithmetic/classification proof body edits. Full fold correctness is reconnected to raw guard premises.',expected_gain='UNKNOWN; static leaf has one UInt32 and/equality and no Model construction, but whole-call timing and caller generated C must decide actual gain. Full gate required.')
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
