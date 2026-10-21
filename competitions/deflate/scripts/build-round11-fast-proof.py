"""Minimal continuation proof bridge bound to the real probe-a extraction.

This writes a separate pair and performs source/interface audits only. Lean
compilation and the original complete gate remain runner-only and UNKNOWN.
"""
from pathlib import Path
import argparse
import hashlib
import json
import re

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'candidates/r11-fast-continuation'
DEST=ROOT/'candidates/r11-fast-continuation-proof'
EXTRACT=ROOT/'evidence/round11/37722786008/probe-a/extraction'

BRIDGE=r'''/-! R11 continuation bridge, adapted to the actual probe-a Funs interface.
Only cached position/word facts are preserved here. The existing probe_m theorem
still supplies the real match. This source is not a claim of a successful gate. -/

@[local step]
theorem r11_continuation_spec (s : Slice Std.U8) (p lim span d a c : Std.Usize)
    (cw : Std.U64) (km : Std.U32) (hlim : lim.val + 8 = s.length)
    (hc : c.val ≤ p.val) (hcw : cw.val = word8 s c.val) :
    slot.r11_continuation s p lim span d a c cw km ⦃ fun r =>
      r.1.val = a.val ∧ r.2.1.val ≤ p.val ∧ r.2.2.val = word8 s r.2.1.val ⦄ := by
  rw [slot.r11_continuation]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  all_goals first
    | exact ⟨rfl, hc, hcw⟩
    | exact ⟨rfl, by scalar_tac, by assumption⟩
    | scalar_tac

'''


def sha(b):return hashlib.sha256(b).hexdigest()


def generate():
    source=(BASE/'parse.rs').read_bytes();proof=(BASE/'Parse.lean').read_bytes()
    parent=json.loads((BASE/'manifest.json').read_text())
    assert sha(source)==parent['hashes']['parse.rs']=='72129aa1e666d7d0faf51731b7ba6fd99922dc6b9149b5b1c6cf2067c7ee3c7a'
    assert sha(proof)==parent['hashes']['Parse.lean']=='e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04'
    research=json.loads((EXTRACT/'research.json').read_text())
    ext=research['extractions'][BASE.name]
    assert ext['extraction_accepted'] and ext['source_sha256']==sha(source)
    for name,meta in ext['files'].items():assert sha((EXTRACT/BASE.name/name).read_bytes())==meta['sha256']
    funs=(EXTRACT/BASE.name/'Funs.lean').read_text()
    wanted={
        'r11_continuation':'s p lim span d a c cw km',
        'run1_loop0_loop0':'input lazy km p head lim pre_slot pre_c pre_w l d ins go',
        'run1_loop0':'input out skip lazy skcap km nt ls p head lim miss fuel pre_slot pre_c pre_w',
        'run1':'H input out skip lazy skcap km',
    }
    interfaces={}
    for name,args in wanted.items():
        m=re.search(r'^def '+re.escape(name)+r'(?=\s)(.*?) := do',funs,re.M|re.S);assert m,name
        actual=' '.join(re.findall(r'\(([^():]+) : ',m.group(1)))
        assert actual==args,(name,actual,args)
        interfaces[name]={'args':actual,'signature_sha256':sha(m.group(0).encode())}
    call='r11_continuation input «end» lim i3 d1 i7 i8 i9 km'
    assert funs.count(call)==1
    body=re.search(r'^def run1_loop0\.body(?=\s)(.*?)(?=\n/--)',funs,re.M|re.S).group(0)
    assert body.index('ahead_fix_m input head3')<body.index(call)<body.index('ok (cont (out2')
    original=proof.decode();marker='/-- `probe` for keys under `km`: nothing, or a real match at `p`'
    assert original.count(marker)==1
    lean=original.replace(marker,BRIDGE+marker,1)
    assert lean.replace(BRIDGE,'',1)==original
    assert 'sorry' not in BRIDGE and 'axiom ' not in BRIDGE
    files={'parse.rs':source,'Parse.lean':lean.encode()}
    audit={
        'status':'ACTUAL_INTERFACE_CHECKED_LEAN_UNCOMPILED',
        'extraction_run':'37722786008','extraction_git_sha':research['git_sha'],
        'extraction':ext,'interfaces':interfaces,'actual_call':call,
        'new_theorems':['r11_continuation_spec'],
        'proof_diff':'One local step theorem before probe_m_spec. Parent proof bytes restored by removing the inserted bridge; no existing theorem/obligation/axiom changed.',
        'preconditions':['lim.val + 8 = input.length','old candidate c.val <= p.val','old cached cw.val = word8 input c.val'],
        'postconditions':['slot value unchanged','candidate <= p','cached word equals word8 at candidate'],
        'reuse':['be8_spec','ahead_fix_m_spec','probe_m_spec','MainInv1','main1_loop_spec'],
        'arithmetic':'p<lim makes p+8 safe; checked d<=p makes rc=p-d safe and rc+8<=input.length. Prefix/distance predicates only choose a cache entry.',
        'unverified':['Lean compilation of new theorem','Automatic consumption of new step rule in original main1_loop_spec','Fresh extraction during complete gate','Original obligation, allowed axioms and full public roundtrip for this exact pair'],
    }
    manifest={**parent,'candidate':DEST.name,'parent':str(BASE.relative_to(ROOT)).replace('\\','/'),
        'parent_hashes':parent['hashes'],'hashes':{n:sha(b)for n,b in files.items()},
        'proof_status':'ADAPTED_TO_REAL_EXTRACTION_UNCOMPILED; complete gate UNKNOWN',
        'proof_change':'Only r11_continuation_spec added to parent proof; no loop theorem, final original obligation or axiom altered.',
        'source_identity':'Exact frozen probe-a continuation Rust; no source changes.',
        'real_extraction':{'run':'37722786008','files':ext['files']}}
    files['manifest.json']=(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n').encode()
    files['proof-audit.json']=(json.dumps(audit,ensure_ascii=False,indent=2)+'\n').encode()
    return files


def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--check',action='store_true');args=ap.parse_args()
    files=generate()
    if args.check:assert all((DEST/n).read_bytes()==b for n,b in files.items())
    else:
        DEST.mkdir(parents=True,exist_ok=True)
        for name,data in files.items():(DEST/name).write_bytes(data)
    print(json.dumps({'candidate':DEST.name,'status':'UNCOMPILED','hashes':{n:sha(b)for n,b in files.items()}},indent=2))


if __name__=='__main__':main()
