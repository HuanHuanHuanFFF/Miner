# R26 追加1h

北京时间2026-10-12 19:50:15–20:50:15。用户接受先建立稳定小份额。未启动正式操作。起点Git e7e0cdb7，工作区干净，单worktree。

双子线程：Astra机制候选；Sol独立路线审计；主线程测量、评分、CI。完整gate与冻结确认预留但不预先宣称可完成。

## 启动决策

官方29907（计算UTC11:44:41）664条；规则commit6bf303f14e6c7bccc63e9a557e4ac83e032fa9e8。原始字节与独立公式audit通过。R26旧13已计时主候选只有A19单块正0.780667%，另一块0，副本0；旧R24/R25确认也不能直接复用为稳定成绩。份额均条件估算。C1同距离fold shortcut被最长前缀/258上限可达性反例阻断，尚未生产。C2先检末byte必要条件后保留原u118_same：缺口是真实扫描覆盖；一份native固定语料/有限相等+完整扫描机会统计决定是否进入原协议。

初次git diff --check将保留CRLF的evidence判为尾空白；未修改原始字节，使用core.whitespace=cr-at-eol重新检查通过。PC精确区别：pc_fold本体无guard，实际pc_run的pc_fold_w外层已有tail word预过滤，不能漏掉wrapper。

## C2反馈与第二圈

run38246156539 native通过：444有限相等、28公共token/原encoder/双解码一致。256144原same调用，tail拒绝102854（40.15%），但只省104330 word pairs（每拒绝1.014）；加256144 byte-pair checks，触发既定thin/首word停止条件，不进行原协议。C1同距0。新公开662已按官方source端点取得，初审主要旧内核/路由参数，Lean仅807B余量，不因“新提交”就当新机制。

C3调查发现o_a_eval/n_eval长匹配扫描后o_a_emit_step又verified同span。候选提案延迟超过直接接受阈值的扩展至既有可信emit，必须先核对lazy/距离/cap/末尾溢读差异。少量质量变化仍按真实输出记录。当前尚无C3实现或性能证据。

## C3反馈与C4决策

C3 run38247257224成功，444decode无失败/无token变化、28encoder/token同658。75920次base fast调用，仅684长>=64；移除5784/99989 wordpairs，prose仅1。按薄覆盖预声明停止标准计时；完整Lean草稿507876B保留未编译，不冒称gate。此前准备器路径拼写错误在Git预检前发现，未派发额外CI，改为核对spec required_files后再提交。

C4为取消O_A整个lazy eval2/3阶段，并在emit可信fullscan一次；这改变算法及质量，区别C3同轨迹延迟长后缀，禁止扫cap。已有C3证据确认可取消全部base的99989wordpairs，仍需真实quality和lazy变化。先native判断端点，若有空间采用1个发现块保留最后两runner独立确认与完整gate时间；未满足条件就不勉强晋升。

## 确认预留开始 UTC12:20

C4 native38248104190全收齐成功。docs+7280B/prose+19619B，共+26899B；size35.387422883%对父35.308210978%。原fast99989wordpairs及eval2/3共312477调用代表被移除的旧阶段，不是新计时。最新29915下同族质量迁移35.682892319%；假设time快0.5%/1%，条件份额0.110974%/0.274586%。有小空间，启动一次原协议发现38248399555（1块/7配对）和原版完整gate38248430871，精确pair ae460229Rust /11426ab4Lean。screen派发UTC12:20:13在固定12:20:15新实验截止前；实际GitHub run created12:20:17单列。后续不再探索新算法，留给原作业、必要证明修复、独立确认及交付。周用量69%已用/31%剩，不兑重置。

## 首次原协议结果 UTC12:29:49

run38248399555 completed success，1runner/1块/7配对，当前29919。C4主primary/shadow均0%，copy primary0%/shadow0.0264192978%；主对父慢0.180460485%，副本慢0.038953283%，parent同binary差0.179165333%，candidate副本差-0.141252298%。未满足预声明确认条件；截至12:30未启动独立确认，不能延长窗。完整gate38248430871已启动继续收齐。

逐file同一总时间median rep恒等分解：主对父2个changed-token files贡献-0.114691pp，26个same-token files贡献+0.295152pp。不能归因后者全部噪声，也不能把局部更快算作修正分数；code layout、环境等未区分。机制净收益未定，稳定份额未建立。独立公式/同源码/逐文件原始值全部保留。
