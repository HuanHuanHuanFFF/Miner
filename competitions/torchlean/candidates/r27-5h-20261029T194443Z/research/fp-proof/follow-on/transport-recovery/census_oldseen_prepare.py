"""Exact metadata census over already-seen oldR26 batch8 nMLP only.
No Lean/native timing, no new confirmation data, no dependency installation.
"""
from pathlib import Path
from datetime import datetime, timezone
import collections
import hashlib
import importlib.util
import json
import sys
import time
sys.dont_write_bytecode = True

HERE = Path(__file__).resolve().parent
A_ROOT = HERE.parents[1]
REPLAY = A_ROOT / "census/fp_replay-batch8.py"
MASK32 = (1 << 32) - 1
MASK64 = (1 << 64) - 1
CENTER = 1 << 62
LIMIT = (1 << 63) - 1


def meta(words):
    lo = min([MASK32] + [((v & 0x7fffffff) - 1) & MASK32 for v in words]) >> 23
    hi = max([0] + [v & 0x7fffffff for v in words]) >> 23
    yk = lambda e: 0 if e == 0 else e - 1
    return {"lo":lo,"hi":hi,"base":yk(lo),"span":(yk(hi)-yk(lo)) & MASK64}


def summarize(x, rows, k, out, weights, stage):
    xs = [x[r*k:(r+1)*k] for r in range(rows)]
    ws = [weights[j*k:(j+1)*k] for j in range(out)]
    xm = [meta(a) for a in xs]
    wm = [meta(a) for a in ws]
    minx = min([99] + [a["span"] for a in xm])
    maxw = max([0] + [a["span"] for a in wm])
    minw = min([MASK64] + [a["span"] for a in wm])
    enabled = k >= 16 and all(a["hi"] != 255 for a in xm+wm) and minx + maxw <= 15
    records = []
    totals = collections.Counter()
    for raw, a in zip(xs, xm):
        nonzero = [v for v in raw if (v & 0x7fffffff) != 0]
        sparse = 0 < len(nonzero) and 4 * len(nonzero) <= 3 * k
        vals = nonzero if sparse else raw
        eligible_cols = sum(a["span"] + w["span"] <= 15 for w in wm)
        row_prepared = enabled and a["span"] + maxw <= 15
        item = dict(a, selected_terms=len(vals), mode="sparse" if sparse else "dense", prepared=row_prepared,
                    span_eligible_columns=eligible_cols,
                    span_potential_MACs=len(vals)*eligible_cols)
        if row_prepared:
            big = 0
            bad60 = 0
            for v in vals:
                e = (v >> 23) & 255
                mant = (v & 0x7fffff) + ((1 << 23) if e else 0)
                yd = e - 1 if e else 0
                M = (mant << ((yd-a["base"]) % 64)) & MASK64
                big += sum(z > LIMIT for z in [(CENTER+M)&MASK64,(CENTER-M)&MASK64])
                bad60 += M >= 1 << 39
            unused_wide = a["span"] > 15
            no_eligible_col = a["span"] + minw > 15
            item.update(prepared_slots=2*len(vals),bigNat_entries=big,aligned60_bound_fail_terms=bad60,unused_wide=unused_wide,no_span_eligible_column=no_eligible_col)
            totals["prepared_rows"] += 1
            totals["prepared_slots"] += 2*len(vals)
            totals["bigNat_entries"] += big
            totals["aligned60_bound_fail_terms"] += bad60
            totals["all_dense_linear_MACs"] += k*out
            if sparse and a["span"] <= 15:
                label = "sparse_le7" if a["span"] <= 7 else "sparse_8to15"
                totals[label+"_rows"] += 1
                totals[label+"_prepared_terms"] += len(vals)
                totals[label+"_span_potential_MACs"] += len(vals)*eligible_cols
            if unused_wide:
                totals["unused_wide_rows"] += 1
                totals["unused_wide_slots"] += 2*len(vals)
                totals["unused_wide_bigNat_entries"] += big
            if no_eligible_col:
                totals["no_span_eligible_column_rows"] += 1
                totals["no_span_eligible_column_slots"] += 2*len(vals)
        records.append(item)
    return dict(stage=stage,shape=[rows,k,out],global_QPS=enabled,min_input_span=minx,max_weight_span=maxw,min_weight_span=minw,rows=records,counts=dict(totals))


def main():
    began = datetime.now(timezone.utc).isoformat()
    start = time.monotonic()
    spec = importlib.util.spec_from_file_location("r27_oldseen_replay_for_metadata", REPLAY)
    replay = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(replay)
    expected = json.loads((replay.E / "summary.json").read_bytes())["protected_before"]["lean/bench/ExactSuite.lean"]
    assert hashlib.sha256(replay.SUITE.read_bytes()).hexdigest() == expected

    class Census(replay.Census):
        def __init__(self):
            super().__init__()
            self.prepare_scope = []
        def linear(self,x,rows,k,out,w,b,relu,stage):
            self.prepare_scope.append(summarize(x,rows,k,out,w,stage))
            return super().linear(x,rows,k,out,w,b,relu,stage)

    cells = []
    total = collections.Counter()
    sources = []
    for root in [26102901,26102903]:
        reqpath = replay.E / f"fp-word-conv6-{root}-request.json"
        oldpath = replay.E / f"fp-word-conv6-{root}-measurement.json"
        req = json.loads(reqpath.read_bytes())
        old = json.loads(oldpath.read_bytes())["result"]
        sources.append({"root":root,"request_sha256":hashlib.sha256(reqpath.read_bytes()).hexdigest(),"measurement_sha256":hashlib.sha256(oldpath.read_bytes()).hexdigest()})
        for workload in req["workloads"]:
            for kind in ["normal","wide","sparse"]:
                assert time.monotonic() - start < 90, "boundedmetadatareplayexceeded90s"
                c = Census()
                result = replay.run_cell("normalized_mlp",workload["seed"],workload["profile"],kind,c)
                cell = f'{workload["id"]}|normalized_mlp:b8:{kind}'
                actual = replay.fnv(result)
                wanted = old["rounds"][0]["cells"][cell]["candidate_checksum"]
                assert actual == wanted, (root,cell,actual,wanted)
                for stage in c.prepare_scope:
                    total.update(stage["counts"])
                cells.append({"root":root,"cell":cell,"profile":workload["profile"],"seed":workload["seed"],"checksum_match":True,"checksum":actual,"stages":c.prepare_scope})
    result = {
        "state":"EXACT_YAH_METADATA_FORMULA_CENSUS_OLD_SEEN_36_NMLP_B8_CELLS",
        "actual_start_utc":began,
        "actual_end_utc":datetime.now(timezone.utc).isoformat(),
        "elapsed_seconds":time.monotonic()-start,
        "cells":cells,
        "total_counts":dict(total),
        "old_inputs":sources,
        "official_generator_sha256":expected,
        "replay_sha256":hashlib.sha256(REPLAY.read_bytes()).hexdigest(),
        "formula_sha256":hashlib.sha256(replay.UTIL.read_bytes()).hexdigest(),
        "script_sha256":hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        "limits":["Formula metadata/codec counts,notnativebranchinstrumentationorallocationtiming.",
                  "Oldseenbatch8normalized_mlp only; no productionfrequencyorgainclaim.",
                  "QPSmodelsactualmininputspan/maxweightspanandYahmin(absBits-1),notmaxyd-minyd.",
                  "No newconfirmationinput/result,Leancompile,kernelchange,CIorcurrentchampionmeasurement."],
        "native_timing":"UNKNOWN"
    }
    (HERE / "oldseen-prepare-census.json").write_text(json.dumps(result,indent=2)+"\n",encoding="utf-8")
    print(json.dumps({"state":result["state"],"cells":len(cells),"checksum_matches":sum(c["checksum_match"] for c in cells),"total_counts":result["total_counts"],"elapsed_seconds":result["elapsed_seconds"]}))


if __name__ == "__main__":
    main()

