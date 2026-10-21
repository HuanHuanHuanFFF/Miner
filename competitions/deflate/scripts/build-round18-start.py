"""Two bounded mechanisms: dense DNA alphabet key and U16 transfer to new583."""
from pathlib import Path
import copy, hashlib, itertools, json

ROOT=Path(__file__).resolve().parents[1]
E=ROOT/'evidence/round18'

def write_candidate(name, parent, rust, lean, mechanism, difference, attribution):
    path=ROOT/'candidates'/name;assert not path.exists();path.mkdir()
    data={'parse.rs':rust.encode(),'Parse.lean':lean.encode()}
    assert all(0<len(v)<=524288 for v in data.values())
    for f,v in data.items():(path/f).write_bytes(v)
    hashes={f:hashlib.sha256(v).hexdigest() for f,v in data.items()}
    manifest={'candidate':name,'parent':parent,'hashes':hashes,'mechanism':mechanism,'difference_from_old_work':difference,'attribution':attribution,'proof_status':'DRAFT_UNCOMPILED_FOR_NEW_EXACT_PAIR','performance_status':'UNKNOWN','formal_submission_sent':False}
    (path/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
    return {'name':name,'path':str(path.relative_to(ROOT)).replace('\\','/'),'control':False,'hashes':hashes}

def control(name,path,formal):
    return {'name':name,'path':path,'formal_id':formal,'control':True,'anchor':name,'hashes':{f:hashlib.sha256((ROOT/path/f).read_bytes()).hexdigest() for f in ('parse.rs','Parse.lean')}}

def main():
    parent=ROOT/'candidates/r17-dna-nofold-proof1'
    rust=(parent/'parse.rs').read_text();lean=(parent/'Parse.lean').read_text()
    old='''        let k = pc_be8(s, i) >> 16;
        (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> 48) as usize % H'''
    new='''        // Dense six-symbol DNA hint: A/C/G/T have distinct two-bit codes.
        // Other bytes may collide; the original matcher still validates all bytes.
        let k = (pc_be8(s, i) >> 17) & 0x0303_0303_0303;
        let k = (k | (k >> 6)) & 0x000F_000F_000F;
        let k = (k | (k >> 12)) & 0x00FF_0000_00FF;
        let k = (k | (k >> 24)) & 4095;
        k as usize % H'''
    assert rust.count(old)==1
    rust=rust.replace(old,new)
    oldroute='pub fn p125_row4(input:&[u8],out:&mut[u32])->usize{pc_run1::<65536>(input,out,16,0,0,0)}'
    assert rust.count(oldroute)==1
    rust=rust.replace(oldroute,oldroute.replace('65536','4096'))
    # Exhaust the intended six-symbol key model; this says nothing about parse correctness.
    keys=set()
    for seq in itertools.product(b'ACGT',repeat=6):
        k=(int.from_bytes(bytes(seq),'big')>>1)&0x030303030303
        k=(k|(k>>6))&0x000F000F000F;k=(k|(k>>12))&0x00FF000000FF;k=(k|(k>>24))&4095
        keys.add(k)
    assert len(keys)==4096
    dna=write_candidate('r18-dna-pack6',parent.name,rust,lean,
        'Replace mixed six-byte DNA hash by collision-free two-bit six-symbol hints for uppercaseACGT and a4096-head table. Preserve dense insertion, no-fold emission, normal PC branches and byte validation.',
        'R14/R17 used a65536-entry multiplied key. New representation eliminates alphabet-key collisions and cuts this table from256KiB to16KiB; no arbitrary delay or search-budget sweep. NonACGT collisions remain possible and require full decode/byte checks.',
        json.loads((parent/'manifest.json').read_bytes()).get('attribution',{'parent':parent.name}))
    dna.update(anchor='dna582',comparison_baseline='dna582',native_decode_reference='dna582')
    parent=ROOT/'references/round18-public-583';rust=(parent/'parse.rs').read_text();lean=(parent/'Parse.lean').read_text()
    old=(ROOT/'references/round13-public-514/parse.rs').read_text();new=(ROOT/'candidates/r13-514-abs15/parse.rs').read_text()
    marker='pub fn pc_f_link<const H: usize>';end='/// Structured binaries (class 3)'
    a=rust.index(marker);b=rust.index(end,a);oa=old.index(marker);ob=old.index(end,oa);assert rust[a:b]==old[oa:ob]
    na=new.index(marker);nb=new.index(end,na)
    helper=new[new.index('/// R13 modular predecessor hint.'):new.rfind('#[inline(always)]',0,na)]
    at=rust.rfind('#[inline(always)]',0,a);rust=rust[:at]+helper+rust[at:a]+new[na:nb]+rust[b:]
    proven=(ROOT/'candidates/r13-514-abs15/Parse.lean').read_text()
    oldproof=(ROOT/'references/round13-public-514/Parse.lean').read_text()
    a=lean.index('theorem f_link_spec');b=lean.index('end PC',a);oa=oldproof.index('theorem f_link_spec');ob=oldproof.index('end PC',oa);assert lean[a:b]==oldproof[oa:ob]
    na=proven.index('theorem f_link_spec');nb=proven.index('end PC',na)
    helper=proven[proven.index('/-- Reconstructed coordinates are hints;'):proven.rfind('@[local step]',0,na)]
    at=lean.rfind('@[local step]',0,a);lean=lean[:at]+helper+lean[at:a]+proven[na:nb]+lean[b:]
    pc=write_candidate('r18-583-abs15','public583',rust,lean,
        'Transfer compact modularU16 predecessor hints into exact newly public583 PC code while preserving every583route and parameter.',
        'Mechanism is inherited, not novel. New583 formal size36.6063565 is below539; its baseline still missed speed admission. Existing514/561 outcomes do not establish this newroute mix; benchmark the whole actual source and both same-source controls.',
        {'source':'Official public583, original headers retained','reference':'references/round18-public-583/source-receipt.json','mechanism':'R13 abs15; no claim of independent whole-parser invention'})
    pc.update(anchor='public583',comparison_baseline='public583',native_decode_reference='public583')
    spec=json.loads((E/'baselines-b-native.json').read_bytes())
    spec['entries']=[e for e in spec['entries'] if e['name'] in ('probe3','r3-432-fast3','public432','public514')]
    spec['entries'] += [control('dna582','candidates/r17-dna-nofold-proof1','582'),control('public583','references/round18-public-583','583'),dna,pc]
    spec.update(native_encoder_references=['dna582','public583'],description='Two actual derivatives: newDNA alphabet/table representation and existingU16 mechanism on newly released583. Minimum action: exact original encoder,28files,decode and parent514calibration. Cap20job-minutes. Changes with useful size/target tradeoff receive standard paired timing; worse-time proxy alone never vetoes potential share. Proofs remain drafts.')
    spec['screen_orders']=[[e['name'] for e in spec['entries']],[e['name'] for e in reversed(spec['entries'])]]
    (E/'mechanisms-d-native.json').write_text(json.dumps(spec,indent=2)+'\n')
    (E/'dna-pack6-key-preflight.json').write_text(json.dumps({'status':'VERIFIED_FINITE_KEY_MODEL','uppercase_ACGT_six_symbol_keys':4096,'unique_keys':len(keys),'scope':'Key mapping only. Rust compiler, parser correctness, nonACGT quality, performance and fullgate remain untested.'},indent=2)+'\n')
    print(json.dumps({'candidates':[dna,pc]}))

if __name__=='__main__':
    main()
