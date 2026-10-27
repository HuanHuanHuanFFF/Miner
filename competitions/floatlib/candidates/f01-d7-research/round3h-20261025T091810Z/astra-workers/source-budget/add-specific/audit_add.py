"""Find only >=2 KiB plain-theorem slack in exact ADD draft; emit no candidate."""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
from time import monotonic
import importlib.util, json, re

HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('capacity', HERE.parent/'audit_budget.py')
capacity=importlib.util.module_from_spec(spec); spec.loader.exec_module(capacity)
ROOT=capacity.ROOT
SOURCE=ROOT/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/scalar-representation/next-add-u32/Kernel-add-native-high-draft1.lean'
EXPECTED='2f998811caa348ad7c0e66026b0d049c6ce0720549dd12622345777d24a1e13e'
def h(b): return sha256(b).hexdigest()

start=monotonic(); raw=SOURCE.read_bytes()
if h(raw)!=EXPECTED:
    print(json.dumps(dict(state='STOP_SOURCE_HASH_CHANGED',expected=EXPECTED,actual=h(raw),bytes=len(raw))))
    raise SystemExit(2)
assert len(raw)==255913
text=raw.decode('utf-8'); clean,comments,literals=capacity.lex(text)
assert not literals, 'Quoted strings or identifiers require more review before ref census'
hazards=re.findall(r'(?<!\w)(?:exact\?|apply\?|simp\?|rw\?|library_search\b|aesop\b|solve_by_elim\b|grind\b|run_tac\b|run_elab\b|mkConst\b|decl_name\b)',clean)
commands=re.findall(r'(?m)^\s*(?:attribute|export|notation|local\s+(?:notation|instance)|macro|syntax|elab|initialize)\b[^\n]*',clean)
assert not hazards and not commands, (hazards,commands)
available=[]
for row in capacity.declaration_rows(text,clean):
    piece=text[row['start']:row['end']]
    # Reject comment-bearing slices and any possible declaration/property registration.
    if '/-' in piece or '--' in piece or '@[' in piece: continue
    leaf=row['name'].split('.')[-1]
    references=list(re.finditer(r"(?<![\w'])"+re.escape(leaf)+r"(?![\w'])",clean))
    if len(references)!=1: continue  # also counts references to generated child names
    assert row['start'] <= references[0].start() < row['end']
    assert re.match(r'(?:private |protected )?(?:theorem|lemma) ',piece)
    row['independent_leaf_or_child_prefix_occurrences']=1
    row['previous_nonblank_line']=next((x for x in reversed(text[:row['start']].splitlines()) if x.strip()),'')
    row['header']=piece.splitlines()[0]
    available.append(row)
available.sort(key=lambda x:(-x['bytes'],x['start']))
selected=[]; recovery=0
for row in available:
    selected.append(row); recovery+=row['bytes']
    if recovery>=2048: break
assert recovery>=2048
assert sum(x['bytes'] for x in available[:len(selected)-1])<2048
selected.sort(key=lambda x:x['start'])
replay=capacity.remove_ranges(text,selected).encode('utf-8')
assert len(raw)-len(replay)==recovery
remaining=capacity.lex(replay.decode('utf-8'))[0]
for row in selected:
    leaf=row['name'].split('.')[-1]
    assert not re.search(r"(?<![\w'])"+re.escape(leaf)+r"(?![\w'])",remaining)
assert SOURCE.read_bytes()==raw, 'STOP_SOURCE_CHANGED_DURING_SCAN'
value=dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),state='STATIC_ADD_SPECIFIC_PLAN_NOT_LEAN_VALIDATED',
    source=SOURCE.relative_to(ROOT).as_posix(),source_sha256=h(raw),source_bytes=len(raw),
    target_recovery_bytes=2048,recovered_bytes=recovery,selected_declarations=len(selected),
    minimum_declaration_count_among_this_plain_unreferenced_pool=True,
    resulting_bytes=len(replay),resulting_sha256=h(replay),remaining_capacity_bytes=256000-len(replay),
    coordinate_unit='start/end are Unicode code point offsets in raw.decode(UTF-8); bytes and SHA cover re-encoded exact slices',
    selected=selected,all_slices_without_attributes_comments_or_runtime_definitions=True,
    environment_search_or_reflection_hazards=hazards,registration_commands=commands,
    original_source_still_unchanged=True,candidate_emitted=False,
    protected_names=sorted(capacity.PROTECTED),Lean='NOT_RUN',full_gate='NOT_RUN',tokens='UNKNOWN',
    scope='Current exact ADD source scanned afresh; single wave explicit reference census, no old deletion list applied. No source/CI/Git mutation.',
    remaining_risk='Static lexical scan is not Lean elaboration. New/repaired source hash invalidates this plan; exact slice replay and full original gate required.',
    elapsed_seconds=monotonic()-start)
assert value['elapsed_seconds']<4.5
(HERE/'budget.json').write_text(json.dumps(value,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(value,ensure_ascii=False,indent=2))
