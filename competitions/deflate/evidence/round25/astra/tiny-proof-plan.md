# tinyPC8 最小证明迁移

目标Rust固定为 `r25-root-tiny-pc8/parse.rs`，SHA-256 `5c20b99cf52ac8e2f047b4e2e83be974b1f9b1f21b23d54ccccb25c58b891f00`。新证明只写 `r25-astra-tiny-pc8-proof1`，不修改算法Rust，不修改root候选或其他冻结文件。

父Lean是combo已验收的 `4ff09d168269ae8d9c93e602496b01078d2d0ec80f27d6cd16041d91a76c70a6`。新原生字节只改变tiny-config的2487→2155B；性能仍由主线程原协议测量，不由证明迁移推导。

## 迁移范围

新Rust仅有两个clone和row12入口：

- `r25_tiny_pc_record8` 是 `pc_record3_m` 的固定8头插入版本。循环内部不变，外层的 `pc_INS_MAX` 改为8；它只改变搜索hint的覆盖，不改变匹配真实性。
- `r25_tiny_pc_run1` 是 `pc_run1`，仅将record调用接到新clone。输入预取、完整匹配验证、lazy、fold、emission和tail逻辑保留。
- row12使用H32768、skip6、lazy16；没有新增路由条件。

拟新增9个局部定理：record两个循环别名和外层spec、lazy循环spec别名、两个literal尾循环别名、主循环spec及便于step的包装、run1外层spec。只让row12调用新的 `PC.tiny_run1_spec`。原 `bulk_parse_spec`、`parse_spec`及其约束、公理策略全部保持。

## 为什么循环可复用

原证明只要求head存储的位置有界，不要求每次只插入2个位置。新record循环仍限制stop<=lim，并将位置不超过end写入head，因此原HeadBound性质适用。外层需要实际验证8这一常量与wrapping加法、stop裁剪、tail边界的交互，不能把源码相似当完整验收。

对实际提取中按名字映射后完全一致的loop与body，使用显式展开两套定义的 `simpa only [...] using parent_spec`，避免重新证明lazy字节逻辑。主循环沿用既有 `MainInv1`/`Dec` 模板，让新增record spec通过局部step规则接入。新增record不增加循环状态字段；真实参数顺序仍须检查。

## 生成器的强制检查

`scripts/build-round25-astra-tiny-proof.py --extracted-dir <真实提取目录>`：

1. 核对固定Rust和父Lean哈希。
2. 与R23原完整gate的Funs逐定义比较；旧定义只能改变row12，不得删除旧定义。
3. 要求14个新增定义全部属于tiny两个clone；除了record外层，按名字映射后必须与父函数逐定义一致。
4. 添加上述9个证明，不添加sorry/admit/axiom；保持最终bulk/parse证明尾部逐字相同。
5. 将Rust逐字复制，保存双文件hash和真实提取工件hash。

目前生成器AST及6262B证明文本构造检查已通过。**这不是Lean解析或编译通过。** 真正完整gate仍需原始重新提取、原LZ77 obligation、公理白名单和roundtrip；主线程负责云端执行。

## 待闭合义务

实际提取接口核查、9个新定理的Lean编译、原版完整gate、精确pair绑定。若编译报错，依据真实报错修复新目录中的Lean，Rust保持同一哈希；不通过修改官方条件或提升限制回避失败。
