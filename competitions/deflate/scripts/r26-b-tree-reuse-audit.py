"""Read-only comparison against the direct R24 A-tree child16/state-prune precedent."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.dont_write_bytecode = True
spec = importlib.util.spec_from_file_location('recovery', ROOT/'scripts/r26-b-recovery-audit.py')
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    current_path = ROOT/'references/round24-public-552/parse.rs'
    parent_path = ROOT/'candidates/r24-609-once/parse.rs'
    current, previous = current_path.read_text(), parent_path.read_text()
    mapping = {'Z189':'a_tree_insert','Z186':'a_find_all','Z164':'a_word_at','Z158':'a_slot_of',
               'Z153':'a_probe','Z165':'a_word_pair','Z157':'a_shared','Z3':'A_NICE','Z0':'A_HB'}
    def renamed(text):
        return re.sub(r'\b(?:'+ '|'.join(mapping) +r')\b',lambda m:mapping[m.group()],text)
    comparisons = {}
    for now, old in [('a_tree_insert','Z189'),('a_probe','Z153'),('a_word_pair','Z165'),('a_word_at','Z164'),('a_slot_of','Z158'),('a_shared','Z157')]:
        comparisons[now] = audit.function(current,now) == renamed(audit.function(previous,old))
    assert all(comparisons.values()), comparisons
    assert 'pub const Z3: usize = 128;' in previous
    assert 'pub const Z0: u32 = 16;' in previous
    assert 'pub const A_NICE: usize = 128;' in current
    assert 'pub const A_HB: u32 = 16;' in current
    # The known guards and push adapter explain the exact remaining finder differences.
    finder = audit.function(current,'a_find_all')
    finder = finder.replace('a_has_room(n, i, 266)','n >= 266 && i <= n - 266')
    finder = finder.replace('a_has_room(n, i, 3)','n >= 3 && i <= n - 3')
    finder = finder.replace('d_push32(mp, 0);','mp.push(0);').replace('d_push32(mp, mb.len() as u32);','mp.push(mb.len() as u32);')
    finder = finder.replace('cd.wrapping_sub(1)','(cd - 1)')
    assert finder == renamed(audit.function(previous,'Z186'))
    receipt_path = ROOT/'evidence/round26/38182721892/repeat-b9-native/diagnostics/r26-b-a-repeat/receipt.json'
    receipt = json.loads(receipt_path.read_bytes())
    assert receipt['source_hashes']['parse.rs'] == sha(current_path)
    rows = []
    for row in receipt['rows']:
        if not row['counts']['a_engine_calls']:
            continue
        pairs = sorted({(c['depth'],c['skip']) for c in row['block_contexts']})
        assert len(pairs) == 1
        depth, skip = pairs[0]
        rows.append({'file':row['file'],'raw_bytes':row['raw_bytes'],'depth':depth,'skip':skip,'AE_eligible':skip>=258})
    result = {'status':'VERIFIED_STATIC_DIRECT_PRECEDENT_AND_REAL_B9_CONTEXT',
              'computed_utc':datetime.now(timezone.utc).isoformat(),'helper_comparisons_after_exact_renaming':comparisons,
              'tree_constants_equal':True,'finder_same_after_explicit_adapters':True,
              'finder_adapters':['equivalent a_has_room bounds helper','guarded d_push32 adapter instead of direct push','wrapping cd subtraction instead of plain subtraction'],
              'current_parent_rust_sha256':sha(current_path),'R24_once_rust_sha256':sha(parent_path),
              'R24_AD_rust_sha256':sha(ROOT/'candidates/r24-609-child16/parse.rs'),
              'R24_AD_builder_sha256':sha(ROOT/'scripts/build-round24-child16.py'),
              'R24_AD_preflight_sha256':sha(ROOT/'evidence/round24/preflight-ad.json'),
              'B9_receipt_sha256':sha(receipt_path),'B9_run_id':receipt['run_id'],'B9_source_hashes':receipt['source_hashes'],
              'actual_A_contexts':rows,'A_inputs':len(rows),'A_input_bytes':sum(r['raw_bytes'] for r in rows),
              'AE_eligible_inputs':sum(r['AE_eligible'] for r in rows),'AE_eligible_input_bytes':sum(r['raw_bytes'] for r in rows if r['AE_eligible']),
              'decision':'STOP child16 model/trace/candidate as a repeated direct AD mechanism; AE is an existing reusable component on6/7 real A inputs, no new mechanism or current gain.',
              'limits':['Static/helper equality and frozen real parent contexts do not establish runtime parity of a newly migrated candidate.',
                        'R24 AD/AG negative timings and AE positive discovery are historical; no current timing/share/gate claim.',
                        'Current docs skip256 is ineligible; any AE reuse must preserve its original fallback and the guarded push/overflow behavior.',
                        'No new finite model, Rust candidate, runner, proof, or formal submission was generated.']}
    output = ROOT/'evidence/round26/route-b/b18-tree-reuse-audit.json'
    output.write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps(result,indent=2))


if __name__ == '__main__':
    main()
