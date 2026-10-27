# c70c 首次真实生成代码：支持一次原完整成本发现

**决定：保留精确 c70c，支持由 D 排一次原 full gate＋同 run B2 对照；不预判通过，不造组合。** 改造确实进入实际 BMM，packet/读取减少的实现前提成立；没有错误入口、重复点积或逐MAC额外结果对象。新增准备控制、闭包及live-state成本也真实存在，静态证据无法决定净收益。没有10%整包预测；尚不具备独立确认资格。

**身份与证明。** run `40395429076`，input 与本方源均为 `c70cf9479ca48b4690990ebbd0b3781139cbeb94e46b28bbe61563e3eeaced1c`；verdict SHA `efa5dc72a18c342504c9c4e3ce83259626a16f7402bd799c0eb68f3b5ad80d04`。原日志明确 VerifyFull build exit0、benchFull build exit0、Submission/VerifyFull两次leanchecker exit0；13个实际根均仅三允许公理，helper audit accepted=true。**这是 statement/replay/audit 通过；rounds=[]、ratio=null，完整gate/checksum/计时仍NOT_RUN。**

本次脚本 `audit_temporal_codegen.py` 新鲜核了17份源/回执/C/ASM/trace原件，提取16个C函数；结果在 `temporal-codegen-review.json`、`temporal-codegen-evidence/`。Submission C SHA `a4087dc824db9a8dcb3de54a21b67bc6038028635f5cdbd5aa5e19a6d1cf519e`；MainFull C SHA `94f69ed19083e0fbb5d4b540d16d4575b82d4aac75779ce88043ef4f908bfecb`。

| 已选实际路径 | 观察及含义 |
| --- | --- |
| MainFull L69 → Submission_bmm → Temporal_dispatch L45035 → output L44958 | MainFull闭包指向新公开bmm，送入两个原bench入口；原underflow及 `2≤p≤8,n>1,m≥4` 选择保留。新output只调用packB一次。 |
| packB L44654 → 每tile回调 L44624 → pack L44223 → packet回调 L43674 | 每tile只创建ceil(n/4)个记录；每条packet完成路径恰一个 `lean_alloc_ctor(0,0,32)`，字段offset0..28，无逐Float32 box。两个静态allocator位置属于末字段valid/padded互斥路径，不能算两次动态分配。 |
| numeric loop L44244 | 完整4项分支一次prepared-record借读、四次原始A解码、两条各4步顺序乘加；尾0..3分别处理。仅终态有8B F2；递归完整块没有结果对象。A原getD检查、Nat索引和全部ofBits仍在。 |
| output专门化group L44831 → 原ThinPairs emitter → 原Packed10.finish L38035 | 每group计算一次result，再输出一/两lane；没有重复loop。原finish非NaN导入或原raw replayEarly，原始A/B及全局地址保持。结果和preparedB按原边界释放。 |

**准备成本已从猜测变成具体实现。** 旧B2内层闭包4 captures，新版6 captures；外层5→4。64位请求模型因此相对旧版每tile增加16B闭包、整次外层减少8B。原packet+slot差值还要加入这些项：`tiles × (48 ceil(n/4) − 24n + 16) − 8`，不含容量、allocator、RC和Nat对象。尤其n=2的record+slot本来持平，现在该模型每tile净增16B。旧源保留，无据此调整冻结谓词。

**ASM实际关闭了一个歧义。** 同一diagnostic object `3c064e376a22c8fb03c90fc12f694af8a033cf49be8707aca7f08b21c98c71bb` 同时保留原B2与新temporal循环。栈frame的 `sub rsp` 为0x48→0xc8（72→200B）。新完整块在0x1f5..0x21c读取四组B并存栈，四个A转换结果的前三个也存栈，之后0x5ca..0x5fb做四组mulps/addps，严格保持原序。

但在已核的small-Nat、数组范围内、完整4项路径上，**新旧每4项均8次XMM存栈＋8次读栈**：旧每k的两次store/load重复4次；新变成四个B向量＋三个A结果＋一对acc。offset清单已机器核对并存JSON。更大的frame不等于该路径动态spill次数更多。尾段/大Nat/默认值路径、准备及缓存行为未纳入这个局部计数，不能据此宣布整体寄存器成本不变。

保存的objdump没有relocation名，不能只凭0x221/0x276/0x479/0x585的call地址断言callee；四次ofBits由匹配C明确给出，ASM对应关系是推断。该对象明确是诊断重建，不是完整计时gate清理后的timed ELF；机器时间、分配器耗时及净收益均UNKNOWN。

验收下一步仍是精确c70c的原完整gate和首个真实发现样本，不需要先做第三次纯静态复核或改变源码。若首次发现不达原门槛，保留负结果；只有新的成本证据或实质机制变化才重新投入。
