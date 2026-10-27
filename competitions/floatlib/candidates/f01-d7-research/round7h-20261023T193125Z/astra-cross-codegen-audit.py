"""Read-only audit of exact914 CrossRows C and selected same-object assembly."""
from pathlib import Path
from datetime import datetime,timezone
from collections import Counter,deque
import hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
BASE=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40030638967/download-224ebe46fc3148e0be4d59757e4fcaf3/diagnostics/f01-d7-public-suite/public-suite'
CAP=BASE/'codegen/f01-r11-crossrow-p2-pack12-proof2/capture-7cbcce971eaf487cb4d51d5ddcaa8d07'
EXPECTED='5c5e7071927400ecd75d02d69b0ce62236a50a615912d99e7f8470a9ccf19c6b'
sha=lambda b:hashlib.sha256(b).hexdigest()
def functions(c):
    out={}
    for m in re.finditer(r'^(?:LEAN_EXPORT |static )[^\n]*?\b((?:lp_|_init_lp_)[A-Za-z0-9_]+)\([^;\n]*\)\s*\{',c,re.M):
        opening=c.index('{',m.start());j=opening+1;depth=1
        while depth:
            depth+=(c[j]=='{')-(c[j]=='}');j+=1
        full=c[m.start():j];body=c[opening+1:j-1]
        out[m[1]]={'header':c[m.start():opening].strip(),'line':c.count('\n',0,m.start())+1,
                   'bytes':len(full.encode()),'body':full,
                   'calls':dict(Counter(re.findall(r'\b((?:lean_|lp_)[A-Za-z0-9_]+)\s*\(',body))),
                   'references':sorted(set(re.findall(r'\b(lp_[A-Za-z0-9_]+)\b',body)))}
    return out
def asm_symbol(text,symbol):
    m=re.search(r'^([0-9a-f]+) <'+re.escape(symbol)+r'>:\s*$',text,re.M);assert m,symbol
    end=re.search(r'^Disassembly of section |^[0-9a-f]+ <[^>]+>:\s*$',text[m.end():],re.M)
    return text[m.start():m.end()+end.start() if end else len(text)].rstrip()+'\n'
def main():
    rec=json.loads((CAP/'capture-record.json').read_text());snap=json.loads((CAP/'snapshot.json').read_text())
    assert sha((CAP/'compiled-Submission.lean').read_bytes())==EXPECTED==rec['kernel_sha256']
    assert (CAP/'compiled-Submission.lean').read_bytes()==(ROOT/'competitions/floatlib/candidates/f01-r11-crossrow-p2-pack12-proof2/Kernel.lean').read_bytes()
    for e in snap['files']:
        b=(CAP/e['artifact']).read_bytes();assert len(b)==e['bytes'] and sha(b)==e['sha256']
    c=(CAP/'file-0-Submission.c').read_text();fs=functions(c)
    start='lp_competition_Submission_bmm';assert start in fs
    paths={start:[start]};q=deque([start])
    while q:
        n=q.popleft()
        for nxt in fs[n]['references']:
            if nxt in fs and nxt not in paths:paths[nxt]=paths[n]+[nxt];q.append(nxt)
    selected={}
    for n,v in fs.items():
        if 'R11CrossRows' in n or n=='lp_competition_Submission_Packed10_finish':
            selected[n]={**v,'syntactic_reachable_from_bmm':n in paths,'path':paths.get(n)}
    assemblies=[]
    for obj in rec['disassembly']['objects']:
        assert obj['object_sha256'] in [e['sha256'] for e in snap['objects']]
        for e in obj.get('symbols',[]):
            a=e['assembly'];b=(CAP/a['artifact']).read_bytes()
            assert sha(b)==a['sha256'] and len(b)==a['bytes']
            if a['ok']:
                snippet=asm_symbol(b.decode(),e['symbol'])
                assemblies.append({'symbol':e['symbol'],'source_asm':a['artifact'],'asm_sha256':a['sha256'],
                                   'object_sha256':obj['object_sha256'],'size_bytes':e['size_bytes'],'body':snippet})
    out={'at_utc':datetime.now(timezone.utc).isoformat(),'run':40030638967,'seed':914,'subject_sha256':EXPECTED,
         'C_file':str(CAP/'file-0-Submission.c'),'C_sha256':sha((CAP/'file-0-Submission.c').read_bytes()),
         'capture_record_sha256':sha((CAP/'capture-record.json').read_bytes()),'snapshot':snap,
         'stage':rec['mode'],'before_first_observed_score':rec['snapshot_finished_before_observed_score'],
         'C_functions':selected,'assembly':assemblies,'assembly_state':rec['disassembly']['state'],
         'scope':'Exact originalgate statement-side capture. C static call/function-pointer reachability is not dynamic execution or completecost attribution. Assembly snippets omit unrelated emptysection headers. No recompile or benchmark modified.'}
    (HERE/'astra-cross-codegen-914.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'C_functions':len(selected),'asm_symbols':len(assemblies),'C_sha256':out['C_sha256'],'stage':out['stage']}))
    for n,v in selected.items():
        if n.endswith('___boxed'):continue
        print(json.dumps({'name':n,'line':v['line'],'bytes':v['bytes'],'reachable':v['syntactic_reachable_from_bmm'],
                          'calls':{k:c for k,c in v['calls'].items() if any(w in k for w in ['float32','alloc','apply','Packed10_finish','R11CrossRows','nat_div','nat_mod','array_push'])}},ensure_ascii=False))
if __name__=='__main__':main()
