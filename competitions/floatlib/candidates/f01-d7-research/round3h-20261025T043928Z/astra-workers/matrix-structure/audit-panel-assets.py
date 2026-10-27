"""Read/hash old accepted assets; build only a reusable fragment bundle, no Kernel."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json, time, re
OUT = Path(__file__).resolve().parent
ROOT = next(p for p in OUT.parents if (p / "competitions/floatlib/pins.json").is_file())
start = time.monotonic()
sha = lambda b: hashlib.sha256(b).hexdigest()
def read(path): return (ROOT / path).read_bytes()
parts = []
def add(label, path, expected=None, content=None, evidence=None):
    original = read(path)
    if expected:
        assert sha(original) == expected, (path, sha(original), expected)
    selected = original if content is None else content(original)
    parts.append({"label": label, "source": path, "source_sha256": sha(original),
                  "selected_sha256": sha(selected), "bytes": len(selected), "evidence": evidence,
                  "text": selected.decode()})

add("F40_and_Panel4", "competitions/floatlib/candidates/f01-d11-panel4-codegen-probe/increment.lean",
    evidence="9a source and existing Panel4 definitions full-gated in931; old BMM entry stayed active")
add("actual_panel_row_projection", "competitions/floatlib/candidates/f01-d11-panel4-projection-proof2/panel4-projection-proof2.lean",
    "93b1ac6fed4b6f73aef621d374fcea195886a04ca3bdd0ef3cd93b5684104bdf",
    evidence="run40050615221 source0feec56a: exact statement-only PASS")
add("direct_lane40", "competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/astra-panel4-lane40-required.lean",
    evidence="lane40 interface retained in full-gated28b source; exact extracted bytes checked below")
def layout(src):
    begin = b"namespace Submission.R11WideLayout"
    end = b"end Submission.R11WideLayout"
    i = src.index(begin); j = src.index(end, i) + len(end)
    return src[i:j] + b"\n"
add("inline_full_gated_writer", "competitions/floatlib/candidates/f01-r11-wide4-inline-proof3/Kernel.lean",
    "28b819120cd3aaa1f19038f66042a9ceffe0c9329baab20fe223e98d151ce00b", content=layout,
    evidence="run40044330511 full-gate PASS, active old wide caller; generic helper alone is not active codegen evidence")
add("local_tail_with_raw_base", "competitions/floatlib/candidates/f01-d11-panel4-tail-factored-proof/tail-factoring.lean",
    "9d7bcb60b483b1b1994836c679e8b466d3cac1c17bc0532875aaf69cbdb2d486",
    evidence="run40051933922 source1b472298: exact statement-only PASS")
entry = (OUT / "Panel4-entry-bridge.lean").read_bytes()
parts.append({"label":"new_actual_entry_bridge", "source":"Panel4-entry-bridge.lean",
              "source_sha256":sha(entry), "selected_sha256":sha(entry), "bytes":len(entry),
              "evidence":"R15 draft NOT_COMPILED; no new IEEE arithmetic theorem", "text":entry.decode()})

bundle = ("\n\n".join(p["text"].rstrip() for p in parts) + "\n").encode()
assert not re.search(rb"\b(sorry|admit|axiom|unsafe|implemented_by|extern)\b", bundle)
# Verify that names in the extracted lane40 helper are present in the actual
# full-gated donor. Whitespace normalization only; no declaration is rewritten.
wide = read("competitions/floatlib/candidates/f01-r11-wide4-inline-proof3/Kernel.lean").decode()
lane = parts[2]["text"]
for marker in ["@[inline] def lane40", "theorem lane40_eq"]:
    a = lane.index(marker)
    z = a + re.search(r"\n(?:@\[[^\n]+\] )?(?:def |theorem |end )", lane[a+1:]).start() + 1
    ls = re.sub(r"\s+", "", lane[a:z])
    b = wide.index(marker)
    zz = b + re.search(r"\n(?:@\[[^\n]+\] )?(?:def |theorem |end )", wide[b+1:]).start() + 1
    ws = re.sub(r"\s+", "", wide[b:zz])
    assert ls == ws, marker
(OUT / "Panel4-reusable-bundle.lean").write_bytes(bundle)

verdicts = [
 ("projection", "competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40050615221/download-dc3fa09f463946e5b590a715193f9be0/diagnostics/f01-d7-public-suite/public-suite", "f01-d11-panel4-projection-proof2", "0feec56a57674a2c7d5de0da3f3c7633e36d5bb5e8c9204ca53a420d4bdcbdfc"),
 ("tail", "competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40051933922/download-ecb6c1975dc349ffb4416b91586fba11/diagnostics/f01-d7-public-suite/public-suite", "f01-d11-panel4-tail-factored-proof", "1b4722989e4352b7f6a80337d545ff0a97d2890f95ccac5788a095da30b1aaa8")]
checked = []
for label, folder, name, expected in verdicts:
    vb = read(folder + "/" + name + "-verdict.json"); verdict = json.loads(vb)
    summary = read(folder + "/summary.json")
    assert expected in summary.decode()
    assert verdict["passed"] and verdict["stage"] == "statement" and verdict["mode"] == "diagnostic-statement-only"
    checked.append({"label":label,"source_sha256":expected,"verdict_sha256":sha(vb),"summary_sha256":sha(summary),
                    "verdict_path":folder+"/"+name+"-verdict.json","status":"STATEMENT_ONLY_PASS"})

base = read("competitions/floatlib/candidates/f01-r15-dev-matrix-only1/Kernel.lean")
assert sha(base) == "ec82ac20cf5b2a9621dce7e409a68a4af9700b1845d23385497c896439e372a1"
receipt = {"at_utc":datetime.now(timezone.utc).isoformat(),"status":"REUSABLE_BUNDLE_ONLY_NO_WHOLE_CANDIDATE",
           "parts":[{k:v for k,v in p.items() if k!="text"} for p in parts], "prior_receipts_rechecked":checked,
           "bundle":"Panel4-reusable-bundle.lean", "bundle_bytes":len(bundle),"bundle_sha256":sha(bundle),
           "bundle_join":"Only trailing whitespace at complete snippet boundaries is normalized; internal donor source is unchanged. Original donor files remain untouched.",
           "base_bytes":len(base),"base_plus_bundle_bytes":len(base)+len(bundle),
           "remaining_to256000_before_dispatch_glue":256000-len(base)-len(bundle),
           "capacity_scope":"Arithmetic byte ledger for exact additive dependencies. No full Kernel assembled and no duplicate-declaration/parser/Lean gate claimed.",
           "new_bridge":"buildTiles_projects -> writeBatch_eq via existing Panel4Tail.tail_eq -> writeBatch_prefix -> output_prefix -> core_eq_reference",
           "runtime_map_boundary":"New output prepares only packedB; A.map occurs in erased proofs. Full rows use local F4 Panel4.packA once per4-row block;0..3tail rows use existing local tail prepare.",
           "actual_entry_remaining":"New bridge compilation, official bmm dispatch/spec wiring and full gate, actual active caller codegen/lifetime, performance. Current source/proof assets do not inherit prior full gate.",
           "audit_repair":"First local extractor failed lane40_eq equality because it included donor's following joinRows/within declarations until namespace end. Fixed declaration boundary only; no source/proof change or negative gate result.",
           "elapsed_seconds":time.monotonic()-start}
assert receipt["elapsed_seconds"] < 5
(OUT / "panel-assets-and-capacity.json").write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+"\n",encoding="utf-8")
print(json.dumps({k:receipt[k] for k in ["status","bundle_bytes","base_plus_bundle_bytes","remaining_to256000_before_dispatch_glue","elapsed_seconds"]}))
