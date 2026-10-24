"""Actual1224003 Fin.foldl core/producer selection regression; fake tools only."""
from pathlib import Path
import importlib.util
import json
import tempfile
import time

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
spec=importlib.util.spec_from_file_location('r12_core_focus',HERE/'capture-mainfull.py')
m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
ACTUAL=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40068680108/download-8d09684e40074ed9b1e2f95af49834e7/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-r12-wide4-typed-within/capture-47397dce6ad348688ea371931e184fa3'
MAIN=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40067286343/download-5936990717ed4c0996f1c31b985d1aa3/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-d11-bmm-combined-classifier/capture-ad2a97ee7ace4c67983e4c060817926c'


def main():
    legacy=m.load_legacy()
    review=json.loads((HERE/'astra-mainfull-bmm-capture-review.json').read_bytes())
    known=[row['symbol'] for row in review['known_actual_symbols']]
    c=(ACTUAL/'file-0-Submission.c').read_bytes();nm=(ACTUAL/'nm-0.txt').read_bytes()
    assert legacy.sha(c)==review['evidence_C_sha256']
    actual_names=[p[3] for line in nm.decode().splitlines() if len(p:=line.split())==4 and p[2] in 'TtWw']
    assert all(name in actual_names and name.encode() in c for name in known)
    assert all(legacy._symbol_info(name) is None and m.bmm_core_symbol_info(name) is not None for name in known)
    invalid=[known[0]+'___boxed',known[0]+'_extra',known[1]+'___redArgument',known[1].replace('_core_spec','_coreExtra_spec'),
             known[1].replace('Fin_foldl_loop___at___00Submission','NotFin_foldl_loop___at___00Submission')]
    assert all(m.bmm_core_symbol_info(name) is None for name in invalid)
    with tempfile.TemporaryDirectory(prefix='scalar-bmm-core-test-',dir=HERE) as temporary:
        folder=Path(temporary);staged=[];files=[];symbols={}
        for index,(module,raw,nm_raw) in enumerate((('MainFull',(MAIN/'file-0-MainFull.c').read_bytes(),(MAIN/'nm-0.txt').read_bytes()),
            ('Submission',c,nm),('BenchSuite',(MAIN/'file-6-BenchSuite.c').read_bytes(),(MAIN/'nm-2.txt').read_bytes()))):
            obj=folder/f'fake-{index}';obj.write_bytes(b'not executable')
            artifact=f'{module}.c';(folder/artifact).write_bytes(raw)
            staged.append((obj,{'source':str(obj),'sha256':'fixture-'+str(index),'module':module}))
            files.append({'kind':'c','module':module,'artifact':artifact});symbols[str(obj)]=nm_raw
        old_tool=legacy._bounded_tool
        def fake_tool(argv,artifact,seconds,limit):
            raw=symbols[argv[-1]] if argv[0]=='nm' else b'fake selected-symbol text\n'
            artifact.write_bytes(raw)
            return {'ok':True,'artifact':artifact.name,'bytes':len(raw),'sha256':legacy.sha(raw),'returncode':0}
        legacy._bounded_tool=fake_tool
        try:
            report=m._disassemble(legacy,staged,folder,time.monotonic()+30,
                {'snapshot':{'files':files},'assembly_focus_configuration':{'assembly_focus':'bmm','state':'CONFIGURED'}})
        finally:
            legacy._bounded_tool=old_tool
        order=[row['symbol'] for row in report['selection_order']]
        assert report['selected_symbols']==20 and report['state']=='PARTIAL'
        assert set(known)<=set(order)
        assert set(order[:len(known)])==set(known)
        assert '___lam__0' in order[0]
        # The typed22ea object predates Panel4 wiring. Panel4 hot/packA coverage
        # is supplied by the separately retained actual927 focus fixture.
        assert any('R11WideRows4_wordLoop' in x for x in order)
        assert any('R11WideLayout_emitTail' in x for x in order)
        assert not set(invalid)&set(order)
        assert any(o['module']=='MainFull' and o['omitted_symbols'] for o in report['objects'])
        print(json.dumps({'state':'PASS','tests':[{'test':'actual1224003 core spec0..3 plus producer all first; actual normal wordLoop/tail within20; exact boundary exclusions','pass':True}],
            'helper_sha256':legacy.sha((HERE/'capture-mainfull.py').read_bytes()),'actual_C_sha256':legacy.sha(c),'actual_nm_sha256':legacy.sha(nm),
            'actual_core_symbols':known,'selected_order':order,'actual_Lean_ELF_gate':'NOT_RUN'},indent=2))


if __name__=='__main__':
    main()
