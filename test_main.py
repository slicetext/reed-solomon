import pytest
from main import *


def test_lagrange():
    temp = lagrange_interpolation([-2, 6, 20], [0, 1, 2], 3)
    assert temp == [3, 5, -2]


def test_poly_div():
    a = [3, 2, 1]
    b = [2, 1]

    assert div_two_poly(a, b) == ([1.5, 0.25], [0.75])


def test_poly_mul():
    a = [2, 3]
    b = [5, 1]

    assert mult_two_poly(a, b) == [10, 17, 3]


def test_poly_sub():
    a = [5, 3, 2]
    b = [2, 1]

    assert sub_two_poly(a, b) == [5, 1, 1]

    a = [3, 2]
    b = [12, -5, 1]

    assert sub_two_poly(a, b) == [-12, 8, 1]


def test_degree():
    a = [12, 13, 14, 17]
    assert degree(a) == 3

    b = [1]
    assert degree(b) == 0

    c = [1, 2]
    assert degree(c) == 1


def test_eea():
    temp = eea([6, 7, 2], [2, 1], 1)
    assert temp == [3, 2]
