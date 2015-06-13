#!/bin/env python
"""This handles job submission for processing on the cluster with
generators.
"""
import os
from tianlu.submit import submit
from thirdparty.elements import ELEMENTS
from builder import Builder


__author__ = 'Tianlu Yuan'
__email__ = 'tianlu.yuan [at] colorado.edu'


def submit_tgts(tgts=[6, 8, 18, 26, 29, 30, 82]):
    builder = Builder()
    submittor = submit()

    for tgt in tgts:
        builder.tgt = ELEMENTS[tgt]
        builder.category = ['targets', builder.tgt.symbol]
        for run in range(100):
            builder.runnum = run

            submittor.add_job(builder.build_genie())
            submittor.add_job(builder.build_neut())

    submittor.run()


if __name__ == '__main__':
    submit_tgts()
