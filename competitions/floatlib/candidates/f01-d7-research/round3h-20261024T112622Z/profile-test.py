"""Lightweight real-generated-C/interface tests; no Lean/compiler/benchmark run."""
from pathlib import Path
import ast,importlib.util,json,copy,time

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
spec=importlib.util.spec_from_file_location('r13_profile_test_module',HERE/'profile-current.py')
m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)


def main():
    started=time.monotonic()
    fixture=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40078982864/download-41e2f9ab2f8c4b5788113c46064a5099/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-d12-none-native-result/capture-cab82d15d6124b9dac0613fa3750affe/file-3-Submission.c'
    original=fixture.read_bytes();changed,coverage=m.instrument(original)
    assert m.sha(original)==m.file_sha(fixture)and original!=changed
    assert all(coverage['category_function_counts'][c]>0 for c in ('whole_bmm','whole_sum','amap','bpack','cross_prepare','compute','output','repair'))
    generated=m.functions(changed.decode())
    selected={r['symbol']:r for r in generated if m.category(r['symbol'])is not None}
    for row in coverage['instrumented_functions']:
        body=selected[row['symbol']]['body']
        assert body.count('pr13_begin(')==1 and body.count('pr13_end(')==row['return_sites']
        assert body.index('pr13_begin(')<body.index('_start:')
    lines=[f'FL13 cat={i} inclusive_ns=100 exclusive_ns=50 calls={4 if c=="whole_bmm"else 0}'for i,c in enumerate(m.CATEGORIES)]
    log='\n'.join(lines+['FL13_END depth=0'])
    stages=m.parse_stages(log)
    case={'name':'bmm:test:0','kernel':'bmm','timed':True,'batch':3}
    assert m.verify_case(case,{'checksum':17},{'checksum':17},stages)==4
    rejected=[]
    for label,action in (
        ('checksum mismatch',lambda:m.verify_case(case,{'checksum':17},{'checksum':18},stages)),
        ('missing stage',lambda:m.parse_stages('\n'.join(lines[:-1]+['FL13_END depth=0']))),
        ('unbalanced timer stack',lambda:m.parse_stages('\n'.join(lines+['FL13_END depth=1']))),
        ('wrong root calls',lambda:m.verify_case(case,{'checksum':17},{'checksum':17},{**stages,'whole_bmm':{**stages['whole_bmm'],'calls':3}})),
        ('exclusive over inclusive',lambda:m.parse_stages(log.replace('exclusive_ns=50','exclusive_ns=101',1)))):
        try:action()
        except RuntimeError:rejected.append(label)
        else:raise AssertionError('failed to reject '+label)
    # Current-source gates and no-score enforcement live in run(). Verify the
    # independently callable CLI still exposes only the four agreed inputs.
    tree=ast.parse((HERE/'profile-entry.py').read_text())
    assert 'profile.run' in (HERE/'profile-entry.py').read_text()
    assert all(name in (HERE/'profile-entry.py').read_text()for name in ('upstream','kernel','out','plan'))
    result={'state':'PASS','seconds':time.monotonic()-started,'fixture':fixture.relative_to(ROOT).as_posix(),
        'fixture_kernel':'42c; actual saved C format only, NOT exactDF runtime/performance evidence',
        'fixture_sha256':m.sha(original),'instrumented_sha256':m.sha(changed),'coverage':coverage,
        'rejected':rejected,'linux_Lean_clang_gate':'NOT_RUN','exactDF_diagnostic_runtime':'NOT_RUN'}
    result['source_sha256']={n:m.file_sha(HERE/n)for n in ('profile-current.py','profile-entry.py','profile-test.py')}
    (HERE/'profile-local-tests.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({k:result[k]for k in ('state','seconds','fixture_sha256','rejected','linux_Lean_clang_gate')},indent=2))


if __name__=='__main__':main()
