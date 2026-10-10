"""Prepare fresh paired checkpoint runs only after both exact gates are accepted."""
from pathlib import Path
from datetime import datetime,timezone
import copy,hashlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24'
def main():
    s=json.loads((E/'screen-noq.json').read_bytes());s['entries']=[x for x in s['entries']if x['control']]
    names=['r24-609-price-groups','r24-609-buffer-split-proof1'];candidates=[];shadows=[];certs={}
    for n in names:
        path=ROOT/'candidates'/n;m=json.loads((path/'manifest.json').read_bytes());c=json.loads((path/'VERIFICATION.json').read_bytes())
        assert c['status']=='VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED' and c['files']==m['hashes']
        assert all(hashlib.sha256((path/f).read_bytes()).hexdigest()==h for f,h in c['files'].items())
        e={'name':n,'path':path.relative_to(ROOT).as_posix(),'control':False,'hashes':c['files'],'anchor':'public609','comparison_baseline':'once','native_decode_reference':'once'}
        if n=='r24-609-price-groups':e['expected_equivalent_to']='once'
        candidates.append(e);shadows.append({'name':n+'-shadow','path':e['path'],'control':True,'hashes':e['hashes'],'anchor':'public609'});certs[n]=c
    s['entries']+=candidates+shadows
    s.update(r18_role='independent_confirmation',r24_role='checkpoint_confirmation',r24_expected_candidates=2,r24_dispatch_after_gate_pair_known=True,description='Frozen accepted-pair checkpoint on two fresh runners, two original opposite-order blocks each. Both609reference and each candidate have same-source shadows. Establish current independent evidence while research continues; this does not replace fresh confirmation after any later source/proof change.')
    ns=[x['name']for x in s['entries']]
    for i in [1,2]:
        spec=copy.deepcopy(s);spec['screen_orders']=[ns,ns[::-1]] if i==1 else[ns[::-1],ns]
        p=E/f'checkpoint-z{i}.json';assert not p.exists();p.write_bytes((json.dumps(spec,indent=2)+'\n').encode())
    p=E/'preflight-z.json';assert not p.exists();p.write_bytes((json.dumps({'declared_utc':datetime.now(timezone.utc).isoformat(),'gap':'N and originalL have only one discovery runner. New splitL Rust has never had original timing; N has no fresh frozen-run confirmation.','change':'No source changes. Two fresh runners with opposite original-protocol block orders, actualonceparent,609andcandidate shadows; actual joint frontier replay in each block.','minimum':'Two runners x2blocks, original1warmup11measured total-compression protocol; retain perfiletimes, library/source/input/output identities and environment.','decision':'All failures/zeroes/below-target blocks retained. Contradictory aliases trigger discriminating measurement work. Continue active search regardless: these checkpoints are below10/15 discovery targets.','cost_cap_runner_minutes_each':55,'exact_certificates':certs,'evidence':'evidence/round24/<run>/checkpoint-z1|z2/gate','limits':'Public conditional snapshot evidence only. Final selected changedpairs need their own exactgate and newconfirmations; observed pass frequency is not formal success probability.'},indent=2)+'\n').encode())
    print('CHECKPOINT_FROZEN',len(ns),'methods x2blocks x2runners')
if __name__=='__main__':main()
