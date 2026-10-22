"""Integer-only boundary diagnostic. Does not execute Lean or the word loop."""
import json


def main():
    rows = points = 0
    for batch in range(9):
        for m in range(9):
            for n in range(17):
                size = batch * m * n
                for b in range(batch):
                    for i in range(m):
                        row = b * m + i
                        base = row * n
                        assert row < batch * m
                        assert base + n <= size
                        assert n <= size
                        if n > 0:
                            assert base + (n - 1) < size
                        for k in range(n):
                            assert base + k < size
                            points += 1
                        rows += 1
    positives = []
    counterexamples = []
    for width in (32, 64):
        limit = 1 << width
        for batch, m, n in ((1, 1, limit - 1), (1, 2, limit // 2 - 1), (3, 5, limit // 16)):
            b, i = batch - 1, m - 1
            size = batch * m * n
            base = (b * m + i) * n
            assert size < limit and n < limit and base < limit
            assert base + (n - 1) < size
            positives.append({'word_bits': width, 'shape': [batch, m, n], 'size': size, 'last_address': base + n - 1})
        for batch, m in ((0, 1), (1, 0)):
            n = limit
            size = batch * m * n
            assert size < limit and not n < limit
            counterexamples.append({'kind': 'empty_shape_hAS_does_not_bound_n', 'word_bits': width, 'shape': [batch, m, n], 'hAS': True, 'hn': False})
        assert not limit < limit
        counterexamples.append({'kind': 'strict_size_boundary_rejected', 'word_bits': width, 'size': limit, 'hAS': False})
    assert not 0 + max(0 - 1, 0) < 0
    counterexamples.append({'kind': 'n_zero_row_span_false', 'shape': [1, 1, 0], 'left': 0, 'right': 0})
    huge_n = 2 ** 128 + 123
    assert 0 * 1 * huge_n == 0
    counterexamples.append({'kind': 'empty_shape_arbitrary_Nat_n', 'shape': [0, 1, huge_n], 'output_count': 0, 'word_conversion_required': False})
    return {
        'status': 'PASSED_INTEGER_BOUNDARY_DIAGNOSTIC_ONLY',
        'shape_range': 'batch,m=0..8; n=0..16',
        'valid_rows_checked': rows,
        'valid_points_checked': points,
        'large_integer_positive_cases': positives,
        'counterexamples_and_rejected_cases': counterexamples,
        'lean_elaboration': 'NOT_RUN',
        'native_word_loop_execution': 'NOT_RUN',
        'timing': 'NOT_RUN',
        'scope': 'Checks finite integer examples and concrete misuse counterexamples, not universal Lean acceptance.'
    }


if __name__ == '__main__':
    print(json.dumps(main(), ensure_ascii=False, indent=2))
