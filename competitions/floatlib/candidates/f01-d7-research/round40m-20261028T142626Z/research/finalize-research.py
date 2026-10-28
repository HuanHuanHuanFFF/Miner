"""Refresh one research entry and its exact file inventory at the fixed cutoff."""
from pathlib import Path
import json,hashlib,datetime,argparse,subprocess
ROOT=next(p for p in Path(__file__).resolve().parents if (p/'AGENTS.md').is_file());HERE=Path(__file__).resolve().parent
ap=argparse.ArgumentParser();ap.add_argument('--close',action='store_true');args=ap.parse_args()
now=datetime.datetime.now(datetime.timezone.utc);deadline=datetime.datetime.fromisoformat('2026-10-28T15:06:26+00:00')
if args.close:assert now>=deadline,'Do not close the shared window early'
status=json.loads((HERE/'research-status.json').read_bytes())
jobs=json.loads((HERE.parent/'development-jobs.json').read_bytes())['jobs']
for job in jobs:
 cp=HERE.parent/'ci-runs'/str(job['run'])/'ci-run.json'
 if cp.is_file():
  cm=json.loads(cp.read_bytes());job['coordinator_snapshot_state']=job['status'];job['status']=cm['status'];job['conclusion']=cm['conclusion']
status.update(updated_at_utc=now.isoformat(),state='WINDOW_CLOSED_COLLECT_EXISTING_CI_ONLY' if args.close else 'RUNNING_VERIFICATION',
 proof_status='Transport3 + conditionalPrefix3 + actualProducer2 five roots PASS original statement/two modules/allowedaxioms. Reader2 FAIL four tile branch goals; FloatArray FAIL two typing locations. Public integer MUL49 roots PASS, no new timing.',
 current_ci=jobs,browser_pro='Disabled Usage limit reached at initial browser check; no request/upload/download',
 known_root_capacity_gap='NONE_OBSERVED; not continuously instrumented',tokens='UNKNOWN',cache_input_tokens='UNKNOWN',
 root_observed_wall_span_to_cutoff_seconds=2106,root_observed_span_scope='14:31:20 first observed tool to15:06:26; not CPU/model active time; latejoin4m54 not replaced',
 remaining='Complete new publicBMM endpoint and whole original25 timing/independentadoption remain open. Original ABI object captured despite capture_codegen=false: hot→cold jmp but cold→hot ordinary call, two-sided-tail premise fails for this toy.',
 next_decision='Finish exact third-run feedback. Current indexed shape covers only7.9~8.6% old whole time, do not promote narrow route to10% whole target. Segmented-hot/borrowed ABI are discriminators, not measured speedups.')
(HERE/'research-status.json').write_text(json.dumps(status,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
entry='''# R23研究当前交接

共同UTC窗口2026-10-28 14:26:26—15:06:26；D唯一Git/CI。R首observed工具14:31:20，至截止35m06墙钟跨度；不当连续模型工时，未观察到capacity缺口，token/cacheUNKNOWN。当前状态见research-status.json。

- **已验**：5d0e/255067B actual indexed output→Nat output3根、0d76/254926B actual4row/tail/output conditionalPrefix3根，40708758777原statement、Submission+VerifyFull和允许公理PASS。R重核192原件/12178975B，精确回执 originals-verified-40708758777-*.json。Prefix仍有reader假设，不冒充完整publicBMM。
- **公共乘法证明**：D f90d/253978B原四义务、两模块及49审计根PASS，R已重核原件；无25轮计时/独立采用成绩，不替换B2。全部三CI原394件/22258107B已逐项重hash，见all-ci-originals-verified.json。
- **定点修复结果**：af9b producer只getInternal/getElem重写形态失败；新producer2 c2d24c27/255143B在第三40711515352/head a3d92aca原两模块/5根PASS，已与原失败相对核验。reader2 7a41b05c/249735B同步该修复，但仍FAIL四个tile第二列不可能分支类型目标，尚未闭合。FloatArray f59d仍6724/6741类型目标FAIL。旧源/失败原件保留，未继续改代码/新CI。
- **独立静态**：新reader原176运行声明逐行保持；完整NatPrefix/reader/guarded草稿在prefix/与producer/，均按各自实际gate状态；完整public端点尚未替换。Root项目check fresh PASS只含轻量路径/配置/字节，不是Lean或性能。
- **投入改变**：producer/cost-frontier.json绑定旧逐case：当前eligible入口仅整包7.87/8.03/8.62/8.52%，即使整入口耗时消失旧样本也不到10%；不外推私有。收组件后转更广热点，见ALLOCATION-DECISION.md；保留B2，不重追f7ba seed。
- **下一机制验收**：借用ABI b0ef/228277B两模块/2根PASS；既有第三CI实际捕获C/对象/ASM。原对象8fd09ad2精确hot→cold为jmp，cold→hot为普通call+调用者清理/return，两侧都尾跳的前提FAIL；两exactbody未发现直接数组inc/dec调用，不能把toy寄存器形态推为BMM收益。见tail-abi-machine-original.json。segmented warm-prefix07b7仍草稿/无driver/NOT_RUN。无新性能/正式提交/资金/本机Lean。

最终源清单research-file-manifest.json；D按持续授权提交推送，远端精确commit回执前不称全已推。已启动CI到点后只回收与交付，不新增研究。
'''
(HERE/'HANDOFF.md').write_text(entry,encoding='utf-8')
roots=[HERE,*sorted((ROOT/'competitions/floatlib/candidates').glob('f01-r23-research-*'))]
files=[]
for folder in roots:
 for p in sorted(folder.rglob('*')):
  if not p.is_file() or '__pycache__' in p.parts or p.name=='research-file-manifest.json':continue
  b=p.read_bytes();files.append(dict(path=p.relative_to(ROOT).as_posix(),bytes=len(b),sha256=hashlib.sha256(b).hexdigest()))
manifest=dict(generated_at_utc=now.isoformat(),state=status['state'],files=files,count=len(files),bytes=sum(f['bytes'] for f in files),excludes='manifest itself and ignored __pycache__ only; D-owned dev files/CI evidence indexed separately')
(HERE/'research-file-manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:manifest[k] for k in ('state','count','bytes')}))
