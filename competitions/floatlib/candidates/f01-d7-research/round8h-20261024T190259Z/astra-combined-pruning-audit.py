"""Replay every frozen deletion and inspect retained references independently.
No development helper is executed, no Lean/source/Git mutation occurs.
"""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
from time import monotonic
from collections import Counter
import re
import json

base=Path(__file__).resolve().parent;root=base.parents[4];start=monotonic()
def h(b): return sha256(b).hexdigest()
def mask(s):
    chars=list(s);i=0;depth=0;string=False;line=False
    while i<len(s):
        if line:
            if s[i]=='\n':line=False
            else:chars[i]=' '
            i+=1;continue
        if depth:
            if s.startswith('/-',i):chars[i:i+2]=[' ',' '];depth+=1;i+=2
            elif s.startswith('-/',i):chars[i:i+2]=[' ',' '];depth-=1;i+=2
            else:
                if s[i]!='\n':chars[i]=' '
                i+=1
            continue
        if string:
            if s[i]=='\\' and i+1<len(s):chars[i:i+2]=[' ',' '];i+=2
            else:
                if s[i]=='"':string=False
                if s[i]!='\n':chars[i]=' '
                i+=1
            continue
        if s.startswith('--',i):chars[i:i+2]=[' ',' '];line=True;i+=2
        elif s.startswith('/-',i):chars[i:i+2]=[' ',' '];depth=1;i+=2
        elif s[i]=='"':chars[i]=' ';string=True;i+=1
        else:i+=1
    assert depth==0 and not string
    return ''.join(chars)

stages=[];current=None
for name in ['development-proof-fixedpoint-inventory1.json',
             'development-unreferenced-declarations-inventory1.json',
             'development-local-dependency-graph1.json']:
    record=json.loads((base/name).read_bytes())
    if current is None:current=(root/record['source']).read_bytes()
    assert h(current)==record['source_sha256']
    rounds=record.get('rounds',[dict(rows=record.get('removed',[]),parent_sha256=record['source_sha256'],result_sha256=record['result_sha256'])])
    for phase in rounds:
        assert h(current)==phase['parent_sha256'];text=current.decode('utf-8');out=[];pos=0
        for row in phase['rows']:
            lo,hi=row['character_start'],row['character_end'];piece=text[lo:hi].encode('utf-8')
            assert lo>=pos and h(piece)==row['sha256'] and len(piece)==row['bytes']
            out.append(text[pos:lo]);pos=hi
        out.append(text[pos:]);current=''.join(out).encode('utf-8')
        assert h(current)==phase['result_sha256']
    assert current==(root/record['result']).read_bytes()
    stages.append(dict(record=name,sha256=record['result_sha256'],bytes=len(current)))
    assert monotonic()-start<4.0

graph=json.loads((base/'development-local-dependency-graph1.json').read_bytes())
orphan=b'/-- Unlike the old NormalBand helper, this covers every normal raw exponent1..254. -/\n'
marker=orphan+b'end Submission.R14NatNormal'
assert current.count(marker)==1
final=current.replace(marker,b'end Submission.R14NatNormal')
candidate=root/'competitions/floatlib/candidates/f01-r14-dev-allword-combined1/Kernel.lean'
assert final==candidate.read_bytes()
assert h(final)=='393473afe5cbcd5a360a30eff7e6729f6f591a7a427aedd101ad6ef9c8bf9c7c'
clean=mask(final.decode('utf-8'))
tokens=re.findall(r"[A-Za-z_][A-Za-z0-9_']*(?:\.[A-Za-z_][A-Za-z0-9_']*)*",clean)
counts=Counter(tokens);suffixes=Counter()
for token,count in counts.items():
    parts=token.split('.')
    for i in range(len(parts)):suffixes['.'.join(parts[i:])]+=count
dead={r['name']:r for r in graph['removed']};live=set(graph['edges'])-dead.keys()
missing_full=[name for name in dead if counts[name]]
partial=[];unique=[]
live_leaves={n.rsplit('.',1)[-1] for n in live}
for name,row in dead.items():
    components=name.split('.');leaf=components[-1]
    for i in range(1,len(components)-1):
        suffix='.'.join(components[i:])
        if counts[suffix]:partial.append(dict(removed=name,token=suffix,count=counts[suffix]))
    if leaf not in live_leaves and counts[leaf]:
        unique.append(dict(removed=name,token=leaf,count=counts[leaf]))
assert not missing_full
source=(root/graph['source']).read_text(encoding='utf-8')
clean_before=mask(source)
prime_decls=re.findall(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:private\s+|protected\s+)?(?:def|abbrev|theorem|lemma)\s+([\w.]+\x27+)",clean_before)
search=re.findall(r'(?<!\w)(?:exact\?|apply\?|simp\?|library_search\b|aesop\b|solve_by_elim\b|grind\b)',clean_before)
other_commands=re.findall(r'(?m)^(?:export|notation|local|macro|syntax|elab|initialize|opaque|instance).*',clean_before)
assert not prime_decls and not search and not other_commands
assert all(r['kind'] not in ['instance','structure','inductive'] and r['attribute'] in ['', '@[inline]', '@[noinline]'] for r in graph['removed'])
record=dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),
    state='EXACT_DELETION_REPLAY_AND_REFERENCE_CENSUS_NOT_A_LEAN_PROOF',
    elapsed_seconds=monotonic()-start,budget_seconds=4.0,stages=stages,
    candidate_sha256=h(final),candidate_bytes=len(final),removed_graph_declarations=len(dead),
    all_slices_sha_match=True,only_final_unowned_duplicate_doc_removed=True,
    missing_fully_qualified_references=missing_full,partial_qualified_review=partial,
    unique_unqualified_review=unique,primed_declarations=prime_decls,environment_search_tactics=search,
    unmodeled_commands=other_commands,
    parser_notes='D graph prefers namespace direct resolution before suffix fallback; this is not a full Lean resolution model. Its boundary guard for exact?/apply? is not robust, but independent scan found neither. No trailing-prime declarations occur in this exact source. Future changed source must be rescanned.',
    scope='No removed instance/structure or registered attribute. Explicit reference census is only conservative static evidence. Original3934 actual compiler errors must still be repaired; every new graph-derived source needs exact compile/gate.',
    authority='Read-only D sources; only this astra receipt is written.')
record['partial_qualified_resolution']=[dict(token='NativeBridge.toModelNativeMul',
    context='R2W01c.native_mul_eq_of_raw_model_mul_eq in namespace R2W01c, actual source line1282',
    resolves_to='R2W01c.NativeBridge.toModelNativeMul',
    removed_homonym='Submission.NativeBridge.toModelNativeMul',
    conclusion='Resolved separate namespace; no concrete missing reference found.')]
assert 'R2W01c.NativeBridge.toModelNativeMul' in graph['edges']['R2W01c.native_mul_eq_of_raw_model_mul_eq']
record['audit_preflight_failure']='The initial comment-only marker appeared both before the retained decoder and before end. The audit was corrected to require the exact comment+end marker; no source was altered.'
Path(__file__).with_suffix('.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(record,ensure_ascii=False,indent=2))
