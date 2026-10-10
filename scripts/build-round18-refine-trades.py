"""Two distinct RF cost trades grounded in the new586phase/byte observations."""
from pathlib import Path
import importlib.util,json,re

ROOT=Path(__file__).resolve().parents[1]

def main():
    sp=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    p=ROOT/'references/round18-public-586';original=(p/'parse.rs').read_text();proof=(p/'Parse.lean').read_text()
    pattern=r'pub const REFINE: \[usize; 32\] = (\[[^\n]+);';match=re.search(pattern,original);assert match
    table=json.loads(match.group(1));assert len(table)==32
    keep={13,25,26,29};select=[v if i in keep else 0 for i,v in enumerate(table)]
    rust=original[:match.start()]+f'pub const REFINE: [usize; 32] = {json.dumps(select)};'+original[match.end():]
    attribution={'source':'Official public586','reference':'references/round18-public-586/source-receipt.json','cost_evidence':'evidence/round18/37976329057/refine-q-native/diagnostics/r18-functions/functions.json'}
    selective=m.write_candidate('r18-586-selective-rf','public586',rust,proof,
        'Keep the existingRF refinements for multibyte and selectedbinary routingclasses13/25/26/29; retain every originalbase engine but skipRF elsewhere. No newclassifier predicates.',
        'QmeasuredRF2.113s of4.513s instrumentedparse, yetonly1740B totalgain. These fourobservedclasses account for1062B gain withabout390.6ms inclusiveRF; expensiveDNA/prose alone spend850ms for287B. This is content-class budget allocation, not a claimthat sums equalofficial-axis gain.',attribution)
    needle='    let n0 = if e[0] == 4 {';assert original.count(needle)==1
    rust=original.replace(needle,'''    let n0 = if REFINE[cls % 32] != 0 {
        // RF constructs its own match cache. Test whether a costly seed search is necessary.
        let seed: Vec<u32> = Vec::new();
        emit(input, &seed, out)
    } else if e[0] == 4 {''')
    seed=m.write_candidate('r18-586-rf-only','public586',rust,proof,
        'ForRF-enabledclasses, replace the expensivebase search with a validliteral seed emitted by the existingchecker; keepRFmatch-cache construction, fitting rounds and exact-cost selection. RF-disabledclasses retain originalbase behavior.',
        'Qshowsbase search andRFcache/search bothconsume substantialwork. This tests whetherRFcanrecover usefulcompression fromits owncandidates without payingtwosearches. Quality loss isUNKNOWN; it is a distinctstagecomposition hypothesis, not anotherround-count sweep. Proofneedsnewseedbranch verification.',attribution)
    spec=json.loads((ROOT/'evidence/round18/refine-q-native.json').read_bytes());spec.pop('r18_function_profile');spec.pop('r15_profile_entry');spec.pop('r15_profile_functions')
    spec['entries']=[e for e in spec['entries']if e.get('control')]+[m.control('base586','candidates/r18-586-base-only','586'),selective,seed]
    spec['entries'][-3].pop('formal_id');spec['entries'][-3]['anchor']='public586'
    for e in [selective,seed]:e.update(anchor='public586',comparison_baseline='public586',native_decode_reference='public586')
    spec['native_encoder_references']=['public586','base586'];spec['screen_orders']=[[e['name']for e in spec['entries']],[e['name']for e in reversed(spec['entries'])]]
    spec['description']='Snative: distinctRFbudget allocation andRF-onlycomposition afteractualphase profile. Compare original586,base-only andtwonewprograms withoriginalencoder,28filesanddecode. Cap25job-minutes. Selectivequalityshouldrestoreits fourclasses; RF-only mayfailquality entirely. Actualbyte/time results decide furtherinvestment; no inheritedgate ormodelgain.'
    (ROOT/'evidence/round18/refine-s-native.json').write_bytes((json.dumps(spec,indent=2)+'\n').encode());print(json.dumps([selective,seed]))

if __name__=='__main__':main()
