"""Prepare a reviewable native spec; root owns live snapshot/route hooks and dispatch."""
from pathlib import Path
import ast
import hashlib
import importlib
import json

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT/'evidence/round26/extension1h/route-c'

def sha(b): return hashlib.sha256(b).hexdigest()
def dump(p,x): p.write_bytes((json.dumps(x,indent=2,ensure_ascii=False)+'\n').encode())

def main():
    source = json.loads((ROOT/'evidence/round26/quality-a18-native.json').read_bytes())
    entry = json.loads((OUT/'c2-entry.json').read_bytes())
    source['entries'] = [e for e in source['entries'] if e['control']] + [entry]
    source['native_encoder_references'] = ['public658']
    source.pop('r26_a_window_counts')
    source['r26_c_fold_tail_counts'] = True
    names = [e['name'] for e in source['entries']]
    source['screen_orders'] = [names,list(reversed(names))]
    source['description'] = 'C2 one necessary last-byte guard before U118 whole-token backward same. Original444 finite identity; actual28 originalencoder/token/decode equality. Original658 observer counts removable source-levelword/byte comparisons, existing same-distance coverage, and addedtailchecks. Counts are untimed and never used as speed or share. Parent Lean unchanged draft; no gate.'
    required = ['scripts/r26-c-build-fold-tail.py','scripts/r26-c-fold-tail-counts.py',
                'scripts/r26-c-prepare-native.py','scripts/r26-a-rep-shadow.py',
                'scripts/research-round25-len3-price.py','scripts/research-round13-encoder-native.py',
                'scripts/research-round4.py','scripts/round26-preflight.py',
                'scripts/research-round13-native.py','evidence/round26/extension1h/route-c/c2-predeclaration.md',
                'references/round26-public-658/source-receipt.json',
                'candidates/r26-c-658-fold-tail/manifest.json',source['snapshot_pages']]
    for e in source['entries']:
        required += [e['path']+'/'+n for n in ('parse.rs','Parse.lean')]
    source['r26_required_files'] = {p:sha((ROOT/p).read_bytes()) for p in required}
    dump(OUT/'c2-native-draft.json',source)
    for p in ROOT.glob('scripts/r26-c-*.py'): ast.parse(p.read_text(encoding='utf-8'),filename=str(p))
    checked = importlib.import_module('r26-c-fold-tail-counts').preflight(source)
    eq = importlib.import_module('research-round4')
    harness = eq.build_harness(eq.equivalence_pairs(source))
    checked.update(python_ast='PASS',finite_harness_constructed=True,
                   finite_harness_sha256=sha(harness.encode()),
                   limits='Local static preflight only. No Rust/Lean compilation or corpus available locally.',
                   root_integration=['Refresh snapshot_pages only if needed; historical snapshot is not used for this native score.',
                                     'Hook r26_c_fold_tail_counts into round26-preflight.py and research-round13-native.py after originalencoder.',
                                     'Freeze exact integrated hook files in r26_required_files before dispatch.'])
    dump(OUT/'c2-local-preflight.json',checked)
    print(json.dumps(checked,indent=2))

if __name__=='__main__': main()
