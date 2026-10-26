"""Import the R14 research proof probes byte-for-byte for a statement-only compile check.

The source files live in the Codex worktree as uncommitted snapshots. This script
verifies each requested SHA-256 before copying, writes no edits, and marks the
imported candidates as `statement-only` so the manual workflow only compiles them.
"""
import datetime
import hashlib
import json
from pathlib import Path

CODEX = Path(r"D:\CodingProject\Bitget")
MINE = Path(r"D:\CodingProject\Bitget-DeepSeek")
RESEARCH = CODEX / "competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z"

PROBES = [
    {
        "name": "f01-deepseek-verify-shape1",
        "source": CODEX / "competitions/floatlib/candidates/f01-r14-math-scale-shape1/Kernel.lean",
        "sha256": "4c523fa6534e5c69ebda55b0c337e5d76be8cd7e88173545588a36007dacd792",
        "bytes": 252569,
        "request": RESEARCH / "astra-ci-request-scale-shape1.json",
        "theorems": [
            "Submission.R14ScaleShape.mantissa_product_bounds",
            "Submission.R14ScaleShape.leading_bounds",
            "Submission.R14ScaleShape.carryNat_le",
            "Submission.R14ScaleShape.normal_form",
            "Submission.R14ScaleShape.first_product_form",
        ],
    },
    {
        "name": "f01-deepseek-verify-native-product1",
        "source": CODEX / "competitions/floatlib/candidates/f01-r14-math-native-product1/Kernel.lean",
        "sha256": "14bc44bba0016f5cd1697718f1780e8f1f6caa7b2a93b8d9e72b19adc463e7d1",
        "bytes": 252176,
        "request": RESEARCH / "astra-ci-request-native-product1.json",
        "theorems": [
            "Submission.R14NativeProduct.model_mul_of_nonzero_decodes",
            "Submission.R14NativeProduct.native_mantissa_product",
            "Submission.R14NativeProduct.dyadic_general_scale_value",
            "Submission.R14NativeProduct.model_mul_of_general_scale_decodes",
        ],
    },
]

now = datetime.datetime.now(datetime.timezone.utc).isoformat()
receipt = {"imported_at_utc": now, "role": "statement-compile-only verification import",
           "scope": "Exact bytes from the Codex worktree uncommitted snapshot; no edits; no axiom audit, timing or adoption claim.",
           "probes": []}

for probe in PROBES:
    raw = probe["source"].read_bytes()
    digest = hashlib.sha256(raw).hexdigest()
    assert digest == probe["sha256"], (probe["name"], digest)
    assert len(raw) == probe["bytes"], (probe["name"], len(raw))
    out = MINE / "competitions/floatlib/candidates" / probe["name"]
    out.mkdir(parents=True, exist_ok=True)
    (out / "Kernel.lean").write_bytes(raw)
    manifest = {
        "candidate": probe["name"],
        "candidate_file": "Kernel.lean",
        "candidate_sha256": digest,
        "candidate_bytes": len(raw),
        "validation_mode": "statement-only",
        "import_role": "EXTERNAL_PROOF_PROBE_COMPILE_CHECK_ONLY",
        "source_workspace": str(CODEX),
        "source_path": str(probe["source"].relative_to(CODEX)).replace("\\", "/"),
        "source_sha256": digest,
        "source_state": "UNCOMMITTED_SNAPSHOT_IN_CODEX_WORKTREE",
        "source_request": str(probe["request"]).replace("\\", "/"),
        "source_request_sha256": hashlib.sha256(probe["request"].read_bytes()).hexdigest(),
        "imported_at_utc": now,
        "theorems_requested": probe["theorems"],
        "scope": ("Compilation/statement only. The project diagnostic replay does not run a #print axioms audit, "
                  "paired timing or full gate for this import. No adoption, submission or champion claim. "
                  "The exact bytes are copied from the listed uncommitted snapshot and are not edited here."),
    }
    (out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    (out / "README.md").write_text(
        f"# {probe['name']}\n\n"
        f"R14 研究侧 proof-only 探针的逐字节导入，仅用于 statement 编译检查。\n\n"
        f"- 来源：`{manifest['source_path']}`（Codex 工作区未提交快照）\n"
        f"- SHA-256：`{digest}`（{len(raw)} B）\n"
        f"- 请求回执：`{manifest['source_request']}`\n"
        f"- 限制：不跑公理审计、不计时、不作采纳；完整证明与收益仍以研究侧后续验收为准。\n",
        encoding="utf-8")
    receipt["probes"].append({"candidate": probe["name"], "sha256": digest, "bytes": len(raw),
                              "source": manifest["source_path"]})
    print(probe["name"], len(raw), digest)

path = MINE / "competitions/floatlib/research/deepseek-20261025/verification-import.json"
path.write_text(json.dumps(receipt, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print("receipt:", path)
