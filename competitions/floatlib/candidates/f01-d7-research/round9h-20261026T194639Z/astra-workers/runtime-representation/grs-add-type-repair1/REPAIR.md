# GRS runtime1真实错误：输出sign mask补一个UInt32类型标注

原CI **40428306094**，提交`a92abea11a0a21e76df44a1a93114801dd3085a8`，输入 **35347e37e2c8d593d868c80522659b4fb18bda7604fc830a9f14eb7d39be33c5**。`full-build-output.txt` SHA **f39743788488176f9a2f65c4118b8864e8758272e72aabd3a86dc02b4ccf8bdf**；verdict SHA **9eb09fcf59fd47dd074852779baf9e042adb06191694aac8bd1524d89de58485**。亲读原输出，只有一个`work/Submission.lean`实质error（其余为旧warning/info和末尾build failed）：

```text
error: work/Submission.lean:6629:24: failed to synthesize instance of type class
  HAnd UInt32 ℕ ?m.226
```

该行是输出打包：`R7W02.fromRaw ((hi &&& 0x80000000) ||| (e <<< 23) ||| (mid &&& 0x7fffff))`。失败目标明确将右侧掩码推成Nat，无法构造`HAnd UInt32 Nat`；这是类型实例问题，未出现算术反例或新ADD规格检查。

唯一修订：

```diff
- (hi &&& 0x80000000)
+ (hi &&& (0x80000000 : UInt32))
```

常量仍为2147483648，严格小于2^32；没有改数值、运算符、顺序或分支。新类型标注使该运算两输入明确为UInt32。**这是有原错误依据的修复尝试，尚未重新编译；不能写成已修复通过。** 原片段没有完成elaboration，因此本报告不虚构原/新Lean等式定理，只证明去除这一处标注逐字恢复全部原源码。

| 独立新产物 | 字节 | SHA-256 |
|---|---:|---|
| Runtime-grs32-add-type-repair1.lean.inc | 1878 | b4625c0f6891e1a0edcf805138cca0a82d637b977f41f0dcc5e30d8dcffe0304 |
| Kernel-grs-add-runtime-repair1.lean | 228707 | 77377f8b373988545c557aa6f5cd5edfd82ec772bb643a404a15e26e02d627af |

完整源精确为保留B2的226829B前缀加新片段；原1867B/e483、228696B/3534及CI失败输入均未修改。修订+11B，`forward.patch`和`inverse.patch`保留单行差异。`build_repair.py`核原件、精确逆替换和两处`fallback x y`顺序保留；normal guard、按magnitude选择、d0/d>=32、sticky、T、T0、postE及最终字段均无其他变化。

仍是同7根：四个`Submission.{add,mul,sum,bmm}_spec`，以及`Submission.R19GRS32Add.{alignNonzero,guardedAdd,diagnosticEntry}`。已写`HelperAudit-grs-add-runtime-repair1.lean.inc`。后3根是定义，不是新ADD等式证明；public四入口仍逐字B2，当前新运行逻辑仅在diagnosticEntry。

固定Lean4.34.0 / 293d5d0c0c3f3dded4688b3ccd6a33939ac5102b、官方4b7保持原环境。只抽取原官方gate的纯`intake/policy/options`函数作文本检查，三项PASS；未运行Lean或更改gate。新statement、整模块重放、7根审计、C/ASM、public等式、完整gate及性能均NOT_RUN/MISSING。

下一必要回执由D队列决定：重验同7根并抓真正`Submission.R19GRS32Add.diagnosticEntry` C/ASM（工具前缀通常为`lp_competition_`，须以实际C为准）；本片段没有`normalCore`声明。成功后检查包含所有guard和原fallback的完整入口，不用独立alignNonzero代替，也不把仍为B2的MainFull当作新ADD性能。无需因这次类型失败重做数学模型或更换算法。

精确绑定见`manifest.json` SHA **224ff3a793ff31a356cf43f37fad2094fa234c7b02657f2012286229d71ea9e5**。本方无Git/index/CI、本机Lean或嵌套agent；未处理DirectBias的另一独立失败。
