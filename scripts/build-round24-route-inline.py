"""Separate small route wrapper inlining from the public606/609 table changes."""
from pathlib import Path
import importlib,json,re
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');fn=importlib.import_module('prepare-round24-extract-repro').fn
def main():
    p=ROOT/'candidates/r24-609-once';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text();old=(ROOT/'references/round24-public-606/parse.rs').read_text()
    always=lambda t:{m[1]for m in re.finditer(r'#\[inline\(always\)\]\s*pub fn ([A-Za-z_0-9]+)\(',t)}
    names=sorted(always(old)-always(r)-{'Z252','Z303','Z416'});assert len(names)==17
    bodies={n:fn(r,n)for n in names};assert all(len(v)<1000 for v in bodies.values())
    for n in names:
        needle='pub fn '+n+'(';assert r.count(needle)==1;r=r.replace(needle,'#[inline(always)]\n'+needle)
    assert all(fn(r,n)==v for n,v in bodies.items())
    e=w.write_candidate('r24-609-route-inline',p.name,r,l,'Expose the existing constant route/knob selections through17small wrapper functions by inline(always), keeping all function bodies, tables and explicit never-inline planner boundaries unchanged.','Public606 had these attributes but also different algorithm tables; this isolates the wrapper effect on exact609once. Earlier H16 attribute edits sometimes produced identical machine code. Original-template compiler identity and actual bytes precede timing.',{'parent':p.name,'attribute_reference':'references/round24-public-606/source-receipt.json','changed_wrappers':names,'explicit_exclusions':['Z252','Z303','Z416'],'proof':'Same Lean text is DRAFT for the new Rust hash until fresh complete gate.'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    s=json.loads((E/'groups-n-native.json').read_bytes());s.pop('r24_group_counts');s['entries']=[x for x in s['entries']if x['control']]+[e]
    shadow=dict(next(x for x in s['entries']if x['name']=='once'));shadow['name']='once-shadow';s['entries'].append(shadow)
    s.update(r24_compile_identity=['once','once-shadow',e['name']],description='AC isolated17small routing wrappers. Native28fileparity and exactoriginaltemplate shared-library build identity with same-source shadow; no compiler-output-to-speed inference.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    for name,d in [('inline-ac-native',s),('preflight-ac',{'gap':'Current actual highquality speed improvements remain too small.606/609 differ in routing-wrapper attributes as well as tables, leaving specialization effects unresolved.','change':'Only17small inline attributes; exclude the two explicitnever planners and non-routerZ416. All Rust function bodies and constants unchanged.','minimum':'Original28fileencoder parity; build three originalbenchmark-template cdylibs offline onrunner with exacttoolchain, compare library/text/rodata hashes including identical-source shadow.','decision':'Identical relevant code means do not allocate another timing screen. Different code alone does not mean faster; only then consider original pairedtotal-time test.','cost_cap_runner_minutes':20,'evidence':'evidence/round24/<run>/inline-ac-native/diagnostics','proof_status':'DRAFT'})]:
        dest=E/(name+'.json');assert not dest.exists();dest.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['name'],names)
if __name__=='__main__':main()
