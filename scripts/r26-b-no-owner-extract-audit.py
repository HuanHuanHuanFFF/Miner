"""Read-only verification of B37 exact extraction and changed interface boundaries."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib
import json
import re
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
NAME = 'r26-b-552-a-no-owner'
CURRENT = ROOT/f'evidence/round26/38227360774/screen-b37/gate/research5/{NAME}'
PARENT = ROOT/'evidence/round26/38223722506/screen-b33/gate/research5/r26-b-552-a-flatten/Funs.lean'
RUST = ROOT/f'candidates/{NAME}/parse.rs'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def definition(text, name):
    match = re.search(r'^def '+re.escape(name)+r'(?=\s)', text, flags=re.M)
    assert match, name
    end = text.find('\n/--', match.start())
    assert end >= 0, name
    return text[match.start():end].strip()


def main():
    receipt_path = CURRENT.parent/'research.json'
    receipt = json.loads(receipt_path.read_bytes())['extractions'][NAME]
    assert receipt['exit_code'] == 0 and receipt['extraction_accepted'] and receipt['proof_status'] == 'NOT_RUN'
    assert receipt['source_sha256'] == sha(RUST.read_bytes()) == '8012a8320f07228f01f383d0946d52f1000d3256d71ea6f1a121a2501ea276eb'
    files = {}
    for name, expected in receipt['files'].items():
        raw = (CURRENT/name).read_bytes()
        assert len(raw) == expected['bytes'] and sha(raw) == expected['sha256']
        files[name] = expected
    current = (CURRENT/'Funs.lean').read_text()
    parent = PARENT.read_text()
    names = ['a_dp_recs_loop0_loop0.body', 'a_dp_recs_loop0_loop0',
             'a_dp_recs_loop0_loop1.body', 'a_dp_recs_loop0_loop1',
             'a_dp_recs_loop0.body', 'a_dp_recs_loop0', 'a_dp_recs',
             'a_dp_min_loop.body', 'a_dp_min_loop', 'a_dp_min',
             'a_store_choice', 'a_dp_pass_loop0.body', 'a_dp_pass_loop0',
             'a_dp_pass_loop1_loop0.body', 'a_dp_pass_loop1_loop0', 'a_slot_of']
    preserved = {}
    for name in names:
        a, b = definition(current, name), definition(parent, name)
        assert a == b, name
        preserved[name] = {'definition_sha256': sha(a.encode()), 'exact_equal_B33_generated_definition': True}
    changed = ['a_fill_loop0_loop0.body', 'a_fill_loop0_loop0', 'a_fill_loop0.body', 'a_fill_loop0', 'a_fill',
               'a_dp_fill_loop.body', 'a_dp_fill_loop', 'a_dp_fill',
               'a_dp_pass_loop1.body', 'a_dp_pass_loop1', 'a_dp_pass']
    headers = {}
    for name in changed:
        part = definition(current, name)
        assert re.search(r'\bdl\d*\b', part) is None, name
        headers[name] = part.split('  := do')[0]
    loop0 = definition(current, 'a_dp_owner_loop0.body')
    loop1 = definition(current, 'a_dp_owner_loop1.body')
    assert loop0.replace('a_dp_owner_loop0', 'OWNER') == loop1.replace('a_dp_owner_loop1', 'OWNER')
    owners = {name: {'header': definition(current, name).split('  := do')[0],
                     'definition_sha256': sha(definition(current, name).encode())}
              for name in ['a_dp_owner_loop0.body', 'a_dp_owner_loop0', 'a_dp_owner_loop1.body', 'a_dp_owner_loop1', 'a_dp_owner']}
    span = importlib.import_module('r26-b-fix-shared-cache').spans
    a = (ROOT/'candidates/r26-b-552-a-flatten/parse.rs').read_text()
    b = RUST.read_text()
    sa, sb = span(a), span(b)
    source_changed = sorted(n for n in sa if a[sa[n][0]:sa[n][1]] != b[sb[n][0]:sb[n][1]])
    source_new = sorted(set(sb)-set(sa))
    assert source_changed == ['a_dp_fill', 'a_dp_pass', 'a_fill'] and source_new == ['a_dp_owner']
    result = {'status': 'VERIFIED_EXACT_EXTRACT_ONLY_AND_GENERATED_INTERFACE_AUDIT',
              'computed_utc': datetime.now(timezone.utc).isoformat(), 'run_id': '38227360774',
              'research_receipt_sha256': sha(receipt_path.read_bytes()), 'source_sha256': receipt['source_sha256'],
              'proof_status': 'NOT_RUN_DRAFT_PARENT552_LEAN_UNCHANGED', 'files': files,
              'comparison_generated_Funs': PARENT.relative_to(ROOT).as_posix(),
              'comparison_generated_Funs_sha256': sha(PARENT.read_bytes()),
              'source_changed_functions_vs_full_owner': source_changed, 'source_new_functions': source_new,
              'preserved_generated_definitions': preserved, 'changed_actual_interfaces': headers,
              'new_owner_actual_interfaces': owners, 'owner_loop_bodies_equal_except_definition_name': True,
              'limits': ['Extraction intake used the extract-only empty Lean placeholder; unchanged candidate552 proof was not compiled against this extraction.',
                         'Two actual owner loops arise from ext branching. Both need totality or an explicit body equality reduction; source has one textual loop.',
                         'The owner stop includes checked U32 +3 after mask255; bound <=258 must justify this addition in addition to index/wrapping-loop steps.',
                         'Exact equality of retained generated definitions supports reuse only. New/changed specifications, original obligation, axiom whitelist and round trip were not run.',
                         'B37 regressions stop proof work. No source or Lean proof file is modified by this audit.']}
    output = ROOT/'evidence/round26/route-b/b40-no-owner-extract-audit.json'
    assert not output.exists()
    output.write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps({'status': result['status'], 'files': files, 'preserved_definitions': len(preserved),
                      'source_changed': source_changed, 'source_new': source_new,
                      'owner_actual_loop_count': 2, 'proof_status': result['proof_status']}))


if __name__ == '__main__':
    main()
