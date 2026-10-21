# R 检查点 03：高优先级原生逻辑模型路径

2026-10-21 10:46 UTC。建议本检查点优先于零捷径长证明和继续循环微调。候选是新的实际可得公开起点；**完整 gate 和公理审计仍 NOT_RUN**。

## 足以改变路线的源码事实

Lean v4.34.0 `src/Init/Data/Float/Float32.lean` 中，Float32 是带 `toModel : Float32.Model` 的结构。`Float32.add`、`Float32.mul`、`ofBits`、`toBits`、`isFinite` 有公开逻辑定义；add/mul 的定义为对 packed model 运算再 ofModel，运行时由 Lean 自身已有 primitive 编译。这些具体函数不是我们需要新增的 axiom。

Pinned FloatLib `0d918257...` 已公开完整证明：

```lean
ExecFloat.Binary.ofFloat32_add_of_isFinite (x y : Float32)
  (hx : x.isFinite = true) (hy : y.isFinite = true) :
  ofFloat32 (x + y) = ofFloat32 x + ofFloat32 y
```

实际来源 `FloatLib/Floats/Formats/IEEE754/Native/AddSub.lean`，已读取整个定理实现。它通过逻辑 unpacked 加法和 packed 模型构造证明，有限输入允许输出零、次正规数或 infinity。不能把 `Configured.NativeFPU.Unchecked` 的旧限制直接套在这个已存在的公开定理上；也不能反向假定它的全部传递公理允许，必须让完整 gate 的 axiom 阶段判定。

## 立即可测的最小包

已冻结 `candidates/f01-r1-guarded-native-add/Kernel.lean`：

- SHA-256 `aa24752887de02da3bf89871afbf9a7e2cae2e821bef4ca1023642e603cc8177`
- 33959 字节；四函数四证明，只有 add 替换；sum/bmm 自然复用新 add，mul 不变。
- 快路径实际检查 fx/fy finite，并检查转换后 raw 位逐个等于原 x/y；任何失败仍 TunedAdd。把往返关系作为运行 guard，使首次证明不依赖尚未闭合的位分类定理。
- 快分支证明直接用上面公开定理，raw guard 用 ExecFloat.ext / Subtype.ext 提升成等式，最后 ExecFloat.Proof.add_eq_spec。未引入新的公理、运行时代码替换、IO、FMA或重排。
- **草稿未编译，尚未证明 gate 允许**。建议 D 复制至自身目录，优先完整 gate 和公理审计；若失败保留精确依赖／错误，不能绕过审计。如果通过，再确认实际 C 的 `lean_float32_add` 和 fallback、完整十二类计时。

这里不是要求信任硬件产生任意近似值：证明对象是当前 Lean 的既有逻辑模型，部署运行仍由官方固定工具链／checksum判定。正式可用性由现有官方规则与完整 gate 决定。

## 后续路线及停止条件

先做 add 可行性，尚不增加第二个 native 候选。若合法且快，R 下一步研究去掉重复位 guard 的纯证明、以及 mul 的桥接。Pinned Native 目录没有 MulDiv.lean（真实404）；搜索命中的 Arithmetic/LeanModel/MulDiv 也属于更新版本，pinned路径实际404，需回查旧版集中式 Arithmetic/LeanModel.lean；不能把 native mul 默认视为已证。

若出现禁止公理，此路线暂停并记录具体依赖，回到直接循环与有限零捷径。若源级合法且 gate通过但收益有限，再查看 C 是否仍有逐元素 boxed state、finite检查和转换冗余。

精确源副本在 `sources/Lean-Float32.lean`、`sources/Native-AddSub.lean`、`sources/Native.lean` 等，URL和SHA在 `native-source-receipts.json`；原 connector 源内容在 `native-source-responses.json`。作者：本次Float32文件头为Amazon，作者Leonardo de Moura与Julia M. Himmel；FloatLib文件头为FloatLib Team。按各原文件许可保留，未伪称自主发现新数学定理。
