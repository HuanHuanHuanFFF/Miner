"""Run complete production validation logic on an owned draft without editing top-level specs."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import importlib
import json
import os

ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('draft', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    draft = args.draft.resolve()
    assert draft.is_relative_to(ROOT / 'evidence/round26/route-b')
    spec = json.loads(draft.read_bytes())
    os.environ['ROUND4_SPEC_DIR'] = 'evidence/round26'
    os.environ['ROUND4_SPEC'] = draft.stem
    os.environ['ROUND26_MODE'] = spec['r26_mode']
    module = importlib.import_module('round4')
    original = module.specification_path
    # Label/directory checks still run. Only the file lookup is redirected to
    # the child-owned draft; all production validation functions are unchanged.
    def owned_lookup(label):
        original(label)
        assert label == draft.stem
        return draft
    module.specification_path = owned_lookup
    result = {'draft': draft.relative_to(ROOT).as_posix(),
              'draft_sha256': hashlib.sha256(draft.read_bytes()).hexdigest(),
              'computed_utc': datetime.now(timezone.utc).isoformat(),
              'scope': 'Exact round4.validate and round26-preflight logic; only specification lookup redirected to owned draft. Root must still validate top-level frozen inputs before dispatch.'}
    try:
        module.validate(draft.stem)
        importlib.import_module('round26-preflight').main()
        result.update(status='VERIFIED_COMPLETE_PRODUCTION_VALIDATION_LOGIC_ON_OWNED_DRAFT',
                      entries=len(spec['entries']), expected_candidates=spec['r26_expected_candidates'])
    except Exception as error:
        result.update(status='REJECTED_BY_PRODUCTION_VALIDATION_LOGIC',
                      error_type=type(error).__name__, error=str(error))
        args.output.write_bytes((json.dumps(result, indent=2) + '\n').encode())
        raise
    finally:
        module.specification_path = original
    args.output.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps(result))


if __name__ == '__main__':
    main()
