"""Exact unused Panel4Tail proof diagnostic; active9a prefix is unchanged.
Default dry run, --write creates once, --verify reads only. No Lean/Git/CI.
"""
from argparse import ArgumentParser
from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
from types import SimpleNamespace
import ast,json,re

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[3]
PARENT=HERE.parent/'f01-d11-panel4-codegen-probe/Kernel.lean'
PARENT_SHA='9a40118eae28c92c1abeca7f6a141fb0fbfe963cbf40321681b8013782f9f7ac'
ASSET=HERE.parent/'f01-d7-research/round7h-20261023T193125Z/review-output-panel4-tail.lean'
ASSET_SHA='1afa76878e5f09cd1e1f5d2ce20795aca9a2755a83d05b845fc059bfeda112f3'
PARSER=HERE.parent/'f01-r8-combined-result-guard/build.py'
GATE=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'


def sha(raw):return sha256(raw).hexdigest()


def functions(raw,names,env):
    nodes=[n for n in ast.parse(raw.decode()).body if isinstance(n,ast.FunctionDef) and n.name in names]
    assert {n.name for n in nodes}==set(names)
    exec(compile(ast.Module(body=nodes,type_ignores=[]),'<pinned helpers>','exec'),env)
    return env


def construct():
    parent,asset=PARENT.read_bytes(),ASSET.read_bytes()
    assert len(parent)==229218 and sha(parent)==PARENT_SHA
    assert len(asset)==9276 and sha(asset)==ASSET_SHA
    assert parent.endswith(b'\n') and asset.endswith(b'\n')
    data=parent+asset
    assert len(data)==238494 and data[:-len(asset)]==parent
    parser=PARSER.read_bytes();assert sha(parser)=='58662bf7218de54978d999bfb424975732cf845708869e1d611dd712d7470f22'
    inv=functions(parser,['strip_comments','declarations'],{'re':re})
    old,new=[inv['declarations'](raw.decode()) for raw in [parent,data]]
    assert set(old)<=set(new) and all(len(v)==1 for v in new.values())
    added=set(new)-set(old)
    assert len(added)==12 and all(k.startswith('Submission.Panel4Tail.') for k in added)
    gate=GATE.read_bytes();assert sha(gate)=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
    tree=ast.parse(gate.decode());assign={t.id:n.value for n in tree.body if isinstance(n,ast.Assign) for t in n.targets if isinstance(t,ast.Name)}
    env={'re':re,'Path':Path,'Verdict':object,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')},
        'OPTIONS':ast.literal_eval(assign['OPTIONS']),'ATTRIBUTES':ast.literal_eval(assign['ATTRIBUTES']),
        'BANNED':re.compile(ast.literal_eval(assign['BANNED'].args[0]))}
    env=functions(gate,['policy','options'],env)
    assert env['policy'](SimpleNamespace(read_text=lambda:data.decode()),SimpleNamespace(slot='full')) is None
    receipt={'candidate':HERE.name,'candidate_sha256':sha(data),'candidate_bytes':len(data),'headroom_bytes':256000-len(data),
        'parent_sha256':PARENT_SHA,'parent_bytes':len(parent),'asset_sha256':ASSET_SHA,'asset_bytes':len(asset),
        'builder_sha256':sha(Path(__file__).read_bytes()),
        'checks':{'parent_active_prefix_and_four_specs_unchanged':'PASS','exact_asset_copy':'PASS',
          'full_inverse_to9a':'PASS','only_new_Panel4Tail_namespace':'PASS','unique_declarations':'PASS','original_policy':'PASS',
          'resource_options_and_parent_author_notices':'UNCHANGED'},
        'validation_mode':'STATEMENT_DIAGNOSTIC','proof_status':'NOT_RUN','kernel_replay':'NOT_RUN','axiom_audit':'NOT_RUN',
        'checksum':'NOT_RUN','full_gate':'NOT_RUN','generated_c_assembly':'NOT_RUN',
        'matrix_algorithm_acceptance':'NOT_APPLICABLE_NO_ACTIVE_PANEL_OR_TAIL_ENTRY','performance':'NOT_APPLICABLE_UNUSED_ASSETS',
        'formal_submission':'NOT_SUBMITTED'}
    inverse={'parent_sha256':PARENT_SHA,'candidate_sha256':sha(data),'offset':len(parent),
        'appended_text':asset.decode(),'appended_sha256':ASSET_SHA,'inverse_recovers_exact_parent':True}
    return data,asset,receipt,inverse


def main():
    ap=ArgumentParser();mode=ap.add_mutually_exclusive_group();mode.add_argument('--write',action='store_true');mode.add_argument('--verify',action='store_true');args=ap.parse_args()
    data,asset,receipt,inverse=construct()
    if args.verify:
        assert (HERE/'Kernel.lean').read_bytes()==data and (HERE/'panel4-tail.lean').read_bytes()==asset
    elif args.write:
        names=['Kernel.lean','panel4-tail.lean','manifest.json','static-checks.json','exact-inverse.json']
        assert not any((HERE/name).exists() for name in names),'Refuse overwrite'
        (HERE/'Kernel.lean').write_bytes(data);(HERE/'panel4-tail.lean').write_bytes(asset)
        manifest=dict(receipt,candidate_file='Kernel.lean',parent='f01-d11-panel4-codegen-probe',created_at_utc=datetime.now(timezone.utc).isoformat(),
            mechanism='Only exact9276B unused Panel4Tail namespace appended to exact9a. Tests preparation, dot10_shift, runDot and raw-finish/prefix proofs without connecting a new active entry.',
            missing='Panel4 wordLoop projection/Projects instance, concrete generalPanel entry/tail connection and complete cost verification remain absent.',ci_owner='root')
        for name,obj in [('manifest.json',manifest),('static-checks.json',receipt),('exact-inverse.json',inverse)]:
            (HERE/name).write_bytes((json.dumps(obj,ensure_ascii=False,indent=2)+'\n').encode())
    print(json.dumps(receipt,indent=2))


if __name__=='__main__':main()
