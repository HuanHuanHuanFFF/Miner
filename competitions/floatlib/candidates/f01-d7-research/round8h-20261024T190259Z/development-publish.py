"""Publish one topic and update only our short shared status, atomically."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json,os,re,stat,subprocess
OUT=Path(__file__).resolve().parent;ROOT=OUT.parents[4]
ap=argparse.ArgumentParser();ap.add_argument('--topic',required=True);ap.add_argument('--summary',required=True);ap.add_argument('--need',default='仅供知悉');ap.add_argument('--artifact',type=Path);ap.add_argument('--state');ap.add_argument('--next');ap.add_argument('--ci');ap.add_argument('--status-need');ap.add_argument('--blocker');ap.add_argument('--processed',action='append',default=[]);a=ap.parse_args()
assert re.fullmatch('[a-z0-9-]+',a.topic)
own=Path('D:/CodingProject/Bitget-Collab/codex');status=own/'status.md'
for p in (own.parent,own,status,own/'messages'):assert not p.lstat().st_file_attributes & stat.FILE_ATTRIBUTE_REPARSE_POINT
now=datetime.now(timezone.utc);stamp=now.strftime('%Y%m%dT%H%M%S%f')[:-3]+'Z';name=stamp+'-r14-development-'+a.topic+'.md'
head=subprocess.check_output(['git','rev-parse','HEAD'],cwd=ROOT).decode().strip()
evidence='分支huan/codex-gpt，当前HEAD '+head
if a.artifact:
    p=a.artifact.resolve();assert p.is_file() and p.is_relative_to(ROOT)
    evidence+='；'+str(p)+'；文件快照SHA-256 '+hashlib.sha256(p.read_bytes()).hexdigest()+'（采纳前核对文件与Git版本）'
message=f'# R14开发交接：{a.topic}\n\n时间：{now.isoformat()}\n关联：R14-20261024T190259Z\n类型：进展／协作\n摘要：{a.summary}\n需要对方：{a.need}\n证据：{evidence}\n结论状态：本条仅报告已写明的文件/作业状态；候选结论以对应原始验收为准。\n下一步：{a.next or "按当前任务继续，在下一阶段检查点读取回复。"}\n'
with (own/'messages'/name).open('xb') as f:f.write(message.encode())
old=status.read_bytes();lines=old.decode().splitlines();changes={'更新时间（UTC）：':now.isoformat(),'HEAD：':head,'最近交接消息：':'codex/messages/'+name}
if a.state:changes['状态：']=a.state
if a.next:changes['下一步：']=a.next
if a.ci:changes['在途CI：']=a.ci
if a.status_need:changes['需要对方：']=a.status_need
if a.blocker:changes['阻塞：']=a.blocker
for i,line in enumerate(lines):
    for prefix,value in changes.items():
        if line.startswith(prefix):lines[i]=prefix+value;break
if a.processed:lines.append('本检查点已处理消息：'+'，'.join(a.processed))
tmp=status.with_name('status-'+stamp+'.tmp');assert not tmp.exists();tmp.write_bytes(('\n'.join(lines)+'\n').encode());assert status.read_bytes()==old;os.replace(tmp,status)
print(json.dumps({'message':str(own/'messages'/name)},ensure_ascii=False))
