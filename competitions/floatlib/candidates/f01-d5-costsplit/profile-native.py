"""Partition one unchanged-source diagnostic build, never the official gate.

Runs inside the existing statement replay after its successful build. Only the
throwaway candidate layer is instrumented; the official repository stays clean.
"""
from pathlib import Path
import hashlib, json, re, shlex


def run(g, kernel, out):
    upper = g.LAYER / 'upper'
    traces = []
    for p in upper.rglob('*.trace'):
        try:
            d = json.loads(p.read_bytes())
            for row in d.get('log', []):
                msg = row.get('message', '')
                if msg.startswith('.> '):
                    traces.append(msg[3:])
        except (ValueError, OSError):
            pass
    (out/'profile-build-commands.json').write_text(json.dumps(traces, indent=2)+'\n')
    compile_cmd = next(s for s in traces if 'clang -c ' in s and '/Submission.c ' in s)
    link_cmd = next(s for s in traces if ' -o ' in s and '/bin/benchFull ' in s and ' -c ' not in s)
    cpath = next(p for p in upper.rglob('Submission.c'))
    original = cpath.read_bytes()
    text = original.decode()
    pattern = r'LEAN_EXPORT lean_object\* lp_competition_Submission_Packed10_core\([^;{]*?\)\s*\{.*?\n}\n}'
    match = re.search(pattern, text, re.S)
    assert match
    body = match.group()
    body, n = re.subn(r'(_start:\s*\{)', r'\1\nunsigned long long fl_t0 = fl_now(), fl_t1, fl_t2, fl_t3, fl_t4;', body, count=1)
    assert n == 1
    for needle, mark in [('= lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(', 'fl_t1'), ('= lp_competition_Submission_Packed10_packB(', 'fl_t2'), ('= lp_competition_Submission_Packed10_tileResults(', 'fl_t3')]:
        lines = body.splitlines()
        positions = [i for i, line in enumerate(lines) if needle in line]
        assert len(positions) == 1, needle
        lines.insert(positions[0]+1, mark+' = fl_now();')
        body = '\n'.join(lines)
    body, n = re.subn(r'(return v_[^;]+;)', r'fl_t4 = fl_now(); fl_calls++; fl_ns[0] += fl_t1-fl_t0; fl_ns[1] += fl_t2-fl_t1; fl_ns[2] += fl_t3-fl_t2; fl_ns[3] += fl_t4-fl_t3;\n\1', body)
    assert n == 1
    prelude = '''
/* Linux x86_64 POSIX ABI: the pinned compiler sysroot omits time.h. */
struct timespec;
struct fl_timespec { long sec; long nsec; };
extern int clock_gettime(int, struct timespec *);
extern int printf(const char *, ...);
static unsigned long long fl_ns[4], fl_calls;
static unsigned long long fl_now(void) { struct fl_timespec t; clock_gettime(1, (struct timespec *)&t); return (unsigned long long)t.sec*1000000000ULL+(unsigned long long)t.nsec; }
__attribute__((destructor)) static void fl_report(void) { printf("FL_PROFILE calls=%llu nativeA_ns=%llu packB_ns=%llu tiles_ns=%llu output_ns=%llu\\n",fl_calls,fl_ns[0],fl_ns[1],fl_ns[2],fl_ns[3]); }
'''
    changed = (prelude+text[:match.start()]+body+text[match.end():]).encode()
    plan = {'diagnostic_only': True, 'kernel_sha256':hashlib.sha256(kernel.read_bytes()).hexdigest(), 'original_c_sha256':hashlib.sha256(original).hexdigest(), 'instrumented_c_sha256':hashlib.sha256(changed).hexdigest(), 'scope':'Four monotonic clock boundaries around nativeA conversion, B packing, tile computation and output assembly. Includes allocation/refcount cost within boundaries. Instrumented copy of diagnostic statement object; not timed official gate object. No ranking claim.'}
    (out/'profile-plan.json').write_text(json.dumps(plan, indent=2)+'\n')
    (out/'profile-instrumented.c').write_bytes(changed)
    def command(argv, name, build, cap=40):
        code, log = g.run(argv, cap, build=build, env_extra={'BENCH_SEED':'601','BENCH_PAIRS':'4','LEAN_ABORT_ON_PANIC':'1'}, memory_mb=g._BENCH_MEMORY_MB)
        (out/name).write_text(log)
        assert code == 0, (name, code, log[-1000:])
        return log
    bench = str(g.BUILD/'bin/benchFull')
    control = command([bench], 'profile-control.log', 'read')
    cpath.write_bytes(changed)
    command(shlex.split(compile_cmd), 'profile-compile.log', 'write', 60)
    command(shlex.split(link_cmd), 'profile-link.log', 'write', 60)
    rows = []
    def checksums(s):
        return {p[0]:p[3] for line in s.splitlines() if len(p:=line.split())==4 and p[1] in ('true','false')}
    for i in range(3):
        log=command([bench], f'profile-instrumented-{i}.log', 'read')
        assert checksums(log) == checksums(control) and checksums(control)
        m=re.search(r'FL_PROFILE calls=(\d+) nativeA_ns=(\d+) packB_ns=(\d+) tiles_ns=(\d+) output_ns=(\d+)',log)
        assert m
        vals=list(map(int,m.groups()));rows.append(dict(zip(['calls','nativeA_ns','packB_ns','tiles_ns','output_ns'],vals)))
    (out/'profile-result.json').write_text(json.dumps({**plan,'checksum_matches_control':True,'measurements':rows},indent=2)+'\n')
