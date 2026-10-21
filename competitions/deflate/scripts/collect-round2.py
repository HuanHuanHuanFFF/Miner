"""Read round2 GitHub CI metadata/logs using the existing Git credential helper.

Credentials stay in process memory and the gh child environment; never print
them or put them in a project file. No mutation or workflow dispatch is done.
"""
from __future__ import annotations
import json
import os
from pathlib import Path
import re
import subprocess
import sys


def gh_env():
    env = os.environ.copy()
    if not env.get('GH_TOKEN') and not env.get('GITHUB_TOKEN'):
        result = subprocess.run(['git', 'credential', 'fill'], input='protocol=https\nhost=github.com\n\n', text=True, capture_output=True, check=True)
        fields = dict(line.split('=',1) for line in result.stdout.splitlines() if '=' in line)
        if not fields.get('password'):
            raise RuntimeError('Existing GitHub credential unavailable')
        env['GH_TOKEN'] = fields['password']
    return env


def run(args, env):
    result = subprocess.run(['gh', *args],env=env,capture_output=True,text=True,encoding='utf-8',check=True)
    return result.stdout


def main():
    mode, run_id = sys.argv[1:3]
    assert mode in ('--status','--collect') and run_id.isdecimal()
    env = gh_env()
    metadata = json.loads(run(['run','view',run_id,'--repo','HuanHuanHuanFFF/Miner','--json','databaseId,headSha,headBranch,event,status,conclusion,createdAt,updatedAt,url,jobs'],env))
    if mode == '--status':
        print(json.dumps(metadata,ensure_ascii=False)); return
    assert metadata['status']=='completed', 'collect only a completed run'
    target = Path(__file__).resolve().parents[1] / 'evidence/round2' / run_id
    target.mkdir(parents=True,exist_ok=True)
    (target/'ci-run.json').write_text(json.dumps(metadata,indent=2)+'\n',encoding='utf-8')
    log = run(['run','view',run_id,'--repo','HuanHuanHuanFFF/Miner','--log'],env)
    clean = '\n'.join(re.sub(r'\x1b\[[0-?]*[ -/]*[@-~]','',line).rstrip() for line in log.splitlines())+'\n'
    (target/'ci.log').write_text(clean,encoding='utf-8')
    # Preserve complete JSON verdicts printed inside each candidate's markers.
    lines = [re.sub(r'^.*?\t\d{4}-\d{2}-\d{2}T\S+\s?', '',line) for line in clean.splitlines()]
    plain = '\n'.join(lines)
    for label, filename in (('RESEARCH', 'research.json'), ('COMPARISON', 'comparison.json')):
        match = re.search(r'^' + label + r' (\{.*\})$', plain, re.M)
        if match:
            (target / filename).write_text(json.dumps(json.loads(match[1]), indent=2) + '\n', encoding='utf-8')
    # The checker keeps full elaboration output, while its verdict prints only
    # the last 2000 characters. Preserve the diagnostic presentation separately.
    for match in re.finditer(r'^GATE_DIAGNOSTIC_BEGIN (\S+) (\S+)\n(.*?)\nGATE_DIAGNOSTIC_END \1 \2$', plain, re.M | re.S):
        name, filename, full = match.groups()
        assert name in ('bucket2', 'probe3', 'probe2-nice16', 'probe2-nice64')
        assert re.fullmatch(r'\d{3}-[A-Za-z0-9_.-]+\.log', filename)
        (target / (name + '-' + filename)).write_text(full.rstrip() + '\n', encoding='utf-8')
    for match in re.finditer(r'^GATE_DIAGNOSTIC_MANIFEST (\{.*\})$', plain, re.M):
        manifest = json.loads(match[1])
        name = manifest['candidate']
        assert name in ('bucket2', 'probe3', 'probe2-nice16', 'probe2-nice64')
        (target / (name + '-diagnostics.json')).write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
    for name in ('bucket2','probe3','probe2-nice16','probe2-nice64'):
        match = re.search(r'CANDIDATE_GATE_BEGIN '+re.escape(name)+r'\n(.*?)CANDIDATE_GATE_END '+re.escape(name), plain,re.S)
        if not match:
            continue
        fragment=match[1]
        verdicts=[]
        for opening in re.finditer(r'^\{',fragment,re.M):
            try:
                value,_=json.JSONDecoder().raw_decode(fragment[opening.start():])
                if isinstance(value,dict) and 'accepted' in value:
                    verdicts.append(value)
            except json.JSONDecodeError:
                pass
        if verdicts:
            (target/(name+'-gate.json')).write_text(json.dumps(verdicts[-1],indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'path':str(target),'status':metadata['status'],'conclusion':metadata['conclusion'],'headSha':metadata['headSha']}))


if __name__=='__main__':
    main()
