"""Coalesce adjacent same-distance extent records only for the unlimited A DP."""
from pathlib import Path
import importlib,json,random
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');fn=importlib.import_module('prepare-round24-extract-repro').fn
HELPER='''#[inline(always)]
pub fn Amergerecord(mb:&mut Vec<u32>,start:usize,m:u32) {
 if mb.len()>start {let last=mb.len()-1;let old=mb[last];
  if old<0x80000000 && m<0x80000000 && (old&32767)==(m&32767) && ((m>>15)&255)>=((old>>15)&255) {mb[last]=m;return;}
 }
 if mb.len()<mb.len().saturating_add(1){mb.push(m);}
}

'''
def main():
    p=ROOT/'candidates/r24-609-once';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text();old=fn(r,'Z189');part=old
    assert r.count('Z189(')==2 and r.count('Z186(')==2
    dp=fn(r,'Z184');assert 'while at <= stop' in dp and 'tail' not in dp and 'width' not in dp
    a=part.index('{')+1;part=part[:a]+'\n    let record_start=mb.len();'+part[a:]
    replacements=0
    import re
    def sub(m):
        nonlocal replacements
        replacements+=1;return 'Amergerecord(mb,record_start,'+m[1]+');'
    part=re.sub(r'if mb\.len\(\) < mb\.len\(\)\.saturating_add\(1\) \{\s*mb\.push\(([^\n]+)\);\s*\}',sub,part)
    assert replacements==3;r=r.replace(old,part);at=r.index('pub fn Z189(');r=r[:at]+HELPER+r[at:]
    e=w.write_candidate('r24-609-record-merge',p.name,r,l,'Within Z189 only, merge adjacent plain extent records when distance is exactly equal and the later extent is at least as long. The consuming Z184/Z187 path enumerates all lengths, so represented length/distance offers remain identical. Never cross a position boundary or an exact-only record.','Do not apply this to bounded-tail Z314: merging there can remove earlier retained lengths. This normalizes cached records once before repeated DP passes, unlike prior per-length packedcost or RFspan pruning. One native test determines actual reductions and fulltoken parity.',{'parent':p.name,'consumer':'Z186 -> Z185 -> Z184 or Z187 (unlimited length enumeration)','prior_different_negative':'docs/rounds/round18.md','proof':'DRAFT: new guarded Vec helper and captured record_start in tree loop require actual extraction/fullgate.'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    s=json.loads((E/'groups-n-native.json').read_bytes());s.pop('r24_group_counts');s['entries']=[x for x in s['entries']if x['control']]+[e];s.update(r24_record_merge_counts=True,description='AN same-distance contiguous extent coalescing only in unlimitedA cache. Record opportunities and original28filetoken/encoder/decode first; bounded-tail engine untouched.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    rng=random.Random(243737);cases=0
    def offers(rs):
        out=[];prev=2
        for length,distance,exact in rs:
            if exact:out.append((length,distance))
            else:out.extend((x,distance)for x in range(prev+1,length+1))
            prev=max(prev,length)
        return out
    for _ in range(20000):
        rs=[];length=2;distance=rng.randrange(1,32769)
        for j in range(rng.randrange(1,16)):
            length=min(258,length+rng.randrange(1,20))
            if rng.randrange(3)==0:distance=rng.randrange(1,32769)
            rs.append((length,distance,rng.randrange(8)==0))
        merged=[]
        for x in rs:
            if merged and not x[2] and not merged[-1][2] and x[1]==merged[-1][1] and x[0]>=merged[-1][0]:merged[-1]=x
            else:merged.append(x)
        assert offers(rs)==offers(merged);cases+=1
    for name,d in [('records-an-native',s),('preflight-an',{'gap':'Tree search populates records consumed across many A DP passes. Repeated same-distance extent boundaries may add traversal work without adding an offer.','change':'Coalesce only adjacent plain same-distance records within one Z189searchposition. Leave all Z162/bounded-tail paths, exact-only records and distances unchanged.','minimum':'20000finite represented-offer sequence checks, actual calls/replacements andbroader same-code opportunity counts, original28file token/encoder/decode equality.','decision':'Meaningful actualreduction with parity earns originaltotal-time. Any mismatch first checks consumer range semantics or record boundaries; operation counts alone never promote speed.','model_cases':cases,'model_scope':'Finite monotone extent-record sequences, not fullRust/Lean equivalence.','cost_cap_runner_minutes':20,'evidence':'evidence/round24/<run>/records-an-native/diagnostics','proof_status':'DRAFT'})]:
        out=E/(name+'.json');assert not out.exists();out.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['name'],cases)
if __name__=='__main__':main()
