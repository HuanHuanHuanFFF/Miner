from pathlib import Path
import json
H=Path('competitions/torchlean/candidates/r27-5h-20261029T194443Z/research/fp-proof')
for n in ['CI-REQUEST-002.json','producer-v1/repair-map.json']:
 p=H/n;d=json.loads(p.read_bytes())
 for r in d.get('candidates',d.get('sources',[])):
  r['path']=r['path'].removeprefix('D:/CodingProject/Bitget/')
 p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
p=H/'status.json';d=json.loads(p.read_bytes());d['next_request']='CI-REQUEST-002.json';d['verification']='9 exact single-import sources original intake/policy PASS, zero placeholder tokens; Lean NOT_RUN';p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
