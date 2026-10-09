# 第十三轮：Chat研究接入与七小时优化

执行规则见 [AGENTS.md](../../AGENTS.md)。用户本轮窗口为北京时间2026-10-09 **03:52—10:52**，原始预算见 [budget.json](../../evidence/round13/budget.json)。最终证据在10:49冻结；探索、独立确认和归档已完成，本轮在10:52截止，争榜拿奖励的目标未完成。

本轮尚未取得新的正式admission、排名或奖励。已完成的实际收益是两个精确Rust/Lean pair通过原始公共gate；已收取的标准性能结果仍不足以支持一个新的可支付前沿点。原始数据和失败均保留。

## 证据规模与成果

截至本次更新：27个手动派发全部终态已收取（21成功、6失败），13个完成标准性能作业，共237公共配对进程、13组测量Rust。每个进程是固定28文件/15930000B、1次预热和11次正式计时。计数、同进程诊断、未计时编码重放与本地统计重放不计入标准配对或独立性能runner。

| 已验证成果 | 精确证据 | 边界 |
|---|---|---|
| #507 abs15原始公共gate | [VERIFICATION](../../candidates/r12-fast-pc507-abs15/VERIFICATION.json)，CI37838456854，532.4秒 | 原重新提取、`LZ77.Obligation slot.parse`、三项公理白名单与公共roundtrip接受；随后附加测试目录冲突造成CI失败，不是证明拒绝 |
| #514 abs15原始公共gate | [VERIFICATION](../../candidates/r13-514-abs15/VERIFICATION.json)，CI37842987797，511.8秒 | 精确pair通过，CI最终成功；未正式提交，性能微小信号未确认 |
| 原始回执与版本审计 | [audit.json](../../evidence/round13/audit.json)、[check-round13.py](../../scripts/check-round13.py) | 校验派发commit/spec、下载文件SHA、候选文件与gate输入；不把失败或有限检验当完整验收 |

两个完整gate的允许传递公理均为`propext`、`Classical.choice`、`Quot.sound`。Rust/Lean精确哈希保存在各VERIFICATION与原回执，证书不扩展到其他Lean稿或Rust版本。

## 候选结果与取舍

时间变化相对同场直接父版；负值表示更快。大小变化为公共等权大小轴百分点（pp），不是总字节比例。

| 方向 | 实际结果 | 取舍 |
|---|---|---|
| Chat compact16 | 540实际Rust有限decode与提取通过；总时间+1.57124%，公共输出相同 | 关闭冻结Rust；C++ parser模型未转化为总压缩收益，不投入gate |
| #507 abs15 Pad64 | 444有限token/decode等价；对abs15 -0.58014%，对public507约-0.298% | 只有单runner发现，当前同族投影仍被支配，未gate |
| #514 abs15 | 六环境17块（含后来作为对照的测量）全数保留，等runner均值-0.11997%；条件中心进入前沿；最新对同ELF shadow却+0.04153% | 不遗漏正向中心，也不晋级：异常第四块足以改变中心的符号，最新仅2/4块胜shadow；原gate仅证明正确性 |
| #514 abs15 Pad64 | 发现+0.10821%，独立确认+0.11540% | 暂停这个新父版布局 |
| cap258剪枝 | 原路径约101万追链请求，仅1633初始cap；444实际token/decode等价 | 停在有限检查，不投入完整性能/gate |
| EF32宽15/16-bit键 | 原35065位置里均找回0额外match/byte，observer输出相同 | 两个草稿不做性能实验，排除只限此父版/固定位置 |
| EF32三字节改literal / min4 | 两份各540 decode、提取通过；分别多3935/3720B，时间+1.25760/+0.87236%，大小+0.040153/+0.037959pp | 关闭两份Rust；短match仍有原编码器价值 |
| PC完整双32位置AoS | 444有限等价及公共同字节，时间+0.02751% | 同容量不同布局没有有用时间优势，不迁移证明 |
| EF32辅助第四字节键 | 原位置12711更长match/18740覆盖B；实际少11215token却多3485压缩B，大小+0.035561pp | 最长优先没有定价远距离，关闭该选择版本 |
| EF32辅助键gain / seven | 实际程序原encoder未计时重放：gain仍多1614B，seven省217B | 仅保留217B小替代，时间/gate未测，不能单独跨当前边界 |
| PC matched lazy0省next-word | 444有限等价、同公共输出、提取通过；总时间+1.29896% | 关闭；逻辑调用数不等于实际机器节省，具体变慢原因未确认 |
| PC过期非零hint归零 | 原observer370万ahead中69万过期非零；444有限等价、公共同字节、提取通过；时间+1.19481% | 关闭，未投入gate |
| PC失败主候选一步恢复 | 原位置有约2.8万一步恢复；gain实际大小-0.007856pp，但总时间+0.22870%，540 decode/提取通过 | 仍被#539支配，不投入完整gate |
| 新公开#542 PC U16迁移 | 完整共享callee隔离后原生/540 decode/提取通过；对542 -0.23175%，只额外省3B | 同族点0.4435568/36.215031仍被#546支配，关闭当前源，未gate |
| U16与gain恢复组合 | 540 decode、提取、两runner六块；全数对abs15 +0.17521%，大小-0.007856pp；新四块对public514 +0.09494%、对shadow +0.26563% | 冻结的五项分配条件全部未满足，组合总体又被#539支配；停止full gate，proof1保持未编译草稿 |
| 原engine四方法共测诊断 | 四块candidate相对parent均值-0.24681%，同ELF shadow均值+0.00579%；块间波动仍大，标准单块为+0.81591% | 协议不同，不能合入标准237进程、性能确认或正式admission |

Cpp覆盖、token数量、匹配长度、逻辑调用数和静态指令数均只作诊断；实际原编码器和配对总时间才能决定本轮性能取舍。多个弱信号不能相加成组合收益。

[成本拆分](../../evidence/round13/cost-decomposition.json)按每文件11次正式总时间的实际中位数rep重算parse+encode，总轴逐行严格相等。#514父版平均文件parser占约18.8%；balance-n异常第四块轴下降约83.9%来自encoder项，且包含分别测量incumbent的波动。拆分仅是描述性计时记账，不能推断编码器因果提速、替换标准指标或把同字节的总时间波动提升为算法收益。

abs15后来作为control仍有真实标准测量，汇总器按精确Rust声明先建索引，避免角色改变或回执顺序丢掉这六块。[全角色诊断](../../evidence/round13/abs15-all-roles-decision.json)保留六环境17块的原中心；若仅作影响诊断，将已知异常块替换为同run另外三块均值，中心会从-0.11997%变为+0.02886%。这个反事实不是删块后的正式成绩，原始第四块仍保留。

最后复测的分配口径在结果artifact创建之前已经提交，见 [预先冻结政策](../../evidence/round13/confirm-aa-decision-policy.json)与 [STOP决策](../../evidence/round13/confirm-aa-decision.json)。三个块胜parent/shadow、均值胜两者、当前同族几何前沿五项均失败；发现两块没有进入这份判断。

[重复采样统计诊断](../../evidence/round13/repetition-uncertainty-diagnostic.json)重用固定官方源码的纯统计函数，对最后四块分别做2000次重复采样，不抽文件、不合并块。abs15对parent只有第四块的局部下界为正；该块的同ELF shadow也得到了统计函数的`passed`标签。四块abs15对shadow均为`inconclusive`。官方函数本身明确不覆盖host/corpus drift，因而这些标签不能推出算法收益。本地适配只校验单个公开stage1 envelope，使用本地证据派生的观测ID；没有执行SQL聚合、官方#539 reference比较、held-out或线上admission。原driver的四块parent/shadow ELF SHA相同，见 [库身份](../../evidence/round13/latest-shadow-library-identities.json)。

## 原包、执行故障和修复

用户ZIP原包76文件、75条SHA清单逐字核对；原始材料与完整导入回执留本地忽略目录。其HANDOFF仅是研究线索，不改变权限。生成候选保留公开父版和作者归属，原contract/encoder/gate/pins未修改。

Windows原生成器有strict-resolve/TemporaryDirectory环境错误（原七项fixture本地5通过/2环境错误），未改原包或冒充云端重放。实际Rust使用仓库自有有限检查。回执下载的Windows共享占用失败通过原实际延时重试与最小持有文件回归验证，有限重试保持字节、拒绝覆盖；原锁持有者仍未知。

#542迁移暴露了PIM对原PC链接/深探测函数的共享U32调用；两份错误派生源和E0308原日志保留。完整隔离版保留原U32函数及证明供PIM，PC使用独立U16函数。原生编码校准配置漏项也独立记录，未执行程序的KeyError没有伪造性能。

共测诊断前两次因来源目录和读取函数接口错误失败，均保留；最终修复逐一核对固定driver九个入口，原engine/encoder/候选不变。37866735582自然成功，四份原始诊断按每文件11次median重算，见 [precision-x-decision.json](../../evidence/round13/precision-x-decision.json)。同进程4方法（含incumbent）、每轮轮换，协议区别于标准一候选隔离，不能替代admission或奖励。

## 当前官方状态与剩余工作

最新完整官方读取见 [official-final-2](../../evidence/round13/official-final-2/receipt.json)：快照29257，UTC02:43:19计算，557提交/529leaderboard行，weights同快照，官方freshness为unknown。截止前先读到29250，随后检测到版本推进并补齐新全页；之前原始快照全部保留。速度端仍#539，新#555进入中段，不改变本轮快端判断；#546仍支配#542。最终两轴已按29257重算，几何权重和同族校准均是条件模型，不能当收入或private保证。

当前注册在finalized区块9242455只读核验通过，UID46归属/key一致，见 [脱敏回执](../../evidence/round13/registration-final-sanitized.json)。旧9241236回执原字节保留在本地忽略目录，完整账户信息未发布。注册不证明还有未消费的accepted-gate提交额度。没有正式上传、钱包签名、燃注册、转账或提款；本轮没有已确认的新正式成绩或新奖励证据。

额度最后读取仍剩43%，10月23日到期卡未使用，见 [脱敏额度记录](../../evidence/round13/quota-final-read.json)；没有触发剩余1%条件。身份/幂等记录不进Git或CI，账号共享额度变化不当作本轮独占成本。

最后确认37869790385已自然完成并收齐；四镜像块的anchor/candidate/direct-parent/shadow平均位置均3.5。proof1仅添加新helper局部合约，Rust逐字不变，因确认失败而保持Lean未编译，不是第三个验证通过的pair。01:22UTC后未扩新算法探索；27作业终态原字节审计、回执顺序反向重算、源版本与索引检查通过。02:52UTC预算到期结束本轮，保留未闭合目标，不将阶段完成或两个gate标为争榜成功。

下一轮的可复用起点是两个已验证的U16证明pair、收益明确但时间不够好的gain恢复、仅省217B且未测时间/证明的EF32 seven。首先需要新的总时间或真实编码字节机会，再分配实现和完整gate预算；相同布局、调用计数或最长匹配代理不足以重启已经关闭的精确版本。UTC02:06对#539官方公开source端点的无认证GET返回403 `SOURCE_WITHHELD`，见 [原始响应与哈希](../../evidence/round13/source539-final/receipt.json)；没有绕过权限。当前family模型没有替代其正式admission比较。查验不能把预算结束、两个gate通过或实验数量替代上榜拿奖励。
