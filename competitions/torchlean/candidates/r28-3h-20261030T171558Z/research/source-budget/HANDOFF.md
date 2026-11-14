# Mobile53证明拼写预算

原创`compact53.py`已经从精确public53生成`2c7365276a8b6d96528a558c08458aca6954e1948d718af195ae69eb4d9ed48e`，**252559B、余3441B、释放3422B**；完整重建源仅private/。保持所有证明，不增加公理，不改runtime函数/算术。只对现有长lemma标识作无捕获全局更名、在lemma/theorem内复用现有类型notation；字符串、嵌套注释、qualified名跳过。更名全局逆变换逐字节相同，158段runtime声明经更名后仍逐字节未动。

**尚未编译、尚未原all12 gate、无性能声明**。这是给Mobile机制腾挪空间的配方，不请求单独占CI。请B按需在新补丁最后调用`build(patched_raw, strict_base=False)`；全局默认`build(raw)`严格绑定public53哈希。新补丁如果需要原长lemma名，先接线后压缩；新组合必须新hash与原gate。API `transform(raw,53,'proof-compact53')`可给D适配器；无外部依赖，已运行两次确定性重建可在receipt查。

源码许可未知整源不发布；公开本原创配方和receipt。其他来源禁止直接套strict-base接口，除非独立核实其notation上下文。
