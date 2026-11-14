"""A source-derived oldQPD value can be NaN even while it fits smallNat."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import math
import struct

HERE = Path(__file__).resolve().parent
MASK64 = (1 << 64)-1
CENTER = 1 << 62
narrow_word = 0x3f800001
high_word = 0x52ffc001
lo = min((((v & 0x7fffffff)-1)&0xffffffff) for v in [narrow_word,high_word]) >> 23
hi = max(v & 0x7fffffff for v in [narrow_word,high_word]) >> 23
base = lo-1 if lo else 0
magnitude = ((high_word & 0x7fffff)+(1 << 23)) << (((high_word >> 23)-1-base)%64)
payload = (CENTER+magnitude)&MASK64
assert (lo,hi) == (127,165) and hi-lo == 38
assert payload == 0x7ff0004000000000
assert payload < (1 << 63) and (payload >> 52)&2047 == 2047
assert payload & ((1 << 52)-1) != 0
value = struct.unpack("<d",struct.pack("<Q",payload))[0]
assert math.isnan(value)
canonical = 0x7ff8000000000000
assert payload != canonical
result = {
    "state":"FUNCTION_QPB_NAN_EXAMPLE_EXCLUDED_BY_EXISTING_YAV_GUARD",
    "at_utc":datetime.now(timezone.utc).isoformat(),
    "raw_inputs":{"other_narrow_row_word":narrow_word,"wide_row_low_word":narrow_word,"wide_row_high_word":high_word,"weight_word":narrow_word,"inW":16},
    "exact_Yah_fields":{"wide_lo":lo,"wide_hi":hi,"wide_span":38,"narrow_span":0,"weight_span":0,"global_QPS_span_test":True,"wide_QPa_span_test":False},
    "actual_QPb_formula":{"M":magnitude,"positive_cached_Nat":payload,"fits_64bit_smallNat":True,"binary64_exp":2047,"binary64_fraction":payload & ((1 << 52)-1)},
    "pinned_Lean4_34_object_cpp":{"blob_sha1":"49213d7be079e11589f1efcfe880dba44622a6e7","lines":[1935,1952],"toBits_ofNaN":canonical,"equals_original_payload":False},
    "actual_YaV_prepares_this_wide_row":False,
    "conclusion":"SmallNat<2^63aloneisnotasufficientFloatrawtransportcondition,butactualYaValreadyexcludesthiswiderowwiththeperrowspan+maxWeightSpanguardline869.Thisisnotacounterexampletoactualpreparedcachebound.",
    "limits":["PythononlyconfirmsNaNclassification.TheLeanruntimecanonicalvalueissource-reviewed,notexecutedhere.","Thewidecacheisunusedbytheguardedoldfastconsumer;thisdoesnotestablishanoldkerneloutputbug.","No performanceornewgateclaim."],
    "script_sha256":hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
}
(HERE/"old-qpb-nan-counterexample.json").write_text(json.dumps(result,indent=2)+"\n",encoding="utf-8")
print(json.dumps({"state":result["state"],"payload":hex(payload),"canonical":hex(canonical),"smallNat":True,"wide_span":38}))

