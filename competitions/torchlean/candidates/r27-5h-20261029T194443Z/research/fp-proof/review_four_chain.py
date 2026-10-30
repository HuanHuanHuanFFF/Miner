from pathlib import Path
import json,hashlib
from datetime import datetime,timezone
H=Path(__file__).parent;F=H/'follow-on';old=F/'FourChain.lean.inc';s=old.read_text(encoding='utf-8-sig');assert s.count('    rw [p2_add, p2_one]')==1;s=s.replace('    rw [p2_add, p2_one]','    rw [p2_add (k + (L : Int)) 1, p2_one]');s=s.replace('    norm_num\n    ring\n  have hcount','    norm_num <;> ring\n  have hcount')
p=F/'FourChain-v2.lean.inc';p.write_text(s,encoding='utf-8',newline='\n');q=F/'FourChainContractOnly-v2.lean';full=(H/'numerics-v1/Sum3ContractOnly.lean').read_text(encoding='utf-8')+'\n'+s;q.write_text(full,encoding='utf-8',newline='\n')
r=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='FOLLOW_ON_NOT_QUEUED',source=q.relative_to(Path.cwd()).as_posix(),bytes=q.stat().st_size,sha256=hashlib.sha256(q.read_bytes()).hexdigest(),prior_source='FourChainContractOnly.lean',prior_sha256=hashlib.sha256((F/'FourChainContractOnly.lean').read_bytes()).hexdigest(),change='Static tactic review: target p2(K+1) explicitly instead of letting rw p2_add hit lhs p2(k+L); robust optional ring afternorm_num. Mathematicalstatement unchanged.',proof='NOT_RUN',finite_replay={'cells':108,'old_output_hashes':'ALL_MATCH','original_radius_counterexamples':0,'same_checker_counts_as_sequential':True},performance='UNKNOWN')
(F/'four-chain-v2-receipt.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
p=H/'HANDOFF.md';s=p.read_text(encoding='utf-8');s+='\n后续方向已隔离：四路Float累加18KB纸面/Lean草稿复用SUM3，L>=3可保持原半径；108旧cell整数RNE模型无半径反例、accept/miss不变。最新`follow-on/four-chain-v2-receipt.json`，未排CI、未声称native收益；不替代当前checker/prepare验收。\n';p.write_text(s,encoding='utf-8')
print(json.dumps(r,indent=2))
