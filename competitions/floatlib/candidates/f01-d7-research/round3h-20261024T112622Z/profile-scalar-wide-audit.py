"""Bounded source/trust preflight; no candidate, Lean invocation or CI."""
from pathlib import Path
import datetime,hashlib,json,re
HERE=Path(__file__).resolve().parent
REPO=next(p for p in HERE.parents if (p/'competitions/floatlib').is_dir())


def run():
    meta=json.loads((HERE/'profile-scalar-wide-source-metadata.json').read_bytes())
    primary=[]
    for source in meta['sources']:
        p=HERE/source['file'];raw=p.read_bytes()
        blob=hashlib.sha1(b'blob '+str(len(raw)).encode()+b'\0'+raw).hexdigest()
        assert blob==source['git_blob_sha'],'not exact fetched Git blob'
        primary.append({**source,'sha256':hashlib.sha256(raw).hexdigest(),'bytes':len(raw),
            'fetched_interval_utc':meta['fetched_interval_utc']})
    core=(HERE/'profile-scalar-wide-lean-Float32.lean').read_text(encoding='utf-8')
    native=(HERE/'profile-scalar-wide-FloatLib-Native.lean').read_text(encoding='utf-8')
    conversion=(HERE/'profile-scalar-wide-FloatLib-ConversionRuntime.lean').read_text(encoding='utf-8')
    assert 'opaque Float.toFloat32 : Float → Float32'in core
    assert 'opaque Float32.toFloat : Float32 → Float'in core
    assert 'Float.toFloat32'not in native and 'Float.toFloat32'not in conversion
    line=lambda text,token:text[:text.index(token)].count('\n')+1
    gate=REPO/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
    gate_text=gate.read_text(encoding='utf-8')
    assert 'AXIOMS = {"propext", "Classical.choice", "Quot.sound"}'in gate_text
    history=[REPO/'competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/astra-design.md',
        REPO/'competitions/floatlib/candidates/f01-d7-research/storage-cost-screening.json',
        REPO/'competitions/floatlib/candidates/f01-d7-research/low-normal-history-review.json']
    cached=REPO/'competitions/floatlib/research/astra-collab-20261022/web/R2-W01c/original-extracted/FloatLib_R2-W01c/public_sources/floatlib_fixed/FloatLib'
    files=sorted(cached.rglob('*.lean'))
    cross_refs=[{'file':str(p),'line':j+1,'text':s}for p in files for j,s in enumerate(p.read_text(encoding='utf-8').splitlines())if re.search(r'Float\.toFloat32|Float32\.toFloat',s)]
    out={'state':'BLOCKED_MISSING_ALLOWED_NATIVE_F64_TO_F32_SEMANTIC_BRIDGE',
        'audit_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'mechanism':'Exact24x24->48bit integer significand product, convert once to binary64, exact power2 scaling, then one native Float.toFloat32 rounding; preserve existing cold NaN/Inf/signed-zero behavior.',
        'decision':'Do not implement or benchmark the mechanism under the current fixed environment.',
        'first_hard_block':{'symbol':'Float.toFloat32','declared_in':primary[0]['url'],
            'line':line(core,'opaque Float.toFloat32'),
            'kind':'Opaque extern; no logical cross-width rounding equation in the verified interfaces.',
            'required_schematic_obligation':'Relate (Float.toFloat32 f).toModel to Float32.Model.pack(f.toModel.unpack), at least for the finite exact-product subset.',
            'schematic_obligation_typechecked':False,
            'why_existing_bridges_do_not_close':'ExecFloat.Binary.toFloat/ofFloat bridge binary64 within one width; toFloat32/ofFloat32 bridge binary32 within one width. NativeFloat ExactDecoder + generic convert is a separate decode/quantize software path, not a theorem about opaque Float.toFloat32.',
            'scope':'A scoped source audit, not a universal impossibility theorem about all conceivable formalizations.'},
        'allowed_trust':{'official_commit':'4b7e83841cc0c32c6529f533923c73d33b5ecf97','FloatLib_commit':'0d91825727839f597fd06b22fdd038ea21480f0c','Lean':'v4.34.0',
            'axioms':['propext','Classical.choice','Quot.sound'],'new_axiom_extern_implemented_by_csimp':'Forbidden by original gate policy',
            'gate_path':str(gate),'gate_sha256':hashlib.sha256(gate.read_bytes()).hexdigest()},
        'source_findings':{'Float32_toFloat_opaque_line':line(core,'opaque Float32.toFloat'),
            'Float_toFloat32_opaque_line':line(core,'opaque Float.toFloat32'),
            'native_exact_decoder_line':line(native,'instance nativeFloatExactDecoder'),
            'generic_conversion_scope':'Decode/map/quantize through destination exact domain; cannot stand in for native cast semantics.',
            'cache_supplemental_file_count':len(files),'cache_exact_cross_cast_reference_count':len(cross_refs),
            'cache_search_scope':'Selected public-source snapshot, not claimed complete FloatLib tree.'},
        'history':[{'file':str(p),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()}for p in history],
        'history_interpretation':'R11 astra-design line25 already parked FloatArray widening/narrowing because these same opaque conversion bridges were unproved. Storage screening reiterates that boundary. No exact48bit-product/F64-scaling performance negative was found; do not reuse UInt64.toFloat32 wide64 decoder timings as this mechanism.',
        'deferred_after_first_block':{'mantissa48_exactness':'NOT_FORMALIZED','Float64_scale_range':'NOT_INVESTIGATED_AFTER_TRUST_BLOCK','single_RNE_and_double_rounding':'BLOCKED_BY_CAST_MODEL','signed_zero_NaN_Inf_end_to_end':'NOT_PROVED','code_size':'UNKNOWN','speed':'UNKNOWN'},
        'proof_cost':'Cannot close under current verified cast interface. After a legitimate bridge exists, still needs exact integer/F64 scaling and final binary32 rounding + existing cold-result composition; no estimate of successful proof or speed is made.',
        'minimal_next_trial':'First locate and typecheck an existing permitted cross-width theorem under import ContractTensor on the pinned runner, print its complete axiom dependencies. No runner/CI is launched for absent theorem. Only after that gate should any numerical proof or complete-cost candidate begin.',
        'primary_sources':primary,'audit_source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        'execution':'Read-only Python/source audit only; no Lean, Linux install, candidate, benchmark or CI.'}
    dest=HERE/'profile-scalar-wide-audit.json';dest.write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'state':out['state'],'sha256':hashlib.sha256(dest.read_bytes()).hexdigest(),'cross_cast_line':out['first_hard_block']['line'],'official_sources':len(primary),'new_Lean':'NOT_RUN'}))


if __name__=='__main__':run()
