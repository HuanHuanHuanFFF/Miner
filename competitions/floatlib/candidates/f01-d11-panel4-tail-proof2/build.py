"""Two proof-only repairs to frozen f767; no runtime or old-asset edits.
Dry run by default. --write creates once; --verify only reads. No Lean/Git/CI.
"""
from argparse import ArgumentParser
from datetime import datetime,timezone
from hashlib import sha256
from pathlib import Path
from types import SimpleNamespace
import ast,importlib.util,json,re,sys

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[3]
PARENT=HERE.parent/'f01-d11-panel4-tail-proof/Kernel.lean'
PARENT_SHA='f767631343de86faebe2296cad41aae60d0e2ae57eb3b5748d3308f8389f915b'
OLD_BUILDER=HERE.parent/'f01-d11-panel4-tail-proof/build.py'
OLD_BUILDER_SHA='ca9e0c37a66a01487b0da83419ea881bf209e9177853a764fd57f94309eef70b'
LOG=HERE.parent/'f01-mul-log2-proof1/ci-runs/40047532920/download-d88176a064404704b0373b609dfd077e/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-d11-panel4-tail-proof/replay.log'


def sha(raw):return sha256(raw).hexdigest()


def construct():
    assert sha(OLD_BUILDER.read_bytes())==OLD_BUILDER_SHA
    sys.dont_write_bytecode=True
    spec=importlib.util.spec_from_file_location('frozen_f767_constructor',OLD_BUILDER);old=importlib.util.module_from_spec(spec);spec.loader.exec_module(old)
    reproduced,old_asset,_,_=old.construct()
    parent=PARENT.read_bytes();assert parent==reproduced and sha(parent)==PARENT_SHA
    data=parent;ledger=[]
    patches=[('dot10_shift: remove no-progress dsimp after dif_pos simp',
      '    dsimp only\n    rw [hread ⟨k, hk⟩]\n','    rw [hread ⟨k, hk⟩]\n'),
      ('group_prefix: normalize all add_mul occurrences and association',
      '        by rw [Nat.add_mul], Packed10Index.runDot_eq]\n',
      '        by simp only [Nat.add_mul, Nat.add_assoc], Packed10Index.runDot_eq]\n')]
    for name,before,after in patches:
        before,after=before.encode(),after.encode();assert data.count(before)==1
        at=data.index(before);assert at>=229218
        new=data[:at]+after+data[at+len(before):]
        ledger.append({'name':name,'offset_in_previous_stage':at,'before':before.decode(),'after':after.decode(),
          'before_sha256':sha(before),'after_sha256':sha(after),'previous_source_sha256':sha(data),'next_source_sha256':sha(new)})
        data=new
    inverse=data
    for op in reversed(ledger):
        assert sha(inverse)==op['next_source_sha256'];at=op['offset_in_previous_stage'];before=op['before'].encode();after=op['after'].encode()
        assert inverse[at:at+len(after)]==after
        inverse=inverse[:at]+before+inverse[at+len(after):]
        assert sha(inverse)==op['previous_source_sha256']
    assert inverse==parent and data[:229218]==parent[:229218]
    asset=data[229218:];assert len(data)<=256000
    parser=old.functions(old.PARSER.read_bytes(),['strip_comments','declarations'],{'re':re})
    a,b=[parser['declarations'](x.decode()) for x in (parent,data)]
    assert {k:len(v) for k,v in a.items()}=={k:len(v) for k,v in b.items()}
    g=old.GATE.read_bytes();tree=ast.parse(g.decode());assign={t.id:n.value for n in tree.body if isinstance(n,ast.Assign) for t in n.targets if isinstance(t,ast.Name)}
    env={'re':re,'Path':Path,'Verdict':object,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')},'OPTIONS':ast.literal_eval(assign['OPTIONS']),
      'ATTRIBUTES':ast.literal_eval(assign['ATTRIBUTES']),'BANNED':re.compile(ast.literal_eval(assign['BANNED'].args[0]))}
    env=old.functions(g,['policy','options'],env);assert env['policy'](SimpleNamespace(read_text=lambda:data.decode()),SimpleNamespace(slot='full')) is None
    receipt={'candidate':HERE.name,'candidate_sha256':sha(data),'candidate_bytes':len(data),'headroom_bytes':256000-len(data),
      'parent_sha256':PARENT_SHA,'original_9a_runtime_prefix_bytes':229218,'repaired_asset_sha256':sha(asset),'repaired_asset_bytes':len(asset),
      'builder_sha256':sha(Path(__file__).read_bytes()),'original_replay_log_sha256':sha(LOG.read_bytes()),
      'checks':{'exact_two_proof_only_edits':'PASS','full_inverse_to_f767':'PASS','same_12_tail_declarations_and_all_old_names':'PASS',
        'runtime_values_and_original9a_prefix_unchanged':'PASS','four_specs_resource_options_and_author_notices_unchanged':'PASS','original_policy':'PASS'},
      'validation_mode':'STATEMENT_DIAGNOSTIC','proof_status':'NOT_RUN','kernel_replay':'NOT_RUN','axiom_audit':'NOT_RUN','checksum':'NOT_RUN',
      'full_gate':'NOT_RUN','matrix_algorithm_acceptance':'NOT_APPLICABLE_NO_ACTIVE_PANEL_OR_TAIL_ENTRY','performance':'NOT_APPLICABLE_UNUSED_ASSETS',
      'formal_submission':'NOT_SUBMITTED'}
    return data,asset,ledger,receipt


def main():
    ap=ArgumentParser();m=ap.add_mutually_exclusive_group();m.add_argument('--write',action='store_true');m.add_argument('--verify',action='store_true');args=ap.parse_args()
    data,asset,ledger,receipt=construct()
    if args.verify:assert (HERE/'Kernel.lean').read_bytes()==data and (HERE/'panel4-tail-proof2.lean').read_bytes()==asset
    elif args.write:
        names=['Kernel.lean','panel4-tail-proof2.lean','manifest.json','static-checks.json','exact-inverse.json']
        assert not any((HERE/n).exists() for n in names),'Refuse overwrite'
        (HERE/'Kernel.lean').write_bytes(data);(HERE/'panel4-tail-proof2.lean').write_bytes(asset)
        manifest=dict(receipt,candidate_file='Kernel.lean',parent='f01-d11-panel4-tail-proof',created_at_utc=datetime.now(timezone.utc).isoformat(),
          repair='Only dot10_shift redundant dsimp removal and group_prefix add_mul/association proof normalization; runtime unchanged.',
          trigger='934 run40047532920:6224 dsimp made no progress;6298 leftover expanded base equality. Newproof has not run.',ci_owner='root')
        for name,obj in [('manifest.json',manifest),('static-checks.json',receipt),('exact-inverse.json',ledger)]:
            (HERE/name).write_bytes((json.dumps(obj,ensure_ascii=False,indent=2)+'\n').encode())
    print(json.dumps(receipt,indent=2))


if __name__=='__main__':main()
