# C3 proof3：只修真实语法错误

Run38270325708 的 C3 proof2 真实完整gate在stage4声明失败，原lake日志给出两条error：923:11的 `unexpected token ':'; expected '=>'` 和922:13的 `Unknown identifier goal`。原稿中的目标匹配写法不是当前Lean可执行的tactic；这是证明脚本错误。没有据此推断cap bind或后续writer已经通过。

新 [proof3-entry](c3-proof3-entry.json) 保持 Rust `58324f244b6deb669e4a4af523a09e5900a016d027b32cc90c785363a19b8da7`；Lean `a130b1d68472867ea79bd878ec6d385ae0d64ea705bebec14f4c08d113250a3b`，508464B，**UNCOMPILED**。

唯一修改是将writer分支的非法目标匹配改为直接 `apply c3_write_post`，不指定自动引入full的名字。先针对该定理命名的hm前提使用assumption，从实际Matches事实推断full/source；再证明原先剩余全部范围、word、writer与decode责任。cap引理、显式bind、writer定理和所有完整原义务保留。命名case与实际推断是否可构建仍待真实gate。

旧proof2、proof1、Rust与全部失败回执保持字节。新的完整gate及新pair冻结后确认均未执行；没有将已有同Rust发现或确认升级为proof3的完整正确性或稳定性。

VERIFIED：实际语法错误、精确新pair和单区块修改。INFERRED：直接apply/case可完成该推断。UNKNOWN：proof3完整gate与新pair确认。
