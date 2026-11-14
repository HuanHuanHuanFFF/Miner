# Preparation discriminator for the frozen band source

The source b8eade4e remains unchanged. This note uses its pre-freeze code and
old seen group sizes; it does not select a variant from any confirmation data.

`row` currently stores an Array of Arrays of UInt32 pairs. The pair is created
once per nonzero input, not per MAC. The hot consumer retrieves that pair and
then its index and factor. The physical pair representation and any compiler
elimination must be checked in emitted code; the source alone does not show
two dense four-byte arrays. Pointer-sized outer entries and possible pair
objects can exceed the footprint of separate factor/index arrays.

There is a second unresolved ownership issue. The expression reads gs[band],
pushes into that inner array, then replaces the outer entry. If the inner
array is still shared while push executes, it may copy its prior elements.
For a group of g inputs, that path could copy g*(g-1)/2 entries over its
construction. This is a conditional cost model, not an observed allocation
count: Lean ownership analysis may improve the code. Do not call the actual
preparation O(n) until this has been resolved from generated code or runtime
evidence.

A separate next implementation, only if the first cost makes it worthwhile,
can count group sizes, compute prefix offsets, then fill flat UInt32 factors
and indices in a second input pass. This matches the R26 flat group interface
and removes nested inner-array growth. It adds prefix/fill invariants to the
proof and does not by itself establish a native speed advantage. The current
frozen source is not silently replaced with that design.

First measurement remains the complete model call. If it is disappointing,
an isolated preparation/body diagnostic should distinguish group allocation,
weight preparation and hot gather costs before rejecting exponent grouping
as a mechanism. Include output destruction in the complete-call result, keep
instrumented binaries separate, and retain both positive and slow samples.
