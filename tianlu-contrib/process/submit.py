#!/bin/env python
"""This handles job submission for processing on the cluster with
generators.
"""
from tianlu.submit import submit
from thirdparty.elements import ELEMENTS
from builder import Builder


__author__ = 'Tianlu Yuan'
__email__ = 'tianlu.yuan [at] colorado.edu'


class SubmitGenerator(submit):
    def __init__(self):
        """Inherits from class submit. Incorporates additional commandline
        args
        """
        super(SubmitGenerator, self).__init__()
        self.parser.add_option('--neut',
                               dest='neut',
                               action='store_true',
                               default=False,
                               help='process NEUT')

        self.parser.add_option('--genie',
                               dest='genie',
                               action='store_true',
                               default=False,
                               help='process GENIE')

        self.parser.add_option('--nuwro',
                               dest='nuwro',
                               action='store_true',
                               default=False,
                               help='process NUWRO')

        self.parser.add_option('--gibuu',
                               dest='nuwro',
                               action='store_true',
                               default=False,
                               help='process GIBUU')

        self.parser.add_option('--allgen',
                               dest='allgen',
                               action='store_true',
                               default=False,
                               help='process all generators')


def add_gen_jobs(builder, submittor):
    """Checks the CL options and decide which generator jobs to add
    """
    (options, args) = submittor.parser.parse_args()
    if options.genie:
        submittor.add_job(builder.build_genie())
    if options.neut:
        submittor.add_job(builder.build_neut())
    if options.nuwro:
        submittor.add_job(builder.build_nuwro())
    if options.allgen:
        submittor.add_job(builder.build_genie())
        submittor.add_job(builder.build_neut())
        submittor.add_job(builder.build_nuwro())


def submit_tgts(tgts=[6, 8, 18, 26, 29, 30, 82]):
    builder = Builder()
    submittor = SubmitGenerator()

    for tgt in tgts:
        builder.tgt = ELEMENTS[tgt]
        builder.category = ['targets', builder.tgt.symbol]
        for run in range(100):
            builder.runnum = run
            add_gen_jobs(builder, submittor)

    submittor.run()


if __name__ == '__main__':
    submit_tgts()
