"""Byte-only probe of A-cache refinement on previously unrefined A routes."""
from pathlib import Path
import importlib.util,json,re

ROOT=Path(__file__).resolve().parents[1]

def main():
    sp=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    p=ROOT/'candidates/r18-586-selective-rf';rust=(p/'parse.rs').read_text();proof=(p/'Parse.lean').read_text();probe=(ROOT/'candidates/r18-586-a-strongseed-probe/parse.rs').read_text();helper=probe[probe.index('pub fn r18_a_shared_plan('):].rstrip()+'\n';assert helper.endswith('}\n')
    donor=(ROOT/'references/round18-public-586/parse.rs').read_text();match=re.search(r'pub const REFINE: \[usize; 32\] = (\[[^\n]+\]);',donor);assert match;mapping=json.loads(match.group(1));assert len(mapping)==32 and max(mapping)<64
    old='    let e = CLASS_TAB[cls % 32];';assert rust.count(old)==1
    new=old+'''
    if e[0] == 0 && CFG[e[1] % 16][0] == 0 && REFINE[cls % 32] == 0
        && R18_CACHE_REFINE[cls % 32] != 0 {
        let plan = r18_a_shared_plan(input,e[1],R18_CACHE_REFINE[cls % 32]);
        return emit(input,&plan,out);
    }'''
    rust=rust.replace(old,new)+'\npub const R18_CACHE_REFINE:[usize;32]='+json.dumps(mapping)+';\n'+helper
    e=m.write_candidate('r18-586-cache-extra-probe',p.name,rust,proof,
      'Retain selectiveRF on already refined routes. On other A routes that public586 originally refined, test exact refinement from the original strong A seed and converted A candidate cache, using each released RF configuration. Deliberately duplicate A search for this byte-only isolation.',
      'AM strong-seed cache lost290B on the already refined multibyte route; this excludes that route and tests added quality where selectiveRF currently skips refinement. It does not extrapolate AM as a whole-engine success. If byte gain supports current5/15geometry, a later shared-lifetime implementation must remove duplicated matching before any time claim.',
      {'parent':'candidates/r18-586-selective-rf/manifest.json','cache_prototype':'candidates/r18-586-a-strongseed-probe/manifest.json','original_refine_table':'references/round18-public-586/source-receipt.json','ownership':'Original A/RF authors retained; this is a derived quality-isolation probe.'})
    e.update(anchor='public586',comparison_baseline='selective586',native_decode_reference='selective586');mp=ROOT/e['path']/'manifest.json';mf=json.loads(mp.read_bytes());mf['artifact_role']='BYTE_FEASIBILITY_PROBE_DUPLICATE_SEARCH_NOT_FOR_TIMING_OR_SUBMISSION';mp.write_bytes((json.dumps(mf,indent=2)+'\n').encode())
    s=json.loads((ROOT/'evidence/round18/strongseed-am-native.json').read_bytes());s['entries']=[x for x in s['entries']if x.get('control')]+[e];s['screen_orders']=[[x['name']for x in s['entries']],[x['name']for x in reversed(s['entries'])]];s['description']='AY one bounded quality-only route extension using the original perclassRFbudgets. Preserve existingRFpaths; refine only unrefinedApaths withstrongAseed andconvertedAcache. Search is duplicated deliberately, so this is not a timing/submission candidate. Original28file encoder/decode, cap20job-minutes. Replay fixedfrontier quality/time requirements before any shared-cache implementation. Stop if qualitydoesnotjustifythe newwork; noiteration/depth grid.';(ROOT/'evidence/round18/cache-extra-ay-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());print(json.dumps(e))

if __name__=='__main__':main()
