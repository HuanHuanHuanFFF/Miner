"""Freeze real-quality depth variant for original time and independent exact gate."""
from pathlib import Path
import json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round23'

def main():
    n=json.loads((E/'38073276904/depth-c-native/diagnostics/r13-encoder/encoder.json').read_bytes());assert n['status']=='VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES'
    s=json.loads((E/'depth-c-native.json').read_bytes());s['entries']=[e for e in s['entries'] if e['name']!='public514']
    s.update(r23_mode='standard',native_only=False,native_encoder=False,native_encoder_references=[],synthetic_validation=False,r18_role='discovery',r23_role='discovery',description='R23 F firstoriginalpairedtwo reversedblocks of one third-candidate source; native3097B improvement vsactualcombo. Pairtotalcompression/595shadow andactualcombo parent. Separate fullgate, no formal/privateclaim.')
    ns=[e['name'] for e in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    p=E/'screen-f.json';assert not p.exists();p.write_bytes((json.dumps(s,indent=2)+'\n').encode())
    e=next(e for e in s['entries'] if not e.get('control'));rr=[r for r in n['rows'] if r['candidate']==e['name']];assert len(rr)==28
    gate={'r23_mode':'gate','candidate':e['name'],'path':e['path'],'files':e['hashes'],'expected_public_output_bytes':sum(r['output_bytes'] for r in rr),'description':'Exactfrozen additionaloldermatch route on595combo, generic Leantextonlydraft, mustfreshlyextract andproveoriginalobligation withaxiomwhitelist/roundtrip.'}
    (E/'gate-chain3.json').write_bytes((json.dumps(gate,indent=2)+'\n').encode())
    plan={'gap':'Native newdepth3 source really saves3097B beyondcombo but leavesnearbyhighsharewindow narrow; no total-time or fullproof evidence.','substantial_change':'Firstoriginal total-time onactualdepth3 versus frozencombo and595; concurrentlyverify itsunchangedexacttwofilepair.','minimum':'Two original1warmup11rep pairedblocks, perfile total/encoder/parser andmatchedcontrols; separateoriginalfullgate.','decision':'Replay eachblock/control andjointgeometry, neveruseaveragecoordinate on_frontier asallblockverdict. Newindependentrunner ifcandidate materially changescurrentchoice andfitsremainingtime. Ifproof repaired, newpairhashbound andconfirmationrequired; neverinherit anotherRustgate.','cost_cap_minutes':{'screen_f':16,'gate_chain3':20},'evidence':'evidence/round23/<run>/screen-f or gate-chain3','native_quality_delta_vs_combo_bytes':-3097,'frozen_files':e['hashes'],'confirmation_schedule':'Canfreezeandconfirmsamepair while separategate pending ifneeded; publicreadiness neverdeclareduntilgateaccepted onthat exactpair. Gatefailure/hashrepairinvalidatespair-readiness andrequiresfreshboundconfirmation.'}
    (E/'preflight-f.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode())
    print('DEPTH_SCREEN_AND_EXACT_GATE_FROZEN',gate['expected_public_output_bytes'],e['hashes'])

if __name__=='__main__':main()
