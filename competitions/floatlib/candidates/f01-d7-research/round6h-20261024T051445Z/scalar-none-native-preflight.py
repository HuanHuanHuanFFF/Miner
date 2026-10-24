"""Freeze None-native proof/cost preflight; reports only, no Kernel or CI."""
from pathlib import Path
import hashlib,importlib.util,json

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
CANDIDATES=HERE.parents[1]
sha=lambda raw:hashlib.sha256(raw).hexdigest()


def main():
    source=(CANDIDATES/'f01-d12-scalar-combined/Kernel.lean').read_bytes();assert sha(source)=='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
    proof=(HERE/'scalar-none-native-proof.lean').read_bytes()
    spec=importlib.util.spec_from_file_location('r12_none_inventory',CANDIDATES/'f01-r8-combined-result-guard/build.py')
    parser=importlib.util.module_from_spec(spec);spec.loader.exec_module(parser)
    decl=parser.declarations(source.decode());lines=source.decode().splitlines(keepends=True);starts=sorted(v[0]for v in decl.values())
    bridges={}
    for name in ('Submission.R7Native.ofFloat32Add','Submission.R7Native.ofFloat32Mul','Submission.NotNaNProbe.roundtrip',
                 'Submission.DWordNaN.rawChoose_eq','Submission.DWordNaN.selected_add','Submission.DWordNaN.selected_mul',
                 'Submission.R7W05.model_toModel_isNaN','Submission.R7W05.toFloat32_isNaN','R7W02.exec_toModel_eq_rawModel',
                 'R2W01c.convert_eq'):
        row=decl[name][0];end=next((x-1 for x in starts if x>row),len(lines));chunk=''.join(lines[row-1:end]).encode()
        bridges[name]={'line':row,'declaration_chunk_sha256':sha(chunk),'bytes':len(chunk),'signature':chunk.decode().split(':=',1)[0]}
    classification=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W05/original-extracted/R7-W05/public/FloatLib/FloatLib/Floats/Formats/BinaryInterchange/Dyadic/Classification.lean'
    library=classification.read_bytes();assert b'chooseNaN2 x y = none' in library and b'isNaN x = false' in library and b'isNaN y = false' in library
    scalar=json.loads((HERE/'scalar-none-scalar-counts.json').read_bytes());tensor=json.loads((HERE/'scalar-none-tensor-counts.json').read_bytes())
    # Moving the two closed existing classifier declarations contributes no
    # duplicated theorem body; reserve a conservative wrapper/leaf allowance.
    conservative_projected_max=len(source)+len(proof)+700
    assert conservative_projected_max<=256000
    report={'state':'PROOF_AND_COST_PREFLIGHT_ONLY_NO_KERNEL','parent_sha256':sha(source),'parent_bytes':len(source),
        'scratch_proof_sha256':sha(proof),'scratch_bytes':len(proof),'all_new_proof_acceptance':'NOT_RUN',
        'existing_bridge_inventory':bridges,
        'primary_choose_none':{'path':classification.relative_to(ROOT).as_posix(),'line':162,'sha256':sha(library),
            'type':'chooseNaN2 x y = none iff isNaN x=false and isNaN y=false'},
        'proof_chain':['rawChoose_eq with hnone rewrites Model.chooseNaN2(...)=none; Option.map_none reduces by rfl.',
            'Model.chooseNaN2_eq_none_iff gives exact raw Model.isNaN false for both operands.',
            'R7W02.exec_toModel_eq_rawModel connects original raw words to the actual Competition carrier.',
            'R7W05.toFloat32_isNaN transports those exact classifications to both native Float32 input predicates.',
            'R7Native.ofFloat32Add/Mul requires only input isNaN=false, includingInf; no finite or result-nonNaN hypothesis.',
            'NotNaNProbe.roundtrip restores original raw input words; ExecFloat.Proof.*_eq_spec reaches unchanged all-input spec.',
            'Some branch remains exact DWordNaN.selected_add/mul, preserving signaling-first sign/payload/quieting.',
            'None returns ofFloat32(result) where result is the already computed caller let; theorem hr is rfl and erased, not another runtime calculation.'],
        'invalid_result_allowed':True,'finite_only_NativeBridge_not_used':True,'result_NaN_implies_exp255_bridge_not_needed':True,
        'source_order_plan':'Move the exact two closed R7W05 model_toModel_isNaN/toFloat32_isNaN theorem chunks plus explicit opens into an earlier reopened Submission.R7W05 before new helpers. Their later references keep identical names; fd scopes and all runtime definitions stay fixed.',
        'namespace_plan':'Scratch is append-context namespace Submission.NoneNativeProof. When inserting inside the existing Submission scope use namespace NoneNativeProof/end NoneNativeProof to avoid accidental Submission.Submission nesting.',
        'unique_candidate_plan':'One candidate on exactdf5c: retain original let result and nonNaN fast branch; replace only add/nativeMul NaN else calls with addColdResult/mulColdResult x y result, cold proof leaves use the new specs at rfl. Keep LowScale, old ScalarNaN functions, all Some selector bodies and all tensor definitions unchanged.',
        'conservative_source_upper_bound':conservative_projected_max,'conservative_headroom':256000-conservative_projected_max,
        'actual_source_size':'UNKNOWN_UNTIL_AUTHORIZED_BUILDER; conservative bound includes scratch plus700B wrapper/leaf allowance and moves classifier bodies without duplication.',
        'scalar_input_counts':{'sha256':sha((HERE/'scalar-none-scalar-counts.json').read_bytes()),'rows':[{k:r[k]for k in ('run','totals')}for r in scalar['runs']],
            'scope':'Input-generator reconstruction, not hardware call measurement; non-special finite domains were skipped after checking generator fields.'},
        'BMM_prefix_model_counts':{'sha256':sha((HERE/'scalar-none-tensor-counts.json').read_bytes()),'state':tensor['state'],'totals':tensor['totals'],
            'scope':tensor['scope'],'official_current_checksum_anchor':tensor['current_official_checksum_anchor']},
        'cost_assessment':'Standalone scalar None is rare in exposed007/009 (add32/mul3 and add1/mul27). BMM specials/extremes source model suggests nontrivial invalid None endpoints (add306/mul25 and add1229/mul14), but exact compiled event counts and stage costs remain UNKNOWN. This targets expensive software None fallback without per-finite-prefix classification, so it is more controlled than raw-first replay, yet it has no measured gain.',
        'already_realized_gain_not_reclaimed':'0079.7409whole percentage points were already gained by coldSome; do not count them as remaining None savings.',
        'first_failure_points':['Lean elaboration of Option.map_none and actual carrier/model rewrites in the new scratch chain.',
            'Correct early placement of two classifier proofs without duplicating names, changing global opens/options or introducing circular references.',
            'Actual generated caller must reuse existing result, preserve ordinary path, preserve Some word priority and remove generic None fallback; extra result liveness/spills can offset savings.',
            'Complete original gate includinginvalidInf operations,NaN payloads,±0 and subnormals; then whole-path timing vs exactdf5c rather than summing component gains.'],
        'decision':'CONDITIONAL_GO_ONE_SHORT_STATEMENT_CANDIDATE_IF_ROOT_AUTHORIZES; mathematical chain uses only existing permitted lemmas, but exact new proof and useful net gain unverified.',
        'Kernel_or_CI_generation':'NOT_AUTHORIZED_NOT_DONE','performance':'UNKNOWN_NOT_ADDITIVE'}
    (HERE/'scalar-none-native-preflight.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'state':report['state'],'scratch_bytes':len(proof),'conservative_source_upper_bound':conservative_projected_max,
        'conservative_headroom':report['conservative_headroom'],'bridges':len(bridges),'Kernel_written':False},indent=2))


if __name__=='__main__':
    main()
