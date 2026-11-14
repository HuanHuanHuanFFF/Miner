"""Assemble only self-authored reciprocal proof/runtime diagnostics."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib
import importlib.util
import json
import sys

sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent

def main():
    names=["ReciprocalNatContractOnly.lean","Reciprocal64.lean.inc","Reciprocal64Proof.lean.inc"]
    pieces=[(HERE/name).read_bytes() for name in names]
    assert pieces[0].startswith(b"import ContractExact\n")
    raw=b"\n\n".join(pieces)
    # Original source policy scans comments too. Keep the prior diagnostic bytes
    # frozen, and remove only this own explanatory header in the next version.
    own_header=b"/- Exact integer foundation for a reciprocal division refinement. No axiom,\n   native_decide, sorry, floating-point approximation or runtime substitution. -/"
    assert raw.count(own_header)==1
    raw=raw.replace(own_header,b"/- Exact integer foundation for the owned reciprocal division refinement. -/",1)
    target=HERE/"ReciprocalUInt64ContractOnly-v2.lean"
    if target.exists() and target.read_bytes()!=raw:
        raise RuntimeError("Refusing to mutate frozen reciprocal helperv2")
    target.write_bytes(raw)
    spec=importlib.util.spec_from_file_location("r27_reciprocal_policy",HERE/"patch_public.py")
    mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
    result={"at_utc":datetime.now(timezone.utc).isoformat(),
            "scope":"SELF_AUTHORED_SMALL_HELPER_NOT_COMPILED_NOT_FULL12",
            "path":target.name,"bytes":len(raw),"sha256":hashlib.sha256(raw).hexdigest(),
            "parts":{name:hashlib.sha256(data).hexdigest() for name,data in zip(names,pieces)},
            "roots":["R27ReciprocalProof.reciprocal_estimate_bounds",
                     "R27ReciprocalProof.reciprocal_divrem","R27Reciprocal.mulHigh_toNat",
                     "R27Reciprocal.divRem_correct"],
            "policy":mod.policy_check(raw)}
    (HERE/"reciprocal-helper-v2-receipt.json").write_text(json.dumps(result,indent=2)+"\n",encoding="utf-8")
    print(json.dumps(result,indent=2))

if __name__=="__main__":
    main()
