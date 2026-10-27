"""Verify and extract an actual wide entry's same-object caller evidence, read only."""
from pathlib import Path
from collections import deque
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json,re
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
CS=HERE.parent.parent
sha=lambda b:hashlib.sha256(b).hexdigest()
sp=importlib.util.spec_from_file_location('old_audit',HERE/'astra-cross-codegen-audit.py')
old=importlib.util.module_from_spec(sp);sp.loader.exec_module(old)

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--capture',type=Path,required=True)
    ap.add_argument('--candidate',required=True)
    ap.add_argument('--seed',type=int,required=True)
    ap.add_argument('--run',type=int,required=True)
    a=ap.parse_args();cap=a.capture
    assert re.fullmatch(r'f01-r11-[a-z0-9-]+',a.candidate)
    source=(CS/a.candidate/'Kernel.lean').read_bytes()
    manifest=json.loads((CS/a.candidate/'manifest.json').read_text(encoding='utf-8'))
    assert sha(source)==manifest['candidate_sha256']
    record=json.loads((cap/'capture-record.json').read_text(encoding='utf-8'))
    snapshot=json.loads((cap/'snapshot.json').read_text(encoding='utf-8'))
    assert source==(cap/'compiled-Submission.lean').read_bytes()
    assert sha(source)==record['kernel_sha256']
    for entry in snapshot['files']:
        raw=(cap/entry['artifact']).read_bytes()
        assert len(raw)==entry['bytes'] and sha(raw)==entry['sha256']
    rawc=(cap/'file-0-Submission.c').read_bytes()
    fs=old.functions(rawc.decode())
    starts=[n for n in fs if re.fullmatch(r'lp_competition_Submission_bmm(?:___redArg)?',n)]
    assert starts
    paths={s:[s] for s in starts};q=deque(starts)
    while q:
        node=q.popleft()
        for nxt in fs[node]['references']:
            if nxt in fs and nxt not in paths:
                paths[nxt]=paths[node]+[nxt];q.append(nxt)
    selected={n:{**v,'syntactic_reachable':n in paths,'reference_path':paths.get(n)}
              for n,v in fs.items() if 'R11Wide' in n or n in starts}
    assembly=[]
    for obj in record['disassembly']['objects']:
        assert obj['object_sha256'] in [e['sha256'] for e in snapshot['objects']]
        for entry in obj.get('symbols',[]):
            item=entry['assembly'];raw=(cap/item['artifact']).read_bytes()
            assert len(raw)==item['bytes'] and sha(raw)==item['sha256']
            if item['ok']:
                assembly.append({'symbol':entry['symbol'],'file':item['artifact'],
                    'sha256':item['sha256'],'object_sha256':obj['object_sha256'],
                    'size':entry['size_bytes'],'text':old.asm_symbol(raw.decode(),entry['symbol'])})
    rec={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'candidate':a.candidate,
         'candidate_sha256':sha(source),'run':a.run,'seed':a.seed,'C_sha256':sha(rawc),
         'capture_record_sha256':sha((cap/'capture-record.json').read_bytes()),
         'capture_path':str(cap),'snapshot':snapshot,'mode':record['mode'],
         'assembly_state':record['disassembly']['state'],'functions':selected,'assembly':assembly,
         'scope':'Exact frozen actual source and same original-gate statement object. Call/function-pointer graph is syntactic evidence, not runtime frequency or per-cell attribution. No recompile, benchmark modification or CI dispatch.'}
    output=HERE/f'astra-wide-codegen-{a.seed}.json'
    assert not output.exists(), 'Keep prior evidence immutable; choose exact new seed/output'
    output.write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    compact=[]
    for n,v in selected.items():
        if not v['syntactic_reachable'] or n.endswith('___boxed'):continue
        compact.append({'function':n,'line':v['line'],'bytes':v['bytes'],
            'calls':{k:c for k,c in v['calls'].items() if any(t in k for t in
                ['lean_apply','alloc','R11Wide','array_push','nat_div','nat_mod','Packed10_finish'])}})
    print(json.dumps({'output':str(output),'source_sha256':sha(source),
                      'selected_C_functions':len(selected),'asm_symbols':len(assembly),
                      'active_functions':compact},ensure_ascii=False))
if __name__=='__main__':main()
