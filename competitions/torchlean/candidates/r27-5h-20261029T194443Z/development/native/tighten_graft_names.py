"""Prepare byte headroom by alpha-renaming only fresh graft declarations.

Do not replace the in-flight frozen source. This is a future repair/composition
recipe; full Lean/gate/native revalidation is required for any resulting source.
"""
from pathlib import Path
import hashlib
import importlib.util
import itertools
import json
import re
import sys

sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent

def main():
    spec=importlib.util.spec_from_file_location("r27_tight_graft_origin",HERE/"graft_native_stats_v1.py")
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    source12=m.fetch(12);source27=m.fetch(27)
    raw,recipe=m.transform(source12,source27,compact=True)
    assert hashlib.sha256(raw).hexdigest()=="beca1b56d24ed64ed124fbeae50cb8be267fe3361336eab52b24f0c49720b0ed"
    raw=raw.replace(b"import ContractExact\n",b"import ContractExact\nset_option maxHeartbeats 1000000\n",1)
    text=raw.decode("utf-8");donor=source27.decode("utf-8")
    native=donor[donor.index("def Y2L ("):donor.index("section\ndef MYa7b",donor.index("def Y2L ("))]
    fresh=set(m.DECL.findall(native)) - {"Y8f","Y8f_eq"}
    current={recipe["renames"].get(name,name) for name in fresh}
    start=text.index("def Y2L(")
    stop=text.index("section\n@[inline] def MYa7",start)
    block=text[start:stop]
    forbidden=set(re.findall(r"[\w']+",text))|{"IO","as","by","do","if","in","at","of","is","or"}
    guard_recipe=HERE.parent.parent/"research/board-frontier/patch_norm_guard_v2.py"
    if guard_recipe.exists():
        forbidden.update(re.findall(r"[\w']+",guard_recipe.read_text(encoding="utf-8")))
    choices=(a+b for a,b in itertools.product("qrstuvwxyzabcdefghijklmnop","ABCDEFGHIJKLMNOPQRSTUVWXYZ"))
    names={}
    for name in sorted(current):
        if len(name.encode())<=2:
            continue
        candidate=next(value for value in choices if value not in forbidden)
        forbidden.add(candidate);names[name]=candidate
    for old,new in sorted(names.items(),key=lambda item:-len(item[0])):
        block,count=re.subn(r"(?<![\w'])"+re.escape(old)+r"(?![\w'])",new,block)
        assert count>0,old
    result=(text[:start]+block+text[stop:]).encode("utf-8")
    assert result.endswith(b"\n")
    result=result[:-1]
    report={"scope":"ALPHA_RENAMING_HEADROOM_ONLY_NOT_COMPILED_NOT_QUEUED",
            "prior_sha256":hashlib.sha256(raw).hexdigest(),"prior_bytes":len(raw),
            "result_sha256":hashlib.sha256(result).hexdigest(),"result_bytes":len(result),
            "saved_bytes":len(raw)-len(result),"remaining_bytes":256000-len(result),
            "final_newline_removed":True,
            "fresh_only_names":names,"binder_capture_policy":"Every newname absentfrom ALL oldsource andguard26v2recipe tokens; no Lean2letterreservednames",
            "candidate_inflight_unchanged":True,"guard26_v2_extra_bytes":351,
            "composition_fits_size":len(result)+351<=256000,
            "required":"New exactsource fullgate/native measurement before adoption; do not sum componentgains",
            "publication":"Own recipe/receipt only; reconstructedwholeupstreamsource remains ephemeral"}
    spec=importlib.util.spec_from_file_location("r27_tight_graft_policy",HERE/"patch_public.py")
    p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p)
    report["policy"]=p.policy_check(result)
    (HERE/"native-stats-headroom-receipt.json").write_text(json.dumps(report,indent=2)+"\n",encoding="utf-8")
    print(json.dumps(report,indent=2))

if __name__=="__main__":
    main()
