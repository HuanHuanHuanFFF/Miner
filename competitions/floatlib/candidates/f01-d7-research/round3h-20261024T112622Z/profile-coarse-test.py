"""Actual DF C structure and coarse boundary tests, no Linux execution."""
from pathlib import Path
import ast,collections,hashlib,importlib.util,json,re,time
HERE=Path(__file__).resolve().parent
def module(name,file):
    s=importlib.util.spec_from_file_location(name,HERE/file);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
m=module('r13_coarse','profile-coarse-current.py')
i=module('r13_coarse_source','profile-coarse-inspect.py')


def run():
    started=time.monotonic();raw=i.CPATH.read_bytes();text=raw.decode();changed,coverage=m.instrument(raw)
    rows=m.functions(text);byname={r['symbol']:r for r in rows}
    selected={r['symbol']for r in coverage['instrumented_functions']}
    assert len(selected)==10 and all(n==1 for n in coverage['category_function_counts'].values())
    assert coverage['skipped']==[]
    assert m.PREFIX=='profile-r13-coarse-'and len(m.CATEGORIES)==10 and m.MAX_SECONDS==300
    assert 'pr13_calls[10]'in m.PRELUDE and 'c<10;'in m.PRELUDE and 'FC13 cat='in m.PRELUDE
    assert all('___lam__'not in n and '___boxed'not in n and 'Fin_foldl'not in n and '_finish'not in n and '_emit'not in n for n in selected)
    graph={}
    for name in sorted(selected):
        incoming=[]
        for r in rows:
            body=m.mask_c(r['body']);body=body[body.index('{')+1:]
            if re.search(r'\b'+re.escape(name)+r'\b',body):
                count=len(re.findall(r'\b'+re.escape(name)+r'\s*\(',body))
                incoming.append({'caller':r['symbol'],'direct_call_sites':count,
                    'address_taken':len(re.findall(r'\b'+re.escape(name)+r'\b',body))>count})
        assert not any(r['address_taken']for r in incoming),'outer boundary is an indirect callback'
        assert not any('___lam__'in r['caller']or 'Fin_foldl' in r['caller']for r in incoming),'outer boundary called by output/packet producer'
        graph[name]={'incoming':incoming,'body_sha256':hashlib.sha256(byname[name]['body'].encode()).hexdigest()}
    for r in m.functions(changed.decode()):
        if r['symbol']in selected:
            assert r['body'].index('pr13_begin')<r['body'].index('_start:')
            assert r['body'].count('pr13_end(')==len(re.findall(r'\breturn\b',m.mask_c(r['body'])))
    base={c:{'inclusive_ns':0,'exclusive_ns':0,'calls':0}for c in m.CATEGORIES}
    base['whole_bmm']={'inclusive_ns':1000,'exclusive_ns':600,'calls':4}
    base['rowstream_scope']={'inclusive_ns':400,'exclusive_ns':400,'calls':4}
    case={'name':'bmm:synthetic:0','kernel':'bmm','timed':True,'batch':1}
    control={'checksum':123};row={'checksum':123}
    assert m.verify_case(case,control,row,base)==4
    log='\n'.join(f"FC13 cat={j} inclusive_ns={base[c]['inclusive_ns']} exclusive_ns={base[c]['exclusive_ns']} calls={base[c]['calls']}"for j,c in enumerate(m.CATEGORIES))+'\nFC13_END depth=0\n'
    assert m.parse_stages(log)==base
    rejected=[]
    def bad(name,fn):
        try:fn()
        except RuntimeError:rejected.append(name)
        else:raise AssertionError(name+' accepted')
    bad('per-output/packet probe count',lambda:m.verify_case(case,control,row,{**base,'rowstream_scope':{**base['rowstream_scope'],'calls':5}}))
    bad('checksum mismatch',lambda:m.verify_case(case,control,{'checksum':124},base))
    bad('root coverage mismatch',lambda:m.verify_case(case,control,row,{**base,'whole_bmm':{**base['whole_bmm'],'calls':3}}))
    bad('missing coarse stage',lambda:m.parse_stages(log.replace('FC13 cat=9 inclusive_ns=0 exclusive_ns=0 calls=0\n','')))
    bad('unbalanced stack',lambda:m.parse_stages(log.replace('depth=0','depth=1')))
    bad('exact boundary missing',lambda:m.instrument(raw.replace(b'lp_competition_Submission_Packed10_packB(',b'lp_competition_Submission_Packed10_packB_renamed(')))
    tree=ast.parse((HERE/'profile-coarse-entry.py').read_text(encoding='utf-8'))
    assert 'profile-coarse-current.py'in (HERE/'profile-coarse-entry.py').read_text(encoding='utf-8')
    assert {n.value for n in ast.walk(tree)if isinstance(n,ast.Constant)and isinstance(n.value,str)}>=set(['upstream','kernel','out','plan'])
    result={'state':'PASS','exit_code':0,'elapsed_seconds':time.monotonic()-started,
        'actual_source_c':str(i.CPATH),'actual_source_c_sha256':hashlib.sha256(raw).hexdigest(),
        'source_identity':'Original uninstrumented DF C from diagnostic40092014611; structure evidence, not new Linux performance.',
        'coverage':coverage,'actual_outer_callgraph':graph,'rejected':rejected,
        'source_sha256':{n:hashlib.sha256((HERE/n).read_bytes()).hexdigest()for n in ['profile-coarse-current.py','profile-coarse-entry.py','profile-coarse-test.py','profile-coarse-build.py']},
        'original_frozen_unchanged':{n:hashlib.sha256((HERE/n).read_bytes()).hexdigest()for n in ['profile-current.py','profile-entry.py','profile-analyze.py']},
        'runtime_boundary':'Every nonroot category must have <=whole_bmm calls; sum has roots only. Missing/unexecuted boundaries remain UNKNOWN.',
        'exactDF_Linux_coarse_execution':'NOT_RUN'}
    (HERE/'profile-coarse-tests.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps(result))


if __name__=='__main__':run()
