"""Read-only actual015 diagnostic-C owner coverage; no tests/compiler/gate rerun."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
RUN=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40079721194'
sha=lambda raw:hashlib.sha256(raw).hexdigest()


def main():
    helper=HERE/'capture-mainfull.py';before=sha(helper.read_bytes())
    assert before=='76ef3176ca1c91026d3c0d9109e40944b541d11aa9e6caa5873cf3ff82ee98cf'
    spec=importlib.util.spec_from_file_location('r12_actual015_selector',helper)
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    index_raw=(RUN/'original-artifact-hashes.json').read_bytes();index=json.loads(index_raw)
    base=RUN/index['directory'];relative='diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r12-column4-narrow'
    folder=base/relative;files={}
    for path in sorted(folder.iterdir()):
        if path.is_file():
            raw=path.read_bytes();key=path.relative_to(base).as_posix();expected=index['files'][key]
            assert len(raw)==expected['bytes']and sha(raw)==expected['sha256']
            files[path.name]={'sha256':sha(raw),'bytes':len(raw),'original_artifact_index_match':True}
    c_index=json.loads((folder/'candidate-c-index.json').read_bytes())
    assert all(x['kernel_sha256']=='da09fb59fa456b498af6bde48d54adcd37f85c4ba7df272163b184a2b83038c4'for x in c_index)
    by_module={row['module']:row for row in c_index}
    for row in c_index:assert sha((folder/row['file']).read_bytes())==row['sha256']
    source=(folder/by_module['Submission']['file']).read_bytes()
    definitions=m.c_functions(source)['defined_functions']
    owned=[n for n in definitions if any(x in n for x in ('Narrow4','Packed4Index','Packed4_packB'))or n=='lp_competition_Submission_Packed10Index_loop___redArg']
    coverage=[{'symbol':n,'column4_selection':m.column4_symbol_info(n)}for n in owned]
    required=['lp_competition_Fin_foldl_loop___at___00Submission_Narrow4_core_spec__'+str(i)for i in (0,1)]
    required+=['lp_competition_Submission_Narrow4_row___redArg___lam__0','lp_competition_Submission_Packed4Index_loop',
        'lp_competition_Submission_Packed4Index_loop___redArg','lp_competition_Submission_Packed4_packB',
        *['lp_competition_Submission_Packed4_packB___lam__'+str(i)for i in (0,1,2)],
        'lp_competition_Submission_Packed10Index_loop___redArg']
    assert all(n in definitions and m.column4_symbol_info(n)is not None for n in required)
    intentional=[n for n in owned if m.column4_symbol_info(n)is None]
    assert all('___boxed'in n or 'Narrow4_batchIndex'in n or 'Narrow4_firstGroup'in n for n in intentional)
    verdict=json.loads((folder/'diagnostic-only-verdict.json').read_bytes());assert verdict['passed']and verdict['diagnostic_only']
    assert sha(helper.read_bytes())==before
    report={'state':'PASS_ACTUAL_DIAGNOSTIC_C_NAME_COVERAGE','recorded_at_utc':datetime.now(timezone.utc).isoformat(),
        'run':40079721194,'source_commit':index['artifact']['workflow_run']['head_sha'],
        'candidate_sha256':'da09fb59fa456b498af6bde48d54adcd37f85c4ba7df272163b184a2b83038c4',
        'helper_sha256_before':before,'helper_sha256_after':sha(helper.read_bytes()),'helper_changed':False,
        'original_artifact_index_sha256':sha(index_raw),'diagnostic_directory':folder.relative_to(ROOT).as_posix(),
        'files':files,'candidate_c_index':c_index,'required_actual_symbols':required,'actual_owned_definitions':coverage,
        'critical_coverage_missing':[],'intentional_exclusions':intentional,
        'actual_producer':'Narrow4_row___redArg___lam__0. Fin.foldl core emits spec0/1; no assumed coreSpec2 lambda is claimed.',
        'owned_ofFn_specializations':'NOT_EMITTED_IN_THIS_C; actual packB lam0/1/2 are covered. Existing pattern remains preparatory only.',
        'scope':'Original015 diagnostic statement replay builds and links the candidate, then saves its C. This is not the original timed full-gate object or16 machine-code evidence. No nm/asm/compilation/gate rerun here.',
        'existing_11_tests':'NOT_RERUN','actual16_nm_assembly':'UNKNOWN_PENDING_CAPTURE'}
    (HERE/'scalar-015-column4-symbol-coverage.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'state':report['state'],'files_rehashed':len(files),'critical_symbols_covered':len(required),
        'owned_selected':sum(x['column4_selection']is not None for x in coverage),'missing':[],'helper_changed':False},indent=2))


if __name__=='__main__':main()
