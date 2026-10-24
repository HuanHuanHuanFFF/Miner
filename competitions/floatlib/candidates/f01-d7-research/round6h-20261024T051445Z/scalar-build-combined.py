"""One authorized exact combination: cold3ff4 plus59de nativeMul converter only."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,ast,hashlib,importlib.util,json,re

HERE=Path(__file__).resolve().parent
CANDIDATES=HERE.parents[1]
ROOT=HERE.parents[4]
TARGET=CANDIDATES/'f01-d12-scalar-combined'
PARENT_SHA='3ff4eb8e3f9be968592a05f3d934b679705a3bbdeb655afb7596951611f36221'
DONOR_SHA='59de0e17223abebdd802bba98347ad8a4a7d6e90bfdca5ffd94bed3ad7005ce4'
sha=lambda raw:hashlib.sha256(raw).hexdigest()


def load(path,name):
    spec=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m


def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--write',action='store_true');args=ap.parse_args()
    parent=(CANDIDATES/'f01-d12-scalar-cold-nan-select-proof2/Kernel.lean').read_bytes()
    donor=(CANDIDATES/'f01-d12-mul-existing-convert/Kernel.lean').read_bytes()
    assert sha(parent)==PARENT_SHA and sha(donor)==DONOR_SHA
    result=parent;ops=[]
    def replace(before,after,name):
        nonlocal result
        assert result.count(before)==1,name
        at=result.index(before);previous=sha(result)
        result=result[:at]+after+result[at+len(before):]
        ops.append({'name':name,'offset_in_previous_stage':at,'before':before.decode(),'after':after.decode(),
            'before_sha256':sha(before),'after_sha256':sha(after),'previous_source_sha256':previous,'next_source_sha256':sha(result)})
    replace(b'  let result := ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y\n',
        b'  let result := R2W01b.convert x.raw.1 * R2W01b.convert y.raw.1\n','exact59de two existing converter inputs')
    replace('''  · rename_i hn
    have hi := NotNaNProbe.mul_inputs _ _ ((R7W04.nonNaN_eq_true_iff _).mp hn)
    rw [R7Native.ofFloat32Mul _ _ hi.1 hi.2,
'''.encode(),'''  · rename_i hn
    rw [R2W01c.convert_eq, R2W01c.convert_eq] at hn ⊢
    change R7W04.nonNaN (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y) = true at hn
    have hi := NotNaNProbe.mul_inputs _ _ ((R7W04.nonNaN_eq_true_iff _).mp hn)
    change ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y) = _
    rw [R7Native.ofFloat32Mul _ _ hi.1 hi.2,
'''.encode(),'exact59de converter_eq rewrite and native proof representation')
    inverse=result
    for op in reversed(ops):
        at=op['offset_in_previous_stage'];after=op['after'].encode()
        assert inverse[at:at+len(after)]==after
        inverse=inverse[:at]+op['before'].encode()+inverse[at+len(after):]
    assert inverse==parent and len(result)<=256000
    audit=load(HERE/'scalar-audit-007.py','r12_combination_seams')
    ps,pe,pnative=audit.native(parent);rs,re_,rnative=audit.native(result);_,_,dnative=audit.native(donor)
    exact_donor=dnative.replace(b'else FastMul.mul x y',b'else ScalarNaN.mul x y').replace(b'exact FastMul.mul_spec x y',b'exact ScalarNaN.mul_spec x y')
    assert rnative==exact_donor and parent[:ps]==result[:rs] and parent[pe:]==result[re_:]
    assert b'else ScalarNaN.mul x y' in rnative and b'exact ScalarNaN.mul_spec x y' in rnative
    preflight=json.loads((HERE/'scalar-cold-convert-preflight.json').read_bytes())
    assert sha(result)==preflight['projected_sha256']=='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
    parser=load(CANDIDATES/'f01-r8-combined-result-guard/build.py','r12_combined_inventory')
    old,new=parser.declarations(parent.decode()),parser.declarations(result.decode())
    assert set(old)==set(new) and all(len(v)==1 for v in new.values())
    signature=lambda raw,row:'\n'.join(raw.decode().splitlines()[row-1:]).split(':=',1)[0]
    exports={}
    for name in ['Submission.'+x for x in ('add','add_spec','mul','mul_spec','sum','sum_spec','bmm','bmm_spec')]:
        assert signature(parent,old[name][0])==signature(result,new[name][0]);exports[name]='TYPE_UNCHANGED'
    gate=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
    assert sha(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
    tree=ast.parse(gate.read_text());find=lambda name:next(n for n in tree.body if isinstance(n,ast.Assign)and any(isinstance(t,ast.Name)and t.id==name for t in n.targets))
    text=result.decode();assert not re.compile(ast.literal_eval(find('BANNED').value.args[0])).search(text)
    env={'re':re,'OPTIONS':ast.literal_eval(find('OPTIONS').value)};node=next(n for n in tree.body if isinstance(n,ast.FunctionDef)and n.name=='options')
    exec(compile(ast.Module(body=[node],type_ignores=[]),str(gate),'exec'),env);assert env['options'](text)is None
    attrs=ast.literal_eval(find('ATTRIBUTES').value)
    assert all(item.split()[-1]in attrs for group in re.findall(r'@\[([^\]]*)\]',text)for item in group.split(','))
    assert [line for line in text.splitlines()if re.search(r'\bimport\b',line)]==['import ContractTensor']
    receipts={'parent_run':40072436647,'donor_run':40073100983,'parent_and_donor_full_gate':'PASS25_INDIVIDUALLY; does not validate combination'}
    report={'parent_sha256':PARENT_SHA,'donor_sha256':DONOR_SHA,'candidate_sha256':sha(result),'candidate_bytes':len(result),
        'headroom_bytes':256000-len(result),'operations':ops,'inverse_parent_exact':True,'inverse_parent_sha256':sha(inverse),
        'only_nativeMul_chunk_changed':True,'exact59de_nativeMul_except_preserved_cold_leaves':True,
        'matches_prior_two_order_projection':True,'eight_public_types':exports,'declaration_inventory_unchanged_unique':True,
        'original_policy_static':'PASS','gate_sha256':sha(gate.read_bytes()),'resources_options_attributes_unchanged':True,
        'individual_component_receipts':receipts,'new_Lean_full_gate':'NOT_RUN','new_performance':'UNKNOWN_NOT_ADDITIVE'}
    manifest={'candidate':TARGET.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(result),'candidate_bytes':len(result),
        'created_at_utc':datetime.now(timezone.utc).isoformat(),'parent':'f01-d12-scalar-cold-nan-select-proof2','parent_sha256':PARENT_SHA,
        'donor':'f01-d12-mul-existing-convert','donor_sha256':DONOR_SHA,
        'mechanism':'Exactly59de per-input nativeMul converter and its convert_eq proof rewrite on frozen3ff4 cold-selector parent. Preserve ScalarNaN.mul/its proof cold leaves, current result guard, add,LowScale and every other parent byte. No thresholds or new numeric grid.',
        'checks':{k:report[k]for k in ('inverse_parent_exact','only_nativeMul_chunk_changed','exact59de_nativeMul_except_preserved_cold_leaves','matches_prior_two_order_projection','eight_public_types','declaration_inventory_unchanged_unique','original_policy_static')},
        'individual_component_receipts':receipts,'state':'READY_FOR_ORIGINAL_FULL_GATE','validation_mode':'full-gate',
        'proof_status':'NOT_RUN_EXACT_COMBINATION','leanchecker':'NOT_RUN','axiom_audit':'NOT_RUN','checksum':'NOT_RUN','full_gate':'NOT_RUN',
        'codegen':'NOT_RUN_EXACT_COMBINATION','performance':'UNKNOWN_NOT_ADDITIVE','attribution':'All3ff4 parent legal/source notices retained; exact59de existing-converter proof/runtime lines reused.',
        'formal_submission':'NOT_SUBMITTED','ci_owner':'Root','build_script_sha256':sha(Path(__file__).read_bytes())}
    if args.write:
        TARGET.mkdir(exist_ok=False);(TARGET/'Kernel.lean').write_bytes(result)
        for name,value in (('manifest.json',manifest),('exact-inverse.json',report)):
            (TARGET/name).write_text(json.dumps(value,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    else:
        assert (TARGET/'Kernel.lean').read_bytes()==result
        assert json.loads((TARGET/'manifest.json').read_bytes())['candidate_sha256']==sha(result)
    print(json.dumps({'candidate':TARGET.name,'sha256':sha(result),'bytes':len(result),'headroom':256000-len(result),
        'operations':len(ops),'static':'PASS','combined_Lean_full_gate':'NOT_RUN','performance':'UNKNOWN_NOT_ADDITIVE'},indent=2))


if __name__=='__main__':
    main()
