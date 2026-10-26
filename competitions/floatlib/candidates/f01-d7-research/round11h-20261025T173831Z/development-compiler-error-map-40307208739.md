# CI 40307208739 精确源码错误索引

原始日志和失败源未修改。这里只去重并定位声明，修复后必须重新编译。

## f01-r17-dev-add-public1
源码：`7e1524c818285ce2c7721140fd0cff23560416abc6ea9a2c72ddf1be9a588be7`；提交：`c8f0cad6abbfb5a81b47465e05e088fc462d3a3a`。

- development · L4811:10 · `R18A.T18.sameNoCarry` · Tactic `rewrite` failed: Did not find an occurrence of the pattern（1次）
- development · L4823:6 · `R18A.T18.oppNoCarry` · Tactic `rewrite` failed: Did not find an occurrence of the pattern（1次）
- development · L4991:50 · `R18A.T18.oppWordShift` · unsolved goals（1次）
- development · L5086:4 · `R18A.O18.addAligned` · Tactic `rewrite` failed: Did not find an occurrence of the pattern（1次）
- development · L5352:17 · `R18A.P18.sorted_spec` · Unknown constant `Bool.and_eq_true.mp`（1次）
- development · L5355:17 · `R18A.P18.sorted_spec` · Unknown constant `Bool.and_eq_true.mp`（1次）

完整错误：JSON同名文件；原日志 `competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40307208739/download-1e71bedd2176434a8c7e70c8f3a14eb0/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r17-dev-add-public1/full-build-output.txt`。

## f01-r17-dev-u64-public1
源码：`23adf0984bef02e611143cfc7e40d64d65c99caa0f4d11a0648812b2fb6f1e73`；提交：`c8f0cad6abbfb5a81b47465e05e088fc462d3a3a`。

- development · L6849:26 · `R18.R17UInt64Fields.mantissaWord_nat` · Tactic `rewrite` failed: Did not find an occurrence of the pattern（1次）
- development · L6873:26 · `R18.R17UInt64Fields.highWord_toUInt32_nat` · Tactic `rewrite` failed: Did not find an occurrence of the pattern（1次）
- development · L6907:23 · `R18.R17UInt64Fields.low_mask_eq_self` · Tactic `rewrite` failed: Did not find an occurrence of the pattern（1次）

完整错误：JSON同名文件；原日志 `competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40307208739/download-1e71bedd2176434a8c7e70c8f3a14eb0/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r17-dev-u64-public1/full-build-output.txt`。

