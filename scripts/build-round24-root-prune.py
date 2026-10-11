"""Specialize the no-skip finder path: retain original fallback for smaller skips."""
from pathlib import Path
import importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');fn=importlib.import_module('prepare-round24-extract-repro').fn
def close(t,a):
    assert t[a]=='{';depth=1;b=a+1
    while depth:depth+=(t[b]=='{')-(t[b]=='}');b+=1
    return b
def remove_if(t,needle):
    a=t.index(needle);b=close(t,t.index('{',a));return t[:a]+t[b:]
def main():
    p=ROOT/'candidates/r24-609-once';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text();extras=[]
    for outer,tree in [('Z145','Z162'),('Z186','Z189')]:
        core=fn(r,tree).replace('pub fn '+tree+'(', 'pub fn Aroot'+tree[1:]+'(',1)
        for line in ['    rct: &mut [u32; 65536],\n','    let cr = pre.4;\n','    rct[h % 65536] = (pos + 1) as u32;\n']:
            assert core.count(line)==1;core=core.replace(line,'')
        core=remove_if(core,'    if cr != cur');extras.append(core)
        old=fn(r,outer);fast=old.replace('pub fn '+outer+'(', 'pub fn Aroot'+outer[1:]+'(',1).replace(', skip: usize)',')')
        for line in ['    let mut rct = [0u32; 65536];\n','    let mut cl = 0usize;\n','    let mut cd = 1usize;\n','    let mut nr = rct[nh % 65536] as usize;\n','            nr = rct[nh % 65536] as usize;\n']:
            assert fast.count(line)==1,(outer,line);fast=fast.replace(line,'')
        if outer=='Z145':fast=fast.replace('(nq, nt, nh, n3, if skip >= 258 { nc } else { nr }, nc)','(nq, nt, nh, n3, nc, nc)')
        else:fast=fast.replace('(nq, nt, nh, n3, nr, nc)','(nq, nt, nh, n3, nc, nc)')
        a=fast.index('            if cl >= skip {');b=close(fast,fast.index('{',a));assert fast[b:b+7]==' else {'
        eb=b+6;end=close(fast,eb);body=fast[eb+1:end-1]
        body=body.replace('                let before = mb.len();\n','')
        body=body.replace('let best = '+tree+'(s, &mut head, &mut kid, &mut h3, &mut rct, i, pre, depth, mb);','Aroot'+tree[1:]+'(s, &mut head, &mut kid, &mut h3, i, pre, depth, mb);')
        body=remove_if(body,'                if best > cl')
        body=body.replace('                    nr = i + 1;\n','')
        fast=fast[:a]+body+fast[end:];fast=remove_if(fast,'        if cl > 0')
        assert 'rct' not in fast and ' nr ' not in fast and ' cl ' not in fast and ' cd ' not in fast and 'skip' not in fast
        extras.append(fast)
        wrapper=f'''pub fn {outer}(s:&[u8],mp:&mut Vec<u32>,mb:&mut Vec<u32>,depth:usize,skip:usize) {{
 if skip>=258 {{Aroot{outer[1:]}(s,mp,mb,depth);}}else{{{outer}full(s,mp,mb,depth,skip);}}
}}
'''
        assert r.count(old)==1;r=r.replace(old,old.replace('pub fn '+outer+'(','pub fn '+outer+'full(',1));extras.append(wrapper)
    r+='\n// R24: skip>=258 consumes no continuation or separate recent-head state.\n'+'\n'.join(extras)
    e=w.write_candidate('r24-609-root-prune',p.name,r,l,'For skip>=258, select a dedicated A finder with one root table instead of separate root/recent tables, no unreachable continuation skip branch, and no unused continuation bookkeeping. Keep the original finder unchanged under a renamed fallback for skip<258.','This removes proven-condition dead work, unlike changing hash keys or merely shrinking a used table. Original best match is bounded258 and decremented at each iteration, so entry continuation stays<=257. No modified configuration or search-depth parameter. Native token parity must still validate the implementation.',{'parent':p.name,'profile':'evidence/round24/weighted-stage-priority.json','proof':'DRAFT: new loop states and renamed fallback interfaces require exact extraction/migration/fullgate. The structural argument is not a completed Lean equivalence proof.'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    s=json.loads((E/'groups-n-native.json').read_bytes());s.pop('r24_group_counts');s['entries']=[x for x in s['entries']if x['control']]+[e];s.update(r24_root_counts=True,description='AE actual eligible finder coverage and original28file parity after removing conditionally unused rct/continuation state. Smaller skips keep exact original fallback; no knob changes.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    for name,d in [('root-ae-native',s),('preflight-ae',{'gap':'Need materially less actual matching work. For skip>=258 the carried match at loopentry cannot reach the skip threshold, so recenthead tracks root and carried length/distance do not influence future candidate generation.','change':'Dedicated no-skip finder selected outside large-array allocation; original fallback retained for all smaller skips. Drop recenthead256KiB, duplicate writes/read and dead continuation tracking only on eligible path.','minimum':'Count original finder invocations/bytes and eligiblecoverage; original28file token/encoder/decode parity. Later standard equivalence includes wrap-boundary generatedinputs.','decision':'Any mismatch diagnoses near-head equivalence or fast-loop extraction first. Material coverage with parity earns whole-time measurement; no speed bound from bytes or calls.','cost_cap_runner_minutes':20,'evidence':'evidence/round24/<run>/root-ae-native/diagnostics','proof_status':'DRAFT'})]:
        out=E/(name+'.json');assert not out.exists();out.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['name'])
if __name__=='__main__':main()
