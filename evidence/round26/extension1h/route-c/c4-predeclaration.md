# C4：O_A 直接贪婪与一次可信扩展

2026-10-12 UTC 12:15。C2和C3均因实际可取消工作薄而停止，不投入计时；C4不叠加它们。C3保存lazy阶段只取消5,784字比较，新增证据促使此次选择完整的质量/速度交换，而非扫描64阈值。

## 单一实际机制

只在原O_A路径：base eval用已有first8字比较给出最多8-byte的候选提示，不再调用fast_len；`o_a_find`只返回原scan结果，删除整个lazy eval2/3选择阶段；greedy调用局部可信`c4_emit_step`，在原窗口/range guard后通过已有`o_a_match_len`按`min(258,n-pos-8)`一次验证并扩展完整match，再发出真实长度。源hint长度不获验证时原literal fallback。共享原emitter、N70、其他kernel、路由、hash和记录政策均未改。跳过lookahead导致未来匹配位置、插入轨迹和输出改变，是本次算法取舍的一部分，不能宣称同token。

这不同于C3：当时为保原lazy决策必须先查到64，而本次直接移除lookahead阶段；不同于跨find携带Matches，后者要加强现有全为True的eval/scan/find后置条件，本窗没有足够证明余量。这里仍由可信matcher确认每个输出字节，证明集中在小emitter，无新增loop。

## 旧路线核对

已检索现有candidate manifests、builder及round报告，未找到同O_A的“整lazy取消+发现first8+可信发射全扩展”直接实验。R3的O_A dense反而使用LZT258和LZN4；R16 lazy8/minlazy针对PC；R15 #573删除SF refinements，是整段质量/速度交换先例，不是此内核的直接证据。public662继续对prose使用O_A LZT32，对docs换PC，所以也不等同。本次不由不存在搜索命中推导全历史绝无先例。

## 最小验证与分配

一份真实native：444 decode（保留token变化）、原public514/658和C4的28文件原encoder/round trip。原658 observer记录原basefast调用/wordpair，eval2/eval3/lazy_more调用及lazyfast2/3wordpair，保持原token并绑定本批encoder哈希。C3已确认原basefast 75,920调用、99,989wordpair；此次名义上移除所有这些发现扩展，而非只删除罕见长尾。原轨迹操作量不等于新版本成本：新插入/匹配/encoder成本都必须由真实输出及配对计时反映。

若输出明显回退且按最新同一榜单快照、合理的局部时间场景仍无值得确认的前沿空间，暂停。旧A19一runner的O_A parser权重约总轴1.55%只作局部场景，不能作全程序上界，因为encoder随token变化；保持“极端场景不利”和“已证明不可能”的区别。若端点有空间且真实取消足量工作，截止前只给一次原协议screen；随后是否gate/独立确认由实际读数和剩余时间决定，不后移窗口。

## 证明代价

可信扩展返回`full<=cap ∧ Matches`；full>=hint且hint>=3供minlen，cap<=258和原distance guard供token有效范围。用现有`EO.EA.match_len_spec`及`emit_match`证明新增emitter，fallback复用原`emit_step_spec/emit_lits_spec`。改后的find仍只需总性，不需加强匹配事实；greedy loop换local-step emitter规格。当前候选Lean为父证明骨架，未编译、未完整gate；主线程另准备精确提取适配，不把native当证明。
