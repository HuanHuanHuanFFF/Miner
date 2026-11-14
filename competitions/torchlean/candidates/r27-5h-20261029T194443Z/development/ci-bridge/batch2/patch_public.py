"""Reconstruct tiny owned compiler patches over exact official public sources.

This script never republishes the upstream source. Public CI may fetch the exact
official endpoint or use --source; output belongs in ephemeral runner storage.
"""
from pathlib import Path
from types import SimpleNamespace
from urllib.request import Request, urlopen
import argparse
import hashlib
import importlib.util
import json
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
PINS = {
    12: "e2c1f1f1ba52e32563fb193ceea7e2a271b989fd3ba2eb16cff747987879b521",
    27: "f92ee2c9a29de78dc434ad158b7141c0e4b5a67a5a198a353d59a4703481aa67",
}
PATCHES = {
    "inline-linear": [("def YaV (rows inW outW:", "@[inline] def YaV (rows inW outW:")],
    "specialize-linear": [("def YaV (rows inW outW:", "@[specialize relu] def YaV (rows inW outW:")],
    "inline-model": [("def MYbc (rows n:Nat)", "@[inline] def MYbc (rows n:Nat)"),
                     ("def YaV (rows inW outW:", "@[inline] def YaV (rows inW outW:")],
    "min-loop": [],
    "inline-min-loop": [("def YaV (rows inW outW:", "@[inline] def YaV (rows inW outW:")],
    "square-only": [],
    "norm-prep": [],
}

def sha(data):
    return hashlib.sha256(data).hexdigest()

def transform(data, submission, variant):
    assert sha(data) == PINS[submission], "Exact official source mismatch"
    text = data.decode("utf-8")
    for before, after in PATCHES[variant]:
        assert text.count(before) == 1, (variant, before, text.count(before))
        text = text.replace(before, after, 1)
    if variant in {"min-loop", "inline-min-loop", "norm-prep"}:
        assert submission == 12, "Min-loop refinement currently binds exact12 source only"
        marker = "@[inline] def Y8f (x:Array Word)"
        assert text.count(marker) == 1
        text = text.replace(marker, (HERE / "MinIndexLoop.lean.inc").read_text(encoding="utf-8")+"\n"+marker, 1)
        for declaration, end in [("@[inline] def Y8f", "lemma Y8f_eq"), ("@[inline] def YaEf", "lemma YaEf_eq")]:
            start = text.index(declaration)
            stop = text.index(end, start)
            body = text[start:stop]
            before = "let b0:=Y2 x (r*n) n"
            assert body.count(before) == 1
            body = body.replace(before, "let b0:=r27MinIndexLoop x (r*n) n 0 255", 1)
            text = text[:start]+body+text[stop:]
        for before in ["unfold Y8f Y8; dsimp only", "unfold YaEf YaE;dsimp only"]:
            assert text.count(before) == 1, before
            text = text.replace(before, before.replace(";", ";rw[r27MinIndex_eq];", 1), 1)
    if variant in {"square-only", "norm-prep"}:
        assert submission == 12, "Square-only refinement currently binds exact12 source only"
        marker = "@[inline] def Y8f (x:Array Word)"
        assert text.count(marker) == 1
        text = text.replace(marker, (HERE / "SquareOnlyLoop.lean.inc").read_text(encoding="utf-8")+"\n"+marker, 1)
        start = text.index("@[inline] def YaEf")
        stop = text.index("lemma YaEf_eq", start)
        body = text[start:stop]
        before = "let u:=rsU x (r*n) n b0 0 0 0 0 0 0 0 true"
        assert body.count(before) == 1
        body = body.replace(before, "let u:=r27SquareLoop x (r*n) n b0 0 0 0 true", 1)
        assert body.count("u.2.2.2") == 1
        body = body.replace("u.2.2.2", "u.2", 1)
        text = text[:start]+body+text[stop:]
        before = "unfold YaEf YaE;"
        assert text.count(before) == 1
        text = text.replace(before, before+"rw[r27SquareLoop_eq];", 1)
    return text.encode("utf-8")

class MemoryPath:
    def __init__(self, data):
        self.data = data
    def is_file(self):
        return True
    def stat(self):
        return SimpleNamespace(st_size=len(self.data))
    def read_bytes(self):
        return self.data
    def read_text(self):
        return self.data.decode("utf-8")

def policy_check(data):
    loader = ROOT / "competitions/torchlean/candidates/r25-90m-20261029T064916Z/verification/exact-policy-preflight.py"
    spec = importlib.util.spec_from_file_location("r27_public_policy", loader)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    ns, sources = mod.load_official_policy()
    path = MemoryPath(data)
    intake = ns["intake"](path, None)
    policy = ns["policy"](path, None) if intake is None else None
    return {"intake": intake, "policy": policy,
            "passed": intake is None and policy is None, "sources": sources}

def main():
    p = argparse.ArgumentParser()
    p.add_argument("--submission", type=int, choices=sorted(PINS), required=True)
    p.add_argument("--variant", choices=sorted(PATCHES), required=True)
    p.add_argument("--source", type=Path)
    p.add_argument("--output", type=Path)
    p.add_argument("--receipt", type=Path)
    args = p.parse_args()
    url = f"https://conjectures.io/v1/competitions/torchlean/submissions/{args.submission}/source"
    if args.source:
        original = args.source.read_bytes()
    else:
        with urlopen(Request(url, headers={"Accept": "text/plain"}), timeout=45) as resp:
            original = resp.read()
    result = transform(original, args.submission, args.variant)
    report = {
        "id": f"public{args.submission}-{args.variant}",
        "upstream": {"submission": args.submission, "url": url, "sha256": sha(original), "bytes": len(original),
                     "status": "PUBLIC_RETIRED_PREDECESSOR_NOT_CURRENT_CHAMPION", "source_publication": "LOCAL_ONLY"},
        "candidate": {"sha256": sha(result), "bytes": len(result), "entry": "Submission.kernels",
                      "proof_entry": "Submission.correct", "status": ("REFINEMENT_PROOF_NOT_COMPILED_ORIGINAL12_ENTRY_PRESENT"
                          if args.variant in {"min-loop", "inline-min-loop", "square-only", "norm-prep"} else "ORIGINAL_PROOF_UNCHANGED_NOT_REPLAYED")},
        "patch": PATCHES[args.variant], "policy": policy_check(result),
        "semantic_scope": ("RMS square-only native loop omits unused signed first moments; exact projection theorem and original12 correct entry"
                           if args.variant in {"square-only", "norm-prep"} else
                           "Tail-loop minimum exponent refinement with exact fold equivalence; original statistics and sqrt/output unchanged"
                           if "min-loop" in args.variant else "Compiler attributes only; original definitions/proofs unchanged"),
        "native_speed": "UNKNOWN",
    }
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_bytes(result)
    if args.receipt:
        args.receipt.write_text(json.dumps(report, indent=2, ensure_ascii=False)+"\n", encoding="utf-8")
    print(json.dumps(report, indent=2, ensure_ascii=False))

if __name__ == "__main__":
    main()
