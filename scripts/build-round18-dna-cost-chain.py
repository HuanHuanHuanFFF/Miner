"""Correct the DNA literal-cost preflight and test one added match candidate."""
from pathlib import Path
import importlib.util,json,re

ROOT=Path(__file__).resolve().parents[1]

def main():
    sp=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    p=ROOT/'candidates/r17-dna-nofold-proof1';original=(p/'parse.rs').read_text();proof=(p/'Parse.lean').read_text();actual=int(re.search(r'pub const pc_HLIT: u32 = (\d+);',original).group(1));assert actual==80
    old=(ROOT/'candidates/r18-dna-gain40/parse.rs').read_text();assert old.count('pc_gain(f.0, f.1) > (f.0 as i32) * 24')==1
    correction={'status':'VERIFIED_PREVIOUS_EXPERIMENT_DEFINITION_ERROR','source':'candidates/r18-dna-gain40/parse.rs','actual_pc_HLIT_units':actual,'previous_subtraction_units':24,'previous_effective_literal_units':actual-24,'previous_effective_bits':(actual-24)/16,'previous_claimed_bits':2.5,'new_target_units':40,'required_subtraction_units':actual-40,'scope':'The prior exact source and all native receipts remain unchanged. It tested3.5bits, not2.5; its observed+1213B does not refute the intended2.5bit criterion.'}
    assert (actual-(actual-40))/16==2.5
    entries=[]
    a=original.index('pub fn pc_run1<');b=original.index('/// The class itself',a);part=original[a:b];needle='if f.0 >= 3 {';assert part.count(needle)==1
    part=part.replace(needle,f'if f.0 >= 3 && (km != 0 || pc_gain(f.0, f.1) > (f.0 as i32) * {actual-40}) {{');rust=original[:a]+part+original[b:]
    e=m.write_candidate('r18-dna-literal40-corrected',p.name,rust,proof,
      'Require positive estimated match savings under40/16=2.5bits perliteral in the existing DNA route, using the actual pc_HLIT=80/16=5bit source constant. The acceptance threshold subtracts40units perbyte from pc_gain; otherPC modes retain their criterion.',
      'Corrects the earlier gain40 preflight error: subtracting24 from actual80 tested56/16=3.5bits. That source and negative result are retained. This is the previously intended but unexecuted2.5bit model, with a source-derived preflight. It changes search decisions, so full actual bytes/time remain unknown.',
      {'parent':'candidates/r17-dna-nofold-proof1/manifest.json','correction':'evidence/round18/dna-cost-preflight-correction.json','ownership':'Original parser/proof authors and R17 contributions retained.'})
    e.update(anchor='dna582',comparison_baseline='dna582',native_decode_reference='dna582');entries.append(e)
    rust=original
    oldrow='pub fn p125_row4(input:&[u8],out:&mut[u32])->usize{pc_run1::<65536>(input,out,16,0,0,0)}';assert rust.count(oldrow)==1
    rust=rust.replace(oldrow,'pub fn p125_row4(input:&[u8],out:&mut[u32])->usize{pc_run1c::<65536>(input,out,16,0,0,0,1,6)}')
    a=rust.index('pub fn pc_f_record3<');b=rust.index('/// `pc_run1` with chain links',a);part=rust[a:b];needle='if stop > ins.wrapping_add(pc_INS_MAX) {';assert part.count(needle)==1;part=part.replace(needle,'if km != 0 && stop > ins.wrapping_add(pc_INS_MAX) {');rust=rust[:a]+part+rust[b:]
    a=rust.index('pub fn pc_run1c<');b=rust.index('\n    nt\n}',a)+len('\n    nt\n}');part=rust[a:b];needle='let b = pc_fold_w(input, out, nt, p, l, d);';assert part.count(needle)==1;part=part.replace(needle,'let b = r14_fold_optional(input, out, nt, p, l, d, km);');rust=rust[:a]+part+rust[b:]
    lean=proof;a=lean.index('theorem p125_row4_spec');b=lean.index('@[local step]',a);part=lean[a:b];needle='exact PC.run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)';assert part.count(needle)==1;part=part.replace(needle,'exact PC.run1c_spec _ input out _ _ _ _ _ _ hlen (by simp) (by simp)');lean=lean[:a]+part+lean[b:]
    e=m.write_candidate('r18-dna-chain2',p.name,rust,lean,
      'Reuse the existing compact-predecessor PC chain engine for the DNA route with exactly one additional older candidate after the nearest six-byte match. Preserve65536heads, denseDNA insertion, no-fold emission, skip/lazy budgets and byte validation. dp=1 means two total candidates, not three.',
      'AQ measured96908length6matches and26237length7matches in the original DNA parse; most accepted matches are short. This tests better match choice from one older occurrence while preserving low token count, rather than flooding the encoder with literals. It changes matcher capability and memory state; existing PC family proof reuse is only a draft for this exact route.',
      {'parent':'candidates/r17-dna-nofold-proof1/manifest.json','reuse':'Existing pc_run1c and compact predecessor mechanism; not an independently invented chain engine.','evidence':'evidence/round18/37992768154/demotion-aq-native/diagnostics/r18-demotion/demotion.json'})
    e.update(anchor='dna582',comparison_baseline='dna582',native_decode_reference='dna582');entries.append(e)
    s=json.loads((ROOT/'evidence/round18/dna-al-native.json').read_bytes());s.pop('r18_dna_domain_counts',None);s['entries']=[x for x in s['entries']if x.get('control')]+entries;s['screen_orders']=[[x['name']for x in s['entries']],[x['name']for x in reversed(s['entries'])]]
    s['description']='AR native: one correction and one distinct matching hypothesis. Source-derived literal40 criterion really uses2.5bits, unlike mislabeled earlier3.5bit test. Chain2 adds exactly one candidate via an existing compact chain while retainingdense/no-fold DNA behavior. Original28file encoder/decode, cap25job-minutes. Evaluate byte/token tradeoff and current required time before original timing. No current high-share signal, proof and time unknown; historical formal0 and0.108percent sensitivity remain.'
    (ROOT/'evidence/round18/dna-ar-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());(ROOT/'evidence/round18/dna-cost-preflight-correction.json').write_bytes((json.dumps(correction,indent=2)+'\n').encode())
    mp=ROOT/'candidates/r18-dna-gain40/manifest.json';mf=json.loads(mp.read_bytes());mf['original_mechanism_description']=mf['mechanism'];mf['mechanism']='The frozen source actually tests3.5bits perliteral: pc_HLIT=80 and subtraction24 imply56/16. The previous2.5bit description was incorrect; source and measured negative result are unchanged.';mf['assumption_correction']=correction;mp.write_bytes((json.dumps(mf,indent=2)+'\n').encode());print(json.dumps({'correction':correction,'candidates':entries}))

if __name__=='__main__':main()
