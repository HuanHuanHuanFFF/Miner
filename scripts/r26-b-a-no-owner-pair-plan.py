"""Last original total pair for owner-free flatten, after exact native full-state checks."""
from pathlib import Path
import argparse
import hashlib
import json

ROOT=Path(__file__).resolve().parents[1]
NAME='r26-b-552-a-no-owner'


def sha(raw):return hashlib.sha256(raw).hexdigest()


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--native-receipt',type=Path,required=True);ap.add_argument('--dp-receipt',type=Path,required=True);ap.add_argument('--capture',type=Path,required=True);a=ap.parse_args()
    paths=[p.resolve() for p in [a.native_receipt,a.dp_receipt,a.capture]];assert all(p.is_relative_to(ROOT/'evidence/round26') for p in paths)
    native,dp=json.loads(paths[0].read_bytes()),json.loads(paths[1].read_bytes())
    assert native['status']=='VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES'
    assert dp['status']=='VERIFIED_ACTUAL_ALL_A_DP_CALLS_FULL_COST_CH_PARENT_EQUAL_AND_TOKEN_DECODE_PARITY'
    assert dp['consumer_mode']=='B36_NO_OWNER_SCRATCH_EXACT_ACTUAL_DP_FULL_STATE_CHECK'
    assert dp['totals']['dp_calls']==dp['totals']['asserted_complete_cost_ch_dp_calls']==1376
    rows={r['candidate']:{} for r in native['rows']}
    for r in native['rows']:rows[r['candidate']][r['file']]=r
    assert len(rows[NAME])==len(rows['public552'])==28
    keys=['input_sha256','tokens_sha256','output_sha256','output_bytes'];assert all(all(r[k]==rows['public552'][f][k] for k in keys) for f,r in rows[NAME].items())
    spec=json.loads((ROOT/'evidence/round26/route-b/b33-a-flatten-screen.json').read_bytes())
    full=dict(next(e for e in spec['entries'] if e['name']=='r26-b-552-a-flatten'));full['control']=True
    for k in ['comparison_baseline','native_decode_reference','expected_equivalent_to']:full.pop(k,None)
    for e in spec['entries']:
        if e['name'].startswith('r26-b-552-a-flatten'):
            shadow=e['name'].endswith('-shadow');e.update(name=NAME+('-shadow' if shadow else ''),path='candidates/'+NAME,
                                                       hashes={f:sha((ROOT/'candidates'/NAME/f).read_bytes()) for f in ('parse.rs','Parse.lean')})
    spec['entries'].append(full)
    hashes=next(e['hashes'] for e in spec['entries'] if e['name']==NAME);assert native['source_hashes'][NAME]==dp['source_hashes']==hashes
    names=[e['name'] for e in spec['entries']]
    spec.update(snapshot_pages=paths[2].relative_to(ROOT).as_posix(),extract_candidates=[NAME],screen_orders=[names,names[::-1]],
                description='B37 final controlled owner-store deletion: original11rep fullencoder two reversedblocks, original552/noowner same-source shadows and actualfullowner auxiliary. Native28tokens/output/full1376costch checked, exact extraction beforetime. Real36Mcached owner reads and base scratch/roundmask costs retained; no newdirection/fullproof/stable share.')
    deps=['scripts/r26-b-a-no-owner-pair-plan.py','scripts/r26-b-preflight-draft.py','evidence/round26/route-b/b37-no-owner-pair-predeclared.md']+[p.relative_to(ROOT).as_posix() for p in paths]
    spec['r26_required_files']={p:sha((ROOT/p).read_bytes()) for p in deps}
    out=ROOT/'evidence/round26/route-b/b37-a-no-owner-screen.json';assert not out.exists();out.write_text(json.dumps(spec,indent=2)+'\n')
    print(json.dumps({'draft':out.relative_to(ROOT).as_posix(),'hashes':hashes,'entries':len(names),'blocks':2}))


if __name__=='__main__':main()
