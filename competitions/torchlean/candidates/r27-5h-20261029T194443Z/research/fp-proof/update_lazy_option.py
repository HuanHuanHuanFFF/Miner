from pathlib import Path
import json,hashlib
H=Path(__file__).parent;C=H/'census';p=H/'LAZY-PREPARE-DISCRIMINATOR.json';d=json.loads(p.read_bytes());d['relative_scalar_equivalence_option']=json.loads((C/'lazy-relative-proof-receipt.json').read_bytes());d['relative_proof_reconstruct']='python -B census/patch_lazy_prepare_proof.py --output <ephemeral>/Kernel.lean --receipt <evidence>/source-receipt.json';p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
p=C/'fp_replay.py';s=p.read_text(encoding='utf-8-sig');s=s.replace("UTIL=H.parents[1]/'board-frontier/norm_frontier.py'","UTIL=H/'formula_snapshot.py'")
(C/'fp_replay-frozen.py').write_text(s,encoding='utf-8',newline='\n')
print('Optional relative scalar proof and frozen census replay entry prepared')
