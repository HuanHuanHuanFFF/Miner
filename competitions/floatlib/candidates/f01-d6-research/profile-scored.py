"""Profile a throwaway statement object; retain per-call scored/raw separation."""
from pathlib import Path
import hashlib, json, re, shlex, statistics


def instrument(text):
    def body(symbol):
        p = re.compile(r'LEAN_EXPORT lean_object\* ' + re.escape(symbol) + r'\([^;{]*?\)\s*\{.*?\n}\n}', re.S)
        m = p.search(text)
        assert m, symbol
        return m

    core = body('lp_competition_Submission_RowStream_core')
    value = core.group()
    value, n = re.subn(r'(_start:\s*\{)', r'\1\nunsigned long long fl_start=fl_now(), fl_a=0, fl_b=0; fl_tile_ns=fl_output_ns=0; fl_row_calls=0;', value, count=1)
    assert n == 1
    lines = value.splitlines()
    for needle, mark in [('= lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(', 'fl_a'), ('= lp_competition_Submission_Packed10_packB(', 'fl_b')]:
        positions = [i for i, line in enumerate(lines) if needle in line]
        assert len(positions) == 1, needle
        lines.insert(positions[0]+1, mark+'=fl_now();')
    value = '\n'.join(lines)
    report = 'fl_calls++; printf("FL_CALL call=%llu total_ns=%llu nativeA_ns=%llu packB_ns=%llu tile_ns=%llu output_ns=%llu rows=%llu\\n",fl_calls,fl_now()-fl_start,fl_a-fl_start,fl_b-fl_a,fl_tile_ns,fl_output_ns,fl_row_calls);'
    value, n = re.subn(r'(return v_[^;]+;)', report+r'\n\1', value)
    assert n >= 1
    text = text[:core.start()]+value+text[core.end():]
    row_name = 'lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg'
    # Locate the actual row loop after replacing the outer core.
    p = re.compile(r'LEAN_EXPORT lean_object\* '+re.escape(row_name)+r'\([^;{]*?\)\s*\{.*?\n}\n}', re.S)
    m = p.search(text); assert m
    lines = m.group().splitlines()
    for needle, counter in [('= l_Array_ofFn___redArg(', 'fl_tile_ns'), ('= lp_competition_Submission_RowOutput_row___redArg(', 'fl_output_ns')]:
        positions = [i for i,line in enumerate(lines) if needle in line]
        assert len(positions)==1, (needle, positions)
        i=positions[0]
        lines.insert(i, '{ unsigned long long fl_local_t=fl_now();')
        lines.insert(i+2, counter+' += fl_now()-fl_local_t; }')
    # The output allocation result is declared at the enclosing scope.
    value='\n'.join(lines).replace('v_rowTiles_', 'v_rowTiles_')
    value, n = re.subn(r'(fl_output_ns \+= fl_now\(\)-fl_local_t; })', r'\1 fl_row_calls++;', value)
    assert n==1
    text=text[:m.start()]+value+text[m.end():]
    prelude='''
struct timespec;
struct fl_timespec { long sec; long nsec; };
extern int clock_gettime(int, struct timespec *);
extern int printf(const char *, ...);
static unsigned long long fl_calls, fl_tile_ns, fl_output_ns, fl_row_calls;
static unsigned long long fl_now(void) { struct fl_timespec t; clock_gettime(1,(struct timespec *)&t); return (unsigned long long)t.sec*1000000000ULL+(unsigned long long)t.nsec; }
'''
    return prelude+text


def run(g, kernel, out):
    upper=g.LAYER/'upper'; traces=[]
    for p in upper.rglob('*.trace'):
        try:
            for row in json.loads(p.read_bytes()).get('log',[]):
                if row.get('message','').startswith('.> '):traces.append(row['message'][3:])
        except (ValueError,OSError):pass
    (out/'profile-build-commands.json').write_text(json.dumps(traces,indent=2)+'\n')
    compile_cmd=next(s for s in traces if 'clang -c ' in s and '/Submission.c ' in s)
    link_cmd=next(s for s in traces if ' -o ' in s and '/bin/benchFull ' in s and ' -c ' not in s)
    cpath=next(upper.rglob('Submission.c')); original=cpath.read_bytes(); changed=instrument(original.decode()).encode()
    (out/'profile-instrumented.c').write_bytes(changed)
    plan={'diagnostic_only':True,'seed':702,'pairs':g._PAIRS,'inner':3,'expected_calls_per_process':13,'kernel_sha256':hashlib.sha256(kernel.read_bytes()).hexdigest(),'original_c_sha256':hashlib.sha256(original).hexdigest(),'instrumented_c_sha256':hashlib.sha256(changed).hexdigest(),'scope':'Only diagnostic statement object instrumented. Calls 1/5/9 are scored-class checksum passes; calls 2-4/6-8/10-12 are scored timed passes; call13 is untimed raw. No official score or acceptance claim.'}
    (out/'profile-plan.json').write_text(json.dumps(plan,indent=2)+'\n')
    def command(argv,name,build,cap=40):
        memory=g._BUILD_MEMORY_MB if build=='write' else g._BENCH_MEMORY_MB
        code,log=g.run(argv,cap,build=build,env_extra={'BENCH_SEED':'702','BENCH_PAIRS':str(g._PAIRS),'BENCH_INNER':'3','LEAN_ABORT_ON_PANIC':'1'},memory_mb=memory)
        (out/name).write_text(log)
        assert code==0,(name,code,log[-1200:])
        return log
    bench=str(g.BUILD/'bin/benchFull'); control=command([bench],'profile-control.log','read')
    cpath.write_bytes(changed)
    command(shlex.split(compile_cmd),'profile-compile.log','write',60)
    command(shlex.split(link_cmd),'profile-link.log','write',60)
    def checksums(s):
        return {p[0]:p[3] for line in s.splitlines() if len(p:=line.split())==4 and p[1] in ('true','false')}
    measurements=[]
    for process in range(3):
        log=command([bench],f'profile-instrumented-{process}.log','read')
        assert checksums(log)==checksums(control) and len(checksums(control))>=4
        rows=[]
        for match in re.finditer(r'FL_CALL call=(\d+) total_ns=(\d+) nativeA_ns=(\d+) packB_ns=(\d+) tile_ns=(\d+) output_ns=(\d+) rows=(\d+)',log):
            row=dict(zip(['call','total_ns','nativeA_ns','packB_ns','tile_ns','output_ns','rows'],map(int,match.groups())))
            i=row['call']; row['class']=['dense','relu','wide','raw'][(i-1)//4];row['timed']=i not in (1,5,9,13)
            assert row['rows']==100 and all(row[k]>0 for k in ['total_ns','nativeA_ns','packB_ns','tile_ns','output_ns'])
            row['residual_ns']=row['total_ns']-sum(row[k] for k in ['nativeA_ns','packB_ns','tile_ns','output_ns'])
            assert row['residual_ns']>=0
            rows.append(row)
        assert [r['call'] for r in rows]==list(range(1,14))
        measurements.append({'process':process,'calls':rows})
    scored=[r for p in measurements for r in p['calls'] if r['timed']]
    shares={k:statistics.median(r[k]/r['total_ns'] for r in scored) for k in ['nativeA_ns','packB_ns','tile_ns','output_ns','residual_ns']}
    (out/'profile-result.json').write_text(json.dumps({**plan,'checksum_matches_control':True,'measurements':measurements,'scored_call_median_stage_share':shares},indent=2)+'\n')
