"""R19 reviewed323 adapter; CLI read-only, adoption receives the original module."""
import argparse
import hashlib
import importlib.util
from pathlib import Path
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
ORIGINAL = ROOT / 'competitions/floatlib/scripts/estimate_champion_time.py'
DEFAULT_ANCHOR = HERE / 'development-workers/anchor-323/reviewed323-anchor.json'
ORIGINAL_SHA256 = '60476400919dff41f190c1779948f8eeca300753eb920c71ae659438f5bc3eb5'
ANCHOR_SHA256 = 'da251287655b84f502434fb6da4f2d3ffaa53fb08ae01e0124bc9a4765afa965'


def load_estimator():
    for path, expected in ((ORIGINAL, ORIGINAL_SHA256), (DEFAULT_ANCHOR, ANCHOR_SHA256)):
        if hashlib.sha256(path.read_bytes()).hexdigest() != expected:
            raise ValueError('Reviewed input bytes changed: ' + str(path))
    spec = importlib.util.spec_from_file_location('r19_reviewed323_original_estimator', ORIGINAL)
    estimator = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(estimator)
    estimator.DEFAULT_ANCHOR = DEFAULT_ANCHOR
    estimator.validate_anchor(estimator.load(DEFAULT_ANCHOR))
    return estimator


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--dry-run', action='store_true', required=True,
                        help='Required: standalone original CLI would refit retained B2 from all later controls')
    parser.parse_args(argv)
    return load_estimator().main(['--dry-run'])


if __name__ == '__main__':
    main()
