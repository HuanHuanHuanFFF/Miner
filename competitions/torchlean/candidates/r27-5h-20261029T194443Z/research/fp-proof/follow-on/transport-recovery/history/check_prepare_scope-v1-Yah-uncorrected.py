"""Source-bound finite counterexample to a global preparation smallNat claim."""
from datetime import datetime, timezone
from pathlib import Path
import hashlib
import json

HERE = Path(__file__).resolve().parent
CANDIDATE = HERE.parents[3]
SOURCE = CANDIDATE / "competition-state/source-private/submission23-Kernel.lean"
MASK = (1 << 64) - 1
CENTER = 1 << 62
MAX_SMALL_NAT = (1 << 63) - 1
ONE = 0x3f800000
TWO40 = 0x53800000


def exponent(w):
    return (w >> 23) & 255


def magnitude(w):
    return (w & 0x7fffff) + ((1 << 23) if exponent(w) else 0)


def yd(w):
    return exponent(w) - 1 if exponent(w) else 0


def span(row):
    vals = [yd(w) for w in row if magnitude(w) != 0]
    return max(vals) - min(vals)


def main():
    start = datetime.now(timezone.utc).isoformat()
    source_bytes = SOURCE.read_bytes()
    assert hashlib.sha256(source_bytes).hexdigest() == "1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe"
    source = source_bytes.decode("utf-8")
    assert "(BX.foldl" in source and "min m (QYF bx)" in source
    assert "(BV.foldl" in source and "max m (QYF bv)" in source
    assert "lemma Yuc4" in source
    narrow = [ONE] * 16
    wide = [ONE] * 15 + [TWO40]
    weights = [ONE] * 16
    row_spans = [span(narrow), span(wide)]
    weight_span = span(weights)
    qps_span = min(99, *row_spans) + max(0, weight_span)
    assert qps_span <= 15
    assert row_spans[1] + weight_span > 15
    m = min(yd(w) for w in wide)
    delta = yd(TWO40) - m
    M = (magnitude(TWO40) << (delta % 64)) & MASK
    pair = [(CENTER + M) & MASK, (CENTER - M) & MASK]
    assert delta == 40 and M == 1 << 63
    assert pair == [3 * (1 << 62)] * 2
    assert all(value > MAX_SMALL_NAT for value in pair)
    result = {
        "state": "SOURCE_BOUND_FINITE_PREPARATION_COUNTEREXAMPLE_NOT_LEAN_NOT_NATIVE",
        "actual_start_utc": start,
        "actual_end_utc": datetime.now(timezone.utc).isoformat(),
        "source": {"path": str(SOURCE.relative_to(CANDIDATE)), "sha256": hashlib.sha256(source_bytes).hexdigest(), "lines": {"Yf_Yd": [453,456], "QPD_QPS_QPa": [688,730], "YaV_prepare": [865,875], "Yuc4": [1340,1340]}},
        "raw_inputs": {"inW":16,"rows":2,"row0":{"word":ONE,"repeat":16},"row1":[{"word":ONE,"repeat":15},{"word":TWO40,"repeat":1}],"weights":{"word":ONE,"repeat":16},"bias":0},
        "metadata": {"input_spans":row_spans,"weight_span":weight_span,"global_min_input_plus_max_weight_span":qps_span,"global_QPS_span_condition":True,"wide_row_QPa_span_condition":False},
        "unused_prepared_high_element": {"magnitude":M,"shift_delta":delta,"two_QPb_Nat_entries":pair,"smallNat_limit_64bit":MAX_SMALL_NAT,"both_require_bigNat":True},
        "decision": "TheimmediateNatstatementholdsunderrowconsumerfastguard,notallglobalQPSpreparation. ConsideractualperrowunreachablefastcacheeliminationbeforeassumingFloatcarrierboxingsavings.",
        "candidate_minimal_condition": "InsideexistingglobalQPSbranch, ifinputrowspan>15thenitcanpassnoQPaglobalspancheckforanynonnegativeweightspan. PreserveoriginalYaUfallbackandgroupedYaUc4behavior; sourcelemmaYuc4alreadyequatesfourYaUresults.",
        "not_claimed": ["No actualQPDkernelwasexecuted.", "No allocationcountorwholemodelgainwasmeasured.", "No frozenconfirmationdatawasread.", "No newcandidateorfullgateproofexists."],
        "script_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    }
    (HERE / "prepare-scope-counterexample.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k:result[k] for k in ["state","metadata","unused_prepared_high_element","actual_start_utc","actual_end_utc"]}))


if __name__ == "__main__":
    main()

