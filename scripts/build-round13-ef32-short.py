"""Test short-token price separately from EF32 search-position density."""
from pathlib import Path
import argparse,hashlib,json

ROOT=Path(__file__).resolve().parents[1];BASE=ROOT/'references/round13-public-514'

def sha(b):return hashlib.sha256(b).hexdigest()

def generate(kind):
    assert kind in('lits3','min4')
    raw={f:(BASE/f).read_bytes()for f in('parse.rs','Parse.lean')};origin=json.loads((BASE/'receipt.json').read_bytes());assert {f:sha(b)for f,b in raw.items()}==origin['files']
    original=raw['parse.rs'].decode();a=original.index('pub fn ef32_run(');b=original.index('// ─────────────── ETINY:',a);old=original[a:b]
    if kind=='min4':
        before='if l >= 3 {';after='if l >= 4 {';assert old.count(before)==1
        body=old.replace(before,after,1);assert body.replace(after,before,1)==old
    else:
        before='''                nt = ef32_put_lits(input, out, nt, ls, p);
                out[nt] = ef32_tok(p - c, l);
                nt += 1;'''
        after='''                if l == 3 {
                    nt = ef32_put_lits(input, out, nt, ls, p + l);
                } else {
                    nt = ef32_put_lits(input, out, nt, ls, p);
                    out[nt] = ef32_tok(p - c, l);
                    nt += 1;
                }'''
        assert old.count(before)==1;body=old.replace(before,after,1);assert body.replace(after,before,1)==old
    rust=(original[:a]+body+original[b:]).encode();proof=raw['Parse.lean']
    if kind=='lits3':
        # Deliberately preserve the original proof as a draft. A new immutable
        # proof candidate will bind the actual extracted branch interface if
        # real encoder measurements justify promotion.
        proof_status='PARENT_PROOF_DRAFT_UNADAPTED_FOR_NEW_LITERAL_BRANCH; full gate NOT_RUN'
    else:proof_status='PARENT_PROOF_UNCOMPILED_FOR_MIN4; existing MatchAt requires3 and new branch supplies4'
    n='r13-514-ef32-'+kind;files={'parse.rs':rust,'Parse.lean':proof}
    manifest={'candidate':n,'parent':'public514','comparison_baseline':'public514','formal_anchor_id':'514','native_relation':'decode_only',
        'hashes':{f:sha(b)for f,b in files.items()},'parent_original_hashes':origin['files'],
        'mechanism':'Write3-byte EF32 matches as literals while keeping original probe/advance/reset positions exactly unchanged.'if kind=='lits3'else'Only accept EF32 matches of at least4 bytes; rejection uses original miss skip and changes future positions.',
        'evidence_basis':'Untimed exact-output observer on public514 found31998 EF32 matches covering96216 bytes and zero wider-key opportunities; 3-byte token pricing is now the specific test.',
        'difference_from_previous':'Different from wide-hash and long-prefix SIMD. Isolates short-token encoding value from candidate coverage; min4 is the position-density control.',
        'attribution':{'source':'Official public514; original headers retained','author_hotkey':origin['author_hotkey'],'reference':'references/round13-public-514/PROVENANCE.md'},
        'proof_status':proof_status,'performance_status':'UNKNOWN; actual official encoder and paired total-time measurement required',
        'semantic_status':'Search/emit token changes permitted; every match remains original validated EF32 match, literals are original bytes. No compression monotonicity claimed.',
        'source_reversal':'Original bytes recovered by reversing one isolated EF32 emission/acceptance block. All routes and other engines unchanged.',
        'stop_condition':'Any actual decode/panic failure or insufficient two-axis gain relative to current official family boundary closes this frozen Rust.',
        'formal_submission_sent':False}
    files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode();return n,files

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    for kind in('lits3','min4'):
        n,files=generate(kind);p=ROOT/'candidates'/n
        if args.check:assert all((p/f).read_bytes()==b for f,b in files.items())
        else:
            assert not p.exists();p.mkdir()
            for f,b in files.items():(p/f).write_bytes(b)
        print(json.dumps({'candidate':n,'hashes':{f:sha(b)for f,b in files.items()},'status':'DRAFT_NOT_RUN'}))

if __name__=='__main__':main()
