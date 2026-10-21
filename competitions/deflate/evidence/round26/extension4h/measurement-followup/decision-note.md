# 原CPU请求未生效：已有证据与下一次最小核验

状态：已有A20回执及官方文档的只读分析；未启动新CI、未修改官方源码或runner配置、未产生候选成绩。原始A20与本次文档响应及SHA均保留。

VERIFIED：A20实际执行的bwrap源码SHA与本地阅读副本仅将CRLF转为LF后的SHA相同（原副本字节未改），原包装通过 `systemd-run --user --scope -p AllowedCPUs=0` 提出约束。实际engine身份、运行期mask及CPU采样见[原反馈](../../route-a/a20-placement-feedback.json)。该进程52个存活样本始终允许0–3，出现CPU0和CPU2；scope的cpu.stat同时可读且增长，cpuset控制文件和cpu.max始终缺失。原stderr只含28文件测量进度，没有记录资源设置警告。外层CI准备脚本的资源健康检查只执行MemoryMax限制下的true，没有核实实际CPU约束。

官方systemd文档说明AllowedCPUs通过cgroup v2的cpuset控制器作用，实际CPU集合另有EffectiveCPUs字段；这属于接口语义，不能用文档版本推断本次runner安装版本。[systemd v255原文](https://raw.githubusercontent.com/systemd/systemd/v255/man/systemd.resource-control.xml)

Linux文档说明父层启用控制器后，子cgroup才出现相应控制文件；cpu.stat则在CPU控制器未启用时也存在。因此“cpu.stat可读”不证明CPU/cpuset约束已工作。[Linux cgroup v2](https://docs.kernel.org/admin-guide/cgroup-v2.html#enabling-and-disabling)

INFERRED：A20现象与该scope上方未实际启用或委派相关控制器相容，但未保存祖先的controllers/subtree_control或systemd属性，不能指定到底在哪一级、由什么设置造成。读取路径绑定到存活scope及同一PID降低了“进程退出后目录消失”的解释空间，却不替代祖先配置证据。A19使用另一runner/CPU型号，本结果不能追认其历史根因。

下一次若需要运行[逐调用关联诊断](../../route-a/a20-next-diagnostic-plan.md)，应先在同一次运行内补一个只读核验：

1. 对本次精确engine所在scope及其祖先路径，记录cgroup.controllers、cgroup.subtree_control、cpuset.cpus、cpuset.cpus.effective；不遍历其他任务、不读取环境变量或配置秘密。
2. 只读取对应scope与父user服务的AllowedCPUs、EffectiveCPUs、Delegate及ControlGroup，并保存systemd版本。对照请求、声明、内核实际mask三层，缺失逐项保留UNKNOWN。
3. 第一条能够区分的分支是“接口请求没有变成控制器状态”，之后才考虑单一绑定干预。即使约束修正，R24显式绑核的副本分歧反例仍有效，不能提前宣布计时变稳定。

以上只补充未来诊断计划。没有更改本轮成绩、补造正式评测环境、筛掉宽mask负样本或自动开启新实验。约束修复与是否改善测量噪声应分别验收；诊断时长不替代原版公共协议。

依据：[文档响应与SHA](receipt.json)、[源码及回执绑定](source-bindings.json)。本次查询约UTC09:35，精确起止见receipt。
