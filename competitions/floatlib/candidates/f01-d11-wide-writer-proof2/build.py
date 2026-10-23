"""Exact three proof-tactic fixes to frozen20a. No runtime or option edits.
Default dry run; --write creates source/new asset once; --verify is read-only.
"""
from argparse import ArgumentParser
from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
from types import SimpleNamespace
import ast,json,re

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[3]
R11=HERE.parent/'f01-d7-research/round7h-20261023T193125Z'
PARENT=HERE.parent/'f01-d11-wide-writer-proof/Kernel.lean'
PARENT_SHA='20a42e290817150b06095e945cf21453808471781cee799917d7c8fe73593b7f'
ASSET=R11/'review-output-wide-layout.lean'
ASSET_SHA='42a3547cd310297a2f79c636b8eb152547c8d4118f3bb66893b4762fd808bab1'
NEW_ASSET=R11/'review-output-wide-layout-proof2.lean'
LOG=HERE.parent/'f01-mul-log2-proof1/ci-runs/40041351847/download-2602218842f749ceb3c6a4245b4682f9/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-d11-wide-writer-proof/replay.log'
PARSER=HERE.parent/'f01-r8-combined-result-guard/build.py'
GATE=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'


def sha(raw):return sha256(raw).hexdigest()


def functions(raw,names,env):
    nodes=[n for n in ast.parse(raw.decode()).body if isinstance(n,ast.FunctionDef) and n.name in names]
    assert {n.name for n in nodes}==set(names)
    exec(compile(ast.Module(body=nodes,type_ignores=[]),'<pinned helpers>','exec'),env)
    return env


def construct():
    parent,old=PARENT.read_bytes(),ASSET.read_bytes()
    assert sha(parent)==PARENT_SHA and len(parent)==245000
    assert sha(old)==ASSET_SHA and len(old)==13649 and parent.endswith(old)
    asset,data,ledger=old,parent,[]
    patches=[
      ('nativeA_span hb uses successor multiplication',b'  rw [Nat.add_mul] at hb\n',b'  rw [Nat.succ_mul] at hb\n'),
      ('nativeA_span hs also has a successor left factor',b'  rw [Nat.add_mul, Nat.one_mul] at hs\n',b'  rw [Nat.succ_mul] at hs\n'),
      ('rowIndex bound proof uses successor multiplication',b'    rw [Nat.add_mul] at h\n',b'    rw [Nat.succ_mul] at h\n')]
    for name,before,after in patches:
        assert asset.count(before)==1,name
        relative=asset.index(before)
        at=len(parent)-len(old)+relative
        assert data[at:at+len(before)]==before
        updated=data[:at]+after+data[at+len(before):]
        ledger.append({'name':name,'offset_in_previous_stage':at,'before':before.decode(),'after':after.decode(),
                       'before_sha256':sha(before),'after_sha256':sha(after),
                       'previous_source_sha256':sha(data),'next_source_sha256':sha(updated)})
        asset=asset[:relative]+after+asset[relative+len(before):]
        data=updated
    assert data==parent[:-len(old)]+asset
    inverse=data
    for op in reversed(ledger):
        assert sha(inverse)==op['next_source_sha256']
        at=op['offset_in_previous_stage'];before=op['before'].encode();after=op['after'].encode()
        assert inverse[at:at+len(after)]==after
        inverse=inverse[:at]+before+inverse[at+len(after):]
        assert sha(inverse)==op['previous_source_sha256']
    assert inverse==parent and len(data)<=256000
    # Two theorem proofs and the proof field of a Fin constructor are the only
    # edited locations. rowIndex's value expression and all later defs survive.
    row_anchor=b'def rowIndex (batch m : Nat)'
    assert old[:old.index(row_anchor)].count(b'rw [Nat.add_mul] at h\n')==0
    assert old[old.index(row_anchor):].split(b', by\n',1)[0]==asset[asset.index(row_anchor):].split(b', by\n',1)[0]
    tail=b'/-- Existing Packed10 path handles exactly the remaining zero to three rows.'
    assert old[old.index(tail):]==asset[asset.index(tail):]
    parser_raw=PARSER.read_bytes();assert sha(parser_raw)=='58662bf7218de54978d999bfb424975732cf845708869e1d611dd712d7470f22'
    inv=functions(parser_raw,['strip_comments','declarations'],{'re':re})
    assert inv['declarations'](parent.decode())==inv['declarations'](data.decode())
    gate_raw=GATE.read_bytes();assert sha(gate_raw)=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
    assignments={t.id:n.value for n in ast.parse(gate_raw.decode()).body if isinstance(n,ast.Assign) for t in n.targets if isinstance(t,ast.Name)}
    env={'re':re,'Path':Path,'Verdict':object,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')},
      'OPTIONS':ast.literal_eval(assignments['OPTIONS']),'ATTRIBUTES':ast.literal_eval(assignments['ATTRIBUTES']),
      'BANNED':re.compile(ast.literal_eval(assignments['BANNED'].args[0]))}
    env=functions(gate_raw,['policy','options'],env)
    assert env['policy'](SimpleNamespace(read_text=lambda:data.decode()),SimpleNamespace(slot='full')) is None
    receipt={'candidate':HERE.name,'candidate_sha256':sha(data),'candidate_bytes':len(data),'headroom_bytes':256000-len(data),
      'parent_sha256':PARENT_SHA,'old_asset_sha256':ASSET_SHA,'new_asset_sha256':sha(asset),'new_asset_bytes':len(asset),
      'builder_sha256':sha(Path(__file__).read_bytes()),'original_log_sha256':sha(LOG.read_bytes()),
      'checks':{'exact_three_proof_edits':'PASS','complete_inverse_to20a':'PASS','same_declarations_and_line_numbers':'PASS',
        'active_base_prefix_and_four_specs_unchanged':'PASS','runtime_value_expressions_unchanged':'PASS','original_policy':'PASS',
        'resource_options_and_author_notices_unchanged':'PASS'},
      'validation_mode':'STATEMENT_DIAGNOSTIC','proof_status':'NOT_RUN','kernel_replay':'NOT_RUN','axiom_audit':'NOT_RUN',
      'checksum':'NOT_RUN','full_gate':'NOT_RUN','matrix_algorithm_acceptance':'NOT_APPLICABLE_NO_ACTIVE_WIDE_ENTRY',
      'performance':'NOT_APPLICABLE_WIDE_UNUSED','formal_submission':'NOT_SUBMITTED'}
    return data,asset,ledger,receipt


def main():
    ap=ArgumentParser();m=ap.add_mutually_exclusive_group();m.add_argument('--write',action='store_true');m.add_argument('--verify',action='store_true');args=ap.parse_args()
    data,asset,ledger,receipt=construct()
    if args.verify:
        assert (HERE/'Kernel.lean').read_bytes()==data and (HERE/'wide-layout-proof2.lean').read_bytes()==asset and NEW_ASSET.read_bytes()==asset
    elif args.write:
        names=['Kernel.lean','wide-layout-proof2.lean','manifest.json','static-checks.json','exact-inverse.json']
        assert not any((HERE/n).exists() for n in names) and not NEW_ASSET.exists(),'Refuse overwrite'
        (HERE/'Kernel.lean').write_bytes(data);(HERE/'wide-layout-proof2.lean').write_bytes(asset);NEW_ASSET.write_bytes(asset)
        manifest=dict(receipt,candidate_file='Kernel.lean',parent='f01-d11-wide-writer-proof',created_at_utc=datetime.now(timezone.utc).isoformat(),
          repair='Only nativeA_span hb/hs and rowIndex bound tactics change from add_mul to succ_mul; the inequalities are Nat.succ products. All other bytes unchanged.',
          failure='924 run40041351847: rewrite failures6262/6399. hs was not yet reached and has same successor shape. Compiler recovery warnings are not source proof admissions.',
          missing='Projects still requires concrete wordLoop/buildTiles wiring; no new active wide entry.',ci_owner='root')
        for name,obj in [('manifest.json',manifest),('static-checks.json',receipt),('exact-inverse.json',ledger)]:
            (HERE/name).write_bytes((json.dumps(obj,ensure_ascii=False,indent=2)+'\n').encode())
    print(json.dumps(receipt,indent=2))


if __name__=='__main__':main()
