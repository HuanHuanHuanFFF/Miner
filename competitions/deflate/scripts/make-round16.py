"""Controlled useful-compression probes from the exact public-gated R13 source."""
from pathlib import Path
import copy, hashlib, json

ROOT=Path(__file__).resolve().parents[1]
E=ROOT/'evidence/round16'
def save(p,v):
    p.parent.mkdir(parents=True,exist_ok=True)
    p.write_bytes((json.dumps(v,indent=2,ensure_ascii=False)+'\n').encode())

def main():
    parent=ROOT/'candidates/r13-514-abs15'
    rust=(parent/'parse.rs').read_text();lean=(parent/'Parse.lean').read_bytes()
    inherited=json.loads((parent/'manifest.json').read_bytes())
    assert hashlib.sha256((parent/'parse.rs').read_bytes()).hexdigest()==inherited['hashes']['parse.rs']
    old=json.loads((ROOT/'evidence/round14/probe-a-native.json').read_bytes())
    controls=[copy.deepcopy(e) for e in old['entries'] if e['control'] and e['name'] in ('probe3','r3-432-fast3','public432','public514','r13-514-abs15')]
    assert len(controls)==5
    needle='pub fn p125_row1(input:&[u8],out:&mut[u32])->usize{pc_run1c::<32768>(input,out,4,0,1000000,4294967295,1,4)}'
    assert rust.count(needle)==1
    variants=[
        ('depth2','4,0,1000000,4294967295,2,4','A second predecessor in the original64-bit-hash text path. R15 tested this on changed32-bit hash; restoring originalhash may avoid its quality loss. No additive gain assumed.'),
        ('lazy8','4,8,1000000,4294967295,1,4','One-byte lookahead only for matches shorter than8; existing gain rule chooses a next-position match. This buys actual match quality, unlike the rejected matched-ahead CPU rewrite.'),
        ('skip5','5,0,1000000,4294967295,1,4','Delay miss skip acceleration in the text path. Test whether missed weak-repetition matches repay the extra probes; no route or public-length changes.')]
    entries=controls[:]
    for suffix,args,mechanism in variants:
        name='r16-514-'+suffix;dest=ROOT/'candidates'/name
        text=rust.replace(needle,needle.replace('4,0,1000000,4294967295,1,4',args))
        data={'parse.rs':text.encode(),'Parse.lean':lean};dest.mkdir(exist_ok=True)
        for f,b in data.items():
            assert not(dest/f).exists() or (dest/f).read_bytes()==b
            (dest/f).write_bytes(b)
        hashes={f:hashlib.sha256(b).hexdigest() for f,b in data.items()}
        save(dest/'manifest.json',{'candidate':name,'parent':'r13-514-abs15','formal_anchor_id':'514','comparison_baseline':'r13-514-abs15','hashes':hashes,'attribution':inherited['attribution'],'mechanism':mechanism,'proof_status':'PARENT_PROOF_UNCOMPILED_FOR_NEW_CONSTANTS; NO_INHERITED_GATE','performance_status':'UNKNOWN','formal_submission_sent':False})
        entries.append({'name':name,'path':'candidates/'+name,'control':False,'anchor':'public514','comparison_baseline':'r13-514-abs15','native_decode_reference':'r13-514-abs15','hashes':hashes})
    spec={**old,'entries':entries,'snapshot_pages':'evidence/round16/official-start/pareto-pages.json','screen_blocks':2,'screen_orders':[[e['name']for e in entries],[e['name']for e in reversed(entries)]],'extract_candidates':[],'gate_candidates':[],'native_only':True,'native_encoder':True,'native_encoder_references':['r13-514-abs15'],'description':'R16 A: three separate text-match quality mechanisms. Exact original encoder byte/decode screening first. No extra timing delay, no route tuning, no proof inheritance. Changed-byte directions need paired total timing; lack of meaningful byte improvement closes the quality hypothesis.'}
    save(E/'quality-a-native.json',spec)
    print(json.dumps({'candidates':[e['name']for e in entries if not e['control']]}))

if __name__=='__main__':main()
