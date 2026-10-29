# TorchLean 当前交接

Droot唯一Git/公共CI负责人；分支huan/codex-gpt。主攻overall冠军。R26共同窗口UTC2026-10-29 **08:55:15—09:55:15**已完成，到期停止新研究；最后已启动CI09:59:57结束并收齐，全部3run终态。初始唤醒后严格文件通信，阻塞/收尾均不直接发消息；下轮遵守用户最新指令。

当前入口：[R26结果](../candidates/r26-1h-20261029T085515Z/README.md)、[实际状态](../candidates/r26-1h-20261029T085515Z/development-status.json)、[固定版本](../pins.json)、[保留版](../retained.json)。本机不编Lean。正式参赛/资金另核授权。

新原型fp-word-conv6/ad9bde3e，公共CI40852769757/source12e6d73f，原MainExact字节和同等编译参数，2seed×6workload×30cells×5round，共1800配对checksum一致。对保留版耗时overall0.7854、ResNet0.4646、MobileNet0.5845；batch1 MLP2.9905、normalized_mlp1.9766，原1.10逐项guard失败。原型无完整Submission.correct；未采纳，R25/bcb817保留版不变。原gate只重放保留参照，不能把CI成功说成新原型完整gate通过。

根看板同时给保留版/原型的冠军耗时估算：overall15.9→12.5倍；冠军快照仍10月29日04:49，Mixer现任未知。推算参照与原始报告链见R26/native-summary.json，未使用微基准冒充冠军成绩。

下一决定：保留卷积2.15×与大批量路径，先判别小批量准备/转置和每dot扫描成本；探索word-block/官方终端舍入以减少证明前提。小证明core应独立编译和保存完整stdout，避免依赖长benchmark前段。研究入口在R26/research/HANDOFF.md；旧key/finite的完整8条error标题及原goal已经由最后CI回收，路径/hash在R26/CI-RESULTS-BATCH3.json。研究子角色截止时的UNKNOWN是当时状态，最终实测以R26当前结果为准。

本轮前两次失败系Droot bridge依赖与启动guard错误，未编译候选，不是算法反例。原始失败/负结果、全C/ASM/逐项数据均保存，CI附件之外有入库字节和哈希。原contracts/gate/bench/pins不变。R24 word循环原已标量化，本轮贡献是完整模型接入；RNE端点反例已否定旧包围假设。详细证明按角色入口加载，无新增Lean接受。
