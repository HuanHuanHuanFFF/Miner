"""Finite symbolic address/order falsifier only; never a Float32 or Lean proof."""
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
    h, groups = m // 4, (p + 1) // 2
    pa, pb, adecodes, bdecodes = [], [], [], []
    for b in range(batch):
        for r in range(h):
            base = (b * m + 4 * r) * n
            for k in range(n):
                packet = tuple(base + lane * n + k for lane in range(4))
                pa.append(packet)
                adecodes.extend(packet)
    for b in range(batch):
        for g in range(groups):
            for k in range(n):
                i = b * n * p + 2 * g + k * p
                packet = (i, i + 1 if 2 * g + 1 < p else ZERO)
                pb.append(packet)
                bdecodes.append(i)
                if packet[1] != ZERO:
                    bdecodes.append(i + 1)
    assert len(pa) == batch * h * n
    assert len(pb) == batch * groups * n
    assert sorted(adecodes) == [((b * m + r) * n + k)
                               for b in range(batch) for r in range(4 * h) for k in range(n)]
    assert sorted(bdecodes) == list(range(batch * n * p))
    out, finishes = [], []
    for b in range(batch):
        for r in range(h):
            ac = (b * h + r) * n
            bc = b * groups * n
            if mutation == 'A_crossbatch': ac = r * n
            if mutation == 'B_crossbatch': bc = 0
            if mutation == 'A_rowblock': ac = (b * h + r + 1) * n
            tiles = []
            for g in range(groups):
                chains = [[[] for _ in range(2)] for _ in range(4)]
                order = range(n - 1, -1, -1) if mutation == 'reverse_k' else range(n)
                for k in order:
                    ai = ac + k
                    bi = bc + g * n + k
                    if mutation == 'B_stride': bi = bc + g * n + k * groups
                    if mutation == 'B_group': bi = bc + g + k
                    a = pa[ai] if 0 <= ai < len(pa) else (ZERO,) * 4
                    bp = pb[bi] if 0 <= bi < len(pb) else (ZERO,) * 2
                    for lane in range(4):
                        for col in range(2):
                            chains[lane][col].append((a[lane], bp[col]))
                for lane in range(4):
                    for col in range(2):
                        if 2 * g + col < p or mutation == 'phantom_finish':
                            finishes.append(((b * m + 4 * r + lane) * n, b * n * p + 2 * g + col))
                tiles.append(chains)
            for lane in range(4):
                readlane = 3 - lane if mutation == 'word_row' else lane
                for j in range(p):
                    out.append(((b * m + 4 * r + lane) * n, b * n * p + j,
                                tuple(tiles[j // 2][readlane][j % 2])))
        for r in range(4 * h, m):
            for j in range(p):
                out.append(((b * m + r) * n, b * n * p + j,
                            tuple((((b * m + r) * n + k), b * n * p + k * p + j)
                                  for k in range(n))))
    expected_finish = [(a, j) for a, j, _ in reference(batch, 4 * h, n, p)]
    # Reference above has a different batch stride when m has a tail.
    expected_finish = [((b * m + r) * n, b * n * p + j)
                       for b in range(batch) for r in range(4 * h) for j in range(p)]
    assert sorted(finishes) == sorted(expected_finish), ('finish', mutation, (batch, m, n, p))
    return out


def main():
    shapes = list(itertools.product(range(4), range(12), range(7), range(10)))
    covered, outputs, macs, eligible = 0, 0, 0, 0
    for shape in shapes:
        expected = reference(*shape)
        actual = model(*shape)
        assert actual == expected, shape
        covered += 1
        outputs += len(actual)
        macs += sum(len(row[2]) for row in actual)
        b, m, n, p = shape
        eligible += bool(n > 1 and m >= 4 and p >= 2)
    mutations = {}
    for mutation in ('A_crossbatch', 'B_crossbatch', 'A_rowblock', 'B_stride', 'B_group',
                     'reverse_k', 'word_row', 'phantom_finish'):
        for shape in shapes:
            try:
                different = model(*shape, mutation) != reference(*shape)
            except AssertionError:
                different = True
            if different:
                mutations[mutation] = {'caught': True, 'first_shape': shape}
                break
        assert mutation in mutations, mutation
    src = (HERE / 'PreparedResident8.lean.inc').read_bytes()
    result = {'status': 'FINITE_SYMBOLIC_PASS', 'source_sha256': hashlib.sha256(src).hexdigest(),
              'shapes': covered, 'eligible_shapes': eligible, 'outputs': outputs,
              'ordered_macs': macs, 'ranges': {'batch': [0, 3], 'm': [0, 11], 'n': [0, 6], 'p': [0, 9]},
              'checked': ['A4 index/unique decode', 'B2 index/unique real decode/padding',
                          'batch stride', 'rowblock stride', 'ascending k', 'rowmajor output',
                          'real lane finish bases', 'no phantom finish', 'tail0..3'],
              'mutations': mutations,
              'limitations': 'Python symbolic layout only. No Float32 arithmetic/NaN/replay/Lean/native/RC/performance claim.'}
    (HERE / 'address-screen.json').write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(result))


if __name__ == '__main__':
    main()
