from pathlib import Path
import json
from datetime import datetime,timezone
H=Path(__file__).parent
text='''# FP64 strict-cell mathematical audit

Status: PAPER_CHECKED, not Lean acceptance. Audit of the exact runtime field expressions preserved in sources-v1/ActualCheckerContractOnly.lean; source SHA is in CI-REQUEST.json. No benchmark conclusion.

Let E be the accepted binary32 exponent (1 through 254), F its 23-bit fraction, and U = 2^(E-150). For the positive magnitude Q=(2^23+F)U, the runtime raw64 midpoint words decode to:

| Branch | Lower | Upper |
|---|---|---|
| F>0 | Q-U/2 | Q+U/2 |
| F=0, E>1 | Q-U/4 | Q+U/2 |
| F=0, E=1 | Q-U/2 | Q+U/2 |

The unsigned widening base word is (E+896)*2^52+F*2^29. Adding 2^28 gives the upper midpoint. Subtracting 2^28 gives the lower midpoint except at minimum-normal, where subtracting 2^29 is required. When F=0, the subtraction borrows one binary64 exponent and the resulting half-binade scale changes the decrement from U/2 to U/4. The minimum-normal special decrement restores U/2 because the previous binary32 is subnormal. Both midpoint words are positive, finite binary64 and nonzero. Applying the sign bit negates the real value and reverses the endpoints for negative Q.

The raw64 XOR key is strictly monotone on finite real values except the -0,+0 pair. Each accepted comparison has a nonzero midpoint at one end, so that unique tie cannot invalidate the strict comparison. This is why an unqualified theorem key(x)<key(y) implies value(x)<value(y) would be false, but the current endpoint theorem has the necessary derived nonzero premise.

For finite representable midpoint M, roundAt64(M)=M. Monotonicity gives M<roundAt64(x) implies M<x and roundAt64(x)<M implies x<M. Applying these to x=s-R and x=s+R and combining |s-S|<=R gives lower<S<upper. Neither rounded native endpoint is asserted to lie outward of S.

Two tempting shortcuts are invalid:

1. Error plus RNE endpoint evaluation does not imply outward enclosure. R26's exact counterexample is preserved separately; current source uses strict pullback instead.
2. For Q=maxFinite32, upper=Q+2^103. A target strictly between Q and upper still rounds to Q while its magnitude is greater than maxFinite32. Therefore Model.isFinite_roundDyadic_of_abs_toReal_le_posMaxFinite cannot alone close the full checker result; it would silently exclude a supported portion of the top cell. The explicit NativeBinary32 cell rounder route preserves that case.

Producer connection required after helper acceptance: actual prepare validity and getter equality; exact native64 products of original binary32 inputs; exact Tail order; SUM3 bound with k=H-250, H<=506 and L<=30; actual radius exponent H+2L-303; native RNE endpoints; official indexed raw sum=dsum*2^-298; nonzero exact sum from a normal strict cell; native32 final rounding=official finishWord; original all12 integration. None is discharged by a helper-only gate or old normal/zero widening result.
'''
(H/'CELL-AUDIT.md').write_text(text,encoding='utf-8',newline='\n')
p=H/'status.json';d=json.loads(p.read_bytes());d.update(updated_at_utc=datetime.now(timezone.utc).isoformat(),accepted=True,active_work='Await first exact helper compile; paper audit closed midpoint arithmetic and max-finite shortcut exclusion; independent numerical small modules prepared, not queued.',verification='15 exact sources original intake/policy PASS; Lean NOT_RUN; CELL-AUDIT paper only',processed_inbox=['父R 19:51方向更新']);p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print('CELL-AUDIT.md and status.json updated')
