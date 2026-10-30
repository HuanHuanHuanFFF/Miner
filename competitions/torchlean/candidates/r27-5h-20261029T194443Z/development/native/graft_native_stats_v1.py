"""Owned exact-source reconstruction recipe, no upstream source publication.

Keep source12's strong dense/RMS/output paths, replace only layernorm moment to
sqrt preparation with source27's proved native128 path. Both exact sources are
official retired public submissions; publication/license remains local-only.
"""
from pathlib import Path
from urllib.request import Request, urlopen
import argparse
import hashlib
import importlib.util
import json
import re
import sys

sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/"AGENTS.md").is_file())
ROUND=HERE.parent.parent
PINS={12:"e2c1f1f1ba52e32563fb193ceea7e2a271b989fd3ba2eb16cff747987879b521",
      27:"f92ee2c9a29de78dc434ad158b7141c0e4b5a67a5a198a353d59a4703481aa67"}

def sha(data):
    return hashlib.sha256(data).hexdigest()

def fetch(submission,explicit=None):
    path=Path(explicit) if explicit else ROUND/f"competition-state/source-private/submission{submission}-Kernel.lean"
    if path.is_file():
        data=path.read_bytes()
    else:
        url=f"https://conjectures.io/v1/competitions/torchlean/submissions/{submission}/source"
        with urlopen(Request(url,headers={"Accept":"text/plain"}),timeout=45) as r:
            data=r.read()
    assert sha(data)==PINS[submission],f"Exact{submission}source mismatch"
    return data

DECL=re.compile(r"^(?:@\[[^\n]*\] )?(?:(?:noncomputable|private) )?(?:def|lemma|theorem) ([^\s(:]+)",re.M)

def transform(source12,source27,compact=False):
    assert sha(source12)==PINS[12] and sha(source27)==PINS[27]
    base=source12.decode("utf-8")
    donor=source27.decode("utf-8")
    start=donor.index("def Y2L (")
    stop=donor.index("section\ndef MYa7b",start)
    graft=donor[start:stop]
    original_start=base.index("@[inline] def Y8f (x:Array Word)")
    original_stop=base.index("section\n@[inline] def MYa7",original_start)
    replaced_text=base[original_start:original_stop]
    original_names=set(DECL.findall(base))
    graft_names=set(DECL.findall(graft))
    expected_replaced={"Y8f","Y8f_eq"}
    collisions=original_names & graft_names
    assert collisions==expected_replaced,sorted(collisions)
    # Prove alias compatibility before relying on the original lexical context.
    aliases=re.findall(r"([\w.]+)->([\w]+)",base.split("\nstructure Acc",1)[0])
    donor_aliases=dict((alias,name) for name,alias in re.findall(r"([\w.]+)->([\w]+)",donor.split("\nstructure Acc",1)[0]))
    own_aliases=dict((alias,name) for name,alias in aliases)
    conflict={k:(own_aliases.get(k),v) for k,v in donor_aliases.items() if k in own_aliases and own_aliases[k]!=v and re.search(r"(?<!\w)"+re.escape(k)+r"(?!\w)",graft)}
    assert not conflict,conflict
    name_map={}
    alias_compactions={}
    lexical_compactions={}
    if compact:
        # Rename only fresh donor declarations; no logic/proof term is removed.
        forbidden=set(re.findall(r"[\w']+",base+graft))
        for i,name in enumerate(sorted(graft_names-expected_replaced)):
            if len(name)>4:
                new=next(prefix+str(i) for prefix in "rjqzvkumtsabcefgdhlpnwxy" if prefix+str(i) not in forbidden)
                forbidden.add(new)
                name_map[name]=new
        for name,new in sorted(name_map.items(),key=lambda p:-len(p[0])):
            graft=re.sub(r"(?<!\w)"+re.escape(name)+r"(?!\w)",new,graft)
        prefix=base.split("\nstructure Acc",1)[0]
        for block in re.finditer(r"\bopen ([\w.]+) renaming (.*?)(?= open | local |$)",prefix):
            namespace,renamings=block.groups()
            for old,alias in re.findall(r"([\w.']+)->([\w]+)",renamings):
                qualified=namespace+"."+old
                if qualified in graft:
                    alias_compactions[qualified]=alias
        for qualified,alias in sorted(alias_compactions.items(),key=lambda p:-len(p[0])):
            graft=re.sub(r"(?<!\w)"+re.escape(qualified)+r"(?!\w)",alias,graft)
        word_casts=0
        typed_lines=[]
        for line in graft.splitlines():
            if "ϥ" in line and line.endswith(".toUInt64"):
                line=line[:-len(".toUInt64")]+"܅"
                word_casts+=1
            typed_lines.append(line)
        assert word_casts==1,word_casts
        graft="\n".join(typed_lines)+"\n"
        lexical_compactions["field_Word_toUInt64"]=word_casts
        for field,notation in [("toUInt64","߸"),("toUInt32","՜"),("toNat","پ")]:
            graft,count=re.subn(r"(?<=[\w)\]!])\."+field+r"(?![A-Za-z0-9_'])",notation,graft)
            lexical_compactions["field_"+field]=count
        for typename,notation in [("UInt64","ػ"),("UInt32","ؼ"),("Nat","ٳ"),("Int","ٴ"),("Bool","ف"),("Word","δ"),("Array","ؽ")]:
            graft,count=re.subn(r"(?<![\w.])"+typename+r"(?![\w.])",notation,graft)
            lexical_compactions["type_"+typename]=count
        # Preserve all line indentation. Remove intra-line spaces adjoining
        # punctuation, as already used throughout both official compact sources.
        lines=[]
        for line in graft.splitlines():
            indent=line[:len(line)-len(line.lstrip(" "))]
            body=line[len(indent):].rstrip()
            body=re.sub(r"[ \t]+"," ",body)
            body=re.sub(r"\s*([,:;])\s*",r"\1",body)
            body=re.sub(r"\s*([\[\]{}()])\s*",r"\1",body)
            lines.append(indent+body)
        graft="\n".join(lines)+"\n"
    result=(base[:original_start]+graft+base[original_stop:]).encode("utf-8")
    report={"source12_sha256":sha(source12),"source27_sha256":sha(source27),
            "source27_graft_start":"def Y2L", "source27_graft_stop":"section before def MYa7b",
            "source12_replaced":"Y8f plus Y8f_eq only", "graft_bytes":len(graft.encode("utf-8")),
            "removed_bytes":len(replaced_text.encode("utf-8")),"fresh_declarations":len(graft_names-expected_replaced),
            "collision_check":sorted(collisions),"shared_alias_conflicts":conflict,"renames":name_map,
            "existing_alias_compactions":alias_compactions,
            "existing_notation_compactions":lexical_compactions,
            "candidate_sha256":sha(result),"candidate_bytes":len(result),"compact":compact,
            "status":"WHOLE_ORIGINAL12_CORRECT_ENTRY_PRESENT_NOT_COMPILED",
            "source_publication":"Whole upstream sources and reconstructed output LOCAL_OR_EPHEMERAL_ONLY"}
    return result,report

def main():
    p=argparse.ArgumentParser()
    p.add_argument("--source12",type=Path)
    p.add_argument("--source27",type=Path)
    p.add_argument("--compact",action="store_true")
    p.add_argument("--output",type=Path)
    p.add_argument("--receipt",type=Path)
    a=p.parse_args()
    result,report=transform(fetch(12,a.source12),fetch(27,a.source27),a.compact)
    spec=importlib.util.spec_from_file_location("r27_patch_public",HERE/"patch_public.py")
    mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
    report["policy"]=mod.policy_check(result)
    if a.output:
        a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    if a.receipt:
        a.receipt.write_text(json.dumps(report,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps(report,indent=2,ensure_ascii=False))

if __name__=="__main__":
    main()
