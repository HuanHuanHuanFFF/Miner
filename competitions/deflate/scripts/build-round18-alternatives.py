"""Entropy-only DNA and high-quality579without its repeated seam-repair stage."""
from pathlib import Path
import importlib.util, json

ROOT=Path(__file__).resolve().parents[1]

def main():
    s=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(s);s.loader.exec_module(m)
    p=ROOT/'candidates/r17-dna-nofold-proof1';rust=(p/'parse.rs').read_text();lean=(p/'Parse.lean').read_text()
    old='pub fn p125_row4(input:&[u8],out:&mut[u32])->usize{pc_run1::<65536>(input,out,16,0,0,0)}'
    assert rust.count(old)==1;rust=rust.replace(old,'pub fn p125_row4(input:&[u8],out:&mut[u32])->usize{q4_lit_all(input,out)}')
    a=lean.index('theorem p125_row4_spec');b=lean.index('@[local step]',a);part=lean[a:b]
    needle='exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)';assert part.count(needle)==1
    lean=lean[:a]+part.replace(needle,'exact Q4.lit_all_spec input out hlen')+lean[b:]
    dna=m.write_candidate('r18-dna-literals',p.name,rust,lean,
        'Use the existing proven-family literal emitter on the existing DNA route, allowing the fixed dynamic Huffman encoder to exploit alphabet entropy without LZ match-search overhead.',
        'A distinct engine tradeoff afterpack6 added16312B and22345tokens ongenome. ExistingDNAoutput is31.62percent; literalentropy plausibly lowersbytes but increasesencoder tokenwork. Measureboth; the all-literalpoint is not inferred to be faster. No new routing predicate.',
        json.loads((p/'manifest.json').read_bytes()).get('attribution',{'parent':p.name}))
    dna.update(anchor='dna582',comparison_baseline='dna582',native_decode_reference='dna582')
    p=ROOT/'references/round18-public-579';rust=(p/'parse.rs').read_text();lean=(p/'Parse.lean').read_text()
    old='else if SFenabled(input) {let plan=SFshape(input,out,nt);Z167(input,&plan,out)}else{nt}'
    assert rust.count(old)==1;rust=rust.replace(old,'else{nt}')
    high=m.write_candidate('r18-579-base-tiny','public579',rust,lean,
        'Retain579exactbase engines and its tiny-input exact-cost chooser; remove the general SFshape seam-repair pass. Original routes, base search budgets and final validator remain unchanged.',
        'Revisits successful550phase removal on a materially stronger published579base and preserves its newtinychooser. New fullversion size is33.832698public,34.095612formal; loss after removingrepair is unknown. This is transferred phase ablation, not a new whole-parser invention.',
        {'source':'Official public579','reference':'references/round18-public-579/source-receipt.json','inherited_mechanism':'R15phase ablation with differentbase andtiny behavior'})
    high.update(anchor='public579',comparison_baseline='public579',native_decode_reference='public579')
    spec=json.loads((ROOT/'evidence/round18/mechanisms-d-native.json').read_bytes())
    spec['entries']=[e for e in spec['entries'] if e['name'] in ('probe3','r3-432-fast3','public432','public514','dna582')]
    spec['entries'] += [m.control('public579','references/round18-public-579','579'),dna,high]
    spec.update(native_encoder_references=['dna582','public579'],description='Hnative: compare two genuinely different engine-work trades. DNAentropyonly may savebytes but overload sharedencoder;579retains its tinychooser while removinggeneralrepair. Originalencoder/decode on28files; cap20job-minutes. Useactualpublicsize and currenttargetmap to decide pairedtiming, not parser-only intuition. Exactpair fullgate stillpending.')
    spec['screen_orders']=[[e['name'] for e in spec['entries']],[e['name'] for e in reversed(spec['entries'])]]
    (ROOT/'evidence/round18/alternatives-h-native.json').write_text(json.dumps(spec,indent=2)+'\n')
    print(json.dumps({'candidates':[dna,high]}))

if __name__=='__main__':
    main()
