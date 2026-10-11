"""Run only explicitly frozen R26 diagnostic helpers before original paired measurements."""
from pathlib import Path
import importlib
import os
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]

def main():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    spec = importlib.import_module('round4').validate(os.environ['ROUND4_SPEC'])
    if spec.get('r26_a_boundary_helper_check'):
        subprocess.run([sys.executable, str(ROOT/'scripts/r26-a-boundary-helper-check.py')], check=True)

if __name__ == '__main__':
    main()
