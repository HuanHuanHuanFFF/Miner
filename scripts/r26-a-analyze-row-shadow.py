"""Summarize fixed-row shadow evidence without treating offers or read counts as quality/time."""
from pathlib import Path
import hashlib
import json
import sys

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'evidence/round26/route-a'

def ratio(n,d):return n/d if d else None

def summarize(c):
    q=c['normal_queries']+c['lazy_queries']
    return {
      'parent':{'prefetches':c['parent_prefetches'],
        'source_words_prefetched':c['parent_prefetch_source_word_reads'],
        'head_reads':c['parent_prefetches']+c['insertions']+c['parent_cache_fix_head_reads'],
        'prev_reads':c['parent_prev_reads'],'head_prev_writes':2*c['insertions'],
        'be4':c['parent_be4_reads'],'be8':c['parent_be8_reads'],
        'xor8_pairs':c['parent_xor8_pairs'],'scalar_pairs':c['parent_scalar_pairs']},
      'row':{'candidate_state_bytes':167936,'insertions':c['insertions'],
        'maintenance_key_reads':c['maintenance_key_be4_reads'],'tag_rmw':c['tag_rmw'],
        'position_writes':c['position_writes'],'cursor_rmw':c['cursor_rmw'],
        'nonempty_victims':c['nonempty_victims'],
        'prefetch_empty_tag_ratio':ratio(c['prefetch_empty_tag_mask'],c['parent_prefetches']),
        'prefetch_empty_despite_parent_equal_key':c['prefetch_empty_with_parent_equal_key'],
        'query_row_changed_since_prefetch_ratio':ratio(c['query_after_changed_row_since_prefetch'],q),
        'query_be4':c['row_query_be4_reads'],'query_be8':c['row_query_be8_reads'],
        'query_xor8_pairs':c['row_query_xor8_pairs'],'query_scalar_pairs':c['row_query_scalar_pairs']},
      **{phase:{'queries':c[phase+'_queries'],
        'parent_matches':c[phase+'_parent_match'],'row_matches':c[phase+'_row_match'],
        'validator_calls':c[phase+'_validator_calls'],'position_reads':c[phase+'_position_reads'],
        'tag_false_positive_per_validation':ratio(c[phase+'_tag_false_positive'],c[phase+'_validator_calls']),
        'evicted_per_parent_match':ratio(c[phase+'_winner_evicted'],c[phase+'_parent_match']),
        'shorter_per_parent_match':ratio(c[phase+'_shorter'],c[phase+'_parent_match']),
        'longer':c[phase+'_longer'],'shorter':c[phase+'_shorter'],'equal_length':c[phase+'_equal_length'],
        'gain_better':c[phase+'_gain_better'],'gain_worse':c[phase+'_gain_worse'],
        'parent_len3':c[phase+'_parent_len3'],'parent_len3_lost':c[phase+'_parent_len3_lost'],
        'row_len3':c[phase+'_row_len3'],
        'parent_only_accepted':c[phase+'_parent_only_accepted'],'row_only_accepted':c[phase+'_row_only_accepted']}
       for phase in ['normal','lazy']}}

def main():
    p=Path(sys.argv[1]);p=p if p.is_absolute()else ROOT/p;raw=p.read_bytes();r=json.loads(raw)
    assert r['status']=='VERIFIED_FROZEN_PARENT_TOKEN_DECODE_AND_FIXED_ROW_COUNTERFACTUAL'
    files=r['files'];assert len(files)==28 and len({f['file']for f in files})==28
    assert all(sum(f['counts'][k]for f in files)==v for k,v in r['totals'].items())
    result={'status':'VERIFIED_SOURCE_LEVEL_COUNTERFACTUAL_SUMMARY_NOT_CANDIDATE_RESULT',
      'run_id':r['run_id'],'receipt':p.relative_to(ROOT).as_posix(),'receipt_sha256':hashlib.sha256(raw).hexdigest(),
      'source_sha256':r['source_sha256'],'observer_sha256':r['observer_sha256'],
      'limitations':['Original parent28tokens/decode unchanged; row offers never emitted.',
        'Counterfactual query helper counts exclude extra truth telemetry and maintenance/preload work, shown separately.',
        'Parent active-PC helper totals and row query-only helper totals have different scopes; not a timing ratio.',
        'Local longer/shorter/gain differences are not future parser quality or original encoder bytes.'],
      'totals':summarize(r['totals']),
      'files':[{'file':f['file'],'engine_calls':f['engine_calls'],**summarize(f['counts'])}for f in files]}
    (OUT/'cycle-a11-row-summary.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps({'run_id':r['run_id'],'totals':result['totals']},indent=2))

if __name__=='__main__':main()
