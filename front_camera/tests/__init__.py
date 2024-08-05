
"""パッケージの初期化を行うモジュール.
@author: bizyutyu
"""
from pathlib import Path
import sys

sys.path.append(str(Path(__file__).parent / "dummy"))
sys.path.append(str(Path(__file__).parent.parent / "src"))