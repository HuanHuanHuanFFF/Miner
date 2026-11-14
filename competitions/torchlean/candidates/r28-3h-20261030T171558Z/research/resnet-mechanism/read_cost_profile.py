#!/usr/bin/env python3
"""Scope-aware read-only interpretation of Droot's instrumented source11 profile."""
from pathlib import Path
import hashlib,json
P=Path(__file__).resolve().parent
def main():
    source=next((P.parents[1]/'evidence/41099255272').rglob('profile.json'))
    d=json.loads(source.read_text());assert d['source_sha256']=='ea6f582fc7a416b8860adb5c71fe3ab670dd4add01999fac7190993110f605a3'
    rows=[]
    for r in d['rows']:
        t=r['instrumented_kernel_entry_times'];total=sum(v['exclusive_ns'] for v in t.values())
        nested=t['linear']['inclusive_ns']-t['linear']['exclusive_ns']
        assert t['conv2d']['calls']==5*t['linear']['calls']
        rows.append({'cell':r['cell'],'checksum_pairs':r['checksum_pairs'],'conv_entry_share':t['conv2d']['exclusive_ns']/total,'nested_linear_ns':nested,'nested_linear_fraction_of_conv_entry':nested/t['conv2d']['exclusive_ns'],'estimated_four_3x3_share_within_profiled_entries':(t['conv2d']['exclusive_ns']-nested)/total,'inference_condition':'Source11 YlN rows=1 maps classifier to Ybp 1x1; no other measured nested entry on that branch. This subtraction is call-graph inference, not independent per-layer timing.'})
    out={'state':'READ_RAW_PROFILE_AND_RECONCILE_REAL_CALL_GRAPH','profile_path':str(source),'profile_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'source_sha256':d['source_sha256'],'raw_boundary':d['boundary'],'rows':rows,'decision':'Proceed with queued ResNet zero/core discriminator and one conditional packed-support native cost; do not infer a champion result or exact whole-model time share. 3x3 optimization excludes classifier1x1, but nested classifier cost is below1% of profiled conv entry time in these rows.','not_claimed':['optimized candidate correctness','optimized candidate latency','full inference timing share','actual Yt3g admission counts'],'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    (P/'profile-scope-review.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8');print(json.dumps(out,indent=2))
if __name__=='__main__':main()
