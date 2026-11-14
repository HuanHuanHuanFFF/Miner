"""Static custom-declaration closure audit without publishing upstream text."""
from pathlib import Path
import hashlib
import importlib.util
import json
import re
import sys

sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent

def sha(data):
    return hashlib.sha256(data).hexdigest()

def declarations(text):
    pattern=re.compile(r"^(?:@\[[^\n]*\] )?(?:(?:noncomputable|private) )?(?:def|lemma|theorem) ([^\s(:]+)",re.M)
    matches=list(pattern.finditer(text))
    return {m.group(1):text[m.start():(matches[i+1].start() if i+1<len(matches) else len(text))]
            for i,m in enumerate(matches)}

def canonical(text):
    text=re.sub(r"\bnoncomputable\s+", "",text)
    text=re.sub(r"@\[(?:inline|noinline|always_inline|specialize)\]\s*", "",text)
    text=re.sub(r"(?m)^(?:section|end)\s*$", "",text)
    return re.sub(r"\s+","",text)

def main():
    spec=importlib.util.spec_from_file_location("r27_graft_check",HERE/"graft_native_stats_v1.py")
    mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
    a=mod.fetch(12);b=mod.fetch(27)
    ta,tb=a.decode(),b.decode()
    da,db=declarations(ta),declarations(tb)
    graft=tb[tb.index("def Y2L ("):tb.index("section\ndef MYa7b",tb.index("def Y2L ("))]
    dg=declarations(graft)
    used={name for name in db if re.search(r"(?<!\w)"+re.escape(name)+r"(?!\w)",graft)}
    unresolved=sorted(used-set(da)-set(dg))
    common=sorted(used & set(da)-set(dg))
    rows=[]
    for name in common:
        ca,cb=canonical(da[name]),canonical(db[name])
        rows.append({"name":name,"same_canonical_source":ca==cb,
                     "source12_declaration_sha256":sha(ca.encode()),
                     "source27_declaration_sha256":sha(cb.encode())})
    report={"scope":"STATIC_CUSTOM_DECLARATION_CLOSURE_NOT_FORMAL_KERNEL_CHECK",
            "source12_sha256":sha(a),"source27_sha256":sha(b),
            "native_graft_declarations":len(dg),"referenced_source27_custom_declarations":len(used),
            "unresolved_custom_names":unresolved,"shared_declarations":rows,
            "differences_require_exact_compile": [r["name"] for r in rows if not r["same_canonical_source"]]}
    (HERE/"native-stats-dependency-audit.json").write_text(json.dumps(report,indent=2)+"\n",encoding="utf-8")
    print(json.dumps(report,indent=2))

if __name__=="__main__":
    main()
