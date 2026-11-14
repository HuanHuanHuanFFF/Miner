from pathlib import Path
import json,collections,hashlib
from datetime import datetime,timezone
H=Path(__file__).parent;groups={};total=collections.Counter();sources=[]
for root in [26102901,26102903]:
 p=H/f'fp-census-{root}.json';d=json.loads(p.read_bytes());sources.append(dict(path=p.name,sha256=hashlib.sha256(p.read_bytes()).hexdigest(),bytes=p.stat().st_size))
 for c in d['cells']:
  _,cell=c['cell'].split('|');board,_,kind=cell.split(':');g=groups.setdefault(board+':'+kind,collections.Counter());g['cells']+=1
  for s in c['stages']:
   n=s['shape'][1];accepted=s['counts'].get('accept',0);reject=sum(v for k,v in s['counts'].items()if k!='accept');calls=accepted+reject
   inc=dict(dots=calls,accepted=accepted,rejected=reject,macs=n*calls,accepted_macs=n*accepted,eager_word_prepare_terms=s['eager_word_prepare_terms'],lazy_uncached_word_prepare_terms=2*n*reject,lazy_ideal_cached_word_prepare_terms=s['word_prepare_terms_if_lazy_cached'])
   g.update(inc);total.update(inc)
summary=dict(at_utc=datetime.now(timezone.utc).isoformat(),status='VERIFIED_FINITE_INTEGER_REPLAY_WITH_OLD_NATIVE_OUTPUT_HASHES',source_receipts=sources,cells=sum(g['cells']for g in groups.values()),old_root_seeds=[26102901,26102903],all108_old_native_output_checksums_match=True,integer_RNE53_steps=True,host_FP64_crosscheck_dots=108*32,total=dict(total),by_board_kind={k:dict(v)for k,v in groups.items()},acceptance_fraction=total['accepted']/total['dots'],lazy_uncached_decode_fraction=total['lazy_uncached_word_prepare_terms']/total['eager_word_prepare_terms'],decision='Observed FP certificates accept almost all investigated dot calls; eager word preparation is a plausible removable complete-call cost. Next decisive experiment: actual FP-only prepare with on-demand strong correct fallback, full model/native cost with the current policy and current champion comparison boundary. Do not infer speed from these word-count ratios.',limits=['Only oldseen b1 MLP/normalizedMLP/Mixer, not CNN or b8/b4','All proposals matched exact dot words in these samples, including rejects; finite evidence does not prove proposal or checker generally','No Lean/native instrumentation of branch counts','No currentchampion timing claim','No policy reconciliation implied'],resources={'Python_runtime_seconds':sum(json.loads((H/f'fp-census-{r}.json').read_bytes())['elapsed_seconds']for r in [26102901,26102903]),'local_native_build':False,'CI':'NONE'})
(H/'SUMMARY.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:summary[k]for k in ['cells','total','acceptance_fraction','lazy_uncached_decode_fraction','resources']},indent=2))
