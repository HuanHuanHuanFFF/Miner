"""Controlled secondary-search allocation and compact primary hints at the fast frontier."""
from pathlib import Path
import importlib.util,json,re
ROOT=Path(__file__).resolve().parents[1]
E=ROOT/'evidence/round21'

def main():
    sp=importlib.util.spec_from_file_location('w',ROOT/'scripts/build-round18-start.py');w=importlib.util.module_from_spec(sp);sp.loader.exec_module(w)
    p=ROOT/'candidates/r20-539-csv-prev16-proof1';r,l=[(p/f).read_text()for f in ('parse.rs','Parse.lean')]
    variants=[]
    for suffix,rows in [('head10',[10]),('head16',[16]),('head18',[18])]:
        rust,lean=r,l
        for row in rows:
            pattern=rf'(pub fn p135_row{row}\(input:&\[u8\],out:&mut\[u32\]\)->usize\{{)pc_run1c::<32768>\(input,out,(\d+),0,1000000,4294967295,1,4\)(\}})'
            rust,n=re.subn(pattern,lambda m:m[1]+'pc_run1::<32768>(input,out,'+m[2]+',0,1000000,4294967295)'+m[3],rust);assert n==1
            old=f'rw [slot.p135_row{row}]\n exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)'
            new=f'rw [slot.p135_row{row}]\n exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)'
            assert lean.count(old)==1;lean=lean.replace(old,new)
        variants.append(('r21-539-'+suffix,rust,lean,
          f'Remove only existing auxiliary chain consumer route{rows}; retain16-bit predecessor and all other routes. No new routing classifier or input-length branch.',
          'R20 removed all three generic chain consumers and paid52122B. R21 isolates their end-to-end quality/time contribution with actual narrower storage; a bounded3-way allocation test, not repeating the old all-or-nothing source.'))
    # Primary heads become low16-bit coordinate hints as well; matches stay byte checked.
    start=r.index('pub fn pc_head_set');end=r.index('pub fn q4_be8',start)
    part=r[start:end].replace('[u32; H]','[u16; H]').replace('[0u32; H]','[0u16; H]')
    part=part.replace('head[a] = i as u32;','head[a] = i as u16;')
    old='let c = head[a] as usize;';assert part.count(old)==1
    part=part.replace(old,'let c = i.wrapping_sub(i.wrapping_sub(head[a] as usize) & 65535);\n    let c = if c < s.len() { c } else { 0 };')
    part=part.replace('head[a] as usize == c','head[a] as usize == (c & 65535)')
    compact=r[:start]+part+r[end:];assert compact!=r
    variants.append(('r21-539-headprev16',compact,l,
      'Store primary PC/PI/PIM head hints in16 bits as well as predecessor hints. Reconstruct low16-bit coordinate at lookup and check bounds before byte probe; retain valid distance checks.',
      'R20 only narrowed predecessors; full-width heads remained. This reduces the principal table footprint and initialization, with a real reconstruction cost and possible hint semantic changes. Lean types are unadapted draft; no correctness claim.'))
    entries=[]
    for name,rust,lean,mechanism,diff in variants:
        en=w.write_candidate(name,p.name,rust,lean,mechanism,diff,{'parent':p.name,'original_source':'references/round18-public-539/source-receipt.json','inherited_router':'Existing length/content routes retained without new benchmark identity rule.'})
        en.update(anchor='public539',comparison_baseline='prev16',native_decode_reference='public539');entries.append(en)
    spec=json.loads((ROOT/'evidence/round20/probe-a-native.json').read_bytes())
    spec['entries']=[e for e in spec['entries']if e.get('control')]
    prev=w.control('prev16','candidates/r20-539-csv-prev16-proof1','539');prev.pop('formal_id');prev['anchor']='public539';spec['entries'].append(prev)
    spec['entries']+=entries;spec['r21_mode']='native';spec['r21_role']='discovery';spec.pop('r20_mode',None);spec.pop('r20_role',None)
    spec['snapshot_pages']='evidence/round21/official-start/pareto-pages.json';names=[e['name']for e in spec['entries']];spec['screen_orders']=[names,names[::-1]]
    spec['description']='R21 A: four materially distinct mechanisms, original28file encode/decode and finite native correctness, no timing or proof claim.'
    (E/'probe-a-native.json').write_bytes((json.dumps(spec,indent=2)+'\n').encode())
    plan={'gap':'Current high-speed coordinate must move beyond control variation for>=10% geometry. Existing prev16 too slow near595, all-head-only loses substantial quality.','changes':[{'candidate':v[0],'mechanism':v[3],'difference':v[4]}for v in variants],'minimum':'Original28file encoding plus444 finite native equivalence/decode cases and exact public output.','decision':'Preserve candidates with real quality/time potential; select original paired timing using actual quality. Compact-head success buys proof migration; quality regressions retain explicit tradeoff.','cost_cap_minutes':15,'final_reserve_minutes':35,'evidence':'evidence/round21/<run>/probe-a-native/diagnostics'}
    (E/'preflight-a.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode());print([e['name']for e in entries])
if __name__=='__main__':main()
