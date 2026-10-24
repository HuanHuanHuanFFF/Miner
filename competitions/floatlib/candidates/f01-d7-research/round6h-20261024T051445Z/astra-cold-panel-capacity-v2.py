"""Static cold/Panel integration and conservative proof closure preflight.

No Kernel is built or modified. Candidate theorem bodies are only considered
when globally unambiguous, untagged, comment-free and not official exports.
An incoming textual reference outside the candidate proof pool keeps a node;
retention propagates through its proof dependencies. Future cold/converter
fragments are also considered retained reference roots.
"""
from pathlib import Path
from collections import Counter, deque
from datetime import datetime, timezone
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
CS = HERE.parent.parent
SHA = 'a1ab536c08d666f8b3f5d848d3fb9341410f37e3072f0d1ee17dba7672e48abe'
sha = lambda raw: hashlib.sha256(raw).hexdigest()


def main():
    path = CS/'f01-r12-general-panel/Kernel.lean'
    raw = path.read_bytes()
    assert sha(raw) == SHA
    text = raw.decode()
    cold_path = CS/'f01-d12-scalar-cold-nan-select-proof2/Kernel.lean'
    cold = cold_path.read_bytes()
    assert sha(cold) == '3ff4eb8e3f9be968592a05f3d934b679705a3bbdeb655afb7596951611f36221'
    inverse = json.loads((CS/'f01-d12-scalar-cold-nan-select/exact-inverse.json').read_text(encoding='utf-8'))
    fixes = json.loads((CS/'f01-d12-scalar-cold-nan-select-proof2/exact-inverse.json').read_text(encoding='utf-8'))
    insertion = inverse['operations'][-1]['after']
    for e in fixes['operations']:
        assert insertion.count(e['before']) == 1
        insertion = insertion.replace(e['before'], e['after'])
    assert insertion.encode() in cold
    anchor = inverse['operations'][-1]['before']
    assert text.count(anchor) == 1 and 'TunedAdd' not in text
    cold_replacements = [
        ('add runtime cold branch', '  else ExecFloat.add x y\n', '  else ScalarNaN.add x y\n'),
        ('add cold proof leaf', '  · exact ExecFloat.Proof.add_eq_spec x y\n', '  · exact ScalarNaN.add_spec x y\n')]
    mul_op = inverse['operations'][2]
    gap = 'else FastMul.mul x y\n\ntheorem nativeMul_spec'
    before = mul_op['before'].replace(gap, gap.replace('\n\n', '\n'))
    after = mul_op['after'].replace('else ScalarNaN.mul x y\n\ntheorem nativeMul_spec',
                                  'else ScalarNaN.mul x y\ntheorem nativeMul_spec')
    cold_replacements.append(('nativeMul cold runtime and proof', before, after))
    cold_replacements.append(('repaired exact cold block insertion', anchor, insertion))
    operations = []
    for label, old, new in cold_replacements:
        assert text.count(old) == 1, label
        operations.append({'name': label, 'old_sha256': sha(old.encode()), 'new_sha256': sha(new.encode()),
            'old_bytes': len(old.encode()), 'new_bytes': len(new.encode()),
            'delta_bytes': len(new.encode())-len(old.encode()), 'start_character': text.index(old)})
    intervals = sorted((e['start_character'], e['start_character']+len(old))
        for e, (_, old, _) in zip(operations, cold_replacements))
    assert all(a[1] <= b[0] for a, b in zip(intervals, intervals[1:]))
    convert = json.loads((CS/'f01-d12-mul-existing-convert/exact-inverse.json').read_text(encoding='utf-8'))
    converter_donor = CS/'f01-d12-mul-existing-convert/Kernel.lean'
    converter_raw = converter_donor.read_bytes()
    converter_sha = '59de0e17223abebdd802bba98347ad8a4a7d6e90bfdca5ffd94bed3ad7005ce4'
    assert sha(converter_raw) == converter_sha == convert['candidate_sha256']
    assert sha(convert['after'].encode()) == convert['after_sha256']
    assert converter_raw.count(convert['after'].encode()) == 1
    baseline_raw = (CS/'f01-d11-bmm-combined-classifier/Kernel.lean').read_bytes()
    assert sha(baseline_raw) == convert['base_sha256'] == '6c2d394dd34e8854d0d44d5d6605c194ecb27c152a1768d236481fc03fa4277d'
    assert converter_raw.replace(convert['after'].encode(), convert['before'].encode()) == baseline_raw
    converter_after = convert['after'].replace(gap, gap.replace('\n\n', '\n'))
    converter_after = converter_after.replace('else FastMul.mul x y', 'else ScalarNaN.mul x y')
    converter_after = converter_after.replace('exact FastMul.mul_spec x y', 'exact ScalarNaN.mul_spec x y')
    assert len(converter_after.encode())-len(after.encode()) == 247
    implicit_search = re.findall(r'\b(?:aesop|grind|library_search)\b|\b(?:exact|apply|simp)\?', text)
    assert not implicit_search, implicit_search
    decl_counts = Counter(re.findall(r'(?m)^(?:@\[[^\n]*\]\s*)?(?:private\s+)?(?:theorem|def|abbrev|structure)\s+([A-Za-z_][A-Za-z0-9_]*)\b', text))
    boundary = re.compile(r'(?m)^(?:@\[[^\n]*\]\s*)?(?:private\s+)?(?:theorem|def|abbrev|end|namespace|structure|open|instance|attribute|set_option|section)\b')
    inventory = json.loads((CS/'f01-r12-general-panel/decl-policy-review.json').read_text(encoding='utf-8'))['all_new_inventory']
    nodes = {}
    for m in re.finditer(r'(?m)^theorem ([A-Za-z_][A-Za-z0-9_]*)\b', text):
        name = m[1]
        if name in ('add_spec', 'mul_spec', 'sum_spec', 'bmm_spec') or decl_counts[name] != 1:
            continue
        previous = text[:m.start()].rstrip().rsplit('\n', 1)[-1]
        if '@[' in previous or previous.rstrip().endswith(']'):
            continue
        stop = boundary.search(text, m.end())
        if not stop:
            continue
        body = text[m.start():stop.start()]
        if any(x in body for x in ['/-', '--', '@[', 'attribute ', 'instance ', 'notation ', 'syntax ', 'macro ']):
            continue
        full_names = [n for n in inventory if n.rsplit('.', 1)[-1] == name]
        if len(full_names) != 1:
            continue
        if full_names[0] == 'Submission.R7W05.repairDotStep_eq_original':
            continue  # Keep its attached87B product docstring on the original theorem.
        nodes[name] = {'qualified_name': full_names[0], 'start': m.start(), 'end': stop.start(), 'body': body}
    intervals = sorted((n['start'], n['end'], name) for name, n in nodes.items())
    assert all(a[1] <= b[0] for a, b in zip(intervals, intervals[1:]))
    incoming = {name: set() for name in nodes}
    external = {name: [] for name in nodes}
    # Future inserted cold proof and adapted converter references are mandatory
    # roots, even when an existing helper currently looks unused.
    extra = insertion + '\n' + converter_after
    for name in nodes:
        if re.search(r'\b'+name+r'\b', extra):
            external[name].append('future_cold_or_converter_fragment')
        for ref in re.finditer(r'\b'+name+r'\b', text):
            owners = [owner for a, z, owner in intervals if a <= ref.start() < z]
            if owners:
                if owners[0] != name:
                    incoming[name].add(owners[0])
            else:
                external[name].append(text.count('\n', 0, ref.start())+1)
    keep = {name for name, refs in external.items() if refs}
    queue = deque(keep)
    while queue:
        owner = queue.popleft()
        for target, callers in incoming.items():
            if owner in callers and target not in keep:
                keep.add(target)
                queue.append(target)
    removable = set(nodes)-keep
    entries = []
    for name in sorted(removable, key=lambda n: nodes[n]['start']):
        e = nodes[name]
        assert not external[name] and incoming[name] <= removable
        entries.append({'name': name, 'qualified_name': e['qualified_name'],
            'start_byte': len(text[:e['start']].encode()), 'end_byte': len(text[:e['end']].encode()),
            'bytes': len(e['body'].encode()), 'sha256': sha(e['body'].encode()), 'body': e['body'],
            'incoming_internal_callers_removed_together': sorted(incoming[name]),
            'incoming_retained_callers': [], 'incoming_external_references': [],
            'attributes_or_comments': False})
    total = sum(e['bytes'] for e in entries)
    delta = sum(e['delta_bytes'] for e in operations)
    rec = {'at_utc': datetime.now(timezone.utc).isoformat(), 'status': 'PREFLIGHT_ONLY_NO_KERNEL_BUILT_OR_MODIFIED',
        'script_sha256': sha(Path(__file__).read_bytes()), 'panel_sha256': SHA, 'cold_sha256': sha(cold),
        'version': 2, 'supersedes_for_current_use': 'astra-cold-panel-capacity.json (original42 preserved)',
        'converter_donor_sha256': converter_sha, 'converter_raw_after_occurrences': 1,
        'converter_exact_inverse_to_6c': True,
        'kept_docstring_and_theorem': 'Submission.R7W05.repairDotStep_eq_original,329B body and original87B docstring retained together',
        'cold_replacements': operations, 'cold_delta_bytes': delta,
        'cold_plus_panel_bytes_before_prune': len(raw)+delta,
        'three_mechanism_bytes_before_prune': len(raw)+delta+247,
        'capacity_double_count_prevented': 'No TunedAdd namespace exists in Panel; do not subtract cold-on6c15524B deletion again.',
        'proof_pool_nodes_considered': len(nodes), 'removable_proof_count': len(entries),
        'removable_proof_bytes': total, 'three_mechanism_bytes_if_full_pool_removed': len(raw)+delta+247-total,
        'three_mechanism_margin_if_full_pool_removed': 256000-(len(raw)+delta+247-total),
        'method': 'Conservative globally unambiguous untagged theorem pool. Text references outside pool and futurecold/converter fragments retain roots; dependency retention propagated. Removed set has no incoming retained references. Homonyms, source comments, attributes, mandatory specs and implicit-search candidates excluded.',
        'implicit_search_tokens': implicit_search, 'entries': entries,
        'scope': 'Only statically closed proof-capacity proposal on exacta1ab. No generated Kernel or source variant, no typecheck/full/timing for combination. Root must independently review the chosen exact deletion set, preserve every notice, build and verify the complete source. Removed statements may be useful future assets; original sources and receipts stay intact.'}
    (HERE/'astra-cold-panel-capacity-v2.json').write_text(json.dumps(rec, ensure_ascii=False, indent=2)+'\n', encoding='utf-8', newline='\n')
    print(json.dumps({k: rec[k] for k in ['cold_delta_bytes', 'three_mechanism_bytes_before_prune',
        'removable_proof_count', 'removable_proof_bytes', 'three_mechanism_bytes_if_full_pool_removed',
        'three_mechanism_margin_if_full_pool_removed']}, indent=2))


if __name__ == '__main__':
    main()
