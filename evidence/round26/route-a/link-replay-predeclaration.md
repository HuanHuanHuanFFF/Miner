# A13：维护成本的独立判别

记录时钟：2026-10-12 01:08:49 UTC。一次 native 诊断，外层最多15分钟；编译最多240秒、运行最多300秒、nm/objdump最多30/60秒。没有新生产候选、容量扫描、原encoder重跑或完整Lean。研究新派发截止03:06:52 UTC，总截止05:06:52 UTC。

## 缺口和改变选择的证据

A12少了约97万次第一来源word预取，但13个受影响文件parser全慢57%–122%，整轴主块慢9.1762%/9.6110%。每类tag/cursor RMW仍约392万次。维护可能解释这份回归，也可能主要是通用查询循环、调度或编译布局；目前不能据次数确认原因。

本次只问：在同一实际插入序列、隔离查询工作之后，row维护相对旧head/prev维护的额外成本是否仍然很大？若隔离差额远不足以解释真实parser delta/link的数量级，只能反对“隔离维护单因足够解释”，不能证明生产维护免费。若差额大，则支持放弃这种每事件双RMW表示，或仅在有能删除主要维护成本的实质新表示时继续；不因结果不理想扫描row容量/深度。重放时间不作为整体加速上界，也不把某个函数视为已证实根因。

## 真实轨迹、身份和不归档的内容

冻结A12 Rust `9c42e665cfdb8831e2c7f4dbe0a2de6012e59bc8ae9bd6918d540ea71704e2ac`，原641 Rust `97254225b7a7a5c67a749b9fed7b58c94a9612b816c233581db6d7401d502181`。临时observer只记录实际`ar_link`的p、row、tag和query/record标记；保留原28token/decode，并绑定 A12 原encoder及计数回执 SHA。必须再次得到3917583个事件，其中2073185为normal/lazy query插入，1844398为record插入。

每事件压成一个u64：p的32位、row/tag共20位、query标记1位。使用实际H/km，逐事件重新核验masked hash产生的row/tag，以及原15位head slot = row12拼接tag高3位。所有本轮H均走原15位路径；未来不同H不在此泛化。完整trace约31.3MB，只写runner临时spool并计算SHA，不上传artifact、不进Git。归档输入/token/trace的SHA、数量、生成器、harness和原timings即可复建。

## 固定重放矩阵

对每个有真实PC事件的输入，旧 `pc_f_link` 和新 `ar_link` 消费完全相同的事件数组。三个固定返回值模式：discard-all模拟record不消费返回值；consume-all消费每次old head或row victim；actual-mixed按真实事件标记消费query返回值。后两者的校验和用于使返回值活跃，旧索引天然还需old head写prev；这不是声称两个索引返回语义相同。

同一完整trace保留全部更新顺序，不把query/record子集拆开重建另一种历史。两个相反kernel顺序块，每块每kernel一次warmup和11次measured；每个rep保存ns、模式、序号、事件数、最终状态digest和返回值checksum。独立标量参考一次计算两种表示最终状态及各模式checksum，全部rep必须一致。digest/checksum不同表示之间不要求相等，而是各自等于参考。

数组清零和最终digest不在计时区；在计时边界使用black_box固定初始化、输入事件切片和最终数组/校验和，防止死存储/循环消除。helper保持冻结源码的inline属性，外层replay kernel noinline，避免逐事件计时。运行固定在当前允许的第一个CPU，归档前后affinity；没有设置全局频率策略。

编译用固定Rust nightly-2026-08-18及原candidate release的优化项：opt-level3、fat LTO、codegen-units1、debug-assertions=false、overflow-checks=true、panic=unwind。保留完整编译参数、rustc verbose、CPU信息、binary SHA、nm符号与完整反汇编。这里是独立可执行harness，模块布局/调用环境不同于原cdylib，不能宣称汇编就是生产parser的相同机器码。

## 明确的环境差异

事件数组带来新的顺序读取和解码，可能成为带宽成本；缺少正常query交错，cache局部性、读写依赖和store buffer压力与生产不同。重置数组虽在计时外，也影响初始cache。consume校验和和mixed标记分支是诊断开销，生产query/record调用点往往已静态区分。孤立helper的编译上下文也不同。禁止用row减parent的ns直接归因真实parser回归，更不能把它作为可回收整轴上界。

VERIFIED（本地）：冻结源、harness唯一替换、完整20位hash拼接模型、Python语法。UNKNOWN（运行前）：Rust编译、真实trace identity、每rep计时/digest、机器码与相对维护成本。完整生产preflight需待主线程接入新hook后实际执行；自模块检查不代替它。
