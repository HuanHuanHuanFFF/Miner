# R7检查点09：c760新样本确认与实际校验和交叉核对

2026-10-22 20:12 UTC。R独立读取807原始artifact，入口`nonnan-composition-807.json`。当前官方原版public-v2、精确源码、25轮、完整重放/三公理/fingerprint/cell_work均核验。

- c760非NaN终点再次FULL PASS，新seed807、新runner：整包归一化0.91787370父本，sum0.85617307、BMM0.85584592。保留805发现样本0.89159742整包，不挑更好的数字覆盖新样本。
- D的60f74aa4 direct+nonnan完整组合FULL PASS：整包0.80180152父本、BMM0.60151121、sum0.85415693。同批相对d9整包0.90700992，相对c760整包0.87354233。该组合首轮结果不是已独立确认的整体，不等于现任冠军比较。
- D的d9本轮完整PASS，整包0.88400524父本，继续保留802/804/806/807变化。

## 有限模型对实际运行的核对

R复用D已经真实执行的807原始诊断和输入计划，未改基准或新派CI。`public-nonfinite-opportunity-807-profile.json`用公开生成器的独立Python转录与整数binary32模型重新计算68个sum/BMM计时case的全部输出，并按原来的UInt32滚动校验和聚合。与D三个实际Lean进程204个校验和逐一相同；诊断也报告与未插桩control一致。证据`public-oracle-checksum-crosscheck-807.json`，可由`crosscheck-public-oracle.py`重放。32位校验和可能碰撞，这只是强于纯自测的有限经验核对，不是数学证明或性能测量。旧805/806分析源在`public-nonfinite-opportunity-v1.py`逐字节保留，旧JSON不改写。

发现计划806还显示：NaN矩阵旧回放51661步，quiet早停后前缀15321步；sum旧NaN回放15186步，前缀5237、后缀9949。计划807中sum后缀11076字，如果在quiet修复之后反向扫描剩余Vector，模型只需5549字。故R准备了`sum-reverse-suffix-block.lean`与builder，但**未生成新候选/未请求新CI**；先等627原native-prefix+forward-suffix实际通过并测量。新证明直接比较两个具体Nat/Vector扫描器，quiet前提仍只在运输到真实加法时使用，没有List.reverse分配，也不会跳过后来的signaling替换。

## 下一步保持可控

现有b169组合优先，ee矩阵prefix、627求和prefix与7ac原始字quiet守卫等待D按槽位采用。W04仍在公开网页处理Float32自比较nonNaN桥。若它真正闭合，优先一次受控替换实际四个终点守卫：这影响每个BMM输出，而不只是NaN回放。新prefix的逐步守卫可在其首轮完整证据之后再复用，避免在未验证父本上混入多项变化。

当前官方冠军直接结果、私有suite、准入/资金均未改变；研究窗口与02:45冻结时点不变。
