"""Additional proof-space diagnostic: reuse exact aliases already in public53.

No tactic macro, runtime edit or proof removal. Not wired into frozen candidates.
"""
from pathlib import Path
import importlib.util,re,hashlib,json,datetime,argparse
HERE=Path(__file__).resolve().parent
COMP=HERE.parent/'source-budget/compact53.py'
COMP_SHA='cce4552bb4d9a52ae316a8c06a87675c7db049647064bcb0a74a91a22a75a480'
BASE=HERE.parents[1]/'competition-state/source-private/official-53.lean'
BASE_SHA='3dbe2f708299e6ee13e512a0f639eae681497ffaf01132330d92071581f7a9cb'

def process(raw):
    assert hashlib.sha256(COMP.read_bytes()).hexdigest()==COMP_SHA
    spec=importlib.util.spec_from_file_location('r28moreAliases',COMP);M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
    source,first=M.build(raw,strict_base=True);s=source.decode()
    header=next(l for l in s.splitlines() if l.startswith('open ExactRuntime'))
    aliases={}
    for ns,part in re.findall(r'open\s+([A-Za-z][A-Za-z0-9_.]*)\s+renaming\s+(.*?)(?=\s+open\s|\s+local\s|$)',header):
      for old,new in re.findall(r'([A-Za-z_][A-Za-z0-9_!?]*)\s*->\s*([^,\s]+)',part):
        full=ns+'.'+old
        if full not in aliases or len(new.encode())<len(aliases[full].encode()):aliases[full]=new
    commands=list(M.COMMAND.finditer(s));result=[];cursor=0;counts={};skipped=[];runtime_before=[]
    for i,c in enumerate(commands):
      end=commands[i+1].start() if i+1<len(commands) else len(s);chunk=s[c.start():end]
      result.append(s[cursor:c.start()]);cursor=end
      if c[1] in ['def','abbrev','structure','instance']:runtime_before.append(chunk)
      if c[1] in ['lemma','theorem']:
        available={}
        for old,new in aliases.items():
          # Conservative binder capture screen. Ambiguous chunks keep qualified spelling.
          shadow=re.search(r'(?:\b(?:let|have|fun|intro|rename_i)\s+|[λ∀∃]\s*|[({]\s*)'+re.escape(new)+r'(?=\s|:|\))',chunk)
          if shadow:skipped.append({'alias':new,'qualified':old});continue
          available[old]=new
        edits=[(a,b,t,available[t]) for a,b,t in M.tokens(chunk) if t in available]
        changed=chunk
        for a,b,old,new in reversed(edits):changed=changed[:a]+new+changed[b:];counts[old]=counts.get(old,0)+1
        # Inverse at the recorded positions, not a global expansion of old aliases.
        positions=[];delta=0
        for a,b,old,new in edits:positions.append((a+delta,a+delta+len(new),old));delta+=len(new)-(b-a)
        restored=changed
        for a,b,old in reversed(positions):restored=restored[:a]+old+restored[b:]
        assert restored==chunk
        chunk=changed
      result.append(chunk)
    result.append(s[cursor:]);out=''.join(result)
    cmds=list(M.COMMAND.finditer(out));runtime_after=[]
    for i,c in enumerate(cmds):
      if c[1] in ['def','abbrev','structure','instance']:runtime_after.append(out[c.start():cmds[i+1].start() if i+1<len(cmds) else len(out)])
    assert runtime_before==runtime_after
    report={'base_sha256':hashlib.sha256(raw).hexdigest(),'base_bytes':len(raw),'parent_compacted_sha256':hashlib.sha256(source).hexdigest(),'parent_compacted_bytes':len(source),'candidate_sha256':hashlib.sha256(out.encode()).hexdigest(),'candidate_bytes':len(out.encode()),'additional_saved_bytes':len(source)-len(out.encode()),'free_bytes':256000-len(out.encode()),'replacement_counts':counts,'skipped_alias_bindings':skipped,'runtime_chunks_byte_identical_after_parent_compaction':len(runtime_before),'proofs_deleted':0,'new_macros':0,'recorded_inverse_exact':True,'compile':'NOT_RUN','scope':'Existing scoped import aliases only in theorem/lemma text; no frozen candidate changed. This is source-space evidence, not accepted all12.'}
    return out.encode(),report

if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--base',type=Path,default=BASE);a=p.parse_args()
    data,report=process(a.base.read_bytes());out=HERE/'private/alias-reuse53.lean';out.write_bytes(data)
    report.update(at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),recipe_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),parent_recipe_sha256=COMP_SHA)
    (HERE/'alias-reuse53-receipt.json').write_text(json.dumps(report,indent=2,ensure_ascii=False)+'\n');print(json.dumps({k:v for k,v in report.items() if k not in ['replacement_counts','skipped_alias_bindings']},indent=2))
