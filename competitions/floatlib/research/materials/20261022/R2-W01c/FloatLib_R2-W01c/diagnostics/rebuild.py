"""Rebuild the single Lean attempt from shipped components; no Lean invocation."""
from pathlib import Path
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
COMP = ROOT / "lean/components"
ORDER = ["AdmissionZero.lean", "NativeProductBridge.lean", "IntegerDyadic.lean",
         "ModelExactProduct.lean", "WordFields.fragment.lean", "NormalIntegration.fragment.lean"]

def body(name):
    text = (COMP / name).read_text()
    first, _, rest = text.partition("\n")
    return rest.lstrip("\n") if first == "import ContractTensor" else text

def build(name, pieces):
    text = "import ContractTensor\n\n" + "\n\n".join(body(p).rstrip() for p in pieces) + "\n"
    target = ROOT / "lean" / name
    target.write_text(text)
    data = target.read_bytes()
    return {"file": str(target.relative_to(ROOT)), "bytes": len(data),
            "sha256": hashlib.sha256(data).hexdigest(), "lean_status": "NOT_RUN"}

if __name__ == "__main__":
    result = [build("NormalEqAttempt.lean", ORDER),
              build("ReusableModel.lean", ["IntegerDyadic.lean", "ModelExactProduct.lean"])]
    (ROOT / "results").mkdir(exist_ok=True)
    (ROOT / "results/build_manifest.json").write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps(result, indent=2))
