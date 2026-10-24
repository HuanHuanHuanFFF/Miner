"""One p3/p4 column kernel on exact df5c; default verifies/dry-runs only."""
from pathlib import Path
from datetime import datetime, timezone
from collections import Counter, deque
import argparse
import hashlib
import importlib.util
import json
import re
import sys
sys.dont_write_bytecode = True

HERE = Path(__file__).resolve().parent
CS = HERE.parent
R12 = CS/'f01-d7-research/round6h-20261024T051445Z'
PARENT = CS/'f01-d12-scalar-combined/Kernel.lean'
EXPECTED = 'df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
ASSET = '9613168637d24b6aa59c41fb184a70c714c87402c93f22e621275843e7674f7e'
sha = lambda raw: hashlib.sha256(raw).hexdigest()


def module(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    obj = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(obj)
    return obj


def generate():
    raw = PARENT.read_bytes()
    assert sha(raw) == EXPECTED
    assert sha((CS/'f01-d7-width4-proof2/Kernel.lean').read_bytes()) == ASSET
    original = raw.decode()
    text = original
    ops = []
    def replace(old, new, label):
        nonlocal text
        assert text.count(old) == 1, (label, text.count(old))
        at = text.index(old)
        ops.append({'name': label, 'offset_in_previous_stage': at, 'before': old, 'after': new,
                    'before_sha256': sha(old.encode()), 'after_sha256': sha(new.encode())})
        text = text[:at]+new+text[at+len(old):]
    pieces = [R12/'astra-column4-assets.lean', R12/'astra-column4-writer.lean']
    addition = '\n'.join(p.read_bytes().decode().rstrip() for p in pieces)+'\n\n'
    anchor = 'def bmmBeforeUnderflowZero (batch m n p : Nat)'
    replace(anchor, addition+anchor, 'insert_minimal_F4_USize_current_finish_continuous_writer')
    old = '  else bmmBeforeR11Cross batch m n p A B\n'
    new = '''  else if h4 : (p=3 ∨ p=4) ∧ 4<n ∧ n<USize.size ∧ A.toArray.size<USize.size then
    Narrow4.core batch m n p A B
      (by rcases h4.1 with h|h <;> omega) (by rcases h4.1 with h|h <;> omega)
  else bmmBeforeR11Cross batch m n p A B
'''
    replace(old, new, 'only_n_gt4_p3_or4_after_existing_Cross_with_machine_bounds')
    old = '  · exact bmmBeforeR11Cross_spec batch m n p A B\n'
    new = '''  · split
    · rw [Narrow4.core_eq_reference]
      exact referenceBmm_spec batch m n p A B
    · exact bmmBeforeR11Cross_spec batch m n p A B
'''
    replace(old, new, 'close_exact_four_exported_spec_chain')
    inv = module('column4_inventory', CS/'f01-r8-combined-result-guard/build.py')
    parent_inventory = inv.declarations(original)
    full_inventory = inv.declarations(text)
    assert all(len(v) == 1 for v in full_inventory.values())
    masked = inv.strip_comments(text)
    assert not re.search(r'\b(?:aesop|grind|library_search|solve_by_elim|apply_rules)\b|\b(?:exact|apply|simp|simpa|simp_all)\?', masked)
    assert not re.search(r'(?m)^(?:mutual|(?:set_option|open|include|omit)\b[^\n]*\bin\s*)$', masked)
    counts = Counter(n.rsplit('.', 1)[-1] for n in full_inventory)
    boundary = re.compile(r'(?m)^(?:@\[[^\n]*\]\s*)?(?:private\s+)?(?:theorem|def|abbrev|end|namespace|structure|open|instance|attribute|set_option|section)\b')
    nodes = {}
    for m in re.finditer(r'(?m)^theorem ([A-Za-z_][A-Za-z0-9_]*)\b', masked):
        name = m[1]
        if name in ('add_spec', 'mul_spec', 'sum_spec', 'bmm_spec', 'repairDotStep_eq_original') or counts[name] != 1:
            continue
        full_names = [n for n in parent_inventory if n.rsplit('.', 1)[-1] == name]
        if len(full_names) != 1 or full_names[0].startswith(('Submission.DWordNaN.', 'Submission.ScalarNaN.')):
            continue
        last = len(masked[:m.start()].rstrip())
        trivia = text[last:m.start()]
        if '/--' in trivia or (last and masked[last-1] == ']'):
            continue
        stop = boundary.search(masked, m.end())
        if not stop:
            continue
        # Keep any following comment attached to its original next command.
        code_end = m.start()+len(masked[m.start():stop.start()].rstrip())
        line_end = text.find('\n', code_end)
        end = min(stop.start(), line_end+1 if line_end >= 0 else code_end)
        body = text[m.start():end]
        if any(x in body for x in ['/-', '--', '@[', 'attribute ', 'instance ', 'syntax ', 'notation ', 'macro ']):
            continue
        if original.count(body) != 1:
            continue  # Only unchanged parent proofs can enter the capacity pool.
        nodes[name] = {'qualified_name': full_names[0], 'start': m.start(), 'end': end, 'body': body}
    intervals = sorted((e['start'], e['end'], name) for name, e in nodes.items())
    assert all(a[1] <= b[0] for a, b in zip(intervals, intervals[1:]))
    incoming = {name: set() for name in nodes}
    external = {name: [] for name in nodes}
    for name in nodes:
        for ref in re.finditer(r'\b'+name+r'\b', text):
            owners = [owner for a, z, owner in intervals if a <= ref.start() < z]
            if owners:
                if owners[0] != name:
                    incoming[name].add(owners[0])
            else:
                external[name].append(text.count('\n', 0, ref.start())+1)
    keep = {n for n, refs in external.items() if refs}
    todo = deque(keep)
    while todo:
        caller = todo.popleft()
        for target, callers in incoming.items():
            if caller in callers and target not in keep:
                keep.add(target)
                todo.append(target)
    pool = set(nodes)-keep
    selected = set()
    before_prune_bytes = len(text.encode())
    before_prune_sha256 = sha(text.encode())
    # A small repair margin is planned; no source comments/runtime are removed.
    needed = max(0, before_prune_bytes-255500)
    recovered = 0
    while recovered < needed:
        ready = [n for n in pool-selected if incoming[n] <= selected]
        assert ready, ('closed comment-free proof capacity insufficient', needed, recovered)
        n = max(ready, key=lambda n: (len(nodes[n]['body'].encode()), n))
        selected.add(n)
        recovered += len(nodes[n]['body'].encode())
    pruning = []
    for name in sorted(selected, key=lambda n: nodes[n]['start'], reverse=True):
        e = nodes[name]
        assert not external[name] and incoming[name] <= selected
        pruning.append({'name': name, 'qualified_name': e['qualified_name'],
            'bytes': len(e['body'].encode()), 'sha256': sha(e['body'].encode()),
            'incoming_removed_callers': sorted(incoming[name]), 'incoming_retained_or_external': [],
            'attributes_comments': False, 'body': e['body']})
        replace(e['body'], '', 'remove_closed_unused_proof:'+e['qualified_name'])
    final = text.encode()
    inverse = text
    for op in reversed(ops):
        at = op['offset_in_previous_stage']
        assert inverse[at:at+len(op['after'])] == op['after']
        inverse = inverse[:at]+op['before']+inverse[at+len(op['after']):]
    assert inverse.encode() == raw
    budget = module('column4_comments', CS/'f01-d7-research/source-budget.py')
    cursor = 0
    for a, z in budget.comment_spans(raw):
        comment = raw[a:z]
        at = final.find(comment, cursor)
        assert at >= 0, 'Original comment or notice lost'
        cursor = at+len(comment)
    outer = raw[raw.rfind(b'namespace Submission\n'):]
    assert final.endswith(outer)
    assert final[-1039:] == raw[-1039:]
    for ns in ['Submission.R11CrossRows', 'Submission.DirectContinuous', 'Submission.UnderflowZero']:
        a = original.index('namespace '+ns+'\n')
        z = original.index('end '+ns, a)+len('end '+ns)
        assert original[a:z] in text, ns
    policy = module('column4_policy', CS/'f01-r11-crossrow-p2-pack12-proof2/build.py')
    policy.static_check(text)
    after_inventory = inv.declarations(text)
    removed = sorted(set(parent_inventory)-set(after_inventory))
    assert removed == sorted(e['qualified_name'] for e in pruning)
    assert all(len(v) == 1 for v in after_inventory.values())
    def header(src, declaration_lines):
        at = sum(len(line) for line in src.splitlines(keepends=True)[:declaration_lines[0]-1])
        return src[at:src.index(':=', at)]
    public = {}
    for name in ['add','add_spec','mul','mul_spec','sum','sum_spec','bmm','bmm_spec']:
        qualified = 'Submission.'+name
        before = header(original, parent_inventory[qualified])
        assert before == header(text, after_inventory[qualified])
        public[qualified] = {'type_header_unchanged': True, 'sha256': sha(before.encode())}
    assert len(final) <= 256000
    evidence = {'candidate': HERE.name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': sha(final),
        'candidate_bytes': len(final), 'size_margin': 256000-len(final), 'parent_sha256': EXPECTED,
        'parent_bytes': len(raw), 'asset_sha256': ASSET, 'created_at_utc': datetime.now(timezone.utc).isoformat(),
        'pre_prune_bytes': before_prune_bytes, 'proof_bytes_removed': recovered,
        'pre_prune_sha256': before_prune_sha256, 'eight_public_types': public,
        'proof_count_removed': len(pruning), 'static_policy': 'PASS', 'inverse_parent_exact': True,
        'all_original_comments_notices_retained': True, 'all_other_parent_bytes_unchanged': True,
        'outer_final_namespace_bytes': len(outer), 'outer_final_namespace_sha256': sha(outer),
        'last1039_parent_bytes_exact': True,
        'mechanism': 'Single n>4,p3/4 column4 route after existingp2Cross, originalmachinebounds andcompleteNatfallback; one4lane packetperrow, continuousoutput, currentPacked10 NaN-only finish/coldreplay.',
        'scope_change_from_history': 'Old961 globallyusedwidth4 withisFinite/fullreplay andoldrow output; this onlyp3/4,n>4 ondf5c withcurrentfinish andfusedcontinuousoutput. Historicalaggregate losses/wins are notmatchedslice evidence.',
        'historical_negative': {'run':39847080316,'seed':809,'vs_direct_small_whole':1.155963,'vs_direct_small_BMM':1.457068,'scope':'Differentglobalwidth4/oldfinish/oldwriter; retained negative, notdismissed orrenamed.'},
        'falsifier': 'Originalstatement thenfull+actualC: onepacked4 update, no hotforeign/readerboxing/spill, oneBprepare/resultperrow, noflatMap/rowTiles. Wholecost vsdf5c and6c; no promotion fromcounts oroldproof.',
        'proof_status': 'NOT_RUN', 'full_gate': 'NOT_RUN', 'performance': 'UNKNOWN',
        'validation_mode': 'full-gate', 'formal_submission': 'NOT_SUBMITTED',
        'build_script_sha256': sha(Path(__file__).read_bytes()),
        'inputs': [{'path': str(p), 'sha256': sha(p.read_bytes())} for p in pieces],
        'unused_proof_closure': 'Full new source including currentcold/converter andactualnewF4proofs analyzed asretainedroots. Noattributes, comments, attached docstrings, instances, runtime or8specsremoved. Statictextgraph only; Lean dependency acceptanceNOT_RUN.'}
    return final, evidence, ops, pruning, after_inventory


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--write', action='store_true')
    args = ap.parse_args()
    raw, evidence, ops, pruning, inventory = generate()
    if args.write:
        assert not (HERE/'Kernel.lean').exists()
        (HERE/'Kernel.lean').write_bytes(raw)
        for name, data in [('manifest.json', evidence),
            ('exact-inverse.json', {'parent_sha256': EXPECTED, 'inverse_exact': True, 'operations': ops}),
            ('decl-policy-review.json', {'candidate_sha256': sha(raw), 'static_policy': 'PASS',
                'unused_proofs': pruning, 'declarations': inventory,
                'mandatory_eight_types': evidence['eight_public_types'],
                'dependency_scope': evidence['unused_proof_closure']})]:
            (HERE/name).write_text(json.dumps(data, ensure_ascii=False, indent=2)+'\n', encoding='utf-8', newline='\n')
    elif (HERE/'Kernel.lean').exists():
        assert (HERE/'Kernel.lean').read_bytes() == raw
    else:
        (HERE/'dry-run.json').write_text(json.dumps(evidence, ensure_ascii=False, indent=2)+'\n', encoding='utf-8', newline='\n')
    print(json.dumps({k: evidence[k] for k in ['candidate_sha256','candidate_bytes','size_margin','pre_prune_bytes','proof_count_removed','proof_bytes_removed','static_policy']}, indent=2))


if __name__ == '__main__':
    main()
