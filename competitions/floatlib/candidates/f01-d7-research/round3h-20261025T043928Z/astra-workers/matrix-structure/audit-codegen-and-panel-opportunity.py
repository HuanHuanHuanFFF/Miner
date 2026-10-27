"""Bounded read-only old-codegen comparison plus new bridge address model."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json, re, time
OUT = Path(__file__).resolve().parent
ROOT = next(p for p in OUT.parents if (p / "competitions/floatlib/pins.json").is_file())
start = time.monotonic(); sha = lambda b: hashlib.sha256(b).hexdigest()
cpath = "competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40136215532/download-b5ee18c29caa44b7ac3cfe73f422b8c7/diagnostics/f01-r14-dev-p2-n1-cache/candidate-generated-0.c"
cb = (ROOT / cpath).read_bytes(); c = cb.decode()
assert sha(cb) == "6b2a3d7073ad77a4b2b3580e1c20853c80f8036011f14b2a79d99a00f59ff37b"
def function(symbol):
    pat = re.compile(r"^LEAN_EXPORT [^\n]*\b"+re.escape(symbol)+r"\([^\n]*\)\{", re.M)
    matches = list(pat.finditer(c)); assert len(matches) == 1
    i = matches[0].start(); j = matches[0].end(); depth = 1
    while depth:
        if c[j] == "{": depth += 1
        elif c[j] == "}": depth -= 1
        j += 1
    return c[i:j]
oldfunctions = []
for name in ["lp_competition_Submission_NativeFinal_dotLoop", "lp_competition_Submission_R11CrossRows_wordLoop___redArg"]:
    body = function(name)
    tokens = ["lean_float32_of_bits(","lean_box_float32(","lean_alloc_ctor(","lean_float32_mul(","lean_float32_add(","goto _start;"]
    oldfunctions.append({"symbol":name,"source_line":c[:c.index(body)].count("\n")+1,
                         "prototype":body.splitlines()[0],"sha256":sha(body.encode()),
                         "static_sites":{t:body.count(t) for t in tokens}})
    (OUT / (name.split("_Submission_")[1]+"-prior-C.txt")).write_text(body+"\n",encoding="utf-8")
assert oldfunctions[0]["static_sites"]["lean_float32_of_bits("] == 2
assert oldfunctions[1]["static_sites"]["lean_alloc_ctor("] == 1
cross = function("lp_competition_Submission_R11CrossRows_wordLoop___redArg")
assert "lean_alloc_ctor(0, 0, 32)" in cross.split("else",1)[0]
assert "lean_alloc_ctor(" not in cross.split("else",1)[1]

analysis_path = "competitions/floatlib/candidates/f01-d7-research/round3h-20261024T112622Z/profile-whole-multi-analysis-40099316795.json"
ab = (ROOT / analysis_path).read_bytes(); analysis = json.loads(ab)
exposure = []; short_pair_exposure = []
for seed in analysis["seeds"]:
    cases = [c for c in seed["cases"] if c["timed"]]
    whole = sum(c["whole_process_mean_ns"] for c in cases)
    selected = [c for c in cases if c["kernel"] == "bmm" and c["shape"]["p"] > 8 and c["shape"]["n"] > 4
                and c["shape"]["m"] >= 4 and c["route"]["route"] != "UnderflowZero"]
    total = sum(c["whole_process_mean_ns"] for c in selected)
    bycell = {}
    for item in selected: bycell[item["cell"]] = bycell.get(item["cell"],0) + item["whole_process_mean_ns"]
    exposure.append({"seed":seed["seed"],"cases":[{"name":c["name"],"shape":c["shape"],"ns":c["whole_process_mean_ns"]} for c in selected],
                     "whole_share":total/whole,"quarter_local_reduction_whole":.25*total/whole,"half_local_reduction_whole":.5*total/whole,
                     "selected_cost_share_by_cell":{k:v/total for k,v in bycell.items()}})
    short = [c for c in cases if c["kernel"] == "bmm" and 2 <= c["shape"]["p"] <= 8
             and 1 < c["shape"]["n"] <= 4 and c["shape"]["m"] >= 4 and c["route"]["route"] != "UnderflowZero"]
    short_pair_exposure.append({"seed":seed["seed"],"whole_share":sum(c["whole_process_mean_ns"] for c in short)/whole,
        "cases":[{"name":c["name"],"shape":c["shape"],"source_terminal_F2_evaluations":c["shape"]["batch"]*c["shape"]["m"]*((c["shape"]["p"]+1)//2)} for c in short],
        "limit":"Constructor evaluations in the new source model, not measured heap allocations or allocation time; old df5c diagnosis is only workload exposure."})

checks = 0; emitted_cases = 0
for batch in range(4):
  for m in range(13):
    for n in range(8):
      for p in range(14):
        emitted = []
        for b in range(batch):
          for h in range(m//4):
            first = 4*h
            for r in range(4):
              rawbase = (b*m+first+r)*n
              panelbase = (b*m+first)*n+r*n
              for k in range(n):
                assert rawbase+k == panelbase+k; checks += 1
              emitted.extend((b*m+first+r)*p+j for j in range(p))
          first = 4*(m//4)
          assert 0 <= m-first < 4
          for r in range(m-first):
            numericbase = r*n
            preparerawbase = (b*m+first)*n
            finishrawbase = (b*m+first+r)*n
            for k in range(n):
              assert preparerawbase+numericbase+k == finishrawbase+k; checks += 1
            emitted.extend((b*m+first+r)*p+j for j in range(p))
        assert emitted == list(range(batch*m*p)); emitted_cases += 1
        assert time.monotonic()-start < 5

receipt = {"at_utc":datetime.now(timezone.utc).isoformat(),"status":"PRIOR_C_AND_FINITE_PANEL_TRACE_ONLY",
           "c_source":cpath,"c_sha256":sha(cb),"c_kernel_sha256":"83a981273988f07ce89d4a18c1dbef475adb6ed2fefce381138c5d165bf2a806",
           "prior_functions":oldfunctions,"new_F2_generated_C":"UNKNOWN_NOT_BUILT",
           "analogy_limit":"Prior C establishes Float32 scalar parameters and terminal record allocation pattern in old functions, not new compiler result. Static site counts are not dynamic counts or physical allocations.",
           "source_expectation":"R15ThinPairs.loop has two Float32 recursive scalar parameters; F2 constructor occurs only in else termination. In-bounds source performs one A raw conversion and two mapped-B reads per k; no F2 is constructed in recursive branch.",
           "short_n_pair_return_risk":short_pair_exposure,
           "panel_exposure_source":analysis_path,"panel_exposure_source_sha256":sha(ab),"panel_exposure":exposure,
           "opportunity_limit":"Old exposed df5c whole diagnostics only. Even complete removal of the selectedp>8 path saves at most1.43%-1.75% of whole there. No prediction for new ec82, formal score or future seeds; category labels do not prove replay shares.",
           "panel_index_checks":checks,"panel_output_shape_checks":emitted_cases,
           "panel_trace_dimensions":{"batch":"0..3","m":"0..12","n":"0..7","p":"0..13"},
           "tail_raw_base_witness":{"batch":2,"m":5,"n":5,"p":11,"b":1,"first":4,"local_numeric_base":0,"correct_original_finish_base":45},
           "elapsed_seconds":time.monotonic()-start}
assert receipt["elapsed_seconds"] < 5
(OUT / "codegen-and-panel-opportunity.json").write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+"\n",encoding="utf-8")
print(json.dumps({"status":receipt["status"],"panel_index_checks":checks,"panel_output_shape_checks":emitted_cases,
                  "elapsed_seconds":receipt["elapsed_seconds"],"whole_shares":[r["whole_share"] for r in exposure]}))
