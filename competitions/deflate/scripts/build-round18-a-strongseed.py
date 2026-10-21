"""Byte-only isolation of shared-cache quality from weak initial-plan quality."""
from pathlib import Path
import importlib.util,json

ROOT=Path(__file__).resolve().parents[1]

def main():
    sp=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    p=ROOT/'candidates/r18-586-a-shared-rf';rust=(p/'parse.rs').read_text();proof=(p/'Parse.lean').read_text()
    old='''    let mut choice = zeros(n);
    let mut cost = zeros(n+1);
    let mut lit = [0u32;256];
    let mut lc = [0u32;512];
    let mut dc = [0u32;32];
    a_first_model(input, &mut lit, &mut lc, &mut dc);
    a_dp_pass(input, &mp, &mb, 0, n, &lit, &lc, &dc, &mut cost, &mut choice);
    let mut seed = zeros(n);
    let nseed = emit_pos(input, &choice, &mut seed);'''
    new='''    // Quality-isolation probe: this intentionally repeats A search in plan_cfg.
    // If bytes justify it, a later implementation must share that search.
    let choice = plan_cfg(input, ak);
    let mut seed = zeros(n);
    let nseed = emit_pos(input, &choice, &mut seed);'''
    assert rust.count(old)==1;rust=rust.replace(old,new)
    e=m.write_candidate('r18-586-a-strongseed-probe',p.name,rust,proof,
      'Retain the original full A seed and replace only the RF candidate cache by converted A matches. This byte-only isolation intentionally executes A search twice; it is not a performance candidate.',
      'AJ weak-seed/cache composition lost1949B on multibyte while unrefined originalA loses633B versus selectiveRF. The probe separates weak initial modeling from candidate-cache loss. A favorable quality result would justify a later implementation that exposes the original A cache without duplicate search; an unfavorable result stops the exact composition.',
      {'parent':'candidates/r18-586-a-shared-rf/manifest.json','negative_evidence':'evidence/round18/shared-aj-decision.json','ownership':'Original public586 A/RF authors retained; derived byte-only mechanism isolation.'})
    e.update(anchor='public586',comparison_baseline='selective586',native_decode_reference='selective586')
    mp=ROOT/e['path']/'manifest.json';mf=json.loads(mp.read_bytes());mf['artifact_role']='BYTE_FEASIBILITY_PROBE_DUPLICATE_SEARCH_NOT_FOR_TIMING_OR_SUBMISSION';mp.write_bytes((json.dumps(mf,indent=2)+'\n').encode())
    s=json.loads((ROOT/'evidence/round18/shared-aj-native.json').read_bytes());s['entries']=[x for x in s['entries']if x.get('control')]+[e];s['screen_orders']=[[x['name']for x in s['entries']],[x['name']for x in reversed(s['entries'])]]
    s['description']='AM single byte-only isolation: use original full A seed with converted A cache, on already A+RF routes. The duplicated A search is deliberate diagnostic overhead and makes this unsuitable for performance promotion. Original28file encoder/decode, cap20job-minutes. If bytes approach or beat selective, implement shared-cache lifetime and only then measure total time; otherwise stop this exact route. Proof migration remains unknown.'
    (ROOT/'evidence/round18/strongseed-am-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());print(json.dumps(e))

if __name__=='__main__':main()
