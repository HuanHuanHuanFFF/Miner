"""Select two distinct gated tradeoff points without rewriting discovery evidence."""
from pathlib import Path
from datetime import datetime,timezone
import copy,json,hashlib,itertools
from round3 import load_scorer
from round10_payability import load_flat_rows,validate_policy_for_replay
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24'
def read(p):return json.loads(p.read_bytes())
def save(name,data):
    p=E/(name+'.json');assert not p.exists();p.write_bytes((json.dumps(data,indent=2)+'\n').encode())
def main():
    capture=E/'official-selection';comp,ctx,rows=load_flat_rows(capture);sc=load_scorer(E/'official-rules-start/validator--scoring--pareto.py');policy=validate_policy_for_replay(comp['policy'],rows,sc);formal={str(r['id']):r for r in rows};bounds=sc.Boundaries(comp['policy']['max_balanced_time_ratio'],comp['policy']['max_mean_file_compression_pct']);front=[sc.Point(str(r['id']),r['metrics']['balanced_time_ratio'],r['metrics']['mean_file_compression_pct'])for r in rows if(r.get('score')or{}).get('on_frontier')]
    def scores(points):
        good=[sc.Point(n,x,y)for n,x,y in points if 0<x<=bounds.time_s and 0<y<=bounds.ratio_pct and not any(p.time_s<=x and p.ratio_pct<=y for p in front)];nf=sc.pareto_front(front+good);ws=sc.local_global_improvement_space_log_weights(nf,bounds);return {n:100*comp['policy']['pareto_share']*ws.get(n,0)for n,_,_ in points}
    root=E/'38102994768/screen-bc/gate';state=read(root/'state.json');by={(m['candidate'],m['round']):m for m in state['metrics']};audit={k.replace('\\','/'):v for k,v in read(E/'analysis-bc.json')['raw_input_audit'].items()};observations=[];joint=[]
    names=['fast-stack','r24-609-fast-adaptive','buffer-adaptive']
    for block in [1,2]:
        for name in names:
            p=root/f'round{block}-{name}.jsonl';assert hashlib.sha256(p.read_bytes()).hexdigest()==audit[p.relative_to(ROOT).as_posix()]['sha256']
        for anchor,fid in [('public609','609'),('public609-shadow','609'),('public607','607')]:
            fm=formal[fid]['metrics'];ref=by[anchor,block];points=[]
            for name in names:
                m=by[name,block];x=fm['balanced_time_ratio']*m['time']/ref['time'];y=fm['mean_file_compression_pct']*m['size_pct']/ref['size_pct'];points.append((name,x,y));observations.append({'block':block,'anchor':anchor,'entry':name,'original_role':'candidate'if name=='r24-609-fast-adaptive'else'incidental_control_in_discovery','projected_time':x,'projected_size_pct':y,'single_pool_share_pct':scores([(name,x,y)])[name]})
            for pair in itertools.combinations(points,2):joint.append({'block':block,'anchor':anchor,'entries':[p[0]for p in pair],'simultaneous_pool_share_pct':scores(pair)})
    s=read(E/'screen-bc.json');a=copy.deepcopy(next(e for e in read(E/'screen-am.json')['entries']if e['name']=='r24-609-root-word-price'));b=copy.deepcopy(next(e for e in s['entries']if e['name']=='r24-609-fast-adaptive'))
    required={'probe3','r3-432-fast3','public432','public609','public609-shadow','public607','fast-stack'};controls=[copy.deepcopy(e)for e in s['entries']if e['control']and e['name']in required];assert {e['name']for e in controls}==required
    path=ROOT/'candidates/r24-609-root-prune-proof1';m=read(path/'manifest.json');c=read(path/'VERIFICATION.json');assert m['hashes']==c['files'];controls.append({'name':'root-prune','path':path.relative_to(ROOT).as_posix(),'control':True,'hashes':c['files'],'anchor':'public609'})
    s['entries']=controls+[a,b];s.update(preflight_only=True,r24_expected_candidates=2,description='NOT_RUN selectionmapping template. Preserve originalAM/BCactualparentaliases while choosing gatedfaststack andfastadaptive. prepare-round24-final replacesexactproofpairs, checksacceptedgates andcreatesnew3runnerx3blockspecs; this templatecannotbedispatched.')
    ns=[e['name']for e in s['entries']];s['screen_orders']=[ns,ns[::-1]];save('final-selection',s)
    record={'status':'PREDECLARED_FINAL_PAIR_SELECTION_NOT_TARGET_SUCCESS','selected_utc':datetime.now(timezone.utc).isoformat(),'snapshot':ctx,'policy_validation':policy,'selected':[{'label':'A','target_pool_share_pct':10,'candidate':'r24-609-root-word-price-proof1','kind':'Faster originalquality point','risk':'Related607anchor assigns muchsmallerconditionalshare; currentevidence isnotstable10percent.'},{'label':'B','target_pool_share_pct':15,'candidate':'r24-609-fast-adaptive-proof1','kind':'Betterquality withboundedextra shortmatchsearch','risk':'Only2discoveryblocks across threecalibrationviews; allbelow5percent, no15percent claim.'}],'why':'Twoactualdifferent optimizationpoints andpublicoutputs, bothwithacceptedexactgates. Keep speed/qualitytradeoff forjointassessment. Theothergatedbuffer-adaptive point isretainedasbackup butisdominated byfastadaptive in the sameBCmeasuredcoordinates andhaszerojointgeometrythere. Single-candidateweights canstillbe nonmonotonic, soallthreecontrol/candidateprojections andpairwisejointresults arepreservedbelow.','selection_observations':observations,'pairwise_joint':joint,'stopped':['chain-LCP8: originaltime+3.28/+2.13percent andallthreeanchorviewszero','spanitems: originaltime+2.57/+2.67percent andallviewszero','stack-packed: isolatedgain doesnotpersist inactualcomposition','a-packed proof2: remainingrecursionfailure; notanacceptedfinalpair'],'confirmation':'Fresh3runnersx3originalblocks afterexactpairfreeze, allshadows/actualparents/607/609preserved. No source/proofedits afterfreezing; all below-target/zero/controlcounterexamples reported.','scope':'Selectiondoesnotestablishstablehighshare, privateadmission, registration/slots, officialsubmission orpayable reward.'};save('final-selection-decision',record);print(json.dumps({'status':record['status'],'selected':record['selected'],'joint_rows':len(joint)},indent=2))
if __name__=='__main__':main()
