"""Checks bytes, the pinned textual policy, and source identity. Does not prove Lean code."""
from pathlib import Path
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]

def sha(data):
    return hashlib.sha256(data).hexdigest()

def blob(data):
    return hashlib.sha1(b"blob " + str(len(data)).encode() + b"\0" + data).hexdigest()

def main():
    policy = json.loads((ROOT / "diagnostics/policy_pattern.json").read_text())
    banned = re.compile(policy["BANNED"])
    checks = []
    for name in ("NormalEqAttempt.lean", "ReusableModel.lean"):
        p = ROOT / "lean" / name
        data = p.read_bytes()
        text = data.decode("utf-8")
        hits = [{"token": m.group(), "line": text.count("\n", 0, m.start()) + 1}
                for m in banned.finditer(text)]
        imports = [line.strip() for line in text.splitlines() if re.search(r"\bimport\b", line)]
        attributes = [a.strip() for group in re.findall(r"@\[([^\]]*)\]", text)
                      for a in group.split(",")]
        badattrs = [a for a in attributes if a.split()[-1] not in policy["allowed_attributes"]]
        item = {"file": str(p.relative_to(ROOT)), "bytes": len(data), "sha256": sha(data),
                "imports": imports, "forbidden_matches": hits,
                "set_option_count": len(re.findall(r"\bset_option\b", text)),
                "disallowed_attributes": badattrs}
        assert len(data) <= policy["max_bytes"]
        assert imports == [policy["required_import"]]
        assert not hits and not badattrs and item["set_option_count"] == 0
        item["status"] = "TEXT_PASS_ONLY"
        checks.append(item)
    manifest = json.loads((ROOT / "public_sources/source_manifest.json").read_text())
    for e in manifest:
        data = (ROOT / e["local_path"]).read_bytes()
        assert len(data) == e["bytes"] and sha(data) == e["sha256"]
        assert blob(data) == e["git_blob_sha1"]
    parent = ROOT / "public_sources/miner_parent/competitions/floatlib/candidates/f01-d2-final-finite/Kernel.lean"
    assert sha(parent.read_bytes()) == "86312a3759286cb207f946af9db95546777fdb16f1bd147f7892c0f9e1d79217"
    fixed = (ROOT / "public_sources/floatlib_fixed/FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Representation.lean").read_text()
    newer = (ROOT / "public_sources/floatlib_comparison/FloatLib/Floats/Formats/BinaryInterchange/DirectedSemantics/Exact.lean").read_text()
    marker = "/-- A nonzero decoded dyadic already uses the format's canonical exponent. -/"
    def proofblock(text):
        start = text.index(marker)
        return text[start:text.index("\nend ", start)].rstrip().encode()
    fblock, nblock = proofblock(fixed), proofblock(newer)
    assert fblock == nblock
    base = (ROOT / "lean/components/AdmissionZero.lean").read_bytes()
    assert sha(base) == "dddb4cd8dd2d3ba987fec1bcd7235e4875548e00b8bbb533431977966dfdfa0d"
    integration = (ROOT / "lean/components/NormalIntegration.fragment.lean").read_text()
    assert "hNormal" not in integration
    assert "theorem convert_eq (u : UInt32) : convert u = Float32.ofBits u" in integration
    result = {"status": "STATIC_CHECKS_PASS", "lean_status": "NOT_RUN",
              "axiom_audit": "NOT_RUN", "official_gate": "NOT_RUN", "performance": "NOT_RUN",
              "c_experiment": "NOT_RUN_BY_REQUEST", "candidate_policy": checks,
              "public_sources_verified": len(manifest),
              "source_bytes": sum(e["bytes"] for e in manifest),
              "equal_roundtrip_block": {"bytes_without_trailing_newline": len(fblock),
                                        "sha256": sha(fblock)},
              "baseline_unchanged": True, "unconditional_signature_has_hNormal": False}
    (ROOT / "results/static_checks.json").write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps(result, indent=2))

if __name__ == "__main__":
    main()
