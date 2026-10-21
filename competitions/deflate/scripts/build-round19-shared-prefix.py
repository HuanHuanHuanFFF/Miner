"""Proof-subset Rust starting point after the diagnostic preserved exact public output."""
from pathlib import Path
import importlib.util
import json

ROOT = Path(__file__).resolve().parents[1]


def main():
    sp = importlib.util.spec_from_file_location('writer', ROOT / 'scripts/build-round18-start.py')
    w = importlib.util.module_from_spec(sp)
    sp.loader.exec_module(w)
    parent = ROOT / 'candidates/r19-sf-nooverlap'
    rust, lean = [(parent / f).read_text() for f in ('parse.rs', 'Parse.lean')]
    signature = '    spass: usize,\n) {\n    let n = input.len();'
    assert rust.count(signature) == 1
    rust = rust.replace(signature, '    spass: usize,\n) -> (Vec<u32>, Vec<u32>) {\n    let n = input.len();')
    end = rust.index('// ───────────────────────────── engine C: DNA and binary')
    head = rust[:end].rstrip()
    assert head.endswith('}')
    rust = head[:-1] + '    (mp, mb)\n}\n\n' + rust[end:]
    a = rust.index('pub fn SFsmallmatches(')
    b = rust.index('pub fn SFpriced(', a)
    small = rust[a:b].replace('pub fn SFsmallmatches(', 'pub fn r19_smallmatches(', 1)
    needle = 'starts:&mut Vec<u32>) {'
    assert small.count(needle) == 1
    small = small.replace(needle, 'starts:&mut Vec<u32>,amp:&[u32],amb:&[u32]) {')
    small = small.replace('let known=SFknown(ot,d,cap);', 'let known=r19_known(amp,amb,p,d,cap,SFknown(ot,d,cap));')
    a = rust.index('pub fn SFshape(')
    b = rust.index('pub fn SFdepth(', a)
    shape = rust[a:b].replace('pub fn SFshape(', 'pub fn r19_shape(', 1)
    shape = shape.replace('nt:usize)->Vec<u32>', 'nt:usize,amp:&[u32],amb:&[u32])->Vec<u32>')
    shape = shape.replace('SFsmallmatches(input,&prev,&orig,&ct,a,e,&mut items,&mut starts);',
                          'r19_smallmatches(input,&prev,&orig,&ct,a,e,&mut items,&mut starts,amp,amb);')
    helper = '''
pub fn r19_known(amp:&[u32],amb:&[u32],p:usize,d:usize,cap:usize,known:usize)->usize {
 let mut k=known;
 if p.wrapping_add(1)<amp.len() {
  let mut j=q9_get(amp,p) as usize;let end=q9_get(amp,p.wrapping_add(1)) as usize;
  while j<end&&j<amb.len() {
   let m=q9_get(amb,j);
   if (m&32767).wrapping_add(1) as usize==d {
    let l=(((m>>15)&255).wrapping_add(3)) as usize;
    k=q9_umax(k,q9_umin(l,cap));
   }j+=1;
  }
 }k
}

pub fn r19_base_cached(input:&[u8],out:&mut[u32])->(usize,Vec<u32>,Vec<u32>) {
 let cls=route_class(input);let e=CLASS_TAB[cls%32];let c=CFG[e[1]%16];
 if input.len()<16777216&&e[0]<2&&c[0]==0&&REFINE[cls%32]==0 {
  let mut plan=zeros(input.len());
  let cache=a_engine(input,&mut plan,c[1],c[2],c[3],c[4],c[5],c[6]);
  let nt=emit_pos(input,&plan,out);
  (nt,cache.0,cache.1)
 }else{
  let nt=r18_base(input,out);(nt,Vec::new(),Vec::new())
 }
}

'''
    a = rust.index('pub fn parse(input: &[u8], out: &mut [u32]) -> usize {')
    parse = rust[a:].replace('let nt = r18_base(input, out);', 'let (nt, amp, amb) = r19_base_cached(input, out);')
    parse = parse.replace('let plan = SFshape(input, out, nt);', 'let plan = r19_shape(input, out, nt, &amp, &amb);')
    rust = rust[:a] + helper + small + shape + parse
    assert 'Mutex' not in rust and 'AtomicU64' not in rust and '.clone()' not in rust
    entry = w.write_candidate('r19-sf-shared-prefix-draft', parent.name, rust, lean,
        'Return the already-created A match vectors, keep them alive through SF, and use same-distance cached lengths to skip known match prefixes. Preserve original SF search/fallback; no global state, Mutex or cloned cache.',
        'Q diagnostic preserved exact public output with 7069779 longer prefixes; this is the actual explicit-lifetime implementation. ABI and helper proofs still need adaptation; no full performance or gate promotion.',
        {'parent': 'candidates/r19-sf-nooverlap/manifest.json',
         'quality_diagnostic': 'evidence/round19/38045695358/cache-q-native/diagnostics/r19-cache-prefix/quality.json'})
    manifest_path = ROOT / entry['path'] / 'manifest.json'
    manifest = json.loads(manifest_path.read_bytes())
    manifest['proof_status'] = 'DRAFT_REQUIRES_A_ENGINE_RETURN_AND_NEW_HELPER_PROOFS'
    manifest['required_proof_work'] = ['a_engine returns cache vectors; recheck existing totality proof',
        'r19_known/r19_base_cached/r19_smallmatches/r19_shape helper totality',
        'outer original LZ77.Obligation via checked emitters; fresh original full gate']
    manifest_path.write_bytes((json.dumps(manifest, indent=2) + '\n').encode())
    entry.update(anchor='base603', comparison_baseline='base603', native_decode_reference='base603')
    spec = json.loads((ROOT / 'evidence/round19/probe-i-native.json').read_bytes())
    spec['entries'] = [e for e in spec['entries'] if e['control']] + [entry]
    names = [e['name'] for e in spec['entries']]
    spec['screen_orders'] = [names, list(reversed(names))]
    spec['description'] = 'R next-round starting point only: actual Rust explicit cache lifetime after Q exact-quality diagnostic. No globals/clones; original encoder/decode28files,10mincap. Source/Lean hashbound but Lean knowingly unadapted. Keep current frozenfinalpair untouched; no late full gate or originaltiming scheduled.'
    (ROOT / 'evidence/round19/probe-r-native.json').write_bytes((json.dumps(spec, indent=2) + '\n').encode())
    print(entry['hashes'])


if __name__ == '__main__':
    main()
