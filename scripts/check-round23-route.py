"""Local workflow route check before the first manually authorized R23 run."""
from pathlib import Path
import yaml

def main():
    root=Path(__file__).resolve().parents[1]
    d=yaml.safe_load((root/'.github/workflows/deflate-round9.yml').read_text())
    trigger=d.get('on',d.get(True));assert set(trigger)=={'workflow_dispatch'}
    assert '23' in trigger['workflow_dispatch']['inputs']['experiment_round']['options']
    assert "inputs.experiment_round != '23'" in d['jobs']['experiment']['if']
    job=d['jobs']['round23'];assert "inputs.experiment_round == '23'" in job['if']
    assert job['env']['ROUND4_SPEC_DIR']=='evidence/round23' and 'ROUND23_MODE' in job['env']
    assert any('verify-round23-exact.py' in s.get('run','') for s in job['steps'])
    assert trigger['workflow_dispatch']['inputs']['allow_private']['default'] is False
    print('R23_MANUAL_PUBLIC_WORKFLOW_ROUTE_VALIDATED')

if __name__=='__main__':main()
