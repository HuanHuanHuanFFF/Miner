"""Separate the long-match tree key from existing short/near match hints."""
from pathlib import Path
import importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start')

def segment(text,name):
    a=text.index('pub fn '+name+'(');b=text.find('pub fn ',a+7)
    return a,b if b>=0 else len(text)

def main():
    p=ROOT/'candidates/r24-609-once';r,l=[(p/f).read_text()for f in ('parse.rs','Parse.lean')]
    assert 'pub const Z0: u32 = 16;' in r
    for name in ['Z162','Z189']:
        assert r.count(name+'(')==2
        a,b=segment(r,name);part=r[a:b]
        old='pre: (u64, usize, usize, usize, usize, usize),';assert part.count(old)==1;part=part.replace(old,'pre: (u64, usize, usize, usize, usize, usize, usize),')
        old='let h = pre.2;\n    let c3 = pre.3;\n    let cr = pre.4;\n    let mut cur = pre.5;';assert part.count(old)==1
        part=part.replace(old,'let h = pre.2;\n    let h6 = pre.3;\n    let c3 = pre.4;\n    let cr = pre.5;\n    let mut cur = pre.6;')
        old='head[h % 65536] = (pos + 1) as u32;';assert part.count(old)==1;part=part.replace(old,'head[h6 % 65536] = (pos + 1) as u32;');r=r[:a]+part+r[b:]
    for name in ['Z145','Z186']:
        a,b=segment(r,name);part=r[a:b]
        old='let mut nh = (((nq >> 32) as u32).wrapping_mul(0x9E3779B1) >> (32 - Z0)) as usize;';assert part.count(old)==1;part=part.replace(old,old+'\n    let mut nh6 = Ahash6(nq);')
        old='let mut nc = head[nh % 65536] as usize;';assert part.count(old)==1;part=part.replace(old,'let mut nc = head[nh6 % 65536] as usize;')
        olds=['let pre = (nq, nt, nh, n3, if skip >= 258 { nc } else { nr }, nc);','let pre = (nq, nt, nh, n3, nr, nc);'];found=[v for v in olds if v in part];assert len(found)==1;part=part.replace(found[0],'let pre = (nq, nt, nh, nh6, n3, nr, nc);')
        old='nh = (((nq >> 32) as u32).wrapping_mul(0x9E3779B1) >> (32 - Z0)) as usize;';assert part.count(old)==2
        # Replace the assignment inside the loop, not the variable declaration.
        marker='            '+old;assert part.count(marker)==1;part=part.replace(marker,marker+'\n            nh6 = Ahash6(nq);')
        old='nc = head[nh % 65536] as usize;';assert part.count(old)==1;part=part.replace(old,'nc = head[nh6 % 65536] as usize;')
        old='''                if nh == pre.2 {
                    nr = i + 1;
                    nc = i + 1;
                }''';assert part.count(old)==1
        part=part.replace(old,'''                if nh == pre.2 {nr = i + 1;}
                if nh6 == pre.3 {nc = i + 1;}''');r=r[:a]+part+r[b:]
    helper='''// R24: only the tree uses the six-byte key; near4 and short3 hints remain.
#[inline(always)]
pub fn Ahash6(w:u64)->usize {
 ((w>>16).wrapping_mul(0x9E3779B97F4A7C15)>>48) as usize
}

'''
    at=r.index('pub fn Z145(');attr=r.rfind('#[inline(never)]',0,at);assert r[attr:at].strip()=='#[inline(never)]';r=r[:attr]+helper+r[attr:]
    e=w.write_candidate('r24-609-longkey6',p.name,r,l,
        'Keep the existing3-byte hint table and nearest4-byte hint, but index both A-family long-match trees by a6-byte prefix in the same65536-head capacity. Prefetch/tree-update indices are separated; short hints are not discarded because the tree head is now a different index.',
        'A matching and DP together are substantial remaining work. Unlike table resizing or depth sweeps, this changes candidate organization and may reduce both traversal and recorded alternatives. Losing older4/5-byte choices or increasing hint cost is an explicit risk, tested with actual encoded output first.',
        {'parent':p.name,'source':'references/round24-public-609/source-receipt.json','profile':'evidence/round24/38083109099/profile-i-native/diagnostics/r18-functions/functions.json','limits':'6-byte key is one controlled mechanism, not an input-identity router. Tuple/proof migration remainsDRAFT.'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once')
    s=json.loads((E/'seedtail-d-native.json').read_bytes());s['entries']=[x for x in s['entries']if x['control']]+[e];s['description']='R24 R separate long6 tree and near4/short3 hints on actual609base. Original28-file encoder/decode first; no speed inferred from fewer nodes and no proof inheritance.'
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]];(E/'longkey-r-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
    plan={'gap':'Several small CPU filters failed or produced weak gains; goal10/15requires more real margin. A matching plus repeated DP are a larger remaining opportunity.',
        'change':'One long6-key tree organization while preserving3/4byte near hints, table size, search budgets and all routing. It changes real match coverage and downstream record workload.',
        'minimum':'Full28-file original encode/decode versus exactonce609, with per-file byte effects. Short-match loss is allowed in exploration but must justify the needed speed tradeoff.',
        'decision':'Replay reachable target regions at actual size before expensive timing/proof. If output quality collapse makes the needed speed implausible, retain negative evidence and stop this precise organization. Useful exchange earns original total-time screen.',
        'cost_cap_runner_minutes':15,'evidence':'evidence/round24/<run>/longkey-r-native/diagnostics','proof':'Two7-field prefetch tuples and hash helper require actual extraction and completeproofmigration only after useful evidence.'};(E/'preflight-r.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode());print(e['name'])
if __name__=='__main__':main()
