"""Per-sample champion projection ratios for the retained df5c model."""
import json
from pathlib import Path

P = Path(r"D:\CodingProject\Bitget-DeepSeek\competitions\floatlib\candidates"
         r"\f01-d7-research\champion-time-estimate.json")
d = json.loads(P.read_text(encoding="utf-8"))
ops = ("add", "mul", "sum", "bmm")
print(f"{'run':>12s} {'seed':>7s} " + " ".join(f"{o:>7s}" for o in ops) + "   whole")
for s in d["samples"]:
    c = s["candidate_total_ns"]
    ch = s["champion_projected_total_ns"]
    row = " ".join(f"{c[o]/ch[o]:7.3f}" for o in ops)
    whole = sum(c.values()) / sum(ch.values())
    print(f"{s['run']:>12d} {s['seed']:>7d} {row} {whole:7.3f}")
print("\nrange (whole):", d["whole"]["ratio_range"], "median:", d["whole"]["ratio_median"])
for o in ops:
    print(o, d["operations"][o])
