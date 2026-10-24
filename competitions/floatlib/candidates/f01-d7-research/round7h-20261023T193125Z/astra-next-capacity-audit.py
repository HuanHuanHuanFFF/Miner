"""Read-only conditional source accounting. This script never deletes a declaration."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,re,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
CS=HERE.parent.parent
sha=lambda b:hashlib.sha256(b).hexdigest()
sp=importlib.util.spec_from_file_location('inventory',CS/'f01-r8-combined-result-guard/build.py')
inv=importlib.util.module_from_spec(sp);sp.loader.exec_module(inv)
parent=CS/'f01-r11-wide4-cross-combined/Kernel.lean'
raw=parent.read_bytes();assert sha(raw)=='e5b279b326e404d210cf2fb254c11a1773f84d2ab39cc853b9172f428c69c2d7'
text=raw.decode();lines=text.splitlines(keepends=True);masked=inv.strip_comments(text).splitlines(keepends=True)
decls=inv.declarations(text)
boundary=re.compile(r'^(?:@\[[^\]]+\]\s*)?(?:def|theorem|abbrev|namespace|end|structure|open|set_option|attribute|instance)\b')
def span(name):
    assert len(decls[name])==1
    a=decls[name][0]-1
    z=next((i for i in range(a+1,len(lines)) if boundary.match(masked[i])),len(lines))
    while z>a+1 and not masked[z-1].strip():z-=1
    before=''.join(lines[:a]).encode();body=''.join(lines[a:z]).encode()
    return {'name':name,'start_byte':len(before),'end_byte':len(before)+len(body),'bytes':len(body),
            'sha256':sha(body),'source_lines':[a+1,z],'condition':'Not approved as unused; remove only after every caller/proof dependency is replaced and exact new source passes.'}
groups={
 'guard_fallback_family':['Submission.R11WideRows4.'+x for x in ['joinRows','run','run_row']],
 'old_machine_family':['Submission.R11WideRows4.'+x for x in ['wordLoop','baseAt','row_bound','wordLoop_row','lane_of_row_eq','joinRows','within','within_row','run','run_row']],
 'old_native_span':['Submission.R11WideLayout.nativeA_span'],
 'old_tail':['Submission.R11WideLayout.'+x for x in ['rowIndex','emitTail','emitTail_prefix']],
 'flow_to_replace':['Submission.R11WideLayout.'+x for x in ['writeBatch','writeBatch_prefix','output','output_prefix']],
 'producer_to_replace':['Submission.R11WideActual.'+x for x in ['buildTiles','buildTiles_projects','output','output_prefix']],
}
records={k:[span(n) for n in ns] for k,ns in groups.items()}
totals={k:sum(x['bytes'] for x in v) for k,v in records.items()}
assets={}
for name,path in [('guard',HERE/'astra-wide-guard-proof.lean'),('projection_helper',HERE/'astra-panel4-projectRow-required.lean'),
                  ('panel_projection',HERE/'astra-panel4-loop-projection.lean'),
                  ('tail_proof2',CS/'f01-d11-panel4-tail-proof2/panel4-tail-proof2.lean')]:
    b=path.read_bytes();assets[name]={'path':str(path),'bytes':len(b),'sha256':sha(b)}
panel_source=(CS/'f01-d11-panel4-codegen-probe/Kernel.lean').read_text(encoding='utf-8')
a=panel_source.index('namespace Submission.Panel4\n');z=panel_source.index('end Submission.Panel4',a)+len('end Submission.Panel4')
panel_ns=panel_source[a:z].encode()
added=len(panel_ns)+assets['panel_projection']['bytes']+assets['tail_proof2']['bytes']
removed=sum(totals[k] for k in ['old_machine_family','old_native_span','old_tail','flow_to_replace','producer_to_replace'])
out={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'parent':{'path':str(parent),'sha256':sha(raw),'bytes':len(raw)},
     'no_Kernel_written_or_pruned':True,'groups':records,'group_totals':totals,'assets':assets,
     'panel_namespace':{'bytes':len(panel_ns),'sha256':sha(panel_ns)},
     'guard_accounting':{'whole_draft_append_bytes':len(raw)+assets['guard']['bytes'],
         'after_conditional_guard_family_removal_before_API_wiring':len(raw)+assets['guard']['bytes']-totals['guard_fallback_family'],
         'API_and_actual_producer_replacement_delta':'UNKNOWN; do not blindly append the full proof draft'},
     'panel_accounting':{'new_panel_projection_tail_bytes':added,'conditional_old_code_to_replace_bytes':removed,
         'temporary_bytes_before_putting_back_new_flow_and_producer':len(raw)-removed+added,
         'headroom_for_all_new_flow_and_producer':256000-(len(raw)-removed+added),
         'feasibility':'UNKNOWN; old flow/producer deletion is not free saving, new bodies must be restored; likely needs proof factoring or independently closed extra pruning'},
     'minimal_statement_recipes':{'guard_on28b':253315+assets['guard']['bytes'],
         'panel_projection_on9a':229218+assets['projection_helper']['bytes']+assets['panel_projection']['bytes'],
         'panel_projection_and_verified_tail_on9a':229218+assets['projection_helper']['bytes']+assets['panel_projection']['bytes']+assets['tail_proof2']['bytes']},
     'scope':'Only exact in-memory declaration byte accounting; not unused-chain authorization, compilation, full gate, runtime estimate or a new candidate. Adjacent comment/namespace bytes are not counted as free deletions; retained notices remain protected.'}
(HERE/'astra-next-capacity.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:out[k] for k in ['group_totals','panel_namespace','guard_accounting','panel_accounting','minimal_statement_recipes']}))
