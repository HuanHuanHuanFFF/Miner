"""Read-only staged reference census; never writes or patches Lean sources."""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import json
import re

here = Path(__file__).resolve().parent
repo = next(p for p in here.parents if (p/'AGENTS.md').is_file())
plan_path = repo/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/source-budget/budget.json'
plan = json.loads(plan_path.read_text())['common_plan']
base = (repo/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
assert sha256(base).hexdigest() == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
old_view = base.decode()
anchors = []
for stage in plan['rounds']:
    info = stage['sources']['b2']
    assert sha256(old_view.encode()).hexdigest() == info['parent_sha256']
    rows = []
    for row in info['rows']:
        fragment = old_view[row['start']:row['end']]
        assert sha256(fragment.encode()).hexdigest() == row['sha256']
        assert len(fragment.encode()) == row['bytes']
        assert re.match(r'^theorem\s+'+re.escape(row['name'])+r'\b',fragment)
        assert not any(x in fragment for x in ('@[','/-','--'))
        assert not re.search(r'(?m)^(?:namespace|section|end|attribute|instance|def|abbrev)\b',fragment)
        rows.append((row,fragment))
    anchors.append((stage['round'],rows))
    for row, fragment in sorted(rows,key=lambda x:x[0]['start'],reverse=True):
        old_view = old_view[:row['start']] + old_view[row['end']:]
    assert sha256(old_view.encode()).hexdigest() == info['result_sha256']
assert sum(len(rows) for _,rows in anchors) == 36
assert sum(row['bytes'] for _,rows in anchors for row,_ in rows) == 11990

targets = [('public_ADD_75da',here/'Kernel.lean','75da1c417a77ab03135897d0c4778f4dece80af3919084db9bd08dad80ae10fa'),
           ('public_combo_f7ba',repo/'competitions/floatlib/candidates/f01-r22-dev-nativecombo-public1/Kernel.lean','f7ba2ddb12939f518e5beb60daf927d9d9d80d24262edd740eefd5e8e917cc03')]
results = []
for label,path,expected in targets:
    raw = path.read_bytes()
    assert sha256(raw).hexdigest() == expected
    target_manifest = json.loads((path.parent/'manifest.json').read_text())
    audit_roots = target_manifest['explicit_helper_audit']
    audit_text = '\n'.join(audit_roots)
    original = raw.decode()
    current = original
    stages = []
    for number,rows in anchors:
        review = []
        accepted = []
        for row,fragment in rows:
            name = row['name']
            assert original.count(fragment) == 1 and current.count(fragment) == 1
            outside = current.replace(fragment,'',1)
            exact = re.compile(r"(?<![\w'])"+re.escape(name)+r"(?![\w'])")
            generated = re.compile(r"(?<![\w'])"+re.escape(name)+r"_[\w']+")
            references = exact.findall(outside) + generated.findall(outside)
            audit_refs = exact.findall(audit_text) + generated.findall(audit_text)
            eligible = not references and not audit_refs
            pos = original.index(fragment)
            review.append({'name':name,'bytes':row['bytes'],'anchor_sha256':row['sha256'],
                           'frozen_byte_start':len(original[:pos].encode()),
                           'frozen_byte_end':len(original[:pos].encode())+row['bytes'],
                           'remaining_leaf_or_dot_child_refs':len(exact.findall(outside)),
                           'remaining_underscore_generated_refs':generated.findall(outside),
                           'helper_root_refs':audit_refs,'eligible_static':eligible})
            if eligible: accepted.append((row,fragment))
        for row,fragment in accepted:
            current = current.replace(fragment,'',1)
        stages.append({'stage':number,'eligible_count':len(accepted),
                       'eligible_bytes':sum(row['bytes'] for row,_ in accepted),'rows':review})
    total = sum(s['eligible_bytes'] for s in stages)
    results.append({'name':label,'path':path.relative_to(repo).as_posix(),'sha256':expected,'bytes':len(raw),
                    'helper_roots':audit_roots,'helper_root_list_sha256':sha256(json.dumps(audit_roots,ensure_ascii=False).encode()).hexdigest(),
                    'current_headroom':256000-len(raw),'stages':stages,'eligible_total':total,
                    'prospective_headroom':256000-len(raw)+total,
                    'source_still_unchanged':sha256(path.read_bytes()).hexdigest()==expected})

out = {'checked_utc':datetime.now(timezone.utc).isoformat(),'first_tool_utc':'2026-10-28T01:25:48Z',
       'bound_utc':'2026-10-28T01:35:48Z','scope':'Historical common36/theorem-only plan, exact current source anchors and staged reference census; all intermediate deletion views exist only in memory',
       'historical_plan_sha256':sha256(plan_path.read_bytes()).hexdigest(),'historical_common_bytes':11990,
       'results':results,'Lean':'NOT_RUN','CI':'NOT_RUN','modified_Lean_source_emitted':False,
       'limitation':'No claim of elaboration equivalence or safe future indexed8 combination. New final source/helper/generated-name references require a new exact census before D applies any deletion.'}
(here/'capacity-precheck.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps([{'name':r['name'],'count':sum(s['eligible_count'] for s in r['stages']),'bytes':r['eligible_total'],'prospective_headroom':r['prospective_headroom'],'unchanged':r['source_still_unchanged']} for r in results]))
