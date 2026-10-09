"""Freeze two structurally distinct R14 probes from the exact public-gated parent."""
from pathlib import Path
import copy, hashlib, json

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round14'
P = ROOT / 'candidates/r13-514-abs15'

def save(p, v):
    p.write_bytes((json.dumps(v, indent=2, ensure_ascii=False) + '\n').encode())

def main():
    rust = (P/'parse.rs').read_text()
    lean = (P/'Parse.lean').read_bytes()
    old = json.loads((ROOT/'evidence/round13/confirm-aa.json').read_bytes())
    controls = [copy.deepcopy(e) for e in old['entries'] if e['control']]
    variants = []
    start = rust.index('pub fn pc_f_try(')
    end = rust.index('pub fn pc_f_deepen(', start)
    region = rust[start:end]
    needle = 'if m > l && m >= minl {'
    assert region.count(needle) == 1
    gain = rust[:start] + region.replace(needle, 'if m > l && m >= minl && pc_gain(m, d2) > pc_gain(l, d) {') + rust[end:]
    variants.append(('r14-514-chain-gain', gain,
        'Keep the nearer current match when an older, slightly longer match loses on the existing bit-saving estimate.',
        'R13 rescue-gain added a second search on initial misses and was too slow. This changes adoption in the already-executed PC chain search; no extra lookup or match extension.'))
    head = rust
    for row in (0, 1):
        needle = f'pub fn p125_row{row}(input:&[u8],out:&mut[u32])->usize{{pc_run1c::<32768>'
        assert head.count(needle) == 1
        head = head.replace(needle, needle.replace('32768', '16384'))
    variants.append(('r14-514-head14', head,
        'Halve only the shallow PC head table; retain the U16 predecessor window, full keys, chain depth and emission.',
        'The R1 enlarged-table result concerned a different parser. Here the gated shallow-chain parent has a 128KiB head plus64KiB links; smaller head trades collisions for cheaper initialization/cache. Real encoder bytes decide whether to spend on timing.'))
    entries = controls[:]
    for name, text, mechanism, difference in variants:
        dest = ROOT/'candidates'/name
        dest.mkdir(exist_ok=True)
        data = {'parse.rs': text.encode(), 'Parse.lean': lean}
        for f, b in data.items():
            assert not (dest/f).exists() or (dest/f).read_bytes() == b
            (dest/f).write_bytes(b)
        hashes = {f: hashlib.sha256(b).hexdigest() for f,b in data.items()}
        save(dest/'manifest.json', {'candidate': name, 'parent': 'r13-514-abs15',
            'formal_anchor_id': '514', 'comparison_baseline': 'r13-514-abs15', 'hashes': hashes,
            'attribution': json.loads((P/'manifest.json').read_bytes())['attribution'],
            'mechanism': mechanism, 'difference_from_old_work': difference,
            'proof_status': 'PARENT_PROOF_UNCOMPILED_FOR_NEW_RUST; no inherited gate',
            'performance_status': 'UNKNOWN', 'formal_submission_sent': False})
        entries.append({'name':name,'path':f'candidates/{name}','control':False,'anchor':'public514',
            'comparison_baseline':'r13-514-abs15','native_decode_reference':'r13-514-abs15','hashes':hashes})
    spec = {**old, 'entries':entries, 'snapshot_pages':'evidence/round14/official-start-2/pareto-pages.json',
        'screen_blocks':2,'screen_orders':[ [e['name'] for e in entries], [e['name'] for e in reversed(entries)] ],
        'extract_candidates':[], 'gate_candidates':[], 'research_synthetic_candidates':[],
        'native_only':True,'native_encoder':True,'native_encoder_references':['r13-514-abs15'],
        'description':'R14 diagnostic A: exact original encoder bytes and public decode for two new mechanisms; no timing/proof claim. A smaller or unchanged size permits paired full-time screening; increased size must have a plausible compensating speed budget.'}
    save(E/'probe-a-native.json', spec)
    print(json.dumps({'candidates':[v[0] for v in variants],'native_batch':'probe-a-native'}))

if __name__ == '__main__': main()
