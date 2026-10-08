"""Bind a successful original public gate to its exact current source/proof pair."""
from pathlib import Path
import argparse
import ast
import hashlib
import json
import re

ROOT=Path(__file__).resolve().parents[1]


def load(p):
    return json.loads(p.read_bytes())


def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('candidate')
    ap.add_argument('receipt',type=Path)
    args=ap.parse_args()
    assert re.fullmatch(r'r11-[a-z0-9-]+',args.candidate)
    folder=args.receipt.resolve()
    assert folder.is_relative_to((ROOT/'evidence/round11').resolve())
    state,ci=load(folder/'state.json'),load(folder/'ci-run.json')
    assert ci['status']=='completed' and str(ci['databaseId'])==state['run_id']
    assert ci['headSha']==state['git_sha']
    entry=next(e for e in state['spec']['entries'] if e['name']==args.candidate)
    candidate=(ROOT/entry['path']).resolve()
    assert candidate.is_relative_to((ROOT/'candidates').resolve())
    hashes=entry['hashes']
    assert hashes==load(candidate/'manifest.json')['hashes']
    for file,digest in hashes.items():
        assert sha(candidate/file)==sha(folder/('input-'+args.candidate)/file)==digest
    raw_inventory=load(folder/'raw-artifact-files.json')
    for file,item in raw_inventory['files'].items():
        path=(folder/file).resolve()
        assert path.is_relative_to(folder) and path.stat().st_size==item['bytes'] and sha(path)==item['sha256']
    gate=load(folder/(args.candidate+'-gate.json'))
    assert gate==state['gates'][args.candidate] and gate['accepted'] is True
    assert gate['corpora']==['corpus-stage1']
    expected=next(m['output_bytes'] for m in state['metrics'] if m['candidate']==args.candidate)
    assert gate['methods']['submission']['output_bytes']==expected
    log_path=folder/(args.candidate+'-gate.log')
    log=re.sub(r'\x1b\[[0-9;]*m','',log_path.read_text(encoding='utf-8'))
    assert 'charon+aeneas re-run by the verifier, no new axioms' in log
    assert '`LZ77.Obligation slot.parse` typechecks' in log
    match=re.search(r'5 axioms\s+ok[^\n]*?(\[.*?\]); extraction intact',log)
    assert match
    axioms=ast.literal_eval(match[1])
    assert set(axioms)=={'Classical.choice','Quot.sound','propext'}
    core=re.search(r'verification accepted in ([0-9.]+)s',log)
    assert core
    report={'status':'VERIFIED_FULL_PUBLIC_STAGE1_GATE','candidate':args.candidate,
        'run_id':state['run_id'],'source_commit':ci['headSha'],'run_url':ci['url'],
        'files':hashes,'corpora':gate['corpora'],'public_inputs':28,'public_raw_bytes':15930000,
        'public_output_bytes':expected,'official_accepted':True,
        'checks':['Official re-extraction','Original LZ77.Obligation','Axiom whitelist','Public round trip'],
        'allowed_axioms':sorted(axioms),'core_verification_seconds':float(core[1]),
        'timing_scope':'Core verification only; excludes the subsequent benchmark/scoring and extra synthetic checks.',
        'additional_synthetic_inputs':len(state.get('synthetic_validation',{}).get('inputs',{})),
        'receipt':folder.relative_to(ROOT).as_posix(),
        'receipt_sha256':{file:sha(folder/file) for file in ('state.json','ci-run.json','raw-artifact-files.json',args.candidate+'-gate.json',args.candidate+'-gate.log')},
        'formal_status':'NOT_SUBMITTED; private corpus, admission and rewards UNKNOWN',
        'equivalence_boundary':'Public identical-output and finite native comparisons are separate evidence; this gate does not prove universal token equivalence to the parent.'}
    (candidate/'VERIFICATION.json').write_bytes((json.dumps(report,indent=2)+'\n').encode())
    print(json.dumps({'candidate':args.candidate,'accepted':True,'files':hashes,'core_verification_seconds':report['core_verification_seconds']}))


if __name__=='__main__':
    main()
