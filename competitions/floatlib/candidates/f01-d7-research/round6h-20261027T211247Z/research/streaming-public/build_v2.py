"""Keep D's fixed cost caller runtime, append proof-only bridge and public alias."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[6]
OLD = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round1h-20261027T103538Z/research'
COST = OUT.parents[1] / 'development-cost/BmmCost.lean.inc'

def sha(x):
    return hashlib.sha256(x).hexdigest()

def main():
    base = (OLD / 'terminal-proof/writer/full-matrix-proof-reproduction.lean').read_bytes()
    assert sha(base) == 'c3c3d6cb7fca720beebcf270036f076508abbe62ab40e722e37c8a3a7ffe2705'
    text = base.decode('utf-8')
    start = text.index('\ndef bmm (batch m n p : Nat)')
    end = text.index('\nend Submission', start)
    block = re.sub(r'\bbmm_spec\b', 'bmmBeforeR22Streaming_spec', text[start:end])
    block = re.sub(r'\bbmm\b', 'bmmBeforeR22Streaming', block)
    text = text[:start] + block + text[end:]
    cost_raw = COST.read_bytes()
    cost = cost_raw.decode('utf-8')
    assert cost.count('else Submission.bmm batch m n p A B') == 1
    cost = cost.replace('else Submission.bmm batch m n p A B',
                        'else Submission.bmmBeforeR22Streaming batch m n p A B')
    text += '\n\n' + cost
    for name in ['CostCallerProof.lean.inc', 'GuardedPublicEntry.lean.inc']:
        text += '\n\n' + (OUT / name).read_text(encoding='utf-8')
    dest = OUT / 'v2-guarded'
    dest.mkdir(exist_ok=True)
    pretrim = text.encode('utf-8')
    (dest / 'pretrim-Kernel.lean').write_bytes(pretrim)
    removed = []
    for namespace, name in [
        ('Submission.R21TerminalWriter', 'emit_finish_eq'),
        ('Submission.R21TerminalWriter', 'emit_two_rows_eq'),
        ('Submission.R21TerminalWriter', 'adjacent_A_base'),
        ('Submission.R21BatchPairTransport', 'odd_tail_valid'),
    ]:
        ns = text.index('\nnamespace ' + namespace)
        start = text.index('\ntheorem ' + name + ' ', ns)
        following = re.search(r'\n(?:theorem |end )', text[start+1:])
        assert following
        stop = start + 1 + following.start()
        fragment = text[start:stop]
        # These are proof-only historical interfaces and have no call sites.
        assert text.count(name) == 1, name
        removed.append({'root':namespace+'.'+name,'bytes':len(fragment.encode('utf-8')),
                        'sha256':sha(fragment.encode('utf-8'))})
        text = text[:start] + text[stop:]
    data = text.encode('utf-8')
    (dest / 'Kernel.lean').write_bytes(data)
    roots = json.loads((OLD / 'terminal-proof/writer/full-matrix-manifest.json').read_text(encoding='utf-8'))['roots']
    roots += ['Submission.bmmBeforeR22Streaming_spec']
    roots += ['Submission.R22StreamingCost.' + name for name in [
        'pairs_size', 'rows_size', 'output_size', 'rows_eq_batchStep',
        'output_eq_matrixOutput', 'core_eq_reference', 'guarded_spec']]
    removed_names = {r['root'] for r in removed}
    roots = [r for r in roots if r not in removed_names]
    assert len(roots) == len(set(roots))
    (dest / 'HelperAudit.lean.inc').write_text('import Submission\n\n' + '\n'.join(
        '#print axioms ' + r for r in roots) + '\n', encoding='utf-8', newline='\n')
    manifest = {
        'candidate': 'r22-streaming-public-v2-guarded',
        'created_at_utc': datetime.now(timezone.utc).isoformat(),
        'candidate_file':'Kernel.lean', 'candidate_sha256':sha(data), 'candidate_bytes':len(data),
        'parent_sha256':sha(base), 'proof_status':'NOT_RUN', 'performance':'UNKNOWN',
        'pretrim_sha256':sha(pretrim), 'pretrim_bytes':len(pretrim),
        'proof_only_unused_interfaces_removed':removed,
        'cost_runtime_source':str(COST.relative_to(ROOT)), 'cost_runtime_sha256':sha(cost_raw),
        'cost_runtime_bytes':len(cost_raw),
        'runtime_change_from_cost_source':'Only rename old Submission.bmm fallback to bmmBeforeR22Streaming; no guard, expression, or loop changes.',
        'eligibility':'1 < n AND 2 <= m AND 2 <= p; frozen by D before timing',
        'explicit_helper_audit':roots, 'helper_audit_required_endpoints':roots,
        'helper_audit_expected_count':len(roots), 'helper_audit_source_sha256':sha(data),
        'source_size_limit_pass':len(data)<=256000,
        'size_headroom_bytes':256000-len(data),
        'limits':['New proof composition NOT_RUN; no inherited 19-root PASS.',
                  'Original cost caller has no full proof until these new roots compile and replay.',
                  'Public wrapper and combined compilation still need complete gate and fresh timing; caller identity alone does not prove performance.'],
        'local_Lean':False, 'CI':False, 'Git':False,
    }
    (dest/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({k:manifest[k] for k in ['candidate_sha256','candidate_bytes','helper_audit_expected_count','size_headroom_bytes','cost_runtime_sha256']},ensure_ascii=False))

if __name__ == '__main__':
    main()
