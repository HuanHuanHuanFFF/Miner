"""Two mechanism changes at the current fast frontier; no gate claims."""
from pathlib import Path
import importlib.util, json, re

ROOT=Path(__file__).resolve().parents[1]
E=ROOT/'evidence/round20'

def main():
    sp=importlib.util.spec_from_file_location('writer',ROOT/'scripts/build-round18-start.py')
    w=importlib.util.module_from_spec(sp);sp.loader.exec_module(w)
    parent=ROOT/'candidates/r18-539-csv-lazy-content'
    rust,lean=[(parent/f).read_text() for f in ('parse.rs','Parse.lean')]
    variants=[]
    # Reconstruct the same low-15-bit hint semantics previously tested on539,
    # now actually reduce representation size. Existing byte checks remain.
    compact=rust.replace('[u32; 32768]','[u16; 32768]').replace('[0u32; 32768]','[0u16; 32768]')
    compact=compact.replace('prev[i % 32768] = head[a];','prev[i % 32768] = head[a] as u16;')
    compact=compact.replace('prev[c2 % 32768] as usize','c2.wrapping_sub(c2.wrapping_sub(prev[c2 % 32768] as usize) & 32767)')
    compact=compact.replace('prev[c % 32768] as usize','c.wrapping_sub(c.wrapping_sub(prev[c % 32768] as usize) & 32767)')
    assert compact!=rust and compact.count('[0u16; 32768]')==2
    variants.append(('r20-539-csv-prev16',compact,lean,
        'Use 16-bit circular predecessor hints in PC/PIM, halve predecessor storage and initialization, reconstruct the closest earlier low15-bit coordinate. Keep full-width head positions and byte-validated matching.',
        'R18 isolated modular semantics in U32 storage and found only3B effect. R13 measured other parser families. This tests actual narrower storage on539 with CSV improvement; proof types remain unadapted until worthwhile signal.'))
    single=rust
    changes=[]
    # Routes with four-byte keys and only one predecessor: remove that entire
    # auxiliary chain, preserving the original head-table search and skip policy.
    for row in [10,16,18]:
        pattern=rf'(pub fn p135_row{row}\(input:&\[u8\],out:&mut\[u32\]\)->usize\{{)pc_run1c::<32768>\(input,out,(\d+),0,1000000,4294967295,1,4\)(\}})'
        single,n=re.subn(pattern,lambda m:m[1]+'pc_run1::<32768>(input,out,'+m[2]+',0,1000000,4294967295)'+m[3],single)
        assert n==1;changes.append(row)
    proof=lean
    for row in changes:
        old=f'rw [slot.p135_row{row}]\n exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)'
        new=f'rw [slot.p135_row{row}]\n exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)'
        assert proof.count(old)==1;proof=proof.replace(old,new)
    variants.append(('r20-539-csv-singlehead',single,proof,
        'Remove the auxiliary predecessor chain from generic4-byte text routes10/16/18. Retain original head size, skip policy, no lazy search and other specialized engines.',
        'Tests the real time/quality return of second candidates on539 text, instead of merely lowering a parameter. Quality loss will be scored jointly with speed; no faster-only promotion.'))
    entries=[]
    for name,r,p,mechanism,difference in variants:
        en=w.write_candidate(name,parent.name,r,p,mechanism,difference,{'source':'references/round18-public-539/source-receipt.json','parent':'candidates/r18-539-csv-lazy-content/manifest.json','ownership':'Original539 author and R18 CSV transfer retained.'})
        en.update(anchor='public539',comparison_baseline='csv18',native_decode_reference='public539');entries.append(en)
    old=json.loads((ROOT/'evidence/round18/screen-bn.json').read_bytes())
    controls=[e for e in old['entries'] if e['name'] in ('probe3','r3-432-fast3','public432','public514','public539','public539-shadow')]
    c=w.control('csv18','candidates/r18-539-csv-lazy-content','539');c.pop('formal_id');c['anchor']='public539';controls.append(c)
    spec={**json.loads((ROOT/'evidence/round19/probe-a-native.json').read_bytes()),'entries':controls+entries,'snapshot_pages':'evidence/round20/official-start/pareto-pages.json','native_encoder_references':['public539'],'r20_mode':'native','r20_role':'discovery','description':'R20 A: actual original encoding/decode on28files for narrower predecessor representation and head-only text mechanisms. 15minute job cap. Quality opportunity earns paired original timing; inherited proof is draft.'}
    spec.pop('r19_mode',None);spec.pop('r19_role',None)
    names=[e['name']for e in spec['entries']];spec['screen_orders']=[names,names[::-1]]
    (E/'probe-a-native.json').write_text(json.dumps(spec,indent=2)+'\n')
    (E/'preflight-a.json').write_text(json.dumps({'gap':'Current595 controls24.4064% at time0.431829610,size36.578142795. CSV18 projects slightly better size but noisy time. Need real speed improvement or meaningful size tradeoff to challenge that region.','changes':[{'candidate':x[0],'mechanism':x[3],'difference':x[4]} for x in variants],'minimum':'Actual full28file original encoder, token/hash and independent decode. No timing claim.','decision':'Retain quality within or better than current top1 region, then original paired total time and scoring sensitivity. Reject only exact unhelpful tradeoffs; reserve independent confirmation and gate.','cost_cap_minutes':15,'proof_risk':'prev16 has unadapted array types and modular hint lemmas; singlehead maps to existing generic PC.run1 lemma. Both require new exact full gate.','evidence':'evidence/round20/<run>/probe-a-native/diagnostics'},indent=2)+'\n')
    print(json.dumps({'candidates':[e['name']for e in entries]}))

if __name__=='__main__':main()
