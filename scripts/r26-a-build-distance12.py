"""One online emitter implementation of the already tested distance12 rule."""
from pathlib import Path
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'candidates/r25-astra-tiny-pc8-proof1'
OUT = ROOT / 'evidence/round26/route-a'
NAME = 'r26-a-tiny-distance12'
RUST = '5c20b99cf52ac8e2f047b4e2e83be974b1f9b1f21b23d54ccccb25c58b891f00'
LEAN = '3bd53694534c0114453a95c2f120d743fde3af233de88c00e1d5c30fe05ccdb8'
HELPER = '''// R26: use the inherited ET first-distance activation policy on the real folded span.
#[inline(always)]
pub fn r26_d12_emit(s: &[u8], out: &mut [u32], nt: usize, p: usize,
                    l: usize, d: usize, used: u32) -> (usize, usize, u32) {
    if et_take(l, 4, used, d) {
        let r = pc_put_match(s, out, nt, p, d, l);
        let mask = used | (1u32 << (et_dcode(d) % 32));
        (r.0, r.1, mask)
    } else {
        let end = p + l;
        let count = pc_flush(s, out, nt, p, end);
        (count, end, used)
    }
}

'''


def sha(raw): return hashlib.sha256(raw).hexdigest()
def dump(path, value): path.write_bytes((json.dumps(value, indent=2) + '\n').encode())


def generate():
    raw = (BASE / 'parse.rs').read_bytes(); lean = (BASE / 'Parse.lean').read_bytes()
    assert sha(raw) == RUST and sha(lean) == LEAN
    source = raw.decode()
    a = source.index('pub fn r25_tiny_pc_run1<')
    opening = source.index('{', a); b = opening + 1; depth = 1
    while depth:
        depth += (source[b] == '{') - (source[b] == '}'); b += 1
    body = source[a:b]
    init = '        let mut head = [0u32; H];'
    initialized = init + '\n        let mut used = 0u32;'
    old = '                let r = pc_put_match(input, out, b.0, b.1, d, b.2);'
    new = '                let r = r26_d12_emit(input, out, b.0, b.1, b.2, d, used);\n                used = r.2;'
    assert body.count(init) == body.count(old) == 1
    changed = body.replace(init, initialized).replace(old, new)
    text = source[:a] + changed + source[b:]
    marker = '#[inline(always)]\npub fn r25_tiny_pc_run1<const H: usize>'
    assert text.count(marker) == 1
    text = text.replace(marker, HELPER + marker)
    assert text.replace(HELPER, '', 1).replace(initialized, init, 1).replace(new, old, 1) == source
    assert len(text.encode()) <= 524288 and len(lean) <= 524288
    return text.encode(), lean


def main():
    predeclared = {
        'status': 'PREDECLARED_BEFORE_ONLINE_DISTANCE12_NATIVE',
        'gap': 'A1 frozen strong tokens with distance12 replay produced2300B rather than2155B, while D symbols fell23to13 and lookup comparisons7114to3355. Online fold history and real encoder costs are UNKNOWN. LL105vs106 and clone13965vs13874 warn that most LL work remains.',
        'change': 'Use existing et_take(l,4,used,d) after the actual tiny-PC fold. Accepted spans use original pc_put_match and activate et_dcode(d); rejected whole spans use original pc_flush. Monotone used is conservative history, not the final distance set. Only the existing tiny kernel changes.',
        'parent': 'candidates/r25-astra-tiny-pc8-proof1',
        'preserved': 'Exact originalstrong matcher/probe/lazy/head/H/record8/routes/fold. No641 helper transplant, sparse LL mask, A8/A7 combination, table or postpass.',
        'minimum_operation': 'Original28file native encoder/decode against strong, combo, public595/public514, then temporary original-encoder work observer on actual online tokens for tiny-config and inactive tiny-app. Bind hashes, compare all original outputs to native receipt, count real emitter acceptance/rejections and preserve fold-induced differences from offline replay.',
        'decision': 'Only retained useful quality together with substantial reduction in observed originalencoder work could justify paired totals; no automatic paired/proof. Poor native quality or unchanged costly LL work closes this single fixed rule. No activation threshold or LL mask sweep.',
        'cost_cap_runner_minutes': 12,
        'target_scale': 'Offline187Bgain againstcombo is .055655pp on public28; against current641only124B/.036905pp if transplanted identically, which is not assumed. This is a discrete encoder-cost component test, not a sufficient single5/10 candidate.',
        'proof': 'Copied gate-passed strongLean is UNADAPTED. Reuse ET.take_spec/dcode_spec and PC.flush/put_match under folded Dec/MatchAt. New helper must return decoded prefix at originalspanend with variable token count; used becomes a main-loop capture. No new all-input guarantee from parent gate.'
    }
    dump(OUT / 'cycle-a9-predeclared.json', predeclared)
    rust, lean = generate(); dest = ROOT / 'candidates' / NAME
    assert not dest.exists(); dest.mkdir()
    (dest / 'parse.rs').write_bytes(rust); (dest / 'Parse.lean').write_bytes(lean)
    hashes = {'parse.rs': sha(rust), 'Parse.lean': sha(lean)}
    manifest = {'candidate': NAME, 'parent': BASE.relative_to(ROOT).as_posix(), 'hashes': hashes,
                'parent_hashes': {'parse.rs': RUST, 'Parse.lean': LEAN},
                'attribution': {'parent_manifest': 'candidates/r25-astra-tiny-pc8-proof1/manifest.json', 'ownership': 'Derivative of the preserved public595/514/combo source and prior tiny-PC work. All original source headers retained.'},
                'mechanism': predeclared['change'], 'preserved': predeclared['preserved'],
                'proof_status': 'COPIED_STRONG_LEAN_UNADAPTED', 'native_quality': 'UNKNOWN', 'total_time': 'UNKNOWN', 'formal_submission_sent': False}
    dump(dest / 'manifest.json', manifest)
    entry = {'name': NAME, 'path': dest.relative_to(ROOT).as_posix(), 'control': False, 'hashes': hashes,
             'anchor': 'public595', 'comparison_baseline': 'strong', 'native_decode_reference': 'strong'}
    dump(OUT / 'distance12-entry.json', entry)
    dump(OUT / 'distance12-build-audit.json', {'status': 'VERIFIED_EXACT_SOURCE_REVERSAL_NOT_NATIVE', 'hashes': hashes,
                                             'new_helper': 1, 'new_mutable_state': 'used:u32 inside tiny kernel', 'proof_unchanged': True})
    template = json.loads((OUT / 'quality-a8-native.json').read_bytes())
    template.pop('r26_a_lazy_chain_counts', None)
    mandatory = [e for e in template['entries'] if e['name'] in ['probe3', 'r3-432-fast3', 'public432', 'public514']]
    def reference(name, path, formal=None):
        e = {'name': name, 'path': path, 'control': True, 'hashes': {f: sha((ROOT / path / f).read_bytes()) for f in ['parse.rs', 'Parse.lean']}, 'anchor': name if formal else 'public595'}
        if formal: e['formal_id'] = formal
        return e
    template['entries'] = mandatory + [reference('public595', 'references/round21-public-595', '595'), reference('combo', 'candidates/r22-595-chain-halfhead'), reference('strong', BASE.relative_to(ROOT).as_posix()), entry]
    names = [e['name'] for e in template['entries']]
    template.update(screen_orders=[names, names[::-1]], native_encoder_references=['public514', 'public595', 'combo', 'strong'],
                    r26_a_distance12_counts=True, snapshot_pages='evidence/round26/official-hour2/pareto-pages.json',
                    description=predeclared['gap'] + ' ' + predeclared['change'] + ' Actual online originalencoder and symbol work before any timing/proof allocation.')
    dump(OUT / 'quality-a9-native.json', template)
    print(json.dumps({'candidate': NAME, 'hashes': hashes}, indent=2))


if __name__ == '__main__': main()
