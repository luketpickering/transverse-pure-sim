"""This class defines methods to build input cards and shell-scripts
for submission. Settings are generator agnostic, all generator
specifics are handled in their build methods.
"""
import os
from thirdparty.elements import ELEMENTS
from tianlu import utils, directories


__author__ = 'Tianlu Yuan'
__email__ = 'tianlu.yuan [at] colorado.edu'


PACKAGE_DIRECTORY = os.path.dirname(os.path.abspath(__file__))

class Builder(object):
    def __init__(self):
        """Default values:
        nevents: 1e4
        nupdg:14
        nupgev: 0.6
        tgt: Carbon
        runnum: 0
        category: ['targets', 'C']

        category defines a unique list of strings that can be used to
        form the output directory, as well as for naming the output
        scripts/cards
        """
        self.nevents = 10000
        self.nupdg = 14
        self.nupgev = 0.6
        self.runnum = 0
        self.tgt = ELEMENTS[6]
        self.category = ['targets', self.tgt.symbol]


    def _outdir(self, generator):
        """Formats the full absolute path for the output directory where
        submission scripts and outputs are stored
        """
        return os.path.join(directories.GENERATORS_STORE,
                            generator,
                            *self.category)


    def build_genie(self):
        """ Modifies the template/genie_script.sh
        """
        outdir = self._outdir('genie')
        out_script = os.path.join(outdir,
                                  '.scripts',
                                  'genie_script_{0}_{1}.sh'.
                                  format('_'.join(self.category),
                                         self.runnum))

        utils.make_dirs_if_needed(os.path.dirname(out_script))
        utils.find_and_replace(os.path.join(PACKAGE_DIRECTORY,
                                            'templates/genie_script.sh'),
                               out_script,
                               ZNEVENTSZ=self.nevents,
                               ZNUPDGZ=self.nupdg,
                               ZNUPGEVZ=self.nupgev,
                               ZTGTPDGZ=utils.z_to_pdg(self.tgt.number,
                                                       self.tgt.number+
                                                       self.tgt.neutrons),
                               ZRUNNUMZ=self.runnum,
                               ZOUTDIRZ=outdir)

        os.chmod(out_script, 0755)
        return out_script


    def build_neut(self):
        """Modifies the template/neut.card and neut_script. Formats the card
        appropriately first and then builds the script for submission.
        """
        outdir = self._outdir('neut')
        out_card = os.path.join(outdir,
                                '.cards',
                                'neut_{0}.card'.format(self.runnum))
        # the name of the script is taken as the sge jobid and thus it
        # must be unique
        out_script = os.path.join(outdir,
                                  '.scripts',
                                  'neut_script_{0}_{1}.sh'.
                                  format('_'.join(self.category),
                                         self.runnum))

        utils.make_dirs_if_needed(os.path.dirname(out_card))
        utils.make_dirs_if_needed(os.path.dirname(out_script))

        # neut card for hydrogen filled differently
        if self.tgt == ELEMENTS[1]:
            utils.find_and_replace(os.path.join(PACKAGE_DIRECTORY,
                                                'templates/neut.card'),
                                   out_card,
                                   ZNEVENTSZ=self.nevents,
                                   ZNUPDGZ=self.nupdg,
                                   ZNUPMEVZ=self.nupgev*1e3,
                                   ZNNZ=0,
                                   ZNBPZ=0,
                                   ZNFPZ=1,
                                   ZNAZ=0)
        else:
            utils.find_and_replace(os.path.join(PACKAGE_DIRECTORY,
                                                'templates/neut.card'),
                                   out_card,
                                   ZNEVENTSZ=self.nevents,
                                   ZNUPDGZ=self.nupdg,
                                   ZNUPMEVZ=self.nupgev*1e3,
                                   ZNNZ=self.tgt.neutrons,
                                   ZNBPZ=self.tgt.number,
                                   ZNFPZ=0,
                                   ZNAZ=self.tgt.number+self.tgt.neutrons)

        utils.find_and_replace(os.path.join(PACKAGE_DIRECTORY,
                                            'templates/neut_script.sh'),
                               out_script,
                               ZRUNNUMZ=self.runnum,
                               ZCARDFILEZ=out_card,
                               ZOUTDIRZ=outdir)

        os.chmod(out_script, 0755)
        return out_script


    def build_nuwro(self):
        """Modifies the template/nuwro.card and nuwro_script. Formats card
        file appropriately first and then builds the script for
        submission.
        """
        outdir = self._outdir('nuwro')
        out_card = os.path.join(outdir,
                                '.cards',
                                'nuwro_{0}.card'.format(self.runnum))
        # the name of the script is taken as the sge job name and thus it
        # must be unique
        out_script = os.path.join(outdir,
                                  '.scripts',
                                  'nuwro_script_{0}_{1}.sh'.
                                  format('_'.join(self.category),
                                         self.runnum))

        utils.make_dirs_if_needed(os.path.dirname(out_card))
        utils.make_dirs_if_needed(os.path.dirname(out_script))

        utils.find_and_replace(os.path.join(PACKAGE_DIRECTORY,
                                            'templates/nuwro.card'),
                               out_card,
                               ZNTESTEVENTSZ=100*self.nevents,
                               ZNEVENTSZ=self.nevents,
                               ZNUPDGZ=self.nupdg,
                               ZNUPMEVZ=self.nupgev*1e3,
                               ZNNZ=self.tgt.neutrons,
                               ZNPZ=self.tgt.protons)

        utils.find_and_replace(os.path.join(PACKAGE_DIRECTORY,
                                            'templates/nuwro_script.sh'),
                               out_script,
                               ZRUNNUMZ=self.runnum,
                               ZCARDFILEZ=out_card,
                               ZOUTDIRZ=outdir)

        os.chmod(out_script, 0755)
        return out_script
