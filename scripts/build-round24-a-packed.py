"""Hoist A price packing while preserving every pre-existing inline boundary."""
from pathlib import Path
import importlib,json,random,re
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');fn=importlib.import_module('prepare-round24-extract-repro').fn
HELPER='''pub fn APprices(src:&[u32;512])->[u32;512] {
 let mut dst=[0u32;512];let mut j=0usize;
 while j<512 {dst[j]=src[j]<<9;j+=1;}dst
}
'''
def main():
    p=ROOT/'candidates/r24-609-once';base=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text();r=base;counts={}
    for n in ['Z184','Z307']:
        old=fn(r,n);part=old;assert part.count('let nxt = cost[i + 1];')==1
        part=part.replace('let nxt = cost[i + 1];','let nxt = cost[i + 1] >> 9;')
        part=part.replace('let cl = cost.len();','let lc=APprices(lc);\n    let cl = cost.len();')
        part,k=re.subn(r'(let base = dc\[[^\n]+\.wrapping_add\(bias\));',r'\1 << 9;',part);assert k==2;counts[n]=k
        part,k=re.subn(r'\.wrapping_add\(base\) << 9\)',r'.wrapping_add(base))',part);assert k==(3 if n=='Z184'else 1)
        needle='cost[i] = ((best >> 9).wrapping_add(nxt)).wrapping_sub(1048576);';assert part.count(needle)==1;part=part.replace(needle,'cost[i] = ((best >> 9).wrapping_add(nxt)).wrapping_sub(1048576) << 9;')
        if n=='Z307':assert part.count('Z314(cost, lc,')==2;part=part.replace('Z314(cost, lc,','Z314(cost, &lc,')
        r=r.replace(old,part)
    old=fn(r,'Z314');part=old;assert part.count('.wrapping_add(base)<<9)')==1;part=part.replace('.wrapping_add(base)<<9)','.wrapping_add(base))');r=r.replace(old,part)
    a=r.index('pub fn Z184(');assert not re.search(r'#\[inline[^\]]*\]\s*$',r[:a]);r=r[:a]+HELPER+'\n'+r[a:]
    attrs=lambda t:{m[2]:m[1]for m in re.finditer(r'(#\[inline\([^\]]+\)\])\s*pub fn (\w+)\(',t)}
    assert attrs(r)==attrs(base)
    e=w.write_candidate('r24-609-a-packed',p.name,r,l,'Pack the internal cost vector, per-pass length costs and per-record distance base before A full and bounded-tail reductions; preserve original 9bit tie ordering and all function inline attributes.','R21 had a small signal but accidentally moved inline(never) from the DP to its helper. This source preserves the actual609 boundaries, extends the representation to both A kernels, and requires real-Rust differential tests including wrapped costs before timing.',{'parent':p.name,'prior':'candidates/r21-a-packed-cost/manifest.json','inline_boundary_identity':True,'changed_functions':['Z184','Z307','Z314'],'proof':'DRAFT; shifted arithmetic identity is not a universal kernel proof or fullgate.'});e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    s=json.loads((E/'groups-n-native.json').read_bytes());s.pop('r24_group_counts');s['entries']=[x for x in s['entries']if x['control']]+[e];s.update(r24_a_packed_check=True,description='AQ preserve actualinline boundaries while hoisting packedA costs across two kernels. ActualRust differential windows/ties/U32wrap and whole28fileencoder/token/decode equality before any time/gate claim.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    rng=random.Random(2441)
    for _ in range(100000):
        x,y,z=[rng.getrandbits(32)for _ in range(3)];v=rng.randrange(512);assert (((x+y+z)<<9)&0xffffffff)|v==(((x<<9)+(y<<9)+(z<<9))&0xffffffff)|v
    for name,d in [('packed-aq-native',s),('preflight-aq',{'gap':'A DP remains material and genericblockRMQ regressed. Prior packedcost signal was confounded by inline placement; exact609 kernels have different boundaries.','change':'Only internalmodularrepresentation, price packing and shifts outside perlength comparisons. Preserve each existing inline attribute exactly; no newcache/search/route knob.','minimum':'100000scalarwrap identities plus2400actualRustwindows for each full/tailkernel, bothchoice andlow23bitcost identities, then28publictokens/output.','decision':'Any realkernel counterexample stops timing and records the input. Exactparity earns one originalpairedscreen. R21gain is background, not a prediction or proof.','cost_cap_runner_minutes':20,'evidence':'evidence/round24/<run>/packed-aq-native/diagnostics','proof_status':'DRAFT'})]:
        out=E/(name+'.json');assert not out.exists();out.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['hashes'])
if __name__=='__main__':main()
