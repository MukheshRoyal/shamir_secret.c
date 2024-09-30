# Shamir's Secret Sharing Algorithm

## Overview
This project implements a simplified version of Shamir's Secret Sharing algorithm. The goal is to reconstruct the constant term of an unknown polynomial given a set of roots encoded in different numerical bases. The program reads inputs in JSON format, decodes them, computes the polynomial's constant term, and identifies any incorrect points (imposter points) in the provided data.

## Problem Statement
Given an unknown polynomial of degree \( m \) represented as:

\[ f(x) = a_m x^m + a_{m-1} x^{m-1} + ... + a_1 x + c \]

The task is to find the constant term \( c \) of the polynomial from given roots encoded in various bases, while also identifying any points that do not lie on the curve.

### Sample Input Format (JSON)
The program accepts input in the following JSON format:

```json
{
    "keys": {
        "n": 4,
        "k": 3
    },
    "1": {
        "base": "10",
        "value": "4"
    },
    "2": {
        "base": "2",
        "value": "111"
    },
    "3": {
        "base": "10",
        "value": "12"
    },
    "6": {
        "base": "4",
        "value": "213"
    }
}
