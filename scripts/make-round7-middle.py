"""Controlled budget experiments on public #361. No local Rust or Lean runtime."""
from pathlib import Path
import argparse
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'references/round7-public-361'

def sha(data):
    return hashlib.sha256(data).hexdigest()

def table(source, name, columns, transform):
    pattern = r'pub const ' + name + r': \[\[usize; ' + str(columns) + r'\]; 16\] = \[\n(.*?)\n\];'
    match = re.search(pattern, source, re.S)
    assert match
    changes = []
    row = 0
    def change(m):
        nonlocal row
        before = [int(x.strip()) for x in m[1].split(',')]
        assert len(before) == columns
        after = transform(row, before.copy())
        assert len(after) == columns and all(0 <= v <= 65536 for v in after)
        if after != before:
            changes.append({'row': row, 'before': before, 'after': after})
        row += 1
        return '[' + ', '.join(map(str, after)) + ']'
    body = re.sub(r'\[([\d ,]+)\]', change, match[1])
    assert row == 16
    old = match[0]
    new = old[:match.start(1)-match.start()] + body + old[match.end(1)-match.start():]
    assert source.count(old) == 1
    return source.replace(old, new, 1), (old, new), changes

def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check', action='store_true')
    args = ap.parse_args()
    provenance = json.loads((BASE / 'PROVENANCE.json').read_text())
    raw = {n:(BASE / n).read_bytes() for n in ('parse.rs', 'Parse.lean')}
    assert all(sha(raw[n]) == provenance['hashes'][n] for n in raw)
    source = raw['parse.rs'].decode()
    recipes = [
        ('upd2', 'Rebuild forward symbol prices half as often in every active DP class; D forward prices also update every 4096 positions.'),
        ('upd4', 'Quarter the symbol-price refresh rate; test whether stable histograms permit fewer cost rebuilds without losing the chosen path.'),
        ('back16', 'Limit backward candidate extension to 16 bytes in the forward DP; preserve match validity checks and all emitters.'),
        ('d7half', 'Halve only the forward DP long-chain search budget; retain three-byte and four-byte candidate search and continuation candidates.'),
        ('huff8k', 'Use actual Huffman-length symbol prices instead of entropy estimates for all active DP classes, with at least 8192 positions between rebuilds.'),
        ('lazy1', 'Search one position after a match anchor in every DP class, reducing speculative lazy searches while retaining the ring DP.'),
        ('ct6', 'Raise the continuation cutoff to six bytes, spending search work on marginal short matches to test a smaller output at moderate extra time.'),
        ('skip32', 'Take a match as-is above 32 bytes in the forward DP, retaining range inserts and verified token emission; test a faster middle tradeoff.'),
    ]
    for name, mechanism in recipes:
        undo=[]
        def transform(row, v):
            if name == 'upd2': v[8] *= 2
            elif name == 'upd4': v[8] *= 4
            elif name == 'back16': v[10] = 16
            elif name == 'd7half': v[3] = max(1, v[3] // 2)
            elif name == 'huff8k': v[6],v[8] = 1,max(8192,v[8])
            elif name == 'lazy1': v[1] = 1
            elif name == 'ct6': v[0] = 6
            elif name == 'skip32': v[4] = 32
            else: raise AssertionError(name)
            return v
        text, edit, changes = table(source, 'DP_KNOBS', 11, transform)
        undo.append(edit)
        if name in ('upd2','upd4'):
            old = 'pub const UPD: usize = 2048;'
            new = f'pub const UPD: usize = {4096 if name == "upd2" else 8192};'
            assert text.count(old) == 1
            text = text.replace(old,new,1); undo.append((old,new))
        restored=text
        for old,new in reversed(undo):
            assert restored.count(new) == 1
            restored=restored.replace(new,old,1)
        assert restored == source
        candidate='r7-mid361-'+name
        files={'parse.rs':text.encode(),'Parse.lean':raw['Parse.lean']}
        assert all(0 < len(b) <= 524288 for b in files.values())
        manifest={'candidate':candidate,'base_submission_id':'361','parent':str(BASE.relative_to(ROOT)).replace('\\','/'),
            'base_hashes':provenance['hashes'],'hashes':{n:sha(b) for n,b in files.items()},'bytes':{n:len(b) for n,b in files.items()},
            'mechanism':mechanism,'parameter_rows':changes,'attribution':{'author_hotkey':provenance['author_hotkey'],'provenance':str((BASE/'PROVENANCE.json').relative_to(ROOT)).replace('\\','/')},
            'audit':'Reverse declared constant/table replacements restores original Rust byte for byte; route, all engine functions and emitters unchanged; proof is copied byte for byte.',
            'proof_status':'UNKNOWN fresh extraction/obligation/axioms; copying the reference proof is not verification.',
            'performance_status':'UNKNOWN public paired metrics, heldout behavior, admission and rewards; formal #361 anchors only a transfer hypothesis.'}
        files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode()
        dest=ROOT/'candidates'/candidate
        if args.check:
            assert all((dest/n).read_bytes()==b for n,b in files.items()),candidate
        else:
            dest.mkdir(exist_ok=True)
            for n,b in files.items():
                assert not (dest/n).exists() or (dest/n).read_bytes()==b
                (dest/n).write_bytes(b)
        print(json.dumps({'candidate':candidate,'hashes':manifest['hashes']}))

if __name__ == '__main__':
    main()
