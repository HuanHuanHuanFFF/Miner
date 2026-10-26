"""Extra mathematical helper audit, separate from full performance acceptance."""
from pathlib import Path
import hashlib
import json
import re


def parse_reports(output, names, allowed):
    text = output.replace('\n', ' ')
    reports = {}
    for name in names:
        pattern = re.escape(name) + r"['’`]?\s+(?:depends on axioms:\s*\[([^\]]*)\]|does not depend on any axioms)"
        found = list(re.finditer(pattern, text))
        if len(found) != 1:
            raise ValueError('Missing/duplicate helper axiom report: ' + name)
        axioms = {x.strip() for x in (found[0].group(1) or '').split(',') if x.strip()}
        if axioms - set(allowed):
            raise ValueError('Extra helper axioms: ' + name + ': ' + ','.join(sorted(axioms - set(allowed))))
        reports[name] = sorted(axioms)
    return reports


def stages(g, kernel, out, manifest):
    raw = kernel.read_bytes()
    digest = hashlib.sha256(raw).hexdigest()
    assert digest == manifest['candidate_sha256'] == manifest['helper_audit_source_sha256']
    names = manifest['explicit_helper_audit']
    assert len(names) == len(set(names)) == manifest['helper_audit_expected_count'] and 1 <= len(names) <= 128
    assert all(re.fullmatch(r'(?:Submission|R18|R18A)\.[A-Za-z0-9_.]+', n) for n in names)
    assert set(manifest['helper_audit_required_endpoints']) <= set(names)
    record = dict(kernel_sha256=digest, names=names, expected_count=len(names), kernel_replay=False, accepted=False,
                  scope='Original leanchecker replays the complete Submission/VerifyFull modules; separate explicit helper axiom reports, not a performance gate.')
    target = out / 'helper-audit.json'

    def save():
        target.write_text(json.dumps(record, indent=2)+'\n', encoding='utf-8')

    def replay(src, verdict):
        reason = g.kernel(src, verdict)
        record.update(kernel_replay=reason is None, kernel_reason=reason)
        save()
        return reason

    def axioms(src, verdict):
        audit = g.WORK.parent / 'R16HelperAudit.lean'
        assert not audit.exists()
        content = 'import Submission\n' + ''.join('#print axioms '+name+'\n' for name in names)
        audit.write_text(content, encoding='utf-8')
        record['audit_source_sha256'] = hashlib.sha256(content.encode()).hexdigest()
        (out / 'helper-audit-source.lean').write_text(content, encoding='utf-8')
        try:
            code, output = g.own([g.LAKE, 'env', 'lean', 'work/R16HelperAudit.lean'], g._BUILD_TIMEOUT, build='read')
            original = output.encode()
            (out / 'helper-axioms.raw').write_bytes(original)
            record.update(exit_code=code, output_sha256=hashlib.sha256(original).hexdigest(),
                          allowed_axioms=sorted(g.AXIOMS))
            if code:
                raise ValueError('Helper audit command failed: '+str(code))
            record['reports'] = parse_reports(output, names, g.AXIOMS)
            record['accepted'] = record['kernel_replay'] and len(record['reports']) == len(names)
            return None if record['accepted'] else 'Incomplete helper replay/axiom audit'
        except (ValueError, OSError) as error:
            record['error'] = str(error)
            return str(error)
        finally:
            audit.unlink()
            save()

    return [('helper-kernel', replay), ('helper-axioms', axioms)]
