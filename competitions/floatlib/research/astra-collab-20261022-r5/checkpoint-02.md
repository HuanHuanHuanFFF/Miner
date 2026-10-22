# R5-02：单层流式逐行候选，减少首稿中间层

10:26:38Z第二份完整稿已落盘。候选`f01-r5-row-stream/Kernel.lean`，138804 bytes，SHA `b5ae8d9b9c8c294ceaa6ee36893c95424bfa3bfc455dc7db7de5c736b154ff17`。首稿97cb保持原字节。所有新源码的Lean/性能仍NOT_RUN。

相对首稿的实质变化：用一个Fin(batch*m)行索引向量和单层Vector.flatMap按行运行；每行只计算一次该行5个tile，立即构建该行50个输出并追加。移除全局结果tiles嵌套向量，以及第二层batch输出flatten。逐行输出只需每行一次r/m与r%m；列回调内仍无全局q解码。A和B准备仅一次，dot中每个k乘后加的原顺序以及所选输出的原始输入回退完全不变。

证明直接比较新core与旧Packed10.core，逐q用固定Vector.getElem_flatMap、getElem_ofFn和已有vector_get_ofFn展开。三个真正索引桥为Nat.div_div_eq_div_mul、Nat.mod_mul_left_div_self、Nat.mod_mul_left_mod；已从Lean4.34固定源码核对声明。证明覆盖任意尺寸，不添加positive shape到最终规格；原空形状/n=0回退保留。

此稿仍会分配行索引和逐行输出数组，flatMap的append/RC成本尚未实测。不是“没有中间数组”，也不保证优于首稿。源层预期从两轮输出引用复制减至一轮；真实优化与释放以C/完整计时为准。若首稿没有收益，第二稿才是判断是否由两级复制抵消的有用对照；两者收益不相加。

已读D5-01：D负责数字转换进入矩阵、packB基址外提、证明getElem及成本诊断；R不重复这些实现，也不改D文件。D可按CI槽和成本结果选择本稿statement或同批完整gate；R继续处理实际反馈和两路网页产物，不操作Git/CI。

第二网页R5-W02于10:24确认GPT-6 Pro并实际responding：尝试以一次toBits和指数位判断替代finish的isFinite+toBits，目标为全输入等价，未知是否可证/更快。它不依赖输出布局，不会阻塞R主候选。
