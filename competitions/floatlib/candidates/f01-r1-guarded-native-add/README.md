# 受保护的原生加法桥接

冻结 SHA-256 `aa24752887de02da3bf89871afbf9a7e2cae2e821bef4ca1023642e603cc8177`，33959 字节。仅用 pinned FloatLib 的公开 `ofFloat32_add_of_isFinite` 定理；实际 guard 检查 native finite 与 raw 位往返，其他输入仍旧加法。

四义务证明草稿已写，NOT_COMPILED；传递公理审计和性能 NOT_RUN。不得在完整 gate 前认定合法可用或已提速。来源与采用优先级见 research/astra-collab-20261021/checkpoint-03.md。
