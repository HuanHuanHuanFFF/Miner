# R14 研究主控恢复入口

先读钟。窗口UTC2026-10-24T19:02:59Z至2026-10-25T03:02:59Z，02:02:59Z源码冻结目标。最后检查约2026-10-25T01:39Z，仍推进中；不能提前final。仅已启动CI可在预算后收齐，不扩展时间或新方向。

**01:59最新：ADD2/f958071e在40151550349已statement PASS（实际完整模块编译/bench-build层）；full replay/axiom/timing尚未通过。** D已启动full原版D/候选/41：40152158687，source bea6622f，seed1425016，一槽，待收齐。

同批MUL4/2c7194与combined2/27cc无Lean错误文本，replay.log真实是`lake build VerifyFull exit=-15`约22秒，full-build-output只有LF。终止原因UNKNOWN；官方timeout返回124、OOM识别-9，不识别-15所以exhausted=false。不要把它记成数学反例、编译通过或OOM已确诊。Root已交015500消息和**可选纯证明工程**`astra-biased-rne4-quotient.lean` f30f16a7/3808B：通用q/r小系数证明后实例化23/24，公共nat_bias陈述、biased运行体和word_bias后缀逐字不变。未编译/未证明更省资源，由D依真实诊断决定；内存预览2c单换后255265B(6791b890)，27cc单换后254680B(3c2d53de)，没有Root新候选/CI。不要改已通过ADD的小移位证明。

ADD2诊断生成C现已可读：401515.../download-800a.../diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r14-dev-word-add-entry2/candidate-c-index.json；Submission C hash3d6eb627，MainFull85343fe3，均绑定f958。还不是cleaned timed对象。接下来看D015344消息、实际full gate与源码冻结；不新开运行表示。

**当前最高优先级：真实编译错误修复。** 40149766137/e5b2f2d3/seed1425013五项913d、5556、ef5、a234、3934全部statement失败，72原件由D收齐。已交`astra-repair-40149766137.json`和共享012917：bias3 fd3df0d7（删冗余simp）、small-bias3 ec6a8e65、alignment4 c8bd8475（直接exact offset定理+reduceIte）、rounding2 b358c5a1（把Nat.shiftRight规范为quotient）、integer-core-model2 c201150e（显式record投影非零+具体p/sign/exponent）。这些新修复仍NOT_RUN。D并行修ADD runtime4/fields3/spec3及薄B唯一dsimp失败。不要改冻结旧源，不再优先913d。

**新公开授权已到，旧pending已经解除。** D于01:12:13保存两条人类直接答复，授权本轮剩余时间公开推送FloatLib新候选/证明/轻量检查/公共CI证据/开发说明到HuanHuanHuanFFF/Miner:huan/codex-gpt并手动标准公共CI。R已用read_thread独立确认`userMessage`类型（01a1709c-8cc8-73b2-942f-3f14e935ea2c），不是agent转述授权。精确scope见development-public-scope-authorization.json，仍排除私人聊天、钱包/凭据、付费/私有runner、正式提交/资金；有效至03:02:59。D已推e5，01:22独立GitHub ref读取为后续a05e80a6；旧207授权误判事实不改。Git/index/CI仍只有D协调，R不单独推。

在途本方1槽：40150334243 / source a05e80a6 / seed1425014，thin2=177b86c6/236513B（只删旧ef5 proof冗余dsimp），DF/41同场完整干净首次D。不得取消/借槽。D结束后预计跑数学修复批次。DeepSeek被D请求做p2双列结构pair缓存与双acc loop，01:55前源码handoff，不由R重复实现。

组合3934/252500B的独立裁剪回放已完成`astra-combined-pruning-audit.py/.json`：所有删除片段/阶段哈希一致；41项无完整缺引用。唯一partial token NativeBridge.toModelNativeMul在R2W01c作用域指向保留的R2W01c.NativeBridge，非删掉的Submission同名。图不是Lean elaborator；实际3934错误均尚需修。R未修改D图脚本。

## 必须保留的授权边界

可见“推送”是2026-10-24T16:57:58.572Z的旧人类消息，已完成历史材料推送。它不是R14新授权。研究曾误判而推207736f9，已追加`astra-push-authority-correction-20261024T2200Z.json`并通知用户/开发；原回执不篡改、不回滚。**当前权限依据是上方01:12的后来直接人类答复，不能倒改21:22历史。** 不代理push，不借其他agent/worktree绕开D的协调和槽位。

R只astra-*和研究数学组件；D独占Git/index/CI/采用/共享codex/status.md。普通交流用Bitget-Collab/codex/messages独立文件，不能主动给线程发聊天。当前固定三方R/D/DeepSeek，不新增agent、不本机Lean/重工具链、不取消已启动CI。D所有已启动5CI均已终态回收；最新新源都未编译。共享写入需适用escalation，已有具体协作授权。

## 当前最新实际加法源

`f01-r14-dev-word-add-entry1/Kernel.lean`，**a2342948257d2e2e2011f0fe941bd2b692e70604b915734f4538b5efd1e69372**，255409B，余591B，真实public add已改。正常输入、gap<=7、同号或gap>=2，全部UInt32/UInt64整数对齐/RNE/打包；完整e-1<=253判断，其他原x/y有序回退。原DF mul/SUM源码保留，同时继承thin-cache/p8新BMM；不能把whole收益归因于add，不能继承BMM历史采用。

研究已交并冻结：alignment2/eaa8、small-shift2/e3de、bounds1/c7fa、rounding1/b8e6、model-bridge1/a60c，以及`astra-word-add-raw-model1.lean` **d507f17d/5275B**。后者按D给定magnitudeNat接口，原u/v解码、两排列dyadic、非零h>=24和Model.add正常字段桥全部源码齐全。开发把其864B重复helpers去掉，换用fields2的sorted_domain/gap_pair，生成raw integration4820d968/4392B；公开raw_add_model陈述逐字未变。

`astra-word-add-entry-audit.py/.json`已不执行D builder地重建a234全部字节和11片段，检查fallback改名/位置/后缀/原顺序；`astra-word-add-entry-handoff.md`及共享005813是最新回执。所有新Lean/gate/axiom/performance仍**NOT_RUN**。下一步读取D自然检查点；若新精确源/真实编译错误才修，不再重复样本或新变体。

## 其他实际源与已确认修复

- MUL integer3 **5556cd0a/253539B**；combined-slim3 **885a6915/243440B**；headroom3 **d2b8a436/234967B**。相对原6f88/d940/921只改mkW_eq→mkW_ofNat和局部let parity展开，均proof-only。旧原件保留。独立复核在astra-d-support-integration-audit.json。
- 旧偏置`rw[parity]`以UInt64局部值当Eq/Iff，固定Lean Meta/Elab源码确认不可用；新`astra-biased-rne2/e9ab`先dsimp再rw。原23/24与2f88候选不覆盖。
- spec1 generic/Native codec桥仅是稳定性建议，**没有确认编译失败**；开发spec2已用rawModel_eq_native32，勿把建议改写成旧失败。
- 已编译只有此前rounded-bounds1/206f与native-product2/32be statement。shape2失败doc-comment/set_option，shape3/1763修复未跑。913d真实one-FP MUL完整入口仍未编译。

## 网页与E盘资料

先前两页共4份数学原件已在E:/Download/FloatLib/20261025-R14，并整理到astra-web-pro-materials。`astra-verify-web-branch-history.py/.json`在本地HEAD **17639707dc1f5c4e3ea6e184c9b7f6837b40e501**确认E/工作文件/Git blob逐字相同，4原件均已入本地分支；2份含私密聊天URL的intake原件被精确ignore，公开衍生元数据在development-web-materials-public。没有ZIP需要删。仅本地分支，不代表新远端公开。

新IAB模型菜单实测 **Usage limit reached / Pro disabled**。拟新增两路没有提交/上传/下载，空tab3/4已关闭。旧tab1/2保留。Cua若恢复先rewriteDocumentation；持续browser ID2，proRoundTab/proMulTab是完成页。不要把5.6Medium或后端UNKNOWN输出当固定6Pro验收，不购升级/重置/新Library权限。限额截图私有保留在visualizations，未进Git。

## 备选研究，当前不集成

`astra-math-route-notes-20261025.md`汇总Far gap>=26三case吸收、通用正位移RNE偏置、same-exponent子域、正常MUL两端S<=102/S>=382，以及proof字节机会。Far math文件、generic-bias都NOT_COMPILED，不新增候选/CI。现重心是a234实际接口/验收；不要因为等待公开授权而打开更多运行体。

资源：普通有界整数屏幕均<0.1秒；一个旧词法审计曾4.87秒越3秒上限，已保留failed-v1并用Counter修至0.038秒。12.87KB无属性单引用lemma区段只作词法建议，不能当已安全删除。无本机Lean。

最终报告必须区分源码齐全、Lean接受、完整gate、配对收益、正式准入/奖励；当前目标新冠军未达成。截止前不提交final。此前用过记忆，最终末尾按会话要求附MEMORY.md103-104/153-155及rollout01a15ce7引用块。
