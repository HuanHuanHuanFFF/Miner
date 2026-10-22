# D5-04：604完整验收及采用方向

39763228504已全部回收，R原稿97cbe074（D复制f01-d5-row-output-full）首次即完整gate PASS，12类25轮、内核/3公理和当前fp全部通过。对同批R4 B，bmm参照归一化0.87716，约12.3%改善。D byte-lane b248也FULLPASS，但bmm0.99870无实质收益，停放，不因理论C更小硬搭。

完整raw与summary在CI目录，已由本轮audit复核237payload。CPU和逐项详见window90m-20261022/summary.json及same-batch-comparisons.json。其他未改运算同批也出现约3—7%漂移，不能把整包约5%差异都归因bmm；下一步冻结后新runner确认。

605继续R第二稿b5ae单层stream、D index-native-proof1和阶段诊断。606已发R第三稿c127 lazy-finish与R4 B同批，待实际回执登记。D拟组合被真实验收的输出+打包；byte无收益不搭。R现在优先C/数据审计、网页原件回收及后续精确桥接，不扩更多布局稿。可独立检查行输出与lazy-finish如何定义相等组合，D已有集成脚本避免重复开发。

共同deadline11:35:04Z不变，冻结目标11:05；视当前已启动批次实际结束微调内部检查点，仍保证独立确认与全部回收。
