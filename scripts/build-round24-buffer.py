"""Retain a useful later match when the four-slot SF buffer contains a dominated slot."""
from pathlib import Path
import importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start')
HELPER='''#[inline(always)]
pub fn SFroom(best:&[u32;4],codes:&[usize;4],t:u32,ct:&[u32;1024])->usize {
 let nc=ct[Z353(SFdist(t)).wrapping_add(512)%1024];let nl=SFlen(t);let mut i=0usize;
 while i<4 {
  let c=ct[codes[i%4].wrapping_add(512)%1024];let l=SFlen(best[i%4]);
  if nc<=c && nl>=l && (nc<c || nl>l) {return i;}
  let mut j=0usize;
  while j<4 {
   let d=ct[codes[j%4].wrapping_add(512)%1024];let m=SFlen(best[j%4]);
   if j!=i && d<=c && m>=l && (d<c || m>l || j<i) {return i;}
   j+=1;
  }i+=1;
 }4
}

'''
def main():
    p=ROOT/'candidates/r24-609-once';r,l=[(p/f).read_text()for f in ('parse.rs','Parse.lean')]
    needle='pub fn SFfastadd(best:&mut[u32;4],codes:&mut[usize;4],count:usize,t:u32)->usize {';assert r.count(needle)==1
    at=r.index(needle);attr=r.rfind('#[inline(always)]',0,at)
    assert r[attr:at].strip()=='#[inline(always)]'
    r=r[:attr]+HELPER+r[attr:]
    r=r.replace(needle,needle.replace('t:u32)','t:u32,ct:&[u32;1024])'))
    old='if count<4{best[count%4]=t;codes[count%4]=dc;count+1}else{count}'
    assert r.count(old)==1;r=r.replace(old,'if count<4{best[count%4]=t;codes[count%4]=dc;count+1}else{let slot=SFroom(best,codes,t,ct);if slot<4{best[slot]=t;codes[slot]=dc;}count}')
    old='SFfastadd(&mut best,&mut codes,count,ot)';assert r.count(old)==1;r=r.replace(old,old[:-1]+',ct)')
    old='SFfastadd(&mut best,&mut codes,count,SFmt(d,l))';assert r.count(old)==1;r=r.replace(old,old[:-1]+',ct)')
    e=w.write_candidate('r24-609-buffer-frontier',p.name,r,l,
        'Only on four distinct distance-code slots already being full, replace a slot that is dominated under the current SF length/distance-price model by the incoming match or another retained match. Preserve search depth and normal non-full path; permit useful later choices without increasing buffer capacity.',
        'Earlier seed-tail pruning added checks on every query and slowed total time. This tests lost quality at a bounded buffer overflow, not that CPU filter or another search-depth sweep. Actual overflow opportunity and full encoded effect are measured together.',
        {'parent':p.name,'source':'references/round24-public-609/source-receipt.json','related_negative':'evidence/round24/analysis-bd.json','proof':'New pure slot selector and modified fastadd signature not yet migrated; this Lean file is a draft only.'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once')
    s=json.loads((E/'seedtail-d-native.json').read_bytes());s['entries']=[x for x in s['entries']if x['control']]+[e]
    s.update(r24_buffer_counts=True,description='R24 L actual four-slot capacity quality test. Original observer counts discarded distinct-code candidates and whether a dominated retained slot exists; new candidate encoding is measured separately, not inferred from counts.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    (E/'buffer-l-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
    plan={'gap':'Need actual additional quality or substantially lower work. SFheavy searches up to8/16 entries but stores only4 distance codes, and may discard a useful late candidate before its existing final dominance filter.',
        'change':'Reuse a currently dominated slot only on overflow; no extra search and no larger buffers.',
        'minimum':'Untimed old-algorithm overflow counts with token/decode equality, plus actual28-file original encoding for the modified candidate.',
        'decision':'No useful overflows or no useful encoded change means pause without a timing/proof campaign. If real quality moves the opportunity, measure original total time and migrate the exact helper proof.',
        'cost_cap_runner_minutes':15,'evidence':'evidence/round24/<run>/buffer-l-native/diagnostics','proof':'DRAFT, no inherited gate. Dominance refers only to current fixed model, not a guarantee of final encoded bytes.'}
    (E/'preflight-l.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode());print(e['name'])
if __name__=='__main__':main()
