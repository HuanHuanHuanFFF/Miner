"""One Cross+Wide composition. Dry-run only until an exact reviewed allowlist exists."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,base64,hashlib,importlib.util,json,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
CS=HERE.parent
RESEARCH=CS/'f01-d7-research/round7h-20261023T193125Z'
WIDE=CS/'f01-r11-wide4-inline-proof3/Kernel.lean'
CROSS=CS/'f01-r11-crossrow-p2-pack12-proof2/Kernel.lean'
WIDE_SHA='28b819120cd3aaa1f19038f66042a9ceffe0c9329baab20fe223e98d151ce00b'
CROSS_SHA='5c5e7071927400ecd75d02d69b0ce62236a50a615912d99e7f8470a9ccf19c6b'
sha=lambda b:hashlib.sha256(b).hexdigest()
OUTER_MARK=b'namespace Submission\nopen FloatLib.Floats Competition\n\n/-- Both short-circuiting scans'
OUTER_SHA='b135a8eef0606c7356dc12d5956115d3832aa5cddb5dc5e71e5030380c76062e'

GLUE='''def bmmWithR11Cross (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)) : Vector Binary32 (batch*m*p) :=
  if h : p=2 ∧ 4≤batch*m ∧ 0<n ∧ n<USize.size ∧
      A.toArray.size<USize.size ∧ B.toArray.size<USize.size ∧ batch*m*p<USize.size then
    R11CrossRows.core batch m n p A B h.2.2.2.1 (Nat.le_of_eq h.1)
  else bmmBeforeWideRows batch m n p A B

theorem bmmWithR11Cross_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)),
    (bmmWithR11Cross batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmmWithR11Cross
  split
  · rw [R11CrossRows.core_eq_rows, DirectRows.core_eq, DirectSmall.core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeWideRows_spec batch m n p A B

'''

def compose(base, donor):
    text=base.decode();d=donor.decode()
    a=d.index('namespace Submission.R11CrossRows\n')
    z=d.index('end Submission.R11CrossRows',a)+len('end Submission.R11CrossRows')
    block=d[a:z]+'\n'
    first=text.index('def bmmBeforeWideRows (')
    insertion=text.rfind('namespace Submission\n',0,first)
    assert insertion>=0 and text[insertion:first].split()==['namespace','Submission','open','FloatLib.Floats','Competition']
    assert 'namespace Submission.R11CrossRows' not in text
    text=text[:insertion]+block+'\n'+text[insertion:]
    needle='def bmmBeforeUnderflowZero ('
    a=text.index(needle);z=text.index('\nend Submission',a)
    old=text[a:z]
    assert old.count('bmmBeforeWideRows')==2
    new=old.replace('bmmBeforeWideRows','bmmWithR11Cross')
    text=text[:a]+GLUE+new+text[z:]
    inverse=text.replace(GLUE+new,old,1).replace(block+'\n','',1)
    assert inverse.encode()==base
    return text.encode(),{'cross_namespace':block,'cross_namespace_sha256':sha(block.encode()),
                         'cross_namespace_bytes':len(block.encode()),'old_dispatch':old,'new_dispatch':new,'glue':GLUE}

def reviewed_base(raw,path):
    """Schema intentionally strict; adapted only after reading actual reviewed artifact."""
    data=json.loads(path.read_text(encoding='utf-8'))
    assert data['source_sha256']==WIDE_SHA
    assert data['review_state']=='MANUALLY_REVIEWED_EXACT_ALLOWLIST'
    edits=data['edits'];last=0;parts=[]
    protected=data['protected']
    assert protected, 'Reviewed author/license/source/runtime preservation records required'
    outer=raw.rfind(OUTER_MARK)
    assert outer>=0 and sha(raw[outer:])==OUTER_SHA
    receipts=[]
    for e in sorted(edits,key=lambda x:x['start']):
        a,z=e['start'],e['end'];assert last<=a<z<=outer
        before=raw[a:z];assert sha(before)==e['sha256']
        assert before.decode()==e['text']
        replacement=e['replacement'].encode()
        assert e['kind'] in ['reviewed_math_comment','ordinary_blank_line']
        assert e['preserves_author_license_source_runtime_obligations'] is True
        assert replacement.strip()==b''
        for keep in protected:
            assert z<=keep['start'] or a>=keep['end'], 'Approved edit overlaps a protected notice/obligation'
        parts.extend([raw[last:a],replacement]);last=z
        receipts.append({**e,'original_base64':base64.b64encode(before).decode()})
    parts.append(raw[last:]);out=b''.join(parts)
    # Exact inverse through the checked original slices and post-edit byte offsets.
    inverse=out;shift=0;positions=[]
    for e in sorted(edits,key=lambda x:x['start']):
        a,z=e['start'],e['end'];replacement=e['replacement'].encode()
        positions.append((a+shift,len(replacement),raw[a:z]));shift+=len(replacement)-(z-a)
    for a,count,original in reversed(positions):inverse=inverse[:a]+original+inverse[a+count:]
    assert inverse==raw
    for keep in protected:
        original=raw[keep['start']:keep['end']]
        assert sha(original)==keep['sha256'] and original.decode()==keep['text']
        assert out.count(original)>=raw.count(original), 'A protected original block was changed or removed'
    scanner_path=CS/'f01-d7-research/source-budget.py'
    assert sha(scanner_path.read_bytes())=='e1ee62f4d61219a80fffe20b54b869baf666b25d136a08a4087f3380a5d6ee51'
    spec=importlib.util.spec_from_file_location('scanner_readonly',scanner_path)
    scanner=importlib.util.module_from_spec(spec);spec.loader.exec_module(scanner)
    # Validation only; never invoke the heuristic prepare function.
    check=scanner.report_for(raw,out)
    assert check['code_lines_byte_equal']
    return out,receipts,sha(path.read_bytes())

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--allowlist',type=Path);ap.add_argument('--write',action='store_true');args=ap.parse_args()
    if args.allowlist is None and (HERE/'reviewed-allowlist.json').exists():
        args.allowlist=HERE/'reviewed-allowlist.json'
    raw=WIDE.read_bytes();donor=CROSS.read_bytes()
    assert sha(raw)==WIDE_SHA and sha(donor)==CROSS_SHA
    edits=[];allow_sha=None;prepared=raw
    if args.allowlist:prepared,edits,allow_sha=reviewed_base(raw,args.allowlist)
    data,composition=compose(prepared,donor)
    outer=raw[raw.rfind(OUTER_MARK):]
    assert len(outer)==1039 and sha(outer)==OUTER_SHA and data.endswith(outer)
    spec=importlib.util.spec_from_file_location('p',CS/'f01-r11-crossrow-p2-pack12-proof2/build.py')
    p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p);p.static_check(data.decode())
    rec={'candidate':HERE.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(data),'candidate_bytes':len(data),
         'created_at_utc':datetime.now(timezone.utc).isoformat(),'parent':WIDE.parent.name,'parent_sha256':WIDE_SHA,
         'cross_donor_sha256':CROSS_SHA,'cross_namespace_sha256':composition['cross_namespace_sha256'],
         'cross_namespace_bytes':composition['cross_namespace_bytes'],'allowlist_path':str(args.allowlist) if args.allowlist else None,
         'allowlist_sha256':allow_sha,'approved_edit_count':len(edits),'prepared_base_bytes':len(prepared),
         'size_margin':256000-len(data),'fits_size_cap':len(data)<=256000,
         'outer_underflow_suffix_sha256':sha(outer),'outer_underflow_suffix_bytes':len(outer),'outer_underflow_byte_identity':True,
         'source_pruning_inverse':True,'composition_inverse':True,
         'route':'Underflow first; originalWide(p>2,n>4,m>=4,machinebounds), then original5c Cross(p=2,otherexactguards), then originalDirect/fused fallback.',
         'new_Lean':'NOT_RUN','proof_status':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN','validation_mode':'full-gate','formal_submission':'NOT_SUBMITTED',
         'state':'PREPARED_NOT_WRITTEN' if args.allowlist else 'DRYRUN_BLOCKED_ON_REVIEWED_ALLOWLIST',
         'static_policy':'PASS','build_script_sha256':sha(Path(__file__).read_bytes())}
    if args.write:
        assert args.allowlist and edits and rec['fits_size_cap'], 'No Kernel before reviewed exact allowlist and capacity fit'
        assert not (HERE/'Kernel.lean').exists()
        (HERE/'Kernel.lean').write_bytes(data);rec['state']='FROZEN_READY_NOT_RUN'
        (HERE/'manifest.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
        (HERE/'inverse-review.json').write_text(json.dumps({'edits':edits,'composition':composition,'original_wide_sha256':WIDE_SHA,'original_cross_sha256':CROSS_SHA},ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    elif (HERE/'Kernel.lean').exists():
        assert (HERE/'Kernel.lean').read_bytes()==data
        frozen=json.loads((HERE/'manifest.json').read_text(encoding='utf-8'))
        assert frozen['candidate_sha256']==sha(data) and frozen['allowlist_sha256']==allow_sha
        assert frozen['build_script_sha256']==sha(Path(__file__).read_bytes())
        rec['state']='FROZEN_VERIFIED_READONLY'
    if not (HERE/'Kernel.lean').exists():
        (HERE/'dry-run.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
        (HERE/'dispatcher.lean').write_bytes(GLUE.encode())
    print(json.dumps({k:rec[k] for k in ['candidate','state','candidate_sha256','candidate_bytes','size_margin','approved_edit_count','static_policy','new_Lean']}))
if __name__=='__main__':main()
