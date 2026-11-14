"""Observe immutable public references; no new competition implementation or score.

Runs the original exactDev profile CLI, whose timings INCLUDE output hashing and
touching. Never publishes the retired entry source, generated C, objects or binaries.
"""
from pathlib import Path
from urllib.request import Request, urlopen
from urllib.error import HTTPError
import datetime, hashlib, json, os, re, shutil, signal, subprocess, time

COMMIT = 'accb82b6e2adeda1b41a57a260d68fb3879c427e'
REPO = 'https://github.com/conjectures-io/conjectures-optimisation-float-kernels.git'
FORMER_SHA = 'cea4422fb6d3bd613b306127e7017331560875ddb840a7f2e174f6c03bdb480f'
TEMP = Path(os.environ['RUNNER_TEMP'])
OUT = TEMP / 'r24-reference-profile-reports'
LIVE = TEMP / 'r24-reference-profile-live-logs'
UP = TEMP / 'r24-readonly-upstream'
ROOT = Path(os.environ['GITHUB_WORKSPACE'])
START = time.monotonic()
ROUND_END = datetime.datetime(2026,10,29,3,38,56,tzinfo=datetime.timezone.utc)
ROUND_LEFT = (ROUND_END-datetime.datetime.now(datetime.timezone.utc)).total_seconds()
DEADLINE = START + min(2100, max(0, ROUND_LEFT))
OUT.mkdir(parents=True, exist_ok=True)
LIVE.mkdir(parents=True, exist_ok=True)
ENV = os.environ.copy()
ENV['PATH'] = str(Path.home()/'.elan/bin') + os.pathsep + ENV.get('PATH','')
summary = {'source_commit': os.environ['GITHUB_SHA'], 'run_id': os.environ['GITHUB_RUN_ID'],
           'scope': 'IMMUTABLE_PUBLIC_REFERENCE_OBSERVATION_ONLY_NOT_NEW_CANDIDATE_OR_SCORE',
           'upstream_commit': COMMIT, 'started_at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
           'model_profile': 'Original exactDev profile, batch1/normal, model seed42, input seed7, best5; includes hashArr/touch inside timing',
           'no_current_champion_source_or_score_inherited': True, 'references': [], 'complete': False}
sha = lambda b: hashlib.sha256(b).hexdigest()

class ObservationFailure(Exception):
    """A failed command ends the complete observer, including failed builds."""

class ObservationTimeout(ObservationFailure):
    """Stop the complete observation after any timeout; never start another load."""

def save():
    (OUT/'summary.json').write_text(json.dumps(summary, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')

def run(argv, label, cwd, cap, capped=False):
    left = int(DEADLINE-time.monotonic())
    if left < 15: raise TimeoutError('Read-only overall budget exhausted')
    command = list(map(str,argv))
    unit = 'r24-ref-'+os.environ['GITHUB_RUN_ID']+'-'+sha(label.encode())[:10]+'.scope'
    if capped:
        command = ['systemd-run','--user','--scope','--quiet','--unit',unit,'-p','MemoryMax=4096M','-p','MemorySwapMax=0',*command]
    began = time.monotonic(); live=LIVE/(label+'.log');path=OUT/(label+'.log')
    item={'label':label,'argv':command,'cwd':str(cwd),'timeout_seconds':min(cap,left-10),'memory_cap_mb':4096 if capped else None}
    with live.open('wb') as stream:
        p=subprocess.Popen(command,cwd=cwd,env=ENV,stdout=stream,stderr=subprocess.STDOUT,start_new_session=True)
        try:
            item['exit_code']=p.wait(timeout=item['timeout_seconds'])
        except subprocess.TimeoutExpired:
            item['exit_code']='TIMEOUT'
        if item['exit_code'] != 0:
            item['cleanup']=[]
            cgroup=None
            if capped:
                try:
                    probe=subprocess.run(['systemctl','--user','show','--property=ControlGroup','--value',unit],capture_output=True,timeout=3)
                    relative=probe.stdout.decode(errors='replace').strip()
                    if probe.returncode==0 and relative.startswith('/'):
                        candidate=(Path('/sys/fs/cgroup')/relative.lstrip('/')).resolve()
                        if candidate.is_relative_to(Path('/sys/fs/cgroup').resolve()): cgroup=candidate
                except (subprocess.TimeoutExpired,OSError) as error:
                    item['cleanup'].append({'cgroup_probe_error':str(error)})
            for sig in (signal.SIGTERM, signal.SIGKILL):
                if capped:
                    try:
                        cleanup=subprocess.run(['systemctl','--user','kill','--kill-whom=all','--signal',sig.name,unit],capture_output=True,timeout=10)
                        item['cleanup'].append({'signal':sig.name,'scope_kill_exit_code':cleanup.returncode,
                            'scope_kill_stderr':cleanup.stderr.decode(errors='replace')[:2000]})
                    except (subprocess.TimeoutExpired,OSError) as error:
                        item['cleanup'].append({'signal':sig.name,'scope_kill_error':str(error)})
                try:
                    os.killpg(p.pid,sig)
                    item['cleanup'].append({'signal':sig.name,'process_group_kill':'SENT'})
                except ProcessLookupError:
                    item['cleanup'].append({'signal':sig.name,'process_group_kill':'ALREADY_GONE'})
                except OSError as error:
                    item['cleanup'].append({'signal':sig.name,'process_group_kill_error':str(error)})
                try: p.wait(timeout=5)
                except subprocess.TimeoutExpired: continue
                if not capped: break
            item['owned_process_exit_code']=p.poll()
            try:
                os.killpg(p.pid,0);group_gone=False
            except ProcessLookupError: group_gone=True
            except OSError: group_gone=False
            scope_empty=not capped
            if capped and cgroup is not None:
                try:
                    events=dict(line.split() for line in (cgroup/'cgroup.events').read_text().splitlines())
                    scope_empty=events.get('populated')=='0'
                except FileNotFoundError: scope_empty=not cgroup.exists()
                except OSError: pass
            item['process_group_gone']=group_gone
            item['scope_empty_confirmed']=scope_empty
            item['cleanup_confirmed']=p.poll() is not None and group_gone and scope_empty
    # A failed launcher may leave a writer alive. Publish a stable byte snapshot,
    # never a file still used by that writer; preserve the uncertainty explicitly.
    snapshot=live.read_bytes();path.write_bytes(snapshot)
    item.update(seconds=time.monotonic()-began,log_sha256=sha(snapshot),log_bytes=len(snapshot),
        log_receipt='FROZEN_COMMAND_LOG' if item['exit_code']==0 or item.get('cleanup_confirmed') else 'FROZEN_PARTIAL_PREFIX_LIVE_TAIL_UNKNOWN')
    summary.setdefault('commands',[]).append(item);save()
    if item['exit_code']=='TIMEOUT':
        summary['abort_after_timeout']='No subsequent reference, build or profile is allowed'
        save()
        raise ObservationTimeout(label+' timed out; cleanup confirmed='+str(item['cleanup_confirmed']))
    if item['exit_code'] != 0:
        summary['abort_after_process_failure']='No subsequent reference, build or profile is allowed'
        save()
        raise ObservationFailure(label+' failed: '+str(item['exit_code']))
    return path

def protected():
    files=[UP/'lean/lakefile.lean',UP/'lean/lake-manifest.json',UP/'lean/lean-toolchain',UP/'setup.sh']
    files += list((UP/'lean/contract').rglob('*.lean')) + list((UP/'lean/bench').rglob('*.lean'))
    return {p.relative_to(UP).as_posix():sha(p.read_bytes()) for p in files if p.is_file()}

def parse_profile(path):
    rows=[]
    for line in path.read_text(errors='replace').splitlines():
        m=re.fullmatch(r'\|\s*(.*?)\s*\|\s*(\d+)\s*\|',line)
        if m: rows.append({'layer':m[1],'microseconds_integer_truncated':int(m[2])})
    total=next((x['microseconds_integer_truncated'] for x in rows if x['layer']=='total'),None)
    assert total is not None and len(rows)>1, 'Missing original profile rows'
    return {'rows':rows,'reported_total_microseconds':total,'scope':'Layer+hash/touch observer; not pure kernel time or official model score'}

def export_c_metadata(name):
    """Facts/hashes only; do not redistribute third-party generated code."""
    p=UP/'lean/.lake/build/ir/Submission.c'
    if not p.is_file(): return {'state':'UNKNOWN_NO_ORIGINAL_C_CAPTURE'}
    raw=p.read_bytes();text=raw.decode(errors='replace')
    masked=re.sub(r'/\*[\s\S]*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"',lambda m:' '*len(m[0]),text)
    records=[]
    pattern=r'(?m)^LEAN_EXPORT[^\n;]*\b(lp_competition_Submission_[A-Za-z0-9_]+)\([^;\n]*\)\s*\{'
    for m in re.finditer(pattern,masked):
        symbol=m[1]
        if name=='former2' and not re.search(r'_(Y6|Y7|Y8|Ya7|Ya8|YaD|YN|Ybb|Ybc)(?:___|$)',symbol):continue
        if name=='shipped' and not re.search(r'(dotLoop|finishFast|rmsnorm|layernorm|Acc_add)',symbol):continue
        end=m.end();depth=1
        while depth and end<len(masked):
            depth += (masked[end]=='{')-(masked[end]=='}');end+=1
        body=text[m.start():end];calls=re.findall(r'\b(lean_[A-Za-z0-9_]+)\s*\(',body)
        records.append({'symbol':symbol,'body_sha256':sha(body.encode()),'body_bytes':len(body.encode()),
                        'runtime_call_text_counts':{x:calls.count(x) for x in sorted(set(calls))},
                        'scope':'Static exported body, may be inlined; neither actual dynamic counts nor selected-caller proof'})
        if len(records)>=40:break
    result={'source_c_sha256':sha(raw),'source_c_bytes':len(raw),'records':records,
            'raw_code_publication':'Excluded; original public source hash and local intake retained separately'}
    (OUT/(name+'-c-metadata.json')).write_text(json.dumps(result,indent=2)+'\n')
    return {'file':name+'-c-metadata.json','sha256':sha((OUT/(name+'-c-metadata.json')).read_bytes()),'exported_bodies':len(records)}

save()
try:
    assert ROUND_LEFT >= 600, 'Too little remaining research window after queueing'
    assert not UP.exists()
    run(['git','clone','--filter=blob:none','--no-checkout','--no-tags',REPO,UP],'clone',ROOT,90)
    run(['git','fetch','--depth','1','origin',COMMIT],'fetch',UP,90)
    run(['git','checkout','--detach',COMMIT],'checkout',UP,45)
    actual=subprocess.check_output(['git','rev-parse','HEAD'],cwd=UP,text=True).strip();assert actual==COMMIT
    cached=TEMP/'floatlib-upstream/lean/.lake/packages'
    dest=UP/'lean/.lake/packages'
    if cached.is_dir():
        dest.parent.mkdir(parents=True,exist_ok=True)
        run(['cp','-al',cached,dest],'reuse-dependencies-only',ROOT,180)
        summary['cache_scope']='Only pinned dependency package tree; own project build not reused'
    before=protected();summary['protected_source_hashes_before']=before
    cpuinfo=Path('/proc/cpuinfo').read_bytes()
    summary['cpuinfo_sha256']=sha(cpuinfo)
    (OUT/'cpuinfo.raw').write_bytes(cpuinfo)
    available=sorted(os.sched_getaffinity(0));summary['available_cpus']=available;summary['profile_cpu']=available[0]
    run(['bash','./setup.sh','--benchmark-worker'],'setup-benchmark-worker',UP,960,True)
    run(['bash','./setup.sh','--check'],'setup-check',UP,90)
    source=UP/'lean/work/Submission.lean'
    shipped=(UP/'kernels/exact/incumbent/Kernel.lean').read_bytes()
    assert source.read_bytes()==shipped
    refs=[('shipped',shipped,{'origin':REPO,'upstream_commit':COMMIT,'input_sha256':sha(shipped)})]
    url='https://conjectures.io/v1/competitions/torchlean/submissions/2/source'
    try:
        with urlopen(Request(url,headers={'User-Agent':'FloatLib-development-readonly'}),timeout=30) as response:
            body=response.read(256001);code=response.status
            summary['former2_download']={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
                'url':url,'http_status':code,'bytes_read':len(body),'sha256':sha(body),
                'content_type':response.headers.get('Content-Type'),
                'raw_source_export':'EXCLUDED_REUSE_LICENSE_UNKNOWN'}
            save()
        assert code==200 and 0<len(body)<=256000 and sha(body)==FORMER_SHA
        assert body.decode('utf-8').splitlines()[0]=='import ContractExact'
        refs.append(('former2',body,{'url':url,'http_status':200,'input_sha256':sha(body),
                    'source_publication':'Not included in artifacts; primary public-source availability is not a reuse license'}))
    except HTTPError as error:
        denied=error.read();(OUT/'former2-download-error.raw').write_bytes(denied)
        summary['former2_access']={'status':'UNKNOWN_OR_UNAVAILABLE_NO_RETRY','error':str(error),'url':url,
                                  'http_status':error.code,'error_sha256':sha(denied),'error_bytes':len(denied)}
    except (OSError,AssertionError) as error:
        summary['former2_access']={'status':'UNKNOWN_OR_UNAVAILABLE_NO_RETRY','error':str(error),'url':url}
    refs.sort(key=lambda x: x[0]!='former2')
    for name,body,receipt in refs:
        if DEADLINE-time.monotonic()<300:
            summary['remaining_references']='NOT_RUN_BUDGET';break
        record={'name':name,'receipt':receipt,'input_bytes':len(body),'profiles':[],'typecheck':'NOT_RUN','complete':False}
        summary['references'].append(record);save();source.write_bytes(body)
        try:
            assert sha(source.read_bytes())==receipt['input_sha256']
            run([str(Path.home()/'.elan/bin/lake'),'build','VerifyExact','exactDev'],name+'-build-original-targets',UP/'lean',960,True)
            record['typecheck']='ORIGINAL_VERIFYEXACT_TARGET_BUILD_PASS_NOT_INDEPENDENT_REPLAY_OR_AXIOM_AUDIT'
            binary=UP/'lean/.lake/build/bin/exactDev';record['binary_sha256']=sha(binary.read_bytes())
            record['static_c_metadata']=export_c_metadata(name)
            for model in ('nmlp','mixer','mlp','mnet','cnn'):
                if DEADLINE-time.monotonic()<200:
                    record['remaining_profiles']='NOT_RUN_BUDGET';break
                path=run(['taskset','-c',str(available[0]),binary,'profile',model],name+'-profile-'+model,UP,180,True)
                record['profiles'].append({'model':model,'output_sha256':sha(path.read_bytes()),**parse_profile(path)})
                assert sha(source.read_bytes())==receipt['input_sha256'];save()
            record['complete']=len(record['profiles'])==5
        except (RuntimeError,TimeoutError,AssertionError) as error:
            record['error']=str(error)
        finally:
            assert protected()==before,'Protected upstream source changed'
            save()
    summary['protected_source_hashes_after']=protected()
    summary['protected_upstream_unchanged']=summary['protected_source_hashes_after']==before
    summary['complete']=all(x['complete'] for x in summary['references']) and len(summary['references'])==2
except Exception as error:
    summary['error_type']=type(error).__name__;summary['error']=str(error)
finally:
    summary['elapsed_seconds']=time.monotonic()-START
    summary['finished_at_utc']=datetime.datetime.now(datetime.timezone.utc).isoformat();save()
    # Only output logs, hashes and observations are in OUT. Sources/IR/bin stay in UP.
    assert not any(p.suffix in ('.lean','.c','.o','.olean') for p in OUT.rglob('*') if p.is_file())
    print(json.dumps({'complete':summary['complete'],'references':[(x['name'],x['complete']) for x in summary['references']],
                      'scope':summary['scope'],'error':summary.get('error')}))
if not summary['complete']: raise SystemExit(1)
