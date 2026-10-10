"""Time only the combination whose actual native quality equals its chain parent."""
from pathlib import Path
import json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round22'

def main():
    n=json.loads((E/'38070707456/probe-i-native/diagnostics/r13-encoder/encoder.json').read_bytes())
    assert n['status']=='VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES'
    rs={(r['candidate'],r['file']):r for r in n['rows']}
    name='r22-595-chain-halfhead';fs=sorted(f for k,f in rs if k=='chain');assert len(fs)==28
    assert all(rs[name,f]['output_sha256']==rs['chain',f]['output_sha256'] and rs[name,f]['tokens_sha256']==rs['chain',f]['tokens_sha256'] for f in fs)
    s=json.loads((E/'probe-i-native.json').read_bytes())
    s['entries']=[e for e in s['entries'] if e['name']!='public514']
    half=next(e for e in json.loads((E/'screen-c.json').read_bytes())['entries'] if e['name']=='r22-595-halfhead')
    half={**half,'name':'halfhead','control':True};half.pop('native_decode_reference',None)
    s['entries'].insert(-1,half)
    s.update(r22_mode='standard',native_only=False,native_encoder=False,native_encoder_references=[],synthetic_validation=False,r22_role='discovery',r18_role='discovery',description='R22 K final boundedscreen: actualchain/halfhead and same-source595controls, 2 reversed originalpairedblocks of frozencombinedcandidate. Native28files tokens/bytes equalchain. No fullgate/independentconfirmation claim for this newpair.')
    ns=[e['name'] for e in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    p=E/'screen-k.json';assert not p.exists();p.write_bytes((json.dumps(s,indent=2)+'\n').encode())
    plan={'gap':'Actual combined source preserves chain7238B improvement but no speed evidence. Components mixed and gainscannot beadded.','substantial_change':'One originaltotal-time experiment for this one frozencombinedtable/search source, actualtwo componentcontrols included.','minimum':'Two reverse-ordered original1warmup11repblocks with595identicalshadow and componentparents; no gatedfullacceptance claim.','decision':'Preserve any actualtargetspace but require a futurefullgate and freshfinalconfirmation; no laternewjobs, no artificial delay, no promotionofsinglepeak. Ifcomplete data notcollected bydeadline, report pending/incompletehonestly.','cost_cap_minutes':12,'measured_recent_screen_wall_minutes':[12,11],'evidence':'evidence/round22/<run>/screen-k/gate','native_parity_receipt':'evidence/round22/38070707456/probe-i-native/diagnostics/r13-encoder/encoder.json','full_gate':'NOT_RUN','independent_confirmation':'NOT_RUN'}
    (E/'preflight-k.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode())
    print('FROZEN screen-k',len(s['entries']))

if __name__=='__main__':main()
