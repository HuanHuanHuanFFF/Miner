"""One sniff representation trial; Python finite model, no local native tools."""
from __future__ import annotations
import argparse, hashlib, json, re
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'candidates/r3-432-fast3';NAME='r11-fast-classpack'
PINS={'parse.rs':'bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef','Parse.lean':'e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04'}
DNA={65,67,71,84,97,99,103,116,78,110,10}
SYMS={35,36,37,38,40,41,42,43,47,59,60,61,62,64,91,92,93,94,95,96,123,124,125,126}

def sha(b):return hashlib.sha256(b).hexdigest()
def function(s,name):
    st=s.index('pub fn '+name+'(');i=s.index('{',st)+1;d=1
    while d:d+=(s[i]=='{')-(s[i]=='}');i+=1
    return s[st:i]
def old_features(h):
    return [sum(h[x] for x in DNA),sum(h[x] for x in [9,10,13])+sum(h[x] for x in range(32,256) if x!=127),sum(h[128:]),h[32]+sum(h[65:91])+sum(h[97:123]),sum(h[x] for x in SYMS),sum(h[48:58]),h[0]]
def flags(x):return [int(x in DNA),int(x in [9,10,13] or x>=32 and x!=127),int(x>=128),int(x==32 or 65<=x<=90 or 97<=x<=122),int(x in SYMS),int(48<=x<=57),int(x==0)]
def entry(x):
    f=flags(x);return sum(f[i]<<(13*i) for i in range(4)),sum(f[i+4]<<(13*i) for i in range(3))
def unpack(a,b):return [(a>>(13*i))&8191 for i in range(4)]+[(b>>(13*i))&8191 for i in range(3)]
def cls(f,t):
    dna,text,high,words,syms,digits,zero=f
    if t>0 and dna>=t-t//10:return 0
    if text>=t-t//100 and zero==0:
        if words>=t-t//7 and syms<=t//64:return 5
        if digits>=t//6:return 6
        return 1
    if high>=t//3:return 4 if zero>=t//20 else 2
    return 3
def model():
    tests=0
    for x in range(256):
        h=[0]*256;h[x]=1;assert flags(x)==old_features(h);tests+=1
        a,b=entry(x)
        for n in [0,1,4095,4096,4097]:
            h[x]=n;f=old_features(h);g=unpack(a*n,b*n);assert f==g and cls(f,n)==cls(g,n);tests+=1
    virtual=[]
    for bits in [32,64]:
        mask=(1<<bits)-1
        for n in [0,1,2047,2048,2049,4095,4096,4097,8191,8192,65535,mask]:
            for mode in range(5):
                step=(n//2048)|1;i=0;t=0;a=b=0;h=[0]*256;positions=[]
                while i<n and t<4097:
                    x=[0,65,128,(i^(i>>8))&255,b'abc012;\n'[i%8]][mode]
                    h[x]+=1;aa,bb=entry(x);a=(a+aa)&((1<<64)-1);b=(b+bb)&((1<<64)-1)
                    positions.append(i);t+=1;i=(i+step)&mask
                f=old_features(h);g=unpack(a,b);assert f==g and cls(f,t)==cls(g,t)
                virtual.append({'usize_bits':bits,'n':n,'mode':mode,'samples':t,'class':cls(f,t),'positions_sha256':sha(json.dumps(positions).encode())})
    return {'status':'VERIFIED_FINITE_PYTHON_FEATURE_PACK_MODEL','single_byte_and_repeated_boundary_cases':tests,'virtual_stride_cases':len(virtual),'virtual_cases':virtual,'feature_order':['dna','text','high','words','syms','digits','zero'],'source_note':'text includes all32..255 except127 plus9/10/13, including high bytes; words onlyspace/A-Z/a-z','not_proved':'all-input classifier equivalence, native parser equality, Aeneas/Lean gate, performance'}

LEAN=r'''
-- Predicted single-loop ABI; actual official extraction must confirm it.
theorem sniff_loop_spec (s : Slice Std.U8) (n : Std.Usize) (a b : Std.U64)
    (step i : Std.Usize) (tot : Std.U32) (hn : n.val = s.length) (ht : tot.val ≤ 4097) :
    slot.sniff_loop s n a b step i tot ⦃ fun r => r.2.2.val ≤ 4097 ⦄ := by
  rw [slot.sniff_loop]
  apply Std.loop.spec_decr_nat (measure := fun r => 4097-r.2.2.2.val)
    (inv := fun r => r.2.2.2.val ≤ 4097)
  · rintro ⟨a,b,i,tot⟩ ht
    simp only [slot.sniff_loop.body]
    step*
    all_goals first
      | exact ht
      | (refine ⟨?_, ?_⟩ <;> scalar_tac)
  · exact ht

@[local step]
theorem sniff_spec (s : Slice Std.U8) : slot.sniff s ⦃ fun _ => True ⦄ := by
  rw [slot.sniff]
  step*
  apply Std.WP.spec_bind (sniff_loop_spec s (Std.Slice.len s) 0#u64 0#u64 step 0#usize 0#u32 (by simp) (by simp))
  rintro ⟨a,b,tot⟩ ht
  step*
  all_goals scalar_tac

'''

def generate():
    raw={f:(BASE/f).read_bytes() for f in PINS};assert {f:sha(v) for f,v in raw.items()}==PINS
    s=raw['parse.rs'].decode();old=function(s,'sniff')
    assert 'let step = (n / SAMPLE) | 1;' in old and 'while i < n && tot < 4097 {' in old
    assert re.search(r'pub const SAMPLE: usize = 2048;',s) and re.search(r'pub const SDIG: u32 = 6;',s)
    suffix=old[old.index('    let mut cls = 3usize;'):]
    digits_line=next(l for l in suffix.splitlines() if 'let digits = cnt[48]' in l)
    suffix=suffix.replace(digits_line+'\n','').replace('cnt[0]','zero')
    prefix='''pub fn sniff(s: &[u8]) -> usize {
    let n = s.len();
    let mut pack0 = 0u64;
    let mut pack1 = 0u64;
    let step = (n / SAMPLE) | 1;
    let mut i = 0usize;
    let mut tot = 0u32;
    while i < n && tot < 4097 {
        let feature = SNIFF_PACKED[s[i] as usize % 256];
        pack0 = pack0.wrapping_add(feature.0);
        pack1 = pack1.wrapping_add(feature.1);
        tot += 1;
        i = i.wrapping_add(step);
    }
    let dna = (pack0 & 8191) as u32;
    let text = ((pack0 >> 13) & 8191) as u32;
    let high = ((pack0 >> 26) & 8191) as u32;
    let words = ((pack0 >> 39) & 8191) as u32;
    let syms = (pack1 & 8191) as u32;
    let digits = ((pack1 >> 13) & 8191) as u32;
    let zero = ((pack1 >> 26) & 8191) as u32;
'''
    new=prefix+suffix
    table='\n// R11 exact sniff one-byte features;13-bit lanes, max4097 samples.\npub const SNIFF_PACKED: [(u64,u64);256] = [\n'+''.join(f'    ({a}u64,{b}u64),\n' for a,b in map(entry,range(256)))+'];\n'
    rust=(s.replace(old,new,1)+table).encode();assert (rust.decode()[:-len(table)].replace(new,old,1)).encode()==raw['parse.rs']
    lean=raw['Parse.lean'].decode();st=lean.index('theorem sniff_loop0_spec ');en=lean.index('/-! ## 14.',st)
    proof=(lean[:st]+LEAN+'\n'+lean[en:]).encode();assert 'slot.sniff_loop0' not in proof.decode() and 'slot.sniff_loop1' not in proof.decode()
    result=model();files={'parse.rs':rust,'Parse.lean':proof};parent=json.loads((BASE/'manifest.json').read_text())
    manifest={'candidate':NAME,'parent':'candidates/r3-432-fast3','parent_hashes':PINS,'hashes':{f:sha(v) for f,v in files.items()},'bytes':{f:len(v) for f,v in files.items()},'attribution':parent['attribution'],'mechanism':'Exact7-feature lookup into twoU64 13-bit-lane counters replaces256 histogram and224 postscan; sampling/threshold/priority unchanged','expected_equivalent_to':'r3-432-fast3','equivalence_status':'FINITE_PYTHON_MODEL_ONLY; native444/public token/byte PENDING, not all-input proof','proof_status':'UNCOMPILED_PREDICTED_SINGLE_LOOP_ABI; actual Funs must confirm sniff_loop and tuple positions; original Decode/root suffix retained','performance_status':'UNKNOWN; table4096B versus histogram1024B and two additions/read loads may lose; no vectorization claim','stop':'Reject any class/token mismatch or unsupported extraction; stop if paired time loses, no thresholds/tf_class/parameters/combination changes'}
    status={'status':'UNCOMPILED_INITIAL_SNIFF_TOTALITY_DRAFT','hashes':manifest['hashes'],'predicted_loop_state':['pack0','pack1','i','tot'],'predicted_loop_return':['pack0','pack1','tot'],'measure':'4097-tot','loop_max_precondition':'tot<=4097, initialized0; no semantic feature premise added to root','actual_extract':'PENDING','original_root_Decode_axioms':'unchanged text outside three old sniff specs','new_sorry_admit_axiom':False}
    assert not re.search(r'\b(sorry|admit|axiom)\b',LEAN)
    for f,v in [('manifest.json',manifest),('MODEL.json',result),('UNCOMPILED_STATUS.json',status)]:files[f]=(json.dumps(v,indent=2,ensure_ascii=False)+'\n').encode()
    files['SOURCE_AUDIT.json']=(json.dumps({'status':'VERIFIED_REVERSIBLE_SNIFF_ONLY_SOURCE','parent_hashes':PINS,'hashes':manifest['hashes'],'sampling_statement_exact':'step=(n/SAMPLE)|1, i<n&&tot<4097, tot+=1, i=wrapping_add(step)','classification_suffix':'exact original excluding precomputed digits line and cnt[0] renamedzero','tf_class_and_all_other_functions':'byte-identical','lane_offsets':[[0,13,26,39],[0,13,26]],'field_max':4097,'field_capacity':8191},indent=2)+'\n').encode()
    return files

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');a=ap.parse_args();fs=generate();d=ROOT/'candidates'/NAME;d.mkdir(parents=True,exist_ok=True)
    for f,v in fs.items():
        p=d/f
        if a.check:assert p.read_bytes()==v
        elif p.exists():assert p.read_bytes()==v,'Refusing frozen candidate mutation'
        else:p.write_bytes(v)
    print(json.dumps({'candidate':NAME,'status':'SOURCE_READY_LEAN_UNCOMPILED_EXTRACT_PENDING','hashes':{f:sha(v) for f,v in fs.items()},'builder_sha256':sha(Path(__file__).read_bytes())}))
if __name__=='__main__':main()
