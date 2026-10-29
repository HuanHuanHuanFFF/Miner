"""Owned schedule selection patch; upstream bytes remain in private/ephemeral storage."""
import argparse, hashlib, json
from pathlib import Path

PIN = 'f92ee2c9a29de78dc434ad158b7141c0e4b5a67a5a198a353d59a4703481aa67'
VARIANTS = {'columns-all':65536, 'columns-medium':17, 'rows-all':0}

def transform(data, submission, variant):
    assert submission == 27 and hashlib.sha256(data).hexdigest() == PIN
    assert variant in VARIANTS
    threshold = VARIANTS[variant]
    text = data.decode('utf-8')
    # Both schedulers already compute the same scalar outputs for all sizes.
    # Change the runtime selector and its generic scheduler equality together.
    # The existing theorem still needs actual Lean compilation and kernel replay.
    for variable in ('rows','c'):
        old = f'if {variable}<2 then Yak4'
        new = f'if {variable}<{threshold} then Yak4'
        assert text.count(old) == 1, (variable, text.count(old))
        text = text.replace(old,new,1)
    result = text.encode('utf-8')
    assert len(result) <= 256000
    return result

if __name__ == '__main__':
    ap=argparse.ArgumentParser()
    ap.add_argument('--source',type=Path,required=True)
    ap.add_argument('--variant',choices=VARIANTS,required=True)
    ap.add_argument('--output',type=Path)
    args=ap.parse_args()
    data=transform(args.source.read_bytes(),27,args.variant)
    if args.output:
        args.output.parent.mkdir(parents=True,exist_ok=True)
        args.output.write_bytes(data)
    print(json.dumps({'source_sha256':PIN,'variant':args.variant,
                      'candidate_sha256':hashlib.sha256(data).hexdigest(),
                      'candidate_bytes':len(data),'proof':'ORIGINAL_ENTRY_PRESENT_NOT_COMPILED',
                      'goal':'Current Mixer champion36 only; public27 is a calibration carrier',
                      'speed':'UNKNOWN'}))
