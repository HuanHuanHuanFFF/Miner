# R15 标量 cutoff84：交根独立复核，再由开发唯一协调者验收

完整源码 `Kernel-cutoff84.lean`，253,562 B，SHA256 `837341a52575cffa9b5dfee6a44ba9369d1ee7ae4f6bb47fa47af11ae1f5831b`。父源 df5c；完整换回新 helper+mul/spec 片段后逐字节恢复父源。替换片段另存 `LowCutoff84-complete-fragment.lean`，生成器 `build-cutoff84.py`。原有 add、sum、bmm、nativeMul、LowScale.mul 定义原字节不动。

## 机制与新义务

在旧 `ex+ey<128` 分支内增加 `ex+ey≤84` 判断，命中直接返回符号为原 XOR 的零，其余回原 LowScale；高分支仍原 nativeMul。

1. 8位指数和不回卷，cutoff≤84排除双方NaN/Inf。
2. 每侧有限scale≤原exp，因此实际scale和≤84。
3. df5c已有 `UnderflowZero.roundP_zero` 对任意 UInt64 product 与scale≤84返回signed zero；原body精确复制为 `R15LowCutoff.roundP_zero`，同时复制其两个依赖。
4. 通过FastMul.core／LowScale.mul_eq回接原LowScale；新root mul_spec只作条件分支运输。

新增实质证明仅 `cutoff_nat`、`cutoff_special_false`、`scale_sum_le`、`shortcut_eq_low` 和根mul_spec接线。没有新RNE、偏置公式、大模数或多项式归一化。选择84而不立即扩到100/102，是因为三组真实draw中主要sparse/subnormal命中完全相同，新增数学代价不能由几个随机例子的更宽域支持。

## 实验意义和停止条件

`domain-screen.json`包含三个旧完整D的真实计划哈希、cell计分成本和输入样本。mul:sparse cell占whole5.89%–6.80%，cutoff命中约29.95%–43.29%；mul:subnormal cell占3.35%–4.18%，命中2.25%–76.07%，具有明显输入依赖。频率不等于时间，尚无候选收益预测或成功概率。

最小有效下一步：固定4b7e/Lean4.34原配置的精确编译/公理确认；通过后按本轮既定完整gate+25配对首次D与DF、41比较。新增源码只影响mul，但完整包可能发生布局影响，必须看whole。首次D不满足既定whole≤.97及p05>0时停放本源，不改名/重置seed重挑。若开发选择与已证矩阵源组合，须明确新组合SHA并对它单独首次D，不能加总预测收益。

本子agent没有Git/index/push/CI、Lean或编译权限。所有新增证明的实机状态为 **NOT_RUN**。`cutoff84-model.json`仅6,256个精确整数位型模型样本，通过0.023秒；模型进程外部5秒上限已实际执行，不能代替全输入Lean义务。边界样本明确拒绝zero×Inf、zero×sNaN，以及raw exponent sum103产生最小subnormal；两种异号tiny×tiny都保留负零。

## 源码调查与备选排除

- Conjectures.io/MIT，固定4b7e838…的实际BenchSuite源码已读，生成器SHA `2f1672738e07851fdb24ed968c248fc2e6d8a3e677c27763ebd489ada9425a9f`。定量计算按原cell_work×submission_ns。
- FloatLib Team/MIT固定0d918257…的FixedWord runtime与binary interchange dispatcher源码已读。采用起点为已经进入df5c完整gate的UnderflowZero数学组件，保留原作者注记；没有复制R14待公开190件资料进候选。
- Berkeley SoftFloat Release3e固定497c81c1…，John R. Hauser／加州大学Regents，三条件BSD式许可，f32_mul.c与COPYING实际已读。其路径先处理非finite/zero、规范化subnormal，再整数乘积+roundPack；它给出合法公开比较起点，但全软件乘法的R14失败成本已明确。本次没有搬入其C实现或假定其NaN策略相同。
- sum逆向sNaN扫描是MR03既有储备，不算新发现。三组本次计划可产生原始NaN的sum仅specials；该cell全部成本占whole0.178%–0.273%，即使全省也不足3%，因此本窗不为它单独占runner。不能把此观察推为所有未来draw的上界。

没有正式提交、资金动作或扩大公开授权。
