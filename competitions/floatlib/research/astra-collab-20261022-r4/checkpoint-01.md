# R4-01：2×4微块完整首稿

请D优先给这一份完整候选做statement并回传真实错误，再由通过的精确版本进入完整计时。同批如果还有长计时，尽量先得到此稿编译反馈，以留出修复与独立确认时间。R不自行Git/CI。

- `competitions/floatlib/candidates/f01-r4-tile2x4/Kernel.lean`
- SHA `7de60fa52c445fa31aad8a0b9e4143933e0c0b26cdebf07d12805c3fa72a5476`，157441 bytes；manifest同目录。
- 父本6744be2b整包完整通过两次；其add/mul/解码sum保持原字节，仅旧bmm重命名为bmmBase。另复制已完整通过bb1f783f中的Packed4模块，字节不变。新公共bmm使用2×4。
- 当前官方纯intake/policy PASS；Lean/完整gate/性能NOT_RUN，不继承父本通过。

运行组织：B用4字段包；每k读两个A和一个B包，显式绑定4个B字段，8个独立Float32累加器分别更新两行。结果按[batch][ceil(m/2)][ceil(p/4)]存F8，输出q用i/2、i%2、j/4、j%4取正确lane。机器字循环同时检查两条A流span；不满足则执行相同的Nat参考循环，保持总读取和原始非finite回退。

奇数m末尾行对的第二行不输出；它可总读取下一batch或越界+0，但低/高累加器组完全独立。最后batch的第二条A流无界时机器字准入失败，退Nat参考。这是当前有意的保守尾行策略，不把未观察lane假定成必须数值为零。列尾继续使用已验证Packed4.packB补零，零输出/n=0在准备前走参考。

新证明路线：low/high投影分别等于已有Packed4.dot4；通过已有dot4_lane/finish_eq_dot接到NativeFinal；wordLoop_eq连接机器字循环与Nat参考；rowBase_eq及行/列分解把合法q映射回原地址。完整bmm_spec已写出，没有外部sound前提。重复B字段在生成C能否真正共用、输出选择是否有额外构造，仍需实际审计。

机会与成本见route-analysis.md。默认形状下padded MAC从560000降到520000、独立B字段值减少，但A读取70000→130000、B对象1400→2600；净收益UNKNOWN。验收必须包含打包、转换、结果buffer、选择、释放和所有回退。优先检查实际C的3次uget、8个scalar累加参数、8mul/8add、4个不同B字段及仅终点F8构造；不直接据C声称SIMD。

本轮首稿已在08:20—08:30区间冻结；后续依据真实错误修复，09:20前停止新增未可编译路线，09:30进入确认，09:52:04截止研究并自然收齐已启动实验。D继续独占Git/CI和最终组合，R只在R4独立范围写入。
