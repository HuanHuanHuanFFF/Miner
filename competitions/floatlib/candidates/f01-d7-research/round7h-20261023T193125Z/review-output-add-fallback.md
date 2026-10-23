# 回收 TunedAdd：独立 a066 完整成本实验

**READY_FOR_STATEMENT**。唯一候选：`f01-d11-add-official-fallback/Kernel.lean`，SHA256 `73177f570f584f3429e181e5a27f98bfb56e6fc26fd6b7b3e0fbd3ba2152a553`，221629 B，余34371 B。严格从 a066 `a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78` 的237142 B构建，净回收15513 B；没有组合self-classifier或其他变体。

运行改动只有 `Submission.add` 原生结果为NaN时，将 `TunedAdd.add x y` 改为原版 `ExecFloat.add x y`。证明该分支直接使用 `ExecFloat.Proof.add_eq_spec`。有限原生结果分支、转换、self-BEq分类及其证明保持原字节。随后删除已无引用的闭合TunedAdd namespace。

独立从namespace标记定位出的范围确为a066的 `[79586,95110)`，15524 B，SHA256 `04f2b622654ce1c70972fa600a27736339b74129a8cd5ca38c922cca6cef9743`。块外仅指定的运行和证明两处引用。块内12个属性均为inline，无instance、simp属性、notation、全局option或其他全局命令；FastMul/LowScale不在删除范围。删除声明库存严格等于原 `Submission.TunedAdd.*`，不新增声明，原八个export/spec仍唯一。

完整块已人工读取；其中37个说明性doc comment不含作者、版权或许可声明。块前fastlog说明和全部块外作者许可行保持原字节。构建器同时检查notice词及块外notice行的字节顺序，遇到notice会拒绝删除。`exact-inverse.json` 保存三步完整旧/新文本、偏移、片段及完整源hash，逆变换恢复a066全部字节。

NativeMul以及之后的原生循环、sum和BMM整个后缀均逐字节相同。不过它们或其修复路径若调用共享 `Submission.add`，会在原生NaN结果时执行新的官方回退，因此不能把源码未变解释成所有运行成本不变。这个实验用于实际测量specials/repair代价，决定约15k容量是否值得留给更大的BMM重构；没有提速假设，也不假定冷分支免费。

本地精确父本/块hash、唯一引用、声明库存、无全局实例或simp泄漏、许可保留、finite热路、后缀字节、完整逆变换、资源选项不变、256000 B限制和固定原版policy检查均PASS。**新Lean语句、leanchecker、axiom审核、checksum、完整gate和生成代码均NOT_RUN，性能UNKNOWN。** Root独占Git/CI，旧源和冻结composer未改。
