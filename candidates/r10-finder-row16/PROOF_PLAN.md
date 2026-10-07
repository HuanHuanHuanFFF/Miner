# Row16 proof preparation

Status: UNADAPTED_PARENT_DRAFT. Current Parse.lean is a migration reference, not an accepted proof for changed source. Main thread owns native extraction and any later complete gate.

Helper obligations:

1. r10_row_tag: total for arbitrary packed bytes/slot; modulo bounds the index, shift is0 or4 and below8; return tag<16.
2. r10_row_store: row<4096, write<16, slot<65536; 16*row+write<=65535; cursor advance fits Usize; position arithmetic wraps U32 explicitly; victim/tag need no truth invariant.
3. r10_row_insert_pos: preserve H3/H4 LeAll<=B and previous-head c3,c4<=B from parent. Row return values are untrusted. Its return tuple and mutable array list change.
4. r10_row_insert_range_loop: preserve H3/H4 bounds for the same inserted positions; measure to-q. Three row arrays carry no content invariant.
5. r10_row_walk: measure16-step; invariant step<=16 and best0<=best<=cap. k-=1 only under k>0. Guard old>0 and old-as-usize<=i gives c=old-1<i, satisfying probe_spec. Original cap/input/nc<15 bounds handle remaining arithmetic and indexing.

For D, remove H7 head7/prev7 state and LeAll head7 invariant; add positions/tags/cursor. Net carried-state increase is expected to be1, but use actual extraction. Preserve H3/H4 and position/continuation bounds. Bind actual wrapper, row-walk and inserted-range returns. Keep original parse validity theorem and checked emitters unchanged.

Ring order, tag accuracy and history capacity are algorithmic quality properties checked by the finite model and later native measurements. They are not axioms: planned matches stay untrusted, and query/emission enforce byte validity. Do not weaken original obligation or allowed-axiom policy to avoid totality work.
