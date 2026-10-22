#!/usr/bin/env python3
"""Limited raw-text checks. This does not invoke or replace the official policy.

The selected restrictions were checked against the public gate.py at
978cc5b445edb9943fd9953b0a9037d97a9f33a8. This is a separately written checker.
Statement checking, dependency checking, Lean kernel checking, compilation,
and benchmark execution are not performed.
"""

import argparse
import hashlib
import json
import re
from pathlib import Path

FORBIDDEN_WORDS = """
sorry admit native_decide axiom implemented_by extern export csimp init initialize
builtin_initialize run_cmd run_elab run_meta macro macro_rules elab elab_rules
syntax attribute IO include_str include_bytes includeStr run_tac
declare_simp_like_tactic
""".split()
BANNED = re.compile("|".join(
    [r"\b" + re.escape(word) + r"\b" for word in FORBIDDEN_WORDS]
    + ["unsafe", "Unchecked", "dbg", "simproc", r"\bregister_\w+",
       r"\w+_elab\b", r"\w*_syntax_\w*", r"#[a-z_]+"]
))
ATTRIBUTES = {"inline", "noinline", "always_inline", "specialize", "simp", "reducible", "irreducible"}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("candidate", type=Path)
    args = parser.parse_args()
    data = args.candidate.read_bytes()
    text = data.decode("utf-8")
    findings = []
    if len(data) > 256000:
        findings.append("file exceeds 256000 bytes")
    import_lines = [line for line in text.splitlines() if re.search(r"\bimport\b", line)]
    if import_lines != ["import ContractTensor"]:
        findings.append("expected exactly one import line: import ContractTensor")
    findings.extend(
        f"pattern match {match.group(0)!r} at line {text.count(chr(10), 0, match.start()) + 1}"
        for match in BANNED.finditer(text)
    )
    if re.search(r"\bset_option\b", text):
        findings.append("this draft is expected to contain no set_option command")
    for group in re.findall(r"@\[([^\]]*)\]", text):
        for item in group.split(","):
            name = item.split()[-1] if item.split() else ""
            if name not in ATTRIBUTES:
                findings.append(f"unlisted attribute {item!r}")
    result = {
        "status": "TEXT_CHECK_PASS" if not findings else "TEXT_CHECK_FAIL",
        "official_policy": "NOT_RUN",
        "official_gate": "NOT_RUN",
        "lean_compile": "NOT_RUN",
        "utf8_bytes": len(data),
        "sha256": hashlib.sha256(data).hexdigest(),
        "lines": len(text.splitlines()),
        "theorem_count": len(re.findall(r"^theorem\s+", text, re.M)),
        "findings": findings,
    }
    print(json.dumps(result, ensure_ascii=False, indent=2))
    return bool(findings)


if __name__ == "__main__":
    raise SystemExit(main())
