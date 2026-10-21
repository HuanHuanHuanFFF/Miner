"""Hoist the fixed nine-bit cost packing out of A's per-length comparison loops."""
from pathlib import Path
import json,importlib.util,random
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round21'
def main():
 sp=importlib.util.spec_from_file_location('w',ROOT/'scripts/build-round18-start.py');w=importlib.util.module_from_spec(sp);sp.loader.exec_module(w)
 p=ROOT/'candidates/r19-sf-nooverlap';r,l=[(p/f).read_text()for f in ('parse.rs','Parse.lean')]
 a=r.index('pub fn a_dp_pass(');b=r.index('pub fn a_walk(',a);part=r[a:b]
 assert part.count('let nxt = cost[i + 1];')==1;part=part.replace('let nxt = cost[i + 1];','let nxt = cost[i + 1] >> 9;')
 part=part.replace('let cl = cost.len();','let lc = a_packed_costs(lc);\n    let cl = cost.len();')
 old='let base = dc[((m >> 23) % 32) as usize].wrapping_add(bias);';assert part.count(old)==1;part=part.replace(old,old.replace('.wrapping_add(bias);','.wrapping_add(bias) << 9;'))
 old='let base = dc[(a_slot_of(x) % 32) as usize].wrapping_add(bias);';assert part.count(old)==1;part=part.replace(old,old.replace('.wrapping_add(bias);','.wrapping_add(bias) << 9;'))
 assert part.count('.wrapping_add(base) << 9)')==3;part=part.replace('.wrapping_add(base) << 9)','.wrapping_add(base))')
 helper='''pub fn a_packed_costs(src:&[u32;512])->[u32;512] {
 let mut dst=[0u32;512];let mut j=0usize;
 while j<512 {dst[j]=src[j] << 9;j+=1;}dst
}

'''
 r=r[:a]+helper+part+r[b:]
 old='if i < cost.len() { cost[i] = value; }';assert r.count(old)==1;r=r.replace(old,'if i < cost.len() { cost[i] = value << 9; }')
 proof='''@[local step]
theorem a_packed_costs_loop_spec (src dst : Array Std.U32 512#usize) (j : Std.Usize) :
 slot.a_packed_costs_loop src dst j ⦃ fun _ => True ⦄ := by
 rw [slot.a_packed_costs_loop]
 apply Std.loop.spec_decr_nat (measure := fun q => 512 - q.2.val) (inv := fun _ => True)
 · rintro ⟨dst1,j1⟩ _
   simp only [slot.a_packed_costs_loop.body]
   step*
   repeat' (split <;> step*)
   all_goals scalar_tac
 · trivial
@[local step]
theorem a_packed_costs_spec (src : Array Std.U32 512#usize) :
 slot.a_packed_costs src ⦃ fun _ => True ⦄ := by
 rw [slot.a_packed_costs]
 step*

'''
 marker='@[local step]\ntheorem a_dp_pass_loop0_spec';assert l.count(marker)==1;l=l.replace(marker,proof+marker)
 en=w.write_candidate('r21-a-packed-cost',p.name,r,l,
  'Store backwardA costs in pre-shifted9-bit packing, prepack512lengthprices once perDPpass and distancebase once perrecord. Perlength loop now adds packed components plus length stamp, instead of shifting the sum repeatedly.',
  'PriorRF span pruning and SF shared-length tests did not change this A cost representation. Here all compared words are intended bit-identical modulo32bits; cost tail is reset by the originalpass and nextcost is decoded for bias. Finite parity and original fresh gate are still required.',
  {'parent':p.name,'profile':'evidence/round19/38042741551/profile-b-native/diagnostics/r18-functions/functions.json','originalsource':'603/586 authors retained','proof':'Newarraypacker totality and changedA body stilldraft'})
 en.update(anchor='base603',comparison_baseline='nooverlap',native_decode_reference='nooverlap',expected_equivalent_to='nooverlap')
 s=json.loads((E/'probe-d-native.json').read_bytes());s['entries']=[e for e in s['entries']if e.get('control')and e['name']not in ['public608','public608-shadow']]+[en];s['native_encoder_references']=['base603','nooverlap'];ns=[e['name']for e in s['entries']];s['screen_orders']=[ns,ns[::-1]];s['description']='R21 H originalencoder/decode for packed-cost baseA kernel on exactnooverlap parent; candidate choice equality hypothesis,15minute cap.';(E/'probe-h-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
 rng=random.Random(2100);mask=2**32-1
 for _ in range(100000):
  x,y,z=[rng.getrandbits(32)for _ in range(3)];n=rng.randrange(259)
  old=((((x+y+z)&mask)<<9)&mask)|n;new=(((x<<9)+(y<<9)+(z<<9))&mask)|n;assert old==new
 (E/'preflight-h.json').write_bytes((json.dumps({'gap':'Highquality needs larger totaltime benefit; SF-only changes touch minority of measuredinclusivecost. A perlengthpacking is repeatedly applied in basicDP.','change':'Re-encode internalprice vector and hoist fixedshift from perlength loop, keepsameprefix search and intended choice ordering.','minimum':'100000deterministicu32 packing identities and full28file actualtoken/encoder/decode comparison. Scalar checks do not prove kernel equivalence.','decision':'Exacttokenparity earns originaltotal time. Anydifference requires identifying mixed raw/packed use before promotion.','cap_runner_minutes':15,'proof_gap':'Fresh a_packed_costs helper specs and newexactA body must pass originalverifier; byte parity alone insufficient.'},indent=2)+'\n').encode());print(en['name'])
if __name__=='__main__':main()
