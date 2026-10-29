"""Audit saved R26 native-only evidence; no network, CI, Lean, or native build."""
from __future__ import annotations
import argparse, datetime, hashlib, importlib.util, json, math, re, shlex, sys
from pathlib import Path, PurePosixPath
HERE=Path(__file__).resolve().parent
ROUND=HERE.parent
ROOT=ROUND.parents[3]
R25=ROOT/'competitions/torchlean/candidates/r25-90m-20261029T064916Z/verification/analyze-results.py'
OFFICIAL='accb82b6e2adeda1b41a57a260d68fb3879c427e'
BRANCH='huan/codex-gpt'
PLAN_PATH='competitions/torchlean/candidates/r26-1h-20261029T085515Z/ci-plan.json'
RUNNER_PATH='competitions/torchlean/candidates/r26-1h-20261029T085515Z/development/ci-bridge/runner.py'
class AuditError(RuntimeError): pass

def sha(data): return hashlib.sha256(data).hexdigest()
def blob(data): return hashlib.sha1(b'blob '+str(len(data)).encode()+b'\0'+data).hexdigest()
def j(path):
    try: return json.loads(path.read_text(encoding='utf-8'))
    except Exception as e: raise AuditError(f'bad/missing JSON {path}: {type(e).__name__}: {e}') from e
def utc(s): return datetime.datetime.fromisoformat(s.replace('Z','+00:00'))
def contained(base, rel):
    p=PurePosixPath(rel.replace('\\','/'))
    if p.is_absolute() or '..' in p.parts: raise AuditError(f'unsafe path: {rel}')
    out=(base/Path(*p.parts)).resolve(); out.relative_to(base.resolve()); return out

def r25_tools():
    spec=importlib.util.spec_from_file_location('r25_native_audit_subset',R25)
    mod=importlib.util.module_from_spec(spec); sys.modules[spec.name]=mod; spec.loader.exec_module(mod)
    modules,pins=mod.load_pinned_modules()
    return mod,modules,pins

def find_dispatch(evidence, run_id):
    hits=[]
    for p in evidence.glob('dispatch-*/dispatch.json'):
        d=j(p)
        if str((d.get('run') or {}).get('databaseId'))==str(run_id): hits.append((p,d))
    if len(hits)!=1: raise AuditError(f'expected one dispatch receipt for {run_id}, found {len(hits)}')
    return hits[0]

def select_review(plan_sha, run_id):
    hits=[]
    for p in HERE.glob('preflight*.json'):
        d=j(p); sent=d.get('actual_dispatch',{})
        h=sent.get('plan_sha256') or d.get('frozen_plan',{}).get('sha256')
        rid=sent.get('run_id') or (d.get('current_run') or {}).get('run_id')
        if h==plan_sha and (rid is None or str(rid)==str(run_id)): hits.append((p,d,rid is not None))
    bound=[x for x in hits if x[2]]
    use=bound or hits
    if len(use)!=1: raise AuditError(f'expected one matching saved preflight, found {len(use)}')
    return use[0][0],use[0][1]

def select_review_run(run_id):
    hits=[]
    for p in HERE.glob('preflight*.json'):
        d=j(p); rid=(d.get('actual_dispatch') or {}).get('run_id') or (d.get('current_run') or {}).get('run_id')
        if rid is not None and str(rid)==str(run_id): hits.append((p,d))
    if len(hits)!=1: raise AuditError(f'expected one run-bound preflight for {run_id}, found {len(hits)}')
    return hits[0]

def audit_tree(base, manifest, excluded=()):
    if not isinstance(manifest,dict): raise AuditError(f'invalid hash manifest: {base}')
    rows=[]
    for rel,exp in sorted(manifest.items()):
        p=contained(base,rel)
        if not p.is_file(): rows.append({'path':rel,'status':'MISSING'}); continue
        b=p.read_bytes(); got={'bytes':len(b),'sha256':sha(b)}
        rows.append({'path':rel,**got,'status':'PASS' if got=={'bytes':exp.get('bytes'),'sha256':exp.get('sha256')} else 'MISMATCH'})
    actual={p.relative_to(base).as_posix() for p in base.rglob('*') if p.is_file() and p.relative_to(base).as_posix() not in set(excluded)}
    expected=set(manifest)
    missing=sorted(expected-actual); extra=sorted(actual-expected-set(excluded))
    return {'status':'PASS' if all(x['status']=='PASS' for x in rows) and not missing and not extra else 'FAIL','files':len(rows),'missing':missing,'unexpected':extra,'entries':rows}

def trace_args(path):
    d=j(path)
    if d.get('synthetic') is not False: raise AuditError(f'synthetic compiler trace: {path.name}')
    xs=[x['message'][3:] for x in d.get('log',[]) if x.get('message','').startswith('.> ')]
    if len(xs)!=1: raise AuditError(f'expected one argv in {path.name}')
    return shlex.split(xs[0])
def normalize(xs):
    return [re.sub(r'(?<=/)(?:MainExact|R26NativeMain)(?=\.)','<MAIN>',re.sub(r'(?<=/)(?:benchExact|r26Native)(?=\.|$)','<BIN>',x)) for x in xs]
def check_flags(folder):
    out={}
    for kind in ('compile','link','response'):
        a=folder/f'original-{kind}.raw'; b=folder/f'owned-{kind}.raw'
        old=shlex.split(a.read_text()) if kind=='response' else trace_args(a)
        new=shlex.split(b.read_text()) if kind=='response' else trace_args(b)
        saved=j(folder/'flags.json').get(kind,{})
        ok=normalize(old)==normalize(new) and saved.get('original_args')==old and saved.get('owned_args')==new and saved.get('equal_only_root_mapping') is True
        out[kind]={'equal_after_only_target_name_mapping':ok,'status':'PASS' if ok else 'FAIL'}
    if not all(x['status']=='PASS' for x in out.values()): raise AuditError(f'compiler/linker flag delta: {out}')
    return out

def command_receipts(summary, folder):
    rows=summary.get('commands',[]); by={x.get('label'):x for x in rows}
    need={'setup','setup-check','reference-proof','quick-config'}
    if set(by)!=need or len(rows)!=len(need): raise AuditError(f'command labels mismatch: {sorted(by)}')
    for name,x in by.items():
        log=folder/f'{name}.log'
        if x.get('exit_code')!=0 or not log.is_file() or sha(log.read_bytes())!=x.get('log_sha256'): raise AuditError(f'command/log mismatch: {name}')
    s=by['setup']['argv']; c=by['setup-check']['argv']; v=by['reference-proof']['argv']; q=by['quick-config']['argv']
    if not ('systemd-run' in s and '--scope' in s and 'MemoryMax=4096M' in s and 'MemorySwapMax=0' in s and s[-3:]==['bash','setup.sh','--benchmark-worker']): raise AuditError('setup argv mismatch')
    if c[-3:]!=['bash','setup.sh','--check']: raise AuditError('setup-check argv mismatch')
    if not ('-m' in v and v[v.index('-m')+1]=='verification' and '--verdict' in v and 'r26-reference' in ' '.join(v)): raise AuditError('reference proof argv mismatch')
    if not ('scripts/exact-config.py' in q and '--quick' in q and q[q.index('--board')+1]=='overall' and '--reference' in q and '--output' in q): raise AuditError('official quick config argv mismatch')
    if PurePosixPath(q[q.index('--reference')+1].replace('\\','/')).name!='Kernel.lean': raise AuditError('reference source filename mismatch')
    return {k:{'argv':by[k]['argv'],'exit_code':by[k]['exit_code']} for k in sorted(need)}

def partial_commands(summary,folder):
    out=[]
    for x in summary.get('commands',[]):
        log=folder/f'{x.get("label")}.log'
        if not log.is_file() or sha(log.read_bytes())!=x.get('log_sha256'): raise AuditError(f'partial command log mismatch: {x.get("label")}')
        out.append({'label':x.get('label'),'argv':x.get('argv'),'exit_code':x.get('exit_code'),'log_hash_match':True})
    return out

def raw_rounds(folder,name,seed,req,result):
    keys={f"{w['id']}|{c}" for w in req['workloads'] for c in req['cells']}
    for i,r in enumerate(result['rounds']):
        if r.get('reference_first') is not (i%2==0): raise AuditError(f'order mismatch {name}/{seed}/round{i}')
        for side in ('reference','candidate'):
            data=j(folder/f'{name}-{seed}-round{i}-{side}.json')
            if set(data)!=keys: raise AuditError(f'raw cell set mismatch {name}/{seed}/round{i}/{side}')
            for cell,pair in data.items():
                x=r['cells'][cell]
                if not isinstance(pair,list) or len(pair)!=2 or isinstance(pair[0],bool) or not isinstance(pair[0],(int,float)) or not math.isfinite(pair[0]) or pair[0]<=0 or type(pair[1]) is not int or not 0<=pair[1]<2**32: raise AuditError(f'invalid raw timing/checksum {cell}')
                if pair!=[x[f'{side}_ns'],x[f'{side}_checksum']]: raise AuditError(f'raw/aggregate disagreement {cell}')

def diagnostics(plan,summary,folder):
    rows=summary.get('proof_diagnostics',[])
    if not isinstance(rows,list): raise AuditError('proof diagnostics malformed')
    got={x.get('name'):x for x in rows}
    if len(got)!=len(rows) or set(got)-{x['name'] for x in plan.get('proof_diagnostics',[])}: raise AuditError('unexpected proof diagnostic')
    out=[]
    for x in plan.get('proof_diagnostics',[]):
        if x.get('measure') is not False: raise AuditError('proof diagnostic unexpectedly measured')
        row=got.get(x['name'])
        if row is None: out.append({'name':x['name'],'status':'NOT_RUN_OR_SKIPPED','proof_acceptance':'NOT_ESTABLISHED'}); continue
        if row.get('sha256')!=x['sha256'] or row.get('scope')!='RAW_STATEMENT_DIAGNOSTIC_ONLY_NOT_FULL_GATE': raise AuditError(f'diagnostic scope/source mismatch: {x["name"]}')
        log=folder/f'{x["name"]}-raw-statement.log'
        if not log.is_file(): raise AuditError(f'diagnostic raw log missing: {x["name"]}')
        out.append({'name':x['name'],'path':x['path'],'sha256':x['sha256'],'measure':False,'exit_code':row.get('exit_code'),'raw_log':log.name,'status':'RAW_STATEMENT_DIAGNOSTIC_ONLY','proof_acceptance':'NOT_ESTABLISHED'})
    return out

def analyze(run_dir):
    ci=j(run_dir/'ci-run.json'); run_id=str(ci.get('databaseId',run_dir.name)); evidence=run_dir.parent
    dp,dispatch=find_dispatch(evidence,run_id); folder=next((p for p in run_dir.glob('download-*') if p.is_dir() and (p/'summary.json').is_file()),None)
    if folder is None: raise AuditError('downloaded artifact missing')
    outer=j(run_dir/'original-artifact-hashes.json')
    if outer.get('directory')!=folder.name: raise AuditError('artifact directory receipt mismatch')
    hashes=audit_tree(folder,outer.get('files',{}))
    if hashes['status']!='PASS': raise AuditError('downloaded artifact hash mismatch')
    inner=j(folder/'file-hashes.json'); inside=audit_tree(folder,inner,excluded=('file-hashes.json',))
    if inside['status']!='PASS': raise AuditError('runner file-hashes mismatch')
    summary=j(folder/'summary.json')
    if not (folder/'plan.json').is_file():
        review_path,review=select_review_run(run_id); sent=review.get('actual_dispatch',{}); frozen=dispatch.get('frozen_files',{}); run_meta=dispatch.get('run',{})
        plan_hash=sent.get('plan_sha256')
        if not plan_hash or frozen.get(PLAN_PATH)!=plan_hash or frozen.get(RUNNER_PATH)!=sent.get('runner_sha256'): raise AuditError('missing-artifact run is not bound to its reviewed frozen plan/runner')
        if dispatch.get('state')!='RUN_IDENTIFIED' or dispatch.get('repository_public') is not True or dispatch.get('source_commit')!=ci.get('headSha') or str(run_meta.get('databaseId'))!=run_id or run_meta.get('headSha')!=ci.get('headSha'): raise AuditError('dispatch/CI run identity mismatch')
        req=dispatch.get('request',{}); inputs=req.get('inputs',{})
        if not (req.get('ref')==BRANCH and inputs.get('competition')=='floatlib' and inputs.get('candidates')=='__torchlean_r26__' and str(inputs.get('allow_private')).lower()=='false'): raise AuditError('public R26 dispatch inputs mismatch')
        runtime={'.github/workflows/deflate-baseline.yml':review.get('frozen_sources',{}).get('workflow_sha256'),'competitions/torchlean/scripts/ci-prepare.sh':review.get('frozen_sources',{}).get('ci_prepare_sha256')}
        if any(not h or frozen.get(p)!=h for p,h in runtime.items()): raise AuditError('workflow/preparation hash changed after review')
        fs=review.get('frozen_sources',{}); sources=[fs.get('candidate'),fs.get('reference'),*fs.get('proof_diagnostics',[])]
        if any(not e or frozen.get(e.get('path'))!=e.get('sha256') for e in sources): raise AuditError('source hash not bound to no-plan dispatch')
        if ci.get('status')!='completed' or not any(x.get('name')=='torchlean_r26' and x.get('status')=='completed' for x in ci.get('jobs',[])): raise AuditError('missing-plan run is not terminal')
        if str(summary.get('run_id'))!=run_id or summary.get('source_commit')!=ci.get('headSha') or summary.get('official_commit')!=OFFICIAL or summary.get('scope')!='UNPROVED_NATIVE_RESEARCH_ONLY_NO_ORIGINAL_GATE_PASS_FOR_PROTOTYPE' or summary.get('current_champion_measurement') is not False: raise AuditError('missing-plan summary identity/scope mismatch')
        cutoff=utc(review.get('plan_cutoff_utc')); started=utc(summary['started_at_utc'])
        if OFFICIAL not in (folder/'prepare.log').read_text(errors='replace'): raise AuditError('official checkout pin missing from prepare log')
        arts=j(run_dir/'artifacts.json').get('artifacts',[]); am=outer.get('artifact',{}); matches=[x for x in arts if x.get('id')==am.get('id')]
        if len(matches)!=1 or matches[0].get('expired') is not False or matches[0].get('name')!=f'torchlean-{run_id}-receipts': raise AuditError('downloaded artifact metadata mismatch')
        return {'round':'R26','run_id':run_id,'status':'INCOMPLETE_NO_ARTIFACT_PLAN','ci':{'conclusion':ci.get('conclusion'),'job_conclusion':next((x.get('conclusion') for x in ci.get('jobs',[]) if x.get('name')=='torchlean_r26'),None),'head_sha':ci.get('headSha')},'artifact_plan':{'status':'MISSING','used_live_plan_fallback':False,'expected_frozen_sha256':plan_hash},'preflight_review':str(review_path),'outer_file_hashes':hashes,'runner_file_hashes':inside,'runner_error_type':summary.get('error_type'),'runner_error':summary.get('error'),'runner_started_at_utc':summary.get('started_at_utc'),'frozen_plan_start_cutoff_utc':review.get('plan_cutoff_utc'),'started_after_cutoff':started>=cutoff,'runner_commands':summary.get('commands',[]),'reference_proof':'NOT_RUN','candidate_native_compile':'NOT_RUN','candidate_measurement':'NOT_RUN','overall_score':'UNKNOWN','original_source_postcheck':'UNKNOWN','candidate_proof':'NOT_RUN_NOT_CLAIMED','claim_boundary':'No artifact plan or native measurements were saved; no live plan was substituted.'}
    if not (folder/'cpuinfo.raw').is_file() or not (folder/'cpuinfo.raw').stat().st_size: raise AuditError('raw runner CPU inventory is missing')
    plan_bytes=(folder/'plan.json').read_bytes(); plan=json.loads(plan_bytes)
    review_path,review=select_review(sha(plan_bytes),run_id)
    if plan.get('scope')!='UNPROVED_NATIVE_RESEARCH_ONLY' or plan.get('primary_board')!='overall' or plan.get('official_commit')!=OFFICIAL or plan.get('allow_private') is not False: raise AuditError('saved plan scope/pins mismatch')
    if ci.get('status')!='completed': raise AuditError(f'CI not terminal: {ci.get("status")}')
    jobs=[x for x in ci.get('jobs',[]) if x.get('name')=='torchlean_r26']
    if len(jobs)!=1 or jobs[0].get('status')!='completed': raise AuditError('torchlean_r26 job not terminal')
    if str(summary.get('run_id'))!=run_id or summary.get('source_commit')!=ci.get('headSha') or summary.get('official_commit')!=OFFICIAL: raise AuditError('runner/CI identity mismatch')
    if summary.get('scope')!='UNPROVED_NATIVE_RESEARCH_ONLY_NO_ORIGINAL_GATE_PASS_FOR_PROTOTYPE' or summary.get('current_champion_measurement') is not False: raise AuditError('runner claim boundary mismatch')
    if OFFICIAL not in (folder/'prepare.log').read_text(errors='replace'): raise AuditError('official checkout pin missing from prepare log')
    if utc(summary['started_at_utc'])>=utc(plan['start_cutoff_utc']): raise AuditError('native experiment started after cutoff')
    frozen=dispatch.get('frozen_files',{}); run_meta=dispatch.get('run',{})
    if dispatch.get('state')!='RUN_IDENTIFIED' or dispatch.get('repository_public') is not True or dispatch.get('source_commit')!=ci.get('headSha') or str(run_meta.get('databaseId'))!=run_id or run_meta.get('headSha')!=ci.get('headSha'): raise AuditError('dispatch/CI run identity mismatch')
    req=dispatch.get('request',{}); inputs=req.get('inputs',{})
    if not (req.get('ref')==BRANCH and inputs.get('competition')=='floatlib' and inputs.get('candidates')=='__torchlean_r26__' and str(inputs.get('seed'))==str(plan.get('dispatch_seed')) and str(inputs.get('allow_private')).lower()=='false'): raise AuditError('public R26 dispatch inputs mismatch')
    sent=review.get('actual_dispatch',{}); reviewed_runner=sent.get('runner_sha256') or review.get('bridge_source_hashes',{}).get('runner.py')
    if sha(plan_bytes)!=(sent.get('plan_sha256') or review.get('frozen_plan',{}).get('sha256')) or frozen.get(PLAN_PATH)!=sha(plan_bytes) or frozen.get(RUNNER_PATH)!=reviewed_runner: raise AuditError('frozen plan/runner differs from matching review')
    paths={'.github/workflows/deflate-baseline.yml':sent.get('workflow_sha256') or review.get('frozen_sources',{}).get('workflow_sha256') or review.get('bridge_source_hashes',{}).get('workflow'),'competitions/torchlean/scripts/ci-prepare.sh':sent.get('ci_prepare_sha256') or review.get('frozen_sources',{}).get('ci_prepare_sha256') or review.get('bridge_source_hashes',{}).get('ci_prepare')}
    if any(not h or frozen.get(p)!=h for p,h in paths.items()): raise AuditError('workflow/preparation hash changed after review')
    for e in [plan['reference'],*plan['candidates'],*plan.get('proof_diagnostics',[])]:
        if frozen.get(e['path'])!=e['sha256']: raise AuditError(f'source hash not bound to dispatch: {e["path"]}')
    listed=j(run_dir/'artifacts.json').get('artifacts',[]); am=outer.get('artifact',{}); arts=[x for x in listed if x.get('id')==am.get('id')]
    if len(arts)!=1 or arts[0].get('expired') is not False or arts[0].get('name')!=f'torchlean-{run_id}-receipts': raise AuditError('downloaded artifact metadata mismatch')
    if not summary.get('complete'):
        ref=summary.get('reference_proof',{})
        rows=[{'name':x.get('name'),'proof_state':x.get('proof_state'),'measurement_state':x.get('measurement_state'),'source_sha256':x.get('source_sha256')} for x in summary.get('results',[]) if isinstance(x,dict)]
        commands=partial_commands(summary,folder); labels={x['label'] for x in commands}
        candidate_rows=[x for x in rows if x.get('name')!='retained']
        errors=summary.get('candidate_errors',[])
        measurement_files=[folder/f'{e["name"]}-{seed}-measurement.json' for e in plan.get('candidates',[]) for seed in plan.get('seeds',[])]
        any_measurement=any(p.is_file() for p in measurement_files)
        build_state='NATIVE_BUILD_SUCCEEDED_FOR_REPORTED_ROWS' if candidate_rows else 'NATIVE_BUILD_ATTEMPTED_FAILED' if errors else 'NOT_RUN'
        measure_state='INCOMPLETE_OR_PARTIAL_FILES_PRESENT' if any_measurement else 'NOT_RUN'
        ref_state='PASS_FOR_REFERENCE_ONLY' if ref.get('passed') is True else 'NOT_RUN' if 'reference-proof' not in labels else 'FAILED_OR_INCOMPLETE'
        return {'round':'R26','run_id':run_id,'status':'INCOMPLETE_NATIVE_ONLY_RUN','ci':{'status':ci.get('status'),'conclusion':ci.get('conclusion'),'job_conclusion':jobs[0].get('conclusion'),'head_sha':ci.get('headSha')},'artifact_plan_sha256':sha(plan_bytes),'plan_source':'downloaded plan.json; no live-plan fallback','preflight_review':str(review_path),'dispatch_receipt':str(dp),'outer_file_hashes':hashes,'runner_file_hashes':inside,'command_argv':commands,'runner_error':summary.get('error'),'runner_error_type':summary.get('error_type'),'summary_results':rows,'reference_proof':ref_state,'candidate_native_compile':build_state,'candidate_measurement':measure_state,'overall_score':'UNKNOWN','original_source_postcheck':'PASS' if summary.get('originals_unchanged') is True and summary.get('protected_before')==summary.get('protected_after') else 'UNKNOWN','candidate_proof':'NOT_RUN_NOT_CLAIMED','claim_boundary':'Incomplete native-only cohort; missing measurements are not imputed.'}
    if summary.get('originals_unchanged') is not True or summary.get('protected_before')!=summary.get('protected_after'): raise AuditError('original source preservation receipt mismatch')
    verdict=summary.get('reference_proof',{})
    if not (verdict.get('passed') is True and verdict.get('stage')=='axioms' and verdict.get('verifier_fingerprint')==verdict.get('verifier_fingerprint_end')): raise AuditError('retained reference original gate did not pass')
    if not re.fullmatch(r'[0-9a-f]{64}',summary.get('owned_main_equals_original_sha256','')): raise AuditError('MainExact copy hash missing')
    mod,modules,pins=r25_tools()
    cmds=command_receipts(summary,folder)
    candidate_rows={x.get('name'):x for x in summary.get('results',[])}
    if len(plan.get('candidates',[]))<1: raise AuditError('no frozen candidates')
    config=modules['config']; cfg=config.Config.load(folder/'overall-config.toml'); board=cfg.plan('overall')
    cells=[f'{m}:b{b}:{k}' for m in config.MODELS for b in config.BATCHES[m] for k in config.KINDS]
    if len(cells)!=30: raise AuditError('pinned model config does not define 30 cells')
    score_rows=[]; cpu_all=[]
    for cand in plan['candidates']:
        cr=candidate_rows.get(cand['name']); rr=candidate_rows.get('retained')
        if not cr or not rr or cr.get('source_path')!=cand['path'] or cr.get('source_sha256')!=cand['sha256'] or rr.get('source_path')!=plan['reference']['path'] or rr.get('source_sha256')!=plan['reference']['sha256']: raise AuditError('summary source filename/hash mismatch')
        if PurePosixPath(cand['path']).name!='Kernel.lean' or PurePosixPath(plan['reference']['path']).name!='Kernel.lean' or cand.get('proof_state')!='UNPROVED_NATIVE_RESEARCH_ONLY' or cr.get('proof_state')!='NOT_PROVED_NATIVE_ONLY': raise AuditError('candidate proof/source boundary mismatch')
        if rr.get('proof_state')!='RETAINED_REFERENCE_PREVIOUSLY_PROVED' or cr.get('measurement_state')!='COMPLETE_NATIVE_ONLY_EXPLORATION' or not cr.get('flags_pass'): raise AuditError('candidate/reference runner state mismatch')
        flags=check_flags(folder/cand['name']); pairs=[]; cpu=[]; measured=[]
        timing=cfg.timing|board['timing']|cfg.environments['local']['timing']; timing.update(build_seconds=300,cached_build_seconds=180,benchmark_seconds=300,run_seconds=120)
        for seed in plan['seeds']:
            seed=int(seed); request=j(folder/f'{cand["name"]}-{seed}-request.json'); raw=j(folder/f'{cand["name"]}-{seed}-measurement.json'); result=raw.get('result')
            if not isinstance(result,dict): raise AuditError('measurement result missing')
            parsed=config.MeasurementRequest.parse(request)
            if not (request.get('candidate_hash')==cand['sha256'] and request.get('reference_hash')==plan['reference']['sha256'] and request.get('seed')==seed and request.get('cells')==cells and request.get('workloads')==modules['multiseed'].workloads(seed) and request.get('timing')==timing and request.get('identity')==cfg.environments['local']['identity'] and request.get('benchmark_identity')==board['benchmark_identity'] and len(parsed.cells)*len(parsed.workloads)==180): raise AuditError(f'request contract mismatch {cand["name"]}/{seed}')
            checked=mod.measurement_check(request,raw,board['cells'],modules)
            if checked.get('status')!='PASS': raise AuditError(f'pinned measurement validation failed: {checked}')
            raw_rounds(folder,cand['name'],seed,request,result)
            paired=sum(len(x['cells']) for x in result['rounds']); ns=2*paired; checks=sum(x.get('reference_checksum')==x.get('candidate_checksum') for r in result['rounds'] for x in r['cells'].values())
            if len(result['rounds'])!=5 or paired!=900 or ns!=1800 or checks!=900: raise AuditError(f'row/ns/checksum counts mismatch {cand["name"]}/{seed}')
            prov=result.get('provenance',{})
            if prov.get('identity')!=request.get('identity') or prov.get('candidate_binary')!=cr.get('binary_sha256') or prov.get('reference_binary')!=rr.get('binary_sha256'): raise AuditError(f'binary/CPU identity mismatch {cand["name"]}/{seed}')
            cpu.append({k:prov.get(k) for k in ('identity','machine','architecture','cpu_affinity')}); cpu_all.append(cpu[-1]); pairs.append((request,result)); measured.append({'seed':seed,'pairs':paired,'ns_values':ns,'checksum_pairs':checks,'status':'PASS'})
        if len(pairs)!=2 or any(cpu[0].get(k)!=cpu[1].get(k) for k in ('identity','machine','architecture','cpu_affinity')): raise AuditError('same CPU provenance mismatch')
        scoring_plan=dict(board); scoring_plan['strata']=[{'environment':q['environment'],'identity':q['identity'],'seed':q['seed'],'weight':1/len(pairs),'timing':q['timing']} for q,_ in pairs]
        score=modules['scoring'].assess(scoring_plan,pairs)
        score_rows.append({'candidate':cand['name'],'candidate_source':{'path':cand['path'],'filename':'Kernel.lean','sha256':cand['sha256']},'reference':{'path':plan['reference']['path'],'filename':'Kernel.lean','sha256':plan['reference']['sha256']},'proof':'NOT_RUN_NOT_CLAIMED_UNPROVED_NATIVE_RESEARCH_ONLY','flags':flags,'per_seed':measured,'total_pairs':sum(x['pairs'] for x in measured),'total_ns_values':sum(x['ns_values'] for x in measured),'total_checksum_pairs':sum(x['checksum_pairs'] for x in measured),'cpu':cpu,'score_vs_saved_reference':score,'status':'NATIVE_ONLY_DIAGNOSTIC'})
    if len({tuple(x.get(k) for k in ('identity','machine','architecture','cpu_affinity')) for x in cpu_all})>1: raise AuditError('CPU provenance differs across candidates')
    diag=diagnostics(plan,summary,folder)
    ci_ok=ci.get('conclusion')=='success' and jobs[0].get('conclusion')=='success'
    return {'round':'R26','run_id':run_id,'status':'COMPLETE_NATIVE_ONLY_DIAGNOSTIC' if ci_ok else 'COMPLETE_NATIVE_ONLY_DIAGNOSTIC_CI_FAILURE','ci':{'status':ci.get('status'),'conclusion':ci.get('conclusion'),'head_sha':ci.get('headSha')},'artifact_plan_sha256':sha(plan_bytes),'plan_source':'downloaded plan.json; no live-plan fallback','preflight_review':str(review_path),'dispatch_receipt':str(dp),'pinned_scoring_sources':pins,'outer_file_hashes':hashes,'runner_file_hashes':inside,'command_argv':cmds,'owned_target_argv_from_frozen_runner':'g.LAKE -f work/R26NativeLake.lean build r26Native (the summary does not separately record the resolved g.LAKE executable path)','MainExact_sha256':summary['owned_main_equals_original_sha256'],'MainExact_identity':'runner copied official bytes and asserted byte equality; raw Lean files not included separately','candidate_comparisons':score_rows,'proof_diagnostics':diag,'reference_scope':'retained only; no same-run originalshipped pair','candidate_proof':'NOT_RUN_NOT_CLAIMED','claim_boundary':'Original quick scorer plus finite checksums only; not full proof, original gate, current champion comparison, or promotion.','usage':{'tokens':'UNKNOWN','cached_input_tokens':'UNKNOWN','continuous_model_cpu':'UNKNOWN'}}

def main():
    ap=argparse.ArgumentParser(description=__doc__); ap.add_argument('--run-dir',type=Path,required=True); ap.add_argument('--output',type=Path); a=ap.parse_args()
    run_dir=a.run_dir.resolve(); ci=j(run_dir/'ci-run.json'); run_id=str(ci.get('databaseId',run_dir.name)); out=a.output.resolve() if a.output else HERE/f'analysis-{run_id}.json'
    if out.exists(): raise SystemExit(f'refusing to overwrite analysis receipt: {out}')
    try: report=analyze(run_dir)
    except Exception as e: report={'round':'R26','run_id':run_id,'status':'FAILED_OR_INCOMPLETE_NATIVE_ONLY_AUDIT','error_type':type(e).__name__,'error':str(e),'score':'UNKNOWN','candidate_proof':'NOT_RUN_NOT_CLAIMED'}
    out.parent.mkdir(parents=True,exist_ok=True); out.write_text(json.dumps(report,indent=2,ensure_ascii=False)+'\n',encoding='utf-8')
    print(json.dumps({'output':str(out),'status':report.get('status'),'error':report.get('error')}))
    return 0 if report.get('status')=='COMPLETE_NATIVE_ONLY_DIAGNOSTIC' else 1
if __name__=='__main__': raise SystemExit(main())
