"""Owned C-entry cost diagnostic; never scored or passed as a submission gate.

Input/generated code remains ephemeral. Only hashes, command arguments and
derived counters leave the runner. This intentionally instrumented binary is
separate from both untouched binaries used by the official paired experiment.
"""
from pathlib import Path
import hashlib, json, re, shlex, time

KERNELS={'YaV':'linear','Ybb2':'rmsnorm','MYbc':'layernorm'}

def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def trace(path):
    data=json.loads(path.read_bytes())
    assert data.get('synthetic') is False
    logs=[x['message'][3:] for x in data.get('log',[]) if x.get('message','').startswith('.> ')]
    assert len(logs)==1
    return shlex.split(logs[0])

def instrument(raw):
    text=raw.decode('utf-8');changes=[];wrappers=[];prototypes=[]
    pattern=re.compile(r'(?m)^(?P<header>LEAN_EXPORT[^\n;{}]*\b(?P<symbol>(?:l_|lp_competition_)Submission_(?P<name>YaV|Ybb2|MYbc))\((?P<args>[^\n;{}]*)\))\s*\{')
    matches=list(pattern.finditer(text))
    assert len(matches)==3,{m['name'] for m in matches}
    for index,m in enumerate(matches):
        header,symbol=m['header'],m['symbol']
        assert 'lean_object*' in header or 'lean_object *' in header or 'lean_obj_res' in header
        arguments=[]
        for parameter in m['args'].split(','):
            found=re.search(r'([A-Za-z_]\w*)\s*$',parameter.strip());assert found
            arguments.append(found[1])
        impl=symbol+'_r27_profile_impl'
        changes.append((m.start('header'),m.end('header'),header.replace(symbol,impl,1)))
        prototypes.append(header+';')
        wrappers.append(header+' {\n'
            +' int depth=r27_depth++; if(depth>=64) abort(); r27_children[depth]=0;\n'
            +' uint64_t start=r27_now();\n'
            +' lean_object *result='+impl+'('+','.join(arguments)+');\n'
            +' uint64_t elapsed=r27_now()-start; --r27_depth;\n'
            +f' ++r27_calls[{index}]; r27_inclusive[{index}]+=elapsed; r27_exclusive[{index}]+=elapsed-r27_children[depth];\n'
            +' if(depth) r27_children[depth-1]+=elapsed; return result;\n}\n')
    for start,end,replacement in reversed(changes):text=text[:start]+replacement+text[end:]
    names=[KERNELS[m['name']] for m in matches]
    prelude='''
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
static uint64_t r27_calls[4],r27_inclusive[4],r27_exclusive[4],r27_children[64];
static int r27_depth=0,r27_registered=0;
static void r27_dump(void) {
'''
    for i,name in enumerate(names):
        prelude+=f' fprintf(stderr,"R27_PROFILE {name} %llu %llu %llu\\n",(unsigned long long)r27_calls[{i}],(unsigned long long)r27_inclusive[{i}],(unsigned long long)r27_exclusive[{i}]);\n'
    prelude+='''}
static uint64_t r27_now(void) {
 if(!r27_registered) {atexit(r27_dump);r27_registered=1;}
 struct timespec t;clock_gettime(CLOCK_MONOTONIC,&t);
 return (uint64_t)t.tv_sec*1000000000ull+(uint64_t)t.tv_nsec;
}
'''
    marker='#include <lean/lean.h>'
    assert text.count(marker)==1
    text=text.replace(marker,marker+'\n'+prelude+'\n'+'\n'.join(prototypes)+'\n',1)
    return (text+'\n'+'\n'.join(wrappers)).encode(),names

def run_profile(g,bm,visible,config,control_binary,source_sha,out,global_end):
    out.mkdir(exist_ok=True)
    c=visible(g.BUILD/'ir/Submission.c');raw=c.read_bytes()
    patched,names=instrument(raw)
    source=g.LIB/'work/R27EntryProfile.c';source.write_bytes(patched)
    object_relative='.lake/build/ir/R27EntryProfile.c.o.export'
    binary_relative='.lake/build/bin/R27EntryProfile'
    compile_args=trace(visible(g.BUILD/'ir/Submission.c.o.export.trace'))
    changed=0
    for i,arg in enumerate(compile_args):
        if arg.endswith('/Submission.c'):
            compile_args[i]='work/R27EntryProfile.c';changed+=1
        elif i and compile_args[i-1]=='-o':compile_args[i]=object_relative
    assert changed==1
    commands=[]
    def own(args,label):
        cap=min(120,max(1,global_end-time.monotonic()-30));g._budget.reset(cap,deadline=time.monotonic()+cap)
        began=time.monotonic();code,text=g.own(args,cap,build='write')
        (out/(label+'.log')).write_text(text)
        commands.append({'label':label,'argv':args,'exit_code':code,'seconds':time.monotonic()-began})
        assert code==0,(label,text[-1000:])
    own(compile_args,'profile-compile')
    rsp=visible(g.BUILD/'bin/r27Native.rsp').read_text()
    assert rsp.count('.lake/build/ir/Submission.c.o.export')==1
    rsp=rsp.replace('.lake/build/ir/Submission.c.o.export',object_relative)
    rsp_path=g.LIB/'work/R27EntryProfile.rsp';rsp_path.write_text(rsp)
    link_args=trace(visible(g.BUILD/'bin/r27Native.trace'));changed=0
    for i,arg in enumerate(link_args):
        if arg.startswith('@') and arg.endswith('/r27Native.rsp'):
            link_args[i]='@work/R27EntryProfile.rsp';changed+=1
        elif i and link_args[i-1]=='-o':link_args[i]=binary_relative
    assert changed==1
    own(link_args,'profile-link')
    profiled=g.LIB/'work/r27-binaries/entry-profile';profiled.write_bytes(visible(g.BUILD/'bin/R27EntryProfile').read_bytes());profiled.chmod(0o755)
    cells=list(config.plan('normalized_mlp')['cells']);rows=[]
    import multiseed
    for cell in cells:
        request={'cells':[cell],'seed':27102977,'workloads':multiseed.workloads(27102977),'timing':{'run_seconds':60}}
        reps={f"{w['id']}|{cell}":32 for w in request['workloads']}
        baseline=bm.run_binary(control_binary,request,reps,1,'profile-control',bm.Deadline('profile-control',60))
        extra={'BENCH_CELLS':bm.lean_cell(cell),'BENCH_SEED':str(request['seed']),'BENCH_INNER':'1','LEAN_ABORT_ON_PANIC':'1',
               'BENCH_REPS':','.join(f"{k.split('|')[0]}|{bm.lean_cell(cell)}={v}" for k,v in reps.items()),
               'BENCH_WORKLOADS':','.join(f"{w['id']}:{w['seed']}:{w['profile']}" for w in request['workloads'])}
        command=[str(profiled)]
        if g._BENCH_CPU:command=['taskset','-c',g._BENCH_CPU,*command]
        code,output=g.run(command,60,env_extra=extra,memory_mb=g._BENCH_MEMORY_MB)
        (out/(cell.replace(':','_')+'.raw')).write_text(output)
        assert code==0
        metrics={};checks={}
        for line in output.splitlines():
            fields=line.split()
            if fields and fields[0]=='R27_PROFILE':
                assert len(fields)==5;metrics[fields[1]]={'calls':int(fields[2]),'inclusive_ns':int(fields[3]),'exclusive_ns':int(fields[4])}
            else:
                assert len(fields)==4 and fields[1]=='true'
                key=fields[0].split('|')[0]+'|'+cell;assert key in baseline
                assert int(fields[3])==baseline[key][1];checks[key]=True
        assert len(metrics)==3 and len(checks)==6
        total=sum(x['exclusive_ns'] for x in metrics.values())
        rows.append({'cell':cell,'instrumented_kernel_entry_times':metrics,'share_within_profiled_entries':{k:v['exclusive_ns']/total if total else None for k,v in metrics.items()},'checksum_pairs':len(checks)})
    report={'source_sha256':source_sha,'original_C_sha256':hashlib.sha256(raw).hexdigest(),'instrumented_C_sha256':hashlib.sha256(patched).hexdigest(),
            'control_binary_sha256':sha(control_binary),'profiled_binary_sha256':sha(profiled),'symbols':names,'commands':commands,'rows':rows,
            'scope':'INSTRUMENTED_COST_DISCRIMINATOR_ONLY_NOT_OFFICIAL_TIMING_OR_GATE',
            'boundary':'Pure kernel-entry wall time; nested profiled entries removed from exclusive sums. Output destruction outside these calls is excluded. Bench warmups may enter counters. One root, six cells, six workloads; no champion score or whole-model-share equality claim.',
            'publication':'Only derived counters/own transform and hashes; whole source/C stays ephemeral'}
    (out/'profile.json').write_text(json.dumps(report,indent=2)+'\n')
    return {'state':'COMPLETE_INSTRUMENTED_COST_DISCRIMINATOR','rows':len(rows),'checksum_pairs':sum(x['checksum_pairs'] for x in rows)}
