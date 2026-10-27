"""Bind original CI13 failure; change only row_prefix proof, never runtime."""
from pathlib import Path
from datetime import datetime,timezone
import ast,difflib,hashlib,json,re

H=Path(__file__).resolve().parent
R=next(p for p in H.parents if(p/'competitions/floatlib/pins.json').is_file())
C=R/'competitions/floatlib/candidates';R19=C/'f01-d7-research/round9h-20261026T194639Z'
sha=lambda b:hashlib.sha256(b).hexdigest()
def bind(p):return dict(path=p.relative_to(R).as_posix(),bytes=p.stat().st_size,sha256=sha(p.read_bytes()))
run=C/'f01-mul-log2-proof1/ci-runs/40432634558';idx=run/'original-artifact-hashes.json'
x=json.loads(idx.read_text());directory=run/x['directory'];total=0
for name,row in x['files'].items():
    p=directory/name
    assert sha(p.read_bytes())==row['sha256'] and p.stat().st_size==row['bytes'],name
    total+=row['bytes']
assert {p.relative_to(directory).as_posix()for p in directory.rglob('*')if p.is_file()}==set(x['files'])
diag=directory/'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-dc-rawpair1'
log=diag/'full-build-output.txt';logtext=log.read_text()
error=re.search(r'error: work/Submission.lean:5993:2: Type mismatch: After simplification, term\n.*?(?=\nwarning:)',logtext,re.S)
assert error and logtext.count('error: work/Submission.lean:')==1
assert sha(log.read_bytes())=='1044bcd6d9e12d5108e5d466833c09eabd80047091f42aa8b5e37213053b6fb0'
source=C/'f01-r19-dev-dc-rawpair1/Kernel.lean';before=source.read_bytes();text=before.decode()
assert sha(before)=='8134696db068ceb0c969c7c896199e9c019a7cd375bfe34ab2712eb8d2464365'
assert (H.parent/'Kernel-dc-rawpair.draft.lean').read_bytes()==before
inputpath=directory/'diagnostics/f01-d7-public-suite/public-suite/inputs/f01-r19-dev-dc-rawpair1/Kernel.lean'
assert inputpath.read_bytes()==before
nsstart=text.index('namespace Submission.R19DCRawPair\n')
nsend=text.index('end Submission.R19DCRawPair',nsstart)
declstart=text.index('theorem row_prefix ',nsstart)
declend=text.index('\n\ndef output ',declstart)
old='  simpa only [row, group, hlast, Nat.add_mul, Nat.one_mul] using h'
assert text.count(old)==1 and old in text[declstart:declend]
new='''  have hgroup : group batch m n p A B r =
      groupFrom n (r.val * n) (r.val / m * n * p) p A.toArray B.toArray := by
    funext acc g
    rfl
  rw [hgroup] at h
  simpa only [row, hlast, Nat.add_mul, Nat.one_mul] using h'''
repaired=text.replace(old,new,1);after=repaired.encode()
assert repaired.replace(new,old,1).encode()==before
assert text[:declstart]==repaired[:declstart]
delta=len(new)-len(old)
assert text[declend:]==repaired[declend+delta:]
assert len(after)<=256000 and b'\r\n'not in after
# All runtime defs and the four public theorem declarations/bodies stay exact.
def runtime(s):
    starts=list(re.finditer(r'^(?:@\[[^\n]+\] )?(def|theorem|structure) (\w+)',s,re.M))
    return [(m.group(2),s[m.start():(starts[i+1].start()if i+1<len(starts)else len(s))])
            for i,m in enumerate(starts)if m.group(1)=='def']
assert runtime(text)==runtime(repaired)
decls=lambda s:re.findall(r'^(?:@\[[^\n]+\] )?(?:def|theorem|structure) (\w+)',s,re.M)
assert decls(text)==decls(repaired)
def publics(s):
    # The final visible declarations for each name belong to public Submission.
    out={}
    for name in('add_spec','mul_spec','sum_spec','bmm_spec'):
        matches=list(re.finditer(r'^theorem '+name+r'\b',s,re.M));m=matches[-1]
        nxt=re.search(r'^(?:theorem |def |end )',s[m.end():],re.M)
        out[name]=s[m.start():(m.end()+nxt.start()if nxt else len(s))]
    return out
assert publics(text)==publics(repaired)
manifest=json.loads((source.parent/'manifest.json').read_text());roots=manifest['explicit_helper_audit']
assert len(roots)==len(set(roots))==14
assert all(root.rsplit('.',1)[-1]in decls(repaired)for root in roots)
assert set('Submission.'+name for name in('add_spec','mul_spec','sum_spec','bmm_spec')).issubset(roots)
assert 'Submission.R19DCRawPair.row_prefix'in roots
def qualified_declarations(s):
    stack=[];namespace='';out={}
    for line_no,line in enumerate(s.splitlines(),1):
        m=re.match(r'^(namespace|section)\s+(\S+)',line)
        if m:
            kind,name=m.groups();stack.append((kind,name,namespace))
            if kind=='namespace':namespace='.'.join(v for v in(namespace,name)if v)
            continue
        m=re.match(r'^end(?:\s+(\S+))?\s*$',line)
        if m:
            kind,name,previous=stack.pop();assert m.group(1)is None or m.group(1)==name,(line_no,name,m.group(1))
            namespace=previous;continue
        m=re.match(r'^(?:@\[[^\n]+\]\s+)?(def|theorem|structure)\s+(\w+)',line)
        if m:
            kind,name=m.groups();key='.'.join(v for v in(namespace,name)if v)
            assert key not in out,key
            out[key]=dict(kind=kind,line=line_no,declaration=line)
    assert not stack
    return out
before_decl=qualified_declarations(text);after_decl=qualified_declarations(repaired)
assert list(before_decl)==list(after_decl)
assert all(after_decl[root]['kind']=='theorem'for root in roots)
root_index=[dict(name=root,before=before_decl[root],after=after_decl[root])for root in roots]
(H/'root-index.json').write_bytes((json.dumps(root_index,indent=2)+'\n').encode())
(H/'Kernel-dc-rawpair-repair1.draft.lean').write_bytes(after)
(H/'proof-patch.lean.txt').write_bytes((new+'\n').encode())
(H/'original-error.txt').write_bytes((error.group(0)+'\n').encode())
for name,a,b in(('forward.diff.txt',text,repaired),('inverse.diff.txt',repaired,text)):
    (H/name).write_bytes(''.join(difflib.unified_diff(a.splitlines(True),b.splitlines(True),fromfile='before',tofile='after')).encode())
rec=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='PROOF_ONLY_CALLBACK_EQUALITY_REPAIR_DRAFT_NOT_COMPILED',
 original_run=40432634558,original_commit='93fe24bf105ed11fd5e56f262adef82be9129b44',
 original_index=bind(idx),original_files_verified=len(x['files']),original_bytes_verified=total,
 original_log=bind(log),original_error_locations=[dict(line=5993,column=2,declaration='Submission.R19DCRawPair.row_prefix')],
 before_sha256=sha(before),before_bytes=len(before),after_sha256=sha(after),after_bytes=len(after),delta_bytes=len(after)-len(before),
 changed_scope='Only final proof step of R19DCRawPair.row_prefix; local hgroup function equality by funext+rfl, then transport existing fold invariant',
 runtime_definitions_byte_identical=True,domain_byte_identical=True,public_four_specs_byte_identical=True,
 declaration_names_and_order_unchanged=True,exact_inverse_to_8134=True,roots=roots,root_count=14,
 namespace_order='R19DCRawPair is after DirectContinuous and before original public dispatch; no namespace or public-target repair required',
 failure_cause='simp equation unfolding does not rewrite underapplied group callback. Existing h has group ... r; row target has fully specialized groupFrom. Their equality is a local function equality proved at full application.',
 new_source_Lean='NOT_RUN',whole_module_replay='NOT_RUN',axiom_audit='NOT_RUN',actual_selected_C='NOT_RUN',timing='NOT_RUN')
(H/'repair-receipt.json').write_bytes((json.dumps(rec,indent=2)+'\n').encode())
ast.parse(Path(__file__).read_text())
print(json.dumps(rec,indent=2))
