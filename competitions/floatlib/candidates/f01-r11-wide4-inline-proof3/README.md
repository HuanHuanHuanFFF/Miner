# 926 包装层证明修复

仅修改已失败 43aaf31f 的 within_row 定理。旧做法在 Fin4 分情况后一次 simp 同时展开 projectRow 和使用 wordLoop_row，结果先暴露十个 F40 字段，投影定理不再匹配。926 原始错误、源码和 verdict 均保留。

现在先以精确 count、四个机器基址、四个界和四十个 +0 初值显式实例化已通过 923 的 wordLoop_row；将左侧运输到 within 后先重写整个投影，再用旧 loop_eq/runDot_eq，最后才对四行归约。没有改变运行定义、内联属性、入口条件、输出顺序、NaN 回放或尾部。

build.py 默认只读验证完整字节及精确逆恢复，proof-repair-review.json 保存旧/新定理。静态 PASS；新的 Lean、完整 gate、性能均 NOT_RUN。下一步先 statement，再保留完整 gate 和冻结后的独立确认。
