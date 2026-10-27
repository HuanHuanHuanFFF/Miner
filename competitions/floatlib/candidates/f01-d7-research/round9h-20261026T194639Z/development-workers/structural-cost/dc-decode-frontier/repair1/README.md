# CI13 rawpair：仅修row_prefix偏应用callback的等式桥

**首因已核：不是public DC规格换错、namespace顺序错误或runtime不等价；失败的是新R19DCRawPair.row_prefix最后一步没有把偏应用group函数值接到groupFrom。** 121份原件、14534863B逐项SHA/size/集合均核对。原full-build-output SHA1044bcd6…，只出现一个Submission错误位置5993:2；完整goal原样保存在original-error.txt。

原h的类型是`Prefix point (r*p+p) (Fin.foldl (groups p) (group batch m n p A B r) out)`；目标是相同Prefix/相同长度，callback为`groupFrom n (r*n) (r/m*n*p) p A.toArray B.toArray`。两边只差函数值写法。group的定义在5917–5923，以out/g两个参数包住同一个groupFrom；row在5969开始把基地址放在Fin.foldl外一次计算。旧末行`simpa only [row, group, ...] using h`留下了未满应用的`group … r`，没有靠group的满应用定义等式完成重写。日志的实际残留goal直接证明了这一点。

命名边界：旧DirectContinuous在5840结束；新R19DCRawPair在5844开始，group/group_prefix/row/row_prefix都在这个新namespace内；旧public dispatch在新namespace结束之后。不是先前lemma指向被改写的旧函数；当前group_prefix与row确实是同一套新定义。应在函数值层给等式桥，不能削弱Prefix、改shape guard或换回带重复行地址计算的旧runtime。

唯一修复，在5993前建立：

```lean
  have hgroup : group batch m n p A B r =
      groupFrom n (r.val * n) (r.val / m * n * p) p A.toArray B.toArray := by
    funext acc g
    rfl
  rw [hgroup] at h
  simpa only [row, hlast, Nat.add_mul, Nat.one_mul] using h
```

`funext acc g; rfl`将两端应用到完全相同的acc/g后按group定义归约，明确提供整个fold callback的函数等式。随后transport的是原有fold invariant；Prefix、长度、output、所有量词及终端规格完全不变，没有新数学假设。

完整新稿`Kernel-dc-rawpair-repair1.draft.lean`，**235456B，SHA6a0c18c52d736a1b8856877d6056372e13f70b095e36e34bd05203bcb7a5d1c0**。父8134696d/235299B；净增157B。只改变row_prefix证明正文，所有runtime def、domain、四个public specs正文逐字不变；全部声明名称/顺序不变；静态namespace解析确认14个原root仍精确存在，位置在root-index.json。local hgroup不新增顶层root。

forward.diff.txt、inverse.diff.txt和build_repair.py给出唯一修改与精确逆变换，逆变换逐字恢复8134696d。旧worker Kernel、旧候选、manifest及所有全局文件均未改。没有Git/CI/本地Lean/新增agent。

静态检查PASS；**新源码Lean编译、整模块回放、公理14root审计及actual selected C均NOT_RUN，计时NOT_RUN。** CI13的statement失败不是本次修复后的成功，也不把同run runtimeCost成功转移为本候选成功。下一步仅按原流程重新statement/回放/14root与actual MainFull→DC codegen；运行机制/domain和原D计划不变，不能直接计时或报收益。
