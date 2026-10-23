"""Bind saved W13d strict compiler receipts to exact unchanged public source bytes."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re

ROOT=Path.cwd().resolve();OWN=Path(__file__).resolve().parent
R=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7'
BASE=R/'web/R7-W13d/original-extracted/R7-W13d'
rows=[]
def read(path):
    raw=path.read_bytes();rows.append({'path':path.relative_to(ROOT).as_posix(),
        'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest()});return raw
def sha(raw):return hashlib.sha256(raw).hexdigest()

sources={}
commands=[]
for stem,expected in [('Kernel','e8fb1bb6671db553162a4e5fcd44d5bc47c7923df68b32cd7cbb9bd8bf65bf54'),
                      ('KernelDiagnostics','4db627a9824f7737aa6c44a0d3ae7cf7ba60c15a31f31314f3690b91ab527453')]:
    source=read(BASE/'source'/(stem+'.lean'))
    assert source==read(R/'web/R7-W13c/original-extracted/R7-W13c'/(stem+'.lean'))
    assert sha(source)==expected
    assert source==read(BASE/'logs'/(stem+'-strict-source.lean'))
    assert not re.search(rb'\bset_option\s+(?:autoImplicit|relaxedAutoImplicit)\b',source)
    record=json.loads(read(BASE/'logs'/(stem+'-strict.json')))
    assert record['exit_code']==0 and record['spawned'] is True
    assert record['output_existed_before'] is False and record['output_exists_after'] is True
    assert record['source_sha256']==record['source_sha256_after']==expected
    assert record['source_unchanged'] and record['snapshot_matches_source']
    assert record['strict_flags']=={'autoImplicit':False,'relaxedAutoImplicit':False}
    assert '-DautoImplicit=false' in record['argv'] and '-DrelaxedAutoImplicit=false' in record['argv']
    assert record['argv'][-1]==record['source']
    for key in ['stdout','stderr']:
        item=record[key];raw=read(BASE/item['path'])
        assert len(raw)==item['bytes'] and sha(raw)==item['sha256']
    commands.append({k:record[k] for k in ['label','argv','exit_code','start_utc','end_utc',
        'source_sha256','source_sha256_after','output_existed_before','output_sha256','output_bytes']})
    sources[stem]=source
assert sources['KernelDiagnostics'].startswith(sources['Kernel'])
tail=sources['KernelDiagnostics'][len(sources['Kernel']):]
assert not re.search(rb'^\s*import\s+Kernel\b',tail,re.M)
required=re.findall(rb'^\s*#print\s+axioms\s+([\w.]+)\s*$',tail,re.M)
assert len(required)==len(set(required))==80
stdout=read(BASE/'logs/KernelDiagnostics-strict.stdout').decode('utf8')
parsed={}
pattern=r"^'([^']+)' (?:depends on axioms: \[([^\]]*)\]|does not depend on any axioms)"
for name,axiomlist in re.findall(pattern,stdout,re.M):
    assert name not in parsed,name
    parsed[name]=[a.strip().split('.{',1)[0] for a in axiomlist.split(',') if a.strip()]
allowed={'propext','Classical.choice','Quot.sound'}
assert set(parsed)=={n.decode() for n in required} and len(parsed)==80
assert all(set(v)<=allowed for v in parsed.values())
saved=json.loads(read(BASE/'logs/strict-axiom-audit.json'))
assert saved['required_declarations']==saved['checked_declarations']==80
assert not saved['missing'] and not saved['unexpected'] and not saved['unapproved']
assert parsed==saved['axioms']
environment=json.loads(read(BASE/'evidence/environment-identity.json'))
assert environment['official_commit']=='4b7e83841cc0c32c6529f533923c73d33b5ecf97'
assert all(row.get('equal') is True for row in environment['components'])
read(BASE/'evidence/source-byte-binding.json')
read(BASE/'R7-W13d-receipt.json')
read(BASE/'logs/run_strict-preflight1.py')
official=json.loads(read(R/'official-lean-settings-receipt.json'))
lake=read(R/official['lakefile']);trace=read(R/official['captured_lake_trace'])
assert sha(lake)==official['lakefile_sha256'] and sha(trace)==official['trace_sha256']
assert re.search(rb'autoImplicit\s*,\s*false',lake) and re.search(rb'relaxedAutoImplicit\s*,\s*false',lake)
assert b'-DautoImplicit=false' in trace and b'-DrelaxedAutoImplicit=false' in trace
review=OWN/'low-normal-public-composition-review.json';read(review)
out={'reviewed_at_utc':datetime.now(timezone.utc).isoformat(),
     'status':'PASS_EXACT_PUBLIC_STRICT_PLAIN_LEAN_RECEIPTS_AND_RAW_AXIOMS',
     'public_main_sha256':sha(sources['Kernel']),'public_diagnostic_sha256':sha(sources['KernelDiagnostics']),
     'source_unchanged_from_W13c':True,'strict_invocations':commands,
     'raw_axiom_declarations':len(parsed),'axioms':parsed,'allowed':sorted(allowed),
     'four_original_type_assertions':'Same exact diagnostic source already independently checked in low-normal-public-composition-review.json; it was re-elaborated with both explicit false flags and exit0.',
     'environment':'Existing relocated cache. Recorded Lean executable/shared-library and official config/manifest/contracts/pins identities agree; complete prior pruned olean-cache byte identity UNKNOWN. No binary rehash performed locally.',
     'preserved_negative':'One launcher-only preflight assertion failed before Lean. Original preflight script/logs retained; source bytes and strict flags did not change.',
     'warnings':'Original stdout includes deprecations, unused simp arguments and tactic suggestions. No raw warnings discarded; explicit compiler exit and complete axiom records are the acceptance evidence for this ordinary compile.',
     'new_private_candidate_compile':'NOT_RUN','original_fullgate':'NOT_RUN',
     'kernel_replay':'NOT_RUN','C_and_performance':'NOT_RUN',
     'input_files':rows,'scope':'Independent offline receipt/source/log audit only. No compiler executed, source uploaded, gate modified or private353d/3d9 acceptance inherited.'}
(OWN/'strict-public-settings-review.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf8')
print(json.dumps({'status':out['status'],'input_file_records':len(rows),'raw_axiom_declarations':len(parsed),'new_private_gate':'NOT_RUN'}))
