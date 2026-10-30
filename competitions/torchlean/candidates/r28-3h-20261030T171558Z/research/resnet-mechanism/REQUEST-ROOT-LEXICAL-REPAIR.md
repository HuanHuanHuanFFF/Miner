> Spatial-v2 f59 was subsequently superseded by parser-spacing repair spatial-v3 **5a43cf03**. The support-v3 **00928141** branch remains current. Use current READY.json; historical one-space receipt remains unchanged.

# Cost prototypes: use the one-character lexer repairs before any new dispatch

Pinned Lean4.34 `Init/Meta/Defs.lean` blob201680de… defines `isIdRest` to include `!`; `Parser/Basic.lean` blob0e135176… consumes that maximal run. Thus old support `if v!=…` names `v!`, and old spatial `Yf w!=0` names `w!`. This is an identified source-level lexical defect, not a native result. Primary c6a4da97 has no such finding.

Old a498d9b7 and8e5b27c0 sources/builders remain byte-identical. New `build_lexical_repair.py` supports **packed-support11-v3** and **spatial11-native-v2** and inserts exactlyone ASCIIspace before the sole affected `!=`. `lexical-repair-receipt.json` pins exact newhash/size and every dependency. Input arithmetic, guard intent, memorylayout, source-byte cap and lack of newcorrect are unchanged. Use at mostone version of each mechanism; no extra experimental family is requested.

The wrapper must have its pinned sibling builders/runtime/compact files available (listed in receipt), or be used in its original repository directory. It refuses dependency drift and verifies both old and repaired source hashes/byte deltas. Repaired owned runtime excerpts are separately materialized; old excerpts remain historical.

**declares_correct=false,full_gate=false** still mandatory. No all12 or native claim. If an old version was already started, do not cancel or edit its plan; retain its actual result and use repair only for a later authorized dispatch. No frozen confirmation input/result informed this change.
