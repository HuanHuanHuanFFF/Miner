"""Freeze the first actual R22 timing batch and a bounded parallel exact gate."""
from pathlib import Path
import json

ROOT=Path(__file__).resolve().parents[1]
E=ROOT/'evidence/round22'

def write(name,data):
    p=E/(name+'.json')
    assert not p.exists()
    p.write_bytes((json.dumps(data,indent=2,ensure_ascii=False)+'\n').encode())

def main():
    native=json.loads((E/'38068755097/probe-b-native/diagnostics/r13-encoder/encoder.json').read_bytes())
    assert native['status']=='VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES'
    spec=json.loads((E/'probe-b-native.json').read_bytes())
    by={(r['candidate'],r['file']):r for r in native['rows']}
    names=[e['name'] for e in spec['entries'] if not e.get('control')]
    files=sorted(f for n,f in by if n=='public595')
    assert len(files)==28 and len(names)==3
    parity=[]
    for n in names:
        assert all(by[n,f]['output_sha256']==by['public595',f]['output_sha256'] and by[n,f]['tokens_sha256']==by['public595',f]['tokens_sha256'] for f in files)
        parity.append({'candidate':n,'files':28,'tokens_identical_to_actual595':True,'output_bytes_identical_to_actual595':True,'total_output_bytes':sum(by[n,f]['output_bytes'] for f in files)})
    spec['entries']=[e for e in spec['entries'] if e['name']!='public514']
    spec.update(r22_mode='standard',native_only=False,native_encoder=False,native_encoder_references=[],synthetic_validation=False,description='R22 C two reversed original paired total-time blocks on three finite-byte-identical595 transfers, exact595 and same-source shadow. No Lean acceptance or private reward claim.')
    ns=[e['name'] for e in spec['entries']]
    spec['screen_orders']=[ns,ns[::-1]]
    write('screen-c',spec)
    en=next(e for e in spec['entries'] if e['name']=='r22-595-halfhead')
    write('gate-halfhead',{'r22_mode':'gate','candidate':en['name'],'path':en['path'],'files':en['hashes'],'expected_public_output_bytes':sum(by[en['name'],f]['output_bytes'] for f in files),'description':'Freeze exact original595 generic Lean and single real primary-capacity change. Native corpus parity already verified; full original obligation/extraction/axioms/roundtrip still required.'})
    write('preflight-c',{'gap':'Native three variants show exact output parity against595 but no total-time evidence, and no exact full gate. Current score geometry admits a narrow high-share region close to595; faster coordinates can also lose score.', 'substantial_change':'First original paired total-time experiment for the three actual newly released595 transfers. Parallel full gate isolates unchanged generic Lean on halfhead; prev16 proofs remain drafts.', 'minimum_effective_action':'Two reverse-ordered original 1warmup+11rep blocks with actual595 and hash-identical shadow; original gate for exact halfhead Rust/Lean.', 'decision':'Use actual measured coordinates plus same-source disagreement and current scorer replay to allocate independent confirmation or a distinct mechanism. No parameter sweep and no artificial delay.', 'cost_cap_minutes':{'screen_c':18,'gate_halfhead':25},'evidence':'evidence/round22/<run>/screen-c and gate-halfhead; native parent parity in native-parity.json', 'parity':parity})
    write('native-parity',{'status':'VERIFIED_FINITE_NATIVE_PARITY_TO_595','run_id':native['run_id'],'receipt':'evidence/round22/38068755097/probe-b-native/diagnostics/r13-encoder/encoder.json','pairs':parity,'scope':'28 finite corpus files only; not Lean correctness, timing or formal success.'})
    print('FROZEN',names,parity[0]['total_output_bytes'])

if __name__=='__main__':main()
