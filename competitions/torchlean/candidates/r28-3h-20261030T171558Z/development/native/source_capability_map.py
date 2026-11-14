"""Lightweight source-only capability map, never a native cost measurement."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
HERE=Path(__file__).resolve().parent
ROUND=HERE.parents[1]
DECL=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:(?:noncomputable|private|protected|unsafe)\s+)*(def|lemma|theorem|structure|abbrev)\s+([\w.'?!]+)")
STOP=re.compile(r"(?m)^(?:(?:@\[[^\n]*\]\s*)?(?:(?:noncomputable|private|protected|unsafe)\s+)*(?:def|lemma|theorem|structure|abbrev)\b|section\b|end\b|open\b|namespace\b|set_option\b)")
def sha(x):return hashlib.sha256(x).hexdigest()
def declarations(s):
    bounds=[m.start() for m in STOP.finditer(s)]
    result={}
    for m in DECL.finditer(s):
        end=next((b for b in bounds if b>m.start()),len(s))
        result[m.group(2)]={"kind":m.group(1),"start_line":s.count("\n",0,m.start())+1,"bytes":len(s[m.start():end].encode()),"body":s[m.start():end]}
    return result
def map_source(p):
    raw=p.read_bytes();s=raw.decode();d=declarations(s)
    kernels=d.get("kernels",{}).get("body","")
    runtime=[]
    for name,row in d.items():
        if row["kind"] not in ["def","abbrev"]:continue
        runtime.append({"name":name,**{k:row[k] for k in ["kind","start_line","bytes"]},
                        "direct_local_runtime_dependencies":sorted({t for t in re.findall(r"[\w.'?!]+",row["body"]) if t in d and t!=name and d[t]["kind"] in ["def","abbrev"]})})
    return {"file":p.name,"source_sha256":sha(raw),"bytes":len(raw),"free_bytes":256000-len(raw),
            "declaration_count":len(d),"runtime_declaration_count":len(runtime),"kernels":kernels.strip(),
            "runtime_inventory":runtime}
if __name__=="__main__":
    sources=[ROUND/"competition-state/source-private"/f"official-{n}.lean" for n in [36,43,11,53,54,8]]
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"state":"SOURCE_ONLY_NOT_NATIVE_COST", "sources":[map_source(p) for p in sources],
         "route_notes":{
             "36":{"linear":"YaVM: native128 paired-row MD2; per-call BX/BV exponent scan, XP/WP signed-immediate Nat preparation; scalar fallback outside dimensions/domain",
                   "gemm":"Ya3M: AP/BC/BP prep then scalar MD for each output; B-wide Yc bb scan plus per-column MQ scan; finite k>=20 pairlinear candidate replaces this extension and preserves original Ya3 fallback",
                   "norm":"YbcN: Y8fL statistics plus LNr/LNj output mutation; native Ya7G output with rational fallback",
                   "candidate":"pairlinear36 recipe targets shared B loads and two-row accumulation, incurs per-batch transpose/extract/flatten plus exact negative-zero bias. End-to-end benefit UNKNOWN; 16.82% predecessor reduction needed at saved snapshot"},
             "priority_update_ack":"Read requests/172118-new-public-near-champion-bases.md. Native keeps independent Mixer substantive route initially; nearer ResNet11/Mobile53 alternatives surveyed next if exact pairlinear feedback loses.",
             "measurement_boundary":"Only source operation/call structure and byte cost verified. No percent attribution, native speed, or proof acceptance inferred."},
         "resources":{"tokens":"UNKNOWN","cached_input_tokens":"UNKNOWN","CI_occupancy":"Root-owned; this role dispatches none","local_native_compile":False}}
    (HERE/"SOURCE-CAPABILITY-COST-MAP.json").write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({"sources":[{"file":r["file"],"sha256":r["source_sha256"],"bytes":r["bytes"]} for r in out["sources"]],"state":out["state"]}))
