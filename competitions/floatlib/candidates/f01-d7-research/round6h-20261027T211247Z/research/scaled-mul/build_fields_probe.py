from pathlib import Path
import hashlib, json

HERE=Path(__file__).resolve().parent
base=(HERE/'Kernel-probe1.lean').read_bytes()
assert hashlib.sha256(base).hexdigest()=='6589f24df6d0048533e3689733d291c5b6f9a0a86328d689fd54c029be595d5e'
parts=['Repack-scaled.lean.inc','Guard-scaled.lean.inc']
kernel=base+b'\nsection R22ScaledFieldsProbe\nset_option maxRecDepth 8192\n'+b'\n'.join((HERE/f).read_bytes() for f in parts)+b'\nend R22ScaledFieldsProbe\n'
assert len(kernel)<=256000,len(kernel)
(HERE/'Kernel-probe2.lean').write_bytes(kernel)
roots=[
 'Submission.R21ScaledU32.native_integer_product_decode',
 'Submission.R21ScaledU32.integer_product_scaled_fields',
 'Submission.R22ScaledFields.highWord_nat',
 'Submission.R22ScaledFields.mantissaWord_nat',
 'Submission.R22ScaledFields.fractionWord_nat',
 'Submission.R22ScaledFields.exponentWord_nat',
 'Submission.R22ScaledFields.output_fields',
 'Submission.R22ScaledFields.low_mask_eq_self',
 'Submission.R22ScaledFields.mkW_eq_unmasked',
 'Submission.R22ScaledFields.packed_fields',
 'Submission.R22ScaledFields.normalCore_eq_fields',
 'Submission.R22ScaledGuard.ex_nat',
 'Submission.R22ScaledGuard.ex_bound',
 'Submission.R22ScaledGuard.sum_nat',
 'Submission.R22ScaledGuard.guard_conditions',
 'Submission.R22ScaledGuard.guardedMul_spec_of_core_spec',
]
(HERE/'HelperAudit-probe2.lean.inc').write_text(''.join('#print axioms '+r+'\n' for r in roots),encoding='utf-8')
files=parts+['Kernel-probe2.lean','HelperAudit-probe2.lean.inc']
manifest={
 'state':'NOT_RUN_INTERFACE_PROBE',
 'base_sha256':hashlib.sha256(base).hexdigest(),
 'explicit_helper_audit':roots,
 'files':{f:{'bytes':(HERE/f).stat().st_size,'sha256':hashlib.sha256((HERE/f).read_bytes()).hexdigest()} for f in files},
 'public_operations':'UNCHANGED_B2',
 'full_public_mul':'NOT_PROVED',
 'scope':'Scaled runtime field repack plus exact original guard and conditional fallback transport. Core-to-model multiplication remains a premise in guardedMul_spec_of_core_spec.',
 'not_claimed':['full new mul_spec','official gate','new performance','adoption'],
}
(HERE/'probe2-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf-8')
print(json.dumps(manifest,indent=2))
