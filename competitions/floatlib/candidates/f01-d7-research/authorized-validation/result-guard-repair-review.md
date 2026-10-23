# d027 result-guard-both 单点证明修复

本次仅创建proof2的Kernel/manifest/README及本报告、JSON；未修改原d027、任何运行时定义、其他证明、属性、许可或官方文件，未运行Lean、Git、push、CI或上传。

[原始814回执](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39903681347/download-104b25d48a2944cda69f8d957ab75ddb/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-d7-result-guard-both/full-build-output.txt) 属run39903681347，SHA `91ab35bb29157b3b1ae80d8a45330f3ede698ad14b3d845d972bec6af51d7b4a`，12284B。原源SHA `d0279229968ba66440efbfcf55abb64a29f313df68ba22d72df70a28aa0a855c`，156454B。日志仅有一条带源位置的error：2580:8，`rw` 寻找 `ofFloat32 (toFloat32 x + toFloat32 y)`，而目标仍显示 `ofFloat32 (Float32.ofBits ↑rawX + Float32.ofBits ↑rawY)`。

原2578行的 `change` 只作用于假设hn。修复是在原2580行重写前，对目标补同样的表示规范化：

```lean
    change ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y) = _
```

已有 `R7Native.ofFloat32Add`、两个 `NotNaNProbe.roundtrip` 及最终规格桥原样保留，新源的原重写移至2581行。相同目标规范化语句已出现在60f原add_spec第2058行；这是当前修复依据，不构成新源编译成功证据。没有新增数学引理、helper或假设。

| 产物 | bytes | SHA256 |
|---|---:|---|
| [proof2 Kernel](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-result-guard-both-proof2/Kernel.lean:2580) | 156558 | `bee6ccdfec16d2b21810af4bea2389bcb2765e534b667cdc952188845227f183` |
| [manifest](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-result-guard-both-proof2/manifest.json) | 2638 | `4eb79dd81a0625f16c1d7fd246dc7ea09d911ba3da88931bf02777a4092a0cea` |
| [README](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-result-guard-both-proof2/README.md) | 401 | `c04de0384977e30dff79ed048f45d52b2f1443bef89501e16fa3253df3ed1cb5` |

差异仅为byte offset111646处插入104B这一行，无删除或替换。移除完整实际Submission.add_spec后，两源其余155893B逐字相等，SHA `119c37e3172b109cb21242bd902fd822c158510f1e0cb5eed1b287d9cf3318bf`；23134个非空白token的相同指纹为 `4a0efc799702876a953f4b03e250425b2359e873c41f0e71e367f54f50c9996c`。这覆盖全部运行时定义及其他证明的原文本，足以确认运行时token未变；不是编译器或C等价测试。原源最后重算仍为精确d027。

新源比256000B上限少99442B；四条原规格义务add_spec/mul_spec/sum_spec/bmm_spec的完整命题头保持相同。全源无sorry/admit/axiom。另用保留的原4b7e838 policy/options做静态检查通过；这是历史原policy的轻量本地检查，**不冒充814当前验证器的新执行或完整gate**。其原文件SHA `1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194`，未修改。

[详细JSON](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/authorized-validation/result-guard-repair-review.json) 记录单行映射、原错误、四命题头摘要和静态差异。**新bee6候选Lean/四义务/完整gate/C均NOT_RUN，性能UNKNOWN。** 协调者负责精确公开CI；本次没有向其他会话发消息。
