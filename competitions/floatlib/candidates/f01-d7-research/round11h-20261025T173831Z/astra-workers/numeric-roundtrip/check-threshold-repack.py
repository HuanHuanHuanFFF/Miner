"""Five-second finite discriminator for R-based repacking; never reads benchmark inputs."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import math
import struct
import subprocess
import sys
import time

HERE = Path(__file__).resolve().parent
LOW, HIGH = 1 << 23, (1 << 24) - 1

def rne_integer(n):
    s = max(0, n.bit_length() - 24)
    if not s:
        return n
    q, r = divmod(n, 1 << s)
    half = 1 << (s - 1)
    return (q + (r > half or (r == half and q & 1))) << s

def host_bits(x):
    try:
        return struct.unpack('>I', struct.pack('>f', x))[0]
    except OverflowError:
        return 0xff800000 if x < 0 else 0x7f800000

def one(ma, mb, d, same, ehi, sign):
    n = (ma << d) + mb if same else (ma << d) - mb
    if not LOW <= n <= 2164260735:
        return None
    r = rne_integer(n)
    threshold_power = 24 + d if same else 23 + d
    c = int(r >= (1 << threshold_power))
    shift = d + c if same else d - 1 + c
    eout = ehi + c if same else ehi - 1 + c
    assert 0 <= shift <= 8
    assert LOW <= (r >> shift) <= HIGH
    assert r % (1 << shift) == 0
    assert 1 <= eout <= 255
    word = ((sign << 31) | 0x7f800000) if eout == 255 else (
        (sign << 31) | (eout << 23) | ((r >> shift) & (LOW - 1)))
    exact_double = math.ldexp(float(n), ehi - d - 150)
    reference = host_bits(-exact_double if sign else exact_double)
    assert word == reference, (ma, mb, d, same, ehi, sign, n, r, word, reference)
    return {'ma': ma, 'mb': mb, 'd': d, 'same': same, 'ehi': ehi,
            'sign': sign, 'N': n, 'R': r, 'shift': shift, 'output_exponent': eout,
            'word_hex': f'{word:08x}',
            'wrong_N_threshold': int(n >= (1 << threshold_power)) != c}

def worker():
    start = time.perf_counter()
    counts = {'checked': 0, 'same': 0, 'opposite': 0, 'shift8': 0,
              'overflow_to_infinity': 0, 'N_threshold_differs_from_R_threshold': 0}
    cases, wrong, edge = set(), None, None
    mantissas = [LOW, LOW + 1, LOW + 2, LOW + 3, LOW + 63, LOW + 64, LOW + 65,
                 LOW + 127, LOW + 128, LOW + 129, 3 << 22,
                 HIGH - 129, HIGH - 128, HIGH - 127, HIGH - 65, HIGH - 64,
                 HIGH - 63, HIGH - 3, HIGH - 2, HIGH - 1, HIGH]
    for d in range(8):
        for same in [False, True]:
            if not same and d == 0:
                continue
            for ma in mantissas:
                for mb in mantissas:
                    cases.add((ma, mb, d, same))
            # Construct true N values immediately around the carry boundary.
            threshold = 1 << ((24 if same else 23) + d)
            for delta in [-257, -129, -128, -127, -65, -64, -63, -3, -2, -1, 0, 1, 2, 3, 63, 64, 65, 127, 128, 129, 257]:
                n = threshold + delta
                if same:
                    ma = (n - LOW) >> d
                    mb = n - (ma << d)
                else:
                    ma = (n + LOW + (1 << d) - 1) >> d
                    mb = (ma << d) - n
                if LOW <= ma <= HIGH and LOW <= mb <= HIGH:
                    cases.add((ma, mb, d, same))
    for ma, mb, d, same in sorted(cases):
        for ehi in sorted({d + 1, max(d + 1, 127), 253, 254}):
            for sign in [0, 1]:
                item = one(ma, mb, d, same, ehi, sign)
                if item is None:
                    continue
                counts['checked'] += 1
                counts['same' if same else 'opposite'] += 1
                counts['shift8'] += item['shift'] == 8
                counts['overflow_to_infinity'] += item['output_exponent'] == 255
                counts['N_threshold_differs_from_R_threshold'] += item['wrong_N_threshold']
                if item['wrong_N_threshold'] and wrong is None:
                    wrong = item
                if item['shift'] == 8 and edge is None:
                    edge = item
    assert wrong is not None and edge is not None
    print(json.dumps({'counts': counts, 'first_N_threshold_counterexample': wrong,
                      'first_shift8_case': edge, 'worker_elapsed_seconds': time.perf_counter() - start}))

if '--worker' in sys.argv:
    worker()
else:
    start = time.perf_counter()
    child = subprocess.run([sys.executable, str(Path(__file__).resolve()), '--worker'],
                           capture_output=True, text=True, timeout=5)
    raw = child.stdout
    (HERE / 'threshold-repack-raw.json').write_bytes(raw.encode('utf-8'))
    (HERE / 'threshold-repack-stderr.txt').write_bytes(child.stderr.encode('utf-8'))
    assert child.returncode == 0, child.stderr
    result = json.loads(raw)
    result.update({'checked_utc': datetime.now(timezone.utc).isoformat(),
                   'scope': 'Finite synthetic aligned normal-mantissa integer model and exact-double-to-binary32 output comparison; no Lean proof, benchmark timing, or hidden/confirmation inputs',
                   'source_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
                   'raw_stdout_sha256': hashlib.sha256(raw.encode('utf-8')).hexdigest(),
                   'actual_timeout_seconds': 5, 'wall_seconds': time.perf_counter() - start,
                   'full_domain_proved': False, 'kernel_candidate': False})
    (HERE / 'threshold-repack-check.json').write_bytes((json.dumps(result, indent=2) + '\n').encode('utf-8'))
    print(json.dumps(result, indent=2))
