"""Require maintained round2 gates; report bucket2 as an optional experiment."""
from __future__ import annotations
import argparse
import json
from pathlib import Path

REQUIRED = ('probe3', 'probe2-nice16', 'probe2-nice64')


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('reports', type=Path)
    ap.add_argument('--require-bucket2', action='store_true', help='Explicit strict experiment check')
    args = ap.parse_args()
    failed = []
    required = REQUIRED + (('bucket2',) if args.require_bucket2 else ())
    for name in required:
        path = args.reports / (name + '-gate.json')
        if not path.is_file():
            failed.append(name + ': missing gate report')
            continue
        try:
            report = json.loads(path.read_text(encoding='utf-8'))
        except (OSError, ValueError):
            failed.append(name + ': unreadable gate report')
            continue
        if report.get('accepted') is not True:
            failed.append(name + ': gate did not accept')
            continue
        if report.get('corpora') != ['corpus-stage1']:
            failed.append(name + ': unexpected gate scope')
            continue
        print('REQUIRED_GATE_ACCEPTED ' + name)
    bucket = args.reports / 'bucket2-gate.json'
    if bucket.is_file() and not args.require_bucket2:
        report = json.loads(bucket.read_text(encoding='utf-8'))
        if report.get('accepted') is True:
            print('EXPERIMENTAL_GATE_ACCEPTED bucket2; not automatically promoted')
        else:
            print('::warning::bucket2 proof rejected; experimental candidate excluded from required CI and measurements')
    elif not bucket.is_file():
        print('EXPERIMENTAL_GATE_NOT_RUN bucket2')
    if failed:
        raise SystemExit('\n'.join(failed))


if __name__ == '__main__':
    main()
