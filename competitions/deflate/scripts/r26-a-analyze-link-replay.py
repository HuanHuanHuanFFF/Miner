"""Read isolated maintenance evidence; never turn it into a production speed bound."""
from pathlib import Path
import hashlib
import json
import statistics as st
import sys

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'evidence/round26/route-a'

def main():
    p=Path(sys.argv[1]);p=p if p.is_absolute()else ROOT/p;raw=p.read_bytes();r=json.loads(raw)
    assert r['status']=='VERIFIED_REAL_TRACE_IDENTITY_AND_ISOLATED_MAINTENANCE_REPLAY'
    assert len(r['timings'])==1872 and len(r['traces'])==28 and sum(t['events']for t in r['traces'])==3917583
    tr={x['file']:x for x in r['traces']if x['events']};groups={}
    for t in r['timings']:
        assert t['events']==tr[t['file']]['events']
        groups.setdefault((t['file'],t['block'],t['method'],t['mode']),[]).append(t)
    med={}
    for key,ts in groups.items():
        assert len(ts)==12 and sorted(x['rep']for x in ts)==list(range(12))
        assert len({(x['result_digest'],x['return_checksum'])for x in ts})==1
        measured=[x['elapsed_ns']for x in ts if x['phase']=='measured'];assert len(measured)==11
        med[key]={'median_ns':st.median(measured),'min_ns':min(measured),'max_ns':max(measured),'result_digest':ts[0]['result_digest'],'return_checksum':ts[0]['return_checksum']}
    pairs=[]
    for file in tr:
        for block in [1,2]:
            for mode in ['discard_all','consume_all','actual_mixed']:
                a=med[file,block,'parent',mode];b=med[file,block,'row',mode];count=tr[file]['events']
                pairs.append({'file':file,'block':block,'mode':mode,'events':count,'parent':a,'row':b,
                    'parent_ns_per_event':a['median_ns']/count,'row_ns_per_event':b['median_ns']/count,
                    'difference_ns_per_event':(b['median_ns']-a['median_ns'])/count,'row_over_parent':b['median_ns']/a['median_ns']})
    totals=[]
    for block in [1,2]:
        for mode in ['discard_all','consume_all','actual_mixed']:
            xs=[x for x in pairs if x['block']==block and x['mode']==mode];count=sum(x['events']for x in xs)
            a=sum(x['parent']['median_ns']for x in xs);b=sum(x['row']['median_ns']for x in xs)
            totals.append({'block':block,'mode':mode,'events':count,'parent_sum_file_medians_ns':a,'row_sum_file_medians_ns':b,
              'parent_ns_per_event':a/count,'row_ns_per_event':b/count,'difference_ns_per_event':(b-a)/count,'row_over_parent':b/a})
    hist=json.loads((OUT/'a12-paired-cost.json').read_bytes());historical=[]
    for x in hist['comparisons']:
        if x['A']!='public641'or x['B']!='r26-a-641-row8':continue
        fs=[]
        for f in x['files']:
            if f['file']not in tr:continue
            delta=(f['candidate_chosen']['parse_s']-f['parent_chosen']['parse_s'])*1e9
            fs.append({'file':f['file'],'parser_delta_ns':delta,'A12_events':tr[f['file']]['events'],'delta_ns_per_event':delta/tr[f['file']]['events']})
        historical.append({'production_block':x['block'],'sum_parser_delta_ns':sum(f['parser_delta_ns']for f in fs),
          'delta_ns_per_A12_event':sum(f['parser_delta_ns']for f in fs)/3917583,'files':fs})
    report={'status':'VERIFIED_ISOLATED_MAINTENANCE_REPLAY_SUMMARY_NOT_CAUSAL_OR_SPEED_BOUND','run_id':r['run_id'],
      'receipt':p.relative_to(ROOT).as_posix(),'receipt_sha256':hashlib.sha256(raw).hexdigest(),'source_sha256':r['source_sha256'],
      'compile_flags':r['compile_flags'],'affinity':r['affinity'],'totals':totals,'pairs':pairs,'historical_other_runner_production_parser':historical,
      'limits':['Sameeventidentity/count inside replay; actualoldproductiontrajectory isdifferent.','Eventarraybandwidth, noqueryinterleaving, resetcache, checksum andmixedflagbranch affectcost.','Productionreferencecomesfromdifferentrunner; blocknumbersarenotpairedacrossexperiments.','Smallisolateddifferenceonlyrejectsisolatedmaintenance-single-cause sufficiency; actualmaintenanceisnotprovedfree.','Largeisolateddifference isnotcausal attribution orrecoverableoveralltimeupperbound.']}
    (OUT/'cycle-a13-replay-summary.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps({'totals':totals,'historical_parser_ns_per_event':[x['delta_ns_per_A12_event']for x in historical]},indent=2))

if __name__=='__main__':main()
