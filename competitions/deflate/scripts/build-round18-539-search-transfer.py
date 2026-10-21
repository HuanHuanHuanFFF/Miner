"""Test the observed CSV search-budget difference after ruling out hint semantics."""
from pathlib import Path
from datetime import datetime, timezone
import importlib.util
import json

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round18'


def main():
    sp = importlib.util.spec_from_file_location('builder', ROOT / 'scripts/build-round18-start.py')
    builder = importlib.util.module_from_spec(sp)
    sp.loader.exec_module(builder)
    source = ROOT / 'references/round18-public-539'
    rust, lean = (source / 'parse.rs').read_text(), (source / 'Parse.lean').read_text()
    old = 'pub fn p135_row14(input:&[u8],out:&mut[u32])->usize{pc_run1c::<32768>(input,out,6,0,1000000,4294967040,2,3)}'
    assert rust.count(old) == 1
    rust = rust.replace(old, old.replace('(input,out,6,', '(input,out,5,'))
    entry = builder.write_candidate('r18-539-key3-search5', 'public539', rust, lean,
        'Transfer the known582 skip-shift5 search budget into539 existing three-byte-key row14. All other539 routes and engines are unchanged.',
        'BG ruled out modular-hint semantics as the source of the25588B CSV deficit. Row14 has skip-shift6 versus582 row0 shift5; this is one mechanism-directed transfer, not a multi-parameter sweep. Slower total time will be scored jointly with size before rejection.',
        {'source': 'references/round18-public-539/source-receipt.json',
         'other_row': 'candidates/r17-dna-nofold-proof1/parse.rs:p125_row0',
         'negative_evidence': 'evidence/round18/chain-bg-decision.json',
         'ownership': 'Original539 and582 authors retained.'})
    entry.update(anchor='public539', comparison_baseline='public539', native_decode_reference='public539')
    spec = json.loads((E / 'public539-bd-native.json').read_bytes())
    spec['entries'].append(entry)
    spec['screen_orders'] = [[e['name'] for e in spec['entries']], [e['name'] for e in reversed(spec['entries'])]]
    spec['snapshot_pages'] = 'evidence/round18/official-extension-30m/pareto-pages.json'
    spec['r15_profile_entry'] = 'dna582'
    spec['r15_profile_functions'] = ['parse', 'bulk_parse'] + ['p125_row' + str(i) for i in range(17)]
    spec['description'] = 'BH single539row14 search-budget transfer afterBG ruled out predecessor semantics. Original28-file encoder/decode versus539/582; output-equivalent582 row observer resolves actual route differences before claiming same row execution. Cap15minutes. Meaningful size recovery earns original paired total timing and scorer replay even if slower. Original539 proof is an untested exact-pair draft.'
    (E / 'search-bh-native.json').write_bytes((json.dumps(spec, indent=2) + '\n').encode())
    preflight = {
        'declared_at_utc': datetime.now(timezone.utc).isoformat(),
        'gap': 'BG key3 hint transfer changed no public bytes; all-key transfer saved only3B in bundle and did not recover CSV. Direct route row parameters differ at search skip shift.',
        'material_change': 'Only539 row14 shift6 to known582 shift5; one controlled search-budget transfer.',
        'minimum_operation': 'Full28 original encoder and decode for one new candidate; observer of actual582 row selection, validated for unchanged output.',
        'decision_boundary': 'A material recovery of CSV size at preserved text gains receives total timing and frontier replay; no improvement stops this specific row transfer. Instrumented timing is diagnostic only.',
        'proof_cost': 'Original row14 generic correctness lemma checks skip<32; unchanged proof is draft until original full gate. Both source files remain within524288B.',
        'cost_cap_runner_minutes': 15,
        'deadline_utc': '2026-10-10T04:32:51+00:00',
    }
    (E / 'search-bh-preflight.json').write_bytes((json.dumps(preflight, indent=2) + '\n').encode())
    print(json.dumps(entry))


if __name__ == '__main__':
    main()
