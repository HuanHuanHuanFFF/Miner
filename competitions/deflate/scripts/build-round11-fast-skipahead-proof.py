"""Freeze the skipahead proof bridge after auditing the actual fast-j extraction.

No local Lean execution: the exact new pair still needs the original full gate.
"""
from pathlib import Path
import argparse, hashlib, json, re

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'candidates/r11-fast-skipahead'
DEST=ROOT/'candidates/r11-fast-skipahead-proof'
EXTRACT=ROOT/'evidence/round11/37734806965/fast-j/extraction'


def sha(b):return hashlib.sha256(b).hexdigest()


def definition(text,name):
    m=re.search(r'^def '+re.escape(name)+r'(?=\s)(.*?)(?=\n/--|\Z)',text,re.M|re.S)
    assert m,name
    return m.group(0)


def generate():
    rust=(BASE/'parse.rs').read_bytes();lean=(BASE/'Parse.lean').read_bytes()
    assert sha(rust)=='3e68ad368a56115111fc0f61038dcaa3658e2b31dee40db24916445b49add08e'
    assert sha(lean)=='672a5c17aabdc647e13ee0c73a4535f73dc3c242785bf7fb5d07e44cefda687f'
    research=json.loads((EXTRACT/'research.json').read_text());ext=research['extractions'][BASE.name]
    assert ext['extraction_accepted'] and ext['source_sha256']==sha(rust)
    for n,meta in ext['files'].items():assert sha((EXTRACT/BASE.name/n).read_bytes())==meta['sha256']
    funs=(EXTRACT/BASE.name/'Funs.lean').read_text()
    expected={
        'r11_next':'p miss skip skcap lim lazy',
        'r11_record_slot':'H s ins lim forecast slot lazy km',
        'run1_loop0_loop0':'input lazy km p head lim pre_slot pre_c pre_w l d ins go',
        'run1_loop0':'input out skip lazy skcap km nt ls p head lim miss fuel pre_slot pre_c pre_w',
        'run1':'H input out skip lazy skcap km',
    }
    audit={}
    for name,wanted in expected.items():
        d=definition(funs,name);signature=d.split(':= do',1)[0]
        args=' '.join(re.findall(r'\(([^():]+) : ',signature));assert args==wanted,(name,args,wanted)
        audit[name]={'arguments':args,'definition_sha256':sha(d.encode())}
    body=definition(funs,'run1_loop0.body')
    calls=['head_set head pre_slot p','r11_next p miss skip skcap lim lazy','ahead_if_m input head1 forecast lim pre_slot pre_c pre_w km','probe_m input pre_c pre_w p km','r11_record_slot H input ins1 lim forecast pre_slot2 lazy km','record3_m input head2 ins1 record_slot «end» lim km']
    assert all(body.count(c)==1 for c in calls)
    assert [body.index(c)for c in calls]==sorted(body.index(c)for c in calls)
    assert 'ok (cont (out, nt, ls, forecast, head1, miss1, fuel1, pre_slot1,' in body
    loop=definition(funs,'run1_loop0')
    state='(out, nt, ls, p, head, miss, fuel, pre_slot, pre_c, pre_w)'
    assert loop.rstrip().endswith(state)
    original=lean.decode();proof=original
    old_comment='''/-! R11 source-level proof bridge draft. Actual new extraction and Lean gate
have NOT been run. The rule concerns bounds, not forecast/search equivalence. -/'''
    new_comment='''/-! R11 bridge checked against fast-j actual extraction (37734806965).
Lean compilation and the complete original gate remain NOT_RUN. These rules
prove bounds for correctness, not all-input token equivalence to fast3. -/'''
    assert proof.count(old_comment)==1;proof=proof.replace(old_comment,new_comment,1)
    a=proof.index('theorem main1_loop_spec {');b=proof.index('/-- The main loop of `run1`, ghost-free.',a)
    old_main=proof[a:b]
    old='all_goals try (obtain ⟨i4, i5, i6⟩ := ae; dsimp only at *; step*)'
    new='all_goals try (obtain ⟨r11_end_slot, r11_end_c, r11_end_w⟩ := ae; dsimp only at *; step*)'
    assert old_main.count(old)==1;new_main=old_main.replace(old,new,1)
    proof=proof[:a]+new_main+proof[b:]
    assert proof.replace(new_comment,old_comment,1).replace(new_main,old_main,1)==original
    files={'parse.rs':rust,'Parse.lean':proof.encode()}
    parent=json.loads((BASE/'manifest.json').read_text())
    manifest={**parent,'candidate':DEST.name,'parent':'candidates/r11-fast-skipahead','parent_hashes':parent['hashes'],'hashes':{n:sha(v)for n,v in files.items()},'proof_status':'ACTUAL_INTERFACE_AUDITED_UNCOMPILED; exact new pair requires original gate','proof_changes':'Keep two helper specs after exact argument/result audit; fresh local names for ae destructuring in main1_loop_spec. No invariant, measure, statement, emitter or axiom changed.','extraction_run':'37734806965','extracted_files':ext['files']}
    receipt={'status':'SOURCE_AND_ACTUAL_INTERFACE_REVIEW_ONLY','run_id':research['run_id'],'git_sha':research['git_sha'],'files':manifest['hashes'],'interfaces':audit,'actual_main_call_order':calls,'main_loop_state':['out','nt','ls','p','head','miss','fuel','pre_slot','pre_c','pre_w'],'measure':'Original fuel projection unchanged','preserved_main_invariant':'Dec at ls, ls<=p, HeadBound head p, miss<=p, valid pre_slot, pre_c<=p, pre_w=word8 pre_c','helper_bridge':['r11_next postcondition p<forecast<=lim supplies ahead_if hBi and keeps miss+1<=forecast','ahead_if uses HeadBound head1 at old p, so pre_c<=old p even when forecast skips farther; no p+1 cache assumption is imported','r11_record_slot only needs H>0, old slot<H and lim+8=input length; ins<lim in its active branch proves be4 arithmetic safe','Lazy loop state stays unchanged; lazy0 body uses forecast as its next p; lazy>0 retains original miss reload'], 'changed_tactic_sites':['main1_loop_spec ae destructuring names made fresh; actual Funs uses i3/i4/i5 where old extraction used i4/i5/i6'], 'remaining_unknown':['Lean compilation of two helper specs','step* inference of ahead_if_m ghost bound at forecast','main-loop branch closure and whole original obligation/axiom whitelist gate'],'formal_or_performance_claim':False}
    files['manifest.json']=(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n').encode()
    files['proof-audit.json']=(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n').encode()
    assert all(len(files[n])<=524288 for n in ('parse.rs','Parse.lean'))
    return files


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args();files=generate()
    if args.check:assert all((DEST/n).read_bytes()==b for n,b in files.items())
    else:
        DEST.mkdir(parents=True,exist_ok=True)
        for n,b in files.items():(DEST/n).write_bytes(b)
    print(json.dumps({'candidate':DEST.name,'status':'UNCOMPILED','hashes':{n:sha(b)for n,b in files.items()}},indent=2))


if __name__=='__main__':main()
