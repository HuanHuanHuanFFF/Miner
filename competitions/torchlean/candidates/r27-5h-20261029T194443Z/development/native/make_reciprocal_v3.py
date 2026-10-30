"""Eliminate a trivial redundant-tactic risk before the first reciprocal CI.

The v2 file stays frozen. Only the prepare_toNat proof becomes a direct use of
the standard toNat_div lemma; every runtime definition is byte-identical.
"""
from pathlib import Path
import hashlib
import importlib.util
import json

HERE=Path(__file__).resolve().parent

def main():
    raw=(HERE/"ReciprocalUInt64ContractOnly-v2.lean").read_bytes()
    assert hashlib.sha256(raw).hexdigest()=="9555634b7ef92dfb7312eaf9b5103ff0034c0dcc81359f62bcb99129797799de"
    before="  unfold prepare\n  rw [UInt64.toNat_div]\n  rfl"
    after="  exact UInt64.toNat_div (0xffffffffffffffff : UInt64) denominator"
    text=raw.decode("utf-8")
    assert text.count(before)==1
    result=text.replace(before,after,1).encode("utf-8")
    spec=importlib.util.spec_from_file_location("r27_reciprocal_proof3_defs",HERE/"repair_norm_prep_v2.py")
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    assert m.runtime_definitions(raw.decode())==m.runtime_definitions(result.decode())
    target=HERE/"ReciprocalUInt64ContractOnly-v3.lean"
    if target.exists() and target.read_bytes()!=result:
        raise RuntimeError("Frozen reciprocalv3 already differs")
    target.write_bytes(result)
    spec=importlib.util.spec_from_file_location("r27_reciprocal_proof3_policy",HERE/"patch_public.py")
    p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p)
    receipt={"id":"reciprocal_u64_v3","sha256":hashlib.sha256(result).hexdigest(),"bytes":len(result),
             "prior_sha256":hashlib.sha256(raw).hexdigest(),"runtime_definition_bytes_identical":True,
             "delta":"prepare_toNat uses standardtoNat_div directly, avoiding rw+rfl NoGoals pattern seen in actualbatch2",
             "scope":"PROOF_ONLY_STATIC_REPAIR_NOT_COMPILED_NO_NEW_RUNTIME_VARIANT",
             "policy":p.policy_check(result)}
    (HERE/"reciprocal-helper-v3-receipt.json").write_text(json.dumps(receipt,indent=2)+"\n",encoding="utf-8")
    print(json.dumps(receipt,indent=2))

if __name__=="__main__":
    main()
