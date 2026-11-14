"""Byte identity and public-binding review; not Lean validation."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re

OUT=Path(__file__).resolve().parent
ROOT=OUT.parents[6]
def sha(x): return hashlib.sha256(x).hexdigest()

def namespace_block(raw, name):
    start=raw.index(('namespace '+name).encode())
    marker=('end '+name).encode()
    end=raw.index(marker,start)+len(marker)
    return raw[start:end]

def main():
    dest=OUT/'v2-guarded'
    raw=(dest/'Kernel.lean').read_bytes()
    manifest=json.loads((dest/'manifest.json').read_text())
    assert sha(raw)==manifest['candidate_sha256']
    base=(ROOT/'competitions/floatlib/candidates/f01-r21-dev-streaming-pair-probe2/Kernel.lean').read_bytes()
    pair=namespace_block(raw,'Submission.R21StreamingPair')
    assert pair==namespace_block(base,'Submission.R21StreamingPair')
    source=(ROOT/manifest['cost_runtime_source']).read_bytes()
    cost=namespace_block(raw,'Submission.R22StreamingCost')
    restored=cost.replace(b'else Submission.bmmBeforeR22Streaming batch m n p A B',
                         b'else Submission.bmm batch m n p A B')
    assert restored==namespace_block(source,'Submission.R22StreamingCost')
    # Inspect namespace/declaration structure without treating it as a parser.
    text=raw.decode('utf-8')
    assert len(re.findall(r'^def bmm ',text,re.M))==1
    assert len(re.findall(r'^theorem bmm_spec ',text,re.M))==1
    assert 'def bmmBeforeR22Streaming ' in text
    assert 'theorem bmmBeforeR22Streaming_spec ' in text
    assert len(raw)<=256000
    result={
        'at_utc':datetime.now(timezone.utc).isoformat(),
        'candidate_sha256':sha(raw),'candidate_bytes':len(raw),
        'R21_pair_exact_namespace_byte_match':True,
        'R21_pair_namespace_sha256':sha(pair),
        'D_cost_exact_namespace_match_after_fallback_symbol_rename':True,
        'D_cost_file_sha256':sha(source),
        'public_bmm_declarations':1,'public_bmm_spec_declarations':1,
        'source_limit_pass':True,
        'proof_only_removed_roots':[x['root'] for x in manifest['proof_only_unused_interfaces_removed']],
        'formal':'NOT_RUN','performance':'UNKNOWN',
    }
    (OUT/'source-identity-check.json').write_text(json.dumps(result,indent=2)+'\n')
    status=json.loads((OUT/'status.json').read_text())
    status['updated_at_utc']=result['at_utc']
    (OUT/'status.json').write_text(json.dumps(status,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(result))

if __name__=='__main__':main()
