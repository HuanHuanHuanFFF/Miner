"""Transfer the actually observed582 CSV engine into539 content routing."""
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
    source = ROOT / 'candidates/r18-539-content-route'
    rust, lean = (source / 'parse.rs').read_text(), (source / 'Parse.lean').read_text()
    old = 'pub fn p135_row14(input:&[u8],out:&mut[u32])->usize{pc_run1c::<32768>(input,out,6,0,1000000,4294967040,2,3)}'
    new = 'pub fn p135_row14(input:&[u8],out:&mut[u32])->usize{pc_run1::<32768>(input,out,4,258,1000000,4294967295)}'
    assert rust.count(old) == 1
    rust = rust.replace(old, new)
    old = 'rw [slot.p135_row14]\n exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)'
    new = 'rw [slot.p135_row14]\n exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)'
    assert lean.count(old) == 1
    lean = lean.replace(old, new)
    entry = builder.write_candidate('r18-539-csv-lazy-content', 'r18-539-content-route', rust, lean,
        'Content class10 uses four-byte lazy single-head PC parser rather than three-byte two-link PC parser. This transfers the actual582 CSV route while retaining539 text, prose, DNA and other engine choices. Outer parse uses the already decoded content-only router.',
        'BH observer disproved the assumed582 CSV row0: CSV actually executes row7 (single-head, lazy258, full4-byte key). Hint/skip-only interventions had no material quality effect. This changes the matcher mechanism, not its name; previousBE proved only public output equality of content routing, not private equality.',
        {'source': 'references/round18-public-539/source-receipt.json',
         'route_evidence': 'evidence/round18/search-bh-decision.json',
         'transferred_engine': 'candidates/r17-dna-nofold-proof1/parse.rs:p125_row7',
         'ownership': 'Original539 and582 authors retained.'})
    entry.update(anchor='public539', comparison_baseline='public539', native_decode_reference='public539')
    spec = json.loads((E / 'public539-bd-native.json').read_bytes())
    for f in ('r18_function_profile', 'r15_profile_entry', 'r15_profile_functions'):
        spec.pop(f)
    spec['entries'].append(entry)
    spec['screen_orders'] = [[e['name'] for e in spec['entries']], [e['name'] for e in reversed(spec['entries'])]]
    spec['snapshot_pages'] = 'evidence/round18/official-extension-30m/pareto-pages.json'
    spec['description'] = 'BI mechanism transfer grounded inBH actual route observation:539 content class10 adopts582 actualCSV four-byte lazy single-head parser. Full28 originalencoder/decode, no inherited proof claim. Expectation is recovery ofCSV quality with539 other gains; actual output decides standard total-time and fullgate. Cap15min; slower-than-parent still scored jointly.'
    (E / 'csv-bi-native.json').write_bytes((json.dumps(spec, indent=2) + '\n').encode())
    (E / 'csv-bi-preflight.json').write_bytes((json.dumps({
        'declared_at_utc': datetime.now(timezone.utc).isoformat(),
        'gap': 'BG andBH excluded hint and skip differences as explanation forCSV25588B deficit; actual582 observer identified a different single-head lazy engine.',
        'material_change': 'CSV content route uses existing539 PC.run1 with exact582 row7 parameters, other content routes preserved.',
        'minimum_operation': 'One frozen pair,28file originalencoder/decode with539 and582 references.',
        'decision_boundary': 'Recovering mostCSV quality while preserving other text gains earns immediate original paired-total timing and scoring; degradation or no recovery stops this engine transfer.',
        'proof_preflight': 'Existing genericPC.run1_spec applies; row14 theorem changed accordingly. BE content-wrapper proof retained. Exact fullgate still unknown.',
        'cost_cap_runner_minutes': 15,
        'deadline_utc': '2026-10-10T04:32:51+00:00',
    }, indent=2) + '\n').encode())
    print(json.dumps(entry))


if __name__ == '__main__':
    main()
