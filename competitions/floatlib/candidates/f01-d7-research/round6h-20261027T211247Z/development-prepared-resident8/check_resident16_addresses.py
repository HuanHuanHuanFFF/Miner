"""4-D symbolic layout/order mutation screen; no floating arithmetic or build."""
from pathlib import Path
import hashlib
import itertools
import json

HERE = Path(__file__).resolve().parent
ZERO = ('PAD_ZERO',)


def reference(batch, m, n, p):
    return [((b * m + r) * n, b * n * p + j,
             tuple((((b * m + r) * n + k), b * n * p + k * p + j) for k in range(n)))
            for b in range(batch) for r in range(m) for j in range(p)]


def model(batch, m, n, p, mutation=None):
    groups = (p + 3) // 4
    pb, decoded_b = [], []
    for b in range(batch):
        for g in range(groups):
            valid = min(4, p - 4 * g)
            packet = []
            for k in range(n):
                i = b * n * p + 4 * g + k * p
                packet.append(tuple(i + c if c < valid else ZERO for c in range(4)))
                decoded_b.extend(i + c for c in range(valid))
            pb.append(packet)
    assert len(pb) == batch * groups
    assert sorted(decoded_b) == list(range(batch * n * p))
    out, finishes, decoded_a = [], [], []
    for b in range(batch):
        for rb in range(m // 4):
            base = (b * m + 4 * rb) * n
            pa = [tuple(base + r * n + k for r in range(4)) for k in range(n)]
            decoded_a.extend(v for a in pa for v in a)
            tile_results = []
            for g in range(groups):
                index = b * groups + g
                if mutation == 'B_crossbatch': index = g
                if mutation == 'B_colgroup': index = b * groups
                packet = pb[index]
                chains = [[[] for _ in range(4)] for _ in range(4)]
                order = range(n - 1, -1, -1) if mutation == 'reverse_k' else range(n)
                for k in order:
                    a = pa[k]
                    if mutation == 'A_crossbatch': a = tuple((4 * rb + r) * n + k for r in range(4))
                    if mutation == 'A_rowstride': a = tuple(base + r * (n + 1) + k for r in range(4))
                    bk = k * groups if mutation == 'B_stride' else k
                    bp = packet[bk] if bk < len(packet) else (ZERO,) * 4
                    for r in range(4):
                        for c in range(4):
                            chains[r][c].append((a[r], bp[c]))
                for r in range(4):
                    for c in range(4):
                        if 4 * g + c < p or mutation == 'phantom_finish':
                            fa = base + r * n
                            if mutation == 'finish_local_base': fa = r * n
                            finishes.append((fa, b * n * p + 4 * g + c))
                tile_results.append(chains)
            for r in range(4):
                for j in range(p):
                    rr, cc = (3 - r if mutation == 'word_row' else r), j % 4
                    if mutation == 'word_column': cc = (cc + 1) % 4
                    out.append((base + r * n, b * n * p + j, tuple(tile_results[j // 4][rr][cc])))
        for r in range(m // 4 * 4, m):
            for j in range(p):
                a = (b * m + r) * n
                if mutation == 'tail_local_base': a = (r - m // 4 * 4) * n
                out.append((a, b * n * p + j,
                            tuple((a + k, b * n * p + k * p + j) for k in range(n))))
    assert sorted(decoded_a) == [((b * m + r) * n + k)
                                 for b in range(batch) for r in range(m // 4 * 4) for k in range(n)]
    expected_finish = [((b * m + r) * n, b * n * p + j)
                       for b in range(batch) for r in range(m // 4 * 4) for j in range(p)]
    assert sorted(finishes) == sorted(expected_finish), ('finish', mutation, (batch, m, n, p))
    return out


def main():
    shapes = list(itertools.product(range(4), range(12), range(7), range(14)))
    count_outputs, count_macs, eligible = 0, 0, 0
    for shape in shapes:
        actual = model(*shape)
        assert actual == reference(*shape), shape
        count_outputs += len(actual)
        count_macs += sum(len(v[2]) for v in actual)
        b, m, n, p = shape
        eligible += bool(n > 1 and m >= 4 and p >= 4)
    caught = {}
    for name in ('A_crossbatch', 'A_rowstride', 'B_crossbatch', 'B_colgroup', 'B_stride',
                 'reverse_k', 'word_row', 'word_column', 'phantom_finish',
                 'finish_local_base', 'tail_local_base'):
        for shape in shapes:
            try:
                bad = model(*shape, name) != reference(*shape)
            except AssertionError:
                bad = True
            if bad:
                caught[name] = {'caught': True, 'first_shape': shape}
                break
        assert name in caught, name
    raw = (HERE / 'Resident16.lean.inc').read_bytes()
    result = {'status': 'FINITE_SYMBOLIC_PASS', 'fragment_sha256': hashlib.sha256(raw).hexdigest(),
              'shape_count': len(shapes), 'eligible_shape_count': eligible,
              'output_count': count_outputs, 'ordered_mac_count': count_macs,
              'ranges': {'batch': [0, 3], 'm': [0, 11], 'n': [0, 6], 'p': [0, 13]},
              'checks': ['one A decode per full-row element', 'one B decode per real element',
                         'B4 group,k continuity', 'batch/rowblock/row stride',
                         'all 16 independent ascending-k chains', 'row-major output',
                         'original finish bases', 'no phantom finish', 'tail0..3 raw bases'],
              'mutations': caught,
              'limitations': 'Finite Python symbolic model only. Float32/NaN/Lean/native/lifetime/cost UNKNOWN.'}
    (HERE / 'resident16-address-screen.json').write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(result))


if __name__ == '__main__':
    main()
