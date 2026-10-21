"""Stop monotone distance-chain probes that the existing full buffer cannot accept."""
from pathlib import Path
import importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start')
HELPER='''#[inline(always)]
pub fn SFmaxcode(codes:&[usize;4])->usize {
 Z457(Z457(codes[0],codes[1]),Z457(codes[2],codes[3]))
}

'''
def main():
    p=ROOT/'candidates/r24-609-once';r,l=[(p/f).read_text()for f in ('parse.rs','Parse.lean')]
    a=r.index('pub fn SFmorematches(');b=r.index('pub fn SFheavy(',a);part=r[a:b]
    marker='if j>=p||d>32768{break;}let cap=';assert part.count(marker)==1
    part=part.replace(marker,'if j>=p||d>32768{break;}if count==4 && Z353(d)>SFmaxcode(&codes){break;}let cap=')
    r=r[:a]+HELPER+part+r[b:]
    proof='''@[local step]
theorem SFmaxcode_spec (codes : Array Std.Usize 4#usize) :
 slot.SFmaxcode codes ⦃ fun _ => True ⦄ := by
 rw [slot.SFmaxcode]
 step*
 all_goals scalar_tac

'''
    at=l.index('theorem SFmorematches');at=l.rfind('@[local step]',0,at);assert at>=0;l=l[:at]+proof+l[at:]
    e=w.write_candidate('r24-609-cap-stop',p.name,r,l,
        'On the original four-code SF collector, stop its strictly backward full-position chain once the buffer is full and the next distance code exceeds every retained code. Later distances cannot return to a retained code, and the original SFfastadd would discard those new codes without updating slots.',
        'L observed millions of overflow additions and only11bytes from retaining new choices. This removes actual work the original collector cannot consume, rather than spending more work to improve the buffer. It is separate from L: do not combine its changed acceptance policy with this original-policy early stop.',
        {'parent':p.name,'source':'references/round24-public-609/source-receipt.json','overflow_evidence':'evidence/round24/38084061512/buffer-l-native/diagnostics/r24-buffer/receipt.json','scope':'Token preservation is expected for the constructed monotone predecessor chain; finite equality and a new original gate remain required.'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    s=json.loads((E/'seedtail-d-native.json').read_bytes());s['entries']=[x for x in s['entries']if x['control']]+[e]
    s.update(r24_cap_counts=True,description='R24 M skip monotone distance-code tail after original buffer saturation. Observe original over-max probes and verify actual complete token/output parity; do not combine with L changed slot policy.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    (E/'cap-m-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
    plan={'gap':'L observed3146060 distinct-code overflows; almost all had a dominated slot, but changing acceptance only saved11bytes. Original policy silently ignores later new codes, suggesting unnecessary matching work.',
        'change':'Stop only after all4slots are filled and monotone current distance code exceeds the maximum retained code. Preserve same-code longer updates and every pre-saturation query.',
        'minimum':'Untimed old-path counts plus28-file native token/encoder/decode equality; generated boundary equality follows only if useful. Original paired timing remains required.',
        'decision':'If original over-max work exists and outputs remain identical, buy a paired timing comparison. Any output difference must be diagnosed before calling it redundant-work removal. L and M cannot be naively combined.',
        'cost_cap_runner_minutes':15,'evidence':'evidence/round24/<run>/cap-m-native/diagnostics','proof':'New max helper and control-flow change are draft until fresh exact gate.'}
    (E/'preflight-m.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode());print(e['name'])
if __name__=='__main__':main()
