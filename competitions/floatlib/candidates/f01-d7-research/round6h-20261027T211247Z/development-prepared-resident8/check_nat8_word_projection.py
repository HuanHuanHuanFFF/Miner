"""Bind the pending structural word leaf to frozen runtime and model its field order."""
from pathlib import Path
import hashlib
import itertools
import json
import re

HERE = Path(__file__).resolve().parent
sha = lambda b: hashlib.sha256(b).hexdigest()


def main():
    runtime = (HERE / 'KernelIndexed8Cost.lean').read_bytes()
    assert sha(runtime) == '8e27baf70ce7e3f10b669cc9f59d66d5fffaa17ee3dc6df934f3229139a5b0dd'
    leaf = (HERE / 'Nat8WordProjection.lean.inc').read_bytes()
    source = leaf.decode()
    roots = ['Submission.R22Resident8Projection.' + s for s in
             re.findall(r'^theorem (\w+)', source, re.M)]
    assert roots == ['Submission.R22Resident8Projection.tile_word']
    assert not re.search(r'\b(sorry|axiom|unsafe|extern|implemented_by)\b', source)
    mapping = re.findall(r'\| [012_] => if c.val = 0 then w\.(w\d\d) else w\.(w\d\d)', source)
    assert mapping == [(f'w{r}0', f'w{r}1') for r in range(4)]
    text = runtime.decode()
    resident8 = text.split('namespace Submission.R22Resident8\n', 1)[1].split('end Submission.R22Resident8', 1)[0]
    words = re.search(r'structure Words where(.*?)\n\s*@\[noinline\] def tile', resident8, re.S)[1]
    assert re.findall(r'(w\d\d) : UInt32', words) == [f'w{r}{c}' for c in range(2) for r in range(4)]
    tile = resident8.split('@[noinline] def tile', 1)[1].split('\ndef tiles', 1)[0]
    assert 'else ⟨w00, w10, w20, w30, 0, 0, 0, 0⟩' in tile
    assert '(Packed10.finish n baseA baseB p A B q00).raw.1' in tile
    for r in range(1, 4):
        a = '(baseA + n)' if r == 1 else f'(baseA + {r} * n)'
        assert f'(Packed10.finish n {a} baseB p A B q{r}0).raw.1' in tile
    for r in range(4):
        a = 'baseA' if r == 0 else '(baseA + n)' if r == 1 else f'(baseA + {r} * n)'
        assert f'(Packed10.finish n {a} (baseB + 1) p A B q{r}1).raw.1' in tile
    checks = 0
    for n, base_a, base_b, second, r, c in itertools.product(range(5), range(3), range(4),
                                                           (False, True), range(4), range(2)):
        if c == 1 and not second:
            continue
        finish = lambda row, col: ('finish-raw', n, base_a + row * n, base_b + col, f'q{row}{col}')
        words_model = {f'w{row}{col}': finish(row, col) if col == 0 or second else ('word-zero',)
                       for row in range(4) for col in range(2)}
        assert words_model[mapping[r][c]] == finish(r, c)
        checks += 1
    dep = (HERE / 'Nat8Projection-v1.lean.inc').read_bytes()
    assert sha(dep) == '79574fb1b64febf7d3cd328fe41c2f11ac2172e81177fd2cb057aa74e574d6dd'
    receipt = dict(fragment='Nat8WordProjection.lean.inc', sha256=sha(leaf), bytes=len(leaf),
                   roots=roots, status='NOT_COMPILED_NOT_RUN', runtime_sha256=sha(runtime),
                   dependencies=[dict(path='Nat8Projection-v1.lean.inc', sha256=sha(dep))],
                   finite_structural_checks=checks, new_kernel_emitted=False,
                   first_falsifier=dict(second=False, c=1, suppressed_word=0,
                     unrestricted_finish='arbitrary UInt32, potentially nonzero'),
                   scope='Words layout and conditional selected finish only; no new arithmetic proof or public binding.')
    (HERE / 'nat8-word-projection-manifest.json').write_text(json.dumps(receipt, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({k: receipt[k] for k in ('sha256', 'bytes', 'finite_structural_checks', 'status')}))


if __name__ == '__main__':
    main()
