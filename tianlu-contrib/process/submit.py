#!/bin/env python
"""This handles job submission for processing on the cluster with
generators.
"""
import os
from tianlu.submit import submit
from thirdparty.elements import ELEMENTS
from builder import Builder


def submit_tgts(tgts=[6, 8, 18, 26, 29, 30, 82]):
    builder = Builder()
    submittor = submit()

    for tgt in tgts:
        for run in range(100):
            builder.runnum = run
            builder.tgt = ELEMENTS[tgt]
            builder.uniquepath = os.path.join('targets', builder.tgt.symbol)

            submittor.add_job(builder.build_genie())
            submittor.add_job(builder.build_neut())

    submittor.run()


if __name__ == '__main__':
    submit_tgts()
