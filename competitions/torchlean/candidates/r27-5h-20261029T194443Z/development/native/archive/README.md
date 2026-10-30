# Historical generator restoration

graft_native_add_portfolio10-precanonical.py restores the exact pre-canonical generator bytes with SHA3f5d7284a57cfee011a190af9f458ec20f770047867907919b069368339706be. Its receipt native-add-portfolio10-precanonical-receipt.json retains the actually observed15805149 candidate and original metadata order. Python hash-seed input was not captured, so the old set-dependent alias ordering is not reproducible by an unrestricted fresh process. This is the negative that caused canonical sorting. Do not select or dispatch it.

The generator originally lived at native/graft_native_add_portfolio10.py; HERE-relative paths in this archive require that original location when restoring a complete historical checkout. Do not overwrite the current frozen generator to replay it. The current qualifiedf60551d5 source and immutable recipe dependencies are separate. No whole third-party Kernel is stored here.
