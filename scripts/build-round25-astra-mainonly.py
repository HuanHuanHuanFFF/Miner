"""One actual maintenance ablation: keep long-table updates only at main positions."""
from pathlib import Path
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
PARENT = ROOT / "candidates/r25-astra-dual8"
OUT = ROOT / "evidence/round25/astra"
NAME = "r25-astra-dual8-mainonly"
EXPECTED = "4bfe5d2973ed553922eca1d451912bda5d8ad2d6f16c0ccb83419c5086f20f88"
COUNTS = ROOT / "evidence/round25/38128787484/origins-f-native/diagnostics/r25-dual8-origins/counts.json"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def save(path, value):
    assert not path.exists(), path
    path.write_bytes((json.dumps(value, indent=2) + "\n").encode())


def main():
    raw = (PARENT / "parse.rs").read_bytes()
    assert sha(raw) == EXPECTED
    base = raw.decode()
    begin = base.index("pub fn r25_d8_link<const H: usize>")
    end = base.index("/// Original short head", begin)
    old = base[begin:end]
    line = "    long[r25_d8_slot(s, i)] = i as u32;\n"
    assert old.count(line) == 1
    new = old.replace(line, "    // R25 maintenance ablation: long-table records are main positions only.\n")
    source = base[:begin] + new + base[end:]
    assert source.replace(new, old, 1) == base
    # The primary table is still updated inside every existing record callback.
    assert new.count("head[a] = i as u32;") == 1
    assert "r25_d8_slot(" not in new
    # The original main update and full long-probe logic remain exact.
    assert source.count("long[la] = p as u32;") == 1
    assert source[source.index("pub fn r25_d8_probe("):source.index("pub fn r25_d8_record3<")] == base[base.index("pub fn r25_d8_probe("):base.index("pub fn r25_d8_record3<")]
    observed = json.loads(COUNTS.read_bytes())
    assert observed["status"] == "VERIFIED_UNTIMED_ORIGINS_TOKEN_DECODE_AND_ALL_E_COUNTS_EQUAL"
    assert observed["source_hashes"]["parse.rs"] == EXPECTED
    total = observed["totals"]
    origins = total["origins"]
    record_accepted = sum(d["record"]["accepted"] for d in origins.values())
    record_extra = sum(d["record"]["accepted_extra_bytes_vs_primary"] for d in origins.values())
    main_accepted = sum(d["main"]["accepted"] for d in origins.values())
    assert (main_accepted, record_accepted, record_extra) == (59982, 53017, 459087)
    path = ROOT / "candidates" / NAME
    assert not path.exists(), path
    path.mkdir()
    files = {"parse.rs": source.encode(), "Parse.lean": (PARENT / "Parse.lean").read_bytes()}
    assert all(0 < len(data) <= 524288 for data in files.values())
    for filename, data in files.items():
        (path / filename).write_bytes(data)
    hashes = {filename: sha(data) for filename, data in files.items()}
    manifest = {
        "candidate": NAME, "parent": PARENT.name, "hashes": hashes,
        "mechanism": "Delete only the independent8-byte hash/store in r25_d8_link, retaining the four-byte head store at every original record position. Main8-byte table reads/writes and all original probes remain. Only rows1/6 inherit this existingdual8 engine; otherroutes unchanged.",
        "difference_from_old_work": "This is an explicit endpoint ablation motivated by measured source provenance, not a maintenance-density sweep. F found record updates account for61.446% of oldhash calls yet supply53017 actual accepted hints and459087 localextra-length bytes. The experiment deliberately risks that quality to measure the real cost/quality endpoint.",
        "attribution": {"source": "references/round21-public-595/source-receipt.json",
                        "code_parent": "candidates/r25-astra-dual8/manifest.json",
                        "original_headers": "Unmodified parent headers retained."},
        "coverage_risk": "Record-sourced useful hints can disappear, and older main hints become visible; future matches, insertions and encoder blocks change. Source-count fractions are not predicted retained-byte fractions. Primary>=8 may now have an older viable long hint, so no such domain is pruned.",
        "proof_status": "DRAFT_UNCOMPILED_FOR_NEW_EXACT_PAIR",
        "proof_migration": "Parentdual8 proof itself is uncompiled; fresh extraction may change recordloop captures because long is no longer mutated there. Match validators remain byte-identical. No oldgate inherited.",
        "performance_status": "UNKNOWN", "formal_submission_sent": False
    }
    save(path / "manifest.json", manifest)
    entry = {"name": NAME, "path": path.relative_to(ROOT).as_posix(), "control": False,
             "hashes": hashes, "anchor": "public595", "comparison_baseline": "dual8", "native_decode_reference": "dual8"}
    save(OUT / "mainonly-entry.json", entry)
    save(OUT / "mainonly-preflight.json", {
        "status": "PREDECLARED_ACTUAL_MAINTENANCE_ABLATION",
        "parent_hash": EXPECTED,
        "observed_F": {"receipt": COUNTS.relative_to(ROOT).as_posix(), "sha256": sha(COUNTS.read_bytes()),
                       "old_hash8_calls": total["counts"]["hash8_calls"],
                       "old_main_updates": total["counts"]["main_long_updates"],
                       "old_record_updates": total["counts"]["record_long_updates"],
                       "old_main_accepted": main_accepted, "old_record_accepted": record_accepted,
                       "old_record_extra_length": record_extra},
        "minimum": "One actual28-file original-encoder/decode run with exactdual8 and combo, plus knownend4 if already present. Capture token/output hashes and per-file size. This is a new trajectory, not replaying F counters as a performance prediction.",
        "cost_cap_runner_minutes": 12,
        "decision": "If quality loss is so large that no credible fast-end tradeoff remains, stop this endpoint. Otherwise obtain originalpaired total compression before any proof investment. No samplingdensity/mask/depth sweep; no automatic combination.",
        "unchanged_probe_rule": "Keep the original full r25_d8_probe, including possibleprimary>=8 adoption. The all-positions8table invariant no longer applies after this ablation.",
        "counts_limit": "The old2538080 record writes/hash calls are a frozen-trajectory count, not the newprogram operationdelta or a3% recoverable-time bound.",
        "gate": "NOT_RUN", "native": "NOT_RUN"
    })
    save(OUT / "mainonly-static-audit.json", {
        "status": "VERIFIED_ONE_HELPER_SCOPE_AND_EXACT_REVERSAL_ONLY",
        "parent_sha256": EXPECTED, "candidate_sha256": hashes["parse.rs"],
        "removed_operation": line.strip(), "four_byte_store_preserved": True,
        "main_long_update_preserved": True, "full_probe_region_identical": True,
        "native_rust": "NOT_RUN", "lean": "NOT_RUN"
    })
    print(json.dumps(entry, indent=2))


if __name__ == "__main__":
    main()
