# 实际冻结原生实验的范围修正

**本环境：NOT_RUN；Lean：NOT_COMPILED；性能及宽gap Int终端：UNKNOWN。**

本文件修正上版的实验描述，不产生新请求、变体、输入窗口或CI。以下对象来自补充附件 `CURRENT-COST-REQUEST.json`；不再用早期Mixer接口替代实际冻结请求。

## 1. 对照、候选与绑定

| 项目 | 实际冻结范围 |
|---|---|
| 内部对照 | 已公开source12，SHA256 `e2c1f1f1ba52e32563fb193ceea7e2a271b989fd3ba2eb16cff747987879b521` |
| Winograd候选 | `winograd12-nativefinish-v2`，SHA256 `600eaaa1af9c7f7b2da1436f4d55d15a51b6879642d2ece0c5fa261e13f10e8d`，71667B |
| 模型 | 完整 `normalized_mlp`，batch8全部三个linear，包括输出宽10的末层；batch1、RMS/layernorm不变 |
| 调用 | `Submission.kernels`；native finish已经由两个builders接线 |
| 实验协议 | 冻结请求的原MainExact/flags、normal/wide/sparse及typical/scale/boundary范围；完整ns/checksum与原校验，不改gate或编译参数 |
| 比较边界 | 同次source12内部对照；public23/冠军链估计只能标INFERRED，不能写成同机public23测量 |

冻结请求已有其他机制条目；本次不增删、重排或执行该队列，也未接触其在途确认输入／结果。本包 signed63 cross、零body及ReLU零出口仍是独立未编译研究草案，**不自动加入600e**。

## 2. 600e已有的工作，不计入本包新增效果

`build_source12_nativefinish.py` 明确把旧接受调用替换为：

```
totalWords (fun hi lo => act relu (finishWords ... hi lo)) a w n
```

v2继承该调用，并在X检查与A准备之后加入 `if !(A.any (fun a => a.valid))`：成立时返回原整入口，跳过W/b扫描和B准备，保留原整入口的融合调度。此前已发生的X扫描／A准备／drop仍是完整成本。

这不是“任意E=0均回原入口”：存在有效A但没有可准入输出时，仍可能进入逐输出计算。**mixed-validity scalar miss丢四行／稀疏融合的风险仍须计入**。宽gap仍可能进入原Int终端；旧接受调用计数为0不代表全候选不存在Int fallback。

## 3. 什么结果才改变已有研究判断

沿用冻结请求的完整调用成本。准备、self/cross/corrections、bias、finish、零回放、fallback、输出与drop都必须在内；不能只用cross-loop时间或旧乘法计数判胜。出现编译依赖裁剪失败时，先按基础设施／源码失败记录，不能当成算法性能反例。

有已有诊断时，解释结果应区分：

- all-input-invalid整入口回退，与仍进入逐输出分支的scalar miss；
- 原对照实际访项数、稀疏nnz与融合路径，不能以public23源码分析冒充source12实测；
- native finish命中、bodyShift/biasShift宽gap与exact-zero replay；
- 输出宽10末层的准备摊销，以及完整模型聚合。

这些是解释同一冻结实验的口径，不要求本轮加插桩或重开计时。没有稳定完整成本改善，不能从“乘法减少”推进大证明；没有同模型全成本份额，不能用旧三入口linear比例外推10%。

`make_probe_delta.py` 仅保留为上轮**孤立片段**的历史组装辅助，不是600e修复器或既有冻结builder的替代品。本次仅核查补充builder文本／AST及声明哈希，没有执行它们的完整transform，没有重跑有限模型、原生实验或CI。
