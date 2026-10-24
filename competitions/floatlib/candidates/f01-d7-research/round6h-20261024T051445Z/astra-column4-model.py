"""Finite exact-word transcription for the frozen narrow4 row/output flow."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
import random
import sys
sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
CS = HERE.parent.parent
EXPECTED = 'da09fb59fa456b498af6bde48d54adcd37f85c4ba7df272163b184a2b83038c4'
sha = lambda raw: hashlib.sha256(raw).hexdigest()
sp = importlib.util.spec_from_file_location('column4_word_oracle', CS/'f01-r11-crossrow-p2-pack12/model-check.py')
m = importlib.util.module_from_spec(sp)
sp.loader.exec_module(m)
o = m.o


def narrow(batch, rows, n, p, A, B, counts):
    assert p in (3, 4)
    native = [o.canon(w) for w in A]
    pb = [[[o.canon(B[(b*n+k)*p+j]) if j < p else 0 for j in range(4)]
           for k in range(n)] for b in range(batch)]
    out = []
    for r in range(batch*rows):
        b = r//rows
        result = [0]*4
        for k in range(n):
            av = native[r*n+k]
            result = [o.native_model(o.add, result[j], o.native_model(o.mul, av, pb[b][k][j]))
                      for j in range(4)]
        counts['row_packets'] += 1
        counts['ignored_padding_NaNs'] += int(p == 3 and o.nan(result[3]))
        for j in range(p):
            value = result[j]
            if o.nan(value):
                value = o.dot(A[r*n:(r+1)*n], [B[(b*n+k)*p+j] for k in range(n)])
                counts['raw_replays'] += 1
            out.append(value)
    return out


def reference(batch, rows, n, p, A, B):
    return [o.dot(A[(b*rows+r)*n:(b*rows+r+1)*n], [B[(b*n+k)*p+j] for k in range(n)])
            for b in range(batch) for r in range(rows) for j in range(p)]


def main():
    assert sha((CS/'f01-r12-column4-narrow/Kernel.lean').read_bytes()) == EXPECTED
    rng = random.Random(202610241234)
    counts = {'matrices': 0, 'outputs': 0, 'row_packets': 0, 'ignored_padding_NaNs': 0, 'raw_replays': 0}
    trace = hashlib.sha256()
    for batch in [0, 1, 2, 5]:
      for rows in [0, 1, 2, 4, 7, 11]:
       for n in [0, 1, 4, 5, 7, 16]:
        for p in [3, 4]:
            mode = counts['matrices'] % 3
            def word():
                if mode == 0:
                    return rng.choice(m.EDGE)
                if mode == 1:
                    return rng.getrandbits(32)
                return rng.choice([0, 0x80000000, 1, 0x800000, 0x3f800000, 0xbf800000])
            A = [word() for _ in range(batch*rows*n)]
            B = [word() for _ in range(batch*n*p)]
            actual = narrow(batch, rows, n, p, A, B, counts)
            wanted = reference(batch, rows, n, p, A, B)
            assert actual == wanted, (batch, rows, n, p)
            counts['matrices'] += 1
            counts['outputs'] += len(wanted)
            for w in wanted:
                trace.update(w.to_bytes(4, 'little'))
    # n>4,p3 actual dispatch slice: an invalid padded lane may be NaN while
    # all three valid lanes are Infinity; no cross-lane endpoint classifier.
    A = [0x7f800000]+[0]*4
    B = [0x3f800000]*3+[0]*12
    edge = narrow(1, 1, 5, 3, A, B, counts)
    assert edge == [0x7f800000]*3
    rec = {'at_utc': datetime.now(timezone.utc).isoformat(), 'candidate_sha256': EXPECTED,
        'status': 'PASS_FINITE_WORD_TRANSCRIPTION_ONLY', 'seed': 202610241234,
        'counts': counts, 'trace_sha256': trace.hexdigest(), 'oracle_sha256': m.EXPECTED,
        'script_sha256': sha(Path(__file__).read_bytes()),
        'padding_boundary': {'shape': [1, 1, 5, 3], 'valid_outputs': [hex(x) for x in edge],
                            'unused_fourth_native_lane': 'NaN, correctly ignored'},
        'scope': 'Common source-derived exact-word oracle, not independent hardware oracle, Lean, original gate or timing. Includes empty shapes and n<=4 only to test the generic mathematical core; actual new dispatch remains n>4,p3/4 and machine bounds. Huge-Nat runtime/machine safety is not established by finite tests.'}
    (HERE/'astra-column4-model.json').write_text(json.dumps(rec, indent=2)+'\n', encoding='utf-8', newline='\n')
    print(json.dumps(rec))


if __name__ == '__main__':
    main()
