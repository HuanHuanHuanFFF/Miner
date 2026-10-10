"""Test reuse of the previous encoder-block model instead of repeated resampling."""
from pathlib import Path
import importlib.util,json

ROOT=Path(__file__).resolve().parents[1]

def main():
    sp=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    p=ROOT/'candidates/r18-586-selective-rf';original=(p/'parse.rs').read_text();proof=(p/'Parse.lean').read_text();start=original.index('pub fn a_engine(');loop=original.index('        while k < passes {',start);a=original.index('\n',loop)+1;b=original.index('            k += 1;',a);body=original[a:b]
    assert 'a_sample_pass('in body and 'a_dp_pass('in body and body.count('a_should_sample')==1
    entries=[]
    for name,condition,description in [
        ('r18-586-carry-model','p0 == 0 || !a_should_sample(k, sampled, passes, pe, p0)','Forlaterblocks carry the model directly, skipping iterations that currentlyrequest sampling.'),
        ('r18-586-carry-one','p0 == 0 || k == 0 || !a_should_sample(k, sampled, passes, pe, p0)','Forlaterblocks allow the firstiteration to refresh the model, then skip additional requested sampling.')]:
        guarded='            if '+condition+' {\n'+''.join('    '+line if line.strip()else line for line in body.splitlines(keepends=True))+'            }\n'
        rust=original[:a]+guarded+original[b:]
        e=m.write_candidate(name,p.name,rust,proof,
            description+' Thefirstblock is unchanged; fullDP branch remains whenevera_should_sample isfalse. Skippedresampling also skips frequency/model updates, avoidingdoublecountingprevious LF/DF. Pe andlatercontrolflow maychange aspart ofthis algorithm.',
            'Zdiagnosis found395samplecalls taking317ms of2267ms instrumentedparse. Existingcost tablesalreadycarry acrossblocks. This compares directreuse withonefreshsample afterfirstblock, not arbitraryglobalpass-count reduction. Actualquality isunknown and must be measuredbeforetime. Theoreticalsamplefraction isnotofficialspeedgain.',
            json.loads((p/'manifest.json').read_bytes())['attribution'])
        e.update(anchor='public586',comparison_baseline='selective586',native_decode_reference='selective586');entries.append(e)
    s=json.loads((ROOT/'evidence/round18/span-w-native.json').read_bytes());s.pop('r18_rf_span_equiv');s['entries']=[e for e in s['entries']if e.get('control')]+entries;s['native_encoder_references']=['public586','selective586'];s['screen_orders']=[[e['name']for e in s['entries']],[e['name']for e in reversed(s['entries'])]]
    s['description']='AAnative: sourceinspectionshowsprice models persist acrossblocks, yet395resamplingcalls cost317ms. Compare noadditional sampling vsoneupdate forlaterblocks; firstblock unchanged andoriginalfullDPbranch retained. Frozenexistingselectiveparent, originalencoder28files/decode, cap25job-minutes. Qualityloss determineswhether the potential~14percentparsework budgetdeservesactualtotal timing. No claimedgainorproofinheritance.'
    (ROOT/'evidence/round18/model-aa-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());print(json.dumps(entries))

if __name__=='__main__':main()
