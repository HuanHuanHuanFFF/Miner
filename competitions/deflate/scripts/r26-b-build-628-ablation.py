"""Freeze the public628 E/RF 2x2 ablation; local source checks only."""
from pathlib import Path
import argparse
import datetime as dt
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = ROOT / 'evidence/round26/route-b'
BASE = ROOT / 'references/round25-public-628'
EXPECTED = {
    'parse.rs': '784e02703c98a32f85753cae4f3b62aea3f505d91088869f327e0ad646629c14',
    'Parse.lean': '7c909191f2801e76ac5080966d6df5339191ce48a97a16a3e66ee2a0ca4c636e',
}

HEADER = '''theorem parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
 (hlen : input.length ≤ out.length) :
 slot.parse input out ⦃ fun r => r.1.val ≤ input.length ∧ r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
'''
BRANCH = '''   rintro ⟨n0, out1⟩ hr
   dsimp only at hr ⊢
   obtain ⟨hn, ho, hv⟩ := hr
   step*
   repeat' (split <;> step*)
   all_goals (first | assumption | (refine ⟨by assumption, by omega, ?_⟩; unfold LZ77.Valid; assumption))
'''


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def build():
    raw = {f: (BASE / f).read_bytes() for f in EXPECTED}
    assert {f: sha(b) for f, b in raw.items()} == EXPECTED
    source, proof = raw['parse.rs'].decode(), raw['Parse.lean'].decode()
    start = source.rindex('pub fn parse(input:&[u8],out:&mut[u32])->usize {')
    stop = source.index('\n}', start) + 2
    assert not source[stop:].strip()
    proof_start = proof.rindex(HEADER)
    proof_stop = proof.index('\nend Submission', proof_start)
    variants = {
        'r26-b-628-no-rf': (
            '''pub fn parse(input:&[u8],out:&mut[u32])->usize {
 if EPon(input){e_parse(input,out)}else{seed_parse(input,out)}
}''',
            HEADER + ''' rw [slot.parse]
 apply Std.WP.spec_bind (EPon_spec input)
 intro b _
 split
 · try simp only [bind_assoc_eq]
   exact e_parse_spec input out hlen
 · try simp only [bind_assoc_eq]
   exact seed_parse_spec input out hlen
''',
            'Retain original E/seed choice, remove the entire RF postpass.'),
        'r26-b-628-no-e': (
            '''pub fn parse(input:&[u8],out:&mut[u32])->usize {
 let n0=seed_parse(input,out); let cls=Z469(input);
 if HY_REFINE[cls%32]!=0 {let plan=refine(input,out,n0,HY_REFINE[cls%32]); if plan.len()>0{return Z271(input,&plan,out);}}
 n0
}''',
            HEADER + ''' rw [slot.parse]
 apply Std.WP.spec_bind (seed_parse_spec input out hlen)
''' + BRANCH,
            'Use original seed on every input, retain the original RF configuration and acceptance.'),
        'r26-b-628-seed': (
            '''pub fn parse(input:&[u8],out:&mut[u32])->usize {
 seed_parse(input,out)
}''',
            HEADER + ''' rw [slot.parse]
 exact seed_parse_spec input out hlen
''',
            'Remove both E and RF; preserve every original seed and SF function/configuration.'),
    }
    results = {}
    for name, (body, theorem, mechanism) in variants.items():
        rust = source[:start] + body + source[stop:]
        lean = proof[:proof_start] + theorem + proof[proof_stop:]
        assert rust[:start].encode() == raw['parse.rs'][:len(source[:start].encode())]
        assert lean[:proof_start].encode() == raw['Parse.lean'][:len(proof[:proof_start].encode())]
        assert rust.count('pub fn parse(') == source.count('pub fn parse(')
        assert rust[:start] + source[start:stop] + rust[start + len(body):] == source
        files = {'parse.rs': rust.encode(), 'Parse.lean': lean.encode()}
        assert all(0 < len(b) <= 524288 for b in files.values())
        manifest = {
            'candidate': name, 'parent': 'public628', 'parent_hashes': EXPECTED,
            'hashes': {f: sha(b) for f, b in files.items()},
            'mechanism': mechanism,
            'difference_from_old_work': 'First native factorial ablation of the newly public628 E and RF layers. This is mechanism diagnosis, not a claim that removing either component preserves quality or establishes reward.',
            'attribution': {
                'source_receipt': 'references/round25-public-628/source-receipt.json',
                'original_author_hotkey': '5DM8HSJ17XPGKYTERQUbQuhqWJm3RtpJqTSUH7Dn8m5MVuJ6',
                'underlying_seed_source': 'references/round24-public-609/source-receipt.json',
                'underlying_seed_author_hotkey': '5DPo51y7zmk2WfnkvU4MxAqw66ouW9KonrUGguLRWtPqiP9t',
                'retained': 'All original functions/constants before the final parse entry and all inherited proof declarations before final parse_spec are byte-preserved.',
            },
            'proof_status': 'DRAFT_FINAL_PARSE_SPEC_ADAPTED_UNCOMPILED',
            'proof_risk': 'Only final parse/parse_spec control flow changes. No new arrays, helper loops or token representation. Actual extraction, original obligation/axiom policy/fullgate remain mandatory; the unchanged original628 proof has not been locally validated.',
            'semantic_status': 'Intentional token differences permitted. Native roundtrip and original encoder are not yet run.',
            'performance_status': 'UNKNOWN', 'formal_submission_sent': False,
        }
        files['manifest.json'] = (json.dumps(manifest, indent=2, ensure_ascii=False) + '\n').encode()
        results[name] = (files, manifest)
    return results


def entry(name, path, control=True, formal_id=None):
    folder = ROOT / path
    row = {'name': name, 'path': path, 'control': control,
           'anchor': 'public628',
           'hashes': {f: sha((folder/f).read_bytes()) for f in EXPECTED}}
    if formal_id:
        row['formal_id'] = str(formal_id)
    if not control:
        row.update(comparison_baseline='public628', native_decode_reference='public628')
    return row


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    results = build()
    for name, (files, _) in results.items():
        folder = ROOT / 'candidates' / name
        if args.check:
            assert all((folder/f).read_bytes() == b for f, b in files.items()), name
        else:
            folder.mkdir(exist_ok=False)
            for f, b in files.items():
                (folder/f).write_bytes(b)
    if args.check:
        print(json.dumps({'status': 'VERIFIED_SOURCE_REVERSAL_AND_BYTE_IDENTITIES_ONLY',
                          'candidates': {n: m['hashes'] for n, (_,m) in results.items()}}))
        return
    EVIDENCE.mkdir(parents=True, exist_ok=True)
    entries = [entry('probe3', 'candidates/probe3', formal_id=427),
               entry('r3-432-fast3', 'candidates/r3-432-fast3', formal_id=453),
               entry('public432', 'references/round3-public-432', formal_id=432),
               entry('public514', 'references/round13-public-514', formal_id=514),
               entry('public628', BASE.relative_to(ROOT).as_posix(), formal_id=628),
               entry('r24-B', 'candidates/r24-609-fast-adaptive-proof1')]
    entries += [entry(n, 'candidates/'+n, False) for n in results]
    names = [e['name'] for e in entries]
    spec = {
        'entries': entries, 'snapshot_pages': 'evidence/round26/official-start/pareto-pages.json',
        'screen_blocks': 2, 'refine_blocks': 0, 'shortlist': 0,
        'gate_candidates': [], 'gate_limit': 0, 'extract_candidates': [],
        'retain_extracted_lean': True, 'synthetic_validation': False,
        'synthetic_reference_candidates': [], 'research_synthetic_candidates': [],
        'cpu_diagnostics': False, 'native_only': True, 'native_encoder': True,
        'native_encoder_references': ['public628', 'r24-B'],
        'r18_role': 'discovery', 'screen_orders': [names, names[::-1]],
        'description': 'R26 B first E/RF 2x2 mechanism diagnosis on original public628. Original pinned encoder and all28 input token/decode; exact B cost/quality baseline. Untimed native bytes first; only useful frontier tradeoffs receive paired total-time testing. All proofs draft, no formal result claim.',
    }
    (EVIDENCE/'628-ablation-native.json').write_bytes((json.dumps(spec, indent=2)+'\n').encode())
    plan = {
        'written_utc': dt.datetime.now(dt.timezone.utc).isoformat(),
        'gap_and_prior': 'R24 B is a verified different quality region but under current competition may be small. Public628 introduces RF exact token-block prices/DP plus E only on one old route; their actual marginal bytes and total costs on original28 inputs are UNKNOWN. R25 handoff explicitly left this diagnostic unrun.',
        'substantial_change': 'A 2x2 E/RF ablation, retaining complete original seed and all configurations; no inherited B duplicate-call savings, tinyPC/end4 or parameter sweep.',
        'minimum_operation': 'Native original encoder on original628, noRF, noE and seed, plus exact R24 B and validated514 encoder fixture. Keep per-file tokens/output/decode and hashes. Then only needed original paired total-time screen.',
        'decision_changing_outcomes': [
            'If RF makes meaningful real encoded improvement at a potentially useful coordinate, retain RF and diagnose its scan/DP/model cost before one bounded migration.',
            'If E accounts for quality on its existing input and bypass costs are material, inspect E internals rather than spread its narrow routing.',
            'If either component loses its internal-estimate advantage at the original encoder or costs swamp available frontier geometry, retain its negative result and pause that exact mechanism.',
            'If original628 offers useful point versus B despite being slower, pair its actual total time; do not reject on parent speed alone.',
        ],
        'runner_cost_cap_minutes': 20,
        'local_preflight': 'Hash-bound original receipt, isolated final-entry source reversal, unchanged preceding function/constants and proof declarations, official size cap, inherited native max6 program count.',
        'first_valid_test_dependency': 'Root commit/push/manual cloud dispatch; existing original encoder harness only. Native no timing/fullgate; full acceptance and frozen confirmation reserved by root.',
        'evidence': 'evidence/round26/route-b/628-ablation-native.json and cloud diagnostics/r13-encoder/encoder.json',
        'formal_submission': 'NOT_AUTHORIZED_OR_ATTEMPTED',
    }
    (EVIDENCE/'628-ablation-predeclared.json').write_bytes((json.dumps(plan, indent=2, ensure_ascii=False)+'\n').encode())
    print(json.dumps({'status': 'SOURCE_AND_NATIVE_SPEC_PREPARED_NOT_RUN', 'native_program_count': 6,
                      'spec': 'evidence/round26/route-b/628-ablation-native.json',
                      'candidates': {n: m['hashes'] for n, (_,m) in results.items()}}, indent=2))


if __name__ == '__main__':
    main()
