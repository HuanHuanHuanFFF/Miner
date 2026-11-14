"""Pure source-shape audit for pinned Lean generated C; no file or tool access.

The default is the five R22 Suite IO entries. Callers may pass another explicit
tuple for a later diagnostic. A passing report is not a Suite selection trace,
semantic proof, provenance check, native-code audit, or performance verdict.
"""
import hashlib
import re

DEFAULT_RUNNERS = ('runControl', 'runInlineOld', 'runOutline', 'runNativeProduct', 'runResident16')


class StaticRunnerAuditError(ValueError):
    def __init__(self, report):
        self.report = report
        super().__init__('; '.join(x['reason'] for x in report['failures']))


def _masked_c(text):
    """Blank comments and literals while preserving source character locations."""
    out, i = list(text), 0
    while i < len(text):
        if text.startswith('//', i):
            end = text.find('\n', i + 2)
            end = len(text) if end == -1 else end
        elif text.startswith('/*', i):
            end = text.find('*/', i + 2)
            if end == -1:
                raise ValueError('Unterminated C block comment')
            end += 2
        elif text[i] in ('"', "'"):
            quote, end = text[i], i + 1
            while end < len(text):
                if text[end] == '\\':
                    end += 2
                elif text[end] == quote:
                    end += 1
                    break
                else:
                    end += 1
            else:
                raise ValueError('Unterminated C literal')
        else:
            i += 1
            continue
        for j in range(i, min(end, len(text))):
            if text[j] != '\n':
                out[j] = ' '
        i = end
    return ''.join(out)


def _close(code, start, opening, closing):
    if start >= len(code) or code[start] != opening:
        raise ValueError('Missing opening delimiter')
    depth = 1
    for i in range(start + 1, len(code)):
        if code[i] == opening:
            depth += 1
        elif code[i] == closing:
            depth -= 1
            if not depth:
                return i
    raise ValueError('Unbalanced C delimiters')


def _split_args(code):
    starts, depth, begin = [], 0, 0
    for i, ch in enumerate(code):
        if ch in '([{':
            depth += 1
        elif ch in ')]}':
            depth -= 1
        elif ch == ',' and depth == 0:
            starts.append(code[begin:i].strip())
            begin = i + 1
    starts.append(code[begin:].strip())
    return starts


def _number(value):
    value = value.strip()
    if not re.fullmatch(r'(?:0[xX][0-9a-fA-F]+|[0-9]+)[uUlL]*', value):
        raise ValueError('Closure arity/fixed value is not a literal integer')
    return int(re.sub(r'[uUlL]+$', '', value), 16 if value.lower().startswith('0x') else 10)


def _symbol(value):
    words = [x for x in re.findall(r'\b[A-Za-z_]\w*\b', value)
             if x not in ('void', 'const', 'volatile', 'uintptr_t')]
    if len(words) != 1 or re.search(r'[^\w\s()*&]', value):
        raise ValueError('Closure callback is not a simple C symbol')
    return words[0]


def _location(text, start, end):
    return {'line': text.count('\n', 0, start) + 1,
            'column': start - text.rfind('\n', 0, start),
            'source_offset_chars': start, 'source_end_chars': end}


def _functions(code):
    found = []
    pattern = r'(?m)^[ \t]*(?:LEAN_EXPORT|static)\s+([^;={}()]*?)\b([A-Za-z_]\w*)\s*\('
    for m in re.finditer(pattern, code):
        opening = code.find('(', m.start(), m.end())
        closing = _close(code, opening, '(', ')')
        body = closing + 1
        while body < len(code) and code[body].isspace():
            body += 1
        if body >= len(code) or code[body] != '{':
            continue  # Prototype, not a function definition.
        end = _close(code, body, '{', '}') + 1
        found.append({'symbol': m[2], 'return_type': m[1].strip(),
                      'parameters': code[opening + 1:closing].strip(),
                      'start': m.start(), 'body_start': body, 'end': end})
    return found


def audit_static_runners(data, wanted=DEFAULT_RUNNERS):
    """Return report or raise StaticRunnerAuditError carrying the same full report.

    IO entries must have zero parameters (World erased), or one lean object
    parameter compatible with World, and no runtime closure construction.
    Reject arity >= 3 with fixed >= 1 in both literal and allocated closures.
    C type shape alone cannot prove that an object parameter denotes World;
    callers still bind this to the exact supplied Lean IO source and trace Suite.
    """
    if not isinstance(data, bytes):
        raise TypeError('Expected actual generated C as bytes')
    if not isinstance(wanted, (tuple, list)) or not wanted or len(set(wanted)) != len(wanted):
        raise ValueError('Expected distinct nonempty IO entry names')
    report = {'format': 'lean-static-suite-c-audit-v1', 'input_sha256': hashlib.sha256(data).hexdigest(),
              'input_bytes': len(data), 'wanted_entries': list(wanted), 'entries': {}, 'closures': [],
              'failures': [], 'passed': False,
              'scope': 'C shape prefilter only. World-compatible parameter types require exact Lean IO-source binding. Still trace each actual Suite argument to its boxed/typed callback, then native hot/cold paths. No gate, correctness, score or speed PASS.'}

    def fail(code, reason, location=None):
        report['failures'].append({'code': code, 'reason': reason, **({'location': location} if location else {})})

    try:
        text = data.decode('utf-8')
        code = _masked_c(text)
        functions = _functions(code)
    except (UnicodeError, ValueError) as exc:
        fail('C_PARSE', str(exc))
        raise StaticRunnerAuditError(report) from exc

    for short in wanted:
        matches = [f for f in functions if f['symbol'] == short or f['symbol'].endswith('_' + short)]
        if len(matches) != 1:
            fail('IO_ENTRY_MISSING_OR_AMBIGUOUS', f'{short}: expected one emitted IO definition, found {len(matches)}')
            continue
        f = matches[0]
        params = [] if f['parameters'] in ('', 'void') else _split_args(f['parameters'])
        object_param = len(params) == 1 and bool(re.fullmatch(
            r'(?:lean_object\s*\*|lean_obj_arg|b_lean_obj_arg)\s*[A-Za-z_]\w*', params[0]))
        world_shape = len(params) == 0 or object_param
        return_shape = bool(re.fullmatch(r'lean_object\s*\*|lean_obj_res', f['return_type']))
        entry = {'symbol': f['symbol'], 'return_type': f['return_type'], 'parameters': f['parameters'],
                 'argument_count': len(params), 'world_only_compatible_ABI_shape': bool(world_shape and return_shape),
                 'location': _location(text, f['start'], f['end']), 'runtime_closure_sites': []}
        report['entries'][short] = entry
        if not entry['world_only_compatible_ABI_shape']:
            fail('IO_ENTRY_PARAMETERS', f'{short}: IO entry is not World-only-compatible C shape', entry['location'])

    def add_closure(storage, start, end, symbol, arity, fixed, variable=None):
        location = _location(text, start, end)
        owner = next((f['symbol'] for f in functions if f['body_start'] < start < f['end']), None)
        item = {'storage': storage, 'callback_symbol': symbol, 'arity': arity, 'fixed': fixed,
                'owner_function': owner, 'location': location}
        if variable is not None:
            item['variable'] = variable
        report['closures'].append(item)
        if not 0 <= fixed <= arity:
            fail('CLOSURE_COUNTS', 'Invalid fixed/arity counts', location)
        if arity >= 3 and fixed >= 1:
            fail('CAPTURED_CALLBACK', f'{storage} callback {symbol} has arity {arity}, fixed {fixed}', location)
        if storage == 'allocated':
            for short, entry in report['entries'].items():
                if entry['symbol'] == owner:
                    entry['runtime_closure_sites'].append(item)
                    fail('IO_ENTRY_RUNTIME_CLOSURE', f'{short}: runtime closure construction remains in Suite IO entry', location)

    for m in re.finditer(r'\bstatic\s+const\s+lean_closure_object\s+([A-Za-z_]\w*)\s*=\s*\{', code):
        try:
            opening = code.find('{', m.start(), m.end())
            end = _close(code, opening, '{', '}') + 1
            init = code[opening:end]
            fun = re.search(r'\.m_fun\s*=\s*(.*?)(?:,|\})', init, re.S)
            arity = re.search(r'\.m_arity\s*=\s*([^,}]+)', init)
            fixed = re.search(r'\.m_num_fixed\s*=\s*([^,}]+)', init)
            if not (fun and arity and fixed):
                raise ValueError('Static closure literal lacks callback/arity/fixed fields')
            add_closure('static_literal', m.start(), end, _symbol(fun[1]), _number(arity[1]), _number(fixed[1]), m[1])
        except ValueError as exc:
            fail('STATIC_CLOSURE_PARSE', str(exc), _location(text, m.start(), m.end()))

    for m in re.finditer(r'\blean_alloc_closure\s*\(', code):
        try:
            opening = code.find('(', m.start(), m.end())
            end = _close(code, opening, '(', ')') + 1
            args = _split_args(code[opening + 1:end - 1])
            if len(args) != 3:
                raise ValueError('Allocated closure does not have three source arguments')
            add_closure('allocated', m.start(), end, _symbol(args[0]), _number(args[1]), _number(args[2]))
        except ValueError as exc:
            fail('ALLOCATED_CLOSURE_PARSE', str(exc), _location(text, m.start(), m.end()))

    report['closures'].sort(key=lambda x: x['location']['source_offset_chars'])
    report['passed'] = not report['failures']
    if not report['passed']:
        raise StaticRunnerAuditError(report)
    return report
