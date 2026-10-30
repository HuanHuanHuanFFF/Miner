from pathlib import Path
import json
from datetime import datetime,timezone
H=Path(__file__).parent
(H/'INTEGRATION-BOUNDARY.md').write_text('''# Exact runtime integration boundary

Inspected R26 fp-word-conv6 source ad9bde3e9e8490df15f3d8d15c08805f85d4451e0a5f2d20977632c0b4b22540, lines1111-1360. This is a historical runtime audit, not a correctness or current-champion result.

The prepared numerical theorem must instantiate `R24PortableF64.prepare raw`. A user-constructed `Prepared` with `valid=true` could contain unrelated cached Float values, so `valid` alone is never a sufficient invariant for arbitrary Prepared records. The original R26 linear/gemm/conv/depthwise construction does use `R26WordFallback.prepare`, whose fp field is definitionally the actual prepare. Array lookup proofs must retain this constructor origin and show index validity; the local Inhabited empty record is a fallback value, not a semantic prepared cache.

For an accepted attempt, derive all shape and validity conditions from actual `attemptPrepared != 0` via AttemptGuards, then rewrite prepare.raw=raw. Do not assume the guessed word was a correctly rounded native conversion: `proposal` is deliberately midpoint-up, and strict checker acceptance must prove the result independently of proposal accuracy.

The final scalar composition has two branches. Accepted FP returns the official dotSpec by the completed producer/checker/rounder chain. Miss returns a separately proved fallback on the same original arrays. The R26 `exact` fallback has unproved 64/128-bit paths and cannot inherit retainedCorrect. A known-correct current-base dot or ExactRuntime.dotSpec can be instantiated if the word proof is unfinished; performance must then be measured for that exact alternative.

Full12 still needs actual cached tensor getters, bias as one extra exact product, zero output sizes, and equality of new kernels to specKernels. The existing retainedCorrect root is about retainedKernels only. Helper compilation, a conditional strict-cell root, or finite checksum agreement cannot discharge this record equality.

The FP module can be attached to a stronger public predecessor only after source budget review: #27 is255647B and #12 is218232B before an owned patch. Appending the current full FP proof closure exceeds the former cap. Dependency removal or source compression must preserve exact replay and axiom checking on the final256000B-limited Kernel.
''',encoding='utf-8',newline='\n')
p=H/'status.json';d=json.loads(p.read_bytes());d.update(updated_at_utc=datetime.now(timezone.utc).isoformat(),state='ACTIVE_WAITING_FIRST_COMPILE',actual_CI_occupancy={'owner':'Droot','run_id':40945451009,'created_at_utc':'2026-10-29T20:02:30Z','source_commit':'2da31f12bea8fce8540630bde77ce053931b8aa0','our_sources':['KeyCore exact4e1ed0b4','PrepareCore exact14034d10'],'feedback':'NOT_YET_AVAILABLE_LOCALLY'},active_work='Independent exact runtime cache-origin/fallback integration audit; waiting core actual goals before source repairs. No further long closure queued.');p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print('integration audit and current status written')
