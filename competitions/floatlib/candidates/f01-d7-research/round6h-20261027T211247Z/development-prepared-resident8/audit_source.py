"""Bind finite address model to exact source wiring; still not a Lean proof."""
from pathlib import Path
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
sha = lambda b: hashlib.sha256(b).hexdigest()


def audit(raw):
    s = raw.decode()
    hot = s.split('def wordLoop', 1)[1].split('def runDot', 1)[0]
    actual = re.findall(r'\(q(\d)(\d) \+ a\.r(\d) \* b\.s(\d)\)', hot)
    expected = [(str(r), str(c), str(r), str(c)) for c in range(4) for r in range(4)]
    assert actual == expected, 'MAC lane mapping/order'
    assert hot.count('.uget k') == 2
    assert not any(x in hot for x in ('toFloat32', 'ofBits', 'convert', '.push', '.map', 'lean_apply'))
    assert hot.count('wordLoop count A B hn (k + 1)') == 1
    returned = re.search(r'else ⟨([^⟩]+)⟩', hot).group(1).split(', ')
    assert returned == [f'q{r}{c}' for c in range(4) for r in range(4)]
    tile = s.split('@[noinline] def tile ', 1)[1].split('\ndef tiles ', 1)[0]
    finishes = re.findall(r'  let w(\d)(\d) := ([^\n]+)', tile)
    assert len(finishes) == 16
    for r, c, expr in finishes:
        rr, cc = int(r), int(c)
        a = 'baseA' if rr == 0 else f'(baseA + {rr} * n)'
        b = 'baseB' if cc == 0 else f'(baseB + {cc})'
        wanted = f'(Packed10.finish n {a} {b} p A B q.q{r}{c}).raw.1'
        if cc: wanted = f'if {cc} < valid then {wanted} else (0 : UInt32)'
        assert expr == wanted, ('finish/valid', r, c)
    assert 'let PA := packA n baseA A\n  Vector.ofFn' in s
    packed = s.split('def packBGroup ', 1)[1].split('\ndef packBBatch ', 1)[0]
    assert 'let i := base + k.val * p' in packed
    assert '⟨ExecFloat.Binary.toFloat32 (B.getD i posZero),' in packed
    for c in range(1, 4):
        assert f'if {c} < valid then ExecFloat.Binary.toFloat32 (B.getD (i + {c}) posZero) else Packed10.zero32' in packed
    assert 'PA (PB.get (tileIndex batch p b g)) hn' in s
    assert '(min 4 (p - 4 * g.val)) A B' in s
    for r in range(4):
        block = s.split(f'@[inline] def read{r} ', 1)[1].split('\n\n', 1)[0]
        assert f'| 0 => w.w{r}0 | 1 => w.w{r}1 | 2 => w.w{r}2 | _ => w.w{r}3' in block
    assert 'else if h : 1 < n ∧ 4 ≤ m ∧ 4 ≤ p ∧ n < USize.size then core' in s
    assert s.count('let PB := packB batch n p B.toArray') == 1
    assert '((b.val * m + m / 4 * 4 + j.val / p) * n) (b.val * n * p + j.val % p)' in s
    assert not re.search(r'\b(sorry|axiom|unsafe|extern|implemented_by)\b', s)
    return {'sixteen_exact_lane_MACs': True, 'terminal_record_order': True,
            'real_column_finish_and_bases': True, 'packA_before_groups': True,
            'single_packB_whole_call': True, 'word_reads_match_lanes': True,
            'fixed_guard_and_raw_tail': True, 'no_hotcodec_container_syntax': True}


def main():
    raw = (HERE / 'Resident16.lean.inc').read_bytes()
    checks = audit(raw)
    mutations = {
        'MAC_A_lane': (b'q13 + a.r1 * b.s3', b'q13 + a.r0 * b.s3'),
        'MAC_B_lane': (b'q32 + a.r3 * b.s2', b'q32 + a.r3 * b.s1'),
        'finish_baseA': (b'finish n (baseA + 3 * n) baseB', b'finish n baseA baseB'),
        'finish_phantom': (b'if 3 < valid then', b'if 0 < valid then'),
        'words_reader': (b'| 2 => w.w22', b'| 2 => w.w23'),
        'tail_crossbatch': (b'b.val * m + m / 4 * 4', b'm / 4 * 4'),
    }
    result_mutations = {}
    for name, (before, after) in mutations.items():
        assert before in raw
        try:
            audit(raw.replace(before, after, 1))
        except AssertionError as error:
            result_mutations[name] = {'caught': True, 'reason': str(error)}
        else:
            raise AssertionError('Source mutation not caught: ' + name)
    source = (HERE / 'KernelResident16Cost.lean').read_bytes()
    manifest = json.loads((HERE / 'resident16-source-manifest.json').read_bytes())
    assert sha(source) == manifest['sha256'] and sha(raw) == manifest['fragment_sha256']
    model = json.loads((HERE / 'resident16-address-screen.json').read_bytes())
    assert model['fragment_sha256'] == sha(raw)
    report = {'status': 'SOURCE_WIRING_AUDIT_PASS', 'fragment_sha256': sha(raw),
              'kernel_sha256': sha(source), 'checks': checks, 'source_mutations': result_mutations,
              'finite_address_screen_sha256': sha((HERE / 'resident16-address-screen.json').read_bytes()),
              'scope': 'Exact source text wiring bound to finite symbolic model. Not parser/typecheck/IEEE/native/proof/performance.'}
    (HERE / 'resident16-source-audit.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(report))


if __name__ == '__main__':
    main()
