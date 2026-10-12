"""Bound a fixed dispersed position sample before any discarded-probe observer exists."""
from pathlib import Path
import json

ROOT = Path(__file__).resolve().parents[1]


def selected(position):
    mask = (1<<32)-1
    x = position ^ (position>>16)
    x = (x*0x7feb352d)&mask
    x ^= x>>15
    x = (x*0x846ca68b)&mask
    x ^= x>>16
    return x>>27 == 0


def main():
    raw = json.loads((ROOT/'evidence/round26/38186466076/overlap-b12-native/diagnostics/r26-b-a-overlap/receipt.json').read_bytes())
    cache, rows = {}, []
    for row in raw['rows']:
        if not row['counts']['dp_calls']:
            continue
        n = row['raw_bytes']
        if n not in cache:
            cache[n] = sum(selected(position) for position in range(n))
        rows.append({'file':row['file'], 'raw_bytes':n, 'deterministic_selected_positions':cache[n],
                     'worst_sparse30code_logical_bytes':240*cache[n]})
    result = {
        'status':'VERIFIED_DETERMINISTIC_SAMPLE_STORAGE_PLAN_ONLY',
        'selector':'u32 avalanche hash >>27 ==0; fixed physical positions before result, not a representative/random probability claim',
        'rows':rows,
        'max_perinput_sparse30code_logical_bytes':max(row['worst_sparse30code_logical_bytes'] for row in rows),
        'scope':'No observer or CI. A potential selected-position observer could retain one longest discarded prefix per code in 8bytes(pos+word); original full/sampled DP consumer prices/costs still used.',
        'bounds':'Upper logical bytes at all30codes on every selected raw position; actual tree-search positions may be fewer. Excludes Vec capacity/allocator and original state; not measured memory.',
        'limits':['Selection is an opportunity probe on this subset; no extrapolated whole-input output/speed claim.',
                  'Raw producer counts cannot substitute for original packedbest consumer comparison.',
                  'Any observer remains subject to root budget/dispatch after B13 feedback.'],
    }
    path = ROOT/'evidence/round26/route-b/a-discarded-sample-plan.json'
    path.write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps(result,indent=2))


if __name__=='__main__':
    main()
