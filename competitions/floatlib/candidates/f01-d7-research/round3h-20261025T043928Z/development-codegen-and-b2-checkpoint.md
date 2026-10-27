# R15 真实statement代码位置与B2接入

开发已接入622d8394为 `f01-r15-dev-packed-b2-1`，保留226829B原源码，独立审阅与完整类型运输路径已核对；seed1526006只做其statement检查，提交9fd0c424已推送，等当前唯一完整D终态后启动。不会挤占或取消40166656717。

本轮40166091242的默认statement诊断其实保留了精确Submission.c及MainFull.c。开发已从65件原件核验、Git归档Kernel绑定后提取原字节函数，见 `development-codegen-audit-40166091242-v2.json` 与 `development-codegen-40166091242-v2/`。第一份导出因参数只识别x_名字，漏了当前v_名字MainFull，保留旧文件并以v2补全，没有覆盖原件。

实物观察：b116的R15ThinPairs.loop终端有 `lean_alloc_ctor(0,0,8)`，两个Float32分别offset0/4，未逐字段float box。可把它作为B2所复用F2类型的当前父本表示证据；新B2准备回调/loop仍待新源实物，不能由旧F4冒充。

f529的MainFull两个MUL字函数C体108569/112748B，b116相应41636/42487B；均为直接UInt32参数，别把___boxed适配器当实际调用。本次新rounder确有0/1 flag和位操作，C本身仍有if，不能先称机器码已branchless。源码显式共享rounded不等于最终消除了全部重复product。C体长、静态站点也不是动态成本或性能；须结合当前完整D。

两份C均为40166091242 statement层编译对象，不能冒充后续40166656717被清理的真实计时对象。默认ASM只抓旧Packed10Index循环，并非新MUL符号。R第三Astra若已完成f529审查可复用这些精确入口，不必重做source发现。新C和pure开发说明已在有限授权范围推送；旧190项完整研究不含在内。

当前目标仍06:19:28冻结、07:39:28截止；本轮余下只选能改变总收益的精确源，负D不重置。
