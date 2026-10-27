# public MUL 接线：一次关键核查

09:25UTC现场检查：365f49b1公共数学探针仍为255561B，余439B；本轮候选目录目前最新仍是u64-lowering1，未找到D已落盘的真正public MUL候选。因此以下结论只绑定365和当前已有源，不称最终候选已检查。

365中原Submission.mul及其mul_spec仍是B2的LowScale/native fallback实现。新增preserved_fallback_entry_spec证明的是R17NumericMulInteger.guardedMul Submission.mul，不会自动替换public入口。当前probe本身未见fallback循环；它也不是新性能候选。

最终必须形成这条调用关系：**新Submission.mul → 新guardedMul → 仅在拒绝路径调用唯一的旧B2 fallback名**。旧fallback和旧fallback_spec须一起保留对应；新mul_spec必须证明新Submission.mul的全输入义务，不能只把旧spec换个名字。若对整段旧Submission作namespace改名，必须同步所有限定引用和审计根，并明确其余三个public导出；若仅改早期mul/mul_spec名字，还要处理后续旧mul_eq/referenceBmm等引用，否则会出现未定义、旧绑定或意外指向新入口。

推荐核对的两式（Legacy仅作映射示意，不是新候选）：

```lean
Submission.mul x y = Legacy.R17NumericMulInteger.guardedMul Legacy.mul x y
Submission.mul_spec = Legacy.R18NumericMulSpec.guardedMul_spec Legacy.mul Legacy.mul_spec
```

第二行表示证明接线关系，具体定理参数/类型仍按实际定义写；公共原gate对新函数的正式义务和实际MainFull MUL回调是最终依据。不要从函数或theorem同名推断已切换。

原439B余量不能覆盖任何未来接线声明：namespace改名、fallback名字长度、public wrapper、定理修复和换行全部计入实际最终字节。365有98处Submission完整标识符；仅全词改名到Base可回收588B，但这不是最终余量，也不建议仅为省字节选可能与局部变量冲突的短名。D最终源必须重算整文件bytes/SHA和LF、运行原policy，≤256000B后再排完整gate。当前核查没有修改或生成D候选，也没有复核已通过的28根数学。
