"""Old-input zero-overlap work census; old formula still computes all outputs."""
from pathlib import Path
from datetime import datetime, timezone
from collections import Counter
import hashlib
import importlib.util
import json
import struct
import sys
import time

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
OWN = HERE.parents[1]
C = OWN.parent/'board-frontier'


def load(path, name):
    spec = importlib.util.spec_from_file_location(name, path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def main():
    start = time.perf_counter()
    f = load(C/'norm_frontier.py', 'r27_mask_formula')
    md = load(OWN/'word_model_coverage.py', 'r27_mask_metadata')
    original = f.linear
    layers = []
    context = {}
    layer = 0

    def observe(x, rows, n, out, w, b, relu):
        nonlocal layer
        assert time.perf_counter()-start < 20
        layer += 1
        xm = [md.metadata(x[i*n:(i+1)*n]) for i in range(rows)]
        wm = [md.metadata(w[j*n:(j+1)*n]) for j in range(out)]
        xi = [sum(1 << k for k in range(n) if x[i*n+k]&0x7fffffff) for i in range(rows)]
        wi = [sum(1 << k for k in range(n) if w[j*n+k]&0x7fffffff) for j in range(out)]
        assert all(m['finite'] for m in xm+wm)
        # QYF is UInt64 subtraction, including the reversed/all-zero case.
        native_span = lambda m: (m['upper']-m['base']) & ((1 << 64)-1)
        max_w_span = max(native_span(m) for m in wm)
        any_prepared = n >= 16 and min(99, min(native_span(m) for m in xm))+max_w_span <= 15
        counts = Counter()
        for i, a in enumerate(xm):
            nz = xi[i].bit_count()
            row_prepared = any_prepared and native_span(a)+max_w_span <= 15
            prune = row_prepared and 0 < nz and 4*nz <= 3*n
            for j, z in enumerate(wm):
                _, mb, ib = f.fields(b[j])
                bias_ok = mb == 0 or a['base']+z['base'] <= ib+126 < a['base']+z['base']+80
                actual_prepared = (row_prepared and not a['reversed'] and not z['reversed']
                                   and native_span(a)+native_span(z) <= 15 and z['base'] >= 1
                                   and n < 1 << 20 and bias_ok)
                nominal = nz if actual_prepared and prune else n
                joint = (xi[i]&wi[j]).bit_count()
                counts['logical_MACs'] += n
                counts['nominal_existing_product_visits'] += nominal
                counts['joint_nonzero_products'] += joint
                counts['prepared_QPa_dots'] += int(actual_prepared)
                counts['input_pruned_dots'] += int(actual_prepared and prune)
                counts['hypothetical_mask32_intersections'] += (n+31)//32
                counts['hypothetical_nonempty_mask32_words'] += sum(
                    bool(((xi[i]&wi[j]) >> k) & 0xffffffff) for k in range(0, n, 32))
        layers.append(dict(**context, layer=layer, rows=rows, n=n, out=out,
                           counts=dict(counts),
                           nominal_extra_word_scan_if_not_fused=rows*n+out*n,
                           mask32_array_slots=(rows+out)*((n+31)//32),
                           limits='Nominal product visits derive from source23 P/I and guards; no emitted instruction count or actual callback trace.'))
        return original(x, rows, n, out, w, b, relu)

    f.linear = observe
    seed = 27051001
    expected = json.loads((C/'norm-frontier-result.json').read_text())['cells']
    cells = []
    for kind in ('normal', 'wide', 'sparse'):
        for rows in (1, 8):
            context.clear()
            context.update(kind=kind, seed=seed, profile='typical')
            layer = 0
            n, h, h2 = f.dimensions(seed, 'typical')
            x = f.gen(kind, rows*n, seed+999)
            x = f.linear(x, rows, n, h, f.weights(kind, seed, 1, n, h*n), f.bias(seed, 2, h), True)
            x = f.norm(x, rows, h, f.scale(seed+3, h))
            x = f.linear(x, rows, h, h2, f.weights(kind, seed, 4, h, h2*h), f.bias(seed, 5, h2), True)
            x = f.norm(x, rows, h2, f.scale(seed+6, h2), f.bias(seed, 7, h2))
            x = f.linear(x, rows, h2, 10, f.weights(kind, seed, 8, h2, 10*h2), f.bias(seed, 9, 10), False)
            digest = hashlib.sha256(b''.join(struct.pack('<I', a) for a in x)).hexdigest()
            old = next(r for r in expected if r['seed']==seed and r['profile']=='typical' and r['kind']==kind and r['rows']==rows)
            assert digest == old['output_sha256']
            rr = [r for r in layers if r['kind']==kind and r['rows']==rows]
            total = Counter()
            for r in rr:
                total.update(r['counts'])
            cells.append({'kind':kind,'rows':rows,'counts':dict(total),
                          'joint_over_nominal_product_visits':total['joint_nonzero_products']/total['nominal_existing_product_visits'],
                          'original_formula_fixture_sha256':digest})
    result = {'at_utc':datetime.now(timezone.utc).isoformat(),
              'state':'OLD_SEEN_ZERO_OVERLAP_WORKCOUNT_ONLY_NO_NEW_KERNEL_NO_NATIVE',
              'cells':cells,'layers':layers,'wall_seconds':time.perf_counter()-start,
              'inputs':'Only pre-freeze27051001 typical cells and public23 metadata/P/I source. No batch9 inputs/results.',
              'limitations':['Old formula produces outputs; hashes bind fixtures only.',
                             'A bitset AND count is not native cost. Enumeration, metadata, preparation, arrays and output drops must be included.',
                             'Source23 already prunes many input zeros. Compare against that nominal path, not dense n.',
                             'Mask generation fused with metadata has no implementation or proof yet; a separate pass has additional cost.',
                             'Do not use Nat.log2 as a presumed hardware bit scan; pinned scalar implementation was inspected separately.',
                             'No new candidate or CI request is created by this census.'],
              'source_hashes':{p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in
                               (Path(__file__),OWN/'word_model_coverage.py',C/'norm_frontier.py',C/'norm-frontier-result.json')}}
    (HERE/'overlap-census.json').write_text(json.dumps(result,indent=2),encoding='utf8')
    print(json.dumps({'wall_seconds':result['wall_seconds'],'cells':cells},indent=2))


if __name__ == '__main__':
    main()
