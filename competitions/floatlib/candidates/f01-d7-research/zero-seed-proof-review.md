# W10/W10b：+0 首项归一化原件审查

开始：2026-10-22 22:44:03 UTC。本次只读核对实际源、成功快照、编译记录、原始公理输出与 C；未运行 Lean、Linux 工具链、Git、CI 或上传，未生成候选，未重复 ZIP/13 包完整性扫描。D 另行负责完整包校验。逐项 LOCAL_ONLY 绝对路径、SHA 和选定输入记录保存在 zero-seed-proof-review.json。

**结论：保存的普通 Lean 编译、公理记录与精确源码相符，支持完整数学命题；不能升级为官方 gate 通过。W10b 确实新增运行实现，并证明它对全部 raw q 与 W10 旧 helper 等价；没有替它的 W10 依赖清除 gate 禁用文本。新 singleton 整合全部 NOT_RUN，收益 UNKNOWN。**

## 已核实的完整命题

一般 q 的命题明确保留前提：

    theorem R7W10b.add_posZero_of_not_snan (q : Competition.Binary32)
      (hq : Model.isSNaN (ExecFloat.Binary.toModel q) = false) :
      ExecFloat.add Competition.posZero q =
        R7W10b.normalizeProductSeedRaw q

W10 的 mul32_not_snan 展开真实 Model.Spec.mul：有限 dyadic 的 zero/rounder、选择 NaN、invalid、overflow 各分支均有具体 not-sNaN 证明；再由真实 operation/model refinement 导出：

    theorem R7W10.exec_mul_not_snan (x y : Competition.Binary32) :
      Model.isSNaN (ExecFloat.Binary.toModel (ExecFloat.mul x y)) = false

所以实际乘积版本没有额外输入前提，既是整个 carrier 等式，也有完整 UInt32 条件式：

    ExecFloat.add Competition.posZero (ExecFloat.mul x y) =
      R7W10b.normalizeProductSeedRaw (ExecFloat.mul x y)

    (ExecFloat.add Competition.posZero (ExecFloat.mul x y)).raw.1 =
      if (ExecFloat.mul x y).raw.1 == (0x80000000 : UInt32)
      then (0 : UInt32) else (ExecFloat.mul x y).raw.1

这对应分别舍入的 mul 后接 add，不是 FMA、实数恒等式或有限输入假设。一般 q 的证明先处理实际 native 非 NaN 的零/有限/Inf，再单独通过真实 Spec 处理保留 payload 的 quiet NaN；没有用 canonical Float32 相等覆盖原始 NaN word。

## 原件与原始退出状态

以下根目录及所有 R 原件均为 LOCAL_ONLY，本文不为它们生成 Git 链接：

    W10 = D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W10/original-extracted/R7-W10
    W10b = D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W10b/original-extracted/R7-W10b

| LOCAL_ONLY 原件（相对上面根目录） | SHA-256 |
|---|---|
| W10/R7W10.lean | c3f9965a7f4f55d13473e5364e95173a2a36b2c1e39bcb1f07f7dce2018432cc |
| W10b/Core.lean | 270c698a2dd2b96d21766d35339e090ca1455f71404145b3323cd1862301b67f |
| W10b/Proofs.lean | 90a6e0461690f8220d7ecc1710d52a267eb6239ec18d50de9f164952eff6bcbd |
| W10b/R7W10bIncrement.lean | 06cb8a1942f609d4ef0afdd85e2bfd373bc44fbf3d09dd6fc8d05f90a7bcf7d1 |
| W10/codegen/NormalizeCodegen.c | d322230093747dd4ad2cfe29f86d6ce2075804c116d51cf5f993c770b743a8ec |
| W10b/codegen/NormalizeRawCodegen.c | 79a769542c952f3e0d42ab8a188beeb6efcd6e58c50dea91ce2dbca160bfa5af |
| W10/logs/R7W10Diagnostics-attempt1.log | d46d547235aa30192e5968ef0f3728915d60de5ff3be121bc24c68af8c76a756 |
| W10b/logs/W10bAuditFull-attempt1.log | 857c0f1c80e5363cc4018e2c6e9bd3df70b25e85b1d539df90819a870682e801 |

直接读取对应 logs/*.json 与原始 *.log，核对结果：

- W10 R7W10-attempt1、R7W10Diagnostics-attempt1、R7W10Types-attempt1 的原退出码均为 0；成功源快照均存在且 SHA 与最终源相符。
- W10b Core-attempt1、Proofs-attempt2、ProofsAxioms-attempt2 的原退出码均为 0；Core/Proofs 的最终成功快照与上表完全一致。
- W10 原始公理输出中，218 个完整预期声明逐项匹配，其中 6 个明确不依赖任何公理；其余输出只含 propext、Classical.choice、Quot.sound。W10b 完整 audit 输出 26 个声明，也全部仅此三项。不是只信 audit.json 的 PASS。
- W10bFull、W10bWitnessFull、W10bAuditFull 的原退出码均为 0。它们的大型展开源/成功快照未打包；本次按原 prepare.py 的字节规则仅在内存中重建，得到原编译记录 SHA 78c85fc7…a148c65、b426b022…6ae2f6c、95be07ae…42fde1，逐字节哈希一致。该边界没有写成“本机重新编译通过”。
- W10 的 4 次失败与 W10b 的 2 次失败原记录保留。前者包括 Decidable、rfl、rewrite/命名问题；后者为诊断模块路径/同名模块冲突。最终成功源另有独立记录，没有覆盖失败。

固定上下文记录为 Lean v4.34.0 / commit293d5d0c0c3f3dded4688b3ccd6a33939ac5102b，FloatLib 0d91825727839f597fd06b22fdd038ea21480f0c，ContractTensor 原固定 978cc5b。恢复包内的真实 Spec/Dyadic、Model/Carrier、Dyadic/Rounding、ExecFloat/Carrier 与本工作区先前固定 0d918 原件逐字节相同。

原 session-verify.py 从 W01 的 lean-path.txt 加上 public、W10、W10b 工作目录构造 LEAN_PATH；当前恢复的 W01 没有该原始路径值文件，单次 attempt JSON 也未保存完整环境。因此本次核实了源码/版本/调用记录的一致性，没有独立重放全部 olean 加载环境，更没有官方 kernel replay。

## W10b 究竟改了什么

W10 运行体在 q 的原始字为 -0 时选择 Competition.posZero，否则直接返回整个 q。W10b 在 UInt32 上先选 u，再调用实际 ExecFloat.ofRaw：

    let u : UInt32 := if q.raw.1 == 0x80000000 then 0 else q.raw.1
    ExecFloat.ofRaw ⟨u, u.toNat_lt⟩

这是运行源码变更；normalizeProductSeedRaw_eq 对所有 q 证明两个实现相等，包括任意 qNaN/sNaN sign/payload。它不表示对任意 sNaN 可以替代真实 +0 加法。另一次 Proofs-attempt1 → attempt2 的差异则仅新增两个 NaN/sNaN 保留定理，没有修改 Core 或其运行体。

W10b 的 Core + Proofs 去掉 imports 后，逐字拼接等于最终 Increment。Core 的整个文件又逐字节等于实际 -c 输入和其成功快照，因此新 C 并非手写 uint32 surrogate。

## 官方入口仍有确定阻塞

按现有固定 4b7e838 官方 gate 的原始文本规则独立提取并检查：

- W10 主源和重建的 W10bFull 均保留第 2283 行 attribute [local instance] Classical.propDecidable。
- 第 1685、1689 行的 BitVec #_ 语法也命中 BANNED。
- 六行注释含单独的 import 一词，会被 gate 在注释中同样执行的 import 检查拒绝。
- Proofs.lean 自身的 import R7W10 / import Core 不能进入 ContractTensor-only 候选；Core 和去 imports 后的 Increment 本身没有这些 raw-policy 命中。

所以 W10b 的“增量源码检查通过”不等于其实际完整依赖包满足 gate。Classical.choice 属允许公理，而禁用 attribute 是另一个源码入口要求，两者不能混为一谈。

移植时不能只删 attribute：原 NativeZeroAudit-attempt1 的实际错误就是缺失 unpacked equality 的 Decidable。可探索给证明辅助条件式显式 Decidable 参数，并在证明体局部使用 classical；#_ 可改为实际宽度的显式 BitVec 写法，相关注释另行改写。这些都属于未运行的新证明适配，必须以实际目标验证。

此外，dab + 完整 W10 + W10bIncrement 的字节数之和已是 263991，超过 256000；这还没有计拼接换行。本次只算大小，没有生成该候选。应提取必要证明依赖，不整包复制。

## 对 dab singleton 的最小接入

现有 [singleton-proof1](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-singleton-proof1/Kernel.lean) 绑定 SHA dab15a44f753c1e8d4654d15ffc54eaa770702eeb42cf0cc601c91809418b21a。最小运行改动是保持原 bmmDecodeC 和 A/B getD 地址，计算同一个 Submission.mul 一次，用 raw normalizer 取代外层 Submission.add posZero。n=1 守卫、n≠1 路径、空输出和所有 batch/m/p 都保持原结构。

该候选已有 Submission.add_eq / mul_eq（2288/2292）。在原件证明被正确移植之后，所需桥的签名与预期证明为：

    -- 新整合 NOT_RUN
    theorem normalize_mul_seed_eq_add (a b : Competition.Binary32) :
        R7W10b.normalizeProductSeedRaw (Submission.mul a b) =
          Submission.add Competition.posZero (Submission.mul a b) := by
      simpa only [Submission.add_eq, Submission.mul_eq] using
        (R7W10b.add_posZero_mul a b).symm

然后保留 singletonCore_eq_reference 原有 Vector.ofFn 外延及 Fin.foldl_succ / foldl_zero / val_zero 化简，使用该桥关闭新的逐元素目标；不需要重写 BMM 的数学规格。

但这不是“只粘 427-byte Core 就结束”。当前 dab 没有 W05 的 add_toFloat32、native_acc_roundtrip、toFloat32_isNaN、quietNaN32_eq_self、roundDyadic32_not_snan 等同名支持；应提取所需 W01/W05/W10 证明或用当前等价桥改接命名空间，不能凭空 import R7W10。必要支持、新 Submission 桥、Core 放置顺序和新逐元素证明，全部尚未在 dab 中编译。

## 语义与代码生成证据的上限

- -0 乘积，包括负下溢和 +0×负数，必须变成 +0；普通非零、最小非零 subnormal、±Inf 均保持完整 word。
- 0×Inf 的 invalid quiet NaN、原始 NaN 优先级及 sign/payload 由原实际 mul 处理；normalizer 不再通过 Float32 转换。
- 任意 sNaN q 的替代是错误的。原件有普通 kernel 见证：q=0xff800011 时 normalizer 保持 0xff800011，真实 +0 加法给 0xffc00011。乘积版本安全依赖完整 mul_not_snan 证明，不能删除此环。

实际独立 helper C 的对照是确定的：W10 的 -0 分支调用 lean_uint32_once；W10b 的 unboxed 入口只有 UInt32 等值比较和返回原 word/字面量 0，没有 once 路径。旧 codegen 输入的运行定义与完整证明源中的定义相同，新 codegen 输入整个文件与已证明 Core 相同，两个 C SHA 都匹配原 -c 成功记录。

该证据只到独立 helper 的真实生成 C。boxed wrapper、模块初始化仍存在；没有汇编、链接执行、硬件计时、singleton 集成 C 或完整 suite 性能结果。未来必须核实 product 只计算一次、Vector.ofFn 使用哪种入口、是否内联及整包实际对象。不能从这个小 C 函数推导整包零分配或速度提升。

第一判别步骤是：用必要依赖生成一份可被 unchanged policy 接受的最小证明移植，再实际编译完整 product/carrier 桥；随后才验证新 singleton 的原版完整 gate 与同口径配对性能。本文不据外部报告 PASS 晋升任何候选。
