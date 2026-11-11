import pytest
from main import *

def test_lagrange():
    temp = lagrange_interpolation([-2, 6, 20], [0, 1, 2], 3)
    assert temp == [3, 5, -2]

def test_eea():
    temp = eea([6, 7, 2], [2, 1], 1)
    assert temp == [3, 2]
