"""Statement-only asset assembly; no active wide entry is introduced.

Default dry run. --write creates one frozen source with exact local asset copies;
--verify checks every byte. No donor edits, Lean, Git, CI or option changes.
"""
from argparse import ArgumentParser
from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
from types import SimpleNamespace
import ast
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
R11 = HERE.parent / 'f01-d7-research/round7h-20261023T193125Z'
PARTS = [
    ('base', HERE.parent/'f01-d11-bmm-wide-backbone/Kernel.lean', '749bc933597ec15b200e8146899f7a055e25b4eef425e156bca337a13c38ca28', 223584, None),
    ('probe', HERE.parent/'f01-r11-wide4-codegen-probe/increment.lean', '04ca30e0c26ae420d1f7991c6c4b7c48401177ca26a6463551171ed44770673f', 4118, 'increment.lean'),
    ('projection', R11/'astra-wide4-projection.lean', 'afd8d0bf8598f2f7eb612d2b53f8c318a8f4eb0b6eec41502c135db060774291', 3649, 'astra-wide4-projection.lean'),
    ('writer', R11/'review-output-wide-layout.lean', '42a3547cd310297a2f79c636b8eb152547c8d4118f3bb66893b4762fd808bab1', 13649, 'wide-layout.lean'),
]
PARSER = HERE.parent/'f01-r8-combined-result-guard/build.py'
PARSER_SHA = '58662bf7218de54978d999bfb424975732cf845708869e1d611dd712d7470f22'
GATE = ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
GATE_SHA = '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'


def sha(raw):
    return sha256(raw).hexdigest()


def functions(raw, names, env):
    nodes = [n for n in ast.parse(raw.decode()).body if isinstance(n,ast.FunctionDef) and n.name in names]
    assert {n.name for n in nodes} == set(names)
    exec(compile(ast.Module(body=nodes,type_ignores=[]),'<pinned helpers>','exec'),env)
    return env


def construct():
    raw, records, ledger = {}, [], []
    data = b''
    for role,path,expected,size,local in PARTS:
        value=path.read_bytes()
        assert len(value)==size and sha(value)==expected and value.endswith(b'\n') and b'\r' not in value,role
        raw[role]=value
        records.append({'role':role,'path':path.relative_to(ROOT).as_posix(),'sha256':expected,'bytes':size,'local_copy':local})
        previous=data
        data+=value
        ledger.append({'role':role,'offset':len(previous),'appended_text':value.decode(),
            'appended_bytes':len(value),'appended_sha256':sha(value),'before_stage_sha256':sha(previous),'after_stage_sha256':sha(data)})
    assert len(data)==245000 and len(data)<=256000 and data.startswith(raw['base'])
    inverse=data
    for op in reversed(ledger[1:]):
        assert sha(inverse)==op['after_stage_sha256']
        at=op['offset'];part=op['appended_text'].encode()
        assert inverse[at:]==part and sha(part)==op['appended_sha256']
        inverse=inverse[:at]
        assert sha(inverse)==op['before_stage_sha256']
    assert inverse==raw['base']
    parser_raw=PARSER.read_bytes();assert sha(parser_raw)==PARSER_SHA
    inv=functions(parser_raw,['strip_comments','declarations'],{'re':re})
    old,new=[inv['declarations'](value.decode()) for value in (raw['base'],data)]
    assert not {k:v for k,v in new.items() if len(v)!=1}
    assert set(old)<=set(new)
    added=set(new)-set(old)
    assert all(k.startswith(('Submission.R11WideRows4.','Submission.R11WideLayout.')) for k in added)
    exports=['Submission.'+name for name in ['add','add_spec','mul','mul_spec','sum','sum_spec','bmm','bmm_spec']]
    assert all(len(new.get(k,[]))==1 for k in exports)
    assert b'structure F40 where\n' in raw['probe'] and b'namespace Submission.R11WideRows4\n' not in raw['base']
    assert b'runBlock' not in raw['writer']
    # Every lane40 use is scoped to an explicit function parameter; there is no
    # declaration or reference to an undefined global lane40 implementation.
    assert raw['writer'].count(b'(lane40 : R11WideRows4.F40')==11
    gate_raw=GATE.read_bytes();assert sha(gate_raw)==GATE_SHA
    assignments={t.id:n.value for n in ast.parse(gate_raw.decode()).body if isinstance(n,ast.Assign) for t in n.targets if isinstance(t,ast.Name)}
    env={'re':re,'Path':Path,'Verdict':object,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')},
        'OPTIONS':ast.literal_eval(assignments['OPTIONS']),'ATTRIBUTES':ast.literal_eval(assignments['ATTRIBUTES']),
        'BANNED':re.compile(ast.literal_eval(assignments['BANNED'].args[0]))}
    env=functions(gate_raw,['policy','options'],env)
    assert env['policy'](SimpleNamespace(read_text=lambda:data.decode()),SimpleNamespace(slot='full')) is None
    outer=raw['base'][raw['base'].rindex(b'namespace Submission\n'):]
    assert len(outer)==1039 and sha(outer)=='b135a8eef0606c7356dc12d5956115d3832aa5cddb5dc5e71e5030380c76062e'
    receipt={'candidate':HERE.name,'candidate_sha256':sha(data),'candidate_bytes':len(data),'headroom_bytes':256000-len(data),
        'parent_sha256':sha(raw['base']),'inputs':records,'builder_sha256':sha(Path(__file__).read_bytes()),
        'checks':{'all_exact_asset_pins':'PASS','complete_inverse_to_749b':'PASS','base_active_entry_and_specs_entire_prefix_unchanged':'PASS',
            'namespace_and_unique_declarations':'PASS','added_declarations':sorted(added),'unique_eight_exports_and_specs':'PASS',
            'original_policy':'PASS','author_notices_all_input_bytes_preserved':'PASS','extra_source_options':'NONE',
            'outer_underflow_sha256':sha(outer),'outer_underflow_bytes':len(outer)},
        'validation_mode':'STATEMENT_DIAGNOSTIC','proof_status':'NOT_RUN','kernel_replay':'NOT_RUN','axiom_audit':'NOT_RUN',
        'checksum':'NOT_RUN','generated_c_assembly':'NOT_RUN','full_gate':'NOT_RUN','matrix_algorithm_acceptance':'NOT_APPLICABLE_NO_ACTIVE_WIDE_ENTRY',
        'performance':'NOT_APPLICABLE_WIDE_UNUSED','formal_submission':'NOT_SUBMITTED'}
    return data,raw,ledger[1:],receipt


def main():
    ap=ArgumentParser();m=ap.add_mutually_exclusive_group();m.add_argument('--write',action='store_true');m.add_argument('--verify',action='store_true');args=ap.parse_args()
    data,raw,ledger,receipt=construct()
    if args.verify:
        assert (HERE/'Kernel.lean').read_bytes()==data
        for role,_,_,_,local in PARTS:
            if local:assert (HERE/local).read_bytes()==raw[role]
    elif args.write:
        outputs=['Kernel.lean','manifest.json','exact-inverse.json','static-checks.json']+[p[4] for p in PARTS if p[4]]
        assert not any((HERE/n).exists() for n in outputs),'Refuse overwrite'
        for role,_,_,_,local in PARTS:
            if local:(HERE/local).write_bytes(raw[role])
        (HERE/'Kernel.lean').write_bytes(data)
        manifest=dict(receipt,candidate_file='Kernel.lean',parent='f01-d11-bmm-wide-backbone',created_at_utc=datetime.now(timezone.utc).isoformat(),
            mechanism='Only exact unused loop, row-projection proof and generic writer assets appended to749b. Entire active base prefix unchanged; no concrete Projects instance, runBlock/buildTiles wiring or active wide entry.',
            missing='Projects still needs actual wordLoop-to-runDot/buildTiles connection. lane40 is universally quantified in generic definitions/theorems, not an undefined global. This package tests real declarations/proofs, not a new accepted matrix algorithm.',ci_owner='root')
        for name,payload in [('manifest.json',manifest),('exact-inverse.json',ledger),('static-checks.json',receipt)]:
            (HERE/name).write_bytes((json.dumps(payload,ensure_ascii=False,indent=2)+'\n').encode())
    print(json.dumps({k:receipt[k] for k in ['candidate','candidate_sha256','candidate_bytes','headroom_bytes','parent_sha256','builder_sha256','validation_mode','proof_status','matrix_algorithm_acceptance','performance']},indent=2))


if __name__=='__main__':main()
