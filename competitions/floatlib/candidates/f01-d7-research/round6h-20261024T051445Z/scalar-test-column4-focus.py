"""SYNTHETIC selector coverage only; no actual Narrow4 nm/machine evidence."""
from pathlib import Path
import importlib.util,json,tempfile,time

HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('r12_column4_capture',HERE/'capture-mainfull.py')
m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)


def main():
    legacy=m.load_legacy()
    core='lp_competition_Fin_foldl_loop___at___00Submission_Narrow4_core_spec__'
    core_names=[core+'0',core+'1',core+'2',core+'2___lam__0']
    hot=['lp_competition_Submission_Packed4Index_loop___redArg','lp_competition_Submission_Packed4Index_loop']
    pack=['lp_competition_Submission_Packed4_packB___redArg___lam__0','lp_competition_Submission_Packed4_packB___lam__1',
          'lp_competition___private_Init_Data_Array_Basic_0__Array_ofFnMUnsafe_go___at___00Submission_Packed4_packB_spec__0___redArg']
    control='lp_competition_Submission_Packed10Index_loop___redArg'
    helpers=['lp_competition_Submission_Narrow4_core___redArg','lp_competition_Submission_Narrow4_output___lam__0',
             'lp_competition_Submission_Packed4Index_runDot','lp_competition_Submission_Packed4Index_within']
    bad=[core+'0___boxed',core+'0_extra',core+'2___lam__0___boxed',core.replace('Narrow4_core','Narrow4_coreExtra')+'0',
         hot[0]+'___boxed','lp_competition_Submission_Packed4Index_looping',pack[0]+'___boxed',
         pack[2].replace('Array_ofFnMUnsafe_go','NotArray_ofFnMUnsafe_go'),'lp_competition_Submission_Packed4_packBExtra___lam__0',
         control+'___boxed']
    assert all(m.column4_symbol_info(n)is not None for n in core_names+hot+pack+[control]+helpers)
    assert all(m.column4_symbol_info(n)is None for n in bad)
    results=[]
    with tempfile.TemporaryDirectory(prefix='scalar-column4-test-',dir=HERE) as temporary:
        folder=Path(temporary);obj=folder/'synthetic-object';obj.write_bytes(b'fake object, not ELF')
        c=b'LEAN_EXPORT uint32_t synthetic_placeholder(uint32_t a){return a;}\n';(folder/'Submission.c').write_bytes(c)
        files=[{'kind':'c','module':'Submission','artifact':'Submission.c'}]
        fixtures=[('owned_families',core_names+hot+pack+[control]+helpers+bad+
            ['lp_competition_Submission_add___lam__'+str(i)for i in range(35)]),
            ('control_slot_reservation',core_names+hot+pack+[control]+[
                'lp_competition_Submission_Packed4_packB___lam__'+str(i)for i in range(2,45)])]
        old_tool=legacy._bounded_tool
        try:
            for label,names in fixtures:
                def fake_tool(argv,artifact,seconds,limit):
                    raw=(''.join('00000000 00000020 T '+n+'\n'for n in names).encode()if argv[0]=='nm'else b'SYNTHETIC NO MACHINE CODE\n')
                    artifact.write_bytes(raw);return {'ok':True,'artifact':artifact.name,'sha256':legacy.sha(raw),'bytes':len(raw),'returncode':0}
                legacy._bounded_tool=fake_tool
                report=m._disassemble(legacy,[(obj,{'source':str(obj),'sha256':'synthetic','module':'Submission'})],folder,time.monotonic()+30,
                    {'snapshot':{'files':files},'assembly_focus_configuration':{'assembly_focus':'bmm','state':'CONFIGURED'}})
                selected=[x['symbol']for x in report['selection_order']]
                assert report['selected_symbols']==20 and report['state']=='PARTIAL'
                assert set(core_names+hot+[control])<=set(selected)
                assert any(name in selected for name in pack)
                assert not set(selected)&set(bad)
                assert report['same_object_comparison_reserved']['object_index']==0
                results.append({'test':label,'pass':True,'evidence':'SYNTHETIC_NOT_MACHINE_OR_EMISSION_EVIDENCE',
                    'selected':selected,'control_slot':selected.index(control)+1})
        finally:legacy._bounded_tool=old_tool
    print(json.dumps({'state':'PASS','tests':results,'actual_Narrow4_C_nm':'NOT_YET_OBSERVED',
        'actual_Lean_ELF_gate':'NOT_RUN','candidate_assets_basis':'Owned source families only; actual015 C/nm must verify emitted names.'},indent=2))


if __name__=='__main__':main()
