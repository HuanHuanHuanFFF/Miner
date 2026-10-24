"""Read-only exact capture audit; writes only this round's astra evidence."""
from pathlib import Path
from datetime import datetime, timezone
from collections import Counter, deque
import argparse
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
CS = HERE.parent.parent
ROOT = CS.parents[2]
EXPECTED = 'da09fb59fa456b498af6bde48d54adcd37f85c4ba7df272163b184a2b83038c4'
sha = lambda data: hashlib.sha256(data).hexdigest()


def functions(c, artifact):
    found = {}
    pattern = r'^(?:LEAN_EXPORT |static )[^\n]*?\b((?:(?:l_|lp_|_init_l_|_init_lp_)[A-Za-z0-9_]+)|_lean_main)\([^;\n]*\)\s*\{'
    for m in re.finditer(pattern, c, re.M):
        start = c.index('{', m.start())
        end, depth = start+1, 1
        while depth:
            depth += (c[end] == '{') - (c[end] == '}')
            end += 1
        body = c[start+1:end-1]
        full = c[m.start():end]
        found[m[1]] = {'kind': 'function', 'artifact': artifact, 'line': c.count('\n', 0, m.start())+1,
            'header': c[m.start():start].strip(), 'bytes': len(full.encode()),
            'body_sha256': sha(full.encode()),
            'calls': dict(Counter(re.findall(r'\b((?:lean_|l_|lp_)[A-Za-z0-9_]+)\s*\(', body))),
            'references': sorted(set(re.findall(r'\b((?:l_|lp_)[A-Za-z0-9_]+)\b', body))),
            'closure_allocations': [line.strip() for line in body.splitlines() if 'lean_alloc_closure(' in line]}
        if m[1] == '_lean_main':
            found[m[1]]['main_entry_C'] = full
    # Static closure aliases are actual edges from MainFull to its kernel
    # arguments. Ignoring these would miss the immutable benchmark's bmm hook.
    for m in re.finditer(r'^static const (lean_closure_object|lean_object\*) ([A-Za-z_][A-Za-z0-9_]*) = ([^\n]+);$', c, re.M):
        name, value = m[2], m[3]
        if m[1] == 'lean_closure_object' and '.m_fun' not in value:
            continue
        refs = sorted(set(re.findall(r'\b((?:l_|lp_)[A-Za-z0-9_]+)\b', value)))
        if not refs:
            continue
        found[name] = {'kind': 'static_closure' if m[1] == 'lean_closure_object' else 'static_alias',
            'artifact': artifact, 'line': c.count('\n', 0, m.start())+1,
            'header': m[0], 'bytes': len(m[0].encode()), 'body_sha256': sha(m[0].encode()),
            'calls': {}, 'references': refs, 'closure_allocations': []}
    return found


def paths_from(fs, starts):
    paths = {start: [start] for start in starts}
    todo = deque(starts)
    while todo:
        name = todo.popleft()
        for nxt in fs[name]['references']:
            if nxt in fs and nxt not in paths:
                paths[nxt] = paths[name]+[nxt]
                todo.append(nxt)
    return paths


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--suite', type=Path, required=True)
    ap.add_argument('--run', type=int, required=True)
    args = ap.parse_args()
    suite = args.suite.resolve()
    summary = json.loads((suite/'summary.json').read_text(encoding='utf-8'))
    row = next(r for r in summary['results'] if r['candidate'] == 'f01-r12-column4-narrow')
    assert row['kernel_sha256'] == EXPECTED
    verdict_path = suite/row['verdict']
    assert sha(verdict_path.read_bytes()) == row['verdict_sha256']
    caps = list((suite/'codegen/f01-r12-column4-narrow').glob('capture-*'))
    assert len(caps) == 1, caps
    cap = caps[0]
    record = json.loads((cap/'capture-record.json').read_text(encoding='utf-8'))
    snap = json.loads((cap/'snapshot.json').read_text(encoding='utf-8'))
    assert record['kernel_sha256'] == EXPECTED
    compiled = cap/snap['compiled_source']['artifact']
    assert sha(compiled.read_bytes()) == EXPECTED
    assert compiled.read_bytes() == (CS/'f01-r12-column4-narrow/Kernel.lean').read_bytes()
    originals = []
    all_functions = {}
    for e in snap['files']:
        raw = (cap/e['artifact']).read_bytes()
        assert len(raw) == e['bytes'] and sha(raw) == e['sha256'], e
        originals.append(e)
        if e['kind'] == 'c':
            fs = functions(raw.decode(), e['artifact'])
            # Keep separate source inventories if a compiler emits same local name.
            for name, f in fs.items():
                f['source_module'] = e.get('module', 'Submission')
                if name in all_functions:
                    assert all_functions[name]['body_sha256'] == f['body_sha256'], name
                else:
                    all_functions[name] = f
    fs = all_functions
    entry = 'lp_competition_Submission_bmm'
    assert entry in fs
    overall = paths_from(fs, [entry])
    main_paths = paths_from(fs, ['_lean_main']) if '_lean_main' in fs else {}
    panel_entries = [n for n in overall if 'Narrow4_core' in n and '_spec__' not in n and '___boxed' not in n]
    assert panel_entries
    panel = paths_from(fs, panel_entries)
    groups = ['Packed4_', 'Packed4Index_', 'Narrow4_', 'Packed10Index_', 'RowStream_']
    chosen = {n: {**f, 'reachable_from_bmm': n in overall, 'bmm_path': overall.get(n),
        'reachable_from_Narrow4_core': n in panel, 'panel_path': panel.get(n)}
        for n, f in fs.items() if any(g in n for g in groups) or n == entry or f['source_module'] == 'MainFull'}
    asms = []
    for obj in record.get('disassembly', {}).get('objects', []):
        assert obj['object_sha256'] in [e['sha256'] for e in snap['objects']]
        for sym in obj.get('symbols', []):
            a = sym['assembly']
            raw = (cap/a['artifact']).read_bytes()
            assert len(raw) == a['bytes'] and sha(raw) == a['sha256']
            asms.append({'symbol': sym['symbol'], 'object_sha256': obj['object_sha256'],
                'size_bytes': sym['size_bytes'], 'assembly': a,
                'reachable_from_bmm': sym['symbol'] in overall,
                'reachable_from_Narrow4_core': sym['symbol'] in panel})
    candidates_for_manual_review = {
        'possible_map_functions_under_Narrow4_core': [n for n in panel if re.search(r'(?:Array|Vector)_map|_map[A-Z_]', n)],
        'Packed4_pack_functions_under_Narrow4_core': [n for n in panel if 'Packed4_packB' in n],
        'actual_Narrow4_core_functions': panel_entries,
        'panel_reachable_float_boxes': {n: fs[n]['calls']['lean_box_float32'] for n in panel if 'lean_box_float32' in fs[n]['calls']},
        'panel_reachable_apply_functions': {n: {k: v for k, v in fs[n]['calls'].items() if k.startswith('lean_apply_')} for n in panel if any(k.startswith('lean_apply_') for k in fs[n]['calls'])}}
    mainfull_comparison = {'parent_sha256': 'df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172',
        'parent_MainFull_machine_identity': 'UNKNOWN_UNLESS_SEPARATELY_CAPTURED_FOR_EXACT_DF5C',
        'scope': 'This capture proves actual candidate MainFull closure binding. Do not infer exact parent caller machine bytes from6c/59de/3ff4 oradd separate gains. Same-object Packed10Index andPacked4Index compare loop mechanisms only.'}
    out = {'at_utc': datetime.now(timezone.utc).isoformat(), 'run': args.run,
        'plan_seed': summary['seed'], 'source_commit': summary['source_commit'], 'candidate_sha256': EXPECTED,
        'capture': str(cap.relative_to(ROOT)), 'capture_record_sha256': sha((cap/'capture-record.json').read_bytes()),
        'snapshot_sha256': sha((cap/'snapshot.json').read_bytes()), 'verified_snapshot_files': originals,
        'summary_sha256': sha((suite/'summary.json').read_bytes()), 'verdict_sha256': row['verdict_sha256'],
        'full_gate': row['full_gate'], 'statement_pass': row['statement_pass'],
        'capture_mode': record['mode'], 'capture_state': record['state'], 'capture_errors': record['errors'],
        'r12_mainfull_capture': record.get('r12_mainfull_capture'),
        'capture_module_sha256': record['capture_module_sha256'],
        'gate_source_sha256': record['gate_source_sha256'],
        'snapshot_finished_before_observed_score': record.get('snapshot_finished_before_observed_score'),
        'mainfull_to_bmm_syntactic_path': main_paths.get(entry),
        'MainFull_comparison_with_retained': mainfull_comparison,
        'functions': chosen, 'assembly': asms, 'manual_review_anchors': candidates_for_manual_review,
        'scope': 'Exact original-gate C/object receipts. Call and closure-target reachability is syntactic, not dynamic frequency or allocator/RSS/time measurement. Map/box/apply anchors require path-level review, especially intended global nativeA-map Float32 boxes. Missing asm or physical final-release evidence remains UNKNOWN. No recompile or gate mutation.'}
    dest = HERE/f'astra-column4-codegen-{summary["seed"]}.json'
    dest.write_text(json.dumps(out, ensure_ascii=False, indent=2)+'\n', encoding='utf-8', newline='\n')
    print(json.dumps({'output': str(dest), 'functions': len(chosen), 'assembly_symbols': len(asms),
        'full_gate': row['full_gate'], 'manual_review_anchors': candidates_for_manual_review}, indent=2))


if __name__ == '__main__':
    main()
