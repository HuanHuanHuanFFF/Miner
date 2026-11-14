#!/usr/bin/env python3
"""Legacy-fragment-only assembly helper; NOT a fix for candidate600eaaa1.

The supplied actual builders already wire totalWords->finishWords in600e. The
connection below receives no novelty credit. Signed63/zero additions remain
archived uncompiled research drafts, not changes to the frozen native queue.

Output is a local .lean.inc cost-probe fragment, NOT a compiled or Correct
submission. No upstream Kernel, compiler, network, Git, or benchmark is used.
The output still requires the missing predecessor interfaces documented in
REVIEW.md. The package does not redistribute the generated inherited fragment.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re

EXPECTED = {
    "WinogradRuntime.lean.inc": "e4dfeb81848bbb888da1c768629a55f00c925ca998215bfb8d3a8bad39994e00",
    "WinogradNativeFinish.lean.inc": "cf90436483d85868201842949e201622b3a9627eb026550431b8ca5b83c3e0ce",
}


def extract(raw, name):
    escaped = re.escape(name.encode())
    m = re.search(rb"=====BEGIN "+escaped+rb" sha256=([0-9a-f]{64})=====\r?\n(.*?)=====END "+escaped+rb"=====", raw, re.S)
    if not m or m.group(1).decode() != EXPECTED[name]:
        raise ValueError(f"Missing or changed frozen block: {name}")
    # A separator can add blank lines after the hash-covered payload. Only
    # accept a byte-exact SHA match, never normalize code or silently rebase.
    body = m.group(2)
    for count in range(5):
        if count and not body.endswith(b"\n"*count):
            continue
        candidate = body[:-count] if count else body
        if hashlib.sha256(candidate).hexdigest() == EXPECTED[name]:
            return candidate.decode("utf-8")
    raise ValueError(f"Hash mismatch: {name}")


def replace_exact(text, old, new, count=1):
    if text.count(old) != count:
        raise ValueError(f"Patch anchor count changed: expected {count}: {old!r}")
    return text.replace(old, new)


def build(attachment, additions):
    raw = attachment.read_bytes()
    runtime = extract(raw, "WinogradRuntime.lean.inc")
    native = extract(raw, "WinogradNativeFinish.lean.inc")
    new_defs = additions.read_text().split("/- Exact edits to the supplied frozen fragments:", 1)[0]
    if "def crossSigned63" not in new_defs or "def finishZeroBodyOr" not in new_defs:
        raise ValueError("Missing original additions")
    native = replace_exact(native, "def finishWords (X W b", "def finishWords (relu : Bool) (X W b")
    native = replace_exact(native,
        "else R27PackedLinear.exactZero X W b row n col",
        "else finishExactZero relu (fun _ => R27PackedLinear.exactZero X W b row n col)", 2)
    start = native.index("  let top := top128 hi\n")
    end = native.index("\n@[specialize] def totalWords", start)
    body = native[start:end].rstrip("\n")
    native = native[:start]+"  finishZeroBodyOr relu bw hi lo (fun _ =>\n"+"\n".join("  "+s for s in body.splitlines())+")\n"+native[end:]
    native = replace_exact(native,
        "  cross (fun h l => subtract h l a.selfHi a.selfLo fun h l =>",
        "  crossSelected (decide (a.peak+b.peak ≤ 3037000499)) (fun h l => subtract h l a.selfHi a.selfLo fun h l =>")
    runtime = replace_exact(runtime,
        "  else if n == 0 || 1073741824 ≤ n ||",
        "  else if n < 2 || rows < 2 || outW < 2 || rows*outW ≤ rows+outW ||\n    1073741824 ≤ n ||")
    runtime = replace_exact(runtime,
        "        act relu (R27PackedLinear.finish X W b row n col (a.low+w.low) (total a w n))",
        "        act relu (totalWords\n          (fun hi lo => finishWords relu X W b row n col (a.low+w.low) hi lo) a w n)")
    runtime = replace_exact(runtime, "\ndef linear (", "\n"+new_defs+"\n"+native+"\ndef linear (")
    # Static wiring assertions, not Lean elaboration or native verification.
    caller = runtime.split("\ndef linear (", 1)[1]
    assert "(total a w n)" not in caller and "act relu (totalWords" in caller
    assert runtime.count("else finishExactZero relu") == 2
    assert "else act relu (Submission.YaU" in caller  # Downgrade remains explicit.
    return "/- GENERATED COST PROBE: NOT_COMPILED; performance UNKNOWN. -/\n"+runtime


if __name__ == "__main__":
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("attachment", type=Path)
    p.add_argument("--additions", type=Path, default=Path(__file__).with_name("WinogradFollowOn.patch.lean.inc"))
    p.add_argument("--out", type=Path, required=True)
    args = p.parse_args()
    output = build(args.attachment, args.additions)
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(output)
    print(json.dumps({"status": "TEXT_PATCH_APPLIED_ONLY", "lean_status": "NOT_COMPILED",
                      "native_performance": "UNKNOWN", "bytes": len(output.encode()),
                      "sha256": hashlib.sha256(output.encode()).hexdigest()}, indent=2))
