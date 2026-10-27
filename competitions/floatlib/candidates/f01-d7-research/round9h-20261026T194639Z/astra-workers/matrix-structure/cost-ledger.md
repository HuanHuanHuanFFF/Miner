# Exact source costs that can affect the first decision

The original B2 scalar-field C and fixed 64-bit runtime imply a conditional record+pointer-slot request model of 24n bytes per tile. The temporal representation would request 48·ceil(n/4), **if** its selected C is one 32-byte-payload B8 per block. Inner/outer array headers and closure allocation remain and are excluded from this comparison. It is not a physical allocator or elapsed-cost model.

The tail matters. At n=2, old and new both request 48 bytes per tile: fewer records do not reduce these bytes, and the new record has four padded fields. At n=3 the requests are 72→48; at n=4, 96→48; at n=5, 120→96. The source still performs exactly the old valid B decode count and adds conditional padding stores. The first full path must include those costs.

`cost_snapshot.py` rehashed original plan/work/verdict bytes from the three already-completed retained B2 groups before computing `cost-snapshot.json`. It does not open any R19 confirmation input. Counts assume the selected shape misses UnderflowZero; actual hit frequency and target-only time are UNKNOWN.

| Completed source sample | Selected shapes / n2 shapes | Packet+slot requests old→new | Packet records old→new | Numeric packet reads old→new | Unchanged output finishes |
| --- | ---: | ---: | ---: | ---: | ---: |
| R15 D / 1526007 | 9 / 2 | 1882920→1229904 B | 78455→25623 | 682982→216456 | 268121 |
| R15 A / 1526101 | 12 / 1 | 2516208→1400256 B | 104842→29172 | 808548→241084 | 229443 |
| R15 B / 1526102 | 14 / 0 | 3952992→2111568 B | 164708→43991 | 1108785→308930 | 184796 |

Each count is one logical plan evaluation, not 25 rounds or measured allocation. The prepared native scalar count and raw-A conversion count do not fall. The new padded field counts are 48074/23692/22512. Actual C may retain more live fields across the external decoder and thus add spills. Earlier B2 C's inner preparation closure captures four objects; the new source also needs n for padding, so closure size is not assumed unchanged before observing its C.

This makes the narrow experiment concrete: first determine whether packet/loop savings exceed extra preparation checks/padding/live-state cost. It does not justify a 10% whole prediction. Whole-time upper bounds from touched historical cells are 14.77/17.15/19.06%; target-only lower bounds remain zero, and these class bounds cannot attribute time to preparation or imply all touched work is removed.

No predicate change follows from these observations. Exact c70c stays fixed for its first real source feedback; a future combination needs its own frozen source and original gate.
