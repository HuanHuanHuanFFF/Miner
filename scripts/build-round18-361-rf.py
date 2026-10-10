"""Public361 base plus the published586RF layer: feasibility/byte screening first."""
from pathlib import Path
import importlib.util,json,re

ROOT=Path(__file__).resolve().parents[1]

def masked(s):
    return re.sub(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"',lambda m:''.join('\n'if c=='\n'else' 'for c in m.group()),s,flags=re.S)

def declarations(s):
    code=masked(s);result={}
    for m in re.finditer(r'\bpub\s+(fn|const)\s+([A-Za-z_][A-Za-z0-9_]*)',code):
        kind,name=m.group(1),m.group(2);start=m.start()
        if kind=='fn':
            brace=code.index('{',m.end());depth=1;end=brace+1
            while depth:
                depth+=(code[end]=='{')-(code[end]=='}');end+=1
        else:
            depths={'(':0,'[':0,'{':0};close={')':'(',']':'[','}':'{'};end=m.end()
            while True:
                c=code[end]
                if c in depths:depths[c]+=1
                elif c in close:depths[close[c]]-=1
                elif c==';'and not any(depths.values()):end+=1;break
                end+=1
        # Preserve adjacent compiler attributes; other donor context is cited separately.
        prev=s.rfind('\n',0,start)+1
        while prev>0:
            line_start=s.rfind('\n',0,prev-1)+1;line=s[line_start:prev].strip()
            if not line.startswith('#['):break
            start=line_start;prev=line_start
        result[name]={'kind':kind,'start':start,'end':end,'text':s[start:end]}
    return result

def canon(s):return re.sub(r'\s+','',masked(s))

def main():
    sp=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    base=ROOT/'references/round7-public-361';donor=ROOT/'references/round18-public-586';old=(base/'parse.rs').read_text();new=(donor/'parse.rs').read_text();od=declarations(old);nd=declarations(new)
    todo=['refine'];selected=set();shared=[]
    while todo:
        name=todo.pop()
        if name in selected or name in shared:continue
        if name in od and canon(od[name]['text'])==canon(nd[name]['text']):shared.append(name);continue
        selected.add(name);words=set(re.findall(r'\b[A-Za-z_][A-Za-z0-9_]*\b',masked(nd[name]['text'])));todo.extend((words&nd.keys())-selected-set(shared))
    clashes=selected&od.keys();renames={name:'r18rf_'+name for name in clashes}
    chunks=[]
    for name in sorted(selected,key=lambda n:nd[n]['start']):
        text=nd[name]['text']
        for a,b in renames.items():text=re.sub(r'\b'+re.escape(a)+r'\b',b,text)
        chunks.append(text)
    assert old.count('pub fn parse(')==1
    rust=old.replace('pub fn parse(','pub fn r18_base_parse(',1)
    rust+='\n// RF and support derived from public submission586; original algorithms retained.\n'+'\n\n'.join(chunks)+'\n'
    mapping=[28 if i in (5,6,7,8,9,10,11,12,13,15)else 0 for i in range(16)]
    rust+='pub const R18_RF_MAP: [usize;16] = '+json.dumps(mapping)+';\n'
    refine=renames.get('refine','refine')
    rust+=f'''pub fn parse(input:&[u8],out:&mut[u32])->usize {{
    let nt=r18_base_parse(input,out);
    let cls=route_class(input);
    let cfg=R18_RF_MAP[cls%16];
    if cfg!=0 {{
        let plan={refine}(input,out,nt,cfg);
        if plan.len()>0 {{return emit(input,&plan,out);}}
    }}
    nt
}}
'''
    proof=(base/'Parse.lean').read_text()
    e=m.write_candidate('r18-361-rf-text','public361',rust,proof,
        'Keep the exactoriginal361 baseparser body, then apply the released586RF matcher/refitter to existingtext classes5-13and15. Use oneexistingRFconfiguration28(depth16,two passes,stride1,seedmatches). Tiny,DNA,sparse andbinary classes keepthe exactbase. Imports are a transitive codeclosure; conflictinghelper names are isolated.',
        'Currenthigh-endselective586 remainsaround2.5percent,while target15requiresa muchlargercost/quality move. This tests a fasterverifiedhistoricalbase with newerrefinement, ratherthan micro-tuningthehigh-endbase. Bytequality andreal total time areUNKNOWN; proofmigration is deliberatelydeferred untilsignals justifyit.',
        {'base':'references/round7-public-361/PROVENANCE.md','refinement':'references/round18-public-586/source-receipt.json','lineage':'Bothpublicauthors retained; wholeprogramcomposition isresearch, notindependentengine invention.'})
    e.update(anchor='public361',comparison_baseline='public361',native_decode_reference='public361')
    mf=ROOT/e['path']/'manifest.json';v=json.loads(mf.read_bytes());v['proof_status']='ORIGINAL361_PROOF_NOT_ADAPTED_TO_NEW_WRAPPER_OR_RF; NOT_READY_FOR_GATE';mf.write_bytes((json.dumps(v,indent=2)+'\n').encode())
    spec=json.loads((ROOT/'evidence/round18/model-aa-native.json').read_bytes());spec['entries']=[x for x in spec['entries']if x.get('control')and x['name']!='selective586']+[m.control('public361','references/round7-public-361','361'),e];spec['native_encoder_references']=['public361','public586'];spec['screen_orders']=[[x['name']for x in spec['entries']],[x['name']for x in reversed(spec['entries'])]]
    spec['description']='ABnative feasibility: exact361base +published586RFtransitiveclosure onexistingtextclasses, onefixedRFmode. Originalencoder28files anddecode; cap25job-minutes. Inspectqualitygap tocurrenttargetregion beforetotal-time/proofmigration. NewLeanwrapper/RFlemmas notadapted; no fullgateclaim.'
    (ROOT/'evidence/round18/361-ab-native.json').write_bytes((json.dumps(spec,indent=2)+'\n').encode())
    report={'candidate':e,'donor_declarations':sorted(selected),'shared_exact_declarations':sorted(shared),'isolated_name_collisions':renames,'source_bytes':len(rust.encode()),'old_proof_bytes':len(proof.encode()),'scope':'Syntacticdependencyclosure andnamespace isolation only; realcompile/encoder/decode pending. Proofportingnotdone.'};(ROOT/'evidence/round18/361-ab-preflight.json').write_bytes((json.dumps(report,indent=2)+'\n').encode());print(json.dumps({k:v for k,v in report.items()if k not in('donor_declarations','shared_exact_declarations')}))

if __name__=='__main__':main()
