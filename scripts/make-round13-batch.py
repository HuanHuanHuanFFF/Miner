"""Freeze small R13 comparisons, explicitly binding both family and direct parent."""
from pathlib import Path
import argparse,hashlib,json,os,re

ROOT=Path(__file__).resolve().parents[1]

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('batch');ap.add_argument('candidates',nargs='+');ap.add_argument('--blocks',type=int,choices=[1,2,3,4],default=2);ap.add_argument('--extract',action='store_true');ap.add_argument('--gates',nargs='*',default=[]);args=ap.parse_args()
    assert re.fullmatch(r'[a-z0-9-]{1,48}',args.batch)and len(set(args.candidates))==len(args.candidates)<=3
    manifests={n:json.loads((ROOT/'candidates'/n/'manifest.json').read_bytes())for n in args.candidates}
    old=json.loads((ROOT/'evidence/round12/probe-c.json').read_bytes())
    anchors={m.get('formal_anchor_id','453')for m in manifests.values()}
    entries=[e.copy()for e in old['entries']if e['control']and(e['name']not in('public507','pc507-shadow')or'507'in anchors)]
    by={e['name']:e for e in entries}
    for aid in anchors-{'453','507'}:
        ref=ROOT/f'references/round13-public-{aid}';name='public'+aid
        e={'name':name,'path':ref.relative_to(ROOT).as_posix(),'control':True,'anchor':name,'formal_id':aid,'hashes':{f:hashlib.sha256((ref/f).read_bytes()).hexdigest()for f in('parse.rs','Parse.lean')}}
        entries.append(e);by[name]=e;shadow={**e,'name':name+'-shadow'};shadow.pop('formal_id');entries.append(shadow);by[shadow['name']]=shadow
    for n,m in manifests.items():
        baseline=m.get('comparison_baseline','r3-432-fast3')
        if baseline not in by and baseline not in args.candidates:
            p=ROOT/'candidates'/baseline
            e={'name':baseline,'path':p.relative_to(ROOT).as_posix(),'control':True,'anchor':('public'+m['formal_anchor_id'])if m.get('formal_anchor_id')not in(None,'453')else'r3-432-fast3','hashes':{f:hashlib.sha256((p/f).read_bytes()).hexdigest()for f in('parse.rs','Parse.lean')}};entries.append(e);by[baseline]=e
        anchor=('public'+m['formal_anchor_id'])if m.get('formal_anchor_id')not in(None,'453')else'r3-432-fast3'
        p=ROOT/'candidates'/n;e={'name':n,'path':p.relative_to(ROOT).as_posix(),'control':False,'anchor':anchor,'comparison_baseline':baseline,'anchor_scope':'Declared parent family; public-to-formal transfer is a hypothesis','hashes':{f:hashlib.sha256((p/f).read_bytes()).hexdigest()for f in('parse.rs','Parse.lean')}}
        if m.get('native_relation')=='decode_only':e['native_decode_reference']=baseline
        else:e['expected_equivalent_to']=baseline
        entries.append(e);by[n]=e
    assert set(args.gates)<=set(by)
    spec={'entries':entries,'snapshot_pages':'evidence/round13/official-start/pareto-pages.json','screen_blocks':args.blocks,'refine_blocks':0,'shortlist':len(args.candidates),'gate_candidates':args.gates,'gate_limit':len(args.gates),'extract_candidates':args.candidates if args.extract else[],'retain_extracted_lean':True,'synthetic_validation':True,'synthetic_reference_candidates':[],'research_synthetic_candidates':args.candidates,'cpu_diagnostics':args.extract,'cpu_diagnostic_candidates':args.candidates+[e['comparison_baseline']for e in entries if not e['control']],'description':'R13 seven-hour continuation. Fresh exact Rust checks, original public28 total-compression axes and explicit current-family projection.','chat_smoke':any(n.startswith('chat-20261008-')for n in args.candidates)}
    p=ROOT/'evidence/round13'/f'{args.batch}.json';assert not p.exists();p.write_bytes((json.dumps(spec,indent=2)+'\n').encode());os.environ['ROUND4_SPEC_DIR']='evidence/round13';from round4 import validate;validate(args.batch)
    print(json.dumps({'batch':args.batch,'paired_processes':len(entries)*args.blocks,'candidates':args.candidates,'full_gate_requests':args.gates}))

if __name__=='__main__':main()
