from pathlib import Path
import re,json,hashlib
from datetime import datetime,timezone
H=Path(__file__).parent;S=H.parent.parent/'competition-state/source-private'
rows=[]
patterns={'Float_type':r'(?<![\w.])Float(?![\w.]|Lib)','FloatArray':r'\bFloatArray\b','Float_ofBits':r'\bFloat\.ofBits\b','Float_toBits':r'\bFloat\.toBits\b','binary64':r'\bbinary64\b','NativeBinary64':r'\bNativeBinary64\b','roundAt':r'\broundAt\b','roundDyadic':r'\broundDyadic\b','roundRatScaled':r'\broundRatScaled\b','UInt64':r'\bUInt64\b','Float_Model':r'\bFloat\.Model\b'}
for n in [12,27]:
 p=S/f'submission{n}-Kernel.lean';b=p.read_bytes();s=b.decode('utf-8-sig')
 rows.append(dict(submission=n,source_sha256=hashlib.sha256(b).hexdigest(),bytes=len(b),counts={k:len(re.findall(v,s)) for k,v in patterns.items()},aliases_first_line_contains_native_fp64=False,scope='Entire UTF8 source searched; line3 aliases inspected. No Float/native64 runtime identifier or roundAt bridge present. Exact UInt64/NativeBinary32 integer paths present. Names heavily aliased; no proof completeness inference from lexical scan.'))
r=dict(at_utc=datetime.now(timezone.utc).isoformat(),source_policy='Local read-only, unknown license whole source not copied or republished',source_request='requests/PUBLIC-RETIRED-CHAMPIONS.json',findings=rows,decision='No ready accepted Float64 producer/orderKey/certify/roundAt closure found in retired12/27. Maintain FP actual proof as independent route; integration into strong retired base requires byte-budget review (27 only353B headroom at256000 cap;12 ~37.8KB headroom). Need replace/remove unused closure or use compiler-compression approach, not append100KB. D controls stronger-base optimization.',evidence_strength='VERIFIED lexical search and source identities, INFERRED representation architecture; no claim on present champion source or speed')
(H/'retired-source-fp-survey.json').write_text(json.dumps(r,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
with (H/'HANDOFF.md').open('a',encoding='utf-8') as f:f.write('\n19:53处理父inbox：已读官方来源请求和退任12/27完整源的别名/primitive入口；未发现native Float64/FloatArray/roundAt桥。`retired-source-fp-survey.json`留hash/全源词汇计数，未复制未知许可整源。FP仍是独立表示路线，但不能直接追加：27仅余353B、12余37768B，完整FP闭包需替换对应旧闭包/压缩后才能集成。\n')
print(json.dumps(r,ensure_ascii=False,indent=2))
