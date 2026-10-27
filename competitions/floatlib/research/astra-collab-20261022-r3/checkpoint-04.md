# R3-04：机器字循环完整通过与实际 C 审计

已直接读取 run405 `39725747762` 原始 full verdict、生成 C 索引及 C 字节；对应记录为 `matrix405-codegen-and-results.json`。原 R3-01 `4d37c26c` 的读值等式失败保留不改，下面通过的是 D 的精确修复/适配版本。

| 候选 | SHA-256 | 完整 gate | bmm 三类 ns/MAC 算术平均 | 官方整包 ratio |
|---|---|---|---:|---:|
| word + Packed4 USize proof1 | `e54f091df8f0b42e375c3fe0456f1cc0446be7bf8a93db53b8632df4a181472a` | PASS | 1.2509746667 | 0.2708161492 |
| word + Packed8 Nat proof1 | `6dc567b91da496a00c7e9b8bb3acabe9db2078f037d8c039dc9d601d20d5d226` | PASS | 1.3236953333 | 0.2696848850 |
| word + Packed8 USize proof1 | `9a4b1ddab0da0b2c798440eca62a2039096a0669d2fa638b6a6bc041a534cc54` | PASS | 1.1879180000 | 0.2666215210 |

每个版本在同一批分别与随附参考配对，均25轮；这不是专门在候选之间交替配对。部分参考类 spread 接近1.74，原始慢样本保留，不按小幅整包差异提前宣告稳定排序。D 已选择冻结八路 USize 做独立确认，R 不重复派发。

## 真实代码生成关闭了什么缺口

4路 C SHA `1de4245d6f25783ee52e354b7a997bcf93d4c709ed88923d1642d937b2c4635b`；8路 C SHA `2438c416445e987ff04ebf246bdd686ce05693ccf256e5abf77eab184bcab60d`。两个 `PackedNIndex_loop___redArg` 都已实见：

- count/baseA/k 为 `size_t`；热循环无 Nat add/mul、无 USize→Nat、无 Array.size 读取及 A 的每步 bounds 分支。
- 两次 `lean_array_uget_borrowed` 分别读 A 和 B；4/8个原生 float 累加参数，分别4/8次独立 mul和add。
- 只有循环终点一个 F4/F8 结果构造点，循环内无状态对象/Float32 boxing。
- 泛型 wrapper 仍可带未使用的 Nat/证明参数，但实际热递归在参数约减的 redArg 中，不应把包装器存在误判为热循环仍有 Nat 运算。

C 中 A 的 unbox 有4/8个静态调用点；这些是内联字段读取，不能直接认作4/8次实际机器加载，也不据此再开微调分支。尚无汇编/SIMD/硬件计数器证据；不能把剩余耗时归因成已证明的某一瓶颈。

## 本窗采用边界与剩余工作

1. R3核心目标已有实际进展：消掉热循环 Nat/边界成本，完整 gate 通过，保留对应计时。当前仍是 discovery；等待冻结版本独立确认，不冒称冠军晋升。
2. R3-03 全局守卫候选保持冻结、NOT_RUN。源码级外围检查减少成立于新证明尝试，但本窗优先最终确认及 D 已准备的求和/矩阵整合；D明确要求保留为后续起点，R不自行开启额外验证。
3. run407真实求和整合首次失败于重新打开命名空间时缺少 Binary32/ExecFloat/sumSpec 的 open；完整数学转换证明已在406实际编译通过，但不能替代运行入口验收。D负责其修复与最终包，R不重复修改。
4. 两项网页已全部回收；两个新 ZIP、两份报告在 E:\Download，分别见R3-02/03及各自download-receipt。旧R2的原件和当时pending观察均保留。

R3状态已绑定此审计；后续只处理当前验证反馈、必要修复和回执回收。截止仍05:36:27Z；用户已明确要求已启动实验与CI完成再停，不因自然检查点提前结束本轮。
