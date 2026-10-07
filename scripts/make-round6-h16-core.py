"""Two H16-small core hypotheses; exact frozen parent and scoped output paths.

Generate source plus explicitly NOT_ADAPTED reference proof. No compiler, CI,
network, Git or wallet action. --check is byte-for-byte read-only verification.
"""
from __future__ import annotations
import argparse
import hashlib
import importlib.util
import json
import random
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PARENT = ROOT / 'candidates/r5-h16-small-proofopt'
LOCK = {'parse.rs': 'd9826bc92ba02f49cb6e552ed172a4fb82dc10fa8fb51aacf73e7947ed38a94d',
        'Parse.lean': 'd55744de52bb0469768f0bbfd73ffecbabf9899b63e0167469fd7bb79c6293c7'}
RECIPES = ('r6-h16-core-h3prefix', 'r6-h16-core-lazy-t5')
module_spec = importlib.util.spec_from_file_location('r6_declaration_audit', ROOT/'scripts/make-round4-hybrid.py')
module = importlib.util.module_from_spec(module_spec)
module_spec.loader.exec_module(module)


def sha(data): return hashlib.sha256(data).hexdigest()

def once(text, old, new):
    assert text.count(old) == 1, (old, text.count(old))
    return text.replace(old, new, 1)


def generate(name, check):
    parent = {n: (PARENT/n).read_bytes() for n in LOCK}
    for n, h in LOCK.items(): assert sha(parent[n]) == h, (n, 'parent drift')
    source = parent['parse.rs'].decode()
    funcs, constants, types = module.declarations(source)
    changed = {}
    if name == 'r6-h16-core-h3prefix':
        body = funcs['h_bt_walk']['text']
        body = once(body, '    hint: usize,\n    mc:', '    hint: usize,\n    known_pos: usize,\n    known_len: usize,\n    mc:')
        body = once(body,
            '            let l0 = h_sel(h_eq(cur, kcur) & h_lt(len, kl), kl, len);',
            '''            let previous = h_sel(h_eq(cur, kcur) & h_lt(len, kl), kl, len);
            // The H3 probe already compared this exact source/current pair.
            // Reuse its verified prefix only when the tree visits that source.
            let l0 = h_sel(h_eq(cur, known_pos) & h_lt(previous, known_len), known_len, previous);''')
        changed['h_bt_walk'] = body
        changed['h_find_pos'] = once(funcs['h_find_pos']['text'],
            'depth, hint, mc, m0);', 'depth, hint, c3, l3, mc, m0);')
        mechanism = 'Pass the already compared H3 source c3 and exact prefix length l3 into the tree walk. At the same tree source only, start comparison at max(existing proven prefix,l3). Preserve traversal order, stop/depth bounds, record emission, cache policy and all cost/iteration settings.'
        proof_gap = 'h_bt_walk and its extracted loop gain known_pos/known_len captures; h_find_pos calls the changed signature. Preserve checked emitter/match proof; adapt totality specs from fresh Funs before any gate.'
        risks = ['Two extra live scalar arguments and a compare/select at every visited tree node can outweigh the skipped byte loads; no speedup claimed.',
                 'Prefix reuse relies on equality of the encoded source position cur==c3; do not replace it with a hash equality.',
                 'Lexicographic comparison must remain identical whenever len<stop; when reaching stop its tie-direction bit is unused.']
    else:
        changed['h_optimize'] = once(funcs['h_optimize']['text'],
            '    let mut t5 = h_filled(nbmax.wrapping_mul(H_TB), 0);',
            '''    // hi is a Boolean flag AND i5; a zero low bit makes t5 unreachable.
    let mut t5 = h_filled(h_sel(i5 & 1, nbmax.wrapping_mul(H_TB), 0), 0);''')
        changed['h_literal_bits'] = once(funcs['h_literal_bits']['text'],
            '        h_init5_table(fr, t5, b.wrapping_mul(H_TB));',
            '''        // An empty optional table cannot be observed by the caller.
        if t5.len() > 0 {
            h_init5_table(fr, t5, b.wrapping_mul(H_TB));
        }''')
        mechanism = 'When i5 has zero low bit, hi=(Boolean & i5) is zero and the t5 table can never be copied into the active model. Allocate an empty t5 and skip its per-literal-block construction. Otherwise preserve the exact original table allocation/build. Keep literal evaluation, histograms, tlit and active models unchanged.'
        proof_gap = 'h_literal_bits loop gains a conditional optional-table update; h_optimize changes allocation length. The old totality proof is retained only as reference until the actual new extraction is checked.'
        risks = ['Only avoids the optional initialization work; if that work is a small part of total time, benefit may be negligible.',
                 'Branching in literal-block initialization and altered allocation/layout may regress time.',
                 'Equivalence argument concerns the complete exported parser; direct callers can observe a shorter optional scratch vector only inside h_optimize, whose result does not expose it.']
    for n, text in changed.items(): source = once(source, funcs[n]['text'], text)
    nf, nc, nt = module.declarations(source)
    assert nf.keys() == funcs.keys() and nc == constants and nt == types
    for n, declaration in funcs.items():
        assert nf[n]['text'] == changed.get(n, declaration['text']), ('unlisted function drift', n)
    assert nf['parse']['text'] == funcs['parse']['text'], 'entry route drift'
    proof = ('-- RESEARCH ONLY / NOT_ADAPTED: changed H core; frozen parent proof below is migration reference.\n').encode() + parent['Parse.lean']
    assert not re.search(r'(?m)^\s*(?:axiom|sorry|admit)\b', proof.decode())
    files = {'parse.rs': source.encode(), 'Parse.lean': proof}
    assert all(len(v) < 524288 for v in files.values())
    manifest = {'candidate': name, 'parent': {'path': PARENT.relative_to(ROOT).as_posix(), 'hashes': LOCK,
                    'fresh_gate': '37584216832/h16-proofopt-gate', 'gate_scope': 'Existing parent only; not new candidate proof'},
                'hashes': {n: sha(v) for n, v in files.items()}, 'bytes': {n: len(v) for n, v in files.items()},
                'mechanism': mechanism, 'changed_functions': sorted(changed),
                'preserved': 'Exact parent declaration text for every other function, all constants/types, small-input routing, A/C portfolio, H search budgets, cost tables, encoder and checked emission.',
                'proof_status': 'NOT_ADAPTED', 'proof_migration': proof_gap,
                'validation': 'VERIFIED local hash locks, declaration scope and generation only. Rust build/extraction, finite token/decode equality, matched performance, new Lean/axioms and gate remain UNKNOWN.',
                'expected_equivalent_to': 'h16-base',
                'gate_policy': 'Research native/finite equivalence/extract-only first; no complete candidate gate until actual proof migration is validated.',
                'performance_risks': risks,
                'attribution': 'External public submissions 299 and 402 via frozen r5-h16-small-proofopt. Original source/provenance retained under references/round4-public-299 and references/round4-public-402.',
                'frontier_scope': 'H/S calibration remains disputed: snapshot25924 fixed427 and matched299 projections differ. Unchanged public size plus measured speed is not formal admission or payout.'}
    files['manifest.json'] = (json.dumps(manifest, indent=2)+'\n').encode()
    destination = ROOT/'candidates'/name
    if check:
        for n, data in files.items(): assert (destination/n).read_bytes() == data, (name, n, 'generated bytes drift')
    else:
        destination.mkdir(parents=True, exist_ok=True)
        for n, data in files.items(): (destination/n).write_bytes(data)
    print(json.dumps({'candidate': name, 'hashes': manifest['hashes'], 'bytes': manifest['bytes'], 'proof_status': 'NOT_ADAPTED'}))


def model_check():
    # Compare the actual extension's observable length and tree direction when
    # given a byte-proven prefix. This is a Python translation, not Rust execution.
    rng = random.Random(616032)
    def word(data, p): return int.from_bytes(data[p:p+8].ljust(8,b'\0'), 'little')
    def first(x): return min(((x & -x).bit_length()-1)//8,7) if x else 7
    def direction(x,y,k): return int(((x>>(8*k))&255)<((y>>(8*k))&255))
    def extend(data,a,b,start,lim):
        x=word(data,a+start);y=word(data,b+start)
        if x!=y:
            fd=first(x^y);return (start+fd)*2+direction(x,y,fd)
        length=start+8;it=0;z=0;x=0
        while it<40 and z==0 and length<lim:
            x=word(data,a+length);z=x^word(data,b+length)
            length+=8 if z==0 else 0;it+=1
        fd=first(z);lf=length if z==0 else length+fd
        return min(lf,lim)*2+direction(x,x^z,fd)
    cases=0;reused=0
    for trial in range(12000):
        n=rng.randrange(8,900);data=bytearray(rng.randrange(256) for _ in range(n))
        b=rng.randrange(1,n);a=rng.randrange(b);cap=min(258,n-b)
        equal=rng.randrange(cap+1)
        for j in range(equal):data[b+j]=data[a+j]
        actual=0
        while actual<cap and data[a+actual]==data[b+actual]:actual+=1
        known=min(actual,8)
        previous=rng.randrange(actual+1)
        # Existing skip/hint prefixes are bounded by the active comparison cap.
        left=extend(bytes(data),a,b,previous,cap)
        start=max(previous,known)
        right=extend(bytes(data),a,b,start,cap)
        ll=min(left//2,cap);rr=min(right//2,cap)
        assert ll==rr,(trial,a,b,cap,previous,known,left,right)
        if ll<cap:assert left%2==right%2,(trial,'tree direction')
        cases+=1;reused+=start>previous
    flags=0
    for i5 in list(range(4096))+[(1<<32)-1,(1<<64)-1]:
        for predicate in (0,1):
            hi=predicate&i5
            if not(i5&1):assert hi==0
            assert hi in (0,1)
            flags+=1
    return {'scope': 'Python byte-prefix and optional-table dataflow models only; not Rust or formal proof',
            'seed':616032,'extension_cases':cases,'cases_with_reused_prefix':reused,'i5_flag_cases':flags,'mismatches':0}


if __name__ == '__main__':
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check',action='store_true')
    ap.add_argument('--only',action='append',choices=RECIPES,default=[])
    ap.add_argument('--model-check',action='store_true')
    args=ap.parse_args()
    if args.model_check: print(json.dumps(model_check()))
    else:
        for name in args.only or RECIPES:generate(name,args.check)
