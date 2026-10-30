# B7 terminal review

Run `40969380731`, source commit `88845d13a8a2ddfde1deda4e5d89d21eeb5d6dc7`, is terminal. The parent checkpoint at `23:02:24Z` records the B7 result and moves the work state to B8. The independent audit [audit-native-run-40969380731.json](audit-native-run-40969380731.json) confirms the raw input, candidate, and paired runner evidence with the pinned R25 scorer.

## Evidence and correctness boundary

The artifact passes 52/52 outer and 51/51 inner file hashes. The dispatch binds the exact B7 plan, runner, patch, official head `27fb1d19c712ead50ad34b4ad0d4ba597161e616`, and public `allow_private=false` run. Public #27 bytes match their saved receipt and planned SHA-256 `f92ee2c9…3481aa67`. The candidate transform recreates SHA-256 `d6294bba2fc3808fabfbd38ed14452403f9fc574b34beff6565fa1aac57e6415` at 255,757 bytes. MainExact hash is `b324bad32bc4ce449eb69be00e252163b77de4a0295736debe4081b53c4681ab`; compile, link, and response files match after target-name mapping.

The plan set `full_gate=false`. The runner compiled and measured the adaptive candidate, but no original all12 gate ran. Its proof status is `DECLARED_CORRECT_TYPECHECKED_NO_FULL_ORIGINAL_REPLAY`; it is not Correct.

## Native result versus current mixer #36

The candidate completed 180 paired rows for each of seeds `27102971` and `27102973` on the same local x86_64 runner. The pinned scorer independently reproduces candidate/public27 time `1.0251530320672158`; all 360 paired checksums agree, the five-round order alternates, and the compiler/linker/response flags match after target mapping.

The saved official #36/#27 report ratio is `0.9622181669992014`, but its config hash predates the current mixer board config. Converting the local screen through that report gives **1.065406025x current #36 time**, INFERRED across benchmark version, environment, and seeds; it is slower than the champion. The strict converter remains UNKNOWN because the #36 report is old-policy and the B7 cohort is local 5×3×2 ms rather than the two production report runs. The latest champion source is unavailable, and #27 remains a retired calibration carrier.

This is a negative result for the adaptive row-selector direction. The parent request records no further rows/columns variant queue; subsequent effort should use a different mechanism or the separately frozen FP/block16 cost routes.
