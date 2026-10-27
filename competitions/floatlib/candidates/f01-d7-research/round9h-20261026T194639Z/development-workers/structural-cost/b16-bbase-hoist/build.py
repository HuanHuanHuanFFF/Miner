"""Single pure-let candidate, source/static evidence only. Never reads D22."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re,difflib,ast
H=Path(__file__).resolve().parent;R=next(p for p in H.parents if(p/'competitions/floatlib/pins.json').is_file())
C=R/'competitions/floatlib/candidates';R19=C/'f01-d7-research/round9h-20261026T194639Z'
sha=lambda b:hashlib.sha256(b).hexdigest()
parent=C/'f01-r19-dev-column4-broad2/Kernel.lean';raw=parent.read_bytes();text=raw.decode()
assert sha(raw)=='bb058c75f59ca36b4952cffae0c943fd296de02cb3e83d164409736b0252c061'and len(raw)==255724
manifest_path=parent.parent/'manifest.json';manifest_bytes=manifest_path.read_bytes();manifest=json.loads(manifest_bytes)
assert manifest['candidate_sha256']==sha(raw)and manifest['statement_run']==40445341829
roots=manifest['explicit_helper_audit'];assert len(roots)==len(set(roots))==20
ns=text.index('namespace Submission.R19Column4Temporal',text.index('theorem runDot_pack_eq'))
a=text.index('@[inline] def group (PA : AC',ns);b=text.index('\ntheorem group_prefix',a)
old=text[a:b]
dot='  let v := runDot (b*m) n r PA (PB.get (ix b p bi g))'
address='(bi.val*n*p+4*g.val+j.val)'
assert old.count(dot)==old.count(address)==1
line='  let baseB := bi.val*n*p+4*g.val\n'
new=old.replace(dot,dot+'\n'+line.rstrip('\n'),1).replace(address,'(baseB+j.val)',1)
draft=text[:a]+new+text[b:];out=draft.encode()
assert len(out)<=256000 and draft.replace(new,old,1).encode()==raw
assert new.replace(line,'',1).replace('(baseB+j.val)',address,1)==old
assert text[:a]==draft[:a]and text[b:]==draft[a+len(new):]
# No proof statement/body or non-group declaration is edited.
assert text[text.index('theorem group_prefix',a):]==draft[draft.index('theorem group_prefix',a):]
def declarations(s):
 stack=[];namespace='';out={}
 for line_no,line_text in enumerate(s.splitlines(),1):
  m=re.match(r'^(namespace|section)\s+(\S+)',line_text)
  if m:
   kind,name=m.groups();stack.append((name,namespace))
   if kind=='namespace':namespace='.'.join(v for v in(namespace,name)if v)
   continue
  m=re.match(r'^end(?:\s+(\S+))?\s*$',line_text)
  if m:
   name,previous=stack.pop();assert m[1]is None or m[1]==name;namespace=previous;continue
  m=re.match(r'^(?:@\[[^\n]+\]\s+)?(def|abbrev|theorem|structure)\s+(\w+)',line_text)
  if m:
   key='.'.join(v for v in(namespace,m[2])if v);assert key not in out;out[key]=dict(line=line_no,kind=m[1],declaration=line_text)
 assert not stack
 return out
before=declarations(text);after=declarations(draft);assert list(before)==list(after)
root_index=[dict(name=n,before=before[n],after=after[n])for n in roots]
assert all(x['before']['declaration']==x['after']['declaration']for x in root_index)
run=C/'f01-mul-log2-proof1/ci-runs/40445341829';idx=run/'original-artifact-hashes.json';inventory=json.loads(idx.read_text());d=run/inventory['directory']
for name,row in inventory['files'].items():
 p=d/name;assert sha(p.read_bytes())==row['sha256']and p.stat().st_size==row['bytes']
assert {p.relative_to(d).as_posix()for p in d.rglob('*')if p.is_file()}==set(inventory['files'])
evidence=R19/'development-workers/anchor-323/b16-ci21-codegen/output-address-boundary/review.json'
review=json.loads(evidence.read_text());assert review['source_sha256']==sha(raw)and review['input_run']==40445341829
for f in review['bound_files']:
 p=R/f['path'];assert sha(p.read_bytes())==f['sha256']
assert review['decision']=='SCOPED_GO_GROUP_BBASE_CACHE_ONLY_NO_GO_R_TIMES_N_REWRITE_OR_THREE_REPEATED_MUL_CLAIM'
(H/'Kernel-bbase-hoist.draft.lean').write_bytes(out)
(H/'group-before.lean.txt').write_bytes(old.encode());(H/'group-after.lean.txt').write_bytes(new.encode())
for file,left,right,ln,rn in(('forward.patch',text,draft,'bb05/Kernel.lean','draft/Kernel.lean'),('inverse.patch',draft,text,'draft/Kernel.lean','bb05/Kernel.lean')):
 (H/file).write_bytes(''.join(difflib.unified_diff(left.splitlines(True),right.splitlines(True),fromfile=ln,tofile=rn)).encode())
(H/'roots.json').write_bytes((json.dumps(root_index,indent=2)+'\n').encode())
rec=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='ONE_PURE_LET_DRAFT_STATIC_PASS_LEAN_AND_CODEGEN_NOT_RUN',
 parent_sha256=sha(raw),parent_bytes=len(raw),draft_sha256=sha(out),draft_bytes=len(out),delta_bytes=len(out)-len(raw),remaining_source_bytes=256000-len(out),
 exact_inverse_to_bb05=True,pure_let_zeta_restores_group_exactly=True,all_proof_bytes_unchanged=True,declaration_names_order_unchanged=True,root_count=20,roots=roots,
 scope='Only R19Column4Temporal.group: bind baseB after runDot and before emit, callback uses baseB+j.val; baseA/loop/guard/fallback/finish/proof text untouched',
 placement='After runDot to avoid a new Nat baseB lifetime across dot. Existing bi/n/p/g liveness across dot is not claimed eliminated; after dot the emit callback uses the computed B-base instead of its address family. n/p/g remain needed elsewhere. No claim compiler retains this let.',
 CI21_original_index_sha256=sha(idx.read_bytes()),CI21_original_files_verified=len(inventory['files']),source_evidence_path=evidence.relative_to(R).as_posix(),source_evidence_sha256=sha(evidence.read_bytes()),
 compiler='NOT_RUN',new_module_replay_20roots='NOT_RUN',actual_C_ASM='NOT_RUN',speed='NOT_RUN',D22_or_confirmation_data_read=False)
(H/'receipt.json').write_bytes((json.dumps(rec,indent=2)+'\n').encode())
assert parent.read_bytes()==raw and manifest_path.read_bytes()==manifest_bytes
ast.parse(Path(__file__).read_text());print(json.dumps(rec,indent=2))
