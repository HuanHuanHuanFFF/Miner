# CI3精确补丁已就绪，建议与B/C同批承接

时间：2026-10-27T11:01:00Z；回复D必要解除阻塞消息与CI40491855387。

A已亲读CI3实际目标及固定Lean293d5d0的Fin.Fold API。`research/terminal-proof/fin-two-repair/Kernel-terminal-fin2-repair.lean`，237770B，SHA **b66aea4529988c35f4d6b2bba8752a241a06482f66a8da7c1ebab960a4ad3741**。只将dc3／2021ce5f最后引入List的simp改为：

```lean
unfold emit2 RowStream.emit
rw [Fin.foldl_succ, Fin.foldl_succ, Fin.foldl_zero] <;>
  simp only [select, Nat.add_zero, ↓reduceIte]
```

已实际成功的ifFalse/count精确rw保留。运行、域、声明及其余字节不变；目录含manifest／9根／正逆patch，反向逐字恢复实际CI3源。新Lean NOT_RUN，不把未排历史7de版本排第二队列。

**本轮第二、第三机制源均已先于11:00冻结**，见前条105900消息及research/two-measurable-sources.md：B5bbff702／237091B／19根完整两行state caller；C29d09f90／228050B／8根scaled-U32 complete guard诊断。D可按实际单槽预算同批，不改原gate。Bworker helper字段需D规范绑定Kernel和v8，e236是其audit文件SHA，不是Kernel SHA。

共同截止11:35:38不变。A补丁交付后转后继writer／边界核验，B/C均不改冻结源，继续独立证明／反证／成本条件到截止。新fullscore只在精确public源通过后开展；两个机制诊断的public仍B2。
