"""Explicitly requested synthetic +/- and old actual-C checks. No Lean/native tools."""
from pathlib import Path
import hashlib
import json
from static_runner_audit import DEFAULT_RUNNERS, StaticRunnerAuditError, audit_static_runners

HERE = Path(__file__).resolve().parent
STATIC = '''static const lean_closure_object closed_value = {
  .m_header = {.m_rc = 0, .m_tag = 245},
  .m_fun = (void*)fMul, .m_arity = 2, .m_num_fixed = 0, .m_objs = {}
};
'''


def entry(name, parameters='void', body='return suite(add, mul, sum, bmm);'):
    return f'LEAN_EXPORT lean_object* lp_competition_{name}({parameters}){{\n{body}\n}}\n'


BASE = STATIC + ''.join(entry(name) for name in DEFAULT_RUNNERS)


def main():
    results = []

    def check(name, text, required_codes=(), wanted=DEFAULT_RUNNERS, closure_counts=None):
        data = text if isinstance(text, bytes) else text.encode()
        try:
            report = audit_static_runners(data, wanted)
        except StaticRunnerAuditError as exc:
            report = exc.report
        codes = {f['code'] for f in report['failures']}
        if required_codes:
            assert set(required_codes) <= codes, (name, codes)
            assert not report['passed']
        else:
            assert report['passed'], (name, report['failures'])
            assert audit_static_runners(data, wanted) == report, 'Pure deterministic report required'
        if closure_counts is not None:
            counts = {storage: sum(c['storage'] == storage for c in report['closures'])
                      for storage in ('static_literal', 'allocated')}
            assert counts == closure_counts, (name, counts)
        assert all(c['location']['line'] > 0 and c['location']['column'] > 0 for c in report['closures'])
        results.append({'name': name, 'input_role': 'SYNTHETIC' if name != 'old_actual_C' else 'HISTORICAL_ACTUAL',
                        'passed_expected_behavior': True, 'audit_passed': report['passed'],
                        'failure_codes': sorted(codes), 'closure_count': len(report['closures']),
                        'input_sha256': report['input_sha256']})
        return report

    check('five_erasedWorld_static_fixed0', BASE, closure_counts={'static_literal': 1, 'allocated': 0})
    check('one_object_World_compatible', BASE.replace('runControl(void)', 'runControl(lean_object* world)'))
    check('static_captured_Bool', BASE.replace('.m_arity = 2, .m_num_fixed = 0', '.m_arity = 3, .m_num_fixed = 1'), ('CAPTURED_CALLBACK',))
    allocated = '\nLEAN_EXPORT lean_object* helper(void){\nreturn lean_alloc_closure((void*)(fMul), 3, 1);\n}\n'
    check('allocated_captured_Bool_outside_IO_entry', BASE + allocated, ('CAPTURED_CALLBACK',))
    check('IO_extra_Bool_parameter', BASE.replace('runControl(void)', 'runControl(uint8_t captured)'), ('IO_ENTRY_PARAMETERS',))
    check('IO_two_parameters', BASE.replace('runControl(void)', 'runControl(lean_object* world, uint8_t captured)'), ('IO_ENTRY_PARAMETERS',))
    check('IO_dynamic_fixed0_construction', BASE.replace('return suite(add, mul, sum, bmm);',
          'return lean_alloc_closure((void*)fMul, 2, 0);', 1), ('IO_ENTRY_RUNTIME_CLOSURE',))
    check('unknown_static_counts_fail_closed', BASE.replace('.m_arity = 2,', '.m_arity = arity + 1,'), ('STATIC_CLOSURE_PARSE',))
    check('missing_static_field_fail_closed', BASE.replace('.m_num_fixed = 0,', ''), ('STATIC_CLOSURE_PARSE',))
    reordered = BASE.replace('.m_fun = (void*)fMul, .m_arity = 2, .m_num_fixed = 0',
                            '.m_num_fixed = 1,\n .m_arity = 3,\n .m_fun = (void*) (&fMul)')
    check('multiline_reordered_static_capture', reordered, ('CAPTURED_CALLBACK',))
    fake = '''// lean_alloc_closure((void*)fake, 3, 1)
/* static const lean_closure_object fake_value = {.m_fun=(void*)fake,.m_arity=3,.m_num_fixed=1}; */
static const char* fake = "lean_alloc_closure((void*)fake, 3, 1) { }";
static const char character = '{';
'''
    check('comments_literals_not_callbacks', fake + BASE, closure_counts={'static_literal': 1, 'allocated': 0})
    check('duplicate_short_IO_entry', BASE + entry('another_runControl'), ('IO_ENTRY_MISSING_OR_AMBIGUOUS',))
    check('missing_named_IO_entry', BASE.replace(entry('runOutline'), ''), ('IO_ENTRY_MISSING_OR_AMBIGUOUS',))
    check('multiline_dynamic_capture', BASE + allocated.replace('((void*)(fMul), 3, 1)',
          '(\n (void*) (&fMul),\n 3,\n 1\n)'), ('CAPTURED_CALLBACK',))
    check('unknown_dynamic_counts_fail_closed', BASE + allocated.replace(', 3, 1)', ', n, 1)'), ('ALLOCATED_CLOSURE_PARSE',))
    check('invalid_UTF8_rejected', b'\xff', ('C_PARSE',))
    check('unterminated_comment_rejected', BASE + '/*', ('C_PARSE',))
    # The stated global capture criterion is >=3/fixed>=1, not all arity3 functions.
    check('uncaptured_arity3_is_only_inventory', BASE.replace('.m_arity = 2,', '.m_arity = 3,'))

    old = (HERE / 'historical-40432634558-Main.c').read_bytes()
    assert hashlib.sha256(old).hexdigest() == '24770ecaad37241f73605bac97e4273604355e85fc893f57e59ccb7d2caa1ed9'
    report = check('old_actual_C', old, ('CAPTURED_CALLBACK', 'IO_ENTRY_RUNTIME_CLOSURE'),
                   wanted=('_lean_main',), closure_counts={'static_literal': 3, 'allocated': 2})
    static = [c for c in report['closures'] if c['storage'] == 'static_literal']
    allocated = [c for c in report['closures'] if c['storage'] == 'allocated']
    assert [(c['arity'], c['fixed']) for c in static] == [(2, 0), (2, 0), (6, 0)]
    assert [(c['arity'], c['fixed']) for c in allocated] == [(3, 1), (3, 1)]
    assert {c['callback_symbol'] for c in allocated} == {
        'lp_competition_main___lam__1___boxed', 'lp_competition_main___lam__3___boxed'}
    output = {'status': 'PASS_EXPECTED_POSITIVE_AND_NEGATIVE_BEHAVIOR', 'test_count': len(results),
              'tests': results, 'audit_source_sha256': hashlib.sha256((HERE / 'static_runner_audit.py').read_bytes()).hexdigest(),
              'old_actual_C_report': report,
              'scope': 'C-source parser/shape checks only; all new-run ABI/native code/performance remain NOT_RUN.'}
    (HERE / 'static-runner-audit-local-verification.json').write_text(json.dumps(output, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'tests': len(results), 'status': output['status'],
                      'old_static_fixed0': len(static), 'old_allocated_captured': len(allocated),
                      'audit_sha256': output['audit_source_sha256']}))


if __name__ == '__main__':
    main()
