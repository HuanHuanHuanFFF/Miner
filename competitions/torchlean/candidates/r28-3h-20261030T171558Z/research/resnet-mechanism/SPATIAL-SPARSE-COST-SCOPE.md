# Source11 sparse arithmetic scope correction

Parent1746 correctly warns that a spatial transform fills sparse weights. Its `36→18 direct nonzero products versus16 transformed` comparison must be labeled an **already weight-filtered direct implementation** or ideal nonzero-work baseline. It is not the current source11 specialized 3×3 runtime count.

I rechecked exact source11 `ea6f582f…`: `cdQ false→Yt3w→Yt3c→Yt3g/Yt3f` contains no weight-support filter. In each paired channel iteration, `Yt3g` calls Y9 eighteen times and cq1 eighteen times for the nine input locations and two output channels. `Yt3f` calls each nine times. An encoded zero weight still enters these products. BW range/all-zero information changes scale/admission, not this loop's nonzero support. Thus one output channel/four spatial outputs/one input channel uses72split-word products (36scalar exact products), even on sparse weights, when this path is admitted.

The proposed spatial block8 word model uses32split-word products (16scalar products) for the same complete2×2tile, before transforms/inverse/bias/prep. This is still only a source-operation comparison. Odd tiles do extra work; all cache preparation,128-bit inverse operations and output destruction remain costs. The newer zero-pair or packed-input candidates change the baseline arithmetic again; their measured versions must be compared separately.

Consequently, sparse fill-in remains a real cost risk and matters against source53's existing sparse-row path or a future weight-filtered source11. It does not by itself bound improvement over the actual original source11 3×3 path to(18−16)/18. No sparse-kind special case or compiler/native speedup is being assumed, and this note does not add a CI request.
