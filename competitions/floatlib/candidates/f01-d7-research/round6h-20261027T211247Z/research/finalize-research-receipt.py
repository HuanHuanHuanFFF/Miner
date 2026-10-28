"""Freeze research delivery metadata only after the fixed common cutoff."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import subprocess

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
cutoff = datetime(2026, 10, 28, 3, 12, 47, tzinfo=timezone.utc)
now = datetime.now(timezone.utc)
assert now >= cutoff, 'The shared window is still active; do not close early.'
capacity = json.loads((HERE / 'capacity-interruption.json').read_bytes())
failed, resumed = capacity['failed_turn'], capacity['resumed_turn']
cut_epoch = int(cutoff.timestamp())
turn_seconds = (failed['durationMs'] + (cut_epoch - resumed['startedAt']) * 1000) / 1000
tool_begin = datetime(2026, 10, 27, 21, 16, 43, tzinfo=timezone.utc)
tool_seconds = (cutoff - tool_begin).total_seconds() - capacity['gap_seconds']
accounting = {
    'recorded_utc': now.isoformat(), 'common_start_utc': '2026-10-27T21:12:47Z',
    'common_cutoff_utc': cutoff.isoformat(), 'common_window_seconds': 21600,
    'state': 'CUTOFF_REACHED_WITH_REPORTED_CONTROLLER_INTERRUPTION',
    'controller_model_turn_wall_seconds_until_cutoff': turn_seconds,
    'controller_first_tool_conservative_wall_seconds_minus_known_gap': tool_seconds,
    'controller_capacity_gap_seconds': capacity['gap_seconds'],
    'controller_model_join_delay_seconds': failed['startedAt'] - 1793135567,
    'controller_first_tool_join_delay_seconds': 236,
    'duration_scope': 'Turn wall includes preparation/coordination, not CPU or token time; first-tool convention is a separate conservative view. Capacity gap excluded. No claim of six uninterrupted controller hours.',
    'children': {
        'A': {'first_tool_utc': '2026-10-27T21:17:47Z', 'final_metadata_tool_utc': '2026-10-28T03:14:29.011125Z', 'current_index': 'streaming-public/status.json', 'continuous_active_seconds': 'UNKNOWN'},
        'B': {'first_tool_utc': '2026-10-27T21:17:57Z', 'final_metadata_tool_utc': '2026-10-28T03:13:59Z', 'current_index': 'scaled-mul/status.json', 'continuous_active_seconds': 'UNKNOWN'},
        'C': {'first_tool_utc': '2026-10-27T21:18:14Z', 'final_metadata_tool_utc': '2026-10-28T03:13:33.859Z', 'current_index': 'independent-frontier/status.json', 'continuous_active_seconds': 'UNKNOWN'},
    },
    'goal': 'NEW_CHAMPION_NOT_ACHIEVED_RETAIN_B2', 'post_cutoff_work': 'Collect already started work, verify delivery and push receipt only.'}
(HERE / 'time-accounting-final.json').write_text(json.dumps(accounting, indent=2) + '\n')
p = HERE / 'research-status.json'
s = json.loads(p.read_bytes())
s.update(state='CUTOFF_REACHED_RESEARCH_HANDED_TO_D_GIT_COORDINATOR', updated_utc=now.isoformat(),
         research_end_utc=cutoff.isoformat(), time_accounting='time-accounting-final.json',
         final_goal='NO_NEW_CHAMPION_RETAIN_B2', git_delivery='D_COORDINATES_COMMIT_PUSH_RECEIPT_SEPARATELY')
p.write_text(json.dumps(s, ensure_ascii=False, indent=2) + '\n')
p = HERE / 'HANDOFF.md'
t = p.read_text().replace('目前仍执行最后核验', '已到共同截止，停止新增研究；仅核验已启动工作及推送回执')
t = t.replace('最终R源清单在截止后冻结', '最终R源清单见research-file-manifest.json')
p.write_text(t, encoding='utf-8')
relative = HERE.relative_to(ROOT).as_posix()
names = subprocess.check_output(['git', 'ls-files', '-z', '--cached', '--others', '--exclude-standard', '--', relative], cwd=ROOT).split(b'\0')
files = {}
for raw_name in sorted(set(names)):
    if not raw_name:
        continue
    name = raw_name.decode('utf-8')
    p = ROOT / name
    if p.name == 'research-file-manifest.json' or not p.is_file():
        continue
    assert p.resolve().is_relative_to(HERE.resolve())
    blob = p.read_bytes()
    files[p.relative_to(HERE).as_posix()] = {'bytes': len(blob), 'sha256': hashlib.sha256(blob).hexdigest()}
manifest = {'snapshot_utc': datetime.now(timezone.utc).isoformat(), 'root': relative,
            'branch': subprocess.check_output(['git', 'branch', '--show-current'], cwd=ROOT, text=True).strip(),
            'files': files, 'file_count': len(files), 'total_bytes': sum(v['bytes'] for v in files.values()),
            'scope': 'Git-eligible research files only; excludes itself and ignored caches. D verifies this snapshot and commits/pushes. This snapshot alone is not a push receipt.'}
(HERE / 'research-file-manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
print(json.dumps({'file_count': manifest['file_count'], 'bytes': manifest['total_bytes'],
                  'model_turn_wall_seconds': turn_seconds, 'first_tool_wall_seconds': tool_seconds,
                  'capacity_gap_seconds': capacity['gap_seconds'], 'snapshot_utc': manifest['snapshot_utc']}))
