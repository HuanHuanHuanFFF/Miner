"""Run the preserved local-only merge integration suite after the directory migration."""
from pathlib import Path
import runpy

if __name__=='__main__':
    runpy.run_path(str(Path(__file__).resolve().parents[1]/'competitions/deflate/scripts/test-merge-operation.py'),run_name='__main__')
