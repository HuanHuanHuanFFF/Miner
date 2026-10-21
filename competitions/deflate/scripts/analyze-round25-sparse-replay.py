"""Check whether final-token emission replay describes the measured sparse stream.

This is a lightweight, one-input diagnostic, not a Rust parser, timing, or proof.
It must report an observed mismatch rather than assume future fold is unchanged.
"""
from pathlib import Path
import hashlib
import json
import struct

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT/'evidence/round25/38132193695/counts-k2-native/diagnostics/r25-tiny-encoder'
NATIVE = ROOT/'evidence/round25/38132623194/quality-m-native/diagnostics/r13-encoder/encoder.json'


def sha(data):
    return hashlib.sha256(data).hexdigest()


def decode(tokens):
    out = bytearray()
    for t in tokens:
        if t < 256:
            out.append(t)
        else:
            assert 16777216 <= t < 25165824
            v = t-16777216
            distance, length = v//256+1, v%256+3
            assert distance <= len(out)
            for _ in range(length):
                out.append(out[-distance])
    return bytes(out)


def main():
    output = ROOT/'evidence/round25/sparse-offline-replay.json'
    assert not output.exists()
    raw_tokens = (BASE/'tokens-and-output/tiny_pc8-tiny-config.json.txt.tokens').read_bytes()
    receipt = json.loads((BASE/'receipt.json').read_bytes())
    original = next(r for r in receipt['rows'] if r['candidate']=='tiny_pc8'
                    and r['file']=='tiny-config.json.txt')
    assert sha(raw_tokens) == original['tokens_sha256']
    tokens = [v[0] for v in struct.iter_unpack('<I', raw_tokens)]
    data = decode(tokens)
    assert len(data) == 12000 and sha(data) == original['input_sha256']
    rust = (ROOT/'candidates/r25-astra-tiny-pc-sparse/parse.rs').read_bytes()
    assert sha(rust) == '84ccbcbe88c56d8459c6df0d8bad5391b0ce95209d4e2f5fb4148369c9c294e5'
    text = rust.decode()
    values = text.split('pub const q4_TF_LSYM:',1)[1].split('= [',1)[1].split('];',1)[0]
    codes = [int(x.strip()) for x in values.split(',') if x.strip()]
    assert len(codes) >= 259
    mask = 302256384
    allowed = [n for n in range(3,259) if (mask >> (codes[n]%32)) & 1]
    assert allowed == [11,12,19,20,21,22]+list(range(51,59))+list(range(163,195))+[258]
    lens = [max((n for n in allowed if n<=r), default=0) for r in range(259)]
    transformed, details, position = [], [], 0
    for t in tokens:
        if t < 256:
            transformed.append(t)
            position += 1
            continue
        v = t-16777216
        distance, length = v//256+1, v%256+3
        left, pieces = length, []
        while lens[left] >= 3:
            n = lens[left]
            transformed.append(16777216+(distance-1)*256+n-3)
            pieces.append(n)
            position += n
            left -= n
        transformed.extend(data[position:position+left])
        position += left
        details.append({'length':length,'distance':distance,'pieces':pieces,'literal_tail':left})
    assert position == len(data) and decode(transformed) == data
    transformed_raw = b''.join(struct.pack('<I', t) for t in transformed)
    actual = next(r for r in json.loads(NATIVE.read_bytes())['rows']
                  if r['candidate']=='r25-astra-tiny-pc-sparse' and r['file']=='tiny-config.json.txt')
    result = {'status':'VERIFIED_ONE_INPUT_OFFLINE_EMISSION_REPLAY_NOT_A_NEW_CANDIDATE',
        'input_sha256':sha(data),'input_bytes':len(data),
        'source_tokens_sha256':sha(raw_tokens),'source_tokens':len(tokens),
        'replayed_tokens_sha256':sha(transformed_raw),'replayed_tokens':len(transformed),
        'measured_native_tokens_sha256':actual['tokens_sha256'],'measured_native_tokens':actual['tokens'],
        'matches_measured_native_stream':sha(transformed_raw)==actual['tokens_sha256'],
        'valid_decode':True,'allowed_lengths':allowed,'matches':details,
        'literal_tail_total':sum(r['literal_tail'] for r in details),
        'matches_below_minimum':sum(r['length']<11 for r in details),
        'native_receipt':NATIVE.relative_to(ROOT).as_posix(),'native_receipt_sha256':sha(NATIVE.read_bytes()),
        'limits':['One frozen public input and final-token transformation only. A match does not prove unchanged parser/fold behavior on other inputs.',
                  'A mismatch is retained as evidence that final-token replay cannot stand in for the actual parser.',
                  'No original encoder execution, new bytes, time, share, universal equivalence or proof claim.']}
    output.write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({k:v for k,v in result.items() if k not in ['matches','allowed_lengths']},indent=2))


if __name__=='__main__':
    main()
