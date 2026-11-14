"""Existing40619267183 original bytes + actual four-root acceptance only."""
from pathlib import Path
import hashlib
import json
import re

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
RUN=HERE.parent/'ci-runs/40619267183'
sha=lambda b:hashlib.sha256(b).hexdigest()


def main():
    index_raw=(RUN/'original-artifact-hashes.json').read_bytes();index=json.loads(index_raw)
    archive=RUN/index['directory'];total=0
    for name,entry in index['files'].items():
        p=(archive/name).resolve();assert p.is_relative_to(archive.resolve())
        b=p.read_bytes();assert len(b)==entry['bytes'] and sha(b)==entry['sha256'],name;total+=len(b)
    parent=archive/'diagnostics/f01-d7-public-suite/public-suite'
    diag=parent/'diagnostics/f01-r22-dev-nat8-projection-probe1'
    source=(parent/'inputs/f01-r22-dev-nat8-projection-probe1/Kernel.lean').read_bytes()
    base=(HERE/'KernelIndexed8Cost.lean').read_bytes();leaf=(HERE/'Nat8Projection-v1.lean.inc').read_bytes()
    assert source==base+b'\n'+leaf
    assert sha(base)=='8e27baf70ce7e3f10b669cc9f59d66d5fffaa17ee3dc6df934f3229139a5b0dd'
    assert sha(leaf)=='79574fb1b64febf7d3cd328fe41c2f11ac2172e81177fd2cb057aa74e574d6dd'
    audit=json.loads((diag/'helper-audit.json').read_bytes())
    roots=json.loads((HERE/'nat8-projection-manifest.json').read_bytes())['roots']
    assert audit['accepted'] and audit['kernel_replay'] and audit['exit_code']==0
    assert audit['kernel_sha256']==sha(source) and audit['names']==roots and audit['expected_count']==4
    allowed={'propext','Classical.choice','Quot.sound'}
    assert set(audit['allowed_axioms'])==allowed
    assert set(audit['reports'])==set(roots) and all(set(a)<=allowed for a in audit['reports'].values())
    axioms=(diag/'helper-axioms.raw').read_bytes()
    assert sha(axioms)==audit['output_sha256']
    log=(diag/'replay.log').read_bytes();text=log.decode()
    assert 'lake build VerifyFull exit=0' in text
    assert '[kernel] Submission replays cleanly' in text and '[kernel] VerifyFull replays cleanly' in text
    verdict=json.loads((diag/'diagnostic-only-verdict.json').read_bytes())
    assert verdict['passed'] and verdict['stage']=='helper-axioms' and verdict['diagnostic_only']
    report={'run':40619267183,'all_original_files':len(index['files']),'all_original_bytes':total,
        'all_original_hashes_match':True,'artifact_index_sha256':sha(index_raw),
        'source_sha256':sha(source),'source_bytes':len(source),'exact8e_prefix_plus795_leaf':True,
        'runtime_source_sha256':sha(base),'leaf_sha256':sha(leaf),'roots':roots,
        'statement':'PASS','Submission_replay':'PASS','VerifyFull_replay':'PASS',
        'selected_helper_axioms':'PASS_ALLOWED3','reports':audit['reports'],
        'helper_audit_sha256':sha((diag/'helper-audit.json').read_bytes()),
        'helper_axioms_sha256':sha(axioms),'raw_replay_log_sha256':sha(log),
        'scope':'VERIFIED conditional row/lane transport toexistingR15 loop/NativeFinal.dotLoop. Cache producer hread still a premise; no full public BMM/performance/adoption claim.',
        'remaining':['Actual producer agreement','finish/read/Prefix/public closure','Wordtransportv2 actualconfirmation']}
    (HERE/'nat8-projection-accepted-40619267183.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(report))


if __name__=='__main__':main()
