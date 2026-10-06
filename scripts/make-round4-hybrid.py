"""Compose original public299 with frozen H cores using general input features.

Only writes candidates/r4-hybrid-h16-small299/. Engine declarations and
constants are copied exactly, except public299 parse is renamed s_parse and
the H-only parse wrapper is removed. No toolchain or CI execution.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path

ROOT=Path(__file__).resolve().parents[1]
NAME="r4-hybrid-h16-small299"
NAME_C="r4-hybrid-h16-smallc299"
NAME_R="r4-hybrid-h3r-smallc299"
S=ROOT/"references/round4-public-299"
H=ROOT/"candidates/r4-parse-h16d64-core"
H3=ROOT/"candidates/r4-parse-hmode-3-i8"
S_HASH={"parse.rs":"71314c4da7ccd29331a360bce9be8697857109c66adc87d3480eeaa22930625d",
        "Parse.lean":"9b77b3523cbf7044aaffa11b6fd9676b3615ca4bf148b43b3cb92da4073b3e3d"}
H_HASH={"parse.rs":"ba3c16422a5fc9432c41d80c0ad0ab5657605c1e020d14b7e1135e430ce3a7ee",
        "Parse.lean":"13f23fc46a6d18283aeb339f949cca102761133d6e1ff9b3a1007cd8b7926a46"}
H3_HASH={"parse.rs":"1c94d7dec959a9862fa79dd862df673abec80556d2f139924094e0a6a78ed840",
         "Parse.lean":"edab13f3296ddd86cb2db928baa1050f5fdb532fc0facc671a4236478995b34e"}
ENTRY='''pub fn parse(input: &[u8], out: &mut [u32]) -> usize {
    if input.len() < 65536 {
        s_parse(input, out)
    } else {
        h_parse_mode(input, out, 0)
    }
}'''
ENTRY_PROOF='''namespace Submission
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000

attribute [local step] s_parse_spec EH.parse_mode_spec

theorem parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.parse input out ⦃ fun r =>
      r.1.val ≤ input.length ∧
      r.2.length = out.length ∧
      LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.parse]
  step*

end Submission
'''
ENTRY_C='''pub fn parse(input: &[u8], out: &mut [u32]) -> usize {
    if input.len() < 65536 {
        return s_parse(input, out);
    }
    let c = classify(input);
    if c >= 1 && c <= 3 {
        s_parse(input, out)
    } else {
        h_parse_mode(input, out, 0)
    }
}'''
ENTRY_C_PROOF=ENTRY_PROOF.replace(
    'attribute [local step] s_parse_spec EH.parse_mode_spec',
    'attribute [local step] s_parse_spec EH.parse_mode_spec classify_spec')
ENTRY_RC=ENTRY_C.replace('h_parse_mode(input, out, 0)','h_parse_mode(input, out, 3)')


def sha(data:bytes)->str:return hashlib.sha256(data).hexdigest()


def mask(source:str)->str:
    return re.sub(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"',
        lambda m:''.join('\n' if c=='\n' else ' ' for c in m[0]),source,flags=re.S)


def declarations(source:str)->tuple[dict,dict,dict]:
    plain=mask(source);fs={};cs={};types={}
    for m in re.finditer(r'(?m)^(?:#\[[^\n]*\]\s*\n)*pub fn (\w+)\b[^{}]*\{',plain):
        pos=m.end();depth=1
        while depth:
            depth+=(plain[pos]=='{')-(plain[pos]=='}');pos+=1
        fs[m[1]]={'start':m.start(),'end':pos,'text':source[m.start():pos],'body':plain[m.end():pos-1]}
    assert len(fs)==len(re.findall(r'\bfn\s+\w+\s*[<(]',plain))
    for m in re.finditer(r'(?m)^pub const (\w+)\s*:',plain):
        eq=plain.index('=',m.end());end=plain.index(';',eq)+1;cs[m[1]]=source[m.start():end]
    for m in re.finditer(r'(?m)^pub (?:struct|enum) (\w+)\b[^{}]*\{',plain):
        pos=m.end();depth=1
        while depth:
            depth+=(plain[pos]=='{')-(plain[pos]=='}');pos+=1
        types[m[1]]=source[m.start():pos]
    return fs,cs,types


def once(text:str,old:str,new:str)->str:
    assert text.count(old)==1,(old,text.count(old));return text.replace(old,new,1)


def generate(name:str, entry:str, entry_proof:str, check:bool)->None:
    h_path=H3 if name==NAME_R else H
    h_hash=H3_HASH if name==NAME_R else H_HASH
    h_key='hmode3_core' if name==NAME_R else 'h16d64_core'
    mode=3 if name==NAME_R else 0
    sb={n:(S/n).read_bytes()for n in S_HASH};hb={n:(h_path/n).read_bytes()for n in h_hash}
    for data,expected in ((sb,S_HASH),(hb,h_hash)):
        for n,h in expected.items():assert sha(data[n])==h,(n,h)
    sr,hr=sb['parse.rs'].decode(),hb['parse.rs'].decode()
    sp,hp=sb['Parse.lean'].decode(),hb['Parse.lean'].decode()
    assert '\r\n' not in sr+hr+sp+hp
    sf,sc,st=declarations(sr);hf,hc,ht=declarations(hr)
    assert sf.keys()&hf.keys()=={'parse'},sf.keys()&hf.keys()
    assert not sc.keys()&hc.keys() and not st.keys()&ht.keys()
    assert 's_parse' not in sf and 's_parse' not in hf
    sr2=once(sr,'pub fn parse(input: &[u8], out: &mut [u32]) -> usize {','pub fn s_parse(input: &[u8], out: &mut [u32]) -> usize {')
    hr2=hr[:hf['parse']['start']]+hr[hf['parse']['end']:]
    # Inner doc comments from the second crate cannot occur after declarations.
    # Only these top-level comment markers change; engine declarations do not.
    sr2=re.sub(r'(?m)^//!', '//',sr2);hr2=re.sub(r'(?m)^//!','//',hr2)
    rust=sr2+'\n\n'+hr2+'\n\n'+entry+'\n'
    cf,cc,ct=declarations(rust)
    for n,d in sf.items():
        target='s_parse' if n=='parse' else n
        expected=d['text'].replace('pub fn parse(','pub fn s_parse(',1) if n=='parse' else d['text']
        assert cf[target]['text']==expected,('S declaration changed',n)
    for n,d in hf.items():
        if n!='parse':assert cf[n]['text']==d['text'],('H declaration changed',n)
    for n,v in {**sc,**hc}.items():assert cc[n]==v,('constant changed',n)
    for n,v in {**st,**ht}.items():assert ct[n]==v,('type changed',n)
    assert cf['parse']['text']==entry
    assert len(cf)==len(sf)+len(hf)
    # Close the original S scope before reopening the original H scope, so
    # local step/scalar rules from S cannot affect EH elaboration.
    sp2=once(sp,'theorem parse_spec (input : Slice Std.U8)','theorem s_parse_spec (input : Slice Std.U8)')
    sp2,count=re.subn(r'\bslot\.parse\b','slot.s_parse',sp2);assert count==2
    hp2=once(hp,'import Lz77\nimport Slot\n','')
    ep=hp2.rindex('theorem parse_spec (input : Slice Std.U8)')
    ee=hp2.index('\nend Submission',ep)
    removed_h_entry=hp2[ep:ee]
    hp2=hp2[:ep]+hp2[ee:]
    lean=sp2+'\n'+hp2+'\n'+entry_proof
    assert lean.count('import Lz77')==lean.count('import Slot')==1
    assert len(re.findall(r'^theorem parse_spec\b',lean,re.M))==1
    assert len(re.findall(r'^theorem s_parse_spec\b',lean,re.M))==1
    assert len(re.findall(r'^namespace Submission$',lean,re.M))==3
    assert len(re.findall(r'^end Submission$',lean,re.M))==3
    assert not re.search(r'(?m)^\s*(?:axiom\b|sorry\b|admit\b)',lean)
    files={'parse.rs':rust.encode(),'Parse.lean':lean.encode()}
    assert all(len(v)<524288 for v in files.values())
    audit={'sources':{'public299':S_HASH,h_key:h_hash},
        'routing':('One generic power-of-two cutoff: n < 65536 -> unmodified public299 engine portfolio, otherwise H mode 0. No filename, hash, exact-size identity or new content classifier.' if name==NAME else
            f'n < 65536 or original public299 classify(input) in 1..3 -> unmodified public299 portfolio; otherwise H mode {mode}. Classes 1..3 are existing general DNA/zero-rich/high-byte-binary features mapped to the C engine. No filename, hash or exact-size identity.'),
        'rust':{'name_conflicts':['parse'],'public299_functions':sorted(sf),'H_functions':sorted(hf),
            'all_other_function_and_constant_declarations':'VERIFIED exact source text preserved',
            'renamed_function':'public299 parse -> s_parse','removed_function':'H-only parse wrapper',
            'new_entry':entry,'custom_types_preserved':sorted(ct),'total_functions':len(cf),
            'doc_comment_handling':'Only top-level //! markers converted to // before concatenation'},
        'proof':{'public299_changes':'Only parse_spec -> s_parse_spec and its two slot.parse references -> slot.s_parse',
            'H_changes':'Remove imports already at file top and final uniform parse_spec; preserve complete EH and T9/T10',
            'removed_H_entry_sha256':sha(removed_h_entry.encode()),
            'new_entry_proof':entry_proof,'local_rule_isolation':('Three separately closed/reopened Submission scopes; only two complete engine specs registered locally in the new final scope' if name==NAME else
                'Three separately closed/reopened Submission scopes; the two complete engine specs and original classify_spec are registered locally only in the final scope')},
        'status':'Static composition audit only; official re-extraction, names, typecheck, axiom whitelist, gate runtime and public/private behavior remain UNKNOWN.'}
    manifest={'candidate':name,'parents':{'public299':{'path':S.relative_to(ROOT).as_posix(),'hashes':S_HASH},
            h_key:{'path':h_path.relative_to(ROOT).as_posix(),'hashes':h_hash}},
        'hashes':{n:sha(v)for n,v in files.items()},'bytes':{n:len(v)for n,v in files.items()},
        'route_threshold':{'operator':'<','bytes':65536},'dependency_audit':'composition-audit.json',
        'attribution':'External public submissions 299 and 402; original source/provenance retained in references/round4-public-299 and references/round4-public-402.',
        'proof_scope':'Compose the full existing S and H correctness specs for a generic size split; no weakened obligation, added axiom, sorry or verifier change.',
        'performance_scope':'Public size estimate from parent measurements is a hypothesis; new compiler layout and extra engine code may affect time. Cross-family/private transfer, online admission and payment UNKNOWN.',
        'verification':'VERIFIED SHA locks, conflict checks, exact declaration preservation and generation only. New Rust build, extraction, proof/axiom checks, <=900s elaboration, round trip and paired performance UNKNOWN.'}
    if name in (NAME_C,NAME_R):
        manifest['content_override']={'classifier':'original public299 classify','inclusive_classes':[1,3],
            'class_1':'sample nucleotide/newline share >=950 per mille',
            'class_2':'sample zero share >=500 per mille',
            'class_3':'sample zero/control share >=20 and high-byte share >=350 per mille',
            'reused_config_engine':'C through original CLASS_CFG/CFG'}
    files['composition-audit.json']=(json.dumps(audit,indent=2)+'\n').encode()
    files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode()
    dest=ROOT/'candidates'/name
    if check:
        for n,v in files.items():assert (dest/n).read_bytes()==v,(name,n)
    else:
        dest.mkdir(parents=True,exist_ok=True)
        for n,v in files.items():(dest/n).write_bytes(v)
    print(json.dumps({'candidate':name,'hashes':manifest['hashes'],'bytes':manifest['bytes'],'functions':len(cf)}))


def main()->None:
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check',action='store_true')
    ap.add_argument('--only',action='append',choices=[NAME,NAME_C,NAME_R],default=[])
    args=ap.parse_args()
    for name in args.only or [NAME,NAME_C,NAME_R]:
        entry=ENTRY if name==NAME else ENTRY_RC if name==NAME_R else ENTRY_C
        generate(name,entry,ENTRY_PROOF if name==NAME else ENTRY_C_PROOF,args.check)


if __name__=='__main__':main()
