"""Rehash original receipts and source plans into a compact R research index."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
CS=HERE.parent.parent
RUNS=CS/'f01-mul-log2-proof1/ci-runs'
sha=lambda b:hashlib.sha256(b).hexdigest()
RECORDS=[
 (908,40024012440,'f01-r11-crossrow-p2-pack12',True),
 (912,40029166371,'f01-r11-crossrow-p2-pack12-proof2',True),
 (914,40030638967,'f01-r11-crossrow-p2-pack12-proof2',True),
 (915,40031408913,'f01-r11-crossrow-short-shared',True),
 (916,40032766690,'f01-r11-crossrow-short-shared',True),
 (921,40039524733,'f01-r11-wide4-codegen-probe',False),
 (923,40040850289,'f01-d11-wide-projection-proof',False),
 (923,40040850289,'f01-d11-bmm-wide-backbone',True),
 (924,40041351847,'f01-d11-wide-writer-proof',False),
 (926,40042639860,'f01-r11-wide4-inline',True),
 (928,40043628421,'f01-r11-wide4-inline-proof3',True),
 (929,40044330511,'f01-r11-wide4-inline-proof3',True),
 (932,40046461091,'f01-r11-wide4-cross-combined',True),
]

def main():
    rows=[]
    for seed,run,name,active in RECORDS:
        paths=list((RUNS/str(run)).glob(f'download-*/diagnostics/f01-d7-public-suite/public-suite/{name}-verdict.json'))
        assert len(paths)==1,(seed,name,paths)
        path=paths[0];v=json.loads(path.read_text(encoding='utf-8'))
        planpath=path.parent/'requested-plan.json';plan=json.loads(planpath.read_text(encoding='utf-8'))
        subjects=[c for c in plan['candidates'] if c['candidate']==name]
        assert len(subjects)==1 and plan['seed']==seed
        source=CS/name/'Kernel.lean';raw=source.read_bytes()
        assert sha(raw)==subjects[0]['sha256']
        captures=list((path.parent/'codegen'/name).glob('capture-*/compiled-Submission.lean'))
        for compiled in captures:assert compiled.read_bytes()==raw
        row={'seed':seed,'run':run,'candidate':name,'sha256':sha(raw),'bytes':len(raw),
             'verdict_path':str(path),'verdict_sha256':sha(path.read_bytes()),
             'requested_plan_sha256':sha(planpath.read_bytes()),'actual_compiled_source_matches':len(captures),
             'passed':v['passed'],'stage':v['stage'],'slot':v['slot'],
             'active_entry_changed_by_research_subject':active,
             'new_algorithm_full_gate':bool(active and v['passed'] and v['slot']=='full' and v['stage']=='score'),
             'reason':v['reason']}
        rows.append(row)
    rec={'updated_at_utc':datetime.now(timezone.utc).isoformat(),'records':rows,
         'current_ready':'f01-r11-wide4-cross-combined/e5b279b326e404d210cf2fb254c11a1773f84d2ab39cc853b9172f428c69c2d7',
         'current_next':'28b819 full929PASS; e5b279 statement932PASS; clean full933 then frozen independent confirmation ownedD',
         'prepared_combination':'f01-r11-wide4-cross-combined/e5b279b326e404d210cf2fb254c11a1773f84d2ab39cc853b9172f428c69c2d7',
         'scope':'Original receipts rehashed, requested candidate plan matched to frozen source; compiled bytes independently compared where capture exists. Full gate is public validation, never formal admission or current champion victory. No performance value inferred from statement or unused probes.',
         'web_delivery':'E:/Download/FloatLib/20261024-R11/README.md',
         'web_integrity':'astra-web-handoff-verification.json'}
    (HERE/'astra-proof-ledger.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'records_verified':len(rows),'current':rec['current_ready']}))
if __name__=='__main__':main()
