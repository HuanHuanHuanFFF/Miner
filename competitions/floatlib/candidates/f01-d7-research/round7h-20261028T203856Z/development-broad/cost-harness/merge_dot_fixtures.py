"""Merge immutable discovery fixtures; pure JSON, no execution or timing."""
from pathlib import Path
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROUND = HERE.parent.parent
SCALAR = ROUND / 'development-scalar/portable-f64-dot-fixtures.json'
BASELINE = HERE.parent / 'exact-dot-cost-fixtures.json'
OUTPUT = HERE / 'merged-dot-fixtures.json'
sha = lambda raw: hashlib.sha256(raw).hexdigest()


def word(value, bits):
    assert type(value) is int and 0 <= value < 1 << bits
    return value


def raw_words(values):
    assert type(values) is list
    return [word(value, 32) for value in values]


def finite(values):
    return all(((value >> 23) & 255) != 255 for value in values)


def main():
    scalar_bytes, baseline_bytes = SCALAR.read_bytes(), BASELINE.read_bytes()
    assert sha(scalar_bytes) == 'b146a148a8fed7eb528e42d8ce1388ed7e7ca4a5e6cf8b4b55b75f1503c5e1ac'
    assert sha(baseline_bytes) == '4b397a8625a154a4a1c3d24e17275bc2a480c61f0dcb8aa1c95bb47ed630d806'
    scalar, baseline = json.loads(scalar_bytes), json.loads(baseline_bytes)
    assert len(scalar['cases']) == 86 and len(baseline['dot_cases']) == 62
    cases = []
    for original in scalar['cases']:
        x, y = raw_words(original['x']), raw_words(original['y'])
        group = 'directed' if original['group'] in ('direct', 'directed') else original['group']
        assert group in ('24282403', '24282405', 'directed')
        fast = original['fast_result']
        assert fast is None or type(fast) is int
        if fast is not None:
            word(fast, 32)
        cases.append({'name': original['name'], 'group': group, 'kind': original['kind'],
                      'x': x, 'y': y, 'expected': word(original['expected'], 32),
                      'fast_result': fast,
                      'timed': bool(x) and len(x) == len(y) and finite(x) and finite(y)})
    for original in baseline['dot_cases']:
        cases.append({'name': 'baseline-' + original['id'], 'group': 'baseline-check',
                      'kind': 'baseline-check', 'x': raw_words(original['a']), 'y': raw_words(original['b']),
                      'expected': word(original['expected'], 32), 'fast_result': None, 'timed': False})
    rounds = []
    for original in baseline['round_cases']:
        assert type(original['negative']) is bool and type(original['base']) is int
        rounds.append({'id': original['id'], 'negative': original['negative'],
                       'lo': word(original['lo'], 64), 'hi': word(original['hi'], 64),
                       'base': original['base'], 'expected': word(original['expected'], 32)})
    assert len(cases) == 148 and len(rounds) == 1049
    assert len({case['name'] for case in cases}) == len(cases)
    assert len({case['id'] for case in rounds}) == len(rounds)
    assert all(not case['timed'] for case in cases[86:])
    for case, original in zip(cases[:86], scalar['cases']):
        assert case['x'] == original['x'] and case['y'] == original['y']
        assert case['expected'] == original['expected'] and case['fast_result'] == original['fast_result']
    OUTPUT.write_bytes((json.dumps({'cases': cases, 'round_cases': rounds}, indent=2) + '\n').encode())
    assert SCALAR.read_bytes() == scalar_bytes and BASELINE.read_bytes() == baseline_bytes
    summary = {'dot_cases': len(cases), 'round_cases': len(rounds),
               'timed_scalar_cases': sum(case['timed'] for case in cases[:86]),
               'untimed_scalar_numerical_cases': sum(not case['timed'] for case in cases[:86]),
               'baseline_numerical_only_cases': 62,
               'timed_groups': {group: sum(case['timed'] and case['group'] == group for case in cases)
                                for group in ('24282403', '24282405', 'directed')}}
    receipt = {'scope': 'Immutable discovery fixture merge only. No sampling/confirmation selection or performance claim.',
               'generator_sha256': sha(Path(__file__).read_bytes()),
               'inputs': [{'path': str(SCALAR.relative_to(ROUND)), 'sha256': sha(scalar_bytes), 'bytes': len(scalar_bytes)},
                          {'path': str(BASELINE.relative_to(ROUND)), 'sha256': sha(baseline_bytes), 'bytes': len(baseline_bytes)}],
               'output': {'file': OUTPUT.name, 'sha256': sha(OUTPUT.read_bytes()), 'bytes': OUTPUT.stat().st_size},
               'inputs_byte_identical_after': True, 'summary': summary}
    (HERE / 'merged-dot-fixtures.receipt.json').write_bytes((json.dumps(receipt, indent=2) + '\n').encode())
    print(json.dumps({'path': str(OUTPUT), 'sha256': receipt['output']['sha256'], 'summary': summary}, indent=2))


if __name__ == '__main__':
    main()
