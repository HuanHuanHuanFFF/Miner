"""Finite address/order diagnostic only; does not execute Float32 or Lean."""
from pathlib import Path
import datetime
import hashlib
import itertools
import json


def old_coordinate(m, p, q):
    size = m * p
    r = q % size
    return q // size, r // p, r % p


def streamed_coordinate(m, p, q):
    row, col = divmod(q, p)
    b, i = divmod(row, m)
    return b, i, col


def address_signature(n, m, p, b, i, j):
    return ((b * m + i) * n, b * n * p + j, j // 10, j % 10)


def run():
    shapes = outputs = ordered_pairs = 0
    for batch, m, n, p in itertools.product(range(4), range(8), range(7), range(15)):
        shapes += 1
        expected = [old_coordinate(m, p, q) for q in range(batch * m * p)]
        nested = [(b, i, j) for b in range(batch) for i in range(m) for j in range(p)]
        streamed = [streamed_coordinate(m, p, q) for q in range(batch * m * p)]
        assert expected == nested == streamed
        for q, (b, i, j) in enumerate(expected):
            assert (b * m + i) * p + j == q
            assert address_signature(n, m, p, *streamed[q]) == address_signature(n, m, p, b, i, j)
            for k in range(n):
                assert (b * m + i) * n + k < batch * m * n
                assert b * n * p + j + k * p == (b * n + k) * p + j
                ordered_pairs += 1
            outputs += 1
    huge_points = 0
    for batch, m, p in itertools.product([1, 2, 2**64 + 3], [1, 7, 2**64 - 1, 2**80 + 7], [1, 10, 51, 2**70 + 3]):
        total = batch * m * p
        for q in sorted({0, total - 1, total // 2, p - 1, min(p, total - 1), min(m * p, total - 1)}):
            assert old_coordinate(m, p, q) == streamed_coordinate(m, p, q)
            huge_points += 1
    # Wrong flat groups of ten can share A across adjacent rows when p=3.
    counterexample = {
        'shape': [1, 2, 1, 3],
        'A': [1, 2],
        'B': [3, 5, 7],
        'expected_integer_exact_outputs': [3, 5, 7, 6, 10, 14],
        'wrong_reused_row0_outputs': [3, 5, 7, 3, 5, 7],
        'scope': 'Analytic exact-small-integer counterexample to crossing row boundaries, not execution of Lean.'
    }
    return {
        'status': 'PASS_FINITE_ADDRESS_ORDER_ONLY',
        'shapes': shapes,
        'valid_outputs': outputs,
        'ordered_address_pairs': ordered_pairs,
        'huge_nat_points': huge_points,
        'float_execution': 'NOT_RUN',
        'lean_proof': 'NOT_RUN',
        'full_gate': 'NOT_RUN',
        'counterexample': counterexample,
        'default_source_counts': {
            'shape': [2, 50, 100, 50],
            'valid_outputs': 5000,
            'ordered_macs': 500000,
            'old_global_coordinate_divmod_expressions': 20000,
            'row_stream_coordinate_divmod_expressions': 200,
            'column_group_divmod_expressions_unchanged': 10000,
            'row_output_intermediate_rows': 100,
            'row_output_batch_buffers': 2,
            'row_stream_batch_buffers': 0,
            'row_stream_index_vector_elements': 100,
            'row_stream_peak_result_tiles_source_lifetime': 5,
            'old_result_tiles': 500,
            'caveat': 'Source counts, not machine instructions, allocation counts, or timing. RC/compiler behavior must be observed.'
        }
    }


if __name__ == '__main__':
    result = run()
    result['script_sha256'] = hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    result['checked_at_utc'] = datetime.datetime.now(datetime.timezone.utc).isoformat()
    Path(__file__).with_suffix('.json').write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(result, indent=2))
