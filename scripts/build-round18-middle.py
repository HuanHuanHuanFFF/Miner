"""Move verified-useful text lookahead into the complementary553engine library."""
from pathlib import Path
import importlib.util,json

ROOT=Path(__file__).resolve().parents[1]

def main():
    sp=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    parent=ROOT/'references/round14-public-553';rust=(parent/'parse.rs').read_text();lean=(parent/'Parse.lean').read_text()
    replacements=[]
    for row,skip in [(10,4),(16,5),(18,8)]:
        old=f'pub fn p135_row{row}(input:&[u8],out:&mut[u32])->usize{{pc_run1c::<32768>(input,out,{skip},0,1000000,4294967295,2,4)}}'
        new=f'pub fn p135_row{row}(input:&[u8],out:&mut[u32])->usize{{pc_run1c::<32768>(input,out,4,16,1000000,4294967295,1,4)}}'
        assert rust.count(old)==1;rust=rust.replace(old,new);replacements.append({'row':row,'before':old,'after':new})
    e=m.write_candidate('r18-553-lookahead','public553',rust,lean,
        'Within553existing PC text wrappers10/16/18, replace deeper immediate predecessor exploration with shallower cost-ranked one-byte lookahead up to16. Retain the original553classifier, nonPCengine library, allocation representation and64-bit hash.',
        'R16 demonstrated realtext byte savings but whole514variants remained dominated. Newfree-switching analysis identifies complementary553paths onprose/weights andR16lookahead ontext. This is an actual whole-program combination experiment; the oracle point has no implementation/measurement standing. No new filename/hash/length predicates are introduced.',
        {'source':'Original public553,542lineage; R16textlookahead mechanism reused','reference':'references/round14-public-553/source-receipt.json','other_evidence':'evidence/round18/oracle-opportunity.json'})
    e.update(anchor='public553',comparison_baseline='public553',native_decode_reference='public553')
    spec=json.loads((ROOT/'evidence/round18/dna-cost-j-native.json').read_bytes());spec['entries']=[x for x in spec['entries']if x['name']in('probe3','r3-432-fast3','public432','public514')]
    parent=m.control('public553','references/round14-public-553','553');ref=m.control('lazy16','candidates/r16-514-lazy16','514');ref.pop('formal_id');ref['anchor']='public514'
    spec['entries'] += [parent,ref,e];spec['native_encoder_references']=['public553','lazy16'];spec['snapshot_pages']='evidence/round18/official-hour1/pareto-pages.json'
    spec['screen_orders']=[[x['name']for x in spec['entries']],[x['name']for x in reversed(spec['entries'])]]
    spec['description']='Mnative: implement the identifiedengine complement inside553, avoiding an unimplementablefreeper-fileoracle. Threeexistingtextwrappers trade immediate depth for validatedcost-ranked lookahead; allotherpaths retained. First actual28fileencodedbytes/decode versus553 andlazy16; cap20job-minutes. Bytequality improvement selects pairedtotal timing; failures guidepathattribution. Fullproof notinherited.'
    (ROOT/'evidence/round18/middle-m-native.json').write_bytes((json.dumps(spec,indent=2)+'\n').encode());(ROOT/'evidence/round18/middle-m-changes.json').write_bytes((json.dumps(replacements,indent=2)+'\n').encode());print(json.dumps(e))

if __name__=='__main__':main()
