"""Build a separate coarse diagnostic from the byte-frozen first profile.

Only selector, timer category count/tag, prefix, scope text and call-boundary
validation differ. Original whole execution, replay, compile/link and cleanup
boundaries stay byte-identical in the copied run body.
"""
from pathlib import Path
import hashlib,json
HERE=Path(__file__).resolve().parent
ORIGINAL='0b973c9c309b4e86d8e0576a32873ab097a41a1db3b45c1600f3892ac538a334'
ENTRY='3e5e7e63411aab9621e1a37e8b6822ac00d33fe4fda271d130a4a33dccea51a0'
CATEGORIES=('whole_bmm','whole_sum','rowstream_amap','rowstream_bpack','rowstream_scope',
    'cross_words','cross_scope','direct_continuous','direct_small','underflow_fill')
SELECTOR='''def category(name):
    # Exact actualDF outer entry points. No lambdas, boxed adapters, ofFn,
    # Fin.foldl, row/packet producers, dot/finish/emit or inner loops.
    return {
        'lp_competition_Submission_bmm':'whole_bmm',
        'lp_competition_Submission_sum':'whole_sum',
        'lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowStream_output_spec__0':'rowstream_amap',
        'lp_competition_Submission_Packed10_packB':'rowstream_bpack',
        'lp_competition_Submission_RowStream_output':'rowstream_scope',
        'lp_competition_Submission_R11CrossRows_words___redArg':'cross_words',
        'lp_competition_Submission_R11CrossRows_core___redArg':'cross_scope',
        'lp_competition_Submission_DirectContinuous_output':'direct_continuous',
        'lp_competition_Submission_DirectSmall_core':'direct_small',
        'lp_competition_Submission_UnderflowZero_zeros':'underflow_fill',
    }.get(name)
'''


def build():
    raw=(HERE/'profile-current.py').read_bytes();entryraw=(HERE/'profile-entry.py').read_bytes()
    assert hashlib.sha256(raw).hexdigest()==ORIGINAL and hashlib.sha256(entryraw).hexdigest()==ENTRY
    text=raw.decode();start=text.index('def category(name):');end=text.index('\n\nPRELUDE=',start)
    text=text[:start]+SELECTOR+text[end:]
    text=text.replace("PREFIX='profile-r13-'","PREFIX='profile-r13-coarse-'")
    old="CATEGORIES=('whole_bmm','whole_sum','amap','bpack','cross_prepare','compute','output','repair','dispatch_scan')"
    assert text.count(old)==1;text=text.replace(old,'CATEGORIES='+repr(CATEGORIES))
    assert text.count('pr13_calls[9]')==1
    text=text.replace('pr13_calls[9]','pr13_calls[10]').replace('pr13_exc[9]','pr13_exc[10]').replace('pr13_inc[9]','pr13_inc[10]')
    assert text.count('c<9;')==1;text=text.replace('c<9;','c<10;')
    text=text.replace('FL13','FC13')
    old="require(any(r['category']=='compute'for r in inventory),'no actual compute boundary')"
    assert text.count(old)==1
    text=text.replace(old,"require(set(r['category']for r in inventory)==set(CATEGORIES),'coarse outer boundary missing; UNKNOWN')")
    old='    return expected_bmm+expected_sum\n'
    assert text.count(old)==1
    text=text.replace(old,"""    # Every selected non-root boundary encloses at most one complete BMM.
    # Any accidental row/packet callback selection fails closed immediately.
    require(all(stages[c]['calls']<=expected_bmm for c in CATEGORIES[2:]),
            'coarse boundary unexpectedly called per output/packet '+case['name'])
    return expected_bmm+expected_sum
""")
    text=text.replace('R13 exactDF per-case whole anchors and independent generated-C stage diagnosis.',
        'R13 exactDF coarse outer-boundary diagnosis; no element/row/packet probes.')
    text=text.replace('Inclusive/exclusive generated-C function intervals across warmup+all3 sweeps; nested exclusive totals avoid double counting.',
        'Coarse inclusive/exclusive outer-function intervals across warmup+all3 sweeps; every non-root boundary is called at most once per BMM; nested exclusive totals avoid double counting.')
    text=text.replace('Inline dispatch scans, fused compute/output and first-NaN repair not isolated by observed C function boundaries remain root exclusive/residual. Zero stage time is not proof that a phase has zero cost.',
        'RowStream scope exclusive combines computation, output and cleanup after excluding outer Amap/packB. Cross words combines preparation, packet computation and repairs; Cross scope exclusive contains output materialization after words plus cleanup. Direct scopes combine complete compute/output. Underflow scans remain root exclusive. Missing/unexecuted boundaries are UNKNOWN, never zero-cost claims.')
    out=HERE/'profile-coarse-current.py';out.write_bytes(text.encode())
    entry=entryraw.decode().replace("'profile-current.py'","'profile-coarse-current.py'")
    entry=entry.replace('r13_exact_df_profile','r13_exact_df_coarse_profile')
    entry=entry.replace('diagnostic-statement-profile','diagnostic-statement-coarse-profile')
    entry=entry.replace('diagnostic-only-verdict.json','diagnostic-only-coarse-verdict.json')
    (HERE/'profile-coarse-entry.py').write_bytes(entry.encode())
    print(json.dumps({n:hashlib.sha256((HERE/n).read_bytes()).hexdigest()for n in ['profile-current.py','profile-entry.py','profile-coarse-current.py','profile-coarse-entry.py']}))


if __name__=='__main__':build()
