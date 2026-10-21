"""Preserve newly public591 and isolate its shaping cost without changing final pairs."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib.util
import json

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round18'


def write_json(path, value):
    path.write_bytes((json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode())


def main():
    module_spec = importlib.util.spec_from_file_location('builder', ROOT / 'scripts/build-round18-start.py')
    builder = importlib.util.module_from_spec(module_spec)
    module_spec.loader.exec_module(builder)
    pages = json.loads((E / 'official-confirmation/pareto-pages.json').read_bytes())
    rows = {r['id']: r for page in pages for r in page['items']}
    receipts = json.loads((E / 'new-public-reference-check/receipt.json').read_bytes())
    for ident in ('590', '591'):
        receipt = next(r for r in receipts if r['submission_id'] == ident)
        raw_path = E / 'new-public-reference-check' / receipt['file']
        assert hashlib.sha256(raw_path.read_bytes()).hexdigest() == receipt['sha256']
        data = json.loads(raw_path.read_bytes())
        assert str(data['id']) == ident and receipt['status_code'] == 200
        source = ROOT / 'references' / ('round18-public-' + ident)
        assert not source.exists()
        source.mkdir()
        files = {}
        for field, name in (('parse_rs', 'parse.rs'), ('proof_lean', 'Parse.lean')):
            content = data[field].encode()
            assert 0 < len(content) <= 524288
            (source / name).write_bytes(content)
            files[name] = {'bytes': len(content), 'sha256': hashlib.sha256(content).hexdigest()}
        write_json(source / 'source-receipt.json', {
            'submission_id': ident, 'url': receipt['url'], 'author_hotkey': rows[ident]['hotkey'],
            'official_response': str(raw_path.relative_to(ROOT)).replace('\\', '/'),
            'official_response_sha256': receipt['sha256'], 'read_at_utc': receipt['read_at_utc'],
            'files': files, 'snapshot': pages[0]['context'],
            'official_gate_status': rows[ident]['gate_status'], 'official_admission': rows[ident]['admission'],
            'scope': 'Exact UTF8 fields from public source API; authorship retained. Published gate result is not a fresh local exact-pair gate.',
        })
        (source / 'PROVENANCE.md').write_bytes((
            f'# Official public submission {ident}\n\n'
            f'Source: {receipt["url"]}\n\n'
            f'Author hotkey: `{rows[ident]["hotkey"]}`. Original source/proof fields and headers retained. '
            'The original API response, exact hashes and published snapshot are linked by source-receipt.json. '
            'Reading this source does not establish new performance or proof for a derived candidate.\n'
        ).encode())
    source = ROOT / 'references/round18-public-591'
    rust = (source / 'parse.rs').read_text()
    proof = (source / 'Parse.lean').read_text()
    before = 'pub fn parse(input:&[u8],out:&mut[u32])->usize {let nt=SFbase(input,out);if TBon(input) {let plan=TBpick(input,out,nt);Z167(input,&plan,out)}else if SFenabled(input) {let plan=SFshape(input,out,nt);Z167(input,&plan,out)}else{nt}}'
    assert rust.count(before) == 1
    modified = rust.replace(before, 'pub fn parse(input:&[u8],out:&mut[u32])->usize { SFbase(input,out) }')
    entry = builder.write_candidate(
        'r18-591-base-diagnostic', 'public591', modified, proof,
        'Bypass the entire SF/TB post-shaping stage of newly public591; keep its base engines and routing exactly. Diagnostic endpoint only.',
        '591 differs materially from prior550 in base-engine routing, match cache width/depth and seam prices. Its current formal point is dominated. Isolate actual byte benefit and inclusive stage cost before any class selection or proof migration.',
        {'source': 'references/round18-public-591/source-receipt.json',
         'comparison_to550': 'evidence/round18/new-public-reference-check/591-vs-550-parse.rs.diff',
         'ownership': 'Official original author and all original code retained; this round only bypasses the outer shaping call.'})
    entry.update(anchor='public591', comparison_baseline='public591', native_decode_reference='public591')
    spec = json.loads((E / 'refine-q-native.json').read_bytes())
    spec['entries'] = [e for e in spec['entries'] if e.get('control')]
    spec['entries'].append(builder.control('public591', 'references/round18-public-591', '591'))
    spec['entries'].append(entry)
    spec['snapshot_pages'] = 'evidence/round18/official-confirmation/pareto-pages.json'
    spec['native_encoder_references'] = ['public586', 'public591']
    spec['r15_profile_entry'] = 'public591'
    spec['r15_profile_functions'] = ['parse', 'SFbase', 'SFshape', 'SFprev', 'SFsmallmatches', 'SFsolve', 'SFcost']
    spec['screen_orders'] = [[e['name'] for e in spec['entries']], [e['name'] for e in reversed(spec['entries'])]]
    spec['description'] = ('BB final bounded newly-public-reference diagnostic. Both final A/B exact gates and two-runner confirmations are complete and frozen. '
                           'Run original public encoder and independent decode on public591 and a SFbase-only diagnostic, with an unchanged591 function observer. '
                           'Maximum25runner-minutes; reserve collection and final report within01:32:51UTC. No parameter scan, final-pair replacement, formal upload or new payment action. '
                           'Decision: only a substantial same-family quality/cost opportunity justifies a later standard experiment; otherwise retain a source-backed alternative starting point. '
                           'Existing exact-length routing remains public author code, not a validated private-corpus transfer or newly adopted classifier.')
    write_json(E / 'shape-bb-native.json', spec)
    write_json(E / 'shape-bb-preflight.json', {
        'declared_at_utc': datetime.now(timezone.utc).isoformat(),
        'gap': 'Both reward targets remain unmet; known seven-file RF restoration mixtures never reach5% in the final observations.',
        'new_evidence': 'This research first retrieved official591 source at00:13:41UTC; the exact public-release time is unknown. Unlike586, it uses the550-derived SF shaping family with changed base routing and cache width/depth.',
        'material_change': 'Exactly one endpoint bypasses shaping; original591 remains unchanged for attribution and observation.',
        'minimum_operation': 'Full28-file original encoder/decode comparison plus inclusive unchanged-source function observer, one native CI.',
        'decision_boundary': 'Quantify bytes lost and stage cost. No native duration will be promoted to official total time. Stop if gains only occur under expensive shape or no credible5/15coordinate space remains.',
        'cost_cap_runner_minutes': 25,
        'fixed_deadline_utc': '2026-10-10T01:32:51+00:00',
        'reason_for_post_cutoff_diagnostic': 'New external source after the planned search cutoff; required final gates and confirmations already complete. One bounded diagnostic improves the requested alternative starting point without changing frozen final candidates.',
        'final_pairs_unchanged': True,
        'proof_status_of_derived_endpoint': 'DRAFT_UNCOMPILED; original591 proof is not evidence for the bypassed wrapper.',
    })
    budget_path = E / 'budget.json'
    budget = json.loads(budget_path.read_bytes())
    budget['post_cutoff_bounded_diagnostic'] = 'evidence/round18/shape-bb-preflight.json'
    write_json(budget_path, budget)
    print(json.dumps(entry))


if __name__ == '__main__':
    main()
