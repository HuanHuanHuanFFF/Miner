"""Reuse proven word-prefix length primitives in the auxiliary match comparator."""
from pathlib import Path
import json,importlib.util
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round21'
def main():
 sp=importlib.util.spec_from_file_location('w',ROOT/'scripts/build-round18-start.py');w=importlib.util.module_from_spec(sp);sp.loader.exec_module(w)
 p=ROOT/'candidates/r20-539-csv-prev16-proof1';r,l=[(p/f).read_text()for f in ('parse.rs','Parse.lean')];entries=[]
 old='let m = pc_common_from(s, c2, p, cap, 0);';assert r.count(old)==1
 for fn,suffix in [('pc_xlen','word8'),('pc_xlen16','word16')]:
  new=f'let m = if cap >= 8 {{let cw=pc_be8(s,c2);let pw=pc_be8(s,p);{fn}(s,c2,p,cw ^ pw)}} else {{pc_common_from(s,c2,p,cap,0)}};'
  source=r.replace(old,new);name='r21-539-secondary-'+suffix
  en=w.write_candidate(name,p.name,source,l,
   'Keep the original endpoint rejection, chain candidates and byte validation; replace generic initial common-prefix loop with existing'+fn+' when8bytes remain. Tail retains original scalar routine.',
   'R20 examined chain utility and distance quality; R21 table narrowing added lookup work. This changes physical match-extension path while retaining intended maximal length and token choices; not a new search budget. Both output/equivalence and fresh proof required.',
   {'parent':p.name,'prior_counts':'evidence/round20/38051458977/secondary-i-native/diagnostics','original_author':'references/round18-public-539/source-receipt.json'})
  en.update(anchor='public539',comparison_baseline='prev16',native_decode_reference='prev16',expected_equivalent_to='prev16');entries.append(en)
 s=json.loads((E/'probe-a-native.json').read_bytes());s['entries']=[e for e in s['entries']if e.get('control')]+entries;s['native_encoder_references']=['public539','prev16'];ns=[e['name']for e in s['entries']];s['screen_orders']=[ns,ns[::-1]];s['description']='R21 F original28file encode/decode for identical-choice word-prefix extension hypothesis; no newchain/routing policy,15mincap. Both exact output and equality remain finite only.'
 (E/'probe-f-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());(E/'preflight-f.json').write_bytes((json.dumps({'gap':'Primary-table narrowing increased computation and had0share. Existing auxiliary candidates remain worthwhile for quality, but generic common-prefix loop adds control flow.','change':'Reuse samealreadyproven first8or16-byte extension primitive inside secondary try; retainendpointfilter, tail and candidates.','minimum':'Actual28fileoriginalencoder token/hash parity plus native decode.','decision':'Parity -> originalpairedtiming; differences -> diagnose exactprefix/tail before promotion. No faster-only gate.','cost_cap_minutes':15,'proof':'Reuseprimitive spec but actual f_try call binding and cap>=8 conditions must pass new extraction.'},indent=2)+'\n').encode());print([e['name']for e in entries])
if __name__=='__main__':main()
