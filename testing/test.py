import sys, re, subprocess as s
from typing import Tuple
from functools import partial as p
from itertools import chain as c
import base64 as b

def ___(f): return lambda *a, **k: (lambda r: r[1] if r[0] else sys.exit(f"Error: {r[1]}"))(f(*a, **k))

def __(p: str) -> Tuple[bool, str]:
    invalid_chars = '<>:|"?*'
    return (True, p) if not any(x in p for x in invalid_chars) else (False, f"Invalid path: {p}")

def _(x: str) -> Tuple[bool, str]:
    try:
        proc = s.Popen(x, stdout=s.PIPE, stderr=s.PIPE, shell=True)
        out, err = proc.communicate()
        out = out + err
        return (True, out.decode() if out else err.decode())
    except Exception as e:
        return (False, f"Execution error: {str(e)}")

def _x_(t: str, r: str) -> Tuple[bool, bool]:
    try:
        return (True, bool(re.search(r, t)))
    except Exception as e:
        return (False, f"Regex error: {str(e)}")

def main():
    try:
        if len(sys.argv) != 3:
            return sys.exit("Usage: script.py <executable_path> <regex_pattern>")

        path_check = __(sys.argv[1])
        if not path_check[0]:
            return sys.exit(path_check[1])

        exec_result = _(path_check[1])
        if not exec_result[0]:
            return sys.exit(exec_result[1])

        match_result = _x_(exec_result[1], sys.argv[2])
        if not match_result[0]:
            return sys.exit(match_result[1])

        print(f"Output: {exec_result[1]}")
        print(f"Regex match: {'Yes' if match_result[1] else 'No'}")
        return match_result[1]

    except Exception as e:
        return sys.exit(f"Unexpected error: {str(e)}")

if __name__ == "__main__":
    sys.exit(0 if main() else 1)
