MADS is an open-source code designed as an integrated high-performance
computational framework performing a wide range of model-based analyses:
Sensitivity Analysis, Parameter Estimation, Model Inversion and
Calibration, Uncertainty Quantification, Model Selection and Averaging,
and Decision Support.

MADS utilizes adaptive rules and techniques which allows the analyses to
be performed with minimum user input. The code provides a series of
alternative algorithms to perform each type of model analyses. The code
allows for coupled model parameters and regularization terms that are
internally computed based on user-defined mathematical expressions.

For more information check out he MADS website at http://mads.lanl.gov

USAGE: mads problem\_name [ keywords | options ] OR mads
MADS\_input\_file [ keywords | options ] OR mads PEST\_input\_file [
keywords | options ]\
 (MADS is compatible with PEST control, template and instruction files)
mads (execution without arguments provides information about
command-line keywords)

Licensing: GPLv3: http://www.gnu.org/licenses/gpl-3.0.html

Download: http://gitlab.com/monty/mads
http://github.com/montyvesselinov/MADS
http://bitbucket.org/monty\_vesselinov/mads

Clone GIT repositories: git clone git@gitlab.com:monty/mads.git\
 git clone git@github.com:montyvesselinov/MADS.git git clone
git@bitbucket.org:monty\_vesselinov/mads.git

Required libraries: GSL: http://www.gnu.org/s/gsl LAPACK:
http://www.netlib.org/lapack/ BLAS: http://www.netlib.org/blas/
MATHEVAL: http://www.gnu.org/software/libmatheval/ YAML:
http://pyyaml.org/wiki/LibYAML; http://www.yaml.org GLIB:
http://developer.gnome.org/glib/ PKG-CONFIG:
http://www.freedesktop.org/wiki/Software/pkg-config/

MAC OS X installation of required libraries: sudo port install gsl glib2
libyaml libmatheval pkgconfig

RHEL/CentOS/Fedora installation of required libraries:\
 sudo yum install gsl glib2 libyaml libmatheval pkgconfig

Ubuntu/Debian installation of required libraries: sudo apt-get install
libgsl0-dev libglib2.0-0 libyaml-0-2 libmatheval1 pkg-config

Compilation: make

Verification (TCSH shell is needed to run verification scripts): make
verify (all test problems listed below) make verify-internal (internal
test functions) make verify-forward (forward contaminant transport
simulations) make verify-contaminant (inverse contaminant transport
analyses) make verify-multistart1 verify-multistart2 (multi-start
inverse problems using random initial parameter guesses) make
verify-external verify-external-short (inverse problems using the code
WELLS; http://wells.lanl.gov) make verify-parallel (parallel inverse
analysis) make verify-sa (global sensitivity analysis)

Examples: make examples (the code WELLS is needed;
http://wells.lanl.gov) In addition, several examples can be found in
directory 'example' (check the 'readme' files in the directory
'example') See also http://mads.lanl.gov/\#examples and
http://mads.lanl.gov/\#demos

Comparisons: Comparisons with the code PEST are available as well (in
subdirectories of 'example', check the 'readme' files) See also
http://mads.lanl.gov/\#comparisons

Manual: http://mads.lanl.gov/\#manual

Additional information: http://mads.lanl.gov
http://www.ees.lanl.gov/staff/monty/codes/mads email: Velimir V
Vesselinov (monty) vvv@lanl.gov -:- velimir.vesselinov@gmail.com