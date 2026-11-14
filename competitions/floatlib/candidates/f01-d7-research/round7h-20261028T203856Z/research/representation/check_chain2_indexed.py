"""Reuse frozen word cases; observe reads and compare with exact modular sums."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
B=1<<64
MASK=B-1
M=1<<128
old=json.loads((HERE/'chain2-word-results.json').read_text())
assert old['source_sha256']=='88ab176703bfdd9636d243855f597202c1b6b10c68f6bec0ce370af6f6b69d35'
def indexed(get,start,count,al,ah,bl,bh):
    i=start
    remaining=count
    while remaining:
        q=get(i)
        lo=(al+q)&MASK
        hi=(ah+(MASK if q>=1<<63 else 0)+(lo<al))&MASK
        al,ah,bl,bh=bl,bh,lo,hi
        i+=1
        remaining-=1
    lo=(al+bl)&MASK
    hi=(ah+bh+(lo<al))&MASK
    return lo+hi*B
rows=[]
for case in old['cases']:
    terms=case['terms']
    for state in [(0,0,0,0),(MASK,MASK,1,0)]:
        start=5
        reads=[]
        def get(i):
            assert start<=i<start+len(terms)
            reads.append(i)
            return terms[i-start]&MASK
        got=indexed(get,start,len(terms),*state)
        al,ah,bl,bh=state
        expected=(al+ah*B+bl+bh*B+sum(terms))%M
        assert got==expected and reads==list(range(start,start+len(terms)))
        rows.append(dict(terms=terms,state=list(state),start=start,reads=reads,word=got,expected=expected))
src=HERE/'TwoChain128Indexed.lean.inc'
result=dict(observed_at_utc=datetime.now(timezone.utc).isoformat(),phase_first_utc='2026-10-29T01:19:21Z',
    source_sha256=hashlib.sha256(src.read_bytes()).hexdigest(),source_bytes=len(src.read_bytes()),
    cases=rows,case_count=len(rows),status='FIXED_PYTHON_WORD_AND_READ_TRACE_ONLY_LEAN_NOT_RUN',
    previous_cases_reused='chain2-word-results.json; no random/seed/tensor expansion',
    scope='Zero/odd/even lengths, offset reads, final carry and wrapped initial states. Exact integer modulo oracle.',
    limitations='No Lean execution, native ABI/closure/codegen/boxing observation or timing; no new CI queue.')
(HERE/'chain2-indexed-word-results.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps(dict(source_sha256=result['source_sha256'],source_bytes=result['source_bytes'],
    fixed_checks=len(rows),all_reads_exactly_once_in_order=True,all_words_match=True,status=result['status'])))
