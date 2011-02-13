PROG = mads
CC = gcc 
## rainier -L/usr/lib/gcc/x86_64-redhat-linux/4.1.1
ifeq ($(OSTYPE),linux)
        DIRS = -I/home/monty/local/include/ -L/home/monty/local/lib
	LG = -lgfortran
else
        DIRS = -I/opt/local/include/ -L/opt/local/lib
endif
CFLAGS = -Wall $(DIRS)
LDLIBS = -lgsl -lm -lgslcblas -llapack -lblas $(LG) $(DIRS)
OBJSMADS = mads.o mads_io.o mads_func.o mads_mem.o lm/opt_lm_mon.o lm/opt_lm_gsl.o lm/lu.o lm/opt_lm_ch.o misc/test_problems.o misc/anasol_contamination.o misc/io.o pesting/pesting.o lhs/lhs.o pso/pso-tribes-lm.o pso/Standard_PSO_2006.o abagus/abagus.o
OBJSMPUN = mprun/mprun.o mprun/mprun_io.o
OBJSKDTREE = abagus/kdtree-0.5.5/kdtree.o
OBJSLEVMAR = levmar-2.5/lm_m.o levmar-2.5/Axb.o levmar-2.5/misc.o levmar-2.5/lmlec.o levmar-2.5/lmbc.o levmar-2.5/lmblec.o levmar-2.5/lmbleic.o

all: $(PROG)

$(PROG): $(OBJSMADS) $(OBJSMPUN) $(OBJSLEVMAR) $(OBJSKDTREE)

mads.o: mads.c mads.h levmar-2.5/levmar.h
mads_io.o: mads_io.c mads.h
mads_func.o: mads_func.c mads.h
mads_mem.o: mads_mem.c
mprun/mprun.o: mprun/mprun.c mads.h
mprun/mprun_io.o: mprun/mprun_io.c
lm/opt_lm_mon.o: lm/opt_lm_mon.c mads.h
lm/opt_lm_gsl.o: lm/opt_lm_gsl.c mads.h
lm/opt_lm_ch.o: lm/opt_lm_gsl.c mads.h
lhs/lhs.o: lhs/lhs.c
misc/test_problems.o: misc/test_problems.c mads.h
misc/anasol_contamination.o: misc/anasol_contamination.c mads.h
pesting/pesting.o: pesting/pesting.c mads.h
pso/pso-tribes-lm.o: pso/pso-tribes-lm.c pso/pso.h mads.h
pso/Standard_PSO_2006.o: pso/Standard_PSO_2006.c mads.h
abagus/abagus.o: abagus/abagus.c mads.h abagus/kdtree-0.5.5/kdtree.o
abagus/kdtree-0.5.5/kdtree.o: abagus/kdtree-0.5.5/kdtree.c abagus/kdtree-0.5.5/kdtree.h
levmar-2.5/lm_m.o: levmar-2.5/lm_m.c levmar-2.5/lm_core_m.c levmar-2.5/levmar.h levmar-2.5/misc.h levmar-2.5/compiler.h mads.h
levmar-2.5/Axb.o: levmar-2.5/Axb.c levmar-2.5/Axb_core.c levmar-2.5/levmar.h levmar-2.5/misc.h
levmar-2.5/misc.o: levmar-2.5/misc.c levmar-2.5/misc_core.c levmar-2.5/levmar.h levmar-2.5/misc.h
levmar-2.5/lmlec.o: levmar-2.5/lmlec.c levmar-2.5/lmlec_core.c levmar-2.5/levmar.h levmar-2.5/misc.h
levmar-2.5/lmbc.o: levmar-2.5/lmbc.c levmar-2.5/lmbc_core.c levmar-2.5/levmar.h levmar-2.5/misc.h levmar-2.5/compiler.h
levmar-2.5/lmblec.o: levmar-2.5/lmblec.c levmar-2.5/lmblec_core.c levmar-2.5/levmar.h levmar-2.5/misc.h
levmar-2.5/lmbleic.o: levmar-2.5/lmbleic.c levmar-2.5/lmbleic_core.c levmar-2.5/levmar.h levmar-2.5/misc.h

clean:
	rm -f $(PROG) $(OBJSMADS) $(OBJSLEVMAR) $(OBJSKDTREE)

tar:
	tar -cvzf mads.tgz `hg st -c -m | awk '{print $$2}'` `find . \( -name "*.[ch]" -o -name "[Mm]akef*" \) -print | sed 's/\.\///'` .hg
