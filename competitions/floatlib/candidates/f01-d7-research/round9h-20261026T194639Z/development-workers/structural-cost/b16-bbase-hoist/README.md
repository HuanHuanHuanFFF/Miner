# B16唯一B-base pure-let草稿，真实编译/成本未运行

完整稿`Kernel-bbase-hoist.draft.lean`：**255745B，SHAf49458b99475b1b7e4a368908c81590b7f357a06938f38d0df141ffa3df5dc5d**。精确父本bb058c75f59ca36b4952cffae0c943fd296de02cb3e83d164409736b0252c061/255724B，净增21B，距256000上限还255B。只有这一个交付版本；未修改父本/manifest/冻结组件。

唯一变化位于R19Column4Temporal.group：

```lean
  let v := runDot (b*m) n r PA (PB.get (ix b p bi g))
  let baseB := bi.val*n*p+4*g.val
  RowStream.emit (min 4 (p-4*g.val)) (fun j =>
    Packed10.finish n (r.val*n) (baseB+j.val) p A.toArray B.toArray
      (select v j.val)) out
```

采用D和独审指定的**dot后、emit前**作用域：不新增baseB Nat值跨runDot的存活期。原bi/n/p/g在dot两侧仍有既有用途，不宣称这次消除了它们跨dot的全部活跃期；dot返回后callback只需缓存B-base再加j。n/p仍由finish或count使用，g仍由count使用。新baseB需要保留到最多4个输出处理结束；大Nat引用/分配/释放及小Nat寄存器/栈压力全部计入，不预先记零。

baseA、loop/runDot表达式、原B tile读取、shape/underflow guard、旧B2 fallback、lane选择、finish及原NaN replay全部原文未动。没有新增helper/noinline、屏障、候选网格、准备数组或更改计时边界。group_prefix及其后所有proof文本逐字不变；前置所有proof也逐字不变。局部let zeta展开后恢复原group全文；无需新增simp或函数等式桥。

静态完成：完整文件正/逆patch、精确逆变换回bb05、局部pure-let逆变换、声明名称/顺序和20根索引均PASS；父文件和manifest前后字节未变。CI21全部130原件SHA/size/集合核对，并验证output-address-boundary既有C/ASM绑定；不重解读D22。`receipt.json`及`roots.json`记录精确20根，`forward.patch`/`inverse.patch`可复核变更，`build.py`可重建。

依据仅限已见CI21：普通小Nat路径`r*n`和`bi*n`已各每emit一次CSE，不能说三次乘法都逐lane重复。非零`bi*n`的乘p@0x182及加4g@0x1c6仍在lane loop、各NaN测试之前，finite toBits@0x376也经过它；bi*n=0有跳过乘法的原分支。本稿只尝试共享残余B-base，不碰r*n，也不将操作计数换算速度。

真实Lean编译、整模块/20根回放、actual C/ASM及速度全部**NOT_RUN**。旧CI21通过只绑定bb05，不能转移为新f494通过。普通let可能被LCNF/LLVM重新展开、下沉或保留，源码书写不是hoist已发生的证据。

若D在当前冻结批收齐后决定做一次C判别，应从真实MainFull→public bmm→B16 output/group→实际emit专化闭包追到本体：确认B-base确只每group计算一次，emit每lane不再重做乘p/加4g；r*n保持原有优化。同时核新capture/普通参数、Nat RC/free、跨emit/finish的GPR保存或spill、closure/临时对象及完整输出销毁，不能用独立helper或C中少表达式替代实际ASM。新增成本抵消或backend未保留时停止该具体稿，不能按源码let就声称收益。

在途D22及确认输入/结果未读取，冻结源未动；D22若达标应先确认原源，不由本稿抢换冻结版本。无Git/CI/本机Lean/新agent。
