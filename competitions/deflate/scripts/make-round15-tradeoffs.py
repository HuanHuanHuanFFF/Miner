"""Two useful-compression tradeoffs from the exact R14-gated hash32 source."""
from pathlib import Path
import hashlib,json,copy
ROOT=Path(__file__).resolve().parents[1]
def main():
    parent=ROOT/'candidates/r14-514-hash32';raw=(parent/'parse.rs').read_bytes();proof=(parent/'Parse.lean').read_bytes();cert=json.loads((parent/'VERIFICATION.json').read_bytes())
    assert hashlib.sha256(raw).hexdigest()==cert['files']['parse.rs']and hashlib.sha256(proof).hexdigest()==cert['files']['Parse.lean']
    text=raw.decode();variants=[]
    a=text.index('pub fn pc_f_try(');b=text.index('pub fn pc_f_deepen(',a);region=text[a:b];needle='if m > l && m >= minl {';assert region.count(needle)==1
    gain=text[:a]+region.replace(needle,'if m > l && m >= minl && pc_gain(m, d2) > pc_gain(l, d) {')+text[b:]
    variants.append(('r15-hash32-chain-gain',gain,'Adopt a longer older match only when the existing gain estimate improves.','R14 isolated gain filtering saved1304B but cost time; combine it with independently confirmed hash32 and measure the actual new pair. Real compression gain, no artificial delay.'))
    needle='pub fn p125_row1(input:&[u8],out:&mut[u32])->usize{pc_run1c::<32768>(input,out,4,0,1000000,4294967295,1,4)}';assert text.count(needle)==1
    deeper=text.replace(needle,needle.replace('4294967295,1,4','4294967295,2,4'))
    variants.append(('r15-hash32-chain-depth2',deeper,'Try one additional existing predecessor at initial text matches; all helpers and bounds already exist.','The R14 source optimized key mixing. This spends additional real search to improve encoded size, targeting an interior speed/size tradeoff rather than another same-size timing tweak.'))
    old=json.loads((ROOT/'evidence/round14/screen-b.json').read_bytes());entries=[copy.deepcopy(e)for e in old['entries']if e['control']and e['name']!='r13-514-abs15']
    entries.append({'name':'r14-514-hash32','path':'candidates/r14-514-hash32','control':True,'anchor':'public514','hashes':cert['files']})
    for name,rust,mechanism,difference in variants:
        dest=ROOT/'candidates'/name;dest.mkdir(exist_ok=True);files={'parse.rs':rust.encode(),'Parse.lean':proof}
        for f,v in files.items():assert not(dest/f).exists()or(dest/f).read_bytes()==v;(dest/f).write_bytes(v)
        hashes={f:hashlib.sha256(v).hexdigest()for f,v in files.items()}
        manifest={'candidate':name,'parent':'r14-514-hash32','formal_anchor_id':'514','comparison_baseline':'r14-514-hash32','hashes':hashes,'mechanism':mechanism,'difference_from_old_work':difference,'attribution':json.loads((parent/'manifest.json').read_bytes())['attribution'],'proof_status':'EXACT_PARENT_LEAN_UNCOMPILED_FOR_NEW_RUST','performance_status':'UNKNOWN','formal_submission_sent':False}
        (dest/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode());entries.append({'name':name,'path':f'candidates/{name}','control':False,'anchor':'public514','comparison_baseline':'r14-514-hash32','native_decode_reference':'r14-514-hash32','hashes':hashes})
    spec={**old,'entries':entries,'snapshot_pages':'evidence/round15/official-start/pareto-pages.json','native_only':True,'native_encoder':True,'native_encoder_references':['r14-514-hash32'],'extract_candidates':[],'gate_candidates':[],'research_synthetic_candidates':[],'screen_orders':[[e['name']for e in entries],[e['name']for e in reversed(entries)]],'description':'R15 tradeoff B native screen of two real compression mechanisms on the exact gated hash32 parent. Goal>=1percent competition pool; no intentional delays. Actual encoded size before paired time and independent confirmation.'}
    (ROOT/'evidence/round15/tradeoff-b-native.json').write_bytes((json.dumps(spec,indent=2)+'\n').encode());print(json.dumps({'candidates':[v[0]for v in variants]}))
if __name__=='__main__':main()
