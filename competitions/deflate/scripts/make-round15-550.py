"""Measured-cost-driven 550 ablations, not a blind parameter sweep."""
from pathlib import Path
import hashlib,json,copy
ROOT=Path(__file__).resolve().parents[1]
def main():
    p=ROOT/'references/round15-public-550';rust=(p/'parse.rs').read_text();lean=(p/'Parse.lean').read_text();src=json.loads((p/'source-receipt.json').read_bytes())
    old='pub fn parse(input:&[u8],out:&mut[u32])->usize {let nt=SFbase(input,out);if SFenabled(input) {let plan=SFshape(input,out,nt);Z167(input,&plan,out)}else{nt}}';assert rust.count(old)==1
    base=rust.replace(old,'pub fn parse(input:&[u8],out:&mut[u32])->usize {SFbase(input,out)}')
    a=lean.rfind('theorem parse_spec ');b=lean.index('\nend Submission',a);proof=lean[:a]+'''theorem parse_spec (input:I) (out:U)
    (hlen:input.length ≤ out.length) :
    slot.parse input out ⦃ Y112P1! ⦄ := by
  rw [slot.parse]
  exact SFbase_spec input out hlen
'''+lean[b:]
    old='pub const SFDEPTH:usize=2;';assert rust.count(old)==1
    depth=rust.replace(old,'pub const SFDEPTH:usize=1;')
    variants=[('r15-550-base-only',base,proof,'Remove the measured21percent SFshape layer and retain the exact original proven-family SFbase plus its original output. Quantify the actual encoded size loss before timing.'),('r15-550-shape-depth1',depth,lean,'Retain seam repair but halve the bounded additional predecessor search. Function profile showed SFsmallmatches about0.312s and SFsolve about0.231s; fewer candidates may also reduce solver work. Actual quality loss is unknown.')]
    s=json.loads((ROOT/'evidence/round15/profile-a-native.json').read_bytes());entries=copy.deepcopy(s['entries']);e=next(e for e in entries if e['name']=='public550');shadow=copy.deepcopy(e);shadow['name']='public550-shadow';shadow.pop('formal_id');entries.append(shadow)
    for name,code,proof,mechanism in variants:
        d=ROOT/'candidates'/name;d.mkdir(exist_ok=True);data={'parse.rs':code.encode(),'Parse.lean':proof.encode()}
        for f,raw in data.items():assert not(d/f).exists()or(d/f).read_bytes()==raw;(d/f).write_bytes(raw)
        hashes={f:hashlib.sha256(v).hexdigest()for f,v in data.items()}
        m={'candidate':name,'parent':'public550','formal_anchor_id':'550','comparison_baseline':'public550','hashes':hashes,'mechanism':mechanism,'difference_from_old_work':'Newly profiled high-compression public550 route; R14 only inspected its source. No claim that phase fractions equal official-axis savings.','attribution':{'source':'Original official550 headers/source/proof retained','reference':'references/round15-public-550/source-receipt.json'},'proof_status':'DRAFT_UNCOMPILED_FOR_NEW_SOURCE','performance_status':'UNKNOWN','formal_submission_sent':False}
        (d/'manifest.json').write_bytes((json.dumps(m,indent=2)+'\n').encode());entries.append({'name':name,'path':f'candidates/{name}','control':False,'anchor':'public550','comparison_baseline':'public550','native_decode_reference':'public550','hashes':hashes})
    s.update(entries=entries,r15_phase_profile=False,native_encoder=True,native_encoder_references=['public550'],screen_orders=[[e['name']for e in entries],[e['name']for e in reversed(entries)]],description='R15 E: actual original encoder size of two phase-cost-driven550 ablations. Base-only measures the whole21percent diagnostic layer tradeoff; depth1 reduces specific search. No timing, proof or 1percent-share promotion from native bytes alone.')
    (ROOT/'evidence/round15/high-e-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());print(json.dumps({'candidates':[v[0]for v in variants]}))
if __name__=='__main__':main()
