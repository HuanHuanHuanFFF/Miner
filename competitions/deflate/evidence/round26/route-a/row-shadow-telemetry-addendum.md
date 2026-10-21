# A11 遥测范围澄清

记录时钟：2026-10-12 00:19:43 UTC，晚于 run38187224205 的 00:14:08 启动。此为事后文字澄清，不修改已冻结 observer、批次、required_files 或评价操作。冻结预声明已恢复为 commit `0053b380bd1dd59590e1451382e1130e311a6b81` 的精确原字节，恢复哈希见 `row-shadow-declaration-recovery.json`。

冻结观察器的 scalar-pair 计数只覆盖 `pc_common_from` 的标量尾部、`pc_f_try` 的末端检查、`pc_probe_lazy` 的末端检查。它不统计 fold 的直接标量比较或输出复制。be4/be8/xor8 计数也只代表对应辅助函数的源码请求，而非所有内存访问。原活动 PC helper 总数和 row query-only 总数具有不同范围，不可直接相减为整体时间节省。

该范围由已冻结代码直接确定，没有依据运行结果更改判别门槛。实际回执仍由主线程收取，写此澄清时本子线程尚未读取 A11 运行结果。
