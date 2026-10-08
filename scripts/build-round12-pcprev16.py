"""Revisit compact links on newly public #507's shallow fast engine, not D planning."""
from pathlib import Path
import argparse, hashlib, json, random

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'references/round12-public-507'
NAME='r12-fast-pc507-prev16'

def sha(b):return hashlib.sha256(b).hexdigest()

def generate():
    raw={f:(BASE/f).read_bytes()for f in ('parse.rs','Parse.lean')}
    receipt=json.loads((BASE/'receipt.json').read_bytes())
    assert {f:sha(b)for f,b in raw.items()}==receipt['files']
    original=raw['parse.rs'].decode()
    start=original.index('pub fn pc_f_link<const H: usize>')
    end=original.index('/// Structured binaries (class 3)',start)
    section=original[start:end];changed=section
    edits=[('[u32; 32768]','[u16; 32768]',3),
        ('prev[i % 32768] = head[a];','let delta = i.wrapping_sub(head[a] as usize);\n    prev[i % 32768] = if delta <= 32768 { delta as u16 } else { 0 };',1),
        ('let c3 = prev[c2 % 32768] as usize;','let c3 = c2.wrapping_sub(prev[c2 % 32768] as usize);',1),
        ('let mut prev = [0u32; 32768];','let mut prev = [0u16; 32768];',1),
        ('let cl = prev[c % 32768] as usize;','let cl = c.wrapping_sub(prev[c % 32768] as usize);',1)]
    for a,b,count in edits:
        assert changed.count(a)==count,(a,changed.count(a),count)
        changed=changed.replace(a,b)
    back=changed
    for a,b,count in reversed(edits):
        assert back.count(b)==count
        back=back.replace(b,a)
    assert back==section
    source=original[:start]+changed+original[end:]
    assert source.replace(changed,section,1)==original
    files={'parse.rs':source.encode(),'Parse.lean':raw['Parse.lean']}
    manifest={'candidate':NAME,'parent':BASE.relative_to(ROOT).as_posix(),'parent_hashes':receipt['files'],
        'hashes':{f:sha(b)for f,b in files.items()},'formal_anchor_id':'507','comparison_baseline':'public507',
        'attribution':{'source':'Officially published #507; original comments retain #435/#436/#488/#503 lineage',
            'author_hotkey':receipt['author_hotkey'],'reference':(BASE/'PROVENANCE.md').relative_to(ROOT).as_posix()},
        'mechanism':'Only PC run1c predecessor links become u16 backward distances. One32768-cell predecessor table falls from128KiB to64KiB; absolute heads, insertion order, shallow depth1/2 and every route remain unchanged.',
        'difference_from_old_work':'Explicit R10 delta16 mechanism revisit under a new legitimate parent: #507 became public after #514 dominated it. R10 applied two predecessor arrays in D forward planning with deeper walks; this version changes one array in shallow PC speed-end rows. Encoding overhead remains a falsifiable cost, not assumed free.',
        'equivalence_argument':'Live unaliased links recover the same older positions. A discarded >32768 link cannot lead to an in-window older candidate. At current-slot alias distance32768, every decreasing successor is out of window in both representations. Zero encodes a self terminator; candidate0 remains representable through positive deltas at positive insertion positions.',
        'expected_equivalent_to':'public507','equivalence_status':'INFERRED reachable parser states; finite native/public identity required; general u32-position wrap not claimed as semantic equality',
        'proof_status':'UNADAPTED_PARENT_ONLY; U16 PC loop-state and delta helper totality need actual extraction and complete original gate',
        'source_reversal':'Exactly reverses three explicit array types, two reads, one store and one initializer; no new input lengths or routing features introduced',
        'fixed_predecessor_bytes_before':131072,'fixed_predecessor_bytes_after':65536,
        'performance_status':'UNKNOWN. Initialization/store bandwidth versus encode/decode arithmetic must be measured in total compression.',
        'stop_condition':'Any native/public mismatch rejects equivalence. No useful gain versus both parent copies closes this version without full gate. Public-to-formal #507 transfer remains a hypothesis.',
        'formal_submission_sent':False}
    files['manifest.json']=(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n').encode()
    return files

def model():
    rng=random.Random(1208507);W=32768;mask=(1<<64)-1
    old=[0]*W;new=[0]*W;heads=[0]*1024;cases=aliases=zero_targets=0
    for p in range(1,200001):
        a=rng.randrange(len(heads));c=heads[a]
        # Inject exact-window candidates via a dedicated bucket at regular boundaries.
        if p%W==0:c=p-W
        old[p%W]=c
        delta=(p-c)&mask;new[p%W]=delta if delta<=W else 0
        heads[a]=p
        if 1<=p-c<=W:
            def visits(prev,compact):
                v=prev[c%W];c2=((c-v)&mask)if compact else v
                values=[]
                if c2<c and 1<=((p-c2)&mask)<=W:values.append(c2)
                if c2<c:
                    v3=prev[c2%W];c3=((c2-v3)&mask)if compact else v3
                    if c3<c2 and 1<=((p-c3)&mask)<=W:values.append(c3)
                return values
            assert visits(old,False)==visits(new,True),(p,c,visits(old,False),visits(new,True))
            cases+=1;aliases+=(p-c==W);zero_targets+=(0 in visits(old,False))
    return {'status':'VERIFIED_FINITE_ELIGIBLE_CHAIN_VISIT_MODEL','seed':1208507,'insertions':200000,
        'live_cases':cases,'exact_window_aliases':aliases,'eligible_zero_targets':zero_targets,
        'scope':'Model of shallow eligible predecessor positions over reachable insertion schedules; not native Rust, all-input equality, Lean gate or timing.'}

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--check',action='store_true');args=ap.parse_args()
    files=generate();dest=ROOT/'candidates'/NAME
    if args.check:assert all((dest/f).read_bytes()==b for f,b in files.items())
    else:
        assert not dest.exists();dest.mkdir()
        for f,b in files.items():(dest/f).write_bytes(b)
    result=model()
    if not args.check:(dest/'model.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({'candidate':NAME,'hashes':{f:sha(b)for f,b in files.items()},'model':result}))

if __name__=='__main__':main()
