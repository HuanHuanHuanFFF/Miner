"""Build one exact None-result reuse candidate; no Git, Lean or CI execution."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,ast,hashlib,importlib.util,json,re

HERE=Path(__file__).resolve().parent
CANDIDATES=HERE.parents[1]
ROOT=HERE.parents[4]
TARGET=CANDIDATES/'f01-d12-none-native-result'
PARENT_SHA='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
sha=lambda raw:hashlib.sha256(raw).hexdigest()


def load(path,name):
    spec=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m


def extract(raw,begin,end):
    assert raw.count(begin)==raw.count(end)==1
    lo=raw.index(begin);hi=raw.index(end,lo)+len(end);return raw[lo:hi]


def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--write',action='store_true');args=ap.parse_args()
    parent=(CANDIDATES/'f01-d12-scalar-combined/Kernel.lean').read_bytes();assert sha(parent)==PARENT_SHA
    scratch=(HERE/'scalar-none-native-proof.lean').read_bytes()
    model=extract(parent,b'theorem model_toModel_isNaN (x : Model FloatFormat.binary32)',
        b'    simp_all [Float.Model.UnpackedFloat.isNaN, Model.IEEE.isNaN]\n')
    classifier=extract(parent,b'theorem toFloat32_isNaN (x : Binary32)',b'  exact model_toModel_isNaN _\n')
    model_copy=model.replace(b'theorem model_toModel_isNaN',b'theorem none_model_toModel_isNaN')
    classifier_copy=classifier.replace(b'theorem toFloat32_isNaN',b'theorem none_toFloat32_isNaN').replace(
        b'exact model_toModel_isNaN _',b'exact none_model_toModel_isNaN _')
    # Extract only actual theorem bodies, not trailing documentation belonging
    # to their next declarations. Original declarations/comments never move.
    body=scratch[scratch.index(b'namespace Submission.NoneNativeProof\n'):]
    body=body.replace(b'namespace Submission.NoneNativeProof\n',b'namespace NoneNativeProof\n',1).replace(
        b'end Submission.NoneNativeProof\n',b'end NoneNativeProof\n')
    body=body.replace(b'R7W05.toFloat32_isNaN',b'none_toFloat32_isNaN')
    anchor=b'open FloatLib.Floats.Formats.BinaryInterchange\n\n'
    assert body.count(anchor)==1
    body=body.replace(anchor,anchor+b'open Float.Model.UnpackedFloat\n\n'+model_copy+b'\n'+classifier_copy+b'\n',1)
    notice=b'/- R12 None-result reuse. Local classifier proofs copy the accepted R7W05\nproof bodies under fresh names; the original declarations and all their\ncomments remain in their original positions. New integration is NOT_RUN. -/\n'
    insertion=b'\n'+notice+body+b'\n'
    result=parent;ops=[]
    def replace(before,after,name):
        nonlocal result
        assert result.count(before)==1,name
        at=result.index(before);old=sha(result);result=result[:at]+after+result[at+len(before):]
        ops.append({'name':name,'offset_in_previous_stage':at,'before':before.decode(),'after':after.decode(),
            'before_sha256':sha(before),'after_sha256':sha(after),'previous_source_sha256':old,'next_source_sha256':sha(result)})
    replace(b'end ScalarNaN\n',b'end ScalarNaN\n'+insertion,'insert copied closed classifiers and full-input None-native helpers')
    replace(b'  else ScalarNaN.add x y\n',b'  else NoneNativeProof.addColdResult x y result\n','reuse computed result only in exported add NaN cold branch')
    replace('  · exact ScalarNaN.add_spec x y\n'.encode(),'  · exact NoneNativeProof.addColdResult_spec x y _ rfl\n'.encode(),'new add cold proof with definitional result identity')
    replace(b'  else ScalarNaN.mul x y\n',b'  else NoneNativeProof.mulColdResult x y result\n','reuse computed result only in nativeMul NaN cold branch')
    replace('  · exact ScalarNaN.mul_spec x y\n'.encode(),'  · exact NoneNativeProof.mulColdResult_spec x y _ rfl\n'.encode(),'new multiply cold proof with definitional result identity')
    assert len(result)<=256000
    inverse=result
    for op in reversed(ops):
        at=op['offset_in_previous_stage'];after=op['after'].encode();assert inverse[at:at+len(after)]==after
        inverse=inverse[:at]+op['before'].encode()+inverse[at+len(after):]
    assert inverse==parent
    parser=load(CANDIDATES/'f01-r8-combined-result-guard/build.py','r12_none_source_inventory')
    old,new=parser.declarations(parent.decode()),parser.declarations(result.decode())
    assert all(len(v)==1 for v in new.values())and set(old)<=set(new)
    public={};signature=lambda raw,row:'\n'.join(raw.decode().splitlines()[row-1:]).split(':=',1)[0]
    for name in ['Submission.'+x for x in ('add','add_spec','mul','mul_spec','sum','sum_spec','bmm','bmm_spec')]:
        assert signature(parent,old[name][0])==signature(result,new[name][0]);public[name]='TYPE_UNCHANGED'
    # Exact classifier original bodies remain once at the original later
    # location; no source notice/comment is removed or repurposed.
    assert parent.count(model)==result.count(model)==1 and parent.count(classifier)==result.count(classifier)==1
    source_lines=parent.decode().splitlines(keepends=True);new_lines=result.decode().splitlines(keepends=True)
    plain=parser.strip_comments(parent.decode()).splitlines();ostarts=sorted(v[0]for v in old.values());nstarts=sorted(v[0]for v in new.values())
    runtime_checks={}
    for name,rows in old.items():
        row=rows[0]
        if not re.search(r'\b(def|abbrev)\b',plain[row-1]):continue
        def chunk(lines,starts,at):
            end=next((x-1 for x in starts if x>at),len(lines));return ''.join(lines[at-1:end]).encode()
        a,b=chunk(source_lines,ostarts,row),chunk(new_lines,nstarts,new[name][0])
        if name in ('Submission.add','Submission.nativeMul'):
            assert a.split(b'\n  else ',1)[0]==b.split(b'\n  else ',1)[0]
            runtime_checks[name]={'ordinary_let_result_guard_fast_prefix_unchanged':True,'before_sha256':sha(a),'after_sha256':sha(b)}
        elif name=='Submission.ScalarNaN.mul':
            # Its chunk acquires the new namespace prefix at the end, but its
            # actual definition and old spec are untouched (full inverse binds).
            assert a in b
            runtime_checks[name]={'original_chunk_preserved_as_prefix':True,'sha256':sha(a)}
        else:
            assert a==b,name
            runtime_checks[name]={'unchanged':True,'sha256':sha(a)}
    assert b'| some w => FastMul.ofBits w\n  | none => ExecFloat.Binary.ofFloat32 result' in body
    assert body.count(b'| none => ExecFloat.Binary.ofFloat32 result')==2
    # None helper definitions contain no FP recomputation; proof equations do.
    for function in (b'addColdResult',b'mulColdResult'):
        start=body.index(b'@[inline] def '+function);stop=body.index(b'\ntheorem ',start)
        definition=body[start:stop]
        assert b'R2W01b.convert'not in definition and b'result' in definition
    gate=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
    assert sha(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
    tree=ast.parse(gate.read_text());find=lambda name:next(n for n in tree.body if isinstance(n,ast.Assign)and any(isinstance(t,ast.Name)and t.id==name for t in n.targets))
    text=result.decode();assert not re.compile(ast.literal_eval(find('BANNED').value.args[0])).search(text)
    env={'re':re,'OPTIONS':ast.literal_eval(find('OPTIONS').value)};node=next(n for n in tree.body if isinstance(n,ast.FunctionDef)and n.name=='options')
    exec(compile(ast.Module(body=[node],type_ignores=[]),str(gate),'exec'),env);assert env['options'](text)is None
    attrs=ast.literal_eval(find('ATTRIBUTES').value);assert all(item.split()[-1]in attrs for group in re.findall(r'@\[([^\]]*)\]',text)for item in group.split(','))
    assert [line for line in text.splitlines()if re.search(r'\bimport\b',line)]==['import ContractTensor']
    report={'parent_sha256':PARENT_SHA,'candidate_sha256':sha(result),'candidate_bytes':len(result),'headroom_bytes':256000-len(result),
        'operations':ops,'inverse_parent_exact':True,'eight_public_types':public,'all_parent_declarations_preserved_unique':True,
        'new_declarations':sorted(set(new)-set(old)),'existing_runtime_checks':runtime_checks,
        'copied_classifiers':{'model_source_sha256':sha(model),'model_copy_sha256':sha(model_copy),'native_source_sha256':sha(classifier),'native_copy_sha256':sha(classifier_copy),
            'originals_and_all_original_comments_unchanged':True,'copies_exclude_next_declaration_comments':True},
        'ordinary_prefixes_unchanged':True,'Some_selection_body_unchanged':True,'None_uses_existing_result_without_FP_recomputation':True,
        'original_policy_static':'PASS','resources_options_unchanged':True,'new_proof_acceptance':'NOT_RUN','performance':'UNKNOWN'}
    manifest={'candidate':TARGET.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(result),'candidate_bytes':len(result),
        'created_at_utc':datetime.now(timezone.utc).isoformat(),'parent':'f01-d12-scalar-combined','parent_sha256':PARENT_SHA,
        'mechanism':'Preserve parent native let/result/selfguard/nonNaN branch and exact rawSome priority. Only already-entered cold branch passes computedFloat32 result to new helper; rawChoose None returns ofFloat32 result, avoiding generic software fallback and a second FP calculation.',
        'proof_route':'rawChoose None→Model.chooseNaN2 None→both model/native inputs nonNaN→R7Native add/mul+exact input roundtrip. Copied closed classifiers have fresh local names; originals/comments remain. Result identity is rfl, with no result-nonNaN/finite assumption.',
        'checks':{k:report[k]for k in ('inverse_parent_exact','eight_public_types','all_parent_declarations_preserved_unique','ordinary_prefixes_unchanged','Some_selection_body_unchanged','None_uses_existing_result_without_FP_recomputation','original_policy_static','resources_options_unchanged')},
        'evidence_links':['scalar-none-native-preflight.json','scalar-none-scalar-counts.json','scalar-none-tensor-counts.json'],
        'opportunity_boundary':'Scalar None is rare; BMM source-model invalid events are not compiled execution counts or a timing guarantee. Existing9.7409point coldSome gain is already realized and is not projected again.',
        'state':'READY_FOR_STATEMENT','validation_mode':'statement first, then complete original gate','proof_status':'NOT_RUN_EXACT_NEW_BRIDGE',
        'leanchecker':'NOT_RUN','axiom_audit':'NOT_RUN','checksum':'NOT_RUN','full_gate':'NOT_RUN','codegen':'NOT_RUN','performance':'UNKNOWN_NOT_ADDITIVE',
        'attribution':'All parent legal/source comments and classifier declarations retained in original order. Newnamespace copies exact R7W05 proof bodies with only local-name references adapted; new bridge/runtime integration remains unverified.',
        'formal_submission':'NOT_SUBMITTED','ci_owner':'Root','build_script_sha256':sha(Path(__file__).read_bytes())}
    if args.write:
        TARGET.mkdir(exist_ok=False);(TARGET/'Kernel.lean').write_bytes(result)
        for name,value in (('manifest.json',manifest),('exact-inverse.json',report)):
            (TARGET/name).write_text(json.dumps(value,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    else:
        assert (TARGET/'Kernel.lean').read_bytes()==result
        assert json.loads((TARGET/'manifest.json').read_bytes())['candidate_sha256']==sha(result)
    print(json.dumps({'candidate':TARGET.name,'sha256':sha(result),'bytes':len(result),'headroom':256000-len(result),
        'operations':len(ops),'new_declarations':len(report['new_declarations']),'static':'PASS','actual_Lean':'NOT_RUN'},indent=2))


if __name__=='__main__':
    main()
