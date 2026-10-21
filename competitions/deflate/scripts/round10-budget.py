"""Record the actual wall-clock budget of this explicitly five-hour run."""
from datetime import datetime, timedelta, timezone
from pathlib import Path
import json

start = datetime(2026, 10, 7, 19, 50, 52, tzinfo=timezone.utc)
deadline = start + timedelta(hours=5)
now = datetime.now(timezone.utc)
reserve = timedelta(minutes=70)
zone = timezone(timedelta(hours=8))
record = {'start_utc': start.isoformat(), 'deadline_utc': deadline.isoformat(),
          'recorded_utc': now.isoformat(), 'start_asia_shanghai': start.astimezone(zone).isoformat(),
          'deadline_asia_shanghai': deadline.astimezone(zone).isoformat(),
          'elapsed_seconds': (now - start).total_seconds(),
          'remaining_seconds': max(0, (deadline - now).total_seconds()),
          'initial_confirmation_reserve_seconds': reserve.total_seconds(),
          'new_experiment_cutoff_asia_shanghai': (deadline - reserve).astimezone(zone).isoformat(),
          'boundary': 'Stop new experiments at the allocation cutoff; running CI completes naturally or at configured timeout. All reading, fixes, dispatch and checks count.'}
target = Path(__file__).resolve().parents[1] / 'evidence/round10/budget.json'
target.write_bytes((json.dumps(record, indent=2) + '\n').encode())
print(json.dumps(record))
