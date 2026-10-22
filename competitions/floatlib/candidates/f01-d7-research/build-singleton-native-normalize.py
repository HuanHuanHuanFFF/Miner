"""Build one n=1 native-product composition; all new Lean remains NOT_RUN."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
from types import SimpleNamespace


HERE = Path(__file__).resolve().parent
CANDIDATES = HERE.parent
TRACK = CANDIDATES.parent
EXPECTED_PARENT = "53d1c2c40642060c970189250ea1aee88c37ba3eb1309b2bcfed1f0fcf9a3fa7"
EXPECTED_97F = "97f77e2ce3f53dc3625349d5d2a7bc761570f9428c0b547070e37254c4960d26"
EXPECTED_SEED = "c44c4afbbe117e97b857ac3541638f3cbee370ba86f837fc76be16c41d08ed26"
EXPECTED_POLICY = "1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194"
EXPECTED_ORACLE = "3dfaeec2bde1364a4f06abd292f0ba265376da79e678d3827aa88bd33219ad72"


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def require(ok, message):
    if not ok:
        raise RuntimeError(message)


def directed_model():
    path = TRACK / "research/astra-collab-20261023-r7/nonfinite-oracle.py"
    source = path.read_bytes()
    require(sha(source) == EXPECTED_ORACLE, "model source differs")
    ns = {"__name__": "singleton_native_model", "__file__": str(path)}
    exec(compile(source, str(path), "exec"), ns)
    # name, x, y, exact product, seeded result
    cases = [
        ("ordinary_positive", 0x3fc00000, 0x40000000, 0x40400000, 0x40400000),
        ("ordinary_negative", 0xbf800000, 0x40000000, 0xc0000000, 0xc0000000),
        ("positive_zero", 0x00000000, 0x3f800000, 0x00000000, 0x00000000),
        ("negative_zero", 0x80000000, 0x3f800000, 0x80000000, 0x00000000),
        ("zero_times_negative", 0x00000000, 0xbf800000, 0x80000000, 0x00000000),
        ("negative_zero_times_negative", 0x80000000, 0xbf800000, 0x00000000, 0x00000000),
        ("negative_underflow", 0x00000001, 0x80000001, 0x80000000, 0x00000000),
        ("smallest_subnormal", 0x00000001, 0x3f800000, 0x00000001, 0x00000001),
        ("normal_to_subnormal", 0x00800000, 0x3f000000, 0x00400000, 0x00400000),
        ("finite_overflow", 0x7f7fffff, 0x40000000, 0x7f800000, 0x7f800000),
        ("infinity_negative", 0x7f800000, 0xbf800000, 0xff800000, 0xff800000),
        ("zero_infinity_invalid", 0x00000000, 0x7f800000, 0x7fc00000, 0x7fc00000),
        ("negative_zero_negative_infinity_invalid", 0x80000000, 0xff800000, 0x7fc00000, 0x7fc00000),
        ("quiet_payload", 0x7fc00001, 0x3f800000, 0x7fc00001, 0x7fc00001),
        ("negative_signaling_payload", 0xff800011, 0x3f800000, 0xffc00011, 0xffc00011),
        ("right_signaling_precedes_left_quiet", 0x7fc01234, 0xff800011, 0xffc00011, 0xffc00011),
    ]
    rows = []
    for name, x, y, expected_product, expected_seeded in cases:
        product = ns["mul"](x, y)
        native = ns["native_model"](ns["mul"], x, y)
        cold = ns["nan"](native)
        selected = product if cold else native
        normalized = 0 if selected == 0x80000000 else selected
        seeded = ns["add"](0, product)
        require(product == expected_product, f"product witness {name}")
        require(selected == product, f"nativeProduct witness {name}")
        require(normalized == seeded == expected_seeded, f"seed witness {name}")
        old_low = ((x >> 23) & 255) + ((y >> 23) & 255) < 128
        rows.append({"name": name, "x": f"0x{x:08x}", "y": f"0x{y:08x}",
                     "exact_product": f"0x{product:08x}", "native_projection": f"0x{native:08x}",
                     "path": "exact_scalar_fallback" if cold else "native_nonNaN",
                     "normalized_result": f"0x{normalized:08x}", "seeded_reference": f"0x{seeded:08x}",
                     "old_scalar_low_guard": old_low, "all_expected_match": True})
    require(len(rows) == 16, "unexpected directed case count")
    return {"status": "PASS_16_DIRECTED_TRANSCRIPTION_ONLY", "source": path.as_posix(),
            "source_sha256": sha(source), "cases": rows,
            "scope": "Shared exact integer word transcription and its canonical native projection only. No Lean, real native execution, generated C or timing.",
            "native_nonNaN_cases": sum(r["path"] == "native_nonNaN" for r in rows),
            "exact_scalar_fallback_cases": sum(r["path"] == "exact_scalar_fallback" for r in rows),
            "old_low_guard_cases_now_native_nonNaN": sum(r["old_scalar_low_guard"] and r["path"] == "native_nonNaN" for r in rows)}


def main():
    started = datetime.now(timezone.utc)
    parent = CANDIDATES / "f01-d7-singleton-normalize/Kernel.lean"
    old97 = CANDIDATES / "f01-d7-direct-nonfinite/Kernel.lean"
    seed_path = HERE / "seed-normalize-block.lean"
    block_path = HERE / "singleton-native-product-block.lean"
    raw, raw97, seed, block = (p.read_bytes() for p in (parent, old97, seed_path, block_path))
    require(sha(raw) == EXPECTED_PARENT and len(raw) == 187374, "frozen53d parent differs")
    require(sha(raw97) == EXPECTED_97F, "97f source differs")
    require(sha(seed) == EXPECTED_SEED and raw.count(seed) == 1, "frozen seed block differs")
    require(block.count(b"def nativeProduct ") == 1 and block.count(b"theorem nativeProduct_eq ") == 1,
            "unexpected helper declarations")

    core_at = raw.index(b"\ndef singletonCore ")
    scope_at = raw.rfind(b"namespace Submission\n", 0, core_at)
    require(scope_at > 0 and raw[scope_at:].count(b"def singletonCore ") == 1, "singleton scope differs")
    tail = raw[scope_at:]
    old_runtime = b"(Submission.mul (A.toArray.getD ((b * m + i) * n + 0) posZero)"
    new_runtime = b"(D7SingletonNative.nativeProduct (A.toArray.getD ((b * m + i) * n + 0) posZero)"
    old_proof = b"  dsimp only\n  rw [D7SeedNormalize.normalize_submission_mul_eq_add]\n"
    new_proof = b"  dsimp only\n  rw [D7SingletonNative.nativeProduct_eq]\n  rw [D7SeedNormalize.normalize_submission_mul_eq_add]\n"
    require(tail.count(old_runtime) == tail.count(old_proof) == 1, "frozen singleton anchors differ")
    adapted = tail.replace(old_runtime, new_runtime, 1).replace(old_proof, new_proof, 1)
    payload = raw[:scope_at] + block + b"\n\n" + adapted
    require(payload[:scope_at] == raw[:scope_at], "parent prefix differs")
    require(adapted.replace(new_runtime, old_runtime, 1).replace(new_proof, old_proof, 1) == tail,
            "singleton inverse transform differs")
    inverse = payload[:scope_at] + payload[scope_at + len(block) + 2:]
    inverse = inverse.replace(new_runtime, old_runtime, 1).replace(new_proof, old_proof, 1)
    require(inverse == raw, "complete inverse transform differs")
    require(payload.count(seed) == 1, "frozen seed block changed")
    core = adapted[:adapted.index(b"\ntheorem singletonCore_eq_reference ")]
    require(core.count(b"D7SingletonNative.nativeProduct ") == 1, "singleton product is duplicated")
    require(b"Submission.mul " not in core, "singleton core still uses scalar entry")
    runtime_helper = block[:block.index(b"\ntheorem nativeProduct_eq ")]
    require(runtime_helper.count(b" * ") == 1 and b"let r :=" in runtime_helper,
            "native product source is duplicated")
    dispatcher = b"  if n = 1 then singletonCore batch m n p A B\n  else bmmBeforeSingleton batch m n p A B"
    require(raw.count(dispatcher) == payload.count(dispatcher) == 1, "dispatcher differs")
    require(len(payload) <= 256000, "candidate exceeds source cap")

    out = CANDIDATES / "f01-d7-singleton-native-normalize"
    out.mkdir(exist_ok=True)
    target = out / "Kernel.lean"
    target.write_bytes(payload)
    policy_path = TRACK / "research/astra-collab-20261023-r7/upstream/gate-4b7e838.py"
    helper_path = HERE / "precheck-plan.py"
    helper = {"__file__": str(helper_path), "__name__": "singleton_policy_helper"}
    exec(compile(helper_path.read_bytes(), str(helper_path), "exec"), helper)
    policy = helper["extract_policy"](policy_path.read_bytes(), EXPECTED_POLICY)
    intake_reason = policy["intake"](target, SimpleNamespace(slot="full"))
    policy_reason = intake_reason or policy["policy"](target, SimpleNamespace(slot="full"))
    require(policy_reason is None, f"exact original intake/policy rejected: {policy_reason}")
    models = directed_model()
    require(parent.read_bytes() == raw and old97.read_bytes() == raw97 and seed_path.read_bytes() == seed,
            "frozen inputs changed during build")
    static = {"status": "PASS_STATIC_ONLY", "complete_inverse_equals53d": True,
              "parent_prefix_unchanged_bytes": scope_at, "seed_block_unchanged": True,
              "n_not_one_dispatcher_unchanged": True, "raw_addresses_unchanged": True,
              "one_helper_call_in_singleton_core": True, "one_native_multiply_expression_in_helper": True,
              "intake_reason": intake_reason, "policy_reason": policy_reason,
              "policy_source": policy_path.as_posix(), "policy_sha256": EXPECTED_POLICY,
              "policy_functions": ["intake", "options", "policy"],
              "policy_helper_sha256": sha(helper_path.read_bytes())}
    manifest = {"candidate": out.name, "candidate_file": "Kernel.lean", "candidate_sha256": sha(payload),
                "candidate_bytes": len(payload), "created_at_utc": datetime.now(timezone.utc).isoformat(),
                "parent": parent.parent.name, "parent_sha256": EXPECTED_PARENT,
                "layout_and_fallback_base": old97.parent.name, "layout_and_fallback_base_sha256": EXPECTED_97F,
                "native_product_block_sha256": sha(block), "frozen_seed_block_sha256": EXPECTED_SEED,
                "builder_sha256": sha(Path(__file__).read_bytes()), "validation_mode": "statement-only",
                "proof_status": "NOT_RUN_NATIVE_HELPER_AND_SINGLETON_COMPOSITION",
                "full_gate_status": "NOT_RUN", "C_asm_status": "NOT_RUN", "performance_status": "NOT_RUN",
                "mechanism": "Only n=1 uses one bound native product. A nonNaN product imports directly and bypasses Submission.mul including the low-exponent guard. A NaN product uses the exact original Submission.mul. The unchanged raw negative-zero normalizer consumes the selected product once.",
                "proof_route": "nativeProduct_eq uses existing mul_inputs, R7Native.ofFloat32Mul, both nonNaN roundtrips and Submission.mul_eq. Singleton proof rewrites nativeProduct_eq before the frozen normalize_submission_mul_eq_add bridge.",
                "cost_boundary": "Source has one native multiply expression; NaN fallback still pays that initial native product plus exact scalar fallback. Normalizer/raw wrapping and guard costs remain. No whole-cost gain is inferred.",
                "static_validation": static, "finite_model_status": models["status"], "gain": "UNKNOWN",
                "formal_submission": "NOT_SUBMITTED", "publication": "NOT_UPLOADED_BY_THIS_BUILD"}
    (out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    design = {"status": "PREPARED_NOT_RUN", "build_started_at_utc": started.isoformat(),
              "build_finished_at_utc": datetime.now(timezone.utc).isoformat(), "candidate": manifest,
              "block": {"path": block_path.as_posix(), "bytes": len(block), "sha256": sha(block)},
              "sources": {"53d_parent": {"path": parent.as_posix(), "bytes": len(raw), "sha256": sha(raw)},
                          "97f_base": {"path": old97.as_posix(), "bytes": len(raw97), "sha256": sha(raw97)},
                          "frozen_seed": {"path": seed_path.as_posix(), "bytes": len(seed), "sha256": sha(seed)}},
              "directed_model": models,
              "scope": {"new_candidate_count": 1, "old_sources_modified": False, "R_modified": False,
                        "Git_modified": False, "CI": False, "uploads": False, "toolchain_install": False,
                        "new_Lean": "NOT_RUN", "fullgate": "NOT_RUN", "actual_C_performance": "NOT_RUN"}}
    (HERE / "singleton-native-normalize-design.json").write_text(json.dumps(design, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"candidate": out.name, "sha256": sha(payload), "bytes": len(payload),
                      "static_policy": "PASS", "inverse": "PASS", "model_cases": len(models["cases"]),
                      "Lean": "NOT_RUN", "fullgate": "NOT_RUN", "performance": "UNKNOWN"}))


if __name__ == "__main__":
    main()
