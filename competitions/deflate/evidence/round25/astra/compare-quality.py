"""Read archived original-encoder bytes; never combine elapsed times across runs."""
from pathlib import Path
import hashlib
import json

ROOT = Path(__file__).resolve().parents[3]
OUT = Path(__file__).resolve().parent
WANTED = {"combo", "public361", "public443", "public514", "public532", "public539",
          "public552", "public553", "public576", "public579", "public583", "public584",
          "public586", "public591", "public595", "public606", "public607", "public608",
          "public609", "public611", "public614"}


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    records = {}
    disagreements = []
    for round_no in range(18, 25):
        for path in sorted((ROOT / f"evidence/round{round_no}").rglob("encoder.json")):
            doc = json.loads(path.read_bytes())
            rows = doc.get("rows", [])
            for name in WANTED & doc.get("source_hashes", {}).keys():
                selected = sorted((row for row in rows if row["candidate"] == name), key=lambda row: row["file"])
                if len(selected) != 28:
                    continue
                identity = [(row["file"], row["raw_bytes"], row["input_sha256"], row["output_bytes"],
                             row["tokens"], row["tokens_sha256"], row["output_sha256"]) for row in selected]
                item = {"source_hashes": doc["source_hashes"][name], "codec_sha256": doc["codec_sha256"],
                        "token_sha256": doc["token_sha256"], "identity": identity, "rows": selected,
                        "receipts": [{"path": path.relative_to(ROOT).as_posix(), "sha256": digest(path)}]}
                if name in records:
                    old = records[name]
                    for key in ("source_hashes", "codec_sha256", "token_sha256", "identity"):
                        if old[key] != item[key]:
                            disagreements.append({"candidate": name, "key": key, "old": old["receipts"][0],
                                                  "new": item["receipts"][0]})
                    old["receipts"] += item["receipts"]
                else:
                    records[name] = item
    assert not disagreements, disagreements
    base = records["combo"]
    corpus = [(r["file"], r["raw_bytes"], r["input_sha256"]) for r in base["rows"]]
    for name, item in records.items():
        assert item["codec_sha256"] == base["codec_sha256"], name
        assert item["token_sha256"] == base["token_sha256"], name
        assert [(r["file"], r["raw_bytes"], r["input_sha256"]) for r in item["rows"]] == corpus, name
        item["public_size_pct"] = sum(r["output_bytes"] / r["raw_bytes"] * 100 for r in item["rows"]) / 28
        item["total_output_bytes"] = sum(r["output_bytes"] for r in item["rows"])
        item["total_tokens"] = sum(r["tokens"] for r in item["rows"])
        del item["identity"]
        changes = []
        for br, row in zip(base["rows"], item["rows"]):
            saved = br["output_bytes"] - row["output_bytes"]
            changes.append({"file": row["file"], "raw_bytes": row["raw_bytes"],
                            "combo_bytes": br["output_bytes"], "reference_bytes": row["output_bytes"],
                            "bytes_saved_vs_combo": saved,
                            "public_pp_saved_vs_combo": saved / row["raw_bytes"] * 100 / 28,
                            "tokens_delta_vs_combo": row["tokens"] - br["tokens"]})
        item["changes_sorted_by_weighted_gap"] = sorted(changes, key=lambda x: x["public_pp_saved_vs_combo"], reverse=True)
        item["public_pp_saved_vs_combo"] = sum(c["public_pp_saved_vs_combo"] for c in changes)

    ref_paths = {}
    for name, item in records.items():
        if name == "combo":
            path = ROOT / "candidates/r22-595-chain-halfhead/parse.rs"
            assert digest(path) == item["source_hashes"]["parse.rs"]
            ref_paths[name] = path.relative_to(ROOT).as_posix()
        elif name.startswith("public"):
            matches = [p for p in (ROOT / "references").glob(f"*-public-{name[6:]}/parse.rs")
                       if digest(p) == item["source_hashes"]["parse.rs"]]
            ref_paths[name] = [p.relative_to(ROOT).as_posix() for p in matches]
            assert matches, name

    output = {"status": "VERIFIED_ARCHIVED_SAME_INPUT_ORIGINAL_ENCODER_BYTE_COMPARISON",
              "scope": "Archived public28 fixed inputs only. No times compared, no oracle portfolio or formal coordinate claim.",
              "base": "combo", "file_count": 28, "raw_bytes": sum(r["raw_bytes"] for r in base["rows"]),
              "all_receipt_repeats_equal": True, "source_paths": ref_paths, "references": records}
    (OUT / "quality-comparison.json").write_bytes((json.dumps(output, indent=2) + "\n").encode())
    print("name public_size_pct pp_saved_vs_combo total_bytes receipts")
    for name, item in sorted(records.items(), key=lambda x: x[1]["public_size_pct"]):
        print(name, round(item["public_size_pct"], 9), round(item["public_pp_saved_vs_combo"], 9),
              item["total_output_bytes"], len(item["receipts"]))
    for name in ("public539", "public583", "public606", "public608", "public532", "public611", "public609"):
        print("TOP", name)
        print(json.dumps(records[name]["changes_sorted_by_weighted_gap"][:8], ensure_ascii=False))


if __name__ == "__main__":
    main()
