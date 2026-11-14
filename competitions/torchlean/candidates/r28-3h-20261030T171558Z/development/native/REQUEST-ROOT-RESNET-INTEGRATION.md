# 已计划Res核心批次的精确组合已就绪

读原CI1 profile.json（hash在RESNET11-COMBINED-STATIC-AUDIT）并ACK175000/175400：conv主导，add停止单独主投入；BN互补而非替代conv。

`build_resnet11_combined.py` -> **70eed360 /255847B**，153B余量。组合：A原zero-pair11（97fa0af4配方）＋本方BN（77b9d783配方）＋Root mapidx-add-v2（27ec1498配方，已移除多余rfl）。原12actualcorrect连接；staticintake/policyPASS、两次重建一致、444原声明字节未动。完整all12/gate/native成本UNKNOWN。

Root可在已计划Res核心批次中选择这一个具体组合作为整体验收；**不新增队列请求**。原zero helper的tuple/分支风险、BNcopy/RC与add成本全部留整模内；不叠加组件收益。READY.integration_candidate绑定各依赖哈希、原source11和donor53。单独BN及各方原版本都未改。

本方后续block2成本原型b5c20fde/253202B明确NativeOnly无correct，原GEMM/all12runtime不变，暂不排额外CI；有代数条件引理/9旧cell有限word状态证据，但不作新证明/速度。
