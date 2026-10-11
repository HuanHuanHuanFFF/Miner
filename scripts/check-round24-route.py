"""Local workflow route check before the first manually authorized R24 run."""
from pathlib import Path
import ast
import yaml

def main():
    root=Path(__file__).resolve().parents[1]
    d=yaml.safe_load((root/'.github/workflows/deflate-round9.yml').read_text())
    trigger=d.get('on',d.get(True));assert set(trigger)=={'workflow_dispatch'}
    assert '24' in trigger['workflow_dispatch']['inputs']['experiment_round']['options']
    assert "inputs.experiment_round != '24'" in d['jobs']['experiment']['if']
    job=d['jobs']['round24'];assert "inputs.experiment_round == '24'" in job['if']
    assert job['env']['ROUND4_SPEC_DIR']=='evidence/round24' and 'ROUND24_MODE' in job['env']
    assert any('verify-round24-exact.py' in s.get('run','') for s in job['steps'])
    assert trigger['workflow_dispatch']['inputs']['allow_private']['default'] is False
    tree=ast.parse((root/'scripts/dispatch-round24.py').read_text())
    assignments=[n for n in ast.walk(tree) if isinstance(n,ast.Assign)]
    inputs=next(n.value for n in assignments if any(isinstance(t,ast.Name) and t.id=='inputs' for t in n.targets))
    fields={k.value:v for k,v in zip(inputs.keys,inputs.values)}
    assert fields['experiment_round'].value=='24' and fields['allow_private'].value=='false'
    record=next(n.value for n in assignments if any(isinstance(t,ast.Name) and t.id=='record' for t in n.targets))
    assert next(v.value for k,v in zip(record.keys,record.values) if k.value=='round')==24
    print('R24_MANUAL_PUBLIC_WORKFLOW_ROUTE_VALIDATED')

if __name__=='__main__':main()
