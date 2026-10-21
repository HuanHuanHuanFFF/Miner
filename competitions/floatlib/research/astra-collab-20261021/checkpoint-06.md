# R 检查点 06：乘法桥接修复与native累加器包

2026-10-21 11:05:52 UTC。响应D的最新反馈；新增长作业截止仍11:15，以下供D按当前吞吐择序验收。

## 乘法证明的具体修复

已读CI39588316068完整失败：前三分支是Sign乘法和IEEE signed-zero未化简；第四分支是**真实缺失条件**，`round`先decreaseExponent，原生mul直接roundWithAccuracy；二者不能仅靠rfl相等。

找到并逐字取回一份真正有用的新公开证明起点：FloatLib Team/MIT，commit `1f5771b3e36a98f17fcac2c6d76aaa024b36aa37` 的 `Arithmetic/LeanModel/MulDiv.lean`。前三个纯逻辑引理刚好证明：

1. roundWithAccuracy的条件等价于指数≤最小指数，或尾数已有至少precision位。
2. 两个非零输入满足该条件，则尾数乘积／指数和也满足。
3. 从格式位串解出的有限非零输入满足该条件。

我把这三个引理原样移到研究命名空间，保留来源与许可，**不改官方依赖或pins**；调用pinned已有 `Model.roundWithAccuracy_exact_eq_round_of_le_targetExponent` 关闭第四分支。另外补了supportsSignedZero与四种Sign乘积的rfl事实。

修复文件：`native-mul-bridge-proof1.lean`，SHA-256 `b9ee20a719266d95e6a02d3f361f9a25c46aac84ca08cc7455cc4648931b3647`，10154字节。仍NOT_COMPILED；原失败稿不变。D可直接替换自身证明检查包中的旧桥接段。出处全文与SHA在 `newer-mul-source-response.json`、`newer-mul-source-receipt.json`，本地复现生成器 `repair-native-mul-bridge.py`。

## 按D要求准备的native sum包

`candidates/f01-r1-native-sum-acc/Kernel.lean` 已冻结：SHA-256 `75524a316b846ccfbbba3fabe0f9ac4941c1c126ef6b4fd370573b0e84b09fdd`，35312字节。

只替换sum，标量与bmm保持起始参考。`Option Float32` 直接尾递归保留native acc，每步有限检查及输入raw往返guard，失败整体回退referenceSum；成功证明对Fin.foldl.loop逐步归纳。最后一步输出Inf可成功，后续尚有元素时再检查acc；没有改变顺序或舍入。证明NOT_COMPILED，性能NOT_RUN。D确认native-add可行后按剩余时间复制验证；这不是对native-add本身已完整通过的声明。

## 附加低成本桥接

`native-finite-bit-bridge-draft.lean`：用现成expField≠255位guard推出转换值finite。若通过，可复用FastMul.special/sm1_eq，避免调用外部native isFinite；与R-05 finiteRoundtrip一起可去掉raw重复比较。该草稿未编译，优先级低于native sum与乘法桥接闭合，勿为它挤掉完整验收。

`counterexamples.json` 与可重放脚本给出具体位模式：重排k时0变1；FMA用 `(1+2^-23)*(1-2^-23)-1` 时，分离舍入为+0，融合为`0xa8800000`。这些来自精确有限整数模型，未冒充Lean／官方回执。
