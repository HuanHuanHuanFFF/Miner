# 隔离后续：跨榜组合源码预算

22:59 UTC，响应D AFTER-FREEZE-CROSSBOARD-PACKING。只用原先公开5/23和已见formula输入，不读确认组；不生成新组合候选、不占CI。

- #5 `bc580a4c…`252691B、#23 `1010c074…`252639B。两者kernels0文本相同，但全局别名/记号与多个同名函数含义不同；不能按函数同名盲接，也不能简单concat。
- `dependency-census.json`：#5 conv+elem词法依赖集合411声明约173071B，真正runtime词法子图115声明约26095B。包含局部变量误命中且未解析隐式依赖，**不是经过Lean确认的闭包，也不是严格不可行下界**。仅去字节完全相同声明不足以解决空间。
- `replace-budget.json`：反向从#5移走旧norm、使用specNorm作为预算占位，保守清除未引用声明后216775B，余39225B；同时移走旧dense后183066B，余72934B。占位源只在内存计数，未产出/编译/测速；仍需新增实际23算子及证明连接。
- 下轮可检验的结构方向：用固定官方fallback代替手写通用fallback，减少独有证明负担，再接5卷积/23dense+norm。`norm-fallback-census.json`在旧54个formula cell中RMS243行全部走原23 native sqrt、layer242/243行native，1行FW shift guard。**这只说明有证伪入口**；官方fallback若极慢，单个row也可能毁cellguard，必须完整成本先判别。
- 当前overall8/retired5官方旧报告点比.92339619；若政策和环境可归约，.97规划线相对5约.89569430。current8直接源/直接新配对UNKNOWN。不能把两个分榜的组件收益相加。

不挤占当前RMS terminal小源、FP/dense真实成本；下一步若做组合先锁定具体新增闭包、逐个冲突映射和bytecap，再申请单完整模型成本。
