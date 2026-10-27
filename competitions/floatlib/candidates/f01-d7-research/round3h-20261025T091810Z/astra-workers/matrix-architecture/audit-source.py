from pathlib import Path
import re,json,hashlib,time
from datetime import datetime,timezone
here=Path(__file__).resolve().parent
root=next(p for p in here.parents if (p/'competitions/floatlib/pins.json').is_file())
start=time.monotonic()
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
manifest=json.loads((here/'candidate-manifest.json').read_text())
base=(root/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
candidate=(here/'Kernel-a4b2.lean').read_bytes()
assert hashlib.sha256(base).hexdigest()==manifest['parent_sha256']
assert hashlib.sha256(candidate).hexdigest()==manifest['kernel_sha256']
core=(here/'A4B2-core.lean').read_text();entry=(here/'A4B2-entry.lean').read_text()
for name in ('A4B2-core.lean','A4B2-entry.lean'):
 assert sha(here/name)==manifest['fragments'][name]['sha256']
prefix=manifest['unchanged_baseline_prefix_bytes']
assert candidate[:prefix]==base[:prefix]
assert len(candidate)<=256000
assert candidate.count(b'import ContractTensor')==1
assert not re.search(r'\b(sorry|axiom|unsafe|implemented_by|extern)\b',core+'\n'+entry)
assert core.count('wordLoop count A B hn (k+1)')==1
loop=core[core.index('def wordLoop'):core.index('theorem wordLoop_row')]
assert loop.count('toFloat32')==0 and loop.count('uget k')==2
assert all(f'c{c}r{r}+a.r{r}*b.s{c}' in loop for c in range(2) for r in range(4))
assert 'let panel := packA' in core and 'Vector.ofFn fun g => runDot n panel' in core
assert 'A.toArray.map' not in core+entry
assert 'R15PackedB2.row batch m n p A B packedB acc' in entry
assert 'R15PackedB2.dispatch batch m n p A B' in entry
sources=[
 'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T043928Z/astra-workers/matrix-structure/C-audit-401680/Submission_R15PackedB2_loop.txt',
 'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T043928Z/astra-workers/matrix-structure/C-audit-401680/B2-loop-diagnostic.asm.txt',
 'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T043928Z/astra-workers/matrix-structure/R11CrossRows_wordLoop___redArg-prior-C.txt',
 'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T043928Z/astra-workers/matrix-structure/Panel4-reusable-bundle.lean',
 'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T043928Z/astra-workers/public-source-runtime/sources/lean-header.txt',
 'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T043928Z/astra-workers/public-source-runtime/sources/lean-object.txt',
 'competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/astra-final-technical-handoff-20261024T021146Z.md',
 'competitions/floatlib/candidates/f01-d7-research/round3h-20261024T112622Z/result-1324003-f01-r13-preparation-convert-vs-f01-d12-scalar-combined.json']
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),status='SOURCE_INVARIANT_CHECK_ONLY',
 candidate_sha256=sha(here/'Kernel-a4b2.lean'),bytes=len(candidate),
 invariants=['Exact622d prefix unchanged','Only final dispatcher/proof target replaced','Eight independent original-order recurrences','No conversion in new source k-loop','A panel outside column-group closure','Tail uses old global-raw-base row emitter','Old B2 fallback retained','No new import or trust keyword'],
 sources=[dict(path=p,sha256=sha(root/p)) for p in sources],
 local_models_timeout_seconds=5,elapsed_seconds=time.monotonic()-start,
 lean='NOT_RUN',new_generated_C='UNKNOWN',new_assembly='UNKNOWN',full_gate='NOT_RUN',performance='NOT_RUN')
(here/'source-audit.json').write_text(json.dumps(record,indent=2)+'\n')
print(json.dumps({k:record[k] for k in ('status','candidate_sha256','bytes','elapsed_seconds')}))
