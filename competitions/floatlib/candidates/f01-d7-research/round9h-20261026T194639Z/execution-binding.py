"""Bind a cohort to the execution files in every actual immutable run HEAD.

The original D7 gate and statistical guard remain unchanged. This adds evidence
checks only; it never checks out code, writes Git state or starts a process.
Git-object reads are supplied by the original guard.
"""
from hashlib import sha256
from pathlib import Path
import re

EXECUTION_FILES = (
    '.github/workflows/deflate-baseline.yml',
    '.github/workflows/floatlib-validate.yml',
    'competitions/floatlib/pins.json',
    'competitions/floatlib/scripts/ci-prepare.sh',
    'competitions/floatlib/scripts/ci-setup.sh',
    'competitions/floatlib/scripts/ci-validate.sh',
    'competitions/floatlib/scripts/run-gates.py',
    'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-ci.py',
    'competitions/floatlib/candidates/f01-word-tensors/ci-diagnostics.py',
    'competitions/floatlib/candidates/f01-d7-public-suite/Kernel.lean',
    'competitions/floatlib/candidates/f01-d7-public-suite/manifest.json',
    'competitions/floatlib/candidates/f01-d7-research/public-suite.py',
)
LOCAL_REVIEW_FILES = (
    'round-plan.json', 'selection-policy.json', 'prepare-plan.py', 'adoption-guard.py',
    'freeze-cohort.py', 'verify-three-groups.py', 'adopt-three-confirmed.py',
    'summarize-run.py', 'execution-binding.py',
    'refresh-retained-metadata.py',
)


def require(condition, message):
    if not condition:
        raise ValueError(message)


def snapshot(root):
    return {name: {'sha256': sha256((Path(root) / name).read_bytes()).hexdigest()}
            for name in EXECUTION_FILES}


def required_local_paths(root, here):
    return ([Path(here) / name for name in LOCAL_REVIEW_FILES] +
            [Path(here).parent / 'adoption-guard.py',
             Path(root) / 'competitions/floatlib/scripts/estimate_champion_time.py',
             Path(root) / 'competitions/floatlib/scripts/render_dashboard.py',
             Path(here) / 'retained-estimate-freeze.json',
             Path(here) / 'development-retained-model.json',
             Path(root) / 'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T043928Z/adoption-attempt-20261025T072850Z-e7312078/receipt.json'])


def verify_freeze(freeze):
    execution = freeze.get('execution_files')
    require(isinstance(execution, dict) and set(execution) == set(EXECUTION_FILES),
            'Missing/extra cohort execution files')
    for name, info in execution.items():
        require(isinstance(info, dict) and
                isinstance(info.get('sha256'), str) and
                re.fullmatch(r'[0-9a-f]{64}', info['sha256']) is not None,
                'Invalid execution digest: ' + name)
        require(freeze.get('files', {}).get(name) == info,
                'Execution/local freeze binding differs: ' + name)


def verify_run(freeze, packet, guard, root):
    execution = freeze.get('execution_files')
    require(isinstance(execution, dict) and set(execution) == set(EXECUTION_FILES),
            'Missing/extra cohort execution files')
    commit = packet.get('evidence', {}).get('source_commit')
    require(isinstance(commit, str) and re.fullmatch(r'[0-9a-f]{40}', commit) is not None,
            'Missing actual execution source commit')
    checked = {}
    for name in EXECUTION_FILES:
        raw = guard.read_tree_blob(root, commit, name)
        actual = sha256(raw).hexdigest()
        require(actual == execution[name]['sha256'],
                'Run execution differs from frozen cohort: ' + name)
        checked[name] = actual
    return {'source_commit': commit, 'files': checked,
            'scope': 'Actual run HEAD blobs match the common pre-observation execution freeze'}
