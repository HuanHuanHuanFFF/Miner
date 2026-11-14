from pathlib import Path
import json
from datetime import datetime,timezone
H=Path(__file__).parent;p=H/'HANDOFF.md';s=p.read_text(encoding='utf-8');s+='\n**任意分榜新取舍**：`MLP-DENSE-ONLY-ROUTE.md`指出可用specKernels保全12接口，仅实现dense.linear冲MLP（快照冠军33），无须把FP证明追加到218KB前任整包。建议ThinFP成本判别顺带MLP；如果有信号，再测ExactRuntime.dotOf懒fallback以去掉Word证明闭包。source约220KB只是组成估算，实际全源/证明/速度仍UNKNOWN，未派CI。\n';p.write_text(s,encoding='utf-8')
p=H/'status.json';d=json.loads(p.read_bytes());d['updated_at_utc']=datetime.now(timezone.utc).isoformat();d['active_work']='Current smallproof feedback plus nativecost wait; source-budget decision identifies dense-onlyMLP full12carrier with spec defaults as possible alternative aftercost. No new integrationclosure orCI launched.';p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print('Board-scoped proof-cost decision recorded')
