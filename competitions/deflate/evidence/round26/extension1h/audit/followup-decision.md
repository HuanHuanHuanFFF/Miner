# C2/C3停止与C4证明边界

UTC12:14检查点。只读主线程已收齐native及已冻结候选；未触发计时、gate或修改候选。C3完整草稿`C3-Parse-draft.lean`保留为UNCOMPILED，不代表gate通过。

## 已执行反馈改变选择

- C2 run38246156539：256144 same调用、269189实际word pairs；102854 tail拒绝只省104330word pairs，新增256144 tail checks。原失败几乎首word即结束，符合原停止条件。28公共token/output相同、444有限相等/双解码不改变这项成本结论。停止该精确实现配对计时。
- C3 run38247257224：75920 base fast calls中684≥64；99989word pairs只省5784，其中document5783、prose1。28token/output相同、444decode通过。OA总时间轴parser约1.55%，这是只削掉部分discovery；不能将5.8%操作减少乘整个parser占比后宣称速度。停止该精确版本原协议与完整gate。

原始C2/C3receipt位于各run的`quality-c2-native/diagnostics/r26-c-fold-tail/receipt.json`及`quality-c3-native/diagnostics/r26-c-deferred/receipt.json`，原字节保留。

## 新公开662的有限结论

`662-static-comparison.json`仅比较613/631/641/658。662有203函数，631同名172函数体逐字规范化一致；对641新增的活动pim、q4函数在631/658均有精确同体，改动主要是wrapper参数、pc_INS_MAX2→8、取消PC近距离特例、r109近距限制以及路由组合。bulk_parse与641规范化同体，p12_et全部内核已在641存在。不能因源码较小/提交较新推测性能或作者传承；本次没有查实际覆盖/质量。662原Lean523481B只余807B，不适合作低成本新增证明的默认父版。没有从它识别出值得本窗再写的新kernel。

## C3的尾界核验与限定范围

OA原cap=min(n-p-8,258)，N原cap=min(n-p,258)，两者不可统一。N fast_len在不足8字节尾部可能由ld8的越界返回0过报搜索长度，旧verified随后拒绝。用trusted-fullscan替代N可能安全但改变旧token，需另行原生核验；当前C3只改OA，N保持原版。

C3首query截64，活动lazy阈值32/64均已关闭；eval2/3保持原版，保留依赖真实l2的选源判断；O_A_BEXT=0，不额外移动起点。仅greedy发射l==64经新helper，由原trusted match_len按原cap补齐并直接发射。它没有在补齐后再次调用旧verified，因而不会复造整段扫描。草稿复用原match_len_spec和emit_match；未编译风险是新Slot提取的分支/SSA局部名与scalar cast目标，旧loop接口预计不改，真实gate仍是必要验收。

## 为什么不直接去掉emit的首8字节验证

当前eval_spec、scan/find/lazy多个规格只给True(totality)。查询中曾读到相等word不等于发射调用点已有该字节事实。移除首8B验证需将“len≥8则首8B Matches、来源和起点有效”通过eval/2/3→scan→find/lazy→run_greedy传播；还涉及lazy的b1起点回移、packed start/dist解包和环绕。另需trusted match_len_from8续扫契约与Matches.append。这比C3局部helper多一个证明层级，现窗没有直接编译/迁移证据，不建议直接rewrite。

## 当前第三圈C4预期边界

按主线程决定：首eval只保first8提示，find返回原scan结果取消整段lazy eval2/3，greedy在l==8以trusted match_len恢复完整原cap。它明确允许质量变化，不声称旧token等价；匹配发射仍由trusted比较保证安全，避开强化整个find链的证明。待真实Rust到手后只在audit准备相应完整父Lean草稿。native需报告真实大小损失、减少的实际discovery/lazy工作及分文件正负覆盖，再决定配对与gate；暂停C3不等于C4已成立。
