"""Repository-level compatibility entry for the preserved guarded merge tool."""
from pathlib import Path
import runpy

if __name__=='__main__':
    runpy.run_path(str(Path(__file__).resolve().parents[1]/'competitions/deflate/scripts/merge操作.py'),run_name='__main__')
