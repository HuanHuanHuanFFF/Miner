"""Prepare one full GeneralPanel composition. Default dry-run until phase1 feedback."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json,re,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
CS=HERE.parent
R11=CS/'f01-d7-research/round7h-20261023T193125Z'
R12=CS/'f01-d7-research/round6h-20261024T051445Z'
PARENT=CS/'f01-r11-wide4-cross-combined/Kernel.lean'
EXPECTED='e5b279b326e404d210cf2fb254c11a1773f84d2ab39cc853b9172f428c69c2d7'
sha=lambda b:hashlib.sha256(b).hexdigest()

def generate():
    raw=PARENT.read_bytes();assert sha(raw)==EXPECTED
    text=raw.decode();ops=[]
    def edit(a,z,new,label):
        nonlocal text
        old=text[a:z];ops.append({'name':label,'offset':a,'old':old,'new':new})
        text=text[:a]+new+text[z:]
    def replace(old,new,label):
        assert text.count(old)==1,(label,text.count(old))
        a=text.index(old);edit(a,a+len(old),new,label)
    cap=json.loads((R11/'astra-next-capacity.json').read_text(encoding='utf-8'))
    assert cap['parent']['sha256']==EXPECTED
    removals=cap['groups']['old_machine_family']+cap['groups']['old_native_span']
    for e in sorted(removals,key=lambda x:x['start_byte'],reverse=True):
        a,z=e['start_byte'],e['end_byte'];piece=raw[a:z]
        assert sha(piece)==e['sha256']
        ca=len(raw[:a].decode());cz=ca+len(piece.decode())
        assert text[ca:cz]==piece.decode()
        edit(ca,cz,'','replace_old_machine:'+e['name'])
    a=text.index('@[inline] def group (',text.index('namespace Submission.RowStream'))
    z=text.index('def core (',a)
    shared=(R12/'astra-shared-rowstream.lean').read_text(encoding='utf-8')
    edit(a,z,shared,'shared_numeric_raw_group_and_row_prefix')
    old_tail_comment='/-- Existing Packed10 path handles exactly the remaining zero to three rows.\nnativeA and packedB are the same global values used by buildTiles. -/'
    a=text.index(old_tail_comment,text.index('namespace Submission.R11WideLayout'))
    z=text.index('end Submission.R11WideLayout',a)
    old_flow=text[a:z]
    flow=(R12/'astra-panel-flow.lean').read_text(encoding='utf-8')
    edit(a,z,flow,'local_tail_and_B_only_global_flow')
    a=text.index('namespace Submission.R11WideActual\n')
    z=text.index('end Submission.R11WideActual',a)+len('end Submission.R11WideActual')
    actual=(R12/'astra-panel-actual.lean').read_text(encoding='utf-8').rstrip()
    edit(a,z,actual,'concrete_Panel4_block_Projects_and_actual_entry')
    panel_path=CS/'f01-d11-panel4-codegen-probe/Kernel.lean'
    panel_raw=panel_path.read_bytes();assert sha(panel_raw)=='9a40118eae28c92c1abeca7f6a141fb0fbfe963cbf40321681b8013782f9f7ac'
    src=panel_raw.decode();a=src.index('namespace Submission.Panel4\n');z=src.index('end Submission.Panel4',a)+len('end Submission.Panel4')
    panel=src[a:z]+'\n'
    proof_path=CS/'f01-d11-panel4-projection-proof2/panel4-projection-proof2.lean'
    proof_raw=proof_path.read_bytes();assert sha(proof_raw)=='93b1ac6fed4b6f73aef621d374fcea195886a04ca3bdd0ef3cd93b5684104bdf'
    src=proof_raw.decode();a=src.index('namespace Submission.Panel4Bridge\n');z=src.index('end Submission.Panel4Bridge',a)+len('end Submission.Panel4Bridge')
    proof=src[a:z]+'\n'
    at=text.index('namespace Submission.R11WideLayout\n')
    edit(at,at,panel+proof,'verified_Panel4_runtime_and_repaired_projection')
    old='''  if 4 ≤ m ∧ 4 < n ∧ 2 < p ∧ n < USize.size ∧ A.toArray.size < USize.size then
    R11WideActual.core batch m n p A B'''
    new='''  if h : 4 ≤ m ∧ 4 < n ∧ 2 < p ∧ n < USize.size ∧ A.toArray.size < USize.size then
    R11WideActual.core batch m n p A B h.2.2.2.1'''
    replace(old,new,'same_outer_shape_guard_supplies_count_proof')
    # Two old namespaces contain only untagged local theorems. Keep namespaces,
    # opens, and the exact FRO/Apache source notice; remove no runtime function.
    finite_pruning=[];finite_closures=[]
    for ns,names in [('WordFinite',['modelFiniteOfExp','nativeFiniteOfExp']),
                     ('FinalFinite',['packNaN_notFinite','packInfinity_notFinite','add_finite_inputs','mul_finite_inputs'])]:
        a=text.index('namespace '+ns+'\n');z=text.index('end '+ns,a)
        block=text[a:z]
        assert not any(token in block for token in ['@[','attribute ','instance ','notation ','syntax ','macro ','set_option '])
        outside=text[:a]+text[z:]
        declared=re.findall(r'^theorem ([A-Za-z0-9_]+)',block,re.M)
        assert set(declared)==set(names) and len(declared)==len(names)
        graph={}
        for name in names:
            start=block.index('theorem '+name)
            nxt=re.search(r'^theorem \w+',block[start+1:],re.M)
            stop=start+1+nxt.start() if nxt else len(block)
            body=block[start:stop]
            graph[name]=[other for other in names if other!=name and re.search(r'\b'+other+r'\b',body)]
        finite_closures.append({'namespace':ns,'original_block_sha256':sha(block.encode()),
            'all_declared_theorems':declared,'deleted_theorems':names,'internal_dependencies':graph,
            'retained_declarations_in_namespace':[],'outside_name_references':0,
            'attributes_instances_notations_syntax_options':False,
            'scope':'Whole local theorem dependency family removed together; no internal dependent remains. Exact new Lean/full remains necessary.'})
        for name in names:
            assert not re.search(r'(?<![\w])'+re.escape(name)+r'(?![\w])',outside),name
        for name in reversed(names):
            a=text.index('namespace '+ns+'\n');z=text.index('end '+ns,a)
            start=text.index('theorem '+name,a)
            assert start<z
            following=re.search(r'^theorem \w+',text[start+1:z],re.M)
            stop=start+1+following.start() if following else z
            old=text[start:stop]
            assert '/-' not in old and '--' not in old,'Preserve any embedded source/obligation comment'
            finite_pruning.append({'namespace':ns,'name':name,'bytes':len(old.encode()),'sha256':sha(old.encode())})
            edit(start,stop,'','remove_untagged_unused_proof:'+ns+'.'+name)
    inverse=text
    for op in reversed(ops):
        at=op['offset'];assert inverse[at:at+len(op['new'])]==op['new']
        inverse=inverse[:at]+op['old']+inverse[at+len(op['new']):]
    assert inverse.encode()==raw
    outer=raw[raw.rfind(b'namespace Submission\nopen FloatLib.Floats Competition\n\n/-- Both short-circuiting scans'):]
    assert len(outer)==1039 and sha(outer)=='b135a8eef0606c7356dc12d5956115d3832aa5cddb5dc5e71e5030380c76062e'
    assert text.encode().endswith(outer)
    for ns in ['Submission.R11CrossRows','Submission.DirectContinuous','Submission.UnderflowZero']:
        src=raw.decode();a=src.index('namespace '+ns+'\n');z=src.index('end '+ns,a)+len('end '+ns)
        assert src[a:z] in text
    spec=importlib.util.spec_from_file_location('budget',CS/'f01-d7-research/source-budget.py')
    budget=importlib.util.module_from_spec(spec);spec.loader.exec_module(budget)
    changed_comments=[old_flow.encode()[a:z] for a,z in budget.comment_spans(old_flow.encode())]
    assert len(changed_comments)==2
    assert all(not budget.is_notice(c) for c in changed_comments)
    cursor=0;new_raw=text.encode()
    for a,z in budget.comment_spans(raw):
        c=raw[a:z]
        if c in changed_comments:continue
        at=new_raw.find(c,cursor);assert at>=0,'Original source/notice/obligation comment lost'
        cursor=at+len(c)
    spec=importlib.util.spec_from_file_location('policy',CS/'f01-r11-crossrow-p2-pack12-proof2/build.py')
    policy=importlib.util.module_from_spec(spec);spec.loader.exec_module(policy);policy.static_check(text)
    # Runtime new Panel flow/producer must not create a global A.map; references
    # in proof statements and the preserved normal fallback are intentional.
    for name,body in [('flow.output',flow[flow.index('@[inline] def output'):flow.index('theorem output_prefix')]),
                      ('actual.buildTiles',actual[actual.index('@[inline] def buildTiles'):actual.index('theorem buildTiles_projects')]),
                      ('flow.emitTail',flow[flow.index('def emitTail'):flow.index('theorem emitTail_prefix')])]:
        assert '.map' not in body,name
    assert 'RowStream.row batch m n p A B nativeA packedB acc' not in text
    return new_raw,ops,changed_comments,sha(panel.encode()),sha(proof.encode()),finite_pruning,finite_closures

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--write',action='store_true');a=ap.parse_args()
    data,ops,changed,panel_sha,proof_sha,finite_pruning,finite_closures=generate()
    rec={'candidate':HERE.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(data),'candidate_bytes':len(data),
         'created_at_utc':datetime.now(timezone.utc).isoformat(),'parent':PARENT.parent.name,'parent_sha256':EXPECTED,
         'size_margin':256000-len(data),'fits_size_cap':len(data)<=256000,'static_policy':'PASS',
         'phase':'FULL_SOURCE_DRYRUN_NOT_WRITTEN','proof_status':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN',
         'validation_mode':'full-gate','formal_submission':'NOT_SUBMITTED','inverse_parent_exact':True,
         'panel_namespace_sha256':panel_sha,'projection_namespace_sha256':proof_sha,
         'unused_finite_proofs':finite_pruning,
         'unused_finite_internal_closures':finite_closures,
         'unused_scope_check':'Only6 untagged theorem bodies, all names absent outside their namespace; no instance/attribute/notation/syntax/options. Kept every source notice/open/namespace. New Lean/full still required.',
         'mechanism':'One generalized RowStream group/row Prefix for numeric/raw bases; direct arrays, erased read equality. Fullblocks localF4 panelsharedacrossG, localtailonlyremainingrows, no fullAmap onPanelentry.',
         'replaced_runtime_obligation_comments':[{'old':c.decode(),'sha256':sha(c),'reason':'GlobalnativeA obligation replaced byone localpanel/tail andsameglobalB/raw lifetime; notdeletedforcapacity.'} for c in changed],
         'preserved':'All other original comments/notices; outer1039,Cross,DirectContinuous,Underflow; original dispatch shape/machine bounds and fallback.',
         'build_script_sha256':sha(Path(__file__).read_bytes()),
         'remaining':'Exact new Lean/full andactualC; dependency closure/capacity ifoverlimit; dynamic panel lifetime, normalfallbackcodegen, wholecost unverified.'}
    if a.write:
        assert rec['fits_size_cap'] and not (HERE/'Kernel.lean').exists()
        (HERE/'Kernel.lean').write_bytes(data);rec['phase']='FROZEN_READY_NOT_RUN'
        (HERE/'manifest.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
        (HERE/'exact-inverse.json').write_text(json.dumps({'parent_sha256':EXPECTED,'operations':ops,'inverse_exact':True},ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
        sp=importlib.util.spec_from_file_location('decl_inventory',CS/'f01-r8-combined-result-guard/build.py')
        inv=importlib.util.module_from_spec(sp);sp.loader.exec_module(inv)
        before=inv.declarations(PARENT.read_bytes().decode());after=inv.declarations(data.decode())
        audit={'candidate_sha256':sha(data),'parent_sha256':EXPECTED,'static_policy':'PASS',
            'decl_inventory_scope':'def/theorem/abbrev only; originalfullLean stillrequired',
            'removed_declarations':sorted(set(before)-set(after)),'added_declarations':sorted(set(after)-set(before)),
            'all_new_inventory':after,'finite_closures':finite_closures,
            'no_global_A_map_on_Panel_runtime_producer_output_tail':'PASS_SOURCE_BODY_CHECK',
            'original_outer1039_cross_direct_underflow_byte_identity':True}
        (HERE/'decl-policy-review.json').write_text(json.dumps(audit,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    elif (HERE/'Kernel.lean').exists():
        assert (HERE/'Kernel.lean').read_bytes()==data
    else:
        (HERE/'dry-run.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({k:rec[k] for k in ['candidate','phase','candidate_sha256','candidate_bytes','size_margin','static_policy','proof_status']}))
if __name__=='__main__':main()
