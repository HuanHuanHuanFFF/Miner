# C3：把已直接接受的长匹配扩展留给可信发射

2026-10-12 UTC 12:08。父版 public658；独立于已暂停的 C2，二者不组合。只有一份 `r26-c-658-deferred-extension`，没有参数扫描。

## 真实工作与变化

原 `o_a_eval` 的 `o_a_fast_len` 先把首来源匹配扩到最多 258；之后 `o_a_emit_step → o_a_verified → o_a_match_len` 对整个选中 span 重扫。与原 PC 的 VERIFY=0 发射不同，O_A 实际执行验证。新版本只把 **base** eval 的发现长度限到 64，这是现有两个 O_A 活动 lazy 阈值 64/32 的最大值。小于 64 的结果不变；达到 64 的原匹配本来也不会进入 lazy，且 O_A_BEXT=0。不改 eval2/3、N70、route 或共享原 emitter。

greedy 调用新增局部 `c3_emit_step`。仅在 l==64、源位置/距离/长度检查通过时，调用已有可信 `o_a_match_len`，上限严格保留原 O_A 的 `min(258,n-pos-8)`。检查得到 full>=64 后发出真实 full 长度；不足 64 走 literal fallback；其他情况调用原 `o_a_emit_step`。每个发出字节仍经可信 matcher 验证，未直接相信 untrusted 搜索提示。输入重叠允许，依据原 match_len 规格处理。

N70 的 cap 是 n-pos，与 O_A 不同，且存在零 head / tail 提示由原 verifier 拒绝的情形，因此本份完全不碰 N70。按 A19 第一原块逐文件 total 中位 rep 的 parser/incumbent 权重，docs/prose 两文件 parser 合计约总轴 1.55%；这是一个 runner 的阶段权重，不是预期速度或可支付份额。它不足以支持本轮预期5%/10%，但比N70单文件约0.248%的可动 parser范围大。最终选择取决于真实省扫和完整计时。

## 新旧差别与风险

不同于C2/A18必要过滤：这里取消已被接受长匹配的重复后缀扫描，而不是替一次很快的失败加读。不同于R20取消fold：没有删除质量阶段。不同于R24/19匹配缓存：无表、缓存生命周期或每位置维护。没有从“已算过”推导免费；新局部 emitter 条件、调用布局和原可信扫描仍付实际成本。

本版可能同 token，但不假定全输入等价。原所有精确上界、距离和tail guard保留；新版跨泛型非活动配置的行为不以当前路由证明。native记录真实token/压缩字节变化、全部失败和正负输入；全验证不只检查大小。

## 最小实验和停止

一份 native：444有限 decode（记录 token变化）、原 public514/658/候选的28文件原encoder/round trip。原658 observer只把base fast_len换为返回原值的影子，比较原完整cap和cap64所执行的真实source wordpair数，核对 capped_len=min(full,64)、原输出逐token不变，并绑定本批 encoder输入/token SHA。按文件保留base调用、原/截断wordpair、移除wordpair、长度>=64次数和span。

如果真实长span覆盖很薄，或新增判断与取消工作相近，就停止，不扫cap。若少量变化造成明显质量回退也停止。只有明显省掉一段工作且真实端点可用，才分配一次原协议主/副本/父/影子计时；原协议结果与冻结后的独立runner/完整gate仍是下一层。

## 证明成本

`EO.EA.match_len_spec`已经返回`l<=cap ∧ Matches`。新局部 emitter 可以按既有 `emit_step_spec` 的 `emit_match` 分支证明：range guard供合法距离/上界，full>=64供minlen，match_len供字节匹配；fallback复用原 emitter/literal规格。greedy loop仅替换对应local-step规格，无新循环或search正确性义务。必须实际提取后再适配自动变量；当前父Lean复制只是草稿骨架，完整gate NOT_RUN。余量19,145 bytes，新增短引理能否编译仍UNKNOWN。
