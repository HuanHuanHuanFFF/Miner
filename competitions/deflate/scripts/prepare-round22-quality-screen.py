"""Bind real D quality deltas to a minimal original timing batch and chain gate."""
from pathlib import Path
import json
ROOT=Path(__file__).resolve().parents[1]
E=ROOT/'evidence/round22'

def write(label,data):
    p=E/(label+'.json');assert not p.exists()
    p.write_bytes((json.dumps(data,indent=2,ensure_ascii=False)+'\n').encode())

def main():
    n=json.loads((E/'38069454707/probe-d-native/diagnostics/r13-encoder/encoder.json').read_bytes())
    assert n['status']=='VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES'
    s=json.loads((E/'probe-d-native.json').read_bytes())
    by={(r['candidate'],r['file']):r for r in n['rows']}
    fs=sorted(f for name,f in by if name=='public595');assert len(fs)==28
    delta=[{'candidate':e['name'],'changed_files':[{'file':f,'output_delta_bytes':by[e['name'],f]['output_bytes']-by['public595',f]['output_bytes']} for f in fs if by[e['name'],f]['output_bytes']!=by['public595',f]['output_bytes']], 'total_output_bytes':sum(by[e['name'],f]['output_bytes'] for f in fs),'total_delta_bytes':sum(by[e['name'],f]['output_bytes']-by['public595',f]['output_bytes'] for f in fs)} for e in s['entries'] if not e.get('control')]
    s['entries']=[e for e in s['entries'] if e['name']!='public514']
    s.update(r22_mode='standard',native_only=False,native_encoder=False,native_encoder_references=[],synthetic_validation=False,description='R22 E two reversed original paired total-time blocks: chain quality gain and broad nofold tradeoff, actual595 and same-source shadow. Separate exact chain gate; no private guarantee.')
    names=[e['name'] for e in s['entries']];s['screen_orders']=[names,names[::-1]]
    write('screen-e',s)
    en=next(e for e in s['entries'] if e['name']=='r22-595-row6-chain')
    write('gate-chain',{'r22_mode':'gate','candidate':en['name'],'path':en['path'],'files':en['hashes'],'expected_public_output_bytes':sum(by[en['name'],f]['output_bytes'] for f in fs),'description':'Exactnew595 singleoldercandidate route, originalgeneric chain theorem and row wrapper bound, native7238B smaller. Full re-extraction/obligation/axioms/roundtrip required.'})
    write('preflight-e',{'gap':'D original encoder measures chain -7238B onlean.txt, nofold broader quality regression; untimed bytes cannot determine two-axis share.', 'substantial_change':'First original total-time measurements for these distinct actual595 parsing decisions; no arbitrary delay or classifier edits.', 'minimum':'Two reversed original 1warmup+11rep timing blocks, paired595 and identicalshadow; parallel original fullgate of exactchain pair.', 'decision':'Replay measured speed and actual size against current frontier, diagnose source-control disagreement before promotion, and independently confirm a frozen accepted pair within remainingtime.', 'cost_cap_minutes':{'screen_e':18,'gate_chain':25},'evidence':'evidence/round22/<run>/screen-e and gate-chain','actual_native_delta':delta})
    print(json.dumps(delta))

if __name__=='__main__':main()
