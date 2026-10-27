"""Derive only temporary-fixture plumbing checks from the executed MUL harness."""
from pathlib import Path
H=Path(__file__).resolve().parent
text=(H.parent/'development-runtime-cost/verify-local.py').read_text()
for a,b in(('R19RuntimeCost','R19AddCost'),('r19RuntimeCost','r19AddCost'),
            ('development-runtime-cost','development-add-cost'),('f01-r19-dev-runtime-cost1','f01-r19-dev-add-cost1'),
            ('R19DirectBias_diagnosticEntry','R19GRS32Add_diagnosticEntry'),('HISTORICAL40420540388_BOUND_NOT_RERUN','PARENT77377_HISTORICAL40430974047_NOT_CURRENT_CARRIER_REPLAY'),
            ('runtime-cost-diagnostic','add-cost-diagnostic'),('runtime-cost/','add-cost/'),("'runtime-cost'","'add-cost'")):text=text.replace(a,b)
text=text.replace("self.HERE=HERE/'synthetic-fixtures'/name","self.HERE=FIXTURE_ROOT/name")
text=text.replace("ns=(100+i)*(2 if env['BENCH_VARIANT']=='control' else 1) if c['timed'] else 0",
 "ns=(100+i)*(1 if env['BENCH_VARIANT']=='guarded' and c['kernel']=='add' else 2) if c['timed'] else 0")
text=text.replace("assert all(x['guarded_over_control']==0.5 for x in seed[block].values())",
 "assert seed[block]['add']['guarded_over_control']==0.5\n                    assert all(seed[block][op]['guarded_over_control']==1 for op in ('mul','sum','bmm'))\n                    assert 0.5 < seed[block]['whole']['guarded_over_control'] < 1")
text=text.replace("('ok','buildfail','flags','drift','checksum','rows','foreign','dependency','noinline')",
 "('ok','buildfail','flags','drift','checksum','rows','foreign','dependency','noinline','trace_schema','arity3')")
text=text.replace("if mode in ('buildfail','flags','drift','foreign','dependency','noinline'):",
 "if mode in ('buildfail','flags','drift','foreign','dependency','noinline','trace_schema','arity3'):")
begin=text.index("            write(self.LAYER/'upper/ir/R19AddCostMain.c',")
end=text.index('\n',begin)
text=text[:begin]+'''            fake_c=b'/*SYNTHETIC BENCH_VARIANT; no actual code generated*/\\n'
            for symbol in ('r19CostControlAdd','r19CostGuardedAdd'):
                arity=3 if self.mode=='arity3' else 2
                fixed=1 if self.mode=='arity3' else 0
                fake_c+=f'static const lean_closure_object {symbol}_value = {{.m_fun = (void*){symbol}___boxed, .m_arity = {arity}, .m_num_fixed = {fixed}, .m_objs = {{}}}};\\n'.encode()
            if self.mode=='noinline':fake_c+=b'R19GRS32Add_diagnosticEntry\\n'
            write(self.LAYER/'upper/ir/R19AddCostMain.c',fake_c)'''+text[end:]
text=text.replace("        args=[obj,", "        if self.mode=='trace_schema' and upper:\n            write(base/'ir'/(root+'.c.o.export.trace'),d.encode({'synthetic':True,'log':[]}))\n        args=[obj,")
point="    parser=real_load(d.R13,'reused_parser_local');plan="
assert point in text
extra='''    for mode in ('traceFlags','function_alias','owned_name_collision'):
        g=Runner(tag+'-reject-'+mode);old_here=d.HERE
        try:
            if mode=='traceFlags':
                write(g.LIB/'lakefile.lean',(g.LIB/'lakefile.lean').read_bytes()+b'  traceFlags := true\\n')
            elif mode=='owned_name_collision':
                write(g.LIB/'lakefile.lean',(g.LIB/'lakefile.lean').read_bytes()+b'-- r19AddCost existing alias\\n')
            else:
                d.HERE=g.HERE/'package'
                wrong=(HERE/'R19AddCostMain.lean').read_bytes().replace(b'guardedAdd Submission.add',b'guardedAdd Submission.mul')
                write(d.HERE/'R19AddCostMain.lean',wrong)
            try:d.prepare(g,g.WORK,g.HERE/'rejected');raise AssertionError('Bad ADD preparation accepted')
            except RuntimeError:pass
            assert not g.calls and not (g.WORK.parent/'R19AddCostMain.lean').exists()
            results.append({'check':'ADD preparation rejects '+mode,'pass':True})
        finally:d.HERE=old_here
    assert d.normalize(['/x/MainFull.c','/x/benchFull.rsp'])==d.normalize(['/x/R19AddCostMain.c','/x/r19AddCost.rsp'])
    assert d.normalize(['/x/MainFull.c'])!=d.normalize(['/x/R19RuntimeCostMain.c'])
    results.append({'check':'flags normalize exactly ADD root/target, not old MUL root','pass':True})
'''
text=text.replace(point,extra+point)
text=text.replace("if __name__=='__main__':main()",'''if __name__=='__main__':
    import tempfile,shutil
    FIXTURE_ROOT=Path(tempfile.mkdtemp(prefix='.local-fixtures-',dir=HERE)).resolve()
    assert FIXTURE_ROOT.is_relative_to(HERE.resolve())
    try:main()
    finally:
        assert FIXTURE_ROOT.is_relative_to(HERE.resolve()) and FIXTURE_ROOT.name.startswith('.local-fixtures-')
        shutil.rmtree(FIXTURE_ROOT)
''')
(H/'verify-local.py').write_bytes(text.encode())
print('ADD verifier derived; fixtures temporary and removed')
