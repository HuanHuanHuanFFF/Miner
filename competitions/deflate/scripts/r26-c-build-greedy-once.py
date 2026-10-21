"""C4: remove O_A lookahead and discover only the first source word, then verify/extend once."""
from pathlib import Path
import hashlib, importlib, json
ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'references/round26-public-658'
OUT=ROOT/'evidence/round26/extension1h/route-c'
NAME='r26-c-658-greedy-once'
P=importlib.import_module('r26-c-build-deferred-extension')
HELP=importlib.import_module('r26-a-rep-shadow')
RUST=P.RUST; LEAN=P.LEAN
EMITTER=P.EMITTER.replace('c3_emit_step','c4_emit_step').replace('C3:','C4:').replace('l==64','l>=3').replace('cap>=64','cap>=l').replace('full>=64','full>=l')
def sha(b):return hashlib.sha256(b).hexdigest()
def dump(p,x):p.write_bytes((json.dumps(x,indent=2,ensure_ascii=False)+'\n').encode())
def source():
    raw=(BASE/'parse.rs').read_bytes();assert sha(raw)==RUST
    text=HELP.edit_fn(raw.decode(),'o_a_eval(',lambda s:HELP.once(s,'o_a_fast_len(input, c.wrapping_sub(1), p, cap)','8'))
    def find(s):return s[:s.index('{')+1]+'\n    o_a_scan::<ACC_>(input, head, pos).0\n}'
    text=HELP.edit_fn(text,'o_a_find<',find)
    text=HELP.edit_fn(text,'o_a_run_greedy<',lambda s:HELP.once(s,'o_a_emit_step(input, out, pos, d, l, 1, ntok)','c4_emit_step(input, out, pos, d, l, 1, ntok)'))
    return(text+EMITTER).encode()
def main():
    p=ROOT/'candidates'/NAME;assert not p.exists();p.mkdir()
    raw=source();lean=(BASE/'Parse.lean').read_bytes();assert sha(lean)==LEAN
    (p/'parse.rs').write_bytes(raw);(p/'Parse.lean').write_bytes(lean)
    hashes={'parse.rs':sha(raw),'Parse.lean':sha(lean)}
    dump(p/'manifest.json',{'candidate':NAME,'parent':'references/round26-public-658','hashes':hashes,
      'attribution':{'source_receipt':'references/round26-public-658/source-receipt.json','author_hotkey':'5G3YLL7PuDhRBoVoDBYKhAfTxFM4EouSDiYuFXeeWciNRzyK'},
      'mechanism':'Remove the entire O_A lazy selection stage: find returns originalscan result directly. Baseeval checks only originalfirstsourceword, with hintlength<=8. Localtrusted emitter validates distance/range and computes exact fullmatch using originalmatch_len once under originalmin258,n-pos-8 cap before emission.',
      'difference':'C3 preservedlazy and removed only rarelongsuffixes. C4 changes the parse strategy to greedy and pays realqualityloss while removing allbase extension and lazy eval2/eval3 work. Not a cap sweep, no same-token assumption. PC,N70,sharedoriginalemitter,replay,hashes,recordpolicy and routes remain original.',
      'proof_status':'DRAFT_PARENT_SCAFFOLD. Needc4_emit_step_spec from existingEO.EA.match_len_spec/emit_match andgreedy localstep replacement. Find/eval retainTruepostconditions; no cross-finder MatchAtstate or untrusted-search correctness proof. Actualextract/fullgate NOT_RUN.',
      'quality_performance':'UNKNOWN untiloriginalencoder andoriginalprotocol. PublicO_Aparser priorstageweight about1.55% oftotalaxis is a historical localparser scenario, not a whole-program upperbound because changedtokens affectencoder. Usequality andscenario geometry toallocateone actualtime experiment.',
      'formal_submission_sent':False})
    e={'name':NAME,'path':p.relative_to(ROOT).as_posix(),'control':False,'anchor':'public658','comparison_baseline':'public658','native_decode_reference':'public658','hashes':hashes}
    dump(OUT/'c4-entry.json',e);print(json.dumps(e,indent=2))
if __name__=='__main__':main()
