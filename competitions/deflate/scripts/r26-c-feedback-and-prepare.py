"""Close C2 on native evidence, freeze the single C3 discovery batch."""
from pathlib import Path
import ast, hashlib, importlib, json, statistics
ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'evidence/round26/extension1h/route-c'
def sha(b):return hashlib.sha256(b).hexdigest()
def dump(p,x):p.write_bytes((json.dumps(x,indent=2,ensure_ascii=False)+'\n').encode())
def main():
    cp=ROOT/'evidence/round26/38246156539/quality-c2-native/diagnostics/r26-c-fold-tail/receipt.json'
    c=json.loads(cp.read_bytes());assert c['status']=='VERIFIED_28_ORIGINAL_TRAJECTORY_AND_CANDIDATE_TOKENS_ENCODER_DECODE'
    t=c['totals'];assert t['same_distance_calls']==0
    feedback={'status':'VERIFIED_C2_NATIVE_STOP_NO_PERFORMANCE_CLAIM','run_id':c['run_id'],'git_sha':c['git_sha'],'receipt':cp.relative_to(ROOT).as_posix(),'receipt_sha256':sha(cp.read_bytes()),'candidate_hashes':c['preflight']['candidate_hashes'],'totals':t,
      'tail_reject_rate':t['tail_reject_calls']/t['original_same_calls'],'average_original_word_pairs_per_reject':t['tail_reject_original_word_pairs']/t['tail_reject_calls'],
      'removed_word_pairs_to_new_byte_pairs_ratio':t['tail_reject_original_word_pairs']/t['original_same_calls'],
      'decision':'STOP exact C2 before timing. Rejected scans averaged only1.014 originalwordpair; addedtailcheck on every256144 eligiblecall. Satisfies declared thin-work stoppingcondition, not measured slower.',
      'c1':'Observed0same-distance fold calls supports the prior maximal-prefix exclusion on this28-file trajectory. No universal proof claimed.',
      'verified':'444finite equality and28token/encoder/decode identity; no time or fullgate.'}
    dump(OUT/'c2-feedback.json',feedback)
    entry=json.loads((OUT/'c3-entry.json').read_bytes());s=json.loads((OUT/'c2-native-draft.json').read_bytes())
    s['entries']=[e for e in s['entries']if e['control']]+[entry]
    s.pop('r26_c_fold_tail_counts');s['r26_c_deferred_counts']=True;s['r26_finite_equivalence']=False;s['r26_native_decode']=True
    names=[e['name']for e in s['entries']];s['screen_orders']=[names,list(reversed(names))]
    s['description']='C3 one OA-base deferred longextension: discover only through64, finish originalcap at trustedemit with originalmatch_len; short/lazy/N/replay unchanged. Original444decode with changes logged;28originalencoder and originaltrajectory savedread oracle. No timing or fullgate, parentLean scaffold only.'
    paths=['scripts/r26-c-build-deferred-extension.py','scripts/r26-c-deferred-counts.py','scripts/r26-c-feedback-and-prepare.py','scripts/r26-a-rep-shadow.py','scripts/research-round25-len3-price.py','scripts/research-round4.py','scripts/research-round12-decode.py','scripts/research-round13-encoder-native.py','scripts/research-round13-native.py','scripts/round26-preflight.py','evidence/round26/extension1h/route-c/c3-predeclaration.md','references/round26-public-658/source-receipt.json','candidates/r26-c-658-deferred-extension/manifest.json',s['snapshot_pages']]
    for e in s['entries']:paths += [e['path']+'/'+f for f in ['parse.rs','Parse.lean']]
    s['r26_required_files']={p:sha((ROOT/p).read_bytes())for p in paths}
    dump(OUT/'c3-native-draft.json',s)
    for p in ROOT.glob('scripts/r26-c-*.py'):ast.parse(p.read_text(encoding='utf-8'),filename=str(p))
    checked=importlib.import_module('r26-c-deferred-counts').preflight(s)
    h,pairs=importlib.import_module('research-round12-decode').harness(s)
    checked.update(python_ast='PASS',decode_harness_constructed=True,decode_harness_sha256=sha(h.encode()),native='NOT_RUN',full_gate='NOT_RUN')
    dump(OUT/'c3-local-preflight.json',checked);print(json.dumps(checked,indent=2))
if __name__=='__main__':main()
