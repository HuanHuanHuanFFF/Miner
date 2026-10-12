"""R13 lightweight native diagnostic within the renewed seven-hour window."""
from pathlib import Path
import hashlib,importlib.util,json,os,subprocess,sys
from round4 import ROOT,validate

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts';out.mkdir(exist_ok=True)
    (out/'execution-start.json').write_text(json.dumps({'run_id':os.environ['GITHUB_RUN_ID'],
        'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
        'status':'NATIVE_EXECUTION_STARTED_NOT_A_RESULT','source_hashes':{e['name']:e['hashes']for e in spec['entries']},
        'scope':'Early identity binding, including later compile failures; no correctness, timing or proof assertion.'},indent=2)+'\n')
    if spec.get('r26_a_replay'):
        subprocess.run([sys.executable,str(ROOT/'scripts/r26-a-replay.py')],check=True)
        return
    if spec.get('r26_a_boundary'):
        subprocess.run([sys.executable,str(ROOT/'scripts/r26-a-boundary.py')],check=True)
        return
    if spec.get('r26_a_boundary641'):
        subprocess.run([sys.executable,str(ROOT/'scripts/r26-a-boundary641.py')],check=True)
        return
    if spec.get('r26_b_match_sharing'):
        subprocess.run([sys.executable,str(ROOT/'scripts/r26-b-match-sharing.py')],check=True)
        return
    if spec.get('r26_b_cache_phases'):
        subprocess.run([sys.executable,str(ROOT/'scripts/r26-b-cache-phases.py')],check=True)
        return
    if spec.get('r26_b_d_front_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/r26-b-d-front-diagnostic.py')],check=True)
        return
    if spec.get('r26_b_a_repeat_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/r26-b-a-repeat-diagnostic.py')],check=True)
        return
    if spec.get('r26_b_a_overlap_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/r26-b-a-overlap-diagnostic.py')],check=True)
        return
    if spec.get('r26_b_a_discarded_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/r26-b-a-discarded-diagnostic.py')],check=True)
        return
    if spec.get('r26_b_tree_edge_counts'):
        module=spec.get('r26_b_tree_edge_module', 'r26-b-tree-edge-diagnostic')
        assert module in ('r26-b-tree-edge-diagnostic', 'r26-b-tree-seed-diagnostic')
        subprocess.run([sys.executable,str(ROOT/'scripts'/(module+'.py'))],check=True)
        return
    if spec.get('r26_b_a_compiler_counts'):
        module=spec.get('r26_b_a_compiler_module', 'r26-b-a-compiler-diagnostic')
        assert module in ('r26-b-a-compiler-diagnostic', 'r26-b-a-checked-lowering')
        subprocess.run([sys.executable,str(ROOT/'scripts'/(module+'.py'))],check=True)
        return
    if spec.get('r26_a_distance12_observer_only'):
        subprocess.run([sys.executable,str(ROOT/'scripts/r26-a-distance12-counts.py')],check=True)
        return
    if spec.get('r26_a_row_shadow'):
        subprocess.run([sys.executable,str(ROOT/'scripts/r26-a-row-shadow.py')],check=True)
        return
    if spec.get('r26_a_link_replay'):
        subprocess.run([sys.executable,str(ROOT/'scripts/r26-a-link-replay.py')],check=True)
        return
    if spec.get('r26_a_rep_shadow'):
        subprocess.run([sys.executable,str(ROOT/'scripts/r26-a-rep-shadow.py')],check=True)
        return
    if spec.get('r26_a_near_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/r26-a-near-counts.py')],check=True)
        return
    if spec.get('r26_b_cache_integrity'):
        module=spec['r26_b_cache_integrity_module']
        assert module=='r26-b-cache-integrity-fix1'
        subprocess.run([sys.executable,str(ROOT/'scripts'/(module+'.py'))],check=True)
        return
    if spec.get('r25_heldout_quality'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round25-heldout-quality.py')],check=True)
        return
    if spec.get('r25_tiny_encoder_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round25-tiny-encoder.py')],check=True)
        return
    if spec.get('r25_len3_price'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round25-len3-price.py')],check=True)
        return
    if spec.get('r25_prefix_diversity_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round25-prefix-diversity-counts.py')],check=True)
        return
    if spec.get('r25_dual8_origins'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round25-dual8-origins.py')],check=True)
        return
    if spec.get('r25_dual8_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round25-dual8-counts.py')],check=True)
        return
    if spec.get('r26_native_decode'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round12-decode.py')],check=True)
    if spec.get('r25_finite_equivalence') or spec.get('r26_finite_equivalence'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round4.py')],check=True)
        eq=json.loads((out/'equivalence-research.json').read_bytes())
        assert eq.get('returncode')==0 and eq.get('cases') and all(r['cases']==444 and r['different_or_failed']==0 for r in eq['cases']), 'R25 requested actual finite equivalence must complete, including compilation'
    if spec.get('r24_output_state_entry'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round24-output-state.py')],check=True)
    if spec.get('r24_tiny_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round24-tiny-counts.py')],check=True)
    if spec.get('r24_buffer_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round24-buffer.py')],check=True)
    if spec.get('r24_cap_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round24-cap-counts.py')],check=True)
    if spec.get('r24_group_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round24-groups.py')],check=True)
    if spec.get('r24_match_cache_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round24-match-cache.py')],check=True)
    if spec.get('r24_word_reuse_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round24-word-reuse.py')],check=True)
    if spec.get('r24_compile_identity'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round24-compile.py')],check=True)
    if spec.get('r24_root_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round24-root.py')],check=True)
    if spec.get('r24_sf32_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round24-sf32.py')],check=True)
    if spec.get('r24_record_merge_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round24-records.py')],check=True)
    if spec.get('r24_heavy_fixed_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round24-heavy-fixed.py')],check=True)
    if spec.get('r24_a_packed_check'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round24-a-packed.py')],check=True)
    if spec.get('r24_item_price_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round24-item-price.py')],check=True)
    if spec.get('r24_span_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round24-span.py')],check=True)
    if spec.get('r24_chain_prefix_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round24-chain-prefix.py')],check=True)
    if spec.get('r20_secondary_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round20-secondary.py')],check=True);return
    if spec.get('r19_cache_prefix'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round19-cache-prefix.py')],check=True);return
    if spec.get('r19_cache_prototype'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round19-cache-prototype.py')],check=True);return
    if spec.get('r19_sf_cache'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round19-sf-cache.py')],check=True);return
    if spec.get('r19_sf_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round19-sf-counts.py')],check=True);return
    if spec.get('r18_range_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round18-ranges.py')],check=True);return
    if spec.get('r18_dp_repeat_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round18-convergence.py')],check=True);return
    if spec.get('r18_rf_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round18-rf-counts.py')],check=True);return
    if spec.get('r18_rf_span_equiv'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round13-encoder-native.py')],check=True)
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round18-rf-span.py')],check=True);return
    if spec.get('r18_rf_dominance_check'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round13-encoder-native.py')],check=True)
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round18-rf-dominance.py')],check=True);return
    if spec.get('r18_rf_prefix_check'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round13-encoder-native.py')],check=True)
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round18-rf-prefix.py')],check=True);return
    if spec.get('r18_a_ring_check'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round13-encoder-native.py')],check=True)
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round18-a-ring.py')],check=True);return
    if spec.get('r18_dna_domain_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round13-encoder-native.py')],check=True)
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round18-dna-domains.py')],check=True);return
    if spec.get('r18_dna_demotion_probe'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round18-dna-demotion.py')],check=True);return
    if spec.get('r18_a_range_counts'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round18-a-ranges.py')],check=True);return
    if spec.get('r18_a_block_check'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round13-encoder-native.py')],check=True)
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round18-a-block.py')],check=True);return
    if spec.get('r18_function_profile'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round13-encoder-native.py')],check=True)
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round18-functions.py')],check=True)
        if spec.get('r26_b_tag_graph_integrity'):
            subprocess.run([sys.executable,str(ROOT/'scripts/r26-b-tag-graph-integrity.py')],check=True)
        if spec.get('r26_b_tree_packed_counts'):
            subprocess.run([sys.executable,str(ROOT/'scripts/r26-b-tree-packed-counts.py')],check=True)
        return
    if spec.get('r16_transfer_candidates'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round16-transfer.py')],check=True);return
    if spec.get('pc_rescue_counts'):
        loader=importlib.util.spec_from_file_location('r13_rescue',ROOT/'scripts/research-round13-rescue.py')
        module=importlib.util.module_from_spec(loader);loader.loader.exec_module(module);module.main();return
    if spec.get('pc_expired_counts'):
        loader=importlib.util.spec_from_file_location('r13_expired',ROOT/'scripts/research-round13-expired.py')
        module=importlib.util.module_from_spec(loader);loader.loader.exec_module(module);module.main();return
    if spec.get('native_encoder'):
        loader=importlib.util.spec_from_file_location('r13_native_encoder',ROOT/'scripts/research-round13-encoder-native.py')
        module=importlib.util.module_from_spec(loader);loader.loader.exec_module(module);module.main()
        if spec.get('r26_a_lazy_chain_counts'):
            subprocess.run([sys.executable,str(ROOT/'scripts/r26-a-lazy-chain-counts.py')],check=True)
        if spec.get('r26_a_distance12_counts'):
            subprocess.run([sys.executable,str(ROOT/'scripts/r26-a-distance12-counts.py')],check=True)
        if spec.get('r26_a_second_look_counts'):
            subprocess.run([sys.executable,str(ROOT/'scripts/r26-a-second-look-counts.py')],check=True)
        if spec.get('r26_a_row_counts'):
            subprocess.run([sys.executable,str(ROOT/'scripts/r26-a-row-counts.py')],check=True)
        if spec.get('r26_a_tagged_counts'):
            subprocess.run([sys.executable,str(ROOT/'scripts/r26-a-tagged-counts.py')],check=True)
        return
    record={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
        'status':'STARTED_NATIVE_ONLY','candidate_hashes':{e['name']:e['hashes']for e in spec['entries']if not e['control']},
        'scope':'R13 native token/decode diagnostic only. Official extraction, paired two axes, full gate and ranking NOT_RUN.'}
    dest=out/'native-only.json';dest.write_text(json.dumps(record,indent=2)+'\n')
    result=subprocess.run([sys.executable,str(ROOT/'scripts/research-round4.py')],check=False)
    eq=json.loads((out/'equivalence-research.json').read_bytes())if(out/'equivalence-research.json').exists()else{}
    record.update(status='VERIFIED_FINITE_NATIVE_ONLY'if result.returncode==0 and eq.get('returncode')==0 and eq.get('cases') and all(r['cases']==444 and r['different_or_failed']==0 for r in eq['cases'])else'FAILED_OR_INCOMPLETE_NATIVE_ONLY',equivalence=eq)
    dest.write_text(json.dumps(record,indent=2)+'\n');print(json.dumps(record))
    if spec.get('ef32_key4_counts'):
        loader=importlib.util.spec_from_file_location('r13_key4_probe',ROOT/'scripts/research-round13-key4.py')
        module=importlib.util.module_from_spec(loader);loader.loader.exec_module(module);module.main()
    assert record['status']=='VERIFIED_FINITE_NATIVE_ONLY'

if __name__=='__main__':main()
