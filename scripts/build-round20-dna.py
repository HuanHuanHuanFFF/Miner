"""Transfer DNA alphabet representation into539's distinct N matcher."""
from pathlib import Path
import importlib.util,json
ROOT=Path(__file__).resolve().parents[1]

def main():
    sp=importlib.util.spec_from_file_location('w',ROOT/'scripts/build-round18-start.py');w=importlib.util.module_from_spec(sp);sp.loader.exec_module(w)
    p=ROOT/'candidates/r18-539-csv-lazy-content';r,l=[(p/f).read_text()for f in ('parse.rs','Parse.lean')]
    old='pub fn n_hash<const H:usize,const K:usize>(input:&[u8],p:usize)->usize {\n let x=o_a_ld8(input,p);'
    assert r.count(old)==1
    # The six DNA alphabet symbols have distinct low-three-bit values. Bytes
    # outside that domain remain hints, never unchecked emitted matches.
    digits=[0,0,5,1,3,0,4,2]
    fragment='\n if K==7 && H>8 {\n'
    for i in range(6):fragment+=f'  let d{i}=R20_DNA_DIGIT[((x >> {8*i}) & 7) as usize] as usize;\n'
    expr='d0'
    for i in range(1,6):expr=f'({expr}).wrapping_mul(6).wrapping_add(d{i})'
    fragment+='  return ('+expr+') % H;\n }'
    r=r.replace(old,old+fragment)
    a='n_run::<65536,6,0,0,0,16,0,8,1>(input,out)';assert r.count(a)==1;r=r.replace(a,a.replace('65536,6,','65536,7,'))
    r+='\n// Alphabet-specific hash hints; original n_eval and checked emitter retain validity.\npub const R20_DNA_DIGIT:[u8;8]='+str(digits)+';\n'
    e=w.write_candidate('r20-539-csv-dna6',p.name,r,l,
      'Only the content-routed DNA N matcher uses a collision-free six-symbol radix6 hint for A,C,G,T,N,newline, obtained by low3-bit digit mapping; retains65536heads, search, insertion, emitter and all other routes.',
      'R18 radix6 was evaluated on a different PC matcher. Here original539 N matcher has distinct insertion and matching choices and faster formal parent. This is one representation transfer; non-DNA prefix aliasing and proof branch are explicitly unverified until native check/full gate.',
      {'parent':'candidates/r18-539-csv-lazy-content/manifest.json','representation_prior':'evidence/round18/dna-al-key-preflight.json','source':'references/round18-public-539/source-receipt.json'})
    e.update(anchor='public539',comparison_baseline='csv18',native_decode_reference='public539')
    s=json.loads((ROOT/'evidence/round20/probe-a-native.json').read_bytes());s['entries']=[x for x in s['entries']if x.get('control')]+[e];s['description']='C one new N-matcher alphabet representation transfer on539CSV. Full28 original encoder/decode plus branch boundedness preflight;15minute job cap. Faster/slower allowed if actual joint geometry improves; no inherited gate claim.'
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    (ROOT/'evidence/round20/probe-c-native.json').write_text(json.dumps(s,indent=2)+'\n')
    check={'alphabet':list(b'ACGTN\n'),'digits':[digits[b&7]for b in b'ACGTN\n'],'unique_symbols':6,'keys':6**6,'head_capacity':65536,'non_alphabet':'May alias; original checked matcher owns correctness','gap':'Broaden quality margin below595 instead of relying only on sub-noise speed placement. Prior539CSV provides~0.013pp projected margin only.','minimum_operation':'One real original-encoder28file byte/decode run before paired timing','cost_cap_minutes':15,'proof_risk':'One n_hash branch and constant table; existing total bounds lemma must be rechecked by original gate.'}
    assert len(set(check['digits']))==6
    (ROOT/'evidence/round20/preflight-c.json').write_text(json.dumps(check,indent=2)+'\n')
    print(e['name'])
if __name__=='__main__':main()
