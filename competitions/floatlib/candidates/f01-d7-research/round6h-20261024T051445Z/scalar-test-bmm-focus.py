"""Assembly-focus tests: real saved C/nm names, fake tools/ELF processes only."""
from pathlib import Path
import importlib.util
import json
import os
import sys
import tempfile
import time

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
spec=importlib.util.spec_from_file_location('r12_focus_capture',HERE/'capture-mainfull.py')
m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
saved=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40067286343/download-5936990717ed4c0996f1c31b985d1aa3/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-d11-bmm-combined-classifier/capture-ad2a97ee7ace4c67983e4c060817926c'
panel_saved=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40042916169/download-ed8deed8e3b24ba9ad8148884350f78f/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-d11-panel4-codegen-probe/capture-2f02cef6044b48bfa9184fc265f5fe5d'


def main():
    results=[]
    legacy=m.load_legacy()
    with tempfile.TemporaryDirectory(prefix='scalar-bmm-focus-test-',dir=HERE) as temporary:
        base=Path(temporary).resolve()
        staged=[];files=[];nm_rows={}
        for index,(module,c_name) in enumerate((('MainFull','file-0-MainFull.c'),('Submission','file-3-Submission.c'),('BenchSuite','file-6-BenchSuite.c'))):
            private=base/f'fake-object-{index}'
            private.write_bytes(b'fake ELF is not inspected by tools')
            staged.append((private,{'source':str(private),'sha256':'fixture-'+str(index),'module':module}))
            c_source=panel_saved/'file-0-Submission.c' if module=='Submission' else saved/c_name
            (base/c_name).write_bytes(c_source.read_bytes())
            files.append({'kind':'c','module':module,'artifact':c_name})
            nm_source=panel_saved/'nm-0.txt' if module=='Submission' else saved/f'nm-{index}.txt'
            nm_rows[str(private)]=nm_source.read_bytes()
        original_tool=legacy._bounded_tool
        def fake_tool(argv,artifact,seconds,limit):
            raw=nm_rows[argv[-1]] if argv[0]=='nm' else b'fake post-gate text output\n'
            artifact.write_bytes(raw)
            return {'ok':True,'artifact':artifact.name,'sha256':legacy.sha(raw),'bytes':len(raw),'returncode':0}
        legacy._bounded_tool=fake_tool
        try:
            reports={}
            for focus in ('scalar','bmm'):
                report=m._disassemble(legacy,staged,base,time.monotonic()+30,
                    {'snapshot':{'files':files},'assembly_focus_configuration':{'state':'CONFIGURED','assembly_focus':focus}})
                reports[focus]=report
                assert report['selected_symbols']==20 and report['state']=='PARTIAL'
            scalar=reports['scalar']['selection_order']
            bmm=reports['bmm']['selection_order']
            assert scalar[0]['object_index']==0
            actual_names=[]
            for line in nm_rows[str(staged[1][0])].decode().splitlines():
                parts=line.split()
                if len(parts)==4 and parts[2] in 'TtWw' and legacy._symbol_info(parts[3]) is not None:
                    actual_names.append(parts[3])
            def priority(name):
                core=m.bmm_core_symbol_info(name)
                if core is not None:
                    return (-3,*core['sort_key'])
                panel=legacy._symbol_info(name)['stem'] in ('Panel4_wordLoop','Panel4_packA','Panel4_block','Panel4_runDot')
                return (-2 if panel else 0,*legacy._symbol_sort_key(name))
            expected=sorted(actual_names,key=priority)[:20]
            assert [s['symbol'] for s in bmm]==expected
            assert all(s['object_index']==1 for s in bmm)
            assert any('Panel4_wordLoop' in s['symbol'] for s in bmm)
            assert any(o['module']=='MainFull' and o['omitted_symbols'] for o in reports['bmm']['objects'])
            assert all('___boxed' not in name for name in expected)
            results.append({'test':'saved40067286343 Main/Bench plus actual927 Panel4 C/nm selector fixture, not a measured run','pass':True,
                            'scalar_first':scalar[0]['symbol'],'bmm_first':bmm[0]['symbol'],
                            'bmm_selected':20,'MainFull_assembly_omission_explicit':True})
        finally:
            legacy._bounded_tool=original_tool
        # Invalid focus still executes the unchanged child exactly once, drains
        # its original bytes, returns original exit7 and removes private ELF.
        workspace=base/'workspace';plan_path=workspace/'competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json'
        plan_path.parent.mkdir(parents=True)
        candidate=base/'fake-candidate';candidate.mkdir();kernel=candidate/'Kernel.lean';kernel.write_bytes(b'import ContractTensor\n')
        plan={'r12_mainfull_capture':{'candidates':[candidate.name],'assembly_focus':'illegal'}}
        plan_path.write_text(json.dumps(plan),encoding='utf-8',newline='\n')
        root=base/'official';upper=root/'.sandbox/layer/upper';(upper/'ir').mkdir(parents=True)
        (root/'lean/work').mkdir(parents=True);(root/'lean/work/Submission.lean').write_bytes(kernel.read_bytes())
        for module in ('MainFull','Submission'):
            (upper/f'ir/{module}.c').write_bytes(b'LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t a){return a;}\n')
            (upper/f'ir/{module}.c.o.export').write_bytes(b'\x7fELF fake object')
            (upper/f'ir/{module}.c.o.export.trace').write_bytes(b'{"log":[]}\n')
        temp_root=base/'runner-temp';temp_root.mkdir();output=base/'output';log=base/'gate.log'
        env=os.environ.copy();env.update(GITHUB_WORKSPACE=str(workspace),RUNNER_TEMP=str(temp_root))
        original_env=env.copy()
        program=r'''
from pathlib import Path
import os,sys,time
root,out=map(Path,sys.argv[1:])
counter=root/'once';counter.write_bytes(counter.read_bytes()+b'x' if counter.exists() else b'x')
os.write(1,b'original\xff\n[statement] ok\n')
deadline=time.monotonic()+5
while not list(out.glob('capture-*/snapshot.json')) and time.monotonic()<deadline:time.sleep(.01)
os.write(1,b'[score] original\x00\n')
sys.exit(7)
'''
        argv=[sys.executable,'-c',program,str(root),str(output)]
        completed,record=m.run_gate(argv,root,env,log,8,output,kernel)
        assert completed.returncode==7 and (root/'once').read_bytes()==b'x'
        assert log.read_bytes()==b'original\xff\n[statement] ok\n[score] original\x00\n'
        assert record['state']=='UNKNOWN' and record['assembly_focus_configuration']['state']=='UNKNOWN'
        assert record['private_objects_removed'] and record['private_directory_removed'] and not list(temp_root.iterdir())
        assert env==original_env
        assert all(not p.read_bytes().startswith(b'\x7fELF') for p in output.rglob('*') if p.is_file())
        results.append({'test':'invalid focus isolated; original once-only exit/log/cleanup preserved','pass':True})
        for requested in ({}, {'assembly_focus':'scalar'}, {'assembly_focus':'bmm'}):
            plan={'r12_mainfull_capture':{'candidates':[candidate.name],**requested}}
            plan_path.write_text(json.dumps(plan),encoding='utf-8',newline='\n')
            config=m.assembly_focus_config(legacy,env,kernel)
            assert config['assembly_focus']==requested.get('assembly_focus','scalar')
            assert config['state']!='UNKNOWN'
        results.append({'test':'missing focus defaults scalar; only explicit scalar/bmm accepted','pass':True})
    print(json.dumps({'state':'PASS','tests':results,'actual_Lean_ELF_gate':'NOT_RUN'},indent=2))


if __name__=='__main__':
    main()
