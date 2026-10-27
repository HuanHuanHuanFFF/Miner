from pathlib import Path
import json
from datetime import datetime, timezone
p=Path(__file__).with_name('research-status.json')
s=json.loads(p.read_text(encoding='utf-8'))
s.update(state='R7_W12_REPORTED_COMPLETE_RECOVERY_AND_SINGLEPASS_SUM',updated_at_utc=datetime.now(timezone.utc).isoformat(),next_checkpoint_utc='2026-10-22T23:30:00Z',checkpoint='checkpoint-17-canonical-singlepass.md',D_feedback_read='r7-feedback.md D17/D16/D15 at head')
s['active_routes']=['W12 canonical-image raw equality: recover and verify concrete proof interfaces','One controlled single-pass raw-NaN-aware sum candidate; attempt to reuse existing decoder conditions','W11 exact public60f scalar actual MainFull C/asm recovery; no timing claim','Existing proof2 validation remains pending D public-push authorization']
s['active_web_jobs']=[]
s['web_results_awaiting_recovery']=['R7-W11 COMPLETE_REPORT, 25min cap exceeded by about5min; download first45s timeout','R7-W12 COMPLETE_REPORT: unconditional imported native operations, actualrawsum/dot/BMM andraw classifier; download pending']
s['ownership']='R this research directory and f01-r7-* canonical math/single-pass sum; D Git/CI/BMM cold-scan/scalar routes'
s['active_ci_readonly']=[]
s['active_browser_tabs'][0].update(job='R7-W12',state='COMPLETE_REPORT_RECOVERY_PENDING')
s['active_browser_tabs'][1].update(job='R7-W11',state='COMPLETE_REPORT_RECOVERY_PENDING')
s['recovered_web'] += ['R7-W10 ZIP8e299a04/report18b22045 CRC183manifestPASS actualpositivezero product normalization; attribute policy issue in new proof remains','R7-W10b ZIP6ca4e420/reportf35c9542 CRC96manifestPASS raw-return normalizer actualC removes negativezero constant initializer; no timing']
s['remote_validation_boundary']['source']='D17 22:51 UTC; D already asked human asynchronously'
s['remote_validation_boundary']['not_running']='810 local updated99d242fd notpushed/notdispatched; allthrough809 terminalcollected'
s['canonical_image_finite_screen']='canonical-image-oracle.json'
s['bmm_cold_scan_cost_screen']='cold-scan-cost-807.json'
p.write_text(json.dumps(s,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print('checkpoint17 synchronized')
