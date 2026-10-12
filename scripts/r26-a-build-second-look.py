"""Use the already cached p+2 offer once when ordinary PC lazy rejects p+1."""
from pathlib import Path
import hashlib
import json
import random

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'evidence/round26/route-a'
BASE = ROOT / 'references/round26-public-641'
NAME = 'r26-a-641-second-look'
RUST = '97254225b7a7a5c67a749b9fed7b58c94a9612b816c233581db6d7401d502181'
LEAN = '7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e'
OLD = '''                    } else {
                        go = 0;
                    }'''
NEW = '''                    } else {
                        // a2 has already cached q+1; no new hash/chain lookup is needed for this offer.
                        let q2 = q + 1;
                        if q2 < lim && l <= input.len() - q2 {
                            let second = pc_probe_lazy(input, pre_c, pre_w, q2, l);
                            // At H=max(l,2+m): current costs C(l,d)+(H-l)*HLIT;
                            // second costs 2*HLIT+C(m,dm)+(H-2-m)*HLIT.
                            // Under the inherited literal-price approximation this is exactly gain(second)>gain(current).
                            if second.0 >= 4 && pc_gain(second.0, second.1) > pc_gain(l, d) {
                                pc_f_link::<H>(&mut head, &mut prev, pre_slot, q2);
                                ins = q2 + 1;
                                let next = pc_ahead_if_m::<H>(input, &head, q2 + 1, lim, pre_slot, pre_c, pre_w, km);
                                pre_slot = next.0;
                                pre_c = next.1;
                                pre_w = next.2;
                                p = q2;
                                l = second.0;
                                d = second.1;
                            }
                        }
                        // At most one second-position chance per outer match; never continue to lookahead3/4.
                        go = 0;
                    }'''


def sha(raw): return hashlib.sha256(raw).hexdigest()
def dump(path, value): path.write_bytes((json.dumps(value, indent=2) + '\n').encode())


def generate():
    raw = (BASE / 'parse.rs').read_bytes(); lean = (BASE / 'Parse.lean').read_bytes()
    assert sha(raw) == RUST and sha(lean) == LEAN
    source = raw.decode(); a = source.index('pub fn pc_run1c<const H: usize>')
    b = source.index('\n#[inline(always)] pub fn pc_put_match_checked', a)
    body = source[a:b]; assert body.count(OLD) == 1
    changed = source[:a] + body.replace(OLD, NEW) + source[b:]
    assert changed.replace(NEW, OLD, 1) == source
    assert len(changed.encode()) <= 524288 and len(lean) <= 524288
    return changed.encode(), lean


def model():
    def gain(l, d):
        return 80*l - 168 - (16*((l-3).bit_length()-3) if 10 < l < 258 else 0) - (16*((d-1).bit_length()-2) if d > 4 else 0)
    rng = random.Random(260010); checks = 0
    for _ in range(10000):
        l = rng.randrange(3,259); m = rng.randrange(4,259); d = rng.randrange(1,32769); md = rng.randrange(1,32769)
        horizon = max(l,2+m); current_cost = 80*l-gain(l,d)+(horizon-l)*80
        second_cost = 2*80 + 80*m-gain(m,md)+(horizon-2-m)*80
        assert second_cost-current_cost == gain(l,d)-gain(m,md)
        assert (second_cost < current_cost) == (gain(m,md) > gain(l,d)); checks += 1
    # Near input end p+l<=n alone is insufficient at q2; the explicit remaining guard is necessary.
    examples = [{'n':100,'p':80,'l':20},{'n':100,'p':80,'l':18},{'n':100,'p':90,'l':4}]
    for row in examples:
        n,p,l = row['n'],row['p'],row['l']; q2=p+2
        row['eligible'] = q2 < n-8 and l <= n-q2
        if row['eligible']: assert q2+8<=n and q2+l<=n
    assert examples[0]['eligible'] is False and examples[1]['eligible'] is True and examples[2]['eligible'] is False
    return {'status':'VERIFIED_FINITE_COMMON_HORIZON_COST_IDENTITY_AND_TAIL_GUARD_NOT_PARSER', 'cases':checks,
            'two_leading_literals_cost_units':160, 'literal_price_units':80, 'tail_examples':examples,
            'limits':'Fixed inherited literal/match estimate with uncovered suffix treated as literals; not actual future parsing or Huffman optimality.'}


def main():
    predeclared = {'status':'PREDECLARED_BEFORE_A10_NATIVE',
                  'gap':'Original641 PC_chain lazy computes a2 for p+2 before rejecting p+1, then never evaluates that cached candidate. A8 added older sources at the sameq with1.211Mextra probes and +2.3percentcost; this instead compares a new start with its existing cached sourceword.',
                  'change':'Only at original lazy rejection, try the already cached q+1 once if it is beforelim and currentl fits its remaininginput. Accept by explicit common-horizon originalcost comparison. Insert accepted newstart once and refresh next cache; immediately leave lazy whether accepted or not. No additionalchain/table/depth/mask/route or A8/A9 combination.',
                  'literal_cost':'For H=max(l,2+m), compare C(l,d)+(H-l)*80 with2*80+C(m,dm)+(H-2-m)*80. This cancels to the existing strictgain comparison. Both skipped leading literals and opposite-path trailing literals are included; finalfold can modify physicalemission.',
                  'tail_boundary':'q2<lim givesq2+8<n. Explicitl<=n-q2 providesq2+l<=n, stronger than originalprobe_lazy_spec requirement<=n+1; originalp+l<=n alone wouldnot suffice. No weakenedobligation.',
                  'coverage_hypothesis':'BroadexistingPCchain lazy-rejection sites can gain a different start without a new hash/prev source lookup. This could recover more quality per validation than A8 but magnitude is UNKNOWN. Native quality must be compared with approximately.195pp public fixed-time5percentscale; small gains do not imply target success.',
                  'costs':'Oneextra bytevalidated probe per outer matched decision that reaches a rejectedlazy site; on acceptance onehead/prev insertion and possible next-cache lookup. Existing prefetch is a sunk source-level operation, not a machine-time saving guarantee. All changedtrajectory/encodercosts remain.',
                  'minimum':'Original28file encoder/independentdecode with actual641/514; untimed candidate observer binds actualtokens and counts oldrejects, eligiblecachedprobes, acceptedsecondoffers, extra insertions/prefetches andpendingliteralpositions. No fullproof before usefulquality and totalcost.',
                  'stop':'Reject panic/decode/missingbinding. If this fixedsecondchance has insufficient quality scale or costly totals, stop; never automatically extend tolookahead3/4 or sweep acceptance penalties.',
                  'cap_runner_minutes':12,
                  'proof':'OriginalLazyInv1.accept allows any newi>=P0, not onlyp+1. New q2 remainingguard supplies probe preconditions; refresh preserves HeadBound/cacheword/ins bounds. Same loopstate/captures expected but actualextraction mandatory. Copied641 Lean is UNADAPTED.'}
    dump(OUT/'cycle-a10-predeclared.json',predeclared);dump(OUT/'second-look-model.json',model())
    rust,lean = generate();dest=ROOT/'candidates'/NAME;assert not dest.exists();dest.mkdir()
    (dest/'parse.rs').write_bytes(rust);(dest/'Parse.lean').write_bytes(lean);hashes={'parse.rs':sha(rust),'Parse.lean':sha(lean)}
    manifest={'candidate':NAME,'parent':BASE.relative_to(ROOT).as_posix(),'hashes':hashes,
              'attribution':{'source_receipt':'references/round26-public-641/source-receipt.json','author_hotkey':'5FYhJSAu4q86E2Yn8UjNvpbUQVZGzq5wB7W7YFqnmvz288yo','ownership':'Derivativeofpublic641; originalheadersretained.'},
              'mechanism':predeclared['change'],'cost_model':predeclared['literal_cost'],'proof_status':'COPIED_ORIGINAL_LEAN_UNADAPTED','quality':'UNKNOWN','time':'UNKNOWN','formal_submission_sent':False}
    dump(dest/'manifest.json',manifest)
    entry={'name':NAME,'path':dest.relative_to(ROOT).as_posix(),'control':False,'hashes':hashes,'anchor':'public641','comparison_baseline':'public641','native_decode_reference':'public641'}
    dump(OUT/'second-look-entry.json',entry);dump(OUT/'second-look-build-audit.json',{'status':'VERIFIED_ONE_REJECTION_BRANCH_REVERSAL_NOT_NATIVE','hashes':hashes,'new_helpers':0,'new_loop_state_fields':0,'tail_guard':True,'proof_unchanged':True})
    spec=json.loads((OUT/'quality-a8-native.json').read_bytes());spec.pop('r26_a_lazy_chain_counts',None)
    spec['entries']=[e for e in spec['entries']if e['control']]+[entry];names=[e['name']for e in spec['entries']]
    spec.update(screen_orders=[names,names[::-1]],snapshot_pages='evidence/round26/official-hour2/pareto-pages.json',r26_a_second_look_counts=True,
                description=predeclared['gap']+' '+predeclared['change']+' Nativequality andrealoperationcounts first; commonhorizon two-literalcost andtaileligibility predeclared.')
    dump(OUT/'quality-a10-native.json',spec);print(json.dumps({'candidate':NAME,'hashes':hashes},indent=2))


if __name__ == '__main__':main()
