"""Isolate public652 A flattened-price consumer onto exact original552, no other source changes."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib
import json
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT/'references/round24-public-552'
REFERENCE = ROOT/'references/round26-public-652'
NAME = 'r26-b-552-a-flatten'
HELPERS = ['a_fill', 'a_dp_fill', 'a_dp_min', 'a_dp_recs']


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def build():
    raw = (BASE/'parse.rs').read_bytes()
    assert sha(raw) == '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'
    reference = (REFERENCE/'parse.rs').read_bytes()
    assert sha(reference) == '20992b6048110ad2837e8e0006936e1539a20d223031b838a7815517e2859d71'
    old, ref = raw.decode(), reference.decode()
    fn = importlib.import_module('prepare-round24-extract-repro').fn
    for dep in ['a_slot_of', 'a_store_choice']:
        assert fn(old, dep) == fn(ref, dep), dep
    before, after = fn(old, 'a_dp_pass'), fn(ref, 'a_dp_pass')
    source = old.replace(before, after, 1)
    helpers = '\n// R26 isolated A consumer closure from public652; original author retained in manifest.\n'
    for name in HELPERS:
        assert 'pub fn '+name+'(' not in old
        helpers += ('#[inline(never)]\n' if name=='a_dp_recs' else '#[inline(always)]\n') + fn(ref, name)+'\n'
    source += helpers
    importlib.import_module('r26-b-fix-shared-cache').spans(source)
    assert source[:-len(helpers)].replace(after, before, 1).encode() == raw
    proof = (BASE/'Parse.lean').read_bytes()
    rust = source.encode()
    manifest = {'candidate': NAME, 'parent': 'public552', 'source_component': 'public652 A DP helper closure',
                'written_utc': datetime.now(timezone.utc).isoformat(), 'hashes': {'parse.rs': sha(rust), 'Parse.lean': sha(proof)},
                'source_audit': {'original_function_changed': 'a_dp_pass', 'new_helpers': HELPERS,
                                 'preserved': 'All matcher/tree/word8/D/route/config/fitter/emitter source bytes unchanged.',
                                 'full_source_reversal_restores_parent_bytes': True,
                                 'component_exact_function_bytes_equal_652': True},
                'mechanism': 'Actual per-position base/dist fill into two1024U32 scratch arrays, overshoot at most7 and mask final lanes, one complete packed scan with winner-length owner lookup. Odd records/near tail retain original record reducer. No block extrema/RMQ or new search edges.',
                'different_from_R18_AW': 'AW kept future cost min/max/position block cache and segmented constant lc queries. This uses no cost extrema cache: flatten distance bases and owners per current position, preserving differing prices in one scan.',
                'costs_retained': '8192byte scratch initialization, every fill including odd fallback work, overshoot stores, rounded masked reads, map lookup, original sampled/full fitting and original encoder.',
                'attribution': {'original_parent_receipt': 'references/round24-public-552/source-receipt.json',
                                'parent_author_hotkey': '5FnYJUitGUNdNyWAB7YnjoYoacLsd7TKxeAND4eYyiFVBP8q',
                                'component_receipt': 'references/round26-public-652/source-receipt.json',
                                'component_author_hotkey': '5EZCsCZ3rxSS5wkhmeZvCULREPMvC99gvhuoYAFN4Hv2PPzL'},
                'proof_status': 'DRAFT_PARENT_PROOF_UNCHANGED; source652 proof is reference only, new exact extraction/migration/fullgate required.',
                'semantic_status': 'UNKNOWN: original28 encoder and actual-call full cost/ch equality observer first.',
                'performance_status': 'UNKNOWN: whole652 formal metrics do not isolate this component; no assumed gain.', 'formal_submission_sent': False}
    assert len(rust) <= 524288 and len(proof) <= 524288
    return rust, proof, manifest


def main():
    folder = ROOT/'candidates'/NAME
    assert not folder.exists()
    rust, proof, manifest = build()
    folder.mkdir()
    (folder/'parse.rs').write_bytes(rust)
    (folder/'Parse.lean').write_bytes(proof)
    (folder/'manifest.json').write_text(json.dumps(manifest, indent=2)+'\n')
    print(json.dumps({'candidate': NAME, 'hashes': manifest['hashes'], 'source_audit': manifest['source_audit']}))


if __name__ == '__main__':
    main()
