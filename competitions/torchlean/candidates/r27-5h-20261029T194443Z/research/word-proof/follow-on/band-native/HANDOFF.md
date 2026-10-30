# Band cost follow-on

Prepared before the R27 23:20 freeze, in a separate directory. This is not a
request to alter the current frozen batch8 candidates or their confirmation.
It uses only the earlier public23 source, R26 band idea and old seen formula
inputs. No confirmation data has been read to select this source.

`build_band_native.py` reconstructs **253142B/b8eade4e...f2287**, with 2858B
free under the original cap. The new fragment is 4822B. Original static
intake/policy passes. All old declarations remain; retainedCorrect proves
retainedKernels only, and the actual new kernels has **no correct**. Nothing
has been compiled or measured. Whole upstream source stayed in memory.

This differs from D's existing-cache block16 experiment. It explicitly prepares
UInt32 weight factors and groups each input row into four-exponent bands.
Four output columns share each gathered input/index load. Products accumulate
in 64-term signed blocks, then use two-word carry/shift. Existing Yp/Yu,
YL/YD and Yai supply the bias-aware terminal and exact-zero fallback. The last
outW%4 columns and all rejected layers use public23 paths.

`native-shape-replay.json` uses the literal old Yc metadata convention, ascending
bands, word carry/shift and original tail scheduling. Six old complete formula
cells match prior outputs: 8856 grouped dots and54 original tail dots. All
selected cells satisfy the whole-layer guard. This is finite Python evidence;
four-lane Lean code, getters, allocation, rounding linkage and performance are
unverified. The replay does not turn these seen inputs into confirmation data.

Main risks: Nat recursion remains inside sum4; extra weight preparation and
gathers may erase the carry savings; four-column sharing loses the old
four-row weight reuse. UInt32 array entries remain pointer-sized. Cost must
include all metadata, pair guards, preparation, group arrays, output drops and
fallbacks. No speed claim follows from counts or source shape.

Next-round choice only: first compile this exact native-only source, fix its
smallest actual error if any, and measure the complete normalized_mlp call
against the then-current champion via an honest exact-version comparator.
Only a useful measured result justifies actual partition/getter/carry proofs.
