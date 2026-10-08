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

nearer-b首轮abs15对514仅-0.05855%，Pad64对新abs15 +0.10821%（变慢）；未跨当前同族投影边界。相同源码public514-shadow移动约3%，远超欲跨的约0.08%间隔，不能取shadow对照夸大收益。安排独立runner四块确认，plainabs15完整gate，并只在未计时observer副本计数max258的可消除追链工作。cap-prune隔离源码已准备，未与布局先行组合。

confirm-c未计时观察：PC1014141首轮请求，初始cap258仅1633次(0.161%)，228358第二跳中g达到258仅483次。cap-prune当前收益空间偏小，暂停完整性能投入，只有444有限同token原生检验作为可复用成果。改投#514新增EF32一槽键的碰撞机会，宽15/16-bit影子表沿原p位置观察、不选择新match；先取得新增候选/字节机会，非新增压缩收益。

ef32-d37844475132自然成功：cap-prune444实际token/decode等价无差异，但不测性能／gate。EF32只影响weights-f32.bin(350000B)，35065探测、31998match覆盖96216B；宽15/16-bit均未找回任何match/byte。暂停这两张扩表，不投入测量。新缺口变为极短匹配编码值：Lits3按原位置原步进把3-byte match写为literal；min4另改拒绝后miss步进作密度对照。先用正式原encoder做两轴，不把96216覆盖字节当成可节省压缩字节。Lits3证明原稿明确未适配，只有性能有机会才新冻结证明pair。

confirm-c四块screen：abs15对514 -0.190589%，对public514-shadow +0.001071%；identical shadow自身对514 -0.191238%。中心点可能进入几何前沿，但同源码也相同移动，因此不提升性能／正式提交结论。Pad64对abs15 +0.115400%，与discovery +0.108207%同向，暂停这个新父版布局。完整gate已启动，按授权自然运行到结果。ef32-short-e实际原编码器筛选同时进行。

confirm-c最终CI成功、#514abs15精确pair原始gate接受(511.8秒)，白名单三公理、fresh提取、原Obligation、公共roundtrip全部通过；独立完整／research synthetic目录本次实际运行也通过。48公共配对进程两runner整体复算保留；中心投影入前沿只是条件计算，原source同字节shadow浮动与收益几乎相同，仍不提升为性能／正式奖励成果。

ef32-short-e37845275650自然成功且两个540decode通过，唯一token变化weights-f32。原284138B；Lits3输出288073(+3935B)，总体大小+0.040153pp／总时间+1.257595%；min4输出287858(+3720B)，+0.037959pp／+0.872356%。原三字节match虽短仍有实际编码价值，反驳只根据长度/覆盖判断收益。关闭两份Rust，不投入证明迁移，避免继续盲扫minlen。下一次先看实际符号／距离收益或保留短匹配减少探测工作。

price-f37848061003原encoder轻量重放自然成功：28父版token/output哈希逐字同公共原回执，所有34输出zlib独立decode。31860个len3里31814按原block实际码长更便宜，只有39更贵(局部损失56bit)。选择性price0/2实际+15/+1B，距离类d32/d128/d512/d2048分别+5505/+3557/+2532/+507B。关闭这个父版的短token价格改写，不由局部bits保证最后bytes。新机制为补充第四字节key(保留3-byte后备)的真实更长match机会；另对PC仅dp1/lazy0行测试完整双32位置AoS，同容量，区别于旧HN SoA bucket2和Chat pair16。先native有限eq与observer，再决定测量／证明投入。

pair-g-native37849678652自然成功：pair64全32bit位置AoS444 token/decode同public514。Key4 observer保持父输出：35065探测找到12711更长match、新增18740覆盖B，>=7有332，>=11零；不把覆盖B当压缩B。冻结独立structure-h两个候选，原encoder配对筛选；aux4保留原head3、严格更长才选head4、tie偏原head3；额外64直接EF32浮点模式边界decode用例补足原泛型样本。两份原证明均未适配新函数，不在首轮申请完整gate。

structure-h37850501371自然成功，16公共配对进程、pair64444有限等价／公共同字节，aux4540 Root decode+64直接EF32浮点边界decode均过。pair64对parent+0.027512%(基本持平，无上榜优势)；aux4对parent -0.071930%但大小+0.035561pp，f32从284138到287623(+3485B)，tokens285782→274567(-11215)。暂停两份原Rust完整证明投入。辅助key仍有新增信息，但最长优先过多选了远距离短收益；仅改变选择predicate的gain/7按原encoder轻量筛选，不盲延长full CI。
当前finalized区块9241236只读注册核验：UID46仍注册且归属/key一致，原历史链hash一致；完整账户回执留本地忽略目录，未签名/转账/提交。官方checkpoint2 snapshot29211(22:04:39UTC)freshness=stale保留，新增547提交但速度端#539边界未变。

choice-i-native37853349223四实际程序原encoder自然成功，28父output/token哈希一致且全zlibdecode：gain仍+1614B；seven省217B，公共大小36.2009312%仅-0.0022143pp，不能单独跨#539大小边界(约需1369B)。保留极小大小替代但不投入配对／证明；不把无计时诊断当两轴。转向新的PClazy0未用ahead word：匹配支路保留插入key、复用当前真实word，miss/lazy支路仍旧完整ahead；原pc_run1c纯probe提前，实际token等价须验证。1014141匹配机会明显大于稀少cap退出，但分支/流水重叠损失UNKNOWN，单受控版本ahead-j，两块配对+提取、不先申请昂贵完整gate。

ahead-j37855505557自然成功，14公共配对、444有限token/decode相同和公共同字节、原提取接受。总时间+1.298957%，关闭这份Rust不投入完整gate；逻辑未用Word次数不等于机器节省，流水/缓存或编译消除解释UNKNOWN。下一步expired-k只计数原pc_ahead_m里过期非零候选，区别于仍有效但当下不用的预取；零sentinel已热，不把它们当冷读取空间。依原父byte/token observer约束，不改变任何输出。
