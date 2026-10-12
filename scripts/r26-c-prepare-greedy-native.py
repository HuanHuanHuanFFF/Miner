"""Freeze C4 discovery and record C3 native stop; no mutation of prior specs."""
from pathlib import Path
import ast, hashlib, importlib, json
ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'evidence/round26/extension1h/route-c'
def sha(b):return hashlib.sha256(b).hexdigest()
def dump(p,x):p.write_bytes((json.dumps(x,indent=2,ensure_ascii=False)+'\n').encode())
def main():
    folder=ROOT/'evidence/round26/38247257224/quality-c3-native/diagnostics'
    rp=folder/'r26-c-deferred/receipt.json';dp=folder/'r12-decode/decode.json';r=json.loads(rp.read_bytes());d=json.loads(dp.read_bytes())
    assert r['status']=='VERIFIED_C3_ORIGINAL_TRAJECTORY_AND_NATIVE_OUTPUTS'
    assert d['cases'][0]['cases']==444 and d['cases'][0]['decode_or_panic_failures']==0 and d['cases'][0]['token_changes']==[]
    assert all(x['candidate_same_tokens']and x['candidate_same_output']for x in r['rows'])
    dump(OUT/'c3-feedback.json',{'status':'VERIFIED_C3_NATIVE_STOP_NO_TIMING_CLAIM','run_id':r['run_id'],'git_sha':r['git_sha'],'receipts':{str(p.relative_to(ROOT)):sha(p.read_bytes())for p in [rp,dp]},'totals':r['totals'],
         'rows':[x for x in r['rows']if x['counts']['base_fast_calls']],
         'decision':'STOP exact C3: observed 5784 source word pairs removed, 684 long64 events out of 75920 base fast calls. Rare long-suffix scope did not justify timing or full gate. Native 28 tokens/outputs same and 444 decode zero changes are correctness-limited evidence, not speed.',
         'performance':'NOT_MEASURED','full_gate':'NOT_RUN'})
    s=json.loads((OUT/'c3-native-draft.json').read_bytes());e=json.loads((OUT/'c4-entry.json').read_bytes())
    s['entries']=[x for x in s['entries']if x['control']]+[e];s.pop('r26_c_deferred_counts');s['r26_c_greedy_counts']=True
    names=[x['name']for x in s['entries']];s['screen_orders']=[names,list(reversed(names))]
    s['description']='C4 one wholeOAlookahead removal: first8sourceworddiscovery thenoriginaltrusted fullmatch extensionatlocalemitter. Real28encoderquality and444decode withchanges; originaltrajectorybase/lazycallsandwordpair oracle. Actualquality-speedtradeoff, nosametoken promise, no timing/fullgate.'
    paths=['scripts/r26-c-build-greedy-once.py','scripts/r26-c-greedy-counts.py','scripts/r26-c-prepare-greedy-native.py','scripts/r26-c-build-deferred-extension.py','scripts/r26-c-deferred-counts.py','scripts/r26-a-rep-shadow.py','scripts/research-round25-len3-price.py','scripts/research-round4.py','scripts/research-round12-decode.py','scripts/research-round13-encoder-native.py','scripts/research-round13-native.py','scripts/round26-preflight.py','evidence/round26/extension1h/route-c/c4-predeclaration.md','references/round26-public-658/source-receipt.json','candidates/r26-c-658-greedy-once/manifest.json',s['snapshot_pages']]
    for x in s['entries']:paths += [x['path']+'/'+f for f in ['parse.rs','Parse.lean']]
    s['r26_required_files']={p:sha((ROOT/p).read_bytes())for p in paths};dump(OUT/'c4-native-draft.json',s)
    for p in ROOT.glob('scripts/r26-c-*.py'):ast.parse(p.read_text(encoding='utf-8'),filename=str(p))
    checked=importlib.import_module('r26-c-greedy-counts').preflight(s);h,pairs=importlib.import_module('research-round12-decode').harness(s)
    checked.update(python_ast='PASS',decode_harness_constructed=True,decode_harness_sha256=sha(h.encode()),native='NOT_RUN',full_gate='NOT_RUN');dump(OUT/'c4-local-preflight.json',checked);print(json.dumps(checked,indent=2))
if __name__=='__main__':main()
