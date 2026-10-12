"""Read retained K token streams; do not rewrite tokens or infer new encoder results."""
from pathlib import Path
from collections import defaultdict
import hashlib
import json
import struct

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'evidence/round25/38132193695/counts-k2-native/diagnostics/r25-tiny-encoder'


def sha(data):
    return hashlib.sha256(data).hexdigest()


def main():
    out = ROOT / 'evidence/round25/tiny-symbol-coverage.json'
    assert not out.exists()
    receipt = json.loads((BASE / 'receipt.json').read_bytes())
    rows = {r['candidate']: r for r in receipt['rows'] if r['file'] == 'tiny-config.json.txt'}
    parent_len = {i for i, v in enumerate(rows['combo']['token_summary']['litlen_frequency_including_eob']) if i >= 257 and v}
    parent_dist = {i for i, v in enumerate(rows['combo']['token_summary']['distance_frequency']) if v}
    source = ROOT / 'candidates/r25-astra-tiny-pc-sparse/parse.rs'
    body = source.read_text().split('pub const q4_TF_LSYM:', 1)[1].split('= [', 1)[1].split('];', 1)[0]
    symbol_indices = [int(v.strip()) for v in body.split(',') if v.strip()]
    length_bases = [3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258]
    distance_bases = [1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193,257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577]
    result = []
    for name in ('combo', 'tiny_pc8'):
        raw = (BASE / f'tokens-and-output/{name}-tiny-config.json.txt.tokens').read_bytes()
        assert sha(raw) == rows[name]['tokens_sha256']
        def empty():
            return {'match_tokens': 0, 'produced_span_bytes': 0, 'length_codes': set(), 'distance_codes': set()}
        groups, lengths = defaultdict(empty), defaultdict(empty)
        decoded, literal = bytearray(), 0
        lf, df = [0] * 288, [0] * 30
        for (token,) in struct.iter_unpack('<I', raw):
            if token < 256:
                decoded.append(token)
                literal += 1
                lf[token] += 1
                continue
            assert 16777216 <= token < 25165824
            val = token - 16777216
            distance, length = val // 256 + 1, val % 256 + 3
            lc = 257 + max(i for i, b in enumerate(length_bases) if b <= length)
            dc = max(i for i, b in enumerate(distance_bases) if b <= distance)
            assert lc == 257 + symbol_indices[length]
            assert distance <= len(decoded)
            for _ in range(length):
                decoded.append(decoded[-distance])
            lf[lc] += 1
            df[dc] += 1
            names = ['all', 'parent_length' if lc in parent_len else 'new_length',
                     'parent_distance' if dc in parent_dist else 'new_distance',
                     'both_parent' if lc in parent_len and dc in parent_dist else 'some_new_symbol']
            for group in [groups[n] for n in names] + [lengths[lc]]:
                group['match_tokens'] += 1
                group['produced_span_bytes'] += length
                group['length_codes'].add(lc)
                group['distance_codes'].add(dc)
        lf[256] += 1
        assert lf == rows[name]['token_summary']['litlen_frequency_including_eob']
        assert df == rows[name]['token_summary']['distance_frequency']
        assert len(decoded) == 12000 and sha(decoded) == rows[name]['input_sha256']
        for family in (groups, lengths):
            for group in family.values():
                for key, value in list(group.items()):
                    if isinstance(value, set):
                        group[key] = sorted(value)
        result.append({'candidate': name, 'input_sha256': sha(decoded), 'tokens_sha256': sha(raw),
                       'literal_tokens': literal, 'groups': dict(groups),
                       'by_length_code': dict(sorted(lengths.items()))})
    record = {'status': 'VERIFIED_RETAINED_TOKEN_SYMBOL_COVERAGE_NOT_NEW_ENCODER_RESULT',
              'gap': 'K shows wider symbol sets and work, but frequency alone does not describe final decoded spans associated with those symbols.',
              'operation': 'Read two frozen token streams; verify reconstruction, frequency vectors and K hashes; classify final matches by parent-active length and distance codes. No rewrite, encoder, timing, parameter selection or CI.',
              'parent_live_length_codes': sorted(parent_len), 'parent_live_distance_codes': sorted(parent_dist),
              'receipt_sha256': sha((BASE / 'receipt.json').read_bytes()),
              'symbol_table_source_sha256': sha(source.read_bytes()), 'rows': result,
              'limits': ['Produced match spans are not marginal output-byte savings; parser boundaries and trajectories differ.',
                         'Deleting a symbol may change future parse/fold and Huffman distributions. Counts are not attainable quality or time bounds.',
                         'One public input; no new candidate, source change, full gate, share or private guarantee.']}
    out.write_text(json.dumps(record, indent=2) + '\n', encoding='utf-8')
    print(json.dumps([{'candidate': r['candidate'], 'groups': r['groups']} for r in result], indent=2))


if __name__ == '__main__':
    main()
