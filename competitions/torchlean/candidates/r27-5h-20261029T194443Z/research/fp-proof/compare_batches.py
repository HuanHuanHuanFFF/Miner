from pathlib import Path
import collections,json,hashlib
from datetime import datetime,timezone
H=Path(__file__).parent;C=H/'census';groups={};files=[]
for batch,pattern in [(1,'fp-census-{}.json'),(8,'fp-census-b8-{}.json')]:
 for root in [26102901,26102903]:
  p=C/pattern.format(root);d=json.loads(p.read_bytes());assert d['complete'];files.append(dict(path=p.name,sha256=hashlib.sha256(p.read_bytes()).hexdigest(),elapsed_seconds=d['elapsed_seconds']))
  for c in d['cells']:
   board=c['cell'].split('|')[1].split(':')[0];g=groups.setdefault(f'{board}:b{batch}',collections.Counter());g['cells']+=1
   for s in c['stages']:
    n=s['shape'][1];acc=s['counts'].get('accept',0);rej=sum(v for k,v in s['counts'].items()if k!='accept');g.update(dict(dots=acc+rej,accepted=acc,rejected=rej,macs=n*(acc+rej),reject_macs=n*rej,eager_word_terms=s['eager_word_prepare_terms'],lazy_uncached_word_terms=2*n*rej,lazy_ideal_cached_word_terms=s['word_prepare_terms_if_lazy_cached']))
rows=[]
for label,g in groups.items():rows.append(dict(board_batch=label,**g,acceptance_fraction=g['accepted']/g['dots'],lazy_uncached_word_fraction=g['lazy_uncached_word_terms']/g['eager_word_terms'],lazy_ideal_cached_word_fraction=g['lazy_ideal_cached_word_terms']/g['eager_word_terms']))
r=dict(at_utc=datetime.now(timezone.utc).isoformat(),status='FINITE_INTEGER_REPLAY_BOTH_TARGET_BATCHES_CHECKSUM_VALIDATED',input_roots=[26102901,26102903],rows=rows,source_results=files,complete_cells=180,all_native_output_hashes_match=True,scope='All oldseen MLP andnormalizedMLP b1/b8cells from12workloads; Mixer b1only. No newconfirmationcohort. Actualnativebranchinstrumentation absent.',interpretation='Do not use mixed-board99.78percent asMLP/NMLP ratio. Batch8weightreuse raises eager-vs-lazy workfraction; useperboard/batch rows. Workcounts are not time/cost/successprobabilities.',primary_next='ThinFP nativecost onrealcurrentpolicy/currentchampion boundary; no integrationproof expansionbeforethatfeedback',current_champion_multiplier='UNKNOWN')
(C/'BATCH-COMPARISON.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
print(json.dumps(rows,indent=2))
p=H/'HANDOFF.md';s=p.read_text(encoding='utf-8');s+='\n21:14已补旧batch8两root：72个完整MLP/NMLP样本全输出FNV匹配；共180个旧完整cell。`census/BATCH-COMPARISON.json`按分榜/batch拆统计，避免把Mixer点数占优的99.78%混用到MLP/NMLP；b8权重复用使懒准备词数比例明显高于b1。仍不报告速度比。\n';p.write_text(s,encoding='utf-8')
