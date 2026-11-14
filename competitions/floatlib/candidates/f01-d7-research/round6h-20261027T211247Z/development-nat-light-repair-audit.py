"""[DEBUG-R22-NAT-LIGHT] Two exact historical proof blocks, original caps, no score."""
from pathlib import Path
import hashlib, importlib.util, json, re, subprocess, threading, time

def stages(g,kernel,out,manifest):
    here=Path(__file__).resolve().parent
    root=next(p for p in here.parents if (p/'AGENTS.md').is_file())
    base=root/'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
    assert hashlib.sha256(base.read_bytes()).hexdigest()==manifest['base_audit_sha256']
    assert g._BUILD_MEMORY_MB==4096 and manifest['diagnostic_only']
    for i in manifest['components']:
        p=(root/i['path']).resolve();assert p.is_relative_to(here/'development-nat-light-repair')
        assert hashlib.sha256(p.read_bytes()).hexdigest()==i['sha256'] and p.stat().st_size==i['bytes']
    spec=importlib.util.spec_from_file_location('r22_isolation_base',base)
    module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
    original=module.stages(g,kernel,out,manifest)
    def isolate(src,verdict):
        records=[];known_scopes=set();deadline=time.monotonic()+360
        for name in ('NatPostBeforeNormalizedExplicit','NatPostLightExplicit','MathOutletLightExplicit'):
            if records and not records[-1].get('typecheck_complete'):
                records.append({'name':name,'status':'SKIPPED_PREVIOUS_REQUIRED_PROBE_FAILED','typecheck_complete':False})
                (out/'nat-light-repair.json').write_text(json.dumps({'records':records,'complete':len(records)==3,'new_public_proof':'NOT_RUN'},indent=2)+'\n');continue
            source=here/'development-nat-light-repair'/(name+'.lean')
            path=g.WORK.parent/('R22'+name+'.lean')
            assert not path.exists();path.write_bytes(source.read_bytes())
            samples=[];errors=[];scopes=set();stop=threading.Event();started=time.monotonic()
            record={'name':name,'source_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'diagnostic_only':True,'original_build_memory_mb':4096,'cap_seconds':90,'scope':'Previouslytypednat_bias explicit plus conditional normalized range proof repair, originaldomain/runtime/caps unchanged. RSS sum may doublecount shared pages. Requiredchain NatBias thenNatPost thenMath48AX; failedprefixskipsdescendants, no newpublicacceptance.'}
            def watch():
                while not stop.is_set():
                    processes=[];groups={}
                    for item in Path('/proc').iterdir():
                        if not item.name.isdecimal():continue
                        try:
                            comm=(item/'comm').read_text().strip()
                            if comm not in ('lean','lake','systemd-run','bwrap'):continue
                            fields=dict(x.split(':',1) for x in (item/'status').read_text().splitlines() if ':' in x)
                            processes.append({'pid':int(item.name),'name':comm,'rss_kb':int(fields.get('VmRSS','0 kB').split()[0])})
                            for line in (item/'cgroup').read_text().splitlines():
                                if not line.startswith('0::'):continue
                                relative=line[3:].lstrip('/');group=(Path('/sys/fs/cgroup')/relative).resolve()
                                if not group.is_relative_to('/sys/fs/cgroup'):continue
                                metrics={}
                                for metric in ('memory.current','memory.peak','memory.max','memory.events'):
                                    try:metrics[metric]=(group/metric).read_text().strip()
                                    except OSError:metrics[metric]='UNKNOWN'
                                groups[relative]=metrics
                                if re.fullmatch(r'run-[A-Za-z0-9_.-]+\.scope',group.name):scopes.add(group.name)
                        except (OSError,ValueError):continue
                    samples.append({'elapsed_seconds':time.monotonic()-started,'processes':processes,'groups':groups})
                    stop.wait(.25)
            monitor=threading.Thread(target=watch,daemon=True);monitor.start()
            try:
                code,output=g.own([g.LAKE,'env','lean','work/'+path.name],min(90,g._BUILD_TIMEOUT,max(1,deadline-time.monotonic()-20)),build='read')
                raw=output.encode();(out/(name+'-output.raw')).write_bytes(raw)
                record.update(exit_code=code,elapsed_seconds=time.monotonic()-started,output_sha256=hashlib.sha256(raw).hexdigest(),typecheck_complete=code==0)
                if name=='MathOutletLightExplicit' and code==0:
                    record['math_axiom_reports']=module.parse_reports(output,manifest['math_outlet_expected_roots'],g.AXIOMS)
                    record['math_axioms_pass']=len(record['math_axiom_reports'])==48
                    record['new_math_independent_kernel_replay']='NOT_RUN'
            except Exception as error:
                record.update(error_type=type(error).__name__,error=str(error),typecheck_complete=False)
            finally:
                stop.set();monitor.join(timeout=2)
                record['systemd_scopes']=[]
                for unit in sorted(scopes)[:12]:
                    try:
                        response=subprocess.run(['systemctl','--user','show',unit,'--property=Result,MemoryPeak,MemoryMax,OOMPolicy,ActiveState,SubState'],capture_output=True,text=True,timeout=3)
                        record['systemd_scopes'].append({'unit':unit,'exit_code':response.returncode,'properties':response.stdout if response.returncode==0 else 'UNKNOWN_SCOPE_GONE'})
                    except (OSError,subprocess.TimeoutExpired):record['systemd_scopes'].append({'unit':unit,'properties':'UNKNOWN_QUERY_FAILED'})
                record['new_scope_units']=sorted(scopes-known_scopes);known_scopes.update(scopes)
                data=(json.dumps(samples,indent=2)+'\n').encode();(out/(name+'-resources.json')).write_bytes(data)
                record.update(resources_sha256=hashlib.sha256(data).hexdigest(),max_observed_rss_sum_kb=max((sum(x['rss_kb'] for x in s['processes']) for s in samples),default=0))
                path.unlink();records.append(record);(out/'nat-light-repair.json').write_text(json.dumps({'records':records,'complete':len(records)==3,'new_public_proof':'NOT_RUN','score':'NOT_RUN'},indent=2)+'\n')
        return None if all(x.get('typecheck_complete') for x in records) else 'Historical shared blocks isolated; failing exact probes retained, see outline-isolation.json'
    return original+[('outline-shared-proof-isolation',isolate)]
