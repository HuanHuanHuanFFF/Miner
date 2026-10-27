"""AST/hash, preparation and synthetic row math only; no Lean/build/benchmark."""
import ast
from copy import deepcopy
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
from pathlib import Path
from types import SimpleNamespace
import sys

sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
def main():
    source=ROOT/'competitions/floatlib/candidates/f01-r19-dev-direct-bias-runtime1/Kernel.lean'
    draft=HERE/'harness-draft.py';ast.parse(draft.read_text())
    spec=importlib.util.spec_from_file_location('harness_local_fixture',draft);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    assert m.sha(source)==m.SOURCE
    assert hashlib.sha256(source.read_bytes()[:226829]).hexdigest()=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
    lean=(HERE/'R19RuntimeCostMain.lean').read_text();assert 'diagnosticEntry' not in lean and '#eval' not in lean and 'unsafe' not in lean and 'extern' not in lean and 'set_option' not in lean
    fixture=HERE/'preparation-fixture';lib=fixture/'lean';work=lib/'work';build=lib/'.lake/build';layer=fixture/'layer'
    for p in [work,build/'ir',build/'bin',lib/'bench',lib/'contract',layer/'upper'] :p.mkdir(parents=True,exist_ok=True)
    config=b'import Lake\nopen Lake DSL\npackage competition where\nlean_exe benchFull where\n  srcDir := "bench"\n  root := `MainFull\n'
    (lib/'lakefile.lean').write_bytes(config);(work/'Submission.lean').write_bytes(source.read_bytes())
    for p in [fixture/'gate.py',fixture/'benchmark_suite.py',lib/'lake-manifest.json',lib/'lean-toolchain',build/'bin/benchFull',build/'ir/MainFull.c',build/'ir/Submission.c',build/'ir/MainFull.c.o.export',build/'ir/Submission.c.o.export']:
        p.write_bytes(b'MOCK_INPUT_NOT_REAL_BUILD\n')
    (fixture/'suites').mkdir(exist_ok=True);(fixture/'suites/public-v2.json').write_bytes(b'{}\n')
    g=SimpleNamespace(_SANDBOX=True,STAGES=[('statement',None)],WORK=work/'Submission.lean',LIB=lib,HERE=fixture,BUILD=build,LAYER=layer,LAKE='MOCK_NEVER_EXECUTED',_BUILD_TIMEOUT=1800)
    out=fixture/'output';prepared=m.prepare(g,source,out)
    assert (work/'R19RuntimeCostLake.lean').read_bytes().startswith(config)
    assert (lib/'lakefile.lean').read_bytes()==config
    assert prepared['build_argv'][1:]==['-f','work/R19RuntimeCostLake.lean','build','r19RuntimeCost']
    assert m.official_sources(g)==prepared['official_before'] and m.original_build(g)==prepared['original_build_before']
    m.cleanup_owned(prepared)
    (lib/'lakefile.lean').write_bytes(config+b'  moreLeancArgs := #["-ffast-math"]\n')
    try:m.prepare(g,source,out)
    except RuntimeError:pass
    else:raise AssertionError('Unsupported original target flags not rejected')
    (lib/'lakefile.lean').write_bytes(config)
    parser=m.load_module(m.R13,'reused_parser_test');checks=[]
    for seed,expected in m.PLANS:
        p=HERE/f'plan-{seed}.json';assert m.sha(p)==expected;plan=json.loads(p.read_bytes());assert len(plan['cases'])==156 and sum(c['timed'] for c in plan['cases'])==152
        log='\n'.join(f"{c['name']} {str(c['timed']).lower()} {100 if c['timed'] else 0} 7" for c in plan['cases'])
        rows=parser.bench_rows(log,plan);parser.verify_same_seed(rows,rows);other=deepcopy(rows)
        for c in plan['cases']:
            if c['timed'] and c['kernel']=='mul':other[c['name']]['best_ns']=50
        result=m.summarize(plan,rows,other);assert result['mul']['guarded_over_control']==0.5
        assert all(result[k]['guarded_over_control']==1 for k in ('add','sum','bmm'))
        checks.append({'seed':seed,'cases':156,'timed_cases':152,'synthetic_MUL_half_ratio':0.5,'whole_ratio':result['whole']['guarded_over_control'],'scope':'Synthetic rows; not measurement.'})
    receipt={'status':'PASS_AST_HASH_PREPARATION_AND_SYNTHETIC_ONLY','verified_at_utc':datetime.now(timezone.utc).isoformat(),
        'source_sha256':m.sha(source),'draft_sha256':m.sha(draft),'lean_draft_sha256':m.sha(HERE/'R19RuntimeCostMain.lean'),
        'alternate_configuration_preserves_original_prefix_bytes':True,'official_fixture_files_unchanged_during_prepare':True,
        'unsupported_target_flags_rejected':True,'checks':checks,'Lean_build':'NOT_RUN','actual_flags_link_and_extra_call_review':'NOT_RUN','CI':'NOT_DISPATCHED'}
    (HERE/'local-verification.json').write_bytes(m.encode(receipt));print(json.dumps(receipt))
if __name__=='__main__':main()
