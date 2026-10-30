"""Finite descriptor boundary checks; not a Lean or native-performance result."""
from pathlib import Path
import hashlib,json,datetime,random
HERE=Path(__file__).resolve().parent
def main():
    rng=random.Random(0x2832);count=0
    for t in list(range(256))+[256,1023,2047,4095]:
      for off in [0,1,(1<<31)-1,1<<31,(1<<32)-1]+[rng.randrange(1<<32) for _ in range(12)]:
        code=(t<<32)+off
        assert code<(1<<44) and code<(1<<63)
        assert code>>32==t and code&((1<<32)-1)==off
        if t<256:assert code<(1<<40)
        count+=1
    out={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'scope':'Finite boundary inverse checks for a future same-family shared-support descriptor; no new kernel/CI/Lean or performance claim','checks':count,'mismatches':0,'narrow_bits':40,'general_k4096_bits':44,'zero_descriptor_counterexample':{'index':0,'offset':0,'descriptor':0,'input_word':0x3f800000,'weight_word':0x3f800000,'bias_word':0,'expected_output_word':0x3f800000,'wrong_skipped_output_word':0},'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    (HERE/'support-descriptor-check.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out,indent=2))
if __name__=='__main__':main()
