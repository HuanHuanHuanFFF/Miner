"""One fixed-mask e_lens specialization; all other masks keep the original fallback."""
from pathlib import Path
import argparse, hashlib, json, re

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'candidates/r3-432-fast3'
NAME='r11-fast-lensconst'
MASK=302256128


def sha(b):return hashlib.sha256(b).hexdigest()


def generate():
    raw={n:(BASE/n).read_bytes()for n in ('parse.rs','Parse.lean')}
    assert sha(raw['parse.rs'])=='bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef'
    assert sha(raw['Parse.lean'])=='e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04'
    source=raw['parse.rs'].decode()
    mat=re.search(r'pub const TF_LSYM: \[u8; 512\] = \[(.*?)\];',source,re.S);assert mat
    symbols=list(map(int,re.findall(r'\d+',mat.group(1))));assert len(symbols)==512
    assert f'pub const TM_LM: u32 = 302_256_128;' in source and f'pub const TZ_LM: u32 = 302_256_128;' in source
    # Exact original loop, including untouched entries0..2 and259.
    values=[0]*260;cur=0
    for x in range(3,259):
        c=symbols[x]%32
        if (MASK>>c)%2==1:cur=x
        values[x]=cur
    # Independent interval description from the original mask's four set bits.
    assert [i for i in range(32)if(MASK>>i)&1]==[12,18,25,28]
    allowed=[x for x in range(3,259)if symbols[x]in(12,18,25,28)]
    expected=[0 if x<3 or x==259 else max([0]+[a for a in allowed if a<=x])for x in range(260)]
    assert values==expected and values[:3]==[0,0,0] and values[259]==0 and max(values)==258
    table='\n'.join('            '+', '.join(map(str,values[i:i+20]))+','for i in range(0,260,20))
    helper='''/// R11: exact fixed e_lens result; arbitrary other masks retain the original builder.
#[inline(always)]
pub fn r11_e_lens(m: u32) -> [u16; 260] {
    if m == 302256128 {
        [
TABLE
        ]
    } else {
        let mut lens = [0u16; 260];
        e_lens(&mut lens, m);
        lens
    }
}

'''.replace('TABLE',table)
    changes=[];new=source
    for mask in ('lm','TZ_LM'):
        old=f'    let mut lens = [0u16; 260];\n    e_lens(&mut lens, {mask});'
        replacement=f'    let mut lens = r11_e_lens({mask});'
        assert new.count(old)==1;new=new.replace(old,replacement,1);changes.append((old,replacement))
    marker='/// The allowed piece for `rem` bytes left:'
    assert new.count(marker)==1;new=new.replace(marker,helper+marker,1)
    back=new.replace(helper,'',1)
    for a,b in reversed(changes):back=back.replace(b,a,1)
    assert back==source
    files={'parse.rs':new.encode(),'Parse.lean':raw['Parse.lean']}
    manifest={'candidate':NAME,'parent':'candidates/r3-432-fast3','parent_hashes':{n:sha(v)for n,v in raw.items()},'hashes':{n:sha(v)for n,v in files.items()},'attribution':{'source':'Public #432 via fast3','reference':'references/round3-public-432/PROVENANCE.md','author_hotkey':'5EAM7rJK571o7asrBBk6oozUZCRubR1tMiDKBNWmWhw66PRy','ownership':'Derivative of public miner code'},'mechanism':'Specialize fixed TM_LM/TZ_LM e_lens initialization as an exact precomputed array; arbitrary m uses unchanged zero-array plus original e_lens fallback. Only run1t/run_z initialization replaced.','proof_status':'UNADAPTED_PARENT_ONLY; real array-return extraction and LensBound helper proof required','expected_equivalent_to':'r3-432-fast3','equivalence_status':'260 fixed-mask values checked by two source models; native444/public equality and decode UNKNOWN','source_reversal':'Removing one helper and restoring two initialization pairs recovers exact parent bytes','asm_evidence':{'source':'evidence/round11/37734806965/fast-j/gate/cpu/r3-432-fast3-assembly.txt','parent_observation':'Runtime fixed-mask table loops reported/inspected at run1t dbb0..dbe4 and run_z17cb0..17cde, preceded by520-byte clear; candidate machine code UNKNOWN'},'cost_limit':'Initialization occurs once per relevant input. Public <=65536 inputs are only tiny-config12KB, tiny-app28KB, sparse40KB; their parent total times are roughly156/117/324us. Expected whole-axis opportunity may be far below0.823%; a real loop is not evidence of frontier gain.','stop':'One fixed version only. Native mismatch or no clear useful paired gain closes it; no parameter sweep or combination.','formal_submission_sent':False}
    files['manifest.json']=(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n').encode()
    model={'status':'VERIFIED_SOURCE_MODEL_ONLY','mask':MASK,'mask_hex':hex(MASK),'checked_indices':260,'unchanged_zero_indices':[0,1,2,259],'lengths':values,'TF_LSYM_sha256':sha(json.dumps(symbols).encode()),'native_rust':'NOT_RUN','all_other_masks':'Original zero initialization and original e_lens call retained verbatim in fallback; no finite sampling claim for all masks'}
    files['model.json']=(json.dumps(model,indent=2)+'\n').encode()
    files['PROOF_PLAN.md']=b'''# Unadapted proof checkpoint

Rust source is ready; parent Lean is byte-identical and UNADAPTED. No compiled proof is claimed.

The actual old e_lens_spec preserves LensBound (all260 entries<=258), not merely totality. After real extraction, add r11_e_lens_spec after e_lens_spec: fixed-mask branch proves LensBound of the concrete260-entry returned array; other-mask branch composes LensBound.init with e_lens_spec. run1t_spec/run_z_spec must consume the new helper result rather than the original repeat+e_lens pair. Inspect actual array-by-value return and tuple shape first. Keep original obligation, emitter and axiom whitelist. Do not add a new metadata assumption.

No lookup, skip, depth, routing, encoder or threshold changes. New array initialization may become memcpy, but this needs actual codegen and paired total-time measurement; source equality alone does not establish a gain.
'''
    return files


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args();files=generate();dest=ROOT/'candidates'/NAME
    if args.check:assert all((dest/n).read_bytes()==b for n,b in files.items())
    else:
        dest.mkdir(parents=True,exist_ok=True)
        for n,b in files.items():(dest/n).write_bytes(b)
    print(json.dumps({'candidate':NAME,'status':'SOURCE_READY_LEAN_UNADAPTED','hashes':{n:sha(b)for n,b in files.items()}},indent=2))


if __name__=='__main__':main()
