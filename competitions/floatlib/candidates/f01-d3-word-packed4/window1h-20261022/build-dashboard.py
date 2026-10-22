"""Render the four-operation dashboard from full-gate evidence only."""
from pathlib import Path
from statistics import median
import datetime,hashlib,json,os
ROOT=Path.cwd();OWN=Path(__file__).resolve().parent
HISTORY=ROOT/'competitions/floatlib/evidence/public-source-survey-20261021T101011Z'
CLOSING=OWN/json.loads((OWN/'current-official-snapshot.json').read_bytes())['directory']
snapshot=json.loads((CLOSING/'receipts.json').read_bytes())
for row in snapshot['responses'].values():
 data=(CLOSING/row['file']).read_bytes();assert len(data)==row['bytes'] and hashlib.sha256(data).hexdigest()==row['sha256']
champ=json.loads((CLOSING/'champion-detail.raw').read_bytes())
chain=json.loads((HISTORY/'findings.json').read_bytes())['champion_hash_chain'];assert chain[0]['digest']==champ['digest']
factors={n:1. for n in champ['classes']}
for edge in chain:
 d=json.loads((HISTORY/f'submission-{edge["ratio_entry"]}.raw').read_bytes());assert d['digest']==edge['digest'] and d['champion_sha256']==edge['reference_digest']
 for n in factors:factors[n]*=d['classes'][n]['ratio']
assert chain[-1]['reference_digest']=='5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868'
new=json.loads((OWN/'summary.json').read_bytes());old=json.loads((ROOT/'competitions/floatlib/candidates/f01-rebuilt-mul-proof1/window90/summary.json').read_bytes());runs=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'
previous=json.loads((ROOT/'competitions/floatlib/candidates/f01-d1-inline-all/window1h/summary.json').read_bytes())
previous_d2=json.loads((ROOT/'competitions/floatlib/candidates/f01-d2-native-bmm/window10h/summary.json').read_bytes())
records=[]
for source,rows in [('old',old['records']),('previous',previous['records']),('previous_d2',previous_d2['records']),('new',new['records'])]:
 for r in rows:
  if not r.get('full_gate') or not r.get('passed') or r['candidate']=='baseline':continue
  if source!='old':path=ROOT/r['verdict_path']
  else:
   d=runs/str(r['run']);a=d/json.loads((d/'original-artifact-hashes.json').read_bytes())['directory'];batch=json.loads((a/'summary.json').read_bytes());row=next(x for x in batch['results'] if x['candidate']==r['candidate']);path=a/row['verdict']
  v=json.loads(path.read_bytes());assert v['passed'] and v['mode']=='gate' and len(v['classes'])==12 and len(v['rounds'])==25
  values={}
  for k in ['add','mul','sum','bmm']:
   weights={n:x['submission_ns'] for n,x in champ['classes'].items() if n.startswith(k+':')};values[k]=sum(w*v['classes'][n]['ratio']/factors[n] for n,w in weights.items())/sum(weights.values())
  overall=sum(x['submission_ns']*v['classes'][n]['ratio']/factors[n] for n,x in champ['classes'].items())/sum(x['submission_ns'] for x in champ['classes'].values())
  records.append({'candidate':r['candidate'],'kernel_sha256':r['kernel_sha256'],'run':r['run'],'values':values,'whole_entry_inferred':overall,'verdict_path':path.relative_to(ROOT).as_posix(),'verdict_sha256':hashlib.sha256(path.read_bytes()).hexdigest()})
labels={'f01-rebuilt-mul-proof1':'固定宽度乘法','f01-index-hoist-proof2':'地址基址外提','f01-tensor-specialization':'调用边界特化','f01-d1-inline-all':'标量与张量展开','f01-d1-direct-dot-loop':'直接点积循环','f01-d1-native-add-proof1':'已证原生加法','f01-d1-native-both-proof1':'已证原生加乘','f01-d1-native-sum-acc':'原生累加器求和','f01-d2-native-bmm-proof1':'原生矩阵累加器','f01-d2-no-raw-guards-proof1':'精简原生加乘','f01-d2-final-finite':'最终检查原生归约','f01-d2-usize-bmm':'机器字索引矩阵','f01-d2-usize-bmm-proof1':'机器字索引矩阵','f01-d2-preconverted-bmm':'预转换原生矩阵','f01-d2-checked-floatarray':'连续浮点数组矩阵','f01-d2-native-fold-sum-proof1':'标准循环原生求和','f01-d2-word-finite-guards-proof1':'整数判断原生加乘'}
eligible={'add':['f01-d1-native-add-proof1','f01-d1-native-both-proof1','f01-rebuilt-mul-proof1'],'mul':['f01-rebuilt-mul-proof1','f01-d1-native-both-proof1'],'sum':['f01-tensor-specialization','f01-d1-inline-all','f01-d1-native-add-proof1','f01-d1-native-both-proof1','f01-d1-native-sum-acc'],'bmm':['f01-index-hoist-proof2','f01-d1-direct-dot-loop','f01-d1-inline-all','f01-d1-native-add-proof1','f01-d1-native-both-proof1']}
for names in eligible.values():names.extend(['f01-d2-no-raw-guards-proof1','f01-d2-final-finite'])
eligible['bmm'].extend(['f01-d2-native-bmm-proof1','f01-d2-usize-bmm'])
eligible['bmm'].extend(['f01-d2-usize-bmm-proof1','f01-d2-preconverted-bmm','f01-d2-checked-floatarray'])
eligible['sum'].append('f01-d2-native-fold-sum-proof1')
for k in ['add','mul']:eligible[k].append('f01-d2-word-finite-guards-proof1')
labels.update({'f01-d2-preconverted-usize':'预转换与机器字索引','f01-d2-word-preconverted-usize':'整数判断组合优化','f01-d2-hybrid-preconverted-usize':'混合乘法组合优化','f01-d2-web-packed4-proof1':'四输出矩阵累加'})
eligible['bmm'].extend(['f01-d2-preconverted-usize','f01-d2-word-preconverted-usize','f01-d2-hybrid-preconverted-usize','f01-d2-web-packed4-proof1'])
for k in ['add','mul']:eligible[k].extend(['f01-d2-word-preconverted-usize','f01-d2-hybrid-preconverted-usize'])
labels.update({'f01-d3-word-packed4':'整数判断与四输出矩阵','f01-d3-fused-floatarray':'单遍连续数组矩阵'})
for k in eligible:eligible[k].append('f01-d3-word-packed4')
eligible['bmm'].append('f01-d3-fused-floatarray')
labels.update({'f01-d3-word-packed4-usize-proof1':'四路机器字矩阵','f01-d3-word-packed8-proof1':'八输出矩阵累加','f01-d3-word-packed8-usize-proof1':'八路机器字矩阵','f01-d3-inline-decode-sum':'数值重构有序求和'})
for k in eligible:eligible[k].extend(['f01-d3-word-packed4-usize-proof1','f01-d3-word-packed8-proof1','f01-d3-word-packed8-usize-proof1'])
eligible['sum'].append('f01-d3-inline-decode-sum')
labels['f01-d3-final-package']='八路矩阵与重构求和'
for k in eligible:eligible[k].append('f01-d3-final-package')
selected={}
for k,names in eligible.items():
 options=[]
 for name in names:
  xs=[r for r in records if r['candidate']==name]
  if xs:options.append({'candidate':name,'label':labels[name],'relative_to_champion_inferred':median(r['values'][k] for r in xs),'full_gate_runs':len(xs),'kernel_sha256':xs[0]['kernel_sha256'],'runs':[r['run'] for r in xs]})
 selected[k]=min(options,key=lambda x:x['relative_to_champion_inferred'])
result={'champion_submission':champ['id'],'champion_sha256':champ['digest'],'policy_snapshot':json.loads((CLOSING/'competition.raw').read_bytes())['current_snapshot_id'],'snapshot_receipts':(CLOSING/'receipts.json').relative_to(ROOT).as_posix(),'queried_at_utc':snapshot['responses']['champion-detail']['queried_at_utc'],'method':'INFERRED: per-class exact-digest historical chain, current champion timing weights, candidate/reference paired class ratios, median over frozen-source full gates. Same-digest promotions excluded; no shared overall multiplier used.','direct_champion_ratio':'UNKNOWN','records':records,'selected_by_operation':selected,'factors_champion_over_shipped':factors,'formal_submission':'NOT_SUBMITTED'}
def save(path,data):
 tmp=path.with_name(path.name+'.update-tmp');tmp.write_bytes((json.dumps(data,ensure_ascii=False,indent=2)+'\n').encode());os.replace(tmp,path)
save(OWN/'operation-comparisons.json',result)
def display(x):
 return f'{x:.2f}' if x<1 else (f'{x:.1f}' if x<10 else f'{x:.0f}' if x<100 else f'{round(x,-1):.0f}')
stamp=datetime.datetime.fromisoformat(result['queried_at_utc']).astimezone(datetime.timezone(datetime.timedelta(hours=8))).strftime('%Y-%m-%d %H:%M')
text=f'# FloatLib 冲冠看板\n\n冠军核对：[{stamp} 北京时间](competitions/floatlib/candidates/f01-d3-word-packed4/window1h-20261022/operation-comparisons.json)｜各项均以现任完整包冠军为 1.00×，耗时越低越好。\n\n| 运算 | 现任冠军 | 我方首选 | 我方／冠军耗时 | 验证 |\n| --- | --- | --- | ---: | --- |\n'
for k,title in [('add','加法'),('mul','乘法'),('sum','求和'),('bmm','矩阵乘法')]:
 s=selected[k];cid=champ['id'];reference=f'[#{cid}](https://conjectures.io/v1/competitions/floatlib/submissions/{cid})' if k=='add' else f'#{cid}';count='两次' if s['full_gate_runs']==2 else '一次' if s['full_gate_runs']==1 else str(s['full_gate_runs'])+'次';text+=f'| {title} {k} | {reference} | [{s["label"]}](competitions/floatlib/candidates/{s["candidate"]}/Kernel.lean) | **约 {display(s["relative_to_champion_inferred"])}×** | 通过{count} |\n'
text+='\n**结论：差距进一步缩小，当前仍不能取代冠军。**\n';p=ROOT/'dashboard.md';tmp=p.with_name(p.name+'.update-tmp');tmp.write_bytes(text.encode());os.replace(tmp,p)
print(json.dumps({'selected':selected,'whole_entry_inferred':{n:median(r['whole_entry_inferred'] for r in records if r['candidate']==n) for n in labels if any(r['candidate']==n for r in records)}},ensure_ascii=False,indent=2))
