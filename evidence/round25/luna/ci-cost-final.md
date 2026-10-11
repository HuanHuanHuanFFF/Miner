# Round 25 CI 实际消耗审计（收尾检查点）

范围覆盖34份dispatch及各自唯一匹配的原始`ci-run.json`；不联网、不轮询/启动CI、不访问私密材料，也不估算账单金额。仅额外核对#38131861001的失败自定义receipt与日志。

**统计口径：**仅将每个CI回执中非skipped job的原始`startedAt → completedAt`差值计为实际runner job wall；队列为`ci-run.createdAt → 最早非skipped job startedAt`。setup和checkout包含在job wall中，因此这不是候选CPU耗时。timeout仅保留为配置上下文，完全不计入实际消耗。每个run均只有一个非skipped job，所以“逐run job wall之和”与“runner累计时间”相等。

## 总览

- 覆盖：dispatch 34，唯一run 34，raw CI receipt 34；缺失/重复：0/0。
- 状态：成功 30，失败 4，取消 0，未收齐 0。
- 实际job：34个；逐run job wall合计 12075s / 201.25min；runner累计 12075s / 201.25min；queue合计 114s / 1.90min。
- 原始UTC时间边界：`2026-10-11T08:17:54Z` → `2026-10-11T11:43:35Z`，差值 12341s / 205.68min；这是源时间轴跨度，含空档/并行，不代表runner消耗。
- Skipped job排除 340个，其中倒序interval 203个、时间缺失 0个。

## 按模式汇总

| 模式 | Runs | 成功 | 失败 | 取消 | 未收齐 | 实际job | queue合计 | runner job wall |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| native | 16 | 15 | 1 | 0 | 0 | 16 | 53s (0.88m) | 630s (10.50m) |
| standard | 12 | 9 | 3 | 0 | 0 | 12 | 40s (0.67m) | 7959s (132.65m) |
| extract | 4 | 4 | 0 | 0 | 0 | 4 | 13s (0.22m) | 1587s (26.45m) |
| gate | 2 | 2 | 0 | 0 | 0 | 2 | 8s (0.13m) | 1899s (31.65m) |

## 逐run原始回执

SHA-256为完整值；时间保留raw source字符串。每行同时列出dispatch到CI created、created到job start的差值。失败步骤与full-gate step按CI job receipt中的step结论直录。
### #38124303645 quality-a-native — native / success

- 实际job wall: 40.0s；queue: 3.0s；job区间: `2026-10-11T08:17:54Z` → `2026-10-11T08:18:34Z`。run createdAt `2026-10-11T08:17:51Z`。
- dispatch→created: 2.053083s；created→job start: 3.000s；dispatch→job start: 5.053083s。dispatch_utc `2026-10-11T08:17:48.946917+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38124303645.json` SHA-256 `b8aa410433821746d9ed908df9c958091f3dbc127559f04ffd792d2616cbce9b`。
- CI/job receipt: `evidence/round25/38124303645/quality-a-native/diagnostics/ci-run.json` SHA-256 `fd99e14e7edf8fe89b969ce37621c097528f49a8de4436cee3af9eb3d4f47bd3`。

### #38124524718 screen-a — standard / success

- 实际job wall: 568.0s；queue: 3.0s；job区间: `2026-10-11T08:21:43Z` → `2026-10-11T08:31:11Z`。run createdAt `2026-10-11T08:21:40Z`。
- dispatch→created: 2.804446s；created→job start: 3.000s；dispatch→job start: 5.804446s。dispatch_utc `2026-10-11T08:21:37.195554+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38124524718.json` SHA-256 `bc8fde56fd859a36f80e7fb1e17d721a05a2a0f01b57a7465299a76123702bb0`。
- CI/job receipt: `evidence/round25/38124524718/screen-a/gate/ci-run.json` SHA-256 `0c5f9db4a82a7849090fce3bd1de9bddef71067f5b0a464c849cb9cbc94fc3c6`。

### #38124536539 proof-a-extract — extract / success

- 实际job wall: 427.0s；queue: 3.0s；job区间: `2026-10-11T08:21:55Z` → `2026-10-11T08:29:02Z`。run createdAt `2026-10-11T08:21:52Z`。
- dispatch→created: 2.147907s；created→job start: 3.000s；dispatch→job start: 5.147907s。dispatch_utc `2026-10-11T08:21:49.852093+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38124536539.json` SHA-256 `b7b68642d8992ee1f847393e0d6c4766468347ed296b1ed2ebdba82c02f16b18`。
- CI/job receipt: `evidence/round25/38124536539/proof-a-extract/diagnostics/ci-run.json` SHA-256 `e8cf2b0e8d85e10765e06ba36c0710451e05773d058eafa6be0587af647e8354`。

### #38124984085 quality-b-native — native / success

- 实际job wall: 42.0s；queue: 3.0s；job区间: `2026-10-11T08:29:38Z` → `2026-10-11T08:30:20Z`。run createdAt `2026-10-11T08:29:35Z`。
- dispatch→created: 2.480449s；created→job start: 3.000s；dispatch→job start: 5.480449s。dispatch_utc `2026-10-11T08:29:32.519551+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38124984085.json` SHA-256 `d860f354bba2fc1cbc218029b8d85805267bbc93870da5397100b8f4fec33d68`。
- CI/job receipt: `evidence/round25/38124984085/quality-b-native/diagnostics/ci-run.json` SHA-256 `7f7687b083f3fe0ffc7e8fb3cc7df217749786d904e0942da2e919a555ad3c23`。

### #38125243582 gate-end4 — gate / success

- 实际job wall: 965.0s；queue: 3.0s；job区间: `2026-10-11T08:33:53Z` → `2026-10-11T08:49:58Z`。run createdAt `2026-10-11T08:33:50Z`。
- dispatch→created: 1.700631s；created→job start: 3.000s；dispatch→job start: 4.700631s。dispatch_utc `2026-10-11T08:33:48.299369+00:00`。
- CI步骤失败: 无；original full public gate step: success。
- Dispatch: `evidence/round25/dispatch-38125243582.json` SHA-256 `be56b36c28359a3a8c119b52c4585b70aae73f8550ea4360e9190a8adf64aaeb`。
- CI/job receipt: `evidence/round25/38125243582/gate-end4/exact-gate/ci-run.json` SHA-256 `cac0e3425aebb5666f650d1d9811a74f56d11cc96d62e1341fc56ae92e5867e4`。

### #38125636793 quality-c-native — native / success

- 实际job wall: 43.0s；queue: 3.0s；job区间: `2026-10-11T08:40:33Z` → `2026-10-11T08:41:16Z`。run createdAt `2026-10-11T08:40:30Z`。
- dispatch→created: 2.471364s；created→job start: 3.000s；dispatch→job start: 5.471364s。dispatch_utc `2026-10-11T08:40:27.528636+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38125636793.json` SHA-256 `c1169ed12fe5ae906286fcb8e9a40dfbced7d14161dcc8d86dc391843d0ab7d2`。
- CI/job receipt: `evidence/round25/38125636793/quality-c-native/diagnostics/ci-run.json` SHA-256 `3aa6247c92a46e04baab46d42fd787c6fdc1f43fcdc1fd2613c59cb1deff2959`。

### #38126014186 screen-c — standard / success

- 实际job wall: 790.0s；queue: 7.0s；job区间: `2026-10-11T08:46:55Z` → `2026-10-11T09:00:05Z`。run createdAt `2026-10-11T08:46:48Z`。
- dispatch→created: 2.355969s；created→job start: 7.000s；dispatch→job start: 9.355969s。dispatch_utc `2026-10-11T08:46:45.644031+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38126014186.json` SHA-256 `618fcd2baf28d79f295d09c66faa60e72835bbcd8ce9c3fe28cd418b9790f015`。
- CI/job receipt: `evidence/round25/38126014186/screen-c/gate/ci-run.json` SHA-256 `5d4027f9bfa1fb2c8d2508cc116abb56effff57a1781e0b142204cf2fc48c617`。

### #38126033837 proof-c-extract — extract / success

- 实际job wall: 371.0s；queue: 3.0s；job区间: `2026-10-11T08:47:11Z` → `2026-10-11T08:53:22Z`。run createdAt `2026-10-11T08:47:08Z`。
- dispatch→created: 2.840244s；created→job start: 3.000s；dispatch→job start: 5.840244s。dispatch_utc `2026-10-11T08:47:05.159756+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38126033837.json` SHA-256 `ca3d017e8ba0464454b29edccf4605e43e9878646b0153681bb12210b5c158c1`。
- CI/job receipt: `evidence/round25/38126033837/proof-c-extract/diagnostics/ci-run.json` SHA-256 `8d3829d24d2ebe53d229bb48e7d7598e28815e34750b07f43f5df3fca0ce7985`。

### #38126399623 quality-d-native — native / success

- 实际job wall: 47.0s；queue: 4.0s；job区间: `2026-10-11T08:53:24Z` → `2026-10-11T08:54:11Z`。run createdAt `2026-10-11T08:53:20Z`。
- dispatch→created: 1.741226s；created→job start: 4.000s；dispatch→job start: 5.741226s。dispatch_utc `2026-10-11T08:53:18.258774+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38126399623.json` SHA-256 `bd37396361638a2605f4755f8d4fd75f046f491de50fa3c6403fe1b4950fe9fb`。
- CI/job receipt: `evidence/round25/38126399623/quality-d-native/diagnostics/ci-run.json` SHA-256 `3711f9fb8c5490bcd77c3bbe39d4d2decb79490efaecdb6a7454943018bf68fb`。

### #38126675905 screen-d — standard / success

- 实际job wall: 691.0s；queue: 3.0s；job区间: `2026-10-11T08:58:08Z` → `2026-10-11T09:09:39Z`。run createdAt `2026-10-11T08:58:05Z`。
- dispatch→created: 1.878399s；created→job start: 3.000s；dispatch→job start: 4.878399s。dispatch_utc `2026-10-11T08:58:03.121601+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38126675905.json` SHA-256 `d824166a1bf9d6ca342c4d84d5e899e0bdf5b5ccc2ae2804a820fb85bd3ab0ce`。
- CI/job receipt: `evidence/round25/38126675905/screen-d/gate/ci-run.json` SHA-256 `90d7852fa93998baccff5f44a1e8fea211392ac35fea6616b46cfed53ff4d67d`。

### #38127500920 counts-e-native — native / success

- 实际job wall: 32.0s；queue: 3.0s；job区间: `2026-10-11T09:11:50Z` → `2026-10-11T09:12:22Z`。run createdAt `2026-10-11T09:11:47Z`。
- dispatch→created: 2.245610s；created→job start: 3.000s；dispatch→job start: 5.245610s。dispatch_utc `2026-10-11T09:11:44.754390+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38127500920.json` SHA-256 `85343661800bf4407e433ed2157cb9cb72f5d4209f44592a5e5eaa9d6379be68`。
- CI/job receipt: `evidence/round25/38127500920/counts-e-native/diagnostics/ci-run.json` SHA-256 `61bb76cf6b29b7474cc70165db300c9e3a945cfb197cdb9e6392af5ee5088d41`。

### #38128787484 origins-f-native — native / success

- 实际job wall: 35.0s；queue: 3.0s；job区间: `2026-10-11T09:33:24Z` → `2026-10-11T09:33:59Z`。run createdAt `2026-10-11T09:33:21Z`。
- dispatch→created: 2.228770s；created→job start: 3.000s；dispatch→job start: 5.228770s。dispatch_utc `2026-10-11T09:33:18.771230+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38128787484.json` SHA-256 `91fc9b2c0375216dc8be742208b3a3c1e05c17d65e78fa3debdfad5403704aa7`。
- CI/job receipt: `evidence/round25/38128787484/origins-f-native/diagnostics/ci-run.json` SHA-256 `77a5e83112966981c062bb24d2e0e5e5f00d568623d223376059fcc4b50179b1`。

### #38129145575 prefix-g-native — native / success

- 实际job wall: 36.0s；queue: 4.0s；job区间: `2026-10-11T09:39:29Z` → `2026-10-11T09:40:05Z`。run createdAt `2026-10-11T09:39:25Z`。
- dispatch→created: 1.934324s；created→job start: 4.000s；dispatch→job start: 5.934324s。dispatch_utc `2026-10-11T09:39:23.065676+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38129145575.json` SHA-256 `5bb8dc9bf9b7a1ff3ff07ae84337d194f72ad51f51781cabc7478a2b4d2fe1b6`。
- CI/job receipt: `evidence/round25/38129145575/prefix-g-native/diagnostics/ci-run.json` SHA-256 `cd4a356a009433b3b8f1a34b4f44e95ffd40e8b6b3148c60fa93f4f18c589473`。

### #38129274435 quality-h-native — native / success

- 实际job wall: 47.0s；queue: 3.0s；job区间: `2026-10-11T09:41:36Z` → `2026-10-11T09:42:23Z`。run createdAt `2026-10-11T09:41:33Z`。
- dispatch→created: 2.433507s；created→job start: 3.000s；dispatch→job start: 5.433507s。dispatch_utc `2026-10-11T09:41:30.566493+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38129274435.json` SHA-256 `c706344518af0afa9949cc06e4d8c71f54a7a55b1ed39d85ef720ed917c9f4f9`。
- CI/job receipt: `evidence/round25/38129274435/quality-h-native/diagnostics/ci-run.json` SHA-256 `7c53d7d2f717af0f9c6143fe9d379773ee2c5756c0572b9053f260ada024a186`。

### #38129545231 quality-i-native — native / success

- 实际job wall: 41.0s；queue: 3.0s；job区间: `2026-10-11T09:46:09Z` → `2026-10-11T09:46:50Z`。run createdAt `2026-10-11T09:46:06Z`。
- dispatch→created: 2.257802s；created→job start: 3.000s；dispatch→job start: 5.257802s。dispatch_utc `2026-10-11T09:46:03.742198+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38129545231.json` SHA-256 `2b3b0db3974c38f2795fb4695947bf61dd2ef9a982d1cb4e3a4dddbc04bcb18b`。
- CI/job receipt: `evidence/round25/38129545231/quality-i-native/diagnostics/ci-run.json` SHA-256 `065b4d0e1c4baee309aa638bcfd542faacbbbfcfae2c65c8f9c89e8ec8836b14`。

### #38130275592 screen-hi — standard / success

- 实际job wall: 809.0s；queue: 3.0s；job区间: `2026-10-11T09:58:37Z` → `2026-10-11T10:12:06Z`。run createdAt `2026-10-11T09:58:34Z`。
- dispatch→created: 2.760460s；created→job start: 3.000s；dispatch→job start: 5.760460s。dispatch_utc `2026-10-11T09:58:31.239540+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38130275592.json` SHA-256 `f7a84efec02d060c933d1c3c992d81c0564bcc0fd1524fc1549ec3f93324354d`。
- CI/job receipt: `evidence/round25/38130275592/screen-hi/gate/ci-run.json` SHA-256 `4bd2d047ff7dc28dd671656d97c62cd6d7f266b4fefcbc5e6ff2c35b08c7440f`。

### #38130286911 proof-i-extract — extract / success

- 实际job wall: 388.0s；queue: 4.0s；job区间: `2026-10-11T09:58:50Z` → `2026-10-11T10:05:18Z`。run createdAt `2026-10-11T09:58:46Z`。
- dispatch→created: 2.290579s；created→job start: 4.000s；dispatch→job start: 6.290579s。dispatch_utc `2026-10-11T09:58:43.709421+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38130286911.json` SHA-256 `a0d4806a84120c6a8e5e5ae772f21ea001366e7be6054ce55140c668cb487bcb`。
- CI/job receipt: `evidence/round25/38130286911/proof-i-extract/diagnostics/ci-run.json` SHA-256 `60b79df774bbf4e86605b376e8badc9be88d71424a509604d1539dd5857a87c4`。

### #38130296690 quality-j-native — native / success

- 实际job wall: 33.0s；queue: 3.0s；job区间: `2026-10-11T09:59:00Z` → `2026-10-11T09:59:33Z`。run createdAt `2026-10-11T09:58:57Z`。
- dispatch→created: 2.802010s；created→job start: 3.000s；dispatch→job start: 5.802010s。dispatch_utc `2026-10-11T09:58:54.197990+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38130296690.json` SHA-256 `d0933abff10d2c1d65325128b49b619cdde1b0b90e3c6b562e7d134538209ae0`。
- CI/job receipt: `evidence/round25/38130296690/quality-j-native/diagnostics/ci-run.json` SHA-256 `a10dbcb2438eb1cb4636d83239e768085b5927e13b1e52bd97e33ea573946e45`。

### #38130458692 screen-j — standard / success

- 实际job wall: 694.0s；queue: 3.0s；job区间: `2026-10-11T10:01:30Z` → `2026-10-11T10:13:04Z`。run createdAt `2026-10-11T10:01:27Z`。
- dispatch→created: 2.238026s；created→job start: 3.000s；dispatch→job start: 5.238026s。dispatch_utc `2026-10-11T10:01:24.761974+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38130458692.json` SHA-256 `c84310a029c7d5e7774c73bcff53341f44721c224c4072b0348a1f9f242ab785`。
- CI/job receipt: `evidence/round25/38130458692/screen-j/gate/ci-run.json` SHA-256 `3b587b693ae51dc26c3a4f97dc08bae2724dd35ad5bbf446a760099798dc1b95`。

### #38130996700 gate-tiny-pc8-proof1 — gate / success

- 实际job wall: 934.0s；queue: 5.0s；job区间: `2026-10-11T10:10:31Z` → `2026-10-11T10:26:05Z`。run createdAt `2026-10-11T10:10:26Z`。
- dispatch→created: 2.401236s；created→job start: 5.000s；dispatch→job start: 7.401236s。dispatch_utc `2026-10-11T10:10:23.598764+00:00`。
- CI步骤失败: 无；original full public gate step: success。
- Dispatch: `evidence/round25/dispatch-38130996700.json` SHA-256 `f21a60ab9a6cef6805c4769610eb2f4c82db6c3f7d939c8bc6964fb694a67cdf`。
- CI/job receipt: `evidence/round25/38130996700/gate-tiny-pc8-proof1/exact-gate/ci-run.json` SHA-256 `3bd364bbd36e276e249f5bcc5927f1c168d08a6426135e7c0b27f283842fa311`。

### #38131861001 counts-k-native — native / failure

- 实际job wall: 22.0s；queue: 4.0s；job区间: `2026-10-11T10:24:57Z` → `2026-10-11T10:25:19Z`。run createdAt `2026-10-11T10:24:53Z`。
- dispatch→created: 2.493401s；created→job start: 4.000s；dispatch→job start: 6.493401s。dispatch_utc `2026-10-11T10:24:50.506599+00:00`。
- CI步骤失败: Validate frozen inputs and workflow route；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38131861001.json` SHA-256 `cf874b611eb3c28596219cf74f51cf344ab33e32407d776c393cc5c86697ae34`。
- CI/job receipt: `evidence/round25/38131861001/counts-k-native/failed-setup/ci-run.json` SHA-256 `200c669e774758c524c571fc199089cc9f994d7178a83776bd7bf67639eef1f3`。
- Custom failure evidence: `evidence/round25/38131861001/counts-k-native/failed-setup/receipt.json` SHA-256 `140c37408a64f4a7b7554677fab457952966c54307a95dd03273d987360c7721` (386 B).
- Custom failure evidence: `evidence/round25/38131861001/counts-k-native/failed-setup/ci-failed.log` SHA-256 `7f53cf0bdc387d093408be538b2a25b9819f7656b7150b4cf7e72b18710a7eb6` (3124 B).

### #38132193695 counts-k2-native — native / success

- 实际job wall: 33.0s；queue: 4.0s；job区间: `2026-10-11T10:30:34Z` → `2026-10-11T10:31:07Z`。run createdAt `2026-10-11T10:30:30Z`。
- dispatch→created: 2.365868s；created→job start: 4.000s；dispatch→job start: 6.365868s。dispatch_utc `2026-10-11T10:30:27.634132+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38132193695.json` SHA-256 `33b2f72a5a8262080752e6e5898a81114ceac73eb62a4a867db5b29cf38ebe9f`。
- CI/job receipt: `evidence/round25/38132193695/counts-k2-native/diagnostics/ci-run.json` SHA-256 `c9d698e6c49a4d383e23fc1ae7d7c748286ae918a13ab107a2fa4c0086c105aa`。

### #38132209168 price-l-native — native / success

- 实际job wall: 47.0s；queue: 3.0s；job区间: `2026-10-11T10:30:47Z` → `2026-10-11T10:31:34Z`。run createdAt `2026-10-11T10:30:44Z`。
- dispatch→created: 1.947375s；created→job start: 3.000s；dispatch→job start: 4.947375s。dispatch_utc `2026-10-11T10:30:42.052625+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38132209168.json` SHA-256 `cef3f187de605409b75a7de53e84c71508c7fc86afd3aec2086d55634cb07182`。
- CI/job receipt: `evidence/round25/38132209168/price-l-native/diagnostics/ci-run.json` SHA-256 `998e9463162023b6a4c7b7341a1959749c311f7edfdb50a24478c83e87bcb00a`。

### #38132623194 quality-m-native — native / success

- 实际job wall: 44.0s；queue: 3.0s；job区间: `2026-10-11T10:37:43Z` → `2026-10-11T10:38:27Z`。run createdAt `2026-10-11T10:37:40Z`。
- dispatch→created: 2.649417s；created→job start: 3.000s；dispatch→job start: 5.649417s。dispatch_utc `2026-10-11T10:37:37.350583+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38132623194.json` SHA-256 `e06b2f7ea1660718cd695b89ab7bc06d4a19fe7b659e0618fc55edc40c879e1a`。
- CI/job receipt: `evidence/round25/38132623194/quality-m-native/diagnostics/ci-run.json` SHA-256 `16f15220ef94e12098e9f289f1e5c3aceaee2614ba60bf187867f727fd7d4dfd`。

### #38132849624 screen-m — standard / success

- 实际job wall: 781.0s；queue: 4.0s；job区间: `2026-10-11T10:41:31Z` → `2026-10-11T10:54:32Z`。run createdAt `2026-10-11T10:41:27Z`。
- dispatch→created: 2.250216s；created→job start: 4.000s；dispatch→job start: 6.250216s。dispatch_utc `2026-10-11T10:41:24.749784+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38132849624.json` SHA-256 `e2b1e0a9186a673acbd2d32723db732ef1dd39b80959b1139726181627261056`。
- CI/job receipt: `evidence/round25/38132849624/screen-m/gate/ci-run.json` SHA-256 `eb6f0d4a0f9aca01b3c68e25ae790fb2196d9d3fa7ad8d6126904f0ae7d10b5f`。

### #38132862529 proof-m-extract — extract / success

- 实际job wall: 401.0s；queue: 3.0s；job区间: `2026-10-11T10:41:43Z` → `2026-10-11T10:48:24Z`。run createdAt `2026-10-11T10:41:40Z`。
- dispatch→created: 2.490329s；created→job start: 3.000s；dispatch→job start: 5.490329s。dispatch_utc `2026-10-11T10:41:37.509671+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38132862529.json` SHA-256 `a26dcc6c6d963b0f3b15f97aaae882f0d995a5868e9f63a009c04e0be26d6924`。
- CI/job receipt: `evidence/round25/38132862529/proof-m-extract/diagnostics/ci-run.json` SHA-256 `d6ce8dd8c62641437fbbaf251990252d57e9cce762bb826eb5c5deb1e7ad3885`。

### #38134237148 quality-n-native — native / success

- 实际job wall: 46.0s；queue: 4.0s；job区间: `2026-10-11T11:04:35Z` → `2026-10-11T11:05:21Z`。run createdAt `2026-10-11T11:04:31Z`。
- dispatch→created: 2.040807s；created→job start: 4.000s；dispatch→job start: 6.040807s。dispatch_utc `2026-10-11T11:04:28.959193+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38134237148.json` SHA-256 `b47a0b6e292df6bb0cfd1ddb912f97e42e40114e3eba62a287ea1e0d35a19db1`。
- CI/job receipt: `evidence/round25/38134237148/quality-n-native/diagnostics/ci-run.json` SHA-256 `a86f77748158af7c2e9bc5fef2367ad03b5fd7131adaac8fe4c9690a2b1e9f43`。

### #38134540554 screen-nt — standard / failure

- 实际job wall: 353.0s；queue: 2.0s；job区间: `2026-10-11T11:09:40Z` → `2026-10-11T11:15:33Z`。run createdAt `2026-10-11T11:09:38Z`。
- dispatch→created: 3.397999s；created→job start: 2.000s；dispatch→job start: 5.397999s。dispatch_utc `2026-10-11T11:09:34.602001+00:00`。
- CI步骤失败: Run standard candidate checks and paired measurements；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38134540554.json` SHA-256 `254b3aa0229ea08f9944176eb7b65d156ffb8719489cb2a7d3a8766cde02a0b8`。
- CI/job receipt: `evidence/round25/38134540554/screen-nt/gate/ci-run.json` SHA-256 `135a578f19075006cb3213af86ae6c1fac4697d2323913001898902601415a79`。

### #38134827293 confirm-components-a — standard / failure

- 实际job wall: 412.0s；queue: 3.0s；job区间: `2026-10-11T11:14:27Z` → `2026-10-11T11:21:19Z`。run createdAt `2026-10-11T11:14:24Z`。
- dispatch→created: 2.998477s；created→job start: 3.000s；dispatch→job start: 5.998477s。dispatch_utc `2026-10-11T11:14:21.001523+00:00`。
- CI步骤失败: Run standard candidate checks and paired measurements；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38134827293.json` SHA-256 `9e86ebf8ad0a42dea7cf40fb027abdd41993f7269102e278ed61a89179683db6`。
- CI/job receipt: `evidence/round25/38134827293/confirm-components-a/gate/ci-run.json` SHA-256 `d03a0dd9586e176e2d356383fd22af4b7561e1c5598dbe632ec8f8945a0104df`。

### #38134842459 confirm-components-b — standard / failure

- 实际job wall: 354.0s；queue: 3.0s；job区间: `2026-10-11T11:14:43Z` → `2026-10-11T11:20:37Z`。run createdAt `2026-10-11T11:14:40Z`。
- dispatch→created: 3.269062s；created→job start: 3.000s；dispatch→job start: 6.269062s。dispatch_utc `2026-10-11T11:14:36.730938+00:00`。
- CI步骤失败: Run standard candidate checks and paired measurements；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38134842459.json` SHA-256 `f615ce7546edc1a581c1675c9947f87cbc68af162667535b874623e566e6cee2`。
- CI/job receipt: `evidence/round25/38134842459/confirm-components-b/gate/ci-run.json` SHA-256 `b6344001b67fb9dc1a597549a0a90493ffdc171539df98b01378e391565ca8b8`。

### #38135725985 screen-nt2 — standard / success

- 实际job wall: 825.0s；queue: 3.0s；job区间: `2026-10-11T11:29:12Z` → `2026-10-11T11:42:57Z`。run createdAt `2026-10-11T11:29:09Z`。
- dispatch→created: 2.872520s；created→job start: 3.000s；dispatch→job start: 5.872520s。dispatch_utc `2026-10-11T11:29:06.127480+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38135725985.json` SHA-256 `e8b4463d01685da3d97962b436d8c42877611bb3a258409eb4ece2f565c9762e`。
- CI/job receipt: `evidence/round25/38135725985/screen-nt2/gate/ci-run.json` SHA-256 `07de92fb3a60283750ba36771c1be53a86e003be0aaf802084fa7614da0e6b76`。

### #38135739022 confirm-components-a2 — standard / success

- 实际job wall: 845.0s；queue: 3.0s；job区间: `2026-10-11T11:29:25Z` → `2026-10-11T11:43:30Z`。run createdAt `2026-10-11T11:29:22Z`。
- dispatch→created: 3.086121s；created→job start: 3.000s；dispatch→job start: 6.086121s。dispatch_utc `2026-10-11T11:29:18.913879+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38135739022.json` SHA-256 `d233127334641e3a0c2aed70615731878da0848a62f167071428d3cdf44eb07b`。
- CI/job receipt: `evidence/round25/38135739022/confirm-components-a2/gate/ci-run.json` SHA-256 `d4e383795e181bddeae63c88b6cdea873c511a8c97baeb7f8500908b7bfce573`。

### #38135751559 confirm-components-b2 — standard / success

- 实际job wall: 837.0s；queue: 3.0s；job区间: `2026-10-11T11:29:38Z` → `2026-10-11T11:43:35Z`。run createdAt `2026-10-11T11:29:35Z`。
- dispatch→created: 2.438321s；created→job start: 3.000s；dispatch→job start: 5.438321s。dispatch_utc `2026-10-11T11:29:32.561679+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38135751559.json` SHA-256 `f22d8f42683b56419baf7758072723c30901b77da856f397676a6ec0e8eef252`。
- CI/job receipt: `evidence/round25/38135751559/confirm-components-b2/gate/ci-run.json` SHA-256 `64f354a95edf01400c14d508a088739ea7ae84c0f8d115983350f527a08861a8`。

### #38136091624 heldout-o-native — native / success

- 实际job wall: 42.0s；queue: 3.0s；job区间: `2026-10-11T11:35:03Z` → `2026-10-11T11:35:45Z`。run createdAt `2026-10-11T11:35:00Z`。
- dispatch→created: 2.682995s；created→job start: 3.000s；dispatch→job start: 5.682995s。dispatch_utc `2026-10-11T11:34:57.317005+00:00`。
- CI步骤失败: 无；original full public gate step: skipped。
- Dispatch: `evidence/round25/dispatch-38136091624.json` SHA-256 `d8d3f6ea036f81c509de1123a5e26bbf56691fed32f73344e863fca3ef8ec3a8`。
- CI/job receipt: `evidence/round25/38136091624/heldout-o-native/diagnostics/ci-run.json` SHA-256 `9d526442b2f8acbf4bbebd0ba580d2b744e01846108e33e4d777cdb4af04dde3`。

## 时间基准核对与旧报告更正

34份raw `dispatch_utc` 均带`+00:00`，对应`ci-run.createdAt`与非skipped job的`startedAt`均带`Z`。逐run顺序全部一致：dispatch→created为1.700631–3.397999s；created→job start为2–7s；dispatch→job start为4.700631–9.355969s。均无负差值。

工具UTC钟观察为`2026-10-11 11:58:58 UTC`；Windows本地钟为`2026-10-11T19:58:58.4313080+08:00`。最后一个raw job完成于`2026-10-11T11:43:35Z`，比工具UTC观察早923s。raw dispatch/CI时间链与当前工具UTC钟一致；没有证据支持raw数据本身存在8小时偏移。

旧派生检查点`evidence/round25/luna/ci-cost-checkpoint.json`所记的首末UTC为`2026-10-11T00:17:54Z`和`2026-10-11T02:13:04Z`；对应相同早期run集合的raw端点为`2026-10-11T08:17:54Z`和`2026-10-11T10:13:04Z`。旧派生JSON两端都早28800s，现明确撤回这两个旧派生端点作为时间依据；旧checkpoint文件本身未改。确切的旧转换错误原因仍为UNKNOWN，但该差异只在旧派生报告字段，不改变raw UTC链。

## 限制

这是云端CI实际job墙钟区间汇总，不是账单金额、benchmark有效测量时间、CPU时间或实验成功率。benchmark JSONL/副本与模型消耗由主线程处理，不在此重复计数。raw时间全局跨度只是source时间轴的差值，不能代替runner累计时间。
