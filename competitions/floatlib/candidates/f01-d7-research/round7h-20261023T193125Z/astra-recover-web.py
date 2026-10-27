"""Preserve downloaded research originals; check each byte before indexing."""
from pathlib import Path,PurePosixPath
from datetime import datetime,timezone
import hashlib,json,zipfile,stat
HERE=Path(__file__).resolve().parent
DOWNLOAD=Path('E:/Download').resolve()
DEST=(DOWNLOAD/'FloatLib/20261024-R11').resolve()
assert DEST.is_relative_to(DOWNLOAD)
def sha(b):return hashlib.sha256(b).hexdigest()
def save(p,b):
    p=p.resolve();assert p.is_relative_to(DEST)
    p.parent.mkdir(parents=True,exist_ok=True)
    if p.exists():assert p.read_bytes()==b, f'Refusing overwrite: {p}'
    else:p.write_bytes(b)
    assert p.read_bytes()==b
    return {'path':str(p),'bytes':len(b),'sha256':sha(b)}
def recover_w01():
    p=DOWNLOAD/'R11-W01-evidence.zip';b=p.read_bytes()
    assert sha(b)=='c02cb925299415fc1caa85ff5779350c6f2987155f6ebc527076ec6b882c6118'
    record={'id':'R11-W01','url':'https://chatgpt.com/g/g-p-6ac5df8076688191a59072d949f4a880-miner/c/6adbc7e9-70b0-83ee-b7d5-0244ac24d372','original_download':str(p),'archive':save(DEST/'W01'/p.name,b),'files':[]}
    with zipfile.ZipFile(p) as z:
        assert z.testzip() is None
        for i in z.infolist():
            rel=PurePosixPath(i.filename)
            assert not rel.is_absolute() and '..' not in rel.parts and not any(':' in part for part in rel.parts)
            assert not stat.S_ISLNK(i.external_attr>>16) and i.file_size<2000000
            if not i.is_dir():record['files'].append(save(DEST/'W01'/'original-extracted'/Path(*rel.parts),z.read(i)))
        mf=json.loads(z.read('R11-W01/R11-W01-manifest.json'))
        for e in mf['files']:
            data=z.read('R11-W01/'+e['path']);assert len(data)==e['bytes'] and sha(data)==e['sha256']
        orig=z.read('R11-W01/Kernel.original.lean')
        local=(HERE.parent.parent/'f01-r11-crossrow-p2-pack12/Kernel.lean').read_bytes()
        assert orig==local
        patch=z.read('R11-W01/R11-W01-conditional.patch').decode()
        altered=z.read('R11-W01/Kernel.conditional.lean')
        # Exact source transformation checked locally; no downloaded program executed.
        a=orig.index(b'theorem natLoop_lane');end=orig.index(b'\ndef wordLoop',a)
        expected=orig[:a]+orig[a:end].replace(b'termination_by n-k\n',b'termination_by n-k\ndecreasing_by omega\n')+orig[end:]
        assert expected==altered
        record.update(manifest_payload_hashes_verified=len(mf['files']),source_equals_frozen_4bdd=True,conditional_patch_verified=True,
                      conditional_patch_adopted=False,formal_verification='NOT_RUN',erratum='Uploaded context incorrectly named synthPendingDepth; actual gate allows synthInstance.maxHeartbeats<=400000. Do not use incorrect option in web command examples.')
    return record
def recover_w02():
    names=['R11-W02-report.md','check_r11_w02.py','patch-fragments.md','MANIFEST.json','R11-W02-Lean-obligations.lean']
    entries=[]
    for n in names:
        p=DOWNLOAD/n
        if p.exists():entries.append(save(DEST/'W02'/n,p.read_bytes()))
    recovered=DOWNLOAD/'R11-W02-recovered-artifacts.zip'
    if recovered.exists():
        data=recovered.read_bytes();assert sha(data)=='3f0076c139170349a5b83f364279ff9e180aa520594b5e08d1e94e29908cb735'
        save(DEST/'W02'/recovered.name,data)
        with zipfile.ZipFile(recovered) as z:
            assert z.testzip() is None
            assert set(z.namelist())=={'R11-W02-Lean-obligations.lean','finite-check.log','MANIFEST.json'}
            for n in z.namelist():
                e=save(DEST/'W02'/n,z.read(n))
                if not any(v['path']==e['path'] for v in entries):entries.append(e)
    mf=json.loads((DEST/'W02/MANIFEST.json').read_text())
    for e in mf['files']:
        data=(DEST/'W02'/e['path']).read_bytes();assert len(data)==e['bytes'] and sha(data)==e['sha256']
    return {'id':'R11-W02','url':'https://chatgpt.com/g/g-p-6ac5df8076688191a59072d949f4a880-miner/c/6adbc858-f3d8-83ec-af29-5e492ac26cb3','files':entries,'manifest_payload_hashes_verified':len(mf['files']),'formal_verification':'NOT_RUN','source_hash_in_web_report':'NOT_INDEPENDENTLY_VERIFIED','review':'Local36576word checks and old852exposure separately recorded; webcategoryscript merelycompares classifier with samecategory rule, not an independent arithmetic test. No downloadedscript executed.'}
def recover_w03():
    p=DOWNLOAD/'R11-W03.zip';b=p.read_bytes()
    assert sha(b)=='58cb49f49c6325a795348f7fd0736de3d6974cb69c6e6d1a3f34f8d8082b7da9'
    record={'id':'R11-W03','url':'https://chatgpt.com/g/g-p-6ac5df8076688191a59072d949f4a880-miner/c/6adbc8e3-f970-83ec-a5da-e34b46681b8c','archive':save(DEST/'W03'/p.name,b),'files':[]}
    with zipfile.ZipFile(p) as z:
        assert z.testzip() is None
        for i in z.infolist():
            rel=PurePosixPath(i.filename)
            assert not rel.is_absolute() and '..' not in rel.parts and not any(':' in part for part in rel.parts)
            assert not stat.S_ISLNK(i.external_attr>>16) and i.file_size<2000000
            if not i.is_dir():record['files'].append(save(DEST/'W03'/'original-extracted'/Path(*rel.parts),z.read(i)))
        mf=json.loads(z.read('R11-W03/manifest.json'))
        for e in mf['files']:
            data=z.read('R11-W03/'+e['path']);assert len(data)==e['bytes'] and sha(data)==e['sha256']
        assert z.read('R11-W03/source/Kernel.lean')==(HERE.parent.parent/'f01-r11-crossrow-p2-pack12/Kernel.lean').read_bytes()
        record.update(manifest_payload_hashes_verified=len(mf['files']),source_equals_frozen_4bdd=True,formal_verification='NOT_RUN',candidate_adopted=False,
                      review='A short-shared and B scalar-call are two lowerings of one mathematical mechanism; not independent algorithm gains. Need rebase observedproof2 repairs, gate and actualassembly. No uncompiledvariant promoted.')
    return record
if __name__=='__main__':
    records=[recover_w01(),recover_w02(),recover_w03()]
    out={'at_utc':datetime.now(timezone.utc).isoformat(),'destination':str(DEST),'browser':'Codex in-appbrowser per latesthuman instruction','records':records,'all_original_research_jobs':'COMPLETE_NO_ACTIVE_WEB_GENERATION','library_uploads':'Not needed; directdownloads used. No new publicsharing.'}
    (HERE/'astra-web-deliveries.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    index='''# FloatLib R11 网页6 Pro研究原件

三个原研究及附件回收均完成。这里保存97份解包/独立工件，另保留下载ZIP；原始NOT_RUN与失败记录不改写。当前研究状态请读项目本轮astra-status.json，勿把本页当作后续验收状态。

| 目录 | 原始成果 | 当前核验边界 |
|---|---|---|
| W01/original-extracted/R11-W01 | 完整证明接线审查、条件补丁、尾部地址反例、20文件 | CRC与18项payload哈希通过；original Kernel逐字节等于4bdd；网页未编译 |
| W02 | 零列/单非零列数学报告、分类脚本、Lean义务、日志与原清单 | 5项payload哈希通过；网页分类模型不是FloatLib执行器；未编译 |
| W03/original-extracted/R11-W03 | 短n两种lowering、完整源、38份固定版本公共源码、验证方案 | CRC与payload清单哈希通过；original Kernel逐字节等于4bdd；未生成目标C/asm/计时 |

W01条件termination补丁没有实际报错支持，未采用。真实908失败另由proof2修复，原4bdd和原网页包保留。W03的A/B是同一数学机制的不同代码组织，不能当作两个独立算法收益。A的5c5e重基构建预备位于项目f01-r11-crossrow-short-shared。

W02单非零列另有本地最早两个非有限位置推导和36576有限字测试；旧852曝光很小，暂不生成新Kernel。这些补充记录见项目astra-sparse-math.md和astra-sparse-screen.json，不替换本目录的网页原报告。

下载ZIP SHA-256：
- W01/R11-W01-evidence.zip: c02cb925299415fc1caa85ff5779350c6f2987155f6ebc527076ec6b882c6118
- W02/R11-W02-recovered-artifacts.zip: 3f0076c139170349a5b83f364279ff9e180aa520594b5e08d1e94e29908cb735
- W03/R11-W03.zip: 58cb49f49c6325a795348f7fd0736de3d6974cb69c6e6d1a3f34f8d8082b7da9

项目入口：D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/astra-status.json
完整逐文件下载索引：同目录astra-web-deliveries.json。
上传往返字节核验：同目录astra-upload-roundtrip.json。
后续验收安排：同目录astra-next-validation.md。

已按用户要求用Codex内置浏览器下载；无需Library额外持久上传，没有启用分享。私人会话、截图和网页原始报告保持本地。完整gate、真实代码生成、性能与正式准入仍按精确候选分别确认。
'''
    # This is our mutable navigation index, not an original downloaded payload.
    index_path=(DEST/'README.md').resolve();assert index_path.is_relative_to(DEST)
    index_path.write_bytes(index.encode('utf-8'))
    print(json.dumps({'destination':str(DEST),'records':[{'id':r['id'],'files':len(r['files'])} for r in records]}))
