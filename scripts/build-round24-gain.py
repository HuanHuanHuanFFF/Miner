"""First loop: accept longer secondary matches only when estimated gain improves."""
from pathlib import Path
import importlib, json
ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round24'
w = importlib.import_module('build-round18-start')

def main():
    template = json.loads((ROOT / 'evidence/round23/depth-c-native.json').read_bytes())
    entries = [e for e in template['entries'] if e['name'] in ('probe3','r3-432-fast3','public432','public514','public595','public595-shadow','combo')]
    chain = w.control('chain3', 'candidates/r23-595-chain3', '595')
    chain.pop('formal_id'); chain['anchor'] = 'public595'; entries.append(chain)
    for name, parent, reference in [('r24-595-gain', 'r22-595-chain-halfhead', 'combo'), ('r24-595-chain3-gain', 'r23-595-chain3', 'chain3')]:
        p = ROOT / 'candidates' / parent
        rust, lean = [(p / f).read_text() for f in ('parse.rs','Parse.lean')]
        start = rust.index('pub fn pc_f_try('); end = rust.index('/// One chain step', start)
        body = rust[start:end]
        old = 'if m > l && m >= minl {'
        assert body.count(old) == 1
        body = body.replace(old, 'if m > l && m >= minl && pc_gain(m, d2) > pc_gain(l, d) {')
        rust = rust[:start] + body + rust[end:]
        entry = w.write_candidate(name, parent, rust, lean,
            'Preserve the validated longer-match and minimum-length conditions; require a positive estimated saving relative to the current match before adopting an older and potentially farther source. Existing routes, search depth, head size, encoder and content classifier remain unchanged.',
            'R23 added search capacity and saved bytes but slowed total compression. This changes acceptance economics on exact595-derived chained paths, not another depth or table sweep. Compare depth2 and depth3 to separate the effect from search capacity.',
            {'parent':str(p.relative_to(ROOT)), 'original_source':'references/round21-public-595/source-receipt.json', 'prior_evidence':'docs/rounds/round23.md', 'ownership':'Original source/Lean authors retained; pc_gain and generic matching proof are inherited.'})
        entry.update(anchor='public595', comparison_baseline=reference, native_decode_reference=reference)
        entries.append(entry)
    for k in list(template):
        if k.startswith('r23_'): del template[k]
    template.update(entries=entries, r24_mode='native', r24_expected_candidates=2,
        native_encoder_references=['public595','combo','chain3'], snapshot_pages='evidence/round24/official-start/pareto-pages.json',
        description='R24 A native full28-file original encoding/decode of cost-filter acceptance at two inherited depths. Byte screen only; no speed or complete proof claim.')
    ns = [e['name'] for e in entries]; template['screen_orders'] = [ns, ns[::-1]]
    plan = {'gap':'Prior combo has zero-share independent observations and control disagreement; chain3 saves more bytes but did not establish total-time gains. Need real quality/speed margin.',
        'change':'Cost-aware secondary-match acceptance at two existing depths; no added loop or delayed timing.',
        'minimum':'Original fixed encoder on all28 public files; byte/token identity, independent decode and exact source hashes. Baselines public595, actualcombo and actualchain3.',
        'decision':'If byte quality or meaningful tradeoff changes, measure original paired total time and replay each block. If identical outputs, do not call acceptance a quality improvement; inspect branch activity before further investment. Worse quality alone does not veto a possible speed tradeoff.',
        'cost_cap_runner_minutes':12, 'proof':'Current inherited Lean is only a draft for each new Rust; inspect f_try/gain totality before full exact gate.',
        'evidence':'evidence/round24/<run>/gain-a-native/diagnostics', 'status':'PREDECLARED'}
    for filename, value in [('gain-a-native.json',template),('preflight-a.json',plan)]:
        path = E / filename; assert not path.exists(); path.write_bytes((json.dumps(value,indent=2)+'\n').encode())
    route = (ROOT / 'scripts/check-round23-route.py').read_text().replace('round23','round24').replace('ROUND23','ROUND24').replace('R23','R24').replace("'23'","'24'").replace('==23','==24')
    (ROOT / 'scripts/check-round24-route.py').write_bytes(route.encode())
    print(json.dumps([e for e in entries if not e['control']]))
if __name__ == '__main__': main()
