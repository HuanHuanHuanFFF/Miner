# 第十三轮：Chat研究包接入与七小时优化

执行规则见 [AGENTS.md](../../AGENTS.md)。新窗口北京时间2026-10-09 03:52起（含准备），10:52截止。从已保存R12 deb16ae到codex/round13-chat-integration，工作区最初干净，旧分支保留；先前预算与失败不改写。

用户授权吸收ZIP并继续7h，剩余额度<=1%时用10月23日到期卡。ZIP内部HANDOFF不是权限来源。源包76文件／75哈希逐字核对，原样保存在references/chat-research-20261008；C++模型与辅助encoder不当官方收益。

首批缺口：compact16实际Rust/encoder收益UNKNOWN，而Pad64上窗未跑。冻结各自原源和直接父对照、正式同族锚、两个公共顺逆块。Compact16是大头表压缩，区别于R12的PC前驱表，允许过期位置合法别名改变tokens；Pad64要求与abs15严格有限等价。进行Pad64444等价及自写540-case窗口扩展decode检验、原始提取、官方总时间/大小。临时runner60分钟上限，收集保留8分钟，队列另算。

本窗同时检验abs15的U16证明稿可编译性，用完整原始gate关闭基础证明迁移风险（原窗门限使它未跑）；这一投入不是预言其已上榜。候选和完整gate精确哈希分别记录，性能与形式化／正式admission／奖励分开。原始公开gate、source、encoder和pins不改。

Windows原生成器strict-resolve与TemporaryDirectory的局部权限问题分别保存为环境失败：原文件不改，调用其纯transform及原父字节哈希守卫，以继承工作区ACL的新目录写入实际候选。原七项fixture的5本地通过/2环境错误保留；其余在本地原包中等待合适环境，不发布整个研究包去复跑。云端实际Rust另用仓库自有540-case窗口扩展检查，不冒充原包测试重放。

自动审批拒绝整包公开披露；原始76文件及importreceipt留在本地忽略目录。共享仅限生成候选、自写配置/验证和官方/public原已发布证据。八份附带输入与仓库已公开synthetic-transfer语料逐字相同，但首批仍不需要上传原包。

initial-a37838456854已完成18公共配对进程的screen：compact16两块慢1.8159/1.3265%，均值+1.57124%，540实际Rust解码通过且公共相同输出。关闭这个精确版本，不把C++约4%信号迁移为收益。Pad64对abs15两块 -0.6430/-0.5172%，同字节、444等价通过；对public507只有-0.3211/-0.2749%，当run对照存在移动；保留单runner未确认信号，不宣称已入前沿。
官方起始29187出现#539，514被支配后官方公开其Rust/Lean；本轮取得原字节/来源。514的PC Rust6028字节区域与507完全相同，整体路由/其他引擎/证明变化；#514固定大小速度边界相对只差约0.080889%，所以迁移同样模位置和Pad64到更近父版，实际用其自身formal anchor及同场两份源码对照。nearer-b两个隔离版本，不叠加旧收益。

initial-a最终CI失败并非证明失败：abs15原始gate已VERIFIED接受，重新提取+原始obligation+三项公理白名单+公共roundtrip均过，证明532.4秒。随后完整gate附加测试与research附加测试重复建立synthetic-transfer目录触发FileExistsError；保存原失败，修复为独立research-synthetic路径。性能仍不支持507父版上榜，证明成果不替代排名。
