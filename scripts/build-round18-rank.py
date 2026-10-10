"""Controlled A-planner ranking conventions, inspired by the verified573 family."""
from pathlib import Path
import importlib.util,json

ROOT=Path(__file__).resolve().parents[1]

def main():
    sp=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    p=ROOT/'candidates/r18-586-selective-rf';original=(p/'parse.rs').read_text();proof=(p/'Parse.lean').read_text();a=original.index('pub fn a_dp_pass(');b=original.index('/// Follows the planned path',a);body=original[a:b]
    init='let mut best = (1048576u32.wrapping_add(lit[s[i] as usize])) << 9;';store='a_store_choice(cost, ch, i, best, bd, nxt);'
    assert body.count(init)==1 and body.count('<< 9) | l;')==3 and body.count(store)==1 and body.count('.wrapping_add(bias)')==2
    entries=[]
    for name,penalty in [('r18-586-long-ties',0),('r18-586-token2',2)]:
        part=body.replace(init,f'let mut best = (1048576u32.wrapping_add(lit[s[i] as usize].wrapping_add({penalty}))) << 9 | 511;')
        part=part.replace('<< 9) | l;','<< 9) | (l ^ 511);').replace(store,'a_store_choice(cost, ch, i, best ^ 511, bd, nxt);')
        if penalty:part=part.replace('.wrapping_add(bias)',f'.wrapping_add({penalty}).wrapping_add(bias)')
        rust=original[:a]+part+original[b:]
        e=m.write_candidate(name,p.name,rust,proof,
            'Prefer longer matches whenpackedprimaryDPcosts tie; convertlength bits back before the unchangedchoice writer.'+(' Add2units(1/32bit inthis64unit model) perliteral/match edge todiscourage excess tokens.'if penalty else' No primarycost penalty.'),
            'The published550/verified573 planner rankswithlength XOR511 and2unit peredgecost;586A usesascendinglength ties. Currentfixedfrontier has meaningfulquality-only targetspace at0.003-0.0045pp, but actualHuffman/block effects mustbechecked. Two controlledrankingvariants, not presumedbyteortime gains.',
            {'parent':'references/round18-public-586/source-receipt.json','ranking_reference':'candidates/r15-550-base-only/parse.rs:Z307/Z314','ownership':'Originalpublicauthors retained; convention transfer isnotanindependent engine invention.'})
        e.update(anchor='public586',comparison_baseline='selective586',native_decode_reference='selective586');entries.append(e)
    s=json.loads((ROOT/'evidence/round18/model-aa-native.json').read_bytes());s['entries']=[e for e in s['entries']if e.get('control')]+entries;s['screen_orders']=[[e['name']for e in s['entries']],[e['name']for e in reversed(s['entries'])]]
    s['description']='ACnative: testexactbit-cost tie convention, thenplusknown2unit tokenregularizer from573. Preservematch discovery,pass budgets,router andRFselection. Originalencoder/decode over28files, cap25job-minutes. Nativebytes canconfirmorrefutequality hypothesis; do notinfer performance orpayability. Fullgate/freshconfirmation neededforeachchangedRust.'
    (ROOT/'evidence/round18/rank-ac-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());print(json.dumps(entries))

if __name__=='__main__':main()
