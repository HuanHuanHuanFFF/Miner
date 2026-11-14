"""Freeze a moving cross-role dependency without changing candidate bytes."""
from pathlib import Path
import hashlib,json
from datetime import datetime,timezone
HERE=Path(__file__).resolve().parent
old=(HERE/'public23_reciprocal_v2.py').read_text(encoding='utf-8')
new=old.replace("BASE/'research/board-frontier/compact_public23.py'","HERE/'frozen_compact_public23.py'")
new=new.replace('0b50cfd3470de2e4ddbb39a158af49bb055278b4570765b04ba497af50c57029',
                '8eb6d15e6d64619b5813e0d31a3bf55fe01976fa5e84e85ad69a1c9a207ee434')
new=new.replace('def transform(data,submission=23,variant=\'row-reciprocal23-v2\'):',
                'def transform(data,submission=23,variant=\'row-reciprocal23-v3\'):')
new=new.replace("assert submission==23 and variant=='row-reciprocal23-v2'", "assert submission==23 and variant=='row-reciprocal23-v3'")
(HERE/'public23_reciprocal_v3.py').write_text(new,encoding='utf-8')
print(json.dumps({'recipe_sha256':hashlib.sha256(new.encode()).hexdigest(),
 'at_utc':datetime.now(timezone.utc).isoformat(),'candidate':'Same exact253499B/9654b727 candidate; only immutable own-scope compactor path changes'}))
