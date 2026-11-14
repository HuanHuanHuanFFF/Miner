"""Small deterministic R25 source package; no Lean, Git, or CI invocation."""
from pathlib import Path
from datetime import datetime, timezone
from fractions import Fraction
import hashlib, json, random, re, struct

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
sha = lambda b: hashlib.sha256(b).hexdigest()
main = HERE / "OrderKey.lean"
text = main.read_text(encoding="utf-8")
assert "namespace Submission.R25OrderKey" in text
assert not re.search(r"(?m)^\s*(axiom|unsafe)\b", text)
assert not any(x in text for x in ["sorry", "admit", "native_decide", "bv_decide", "implemented_by", "@[extern"])
core = text.split("noncomputable def magnitudeReal", 1)[0] + "\nend Submission.R25OrderKey\n"
(HERE / "OrderKeyCore.lean").write_text(core, encoding="utf-8", newline="\n")
inc = "\n".join(line for line in text.splitlines() if not line.startswith("import ")) + "\n"
(HERE / "OrderKey.lean.inc").write_text(inc, encoding="utf-8", newline="\n")
(HERE / "OrderKeyContractOnly.lean").write_text("import ContractExact\n" + inc, encoding="utf-8", newline="\n")
core_inc = "\n".join(line for line in core.splitlines() if not line.startswith("import ")) + "\n"
(HERE / "OrderKeyCoreContractOnly.lean").write_text("import ContractExact\n" + core_inc, encoding="utf-8", newline="\n")
roots = ["raw_sign", "raw_exp", "raw_frac", "raw_fields", "field_bounds",
         "magnitude_fields", "magnitude_div", "magnitude_mod", "finite64_iff_exp",
         "finite64_model", "orderKey_nat", "orderKey_lt_cases",
         "magnitudeReal_strictMono", "magnitudeReal_pos_iff", "raw_value",
         "orderKey_lt_real", "value_toBits", "orderKey_toBits_lt_real", "native_ofBits",
         "value_ofBits", "orderKey_native_endpoints"]
files = [HERE / "OrderKeyCore.lean", main, HERE / "OrderKeyContractOnly.lean",
         HERE / "OrderKeyCoreContractOnly.lean", HERE / "OrderKey.lean.inc"]
manifest = dict(
    source_created_at_utc=datetime.now(timezone.utc).isoformat(),
    round="R25", role="order-key", first_tool_utc="2026-10-29T06:52:57Z",
    deadline_utc="2026-10-29T08:19:16Z", status="READY_FOR_FIRST_PINNED_TYPECHECK",
    proof_status="NOT_RUN", axiom_audit="NOT_RUN", kernel_replay="NOT_RUN",
    official_full_gate="NOT_RUN", timing="NOT_RUN", formal_submission="NOT_SUBMITTED",
    local_Lean=False, local_native_build=False, CI_owner="Droot",
    official_commit="accb82b6e2adeda1b41a57a260d68fb3879c427e",
    FloatLib_commit="0d91825727839f597fd06b22fdd038ea21480f0c",
    Lean="v4.34.0", tokens="UNKNOWN", cached_input_tokens="UNKNOWN",
    reasoning_not_double_counted=True,
    carrier=dict(kind="independent proof probe, not a Kernel submission",
        command="lake env lean OrderKeyContractOnly.lean",
        prerequisite="Pinned official TorchLean lean project and built ContractExact import.",
        allowed_imports=["ContractExact"],
        exploratory_probe_imports=[line[7:] for line in text.splitlines() if line.startswith("import ")],
        import_status="Additional imports only retained in original exploratory probe; ContractOnly and no-import include have no broadened import permission."),
    files=[dict(path=p.relative_to(ROOT).as_posix(), bytes=p.stat().st_size,
                sha256=sha(p.read_bytes())) for p in files],
    explicit_axiom_roots=["Submission.R25OrderKey."+x for x in roots],
    allowed_axioms=["propext","Classical.choice","Quot.sound"],
    invariant="The orderKey and finite64 definitions are the exact expressions from PortableF64Dot, modulo namespace.",
    semantic_endpoint="finite64 x && finite64 y; magnitude x != 0 OR magnitude y != 0; actual UInt64 key x < key y implies real(raw x) < real(raw y).",
    included="Raw fields, actual UInt64 XOR branch, normal/subnormal/signed-zero decode, native toBits and finite ofBits bridge.",
    omitted="Producer loop, midpoint construction, radius derivation, full certify soundness, actual Kernel obligations, model timing.")
(HERE / "manifest.json").write_text(json.dumps(manifest, indent=2)+"\n",encoding="utf-8")

# Exact-rational small model and representative binary64 boundary regression.
def decode(w, eb, fb):
    e = (w >> fb) & ((1 << eb)-1)
    f = w & ((1 << fb)-1)
    if e == (1 << eb)-1:
        return None
    bias = (1 << (eb-1))-1
    m, z = (f, 1-bias-fb) if e == 0 else ((1 << fb)+f, e-bias-fb)
    r = Fraction(m << max(z,0), 1 << max(-z,0))
    return -r if w >> (eb+fb) else r
def key(w, eb, fb):
    sign = 1 << (eb+fb)
    return w ^ (((sign << 1)-1) if w & sign else sign)
def verify(eb,fb,words):
    words = sorted(set(words))
    vals = {w:decode(w,eb,fb) for w in words}
    words = [w for w in words if vals[w] is not None]
    tested, zero_ties = 0, []
    for x in words:
        for y in words:
            if key(x,eb,fb)<key(y,eb,fb):
                tested += 1
                if vals[x] == vals[y]:
                    zero_ties.append([x,y])
                elif not vals[x] < vals[y]:
                    raise AssertionError((eb,fb,x,y,vals[x],vals[y]))
                if (x & ((1 << (eb+fb))-1)) or (y & ((1 << (eb+fb))-1)):
                    assert vals[x]<vals[y]
    return dict(exponent_bits=eb,fraction_bits=fb,finite_words=len(words),
                ordered_pairs=tested,equal_value_key_strict_pairs=zero_ties)
small = verify(3,3,range(128))
S, B = 1<<63, 1<<52
edges = [0,1,2,B-2,B-1,B,B+1,(2<<52)-1,2<<52,
         (1022<<52), (1023<<52)-1,1023<<52,(1023<<52)+1,
         (2046<<52), (2047<<52)-2,(2047<<52)-1,2047<<52,(2047<<52)+1]
rng=random.Random(25064916)
words = edges + [S|w for w in edges] + [rng.getrandbits(64) for _ in range(192)]
wide=verify(11,52,words)
assert small["equal_value_key_strict_pairs"] == [[64,0]]
assert wide["equal_value_key_strict_pairs"] == [[S,0]]
receipt=dict(at_utc=datetime.now(timezone.utc).isoformat(),arithmetic="fractions.Fraction, exact",
             scope="finite exhaustive 7-bit toy format; finite binary64 boundary/random sample; not all-input proof",
             small=small,binary64=wide,
             counterexample=dict(left_hex="0x8000000000000000",right_hex="0x0000000000000000",
                 left_key_hex="0x7fffffffffffffff",right_key_hex="0x8000000000000000",
                 left_exact="0",right_exact="0"),
             statement_discrimination="Unconditional finite strict-order equivalence is false. At least one nonzero magnitude removes the observed tie.",
             random_seed=25064916,source_sha256=sha(main.read_bytes()))
(HERE/"small-model.json").write_text(json.dumps(receipt,indent=2)+"\n",encoding="utf-8")
print(json.dumps(dict(files=manifest["files"],roots=len(roots),model=receipt,status="NOT_RUN"),indent=2))

