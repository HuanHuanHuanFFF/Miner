# 暂缓 bias 半径细化

07:10 UTC，`linear-bias-radius-probe.py/json`核对公开legacy MLP seed42、batch1、三类输入，共1020点积。依赖C的精确生成器镜像与原输出记录，Python double模拟实际分步乘加和raw checker，非Lean／本机原生测量。

实际linear把bias作为最后一个`1*b`项。直接取两份追加向量的peak之和会把不存在的交叉乘积也纳入误差界；可改用`max(peakX+peakW, idxBias+125)`（bias非零时），只约束实际body乘积与精确bias。有限筛选中H减少0–2位，证书放行由994增加到1008，多14项，没有观察到被接受word与原精确输出不符。

这只关闭“bias追加必使主路径大量不可达”的一个担忧，没有建立新候选、形式证明或速度结论；计数比例不是成功概率。此legacy形状也不是正式typical/scale/boundary评测。本轮先保留原半径和运行时，暂停为此新增整包证明。后续只有真实模型回退成本显示它影响采用时再重访。优先完成实际拓宽、orderKey、prepare/getter、Tail enclosure与rounder连接。
