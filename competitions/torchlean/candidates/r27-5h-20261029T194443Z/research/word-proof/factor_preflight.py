from pathlib import Path
import datetime
import hashlib
import json

HERE = Path(__file__).resolve().parent


def exact_value(word, base):
    exponent = (word >> 23) & 255
    fraction = word & 0x7fffff
    mantissa = fraction if exponent == 0 else 0x800000 + fraction
    index = max(0, exponent - 1)
    value = mantissa << max(0, index-base)
    return -value if word >> 31 else value


def valid(word, base):
    exponent = (word >> 23) & 255
    fraction = word & 0x7fffff
    mantissa = fraction if exponent == 0 else 0x800000 + fraction
    index = max(0, exponent-1)
    z = exact_value(word, base)
    return exponent != 255 and (mantissa == 0 or base <= index) and -(1<<31) <= z < (1<<31)


def decode_signed32(word):
    return word if word < (1<<31) else word-(1<<32)


def main():
    counts = dict(checked=0, accepted=0, nonfinite_rejected=0,
                  negative_minimum_accepted=0, positive_minimum_rejected=0)
    selected = []
    for exp in range(256):
        for fraction in (0, 1, 2, 0x3fffff, 0x7ffffe, 0x7fffff):
            for sign in (0, 1):
                word = (sign << 31) | (exp << 23) | fraction
                index = max(0, exp-1)
                for base in sorted({0, max(0,index-8), max(0,index-7), index, index+1, 254, 255}):
                    z = exact_value(word,base)
                    eligible = valid(word,base)
                    counts['checked'] += 1
                    if exp == 255:
                        assert not eligible
                        counts['nonfinite_rejected'] += 1
                    if eligible:
                        counts['accepted'] += 1
                        assert decode_signed32(z & 0xffffffff) == z
                        assert abs(z) <= 1<<31
                    if z == -(1<<31) and exp != 255 and base <= index:
                        assert eligible
                        counts['negative_minimum_accepted'] += 1
                    if z == 1<<31:
                        assert not eligible
                        counts['positive_minimum_rejected'] += 1
                    if abs(z) == 1<<31 and len(selected) < 8:
                        selected.append(dict(word=word,base=base,value=z,guard=eligible))
    # For zero bias the clipped exponent is harmless; nonzero tiny bias is not.
    one, minus_one, subnormal = 0x3f800000, 0xbf800000, 1
    total_body = exact_value(one,126)*exact_value(one,126) + exact_value(minus_one,126)*exact_value(one,126)
    assert total_body == 0
    assert exact_value(0x80000000,252-149) == 0
    sources = {p.name: dict(bytes=p.stat().st_size,sha256=hashlib.sha256(p.read_bytes()).hexdigest())
               for p in (Path(__file__), HERE/'FactorInt32.lean')}
    report = dict(at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
                  classification='FINITE_BOUNDARY_GUARD_REPLAY_ONLY_NOT_LEAN_OR_NATIVE',
                  generation='All256 exponentfields x6selectedfractions x2signs xdeduplicatedboundarybases',
                  counts=counts, selected_signed_endpoint_cases=selected, sources=sources,
                  exclusions=['Not all2^32words', 'No all-input Lean proof acceptance', 'No full12/native speed'],
                  bias_note='Zero bias can bypass lower-exponent guard, but exacttotalzero must retain originalsignedzero fallback. Nonzero minsubnormal still requires the lowerexponent guard.')
    (HERE/'factor-preflight.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(counts,indent=2))


if __name__ == '__main__':
    main()
