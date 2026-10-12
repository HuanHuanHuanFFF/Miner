#!/usr/bin/env python3
"""Offline static lineage audit for public DEFLATE sources #652 and #658.

Scans every public reference parse.rs and every existing candidate parse.rs,
checks source-receipt hashes (where present), and compares function signatures,
function bodies, whole-source token streams, and syntactic call closures. It
does not access the network, private source, CI, or Git.
"""
from __future__ import annotations

import bisect
import collections
import difflib
import hashlib
import json
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "evidence/round26/extension4h/new-source-audit"
CAPTURE = ROOT / "evidence/round26/extension4h/public-new-0735"
TARGETS = ("652", "658")
FOCUS_IDS = {"552", "628", "609", "595", "601", "641"}
MULTI = ("...", "..=", "::", "->", "=>", "==", "!=", "<=", ">=", "&&", "||", "<<", ">>", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "..")
RAW_STRING_START = re.compile(r"(?:br|r)(#+)?\"")


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def token_stream(source: str, with_spans: bool = False) -> list:
    """Lex enough Rust to ignore comments/formatting and balance function bodies."""
    out: list = []
    n = len(source)
    i = 0

    def emit(value: str, start: int, end: int) -> None:
        out.append((value, start, end) if with_spans else value)

    while i < n:
        c = source[i]
        if c.isspace():
            i += 1
            continue
        if source.startswith("//", i):
            j = source.find("\n", i + 2)
            i = n if j < 0 else j + 1
            continue
        if source.startswith("/*", i):
            depth = 1
            i += 2
            while i < n and depth:
                if source.startswith("/*", i):
                    depth += 1
                    i += 2
                elif source.startswith("*/", i):
                    depth -= 1
                    i += 2
                else:
                    i += 1
            continue
        # Rust raw string: r###"..."### or br###"..."###.
        raw = RAW_STRING_START.match(source, i)
        if raw:
            hashes = raw.group(1) or ""
            start = i
            i += raw.end()
            terminator = '"' + hashes
            end = source.find(terminator, i)
            i = n if end < 0 else end + len(terminator)
            emit("STR:" + sha(source[start:i].encode("utf-8")), start, i)
            continue
        if c == '"':
            start = i
            i += 1
            while i < n:
                if source[i] == "\\":
                    i += 2
                elif source[i] == '"':
                    i += 1
                    break
                else:
                    i += 1
            emit("STR:" + sha(source[start:i].encode("utf-8")), start, i)
            continue
        if c == "'":
            # A character literal is short and closed; an apostrophe followed
            # by an identifier is a lifetime and remains punctuation + name.
            end = None
            if i + 1 < n and source[i + 1] == "\\":
                k = i + 2
                while k < min(n, i + 14):
                    if source[k] == "\\":
                        k += 2
                    elif source[k] == "'":
                        end = k + 1
                        break
                    else:
                        k += 1
            elif i + 2 < n and source[i + 2] == "'":
                end = i + 3
            if end is not None:
                emit("CHAR:" + sha(source[i:end].encode("utf-8")), i, end)
                i = end
            else:
                emit("'", i, i + 1)
                i += 1
            continue
        if c.isalpha() or c == "_":
            j = i + 1
            while j < n and (source[j].isalnum() or source[j] == "_"):
                j += 1
            emit(source[i:j], i, j)
            i = j
            continue
        if c.isdigit():
            j = i + 1
            while j < n and (source[j].isalnum() or source[j] in "_.'"):
                j += 1
            emit(source[i:j], i, j)
            i = j
            continue
        op = next((item for item in MULTI if source.startswith(item, i)), None)
        if op:
            emit(op, i, i + len(op))
            i += len(op)
        else:
            emit(c, i, i + 1)
            i += 1
    return out


def digest_tokens(tokens: list[str] | tuple[str, ...]) -> str:
    return sha("\x1f".join(tokens).encode("utf-8"))


def matching_open(tokens: list[str], close_at: int) -> int | None:
    pairs = {")": "(", "]": "[", "}": "{"}
    close = tokens[close_at]
    if close not in pairs:
        return None
    depth = 0
    for j in range(close_at, -1, -1):
        if tokens[j] == close:
            depth += 1
        elif tokens[j] == pairs[close]:
            depth -= 1
            if depth == 0:
                return j
    return None


def declaration_prefix(tokens: list[str], fn_at: int) -> list[str]:
    """Capture visibility/modifiers and contiguous attributes preceding fn."""
    j = fn_at - 1
    prefix: list[str] = []
    modifiers = {"pub", "async", "unsafe", "const", "default", "extern"}
    while j >= 0:
        if tokens[j].startswith("STR:") and j > 0 and tokens[j - 1] == "extern":
            prefix[0:0] = tokens[j - 1 : j + 1]
            j -= 2
            continue
        if tokens[j] in modifiers:
            prefix.insert(0, tokens[j])
            j -= 1
            continue
        if tokens[j] == ")":
            opening = matching_open(tokens, j)
            if opening is not None and opening > 0 and tokens[opening - 1] == "pub":
                prefix[0:0] = tokens[opening - 1 : j + 1]
                j = opening - 2
                continue
        break
    while j >= 1 and tokens[j] == "]" and tokens[j - 1] != "#":
        opening = matching_open(tokens, j)
        if opening is None or opening == 0 or tokens[opening - 1] != "#":
            break
        prefix[0:0] = tokens[opening - 1 : j + 1]
        j = opening - 2
    return prefix


def find_body_open(tokens: list[str], after_fn_name: int) -> int | None:
    paren = bracket = angle = nested_brace = 0
    for j in range(after_fn_name, len(tokens)):
        t = tokens[j]
        if t == "(" :
            paren += 1
        elif t == ")":
            paren = max(0, paren - 1)
        elif t == "[":
            bracket += 1
        elif t == "]":
            bracket = max(0, bracket - 1)
        elif t == "<":
            angle += 1
        elif t == ">":
            angle = max(0, angle - 1)
        elif t == "{" and paren == 0 and bracket == 0 and angle == 0 and nested_brace == 0:
            return j
        elif t == "{" :
            nested_brace += 1
        elif t == "}" and nested_brace:
            nested_brace -= 1
        elif t == ";" and paren == 0 and bracket == 0 and angle == 0 and nested_brace == 0:
            return None
    return None


def parse_functions(source: str, with_tokens: bool = False) -> list[dict]:
    located = token_stream(source, with_spans=True)
    toks = [row[0] for row in located]
    starts = [0]
    starts.extend(i + 1 for i, ch in enumerate(source) if ch == "\n")
    result: list[dict] = []
    counts: collections.Counter[str] = collections.Counter()
    for i, t in enumerate(toks[:-1]):
        if t != "fn" or not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", toks[i + 1]):
            continue
        name = toks[i + 1]
        open_at = find_body_open(toks, i + 2)
        if open_at is None:
            continue
        depth = 1
        close_at = open_at + 1
        while close_at < len(toks) and depth:
            if toks[close_at] == "{":
                depth += 1
            elif toks[close_at] == "}":
                depth -= 1
            close_at += 1
        if depth:
            continue
        body_tokens = toks[open_at + 1 : close_at - 1]
        sig_tokens = declaration_prefix(toks, i) + toks[i:open_at]
        occurrence_index = counts[name]
        counts[name] += 1
        char_start = located[i][1]
        line = bisect.bisect_right(starts, char_start)
        raw_body = source[located[open_at][2] : located[close_at - 1][1]]
        row = {
            "name": name,
            "occurrence": counts[name],
            "line": line,
            "signature_sha256": digest_tokens(sig_tokens),
            "signature_tokens": sig_tokens,
            "body_sha256": sha(raw_body.encode("utf-8")),
            "body_token_sha256": digest_tokens(body_tokens),
            "body_token_count": len(body_tokens),
            "body_bytes": len(raw_body.encode("utf-8")),
        }
        if with_tokens:
            row["body_tokens"] = body_tokens
            row["signature"] = " ".join(sig_tokens)
        result.append(row)
    return result


def source_record(path: Path, kind: str, label: str, with_tokens: bool = False) -> dict:
    raw = path.read_bytes()
    source = raw.decode("utf-8")
    toks = token_stream(source)
    funcs = parse_functions(source, with_tokens=with_tokens)
    return {
        "path": path,
        "kind": kind,
        "label": label,
        "bytes": len(raw),
        "sha256": sha(raw),
        "token_sha256": digest_tokens(toks),
        "tokens": toks,
        "functions": funcs,
        "function_count": len(funcs),
    }


def compare_functions(left: list[dict], right: list[dict]) -> dict:
    """Compare target(left) to possible ancestor(right), pairing overloads by identity first."""
    lmap: dict[str, list[dict]] = collections.defaultdict(list)
    rmap: dict[str, list[dict]] = collections.defaultdict(list)
    for row in left:
        lmap[row["name"]].append(row)
    for row in right:
        rmap[row["name"]].append(row)
    same_body = same_signature = 0
    changed: list[dict] = []
    common_names = set(lmap) & set(rmap)
    for name in sorted(common_names):
        remain = list(rmap[name])
        for lrow in lmap[name]:
            match = next((r for r in remain if r["body_token_sha256"] == lrow["body_token_sha256"]), None)
            if match is None:
                match = next((r for r in remain if r["signature_sha256"] == lrow["signature_sha256"]), None)
            if match is None and remain:
                match = remain[0]
            if match is None:
                continue
            remain.remove(match)
            body_equal = lrow["body_token_sha256"] == match["body_token_sha256"]
            sig_equal = lrow["signature_sha256"] == match["signature_sha256"]
            same_body += int(body_equal)
            same_signature += int(sig_equal)
            if not body_equal or not sig_equal:
                changed.append({
                    "name": name,
                    "target_line": lrow["line"],
                    "ancestor_line": match["line"],
                    "signature_equal": sig_equal,
                    "body_equal": body_equal,
                    "target_signature_sha256": lrow["signature_sha256"],
                    "ancestor_signature_sha256": match["signature_sha256"],
                    "target_body_sha256": lrow["body_sha256"],
                    "ancestor_body_sha256": match["body_sha256"],
                    "target_body_token_sha256": lrow["body_token_sha256"],
                    "ancestor_body_token_sha256": match["body_token_sha256"],
                    "target_body_tokens": lrow["body_token_count"],
                    "ancestor_body_tokens": match["body_token_count"],
                })
    lnames, rnames = set(lmap), set(rmap)
    left_counter = collections.Counter((f["name"], f["body_token_sha256"]) for f in left)
    right_counter = collections.Counter((f["name"], f["body_token_sha256"]) for f in right)
    matched_body_tokens = 0
    right_by_key = {(f["name"], f["body_token_sha256"]): f for f in right}
    for key, count in (left_counter & right_counter).items():
        matched_body_tokens += count * right_by_key[key]["body_token_count"]
    target_body_tokens = sum(f["body_token_count"] for f in left)
    return {
        "target_function_count": len(left),
        "ancestor_function_count": len(right),
        "common_function_names": len(common_names),
        "same_body_functions": same_body,
        "same_signature_functions": same_signature,
        "target_body_token_coverage": (matched_body_tokens / target_body_tokens) if target_body_tokens else 1.0,
        "new_function_names": sorted(lnames - rnames),
        "removed_function_names": sorted(rnames - lnames),
        "changed_common_functions": changed,
        "changed_common_function_count": len(changed),
    }


def file_similarity(left: dict, right: dict) -> dict:
    lc = collections.Counter(left["tokens"])
    rc = collections.Counter(right["tokens"])
    overlap = sum((lc & rc).values())
    lt, rt = len(left["tokens"]), len(right["tokens"])
    fc = compare_functions(left["functions"], right["functions"])
    return {
        "target": left["label"],
        "ancestor": right["label"],
        "target_sha256": left["sha256"],
        "ancestor_sha256": right["sha256"],
        "exact_bytes": left["sha256"] == right["sha256"],
        "exact_token_stream": left["token_sha256"] == right["token_sha256"],
        "target_tokens": lt,
        "ancestor_tokens": rt,
        "shared_token_multiset": overlap,
        "target_token_retained": overlap / lt if lt else 1.0,
        "ancestor_token_retained": overlap / rt if rt else 1.0,
        "token_multiset_dice": 2 * overlap / (lt + rt) if lt + rt else 1.0,
        **fc,
    }


def reference_receipt(path: Path, rec: dict) -> dict:
    receipt_path = path.parent / "source-receipt.json"
    result = {"path": str(receipt_path.relative_to(ROOT)).replace("\\", "/"), "present": receipt_path.exists()}
    if not receipt_path.exists():
        return result
    receipt = json.loads(receipt_path.read_text(encoding="utf-8"))
    files = receipt.get("files", {})
    checks = {}
    for name in ("parse.rs", "Parse.lean"):
        fpath = path.parent / name
        expected = files.get(name, {}).get("sha256") if isinstance(files.get(name), dict) else None
        if fpath.exists() and expected:
            checks[name] = {"expected": expected, "actual": sha(fpath.read_bytes()), "match": expected == sha(fpath.read_bytes())}
    result.update({"id": str(receipt.get("id", "")), "author_hotkey": receipt.get("author_hotkey"), "file_checks": checks,
                   "source_metrics_present": bool(receipt.get("metrics"))})
    return result


def capture_integrity(target_id: str, rec: dict) -> dict:
    folder = ROOT / f"references/round26-public-{target_id}"
    src_receipt = json.loads((folder / "source-receipt.json").read_text(encoding="utf-8"))
    capture_receipts = json.loads((CAPTURE / "receipt.json").read_text(encoding="utf-8"))
    cap_row = next(x for x in capture_receipts if str(x.get("id")) == target_id)
    raw_path = CAPTURE / f"{target_id}.response.json"
    raw_bytes = raw_path.read_bytes()
    raw_obj = json.loads(raw_bytes.decode("utf-8"))
    parse_bytes = (folder / "parse.rs").read_bytes()
    lean_bytes = (folder / "Parse.lean").read_bytes()
    raw_parse = raw_obj["parse_rs"].encode("utf-8")
    raw_lean = raw_obj["proof_lean"].encode("utf-8")
    checks = {
        "capture_id_matches": str(cap_row.get("id")) == target_id == str(src_receipt.get("id")),
        "capture_author_matches_reference_receipt": cap_row.get("author_hotkey") == src_receipt.get("author_hotkey"),
        "capture_metrics_match_reference_receipt": cap_row.get("metrics") == src_receipt.get("metrics"),
        "raw_parse_equals_reference_bytes": raw_parse == parse_bytes,
        "raw_lean_equals_reference_bytes": raw_lean == lean_bytes,
        "raw_parse_sha256_matches_receipt": sha(raw_parse) == src_receipt["files"]["parse.rs"]["sha256"],
        "raw_lean_sha256_matches_receipt": sha(raw_lean) == src_receipt["files"]["Parse.lean"]["sha256"],
        "raw_parse_bytes_match_receipt": len(raw_parse) == src_receipt["files"]["parse.rs"]["bytes"],
        "raw_lean_bytes_match_receipt": len(raw_lean) == src_receipt["files"]["Parse.lean"]["bytes"],
    }
    return {
        "target_id": target_id,
        "author_hotkey": src_receipt.get("author_hotkey"),
        "snapshot_id": src_receipt.get("snapshot_id"),
        "request_start_utc": src_receipt.get("request_start_utc"),
        "request_end_utc": src_receipt.get("request_end_utc"),
        "http_status": src_receipt.get("http_status"),
        "source_receipt_sha256": sha((folder / "source-receipt.json").read_bytes()),
        "parse_sha256": sha(parse_bytes),
        "parse_bytes": len(parse_bytes),
        "lean_sha256": sha(lean_bytes),
        "lean_bytes": len(lean_bytes),
        "raw_response_path": str(raw_path.relative_to(ROOT)).replace("\\", "/"),
        "raw_response_sha256": sha(raw_bytes),
        "raw_response_bytes": len(raw_bytes),
        "checks": checks,
        "all_checks_pass": all(checks.values()),
    }


def call_graph(functions: list[dict]) -> dict[str, set[str]]:
    names = {f["name"] for f in functions}
    graph: dict[str, set[str]] = collections.defaultdict(set)
    for row in functions:
        toks = row.get("body_tokens", [])
        for i, t in enumerate(toks[:-1]):
            if t not in names:
                continue
            # Ignore method calls, which are not statically resolved here.
            if i and toks[i - 1] == ".":
                continue
            call = toks[i + 1] == "("
            if not call and i + 2 < len(toks) and toks[i + 1] == "::" and toks[i + 2] == "<":
                depth = 0
                j = i + 2
                while j < len(toks):
                    if toks[j] == "<":
                        depth += 1
                    elif toks[j] == ">":
                        depth -= 1
                    elif toks[j] == ">>":
                        depth -= 2
                    if depth <= 0:
                        call = j + 1 < len(toks) and toks[j + 1] == "("
                        break
                    j += 1
            if call:
                graph[row["name"]].add(t)
    return graph


def reachable(graph: dict[str, set[str]], root: str) -> list[str]:
    seen: set[str] = set()
    pending = [root]
    while pending:
        name = pending.pop()
        if name in seen:
            continue
        seen.add(name)
        pending.extend(graph.get(name, set()) - seen)
    return sorted(seen)


def route_comparison(target: dict, ancestor: dict) -> dict:
    tg = call_graph(target["functions"])
    ag = call_graph(ancestor["functions"])
    roots = ("parse", "bulk_parse", "bulk_parse_fallback", "compress", "lz77")
    root_rows = {}
    for name in roots:
        if name in tg or name in ag:
            root_rows[name] = {
                "target_calls": sorted(tg.get(name, set())),
                "ancestor_calls": sorted(ag.get(name, set())),
                "added_calls": sorted(tg.get(name, set()) - ag.get(name, set())),
                "removed_calls": sorted(ag.get(name, set()) - tg.get(name, set())),
            }
    tc = set(reachable(tg, "parse")) if "parse" in tg else set()
    ac = set(reachable(ag, "parse")) if "parse" in ag else set()
    tfunc = {f["name"]: f for f in target["functions"]}
    afunc = {f["name"]: f for f in ancestor["functions"]}
    shared = tc & ac
    changed_active = sorted(n for n in shared if n in tfunc and n in afunc and tfunc[n]["body_token_sha256"] != afunc[n]["body_token_sha256"])
    return {
        "entrypoint_direct_calls": root_rows,
        "target_parse_possible_closure": sorted(tc),
        "ancestor_parse_possible_closure": sorted(ac),
        "parse_closure_added_functions": sorted(tc - ac),
        "parse_closure_removed_functions": sorted(ac - tc),
        "parse_closure_shared_same_body_count": len(shared - set(changed_active)),
        "parse_closure_shared_changed_body_functions": changed_active,
        "target_bulk_parse_possible_closure": reachable(tg, "bulk_parse") if "bulk_parse" in tg else [],
        "ancestor_bulk_parse_possible_closure": reachable(ag, "bulk_parse") if "bulk_parse" in ag else [],
        "limits": ["Syntactic direct calls only; method dispatch, macros, function pointers, actual branch conditions and source-file routing are not resolved.",
                   "Possible closure includes every syntactic branch and does not establish runtime reachability."],
    }


def active_closure_comparison(target: dict, reference: dict, reference_path: Path) -> dict:
    """Compare only function definitions syntactically reachable from parse."""
    ref_source = reference_path.read_text(encoding="utf-8")
    ref_functions = parse_functions(ref_source, with_tokens=True)
    target_graph = call_graph(target["functions"])
    ref_graph = call_graph(ref_functions)
    target_closure = set(reachable(target_graph, "parse")) if "parse" in target_graph else set()
    ref_closure = set(reachable(ref_graph, "parse")) if "parse" in ref_graph else set()
    tfunc = {f["name"]: f for f in target["functions"] if f["name"] in target_closure}
    rfunc = {f["name"]: f for f in ref_functions if f["name"] in ref_closure}
    common = set(tfunc) & set(rfunc)
    exact = sorted(n for n in common if tfunc[n]["body_token_sha256"] == rfunc[n]["body_token_sha256"])
    changed = sorted(common - set(exact))
    total_target_tokens = sum(f["body_token_count"] for f in tfunc.values())
    matched_target_tokens = sum(tfunc[n]["body_token_count"] for n in exact)
    return {
        "ancestor": reference["label"],
        "ancestor_sha256": reference["sha256"],
        "target_parse_closure_count": len(target_closure),
        "ancestor_parse_closure_count": len(ref_closure),
        "common_parse_closure_names": len(common),
        "same_body_parse_closure_functions": len(exact),
        "changed_body_parse_closure_functions": changed,
        "target_active_body_token_coverage": matched_target_tokens / total_target_tokens if total_target_tokens else 1.0,
        "target_parse_closure_only": sorted(target_closure - ref_closure),
        "ancestor_parse_closure_only": sorted(ref_closure - target_closure),
        "entrypoint_direct_calls": {
            name: {"target": sorted(target_graph.get(name, set())), "ancestor": sorted(ref_graph.get(name, set()))}
            for name in ("parse", "bulk_parse", "route") if name in target_graph or name in ref_graph
        },
    }


def const_census(source: str) -> dict[str, str]:
    toks = token_stream(source)
    result: dict[str, str] = {}
    for i in range(len(toks) - 2):
        if toks[i] != "pub" or toks[i + 1] not in ("const", "static"):
            continue
        name = toks[i + 2]
        if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", name):
            continue
        j = i + 3
        paren = bracket = brace = angle = 0
        while j < len(toks):
            t = toks[j]
            if t == "(" : paren += 1
            elif t == ")": paren = max(0, paren - 1)
            elif t == "[": bracket += 1
            elif t == "]": bracket = max(0, bracket - 1)
            elif t == "{": brace += 1
            elif t == "}": brace = max(0, brace - 1)
            elif t == "<": angle += 1
            elif t == ">": angle = max(0, angle - 1)
            elif t == ";" and not (paren or bracket or brace or angle):
                break
            j += 1
        result[name] = digest_tokens(toks[i : min(j + 1, len(toks))])
    return result


def main() -> None:
    OUT.mkdir(parents=True, exist_ok=True)
    ref_records: list[dict] = []
    inventory: list[dict] = []
    for path in sorted((ROOT / "references").glob("*/parse.rs")):
        receipt = reference_receipt(path, {})
        label = f"#receipt-{receipt.get('id') or path.parent.name}"
        rec = source_record(path, "reference", label)
        rec["receipt"] = receipt
        ref_records.append(rec)
        inventory.append({"kind": "reference", "label": label, "path": str(path.relative_to(ROOT)).replace("\\", "/"),
                          "bytes": rec["bytes"], "sha256": rec["sha256"], "token_sha256": rec["token_sha256"],
                          "function_count": rec["function_count"], "receipt_checks": receipt.get("file_checks", {})})

    reference_body_index: dict[str, list[dict]] = collections.defaultdict(list)
    for ref in ref_records:
        for fn in ref["functions"]:
            reference_body_index[fn["body_token_sha256"]].append({
                "reference": ref["label"], "function": fn["name"], "line": fn["line"]})

    target_records = {}
    capture_checks = {}
    for target_id in TARGETS:
        path = ROOT / f"references/round26-public-{target_id}/parse.rs"
        target = source_record(path, "target", f"#{target_id}")
        # Keep exact body tokens for routing analysis; other inputs are parsed
        # one at a time to keep the full candidate scan light.
        target["functions"] = parse_functions(path.read_text(encoding="utf-8"), with_tokens=True)
        target["receipt"] = reference_receipt(path, target)
        target_records[target_id] = target
        capture_checks[target_id] = capture_integrity(target_id, target)

    # Guard against the generic-call omission that would hide the three known
    # parameterized dispatch edges in #658's route table.
    generic_call_assertions = {}
    graph658 = call_graph(target_records["658"]["functions"])
    for caller, callee in (("p125_row8", "pc_run1c"), ("p125_row9", "u118_run"), ("p125_row10", "o_a_main_part")):
        present = callee in graph658.get(caller, set())
        generic_call_assertions[f"{caller}->{callee}"] = present
        if not present:
            raise SystemExit(f"Generic call-graph assertion failed: {caller} -> {callee}")

    ref_comparisons: dict[str, list[dict]] = {}
    best_refs: dict[str, list[dict]] = {}
    active_rankings: dict[str, list[dict]] = {}
    for target_id, target in target_records.items():
        rows = [file_similarity(target, ref) for ref in ref_records if str(ref["receipt"].get("id")) != target_id]
        rows.sort(key=lambda r: (r["target_token_retained"], r["target_body_token_coverage"], r["same_body_functions"], r["token_multiset_dice"]), reverse=True)
        ref_comparisons[target_id] = rows
        top = rows[:15]
        focus = [r for r in rows if r["ancestor"].replace("#receipt-", "") in FOCUS_IDS]
        best_refs[target_id] = top + [r for r in focus if r not in top]
        active_rows = []
        for ref in ref_records:
            if str(ref["receipt"].get("id")) == target_id:
                continue
            active_rows.append(active_closure_comparison(target, ref, ref["path"]))
        active_rows.sort(key=lambda r: (r["target_active_body_token_coverage"], r["same_body_parse_closure_functions"], r["common_parse_closure_names"]), reverse=True)
        active_top = active_rows[:12]
        active_focus = [r for r in active_rows if r["ancestor"].replace("#receipt-", "") in FOCUS_IDS]
        active_rankings[target_id] = active_top + [r for r in active_focus if r not in active_top]

    # Prepare exact active-function body probes for the complete local
    # candidate corpus. This is a hash lookup only; no pairwise candidate diff.
    candidate_probe_functions: dict[str, dict[str, dict]] = {}
    wanted_body_hashes: set[str] = set()
    for target_id, target in target_records.items():
        active_label = active_rankings[target_id][0]["ancestor"]
        parent = next(r for r in ref_records if r["label"] == active_label)
        parent["functions"] = parse_functions(parent["path"].read_text(encoding="utf-8"), with_tokens=True)
        route = route_comparison(target, parent)
        names = sorted(set(route["parse_closure_added_functions"]) |
                       set(route["parse_closure_shared_changed_body_functions"]))
        tfunc = {f["name"]: f for f in target["functions"]}
        selected = {name: tfunc[name] for name in names if name in tfunc}
        candidate_probe_functions[target_id] = selected
        wanted_body_hashes.update(f["body_token_sha256"] for f in selected.values())

    # Hash every existing candidate source first. The candidate corpus is much
    # larger than the reference set; only possible exact repeats are opened
    # beyond byte hashing in this bounded audit.
    candidate_total = 0
    candidate_function_body_matches: dict[str, list[dict]] = {target_id: [] for target_id in TARGETS}
    candidate_exact = {target_id: [] for target_id in TARGETS}
    for path in sorted((ROOT / "candidates").rglob("parse.rs")):
        candidate_total += 1
        raw = path.read_bytes()
        candidate_hash = sha(raw)
        candidate_source = raw.decode("utf-8")
        for fn in parse_functions(candidate_source):
            body_hash = fn["body_token_sha256"]
            if body_hash in wanted_body_hashes:
                for target_id, selected in candidate_probe_functions.items():
                    for target_name, target_fn in selected.items():
                        if target_fn["body_token_sha256"] == body_hash:
                            candidate_function_body_matches[target_id].append({
                                "target_function": target_name,
                                "target_body_token_sha256": body_hash,
                                "candidate_path": str(path.relative_to(ROOT)).replace("\\", "/"),
                                "candidate_function": fn["name"],
                                "candidate_line": fn["line"],
                            })
        for target_id, target in target_records.items():
            if candidate_hash == target["sha256"]:
                candidate_exact[target_id].append(str(path.relative_to(ROOT)).replace("\\", "/"))
        inventory.append({"kind": "candidate", "label": path.parent.name, "path": str(path.relative_to(ROOT)).replace("\\", "/"),
                          "bytes": len(raw), "sha256": candidate_hash})

    # Full source and focused function diffs for the strongest reference matches.
    full_diffs = []
    route_data = {}
    constant_changes = {}
    for target_id, target in target_records.items():
        top = best_refs[target_id][:3]
        if not top:
            continue
        target_source = target["path"].read_text(encoding="utf-8")
        route_data[target_id] = {}
        constant_changes[target_id] = {}
        for rank, chosen in enumerate(top, start=1):
            ancestor_id = chosen["ancestor"].replace("#receipt-", "")
            ancestor_record = next(r for r in ref_records if r["label"] == chosen["ancestor"])
            ancestor_source = ancestor_record["path"].read_text(encoding="utf-8")
            diff = list(difflib.unified_diff(ancestor_source.splitlines(), target_source.splitlines(),
                                             fromfile=ancestor_record["label"] + "/parse.rs",
                                             tofile=f"#{target_id}/parse.rs", lineterm="", n=3))
            diff_path = OUT / f"public-{target_id}-vs-{ancestor_id}.diff"
            diff_path.write_text("\n".join(diff) + ("\n" if diff else ""), encoding="utf-8")
            full_diffs.append({"target": target_id, "rank": rank, "ancestor": ancestor_id,
                               "path": str(diff_path.relative_to(ROOT)).replace("\\", "/"),
                               "lines": len(diff), "sha256": sha(diff_path.read_bytes())})
            ancestor_record["functions"] = parse_functions(ancestor_source, with_tokens=True)
            route = route_comparison(target, ancestor_record)
            tfunc = {f["name"]: f for f in target["functions"]}
            relevant = sorted(set(route["parse_closure_added_functions"]) |
                              set(route["parse_closure_shared_changed_body_functions"]))
            body_matches = {}
            for name in relevant:
                fn = tfunc.get(name)
                if fn is None:
                    continue
                matches = [m for m in reference_body_index.get(fn["body_token_sha256"], [])
                           if m["reference"] not in (f"#receipt-{target_id}", chosen["ancestor"])]
                body_matches[name] = {
                    "body_token_sha256": fn["body_token_sha256"],
                    "exact_body_matches_elsewhere": matches,
                    "exact_body_match_count_elsewhere": len(matches),
                }
            route["active_changed_function_body_matches_across_references"] = body_matches
            route_data[target_id][ancestor_id] = route
            tc = const_census(target_source)
            ac = const_census(ancestor_source)
            constant_changes[target_id][ancestor_id] = {
                "added": {k: tc[k] for k in sorted(set(tc) - set(ac))},
                "removed": {k: ac[k] for k in sorted(set(ac) - set(tc))},
                "changed": {k: {"ancestor": ac[k], "target": tc[k]} for k in sorted(set(tc) & set(ac)) if tc[k] != ac[k]},
            }

        # Also preserve a full diff for the nearest active-closure reference if
        # whole-source and active-path rankings choose different ancestors.
        active_choice = active_rankings[target_id][0]
        active_label = active_choice["ancestor"]
        if not any(x["target"] == target_id and x["ancestor"] == active_label.replace("#receipt-", "") for x in full_diffs):
            active_ref = next(r for r in ref_records if r["label"] == active_label)
            active_source = active_ref["path"].read_text(encoding="utf-8")
            lines = list(difflib.unified_diff(active_source.splitlines(), target_source.splitlines(),
                                              fromfile=active_label + "/parse.rs", tofile=f"#{target_id}/parse.rs",
                                              lineterm="", n=3))
            active_id = active_label.replace("#receipt-", "")
            diff_path = OUT / f"public-{target_id}-vs-{active_id}-active-closure.diff"
            diff_path.write_text("\n".join(lines) + ("\n" if lines else ""), encoding="utf-8")
            full_diffs.append({"target": target_id, "rank": "active-closure-nearest", "ancestor": active_id,
                               "path": str(diff_path.relative_to(ROOT)).replace("\\", "/"),
                               "lines": len(lines), "sha256": sha(diff_path.read_bytes())})

    summary = {
        "status": "VERIFIED_STATIC_SOURCE_LINEAGE_AUDIT",
        "scope": "Offline public-source comparison; no protected source, network, CI, or Git used.",
        "capture_integrity": capture_checks,
        "targets": {
            target_id: {
                "label": target["label"],
                "author_hotkey": target["receipt"].get("author_hotkey"),
                "rust_sha256": target["sha256"],
                "rust_bytes": target["bytes"],
                "lean_sha256": capture_checks[target_id]["lean_sha256"],
                "lean_bytes": capture_checks[target_id]["lean_bytes"],
                "function_count": target["function_count"],
                "token_sha256": target["token_sha256"],
            } for target_id, target in target_records.items()
        },
        "reference_count": len(ref_records),
        "candidate_parse_source_count": candidate_total,
        "generic_call_assertions": generic_call_assertions,
        "focus_reference_ids": sorted(FOCUS_IDS),
        "reference_rankings": best_refs,
        "active_closure_reference_rankings": active_rankings,
        "candidate_scan": "Raw SHA-256/byte count for every candidate parse.rs plus exact body-token hash probes for target active changes; no pairwise candidate diffs.",
        "candidate_exact_byte_matches": candidate_exact,
        "candidate_active_function_body_matches": candidate_function_body_matches,
        "nearest_reference_function_route_data": route_data,
        "nearest_reference_public_constant_changes": constant_changes,
        "full_source_diffs": full_diffs,
        "input_inventory": inventory,
        "method": {
            "function_identity": "Lexically located fn definitions; signatures and bodies use token hashes after comments/whitespace are omitted; literal contents remain represented by hashes.",
            "whole_source_similarity": "Exact byte hash, exact canonical token hash, and token-multiset overlap; top pair also gets a complete line diff.",
            "ancestor_ranking": "Target token retention, then target function-body token coverage, exact body count, and whole-source token Dice. Ranking is a static proximity screen, not proof of authorship lineage.",
            "interpretation_boundary": "Source similarity cannot establish runtime causality, quality, speed, formal acceptance, admission, ranking, or reward. Submission IDs and metrics are not used to infer novelty.",
        },
        "limits": [
            "The lightweight lexer is not a Rust parser; macro-generated functions, conditional compilation, method resolution, and type-level semantics may be missed.",
            "The call graph is syntactic and includes all branches; it does not prove which file classes or branches run.",
            "Token identity ignores whitespace and comments but distinguishes literal content; it is not semantic equivalence.",
            "Candidate scan covers all existing candidates/parse.rs and all reference parse.rs; it does not inspect arbitrary evidence payloads or private/protected source.",
        ],
    }
    if not all(v["all_checks_pass"] for v in capture_checks.values()):
        raise SystemExit("Target capture integrity check failed; see diagnostic JSON inputs before interpretation.")
    if any(not all(x.get("match", True) for x in r.get("file_checks", {}).values()) for r in [rec["receipt"] for rec in ref_records]):
        raise SystemExit("At least one reference source-receipt hash mismatch; inspect inventory.")
    (OUT / "audit.json").write_text(json.dumps(summary, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"status": summary["status"], "targets": summary["targets"],
                      "reference_count": len(ref_records), "candidate_parse_source_count": candidate_total,
                      "capture_integrity": {k: v["all_checks_pass"] for k, v in capture_checks.items()},
                      "generic_call_assertions": generic_call_assertions,
                      "nearest_references": {k: [{key: row.get(key) for key in ("ancestor", "ancestor_sha256", "target_sha256", "target_token_retained", "target_body_token_coverage", "same_body_functions", "common_function_names", "changed_common_function_count")} for row in v[:3]] for k, v in best_refs.items()},
                      "candidate_exact_byte_matches": candidate_exact,
                      "full_source_diffs": full_diffs}, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
