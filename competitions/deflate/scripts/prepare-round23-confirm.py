"""Freeze new accepted-pair original confirmations without renaming the candidate."""
from pathlib import Path
import argparse,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round23'

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--labels',nargs='+',default=['confirm-d','confirm-e']);a=ap.parse_args()
    s=json.loads((ROOT/'evidence/round22/screen-k.json').read_bytes())
    name='r22-595-chain-halfhead';candidate=next(e for e in s['entries'] if e['name']==name)
    cert=json.loads((ROOT/candidate['path']/'VERIFICATION.json').read_bytes())
    assert cert['status']=='VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED' and cert['files']==candidate['hashes']
    s['entries']=[e for e in s['entries'] if e['name'] in ('probe3','r3-432-fast3','public432','public595','public595-shadow','chain',name)]
    for k in list(s):
        if k.startswith('r22_'):del s[k]
    s.update(r23_mode='standard',r23_expected_candidates=1,r23_dispatch_after_gate_pair_known=True,r18_role='independent_confirmation',r23_role='independent_confirmation',snapshot_pages='evidence/round23/official-start/pareto-pages.json',description='R23 freshaccepted-pair independentconfirmation, exactfrozenRust/Lean, original1warmup+11reps, two oppositeblocks, actualchainparent and hashidentical595shadow. Discovery, latercontrols and diagnostics excludedfromindependentstatistics.')
    names=[e['name'] for e in s['entries']];s['screen_orders']=[names,names[::-1]]
    for label in a.labels:
        p=E/(label+'.json');assert not p.exists();p.write_bytes((json.dumps(s,indent=2)+'\n').encode())
        plan={'gap':'Exactpair nowaccepted, prior publictwo-blocksignal16percent/zero stillunconfirmed.','substantial_change':'Newindependentrunner perlabel, unchangedacceptedpair, tworeverseordered originalpairedblocks with bothactual595andidenticalshadowplus actualchainparent.','minimum':'Save28file measuredreps,totalcompressiontimes,incumbentpairs,input/output/libraryhashes and environment; replay everyblock separately and matching-blockjoint shares.','decision':'Report best,median,range,zeroand>=10counts byrunnerandcontrol. HighrepeatconflictsremainUNKNOWN; noformalpromotionor probabilityinterpretation.','cost_cap_minutes':16,'evidence':'evidence/round23/<run>/'+label+'/gate','accepted_pair':candidate['hashes'],'public_gate_run_id':cert['run_id']}
        (E/('preflight-'+label+'.json')).write_bytes((json.dumps(plan,indent=2)+'\n').encode())
    print('FROZEN_NEW_CONFIRMATIONS',a.labels,candidate['hashes'])

if __name__=='__main__':main()
